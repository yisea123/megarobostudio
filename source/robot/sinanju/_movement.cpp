#include "sinanju.h"
#include "../../com/comassist.h"
#include <float.h>
int robotSinanju::call( int n, const tpvRegion &region )
{
    onLine();

    setLoop( n, region );

    fsm( region )->setState( MegaDevice::mrq_state_calcend );

    lpc()->postMsg( (eRoboMsg)(MegaDevice::mrq_msg_call), region );

    return 0;
}

//! load the data from the file
int robotSinanju::program( const QString &fileName,
                         const tpvRegion &region )
{
    //! 1.load
    int ret;
    ret = loadProgram( fileName );
    if ( ret != 0 )
    { return ret; }

    //! 2.config
    setLoop( 1 );

    //! 3.download
    ret = downloadTrace( region, mJointsGroup );
    if ( ret != 0 )
    { return ret; }

    return 0;
}

//! 0   1   2   3   4    5
//! J1  J2  J3  J4  End Time
//!
//! 0  1 2  3  4  5  6  7  8  9  10
//! t J1 J2 J3 J4 J5 V1 V2 V3 V4 V5
int robotSinanju::loadProgram( const QString &fileName )
{
    QList<float> dataset;
    QList<int> dataCols;
    int col;
    int timeCol, pOffset, vOffset;
    do
    {
        //! try first
        col = 11;
        dataset.clear();
        dataCols.clear();
        dataCols<<0<<1<<2<<3<<4<<5<<6<<7<<8<<9<<10;
        if ( 0 == comAssist::loadDataset( fileName, col, dataCols, dataset ) )
        {logDbg()<<dataset.size();
            timeCol = 0;
            pOffset = 1;
            vOffset = 6;
            break;
        }
        else
        {
        }

        //! try again
        col = 6;
        dataset.clear();
        dataCols.clear();;
        dataCols<<0<<1<<2<<3<<4<<5;
        if ( 0 == comAssist::loadDataset( fileName, col, dataCols, dataset ) )
        {logDbg()<<dataset.size();
            timeCol = 5;
            pOffset = 0;
            vOffset = -1;
            break;
        }
        else
        {  return ERR_INVALID_INPUT; }

    }while( 0 );

    //! convert to tpvitem
    if ( dataset.size() < 2 * col )
    { return ERR_INVALID_INPUT; }logDbg();

    //! file split
    delete_all( mJointsGroup );logDbg();

    //! for 5 axis
    for ( int i = 0; i < 5; i++ )
    {
        tpvGroup *pGroup = new tpvGroup();
        if ( NULL == pGroup )
        { return -1; }logDbg();

        //! for each time
        int ret;
        for ( int j = 0; j < dataset.size() / col; j++ )
        {
            if ( vOffset < 0 )
            {
                ret = pGroup->addItem( dataset.at( j * col + timeCol),     //! time
                                       dataset.at( j * col + pOffset + i ),//! p
                                       0
                                       );
            }
            else
            {
                ret = pGroup->addItem( dataset.at( j * col + timeCol),     //! time
                                       dataset.at( j * col + pOffset + i ),//! p
                                       dataset.at( j * col + vOffset + i ) //! v
                                       );
            }

            if ( ret != 0 )
            {
                delete pGroup;
                return ERR_FAIL_ADD_TPV;
            }
        }

        mJointsGroup.append( pGroup );
    }

//    //! log joint group
//    foreach ( tpvGroup *pGp, mJointsGroup )
//    {
//        logDbg()<<"*******";
//        foreach(  tpvItem *pItem, pGp->mItems )
//        {
//            logDbg()<<pItem->mT<<pItem->mP<<pItem->mV;
//        }
//    }

    return 0;
}

int robotSinanju::program( QList<TraceKeyPoint> &curve,
             const tpvRegion &region )
{
    int ret;

    //! 0. loop
    setLoop( 1, region );

    //! 1.build
    delete_all( mJointsGroup );

    xxxGroup<tracePoint> tracePlan;
    xxxGroup<jointsTrace> jointsPlan;

    ret = buildTrace( curve, tracePlan, jointsPlan );
    if ( ret != 0 )
    { return ret; }

    //! 2.convert
    QList<int> secList;
    ret = convertTrace( curve, jointsPlan, mJointsGroup, secList );
    if ( ret != 0 )
    { return ret; }

    //! 3.download
    ret = downloadTrace( region, mJointsGroup );
    if ( ret != 0 )
    { return ret; }

    //! 4.export
//    int lastPt = curve.size() - 1;
//    QString fileName = QString( "%1_%2_%3-%4_%5_%6.csv" ).arg( curve.at(0).x ).arg( curve.at(0).y ).arg( curve.at(0).z )
//                                                     .arg( curve.at(lastPt).x ).arg( curve.at(lastPt).y ).arg( curve.at(lastPt).z );
//    exportPlan( QCoreApplication::applicationDirPath() + "/dump/" + "plan_" + fileName, tracePlan );
//    exportJoints( QCoreApplication::applicationDirPath() + "/dump/" + "joints_" + fileName, jointsPlan );

    return 0;
}

int robotSinanju::move( QList<TraceKeyPoint> &curve,
                        const tpvRegion &region )
{
    int ret;

    //! request run
    run( region );

    //! program
    ret = program( curve, region );

    return ret;
}

int robotSinanju::moveTest1( const tpvRegion &region )
{
    TraceKeyPoint pt1,pt2;
    pt1.t = 0;
    pt1.x = 280;
    pt1.y = 21.5;
    pt1.z = 452.75;
    pt1.hand = 0;

    pt2.t = 1;
    pt2.x = 250;
    pt2.y = 0;
    pt2.z = 502;
    pt2.hand = 270;

    QList<TraceKeyPoint> curve;
    curve.append( pt1 );
    curve.append( pt2 );
//    return moveTest( pt1, pt2, dt );
// MOVE 280,21.5,452.75,0,250,0,502,90,1
// MOVE 250,0,502,90,280,21.5,452.75,0,1
    return move( curve, region );
}

int robotSinanju::moveTest2( const tpvRegion &region )
{
    TraceKeyPoint pt1,pt2;
    pt1.t = 1;
    pt1.x = 280;
    pt1.y = 21.5;
    pt1.z = 452.75;
    pt1.hand = 0;

    pt2.t = 0;
    pt2.x = 250;
    pt2.y = 0;
    pt2.z = 502;
    pt2.hand = 270;

    //! p2 -> p1
    QList<TraceKeyPoint> curve;
    curve.append( pt2 );
    curve.append( pt1 );

    return move( curve, region );
}


#define ref_angle(id)   mRefAngles.at(id)
#define rot_angle(id)   mRotateAngles.at(id)
#define arm_len(id)     mArmLengths.at(id)

#define ref_angles( id1,id2,id3,id4 )   ref_angle( id1 ),\
                                        ref_angle( id2 ),\
                                        ref_angle( id3 ),\
                                        ref_angle( id4 ),
#define rot_angles( id1,id2,id3,id4 )   rot_angle( id1 ),\
                                        rot_angle( id2 ),\
                                        rot_angle( id3 ),\
                                        rot_angle( id4 ),
#define arm_lens( id1,id2,id3,id4,id5,id6 )     arm_len( id1 ),\
                                                arm_len( id2 ),\
                                                arm_len( id3 ),\
                                                arm_len( id4 ),\
                                                arm_len( id5 ),\
                                                arm_len( id6 ),
int robotSinanju::nowPose( TraceKeyPoint &pos )
{
    //! get
    float angles[4];
    if ( nowAngle( angles ) != 0 )
    { return -1; }

    //! convert
    return angleToPos( angles, pos );
}

int robotSinanju::nowAngle( float angles[] )
{
    MegaDevice::deviceMRQ *pDev;
    int ax;

    for ( int i = 0;  i < 4; i++ )
    {
        pDev = jointDevice( i, &ax );
        if ( NULL == pDev )
        { return -1; }

        angles[i] = pDev->getAbsAngle( ax );
        if ( angles[i] < 0 )
        { return -1; }
    }

    return 0;
}

int robotSinanju::nowJointAngle( float angles[4] )
{
    int ret;
    float absAngles[4];

    ret = nowAngle( absAngles );
    if ( ret != 0 )
    { return ret; }

    diffAngle( absAngles, angles );

    //! normalize to [-pi,pi)
    comAssist::normalizeDegreeN180_180( angles, 4 );

    return 0;
}

int robotSinanju::jointMove( int jointId, int subPage, float angle, float t )
{
    MegaDevice::deviceMRQ *pDev;
    int ax;

    pDev = jointDevice( jointId, &ax );
    if ( NULL == pDev )
    { return -1; }

    if ( jointId < 0 || jointId > 3 )
    { return -1; }

    int dirs[]={ -1, 1, 1, -1 };        //! for rviz dir

    return pDev->rotate( tpvRegion(ax, subPage), t, angle * dirs[ jointId ] );
}

#define ref_angle(id)   mRefAngles.at(id)
#define rot_angle(id)   mRotateAngles.at(id)
#define arm_len(id)     mArmLengths.at(id)

#define ref_angles( id1,id2,id3,id4 )   ref_angle( id1 ),\
                                        ref_angle( id2 ),\
                                        ref_angle( id3 ),\
                                        ref_angle( id4 ),
#define rot_angles( id1,id2,id3,id4 )   rot_angle( id1 ),\
                                        rot_angle( id2 ),\
                                        rot_angle( id3 ),\
                                        rot_angle( id4 ),
#define arm_lens( id1,id2,id3,id4,id5,id6 )     arm_len( id1 ),\
                                                arm_len( id2 ),\
                                                arm_len( id3 ),\
                                                arm_len( id4 ),\
                                                arm_len( id5 ),\
                                                arm_len( id6 ),
int robotSinanju::angleToPos( float angles[4],
                               TraceKeyPoint &pos )
{
    //! convert
    jointsAngle rotAngles={ rot_angles(0,1,2,3) };
    jointsAngle archAngles={ mArchAngles.at(0),
                             mArchAngles.at(1),
                             mArchAngles.at(2),
                             mArchAngles.at(3),
                            };
    double armLength[]={ arm_lens(0,1,2,3,4,5) };
    double dAngles[4];
    double xyz[3];
    int ret;

    //! ref the the zero
    diffAngle( angles, dAngles );

    ret = ns_sinanju::GetEndPosition( armLength,sizeof_array(armLength),
                                        rotAngles.angles,
                                        archAngles.angles,
                                        dAngles,
                                        4,
                                        xyz
                                        );
    if ( ret != 0 )
    { return -1; }

    //! export
    pos.hand = 0;
    pos.x = double_to_float( xyz[0] );
    pos.y = double_to_float( xyz[1] );
    pos.z = double_to_float( xyz[2] );
    pos.t = 0;

    //! coord i rotate
    coordIRotate( pos );

    return 0;
}

//! - init angle
void robotSinanju::diffAngle( float angles[4],
                              float anglesOut[4]  )
{
    Q_ASSERT( mAngleDir.size() == 4 );

    for ( int i = 0; i < 4; i++ )
    {
        anglesOut[i] = (angles[i] - mInitAngles.at(i));
    }

    int signs[]={ -1, -1, 1, 1 };

    //! direction
    for ( int i = 0; i < 4; i++ )
    {
        anglesOut[i] = signs[i] * anglesOut[i];

        anglesOut[i] = comAssist::normalizeDegree360( anglesOut[i] );
    }
}
//! - init angle
void robotSinanju::diffAngle( float angles[4],
                              double anglesOut[4]  )
{
    Q_ASSERT( mAngleDir.size() == 4 );

    for ( int i = 0; i < 4; i++ )
    {
        anglesOut[i] = (angles[i] - mInitAngles.at(i));
    }

    //! direction
    for ( int i = 0; i < 4; i++ )
    {
        if ( mAngleDir.at(i) )
        {}
        else
        { anglesOut[i] = -anglesOut[i]; }

        anglesOut[i] = comAssist::normalizeDegree360( anglesOut[i] );
    }
}

int robotSinanju::nowDist( QList<float> &dists )
{
    //! get
    float dist;
    MegaDevice::deviceMRQ *pDev;
    int ax;
    for ( int i = 0;  i < 4; i++ )
    {
        pDev = jointDevice( i, &ax );
        if ( NULL == pDev )
        { return -1; }

        dist = pDev->getDist( ax );
        dists.append( dist );
    }

    return 0;
}



