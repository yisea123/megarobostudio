
#include "sinanju.h"
#include "sinanjutask.h"

#include "../../device/board/_MRQ_enum.h"

static quint8 _megaimage[]=
{
    #include "./robot.cpp"
};

static quint8 _detail[]=
{
    #include "./detail.cpp"
};

robotSinanju::robotSinanju()
{
    mClass = QObject::tr("MRX-T4");
    mId = robot_sinanju;

    //! default gpid
    mCanGroupId = group_id_from + (mId - robot_complex)*group_segment;

    setAxes( 5 );
    setAxesDefName( 5 );
    setJointName( 5 );

    setPoseCount( 3 );   //! x,y,z
    mPoseTitles.clear();
    mPoseTitles<<"X"<<"Y"<<"Z";

    setAbsCount( 4 );

    mDetail = QString::fromLocal8Bit( (char*)_detail, sizeof_array(_detail) );

    //! joint name
    mJointName.clear();
    mJointName<<QObject::tr("Basement")
              <<QObject::tr("Big Arm")
              <<QObject::tr("Little Arm")
              <<QObject::tr("Wrist")
              <<QObject::tr("Hand");

    mImage = QImage::fromData( _megaimage, sizeof(_megaimage) );

    //! angles
    mJointAngleMask[0]=true;
    mJointAngleMask[1]=true;
    mJointAngleMask[2]=true;
    mJointAngleMask[3]=true;

    mJointCcwMask.clear();
    mJointCcwMask<<false<<false<<false<<false<<true;

    mJointZeroCcw.clear();
    mJointZeroCcw<<false<<false<<false<<false<<true;

    //! angle dir
    mAngleDir.clear();
    mAngleDir<<true<<false<<true<<false;     //! big arm invert

    //! lvt able
    mLvtAble.clear();
    mLvtAble<<true<<true<<true<<true<<false;

    //! zero angle
    //! must be caled
    mInitAngles.clear();
    mInitAngles<<1.553<<5.504<<318<<182.9;

    mInitPos.clear();
    mInitPos<<250<<0<<(257+255);

    //! interp
    mbInterpAble = true;

    //! debug used
    //! alter the axes name
    mAxesConnectionName[0] = "CH1@device1"; //! base
    mAxesConnectionName[1] = "CH2@device1"; //! b Arm
    mAxesConnectionName[2] = "CH3@device1"; //! s Arm
    mAxesConnectionName[3] = "CH4@device1"; //! wrist
    mAxesConnectionName[4] = "CH5@device1"; //! hand

    //! rotate angle
    //! by the arch
    //! ---------
    //! |
    mRotateAngles.append( 0 );
    mRotateAngles.append( 90 );
    mRotateAngles.append( 0 );
    mRotateAngles.append( -90 );

    //! ref
    mRefAngles.append( 0 );
    mRefAngles.append( 180 );
    mRefAngles.append( -90 );
    mRefAngles.append( -90 );

    //! arch angles
    //! angle ref to the pre
    //!  ----
    //!  |  |
    //!  |
    mArchAngles.append( 0 );
    mArchAngles.append( 180 );
    mArchAngles.append( -90 );
    mArchAngles.append( -90 );

    //! arm length
    //! 257, 255, 250, 0, 0, 0
    mArmLengths.append( 257 );
    mArmLengths.append( 255 );
    mArmLengths.append( 250 );
    mArmLengths.append( 0 );

    mArmLengths.append( 0 );
    mArmLengths.append( 0 );

    m_pRoboTask = new SinanjuTask();
    Q_ASSERT( NULL != m_pRoboTask );


    //! zero
    mHandZeroTime = 5;
    mHandZeroAngle = 60;

    mGapTime = 1;
    mGapAngle = 3;

    //! hand
    mbHandAble = true;
    mJointFactoryList.clear();
    mJointFactoryList<<0<<-20<<-65<<100;  //! \ref to the zero
}

robotSinanju::~robotSinanju()
{

}

static msg_type _msg_patterns[]={

    //! member_state
    { e_robot_member_state,
      { QMetaType::Int, TPV_REGEION_TYPE_ID, QMetaType::Int },   //! subax, region, ax
    },

    //! msg
    { MegaDevice::mrq_msg_run,
      { TPV_REGEION_TYPE_ID },  //! region
    },

    { MegaDevice::mrq_msg_stop,
      { TPV_REGEION_TYPE_ID },  //! region
    },

    { MegaDevice::mrq_msg_call,
      { TPV_REGEION_TYPE_ID },  //! region
    },
};

//! \note subax invalid
void robotSinanju::onMsg( int subAxes, RoboMsg &msg )
{
    if ( !RoboMsg::checkMsg( msg, _msg_patterns, sizeof_array(_msg_patterns)) )
    {
        logDbg()<<msg.Msg()<<msg.size();
        return;
    }

    //! for some region
//    tpvRegion region = msg.at(0).value<tpvRegion>();
//    region.set( subAxes, region.page() );
//    tpvRegion region;
    tpvRegion region;
    if ( msg.getMsg() == e_robot_member_state )     //! subax, region, ax
    {
        int tabAx = msg.at(0).toInt();
        region = msg.at(1).value<tpvRegion>();
        Q_ASSERT( tabAx >= 0 && tabAx < axes() );
        region.setAx( 0 );
    }
    else
    {
        region = msg.at(0).value<tpvRegion>();
    }

//    logDbg()<<region.axes()<<region.page();
    Q_ASSERT( region.page() >= 0 && region.page() < regions() );

    fsm( region )->proc( msg.Msg(), msg );
}

int robotSinanju::download( QList<tpvGroup*> &groups,
                             QList<int> &joints,
                             const tpvRegion &region )
{logDbg();
    Q_ASSERT( groups.size() == joints.size() );

    MegaDevice::deviceMRQ *pMrq;
    int axes;
logDbg();
    int ret;
    tpvRegion mrqRegion;
    for ( int i = 0; i < groups.size(); i++ )
    {
        pMrq = jointDevice( joints[i], &axes );

        if ( NULL == pMrq )
        { logDbg()<<mAxesConnectionName[i];return ERR_INVALID_DEVICE_NAME; }

        QList<tpvRow*> rows;
        groups[i]->getRows( rows );
logDbg();
        //! \note change to mrq ax
        mrqRegion = region;
        mrqRegion.setAx( axes );

        //! hand can not lvt
        Q_ASSERT( i < mLvtAble.size() && i >= 0 );
        if ( !mLvtAble.at(i) )
        { mrqRegion.setMotionMode( -1 ); }

        //! send
        ret = pMrq->pvtWrite( mrqRegion, rows );
        if ( ret != 0 )
        { return ret; }
    }
logDbg();
    return 0;
}

int robotSinanju::download( VRobot *pSetup )
{
    Q_ASSERT( NULL != pSetup );

    return 0;
}

int robotSinanju::run( const tpvRegion &region  )
{
    lpc()->postMsg( (eRoboMsg)(MegaDevice::mrq_msg_run), region );
    return 0;
}
int robotSinanju::stop( const tpvRegion &region  )
{
    lpc()->postMsg( (eRoboMsg)(MegaDevice::mrq_msg_stop), region );
    return 0;
}

int robotSinanju::loopNow()
{ return 0; }

//void robotSinanju::onLine()
//{
//    MegaDevice::deviceMRQ *pMrq;
//    int ax;

//    //! each ax
//    for ( int i = 0; i < axes(); i++ )
//    {
//        pMrq = jointDevice( i, &ax );

//        Q_ASSERT( NULL != pMrq );

//        Q_ASSERT( regions() == pMrq->regions() );

//        //! each region
//        for ( int j = 0; j < regions(); j++ )
//        {
//            Q_ASSERT( pMrq->Fsm( tpvRegion(ax,j) ) != NULL );
//            Q_ASSERT( NULL != mFsms[ tpvRegion(0,j) ] );
//            pMrq->Fsm( tpvRegion(ax,j) )->setLeader( mFsms[ tpvRegion(0,j) ],
//                                                    (void*)i );
//        }

//        //! use phy bus
//        attachBus( pMrq->Bus() );
//    }
//}
//void robotSinanju::offLine()
//{
//    MegaDevice::deviceMRQ *pMrq;
//    int ax;

//    //! each ax
//    for ( int i = 0; i < axes(); i++ )
//    {
//        pMrq = jointDevice( i, &ax );

//        //! each region
//        for ( int j = 0; j < regions(); j++ )
//        {
//            Q_ASSERT( pMrq->Fsm( tpvRegion(ax,j) ) != NULL );
//            pMrq->Fsm( tpvRegion(ax,j) )->setLeader( NULL, NULL );
//        }
//    }

//    //! \todo
////    detachBus();
//}

//QAbstractTableModel *robotSinanju::handActions()
//{ return &mHandActionModel; }


void robotSinanju::setHandZeroAttr( double zeroTime, double zeroAngle )
{
    mHandZeroTime = zeroTime;
    mHandZeroAngle = zeroAngle;
}
void robotSinanju::handZeroAttr( double &zeroTime, double &zeroAngle )
{
    zeroTime = mHandZeroTime;
    zeroAngle = mHandZeroAngle;
}

void robotSinanju::setGapAttr( double gapTime, double gapAngle )
{
    mGapTime = gapTime;
    mGapAngle = gapAngle;
}
void robotSinanju::gapAttr( double &gapTime, double &gapAngle )
{
    gapTime = mGapTime;
    gapAngle = mGapAngle;
}

void robotSinanju::setHandAble( bool b )
{ mbHandAble = b; }
bool robotSinanju::handAble()
{ return mbHandAble; }

void robotSinanju::setJointFactoryAngle( int id, double angle )
{
    Q_ASSERT( id >= 0 && id < mJointFactoryList.size() );
    mJointFactoryList[ id ] = angle;
}
double robotSinanju::jointFactoryAngle( int id )
{
    return mJointFactoryList.at(id);
}
