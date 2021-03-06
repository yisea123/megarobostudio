#include "deviceMRQ.h"

#ifdef DEVICE_EMIT_SIGNAL
#include "../../app/dpcobj.h"
#endif

namespace MegaDevice
{

//! load only one time
int deviceMRQ::loadTpvCap( )
{
    int ret;
    tpvRegion region;

    //! read again
    uint16 cap;
    foreach_page()
    {
        ret = getMOTIONPLAN_REMAINPOINT( _i, _axPage, &cap );
        if ( ret != 0 )
        { return ret; }

        region.setRegion( _i, _j );
        Q_ASSERT( mTpvCaps.contains(region) );

        mTpvCaps[ region ] = cap;
    }
    end_foreach_page()

    uint32 bufSize;
    foreach_page()
    {
        ret = getMOTIONPLAN_BUFFERSIZE( _i, _axPage, &bufSize );
        if ( ret != 0 )
        { return ret; }

        region.setRegion( _i, _j );
        Q_ASSERT( mTpvBufferSizes.contains(region) );

        mTpvBufferSizes[ region ] = bufSize;
    }
    end_foreach_page()

    return 0;
}

int deviceMRQ::getTpvCap( const tpvRegion &region )
{
    Q_ASSERT( mTpvCaps.contains(region) );
    return mTpvCaps[ region ];
}
int deviceMRQ::getTpvBuf( pvt_region )
{
    Q_ASSERT( mTpvBufferSizes.contains(region) );
    return mTpvBufferSizes[ region ];
}

//! vernier/ratio/step angle
int deviceMRQ::loadMotorBasic()
{
    int ret;
    for ( byte i = 0; i < axes(); i++ )
    {
        ret = getMOTOR_STEPANGLE( i, &mMOTOR_STEPANGLE[i] );
        if ( ret != 0 )
        { return ret; }

        ret = getMOTOR_GEARRATIONUM( i, &mMOTOR_GEARRATIONUM[i] );
        if ( ret != 0 )
        { return ret; }

        ret = getMOTOR_GEARRATIODEN( i, &mMOTOR_GEARRATIODEN[i] );
        if ( ret != 0 )
        { return ret; }

        ret = getMOTOR_LEAD( i, &mMOTOR_LEAD[i] );
        if ( ret != 0 )
        { return ret; }

        ret = getMOTOR_TYPE( i, &mMOTOR_TYPE[i] );

        //! driver
        if ( mDriverId == VRobot::motor_driver_262 )
        {
            ret = getDRIVER_MICROSTEPS( i, &mDRIVER_MICROSTEPS[i] );
            if ( ret != 0 )
            { return ret; }
        }
        else if ( mDriverId == VRobot::motor_driver_820 )
        {
            ret = getNEWDRIVER_MICROSTEPS( &mNEWDRIVER_MICROSTEPS );
            if ( ret != 0 )
            { return ret; }
        }
        else
        {}
    }

    return 0;
}

int deviceMRQ::beginTpvDownload( const tpvRegion &region )
{
    int ret;

    DELOAD_REGION();

    //! clear
    checked_call( setMOTIONPLAN_PVTCONFIG( pvt_page_p, MRQ_MOTIONPLAN_PVTCONFIG_1_CLEAR ) );

    //! reset
    checked_call( setMOTION_SWITCH( region.axes(),
                                    MRQ_MOTION_SWITCH_RESET,
                                    (MRQ_MOTION_SWITCH_1)region.page()) );

    //! force to program
    ((MrqFsm*)Fsm( region ))->setState( MegaDevice::mrq_state_program );

    //! \errant exec mode to cycle
    checked_call( setMOTIONPLAN_EXECUTEMODE( pvt_page_p,
                                             MRQ_MOTIONPLAN_EXECUTEMODE_1_CYCLE) );
//    checked_call( setMOTION_STATEREPORT( ax, MRQ_MOTION_STATEREPORT_QUERY ) );

    setTpvIndex( pvt_region_p, 0 );

    //! cache slew rst
    mSlewCache[ region ] = 0;

    return ret;
}

int deviceMRQ::tpvDownload(
                 const tpvRegion &region,
                 int index,
                 f32 t,
                 f32 p,
                 f32 v )
{
    int ret;

    DELOAD_REGION();

    QList<frameData> tpvPacks;
    frameData framePackage;
    float val;
    int16 i16Val;

    //! scale
    if ( index == 1 && mSlewCache[region] < 1 )
    {
        framePackage.clear();
        framePackage.setFrameId( mDeviceId.mRecvId );
        framePackage.append( (byte)MRQ_mc_TIMESCALE );
        framePackage.append( (byte)ax );
        framePackage.append( (byte)page );
        framePackage.append( (byte)index );

        i16Val = mAccList.at(ax);
        framePackage.append( (const char*)&i16Val, sizeof(i16Val) );

        i16Val = mDecList.at(ax);
        framePackage.append( (const char*)&i16Val, sizeof(i16Val) );

        tpvPacks.append( framePackage );

        //! set cache
        mSlewCache[ region] = 1;
    }

    //! p
    framePackage.clear();
    framePackage.setFrameId( mDeviceId.mRecvId );
    framePackage.append( (byte)MRQ_mc_POSITION );
    framePackage.append( (byte)ax );
    framePackage.append( (byte)page );
    framePackage.append( (byte)index );
    val = p ;
    framePackage.append( (const char*)&val, sizeof(val) );
    tpvPacks.append( framePackage );

    //! v
    framePackage.clear();
    framePackage.setFrameId( mDeviceId.mRecvId );
    framePackage.append( (byte)MRQ_mc_VELOCITY );
    framePackage.append( (byte)ax );
    framePackage.append( (byte)page );
    framePackage.append( (byte)index );
    val = v;
    framePackage.append( (const char*)&val, sizeof(val) );
    tpvPacks.append( framePackage );

    //! t
    framePackage.clear();
    framePackage.setFrameId( mDeviceId.mRecvId );
    framePackage.append( (byte)MRQ_mc_TIME );
    framePackage.append( (byte)ax );
    framePackage.append( (byte)page );
    framePackage.append( (byte)index );
    val = t;
    framePackage.append( (const char*)&val, sizeof(val) );
    tpvPacks.append( framePackage );

    ret = m_pBus->doWrite( tpvPacks );

    return ret;
}
int deviceMRQ::tpvDownload( const tpvRegion &region,
                 QList<tpvRow *> &list,
                 int from,
                 int len )
{
    int ret = 0;

    DELOAD_REGION();

    int id = 0;
    for( int i = 0; i < mMOTIONPLAN_REMAINPOINT[ax][page] && i < len && id < list.size(); i++ )
    {
        id = i + from;
        checked_call( tpvDownload( region,
                                   i,
                                   list[id]->mT,
                                   list[id]->mP,
                                   list[id]->mV
                                   )
                      );

        #ifdef DEVICE_EMIT_SIGNAL
        dpcObj::instance()->tlsProgress( i, 0, len );
        logDbg()<<i;
        #endif
    }

    return ret;
}

int deviceMRQ::tpvDownload( pvt_region,
                            tpvRow *pItem )
{
    Q_ASSERT( NULL != pItem );
    int ret;

    checked_call( tpvDownload( pvt_region_p,
                               getTpvIndex( pvt_region_p ),
                               pItem->mT,
                               pItem->mP,
                               pItem->mV
                               )
                  );

    accTpvIndex( pvt_region_p );

    return ret;
}

int deviceMRQ::endTpvDownload( pvt_region )
{
    int ret;

    DELOAD_REGION();

    checked_call( setMOTIONPLAN_PVTCONFIG( pvt_page_p, MRQ_MOTIONPLAN_PVTCONFIG_1_END ) );

    return ret;
}

int deviceMRQ::tpvDownloadMission( pvt_region,
                                   QList<tpvRow *> &list,
                                   int from,
                                   int len )
{
    int ret;

    checked_call( beginTpvDownload( pvt_region_p ) );

    ret = tpvDownload( pvt_region_p, list, from, len );

    checked_call( endTpvDownload( pvt_region_p ) );

    return ret;
}

int deviceMRQ::pvtWrite( pvt_region,
              QList<tpvRow *> &list,
              int from,
              int len )
{
    //! verify the memory
    if( pvtVerify( region, list ) )
    { }
    else
    {
        sysPrompt( QObject::tr("pvt verify fail: memory overflow") );
        return ERR_CAN_NOT_RUN;
    }

    Q_ASSERT( mMrqFsms.contains(region) );
    mMrqFsms[ region ]->setState( mrq_state_program );

    tpvDownloader *pLoader = downloader( region );
    Q_ASSERT( NULL != pLoader );

    if ( pLoader->isRunning() && !pLoader->wait( 10000 ) )
    {
        sysError( QObject::tr("Busy now, can not download") );
        sysError( QString::number(region.axes()), QString::number(region.page()) );
        return ERR_CAN_NOT_RUN;
    }
    else
    {}

    int ret;
    {
        //! check end state
        int lastIndex;
        if ( len == -1 )
        { lastIndex = list.size() - 1; }
        else
        { lastIndex = from + len - 1; }

        //! check nan
        Q_ASSERT( !qIsNaN(list.at(lastIndex)->mV) );
        if ( list.at(lastIndex)->mV != 0 )
        {
            ret = setMOTIONPLAN_ENDSTATE( region.axes(),
                                          (MRQ_MOTION_SWITCH_1)region.page(),
                                          MRQ_MOTIONPLAN_ENDSTATE_1_HOLD );
            if ( ret != 0 )
            { sysError( QObject::tr("end speed keeped fail") ); }
            else
            {
                sysLog( QString::number( list.at(lastIndex)->mV) );
                sysLog( QObject::tr("end speed keeped") );
            }
        }
        else
        {
            ret = setMOTIONPLAN_ENDSTATE( region.axes(),
                                          (MRQ_MOTION_SWITCH_1)region.page(),
                                          MRQ_MOTIONPLAN_ENDSTATE_1_STOP );
            if ( ret != 0 )
            { sysError( QObject::tr("end speed stoped fail") ); }
            else
            {  }
        }

        //! motion mode: pvt, lvt1, lvt2
        //! valid motion mode
        if ( region.motionMode() >= 0 )
        {
            ret = setMOTIONPLAN_MOTIONMODE( region.axes(),
                                          (MRQ_MOTION_SWITCH_1)region.page(),
                                          (MRQ_MOTIONPLAN_MOTIONMODE_1)region.motionMode() );
            if ( ret != 0 )
            { sysError( QObject::tr("motion mode fail") ); }
        }

        pLoader->append( list, from, len );
        pLoader->setRegion( region );
        pLoader->start();
    }

    return 0;
}

int deviceMRQ::pvtWrite( pvt_region,
              float t1, float p1,
              float t2, float p2,
              float endV
              )
{
    DELOAD_REGION();

    //! point 1
    tpvRow *pRow1 = new tpvRow();
    if ( NULL == pRow1 )
    { return ERR_ALLOC_FAIL; }

    pRow1->setGc( true );
    pRow1->mT = t1;
    pRow1->mP = p1;
    pRow1->mV = 0;

    //! point 2
    tpvRow *pRow2 = new tpvRow();
    if ( NULL == pRow2 )
    {
        delete pRow1;
        return ERR_ALLOC_FAIL;
    }

    pRow2->setGc( true );
    pRow2->mT = t2;
    pRow2->mP = p2;
    pRow2->mV = endV;

    QList< tpvRow *> rotList;
    rotList.append( pRow1 );
    rotList.append( pRow2 );

    return pvtWrite( pvt_region_p, rotList );
}

int deviceMRQ::pvtWrite( pvt_region,
                         float dT,
                         float dAngle,
                         float endV )
{
//    Q_ASSERT( dT > 0 );
    if ( dT > 0 )
    {}
    else
    { return -1; }

    return pvtWrite( pvt_region_p, 0, 0, dT, dAngle, endV );
}

int deviceMRQ::pvtWrite( pvt_region,
              tpvRow *pRows,
              int n
              )
{
    Q_ASSERT( NULL != pRows );

    QList< tpvRow *> transRows;
    tpvRow *pRow;
    for ( int i = 0; i < n; i++ )
    {
        pRow = new tpvRow();
        if ( NULL == pRow )      //! new fail
        {
            delete_all(transRows);
            return -1;
        }

        //! copy
        *pRow = pRows[i];
        pRow->setGc( true );

        transRows.append( pRow );
    }

    return pvtWrite( pvt_region_p, transRows );
}

int deviceMRQ::pvtWrite( pvt_region,
              QList<tpvRow> &rows )
{
    QList< tpvRow *> transRows;
    tpvRow *pRow;
    for ( int i = 0; i < rows.size(); i++ )
    {
        pRow = new tpvRow();
        if ( NULL == pRow )      //! new fail
        {
            delete_all(transRows);
            return -1;
        }

        //! copy
        *pRow = rows.at(i);
        pRow->setGc( true );

        transRows.append( pRow );
    }

    return pvtWrite( pvt_region_p, transRows );
}

void deviceMRQ::setTpvIndex( pvt_region, int index )
{
    DELOAD_REGION();

    Q_ASSERT( mTpvIndexes.contains(region) );

    mTpvIndexes[ region ] = index;
}
int  deviceMRQ::getTpvIndex( pvt_region )
{
    DELOAD_REGION();

    Q_ASSERT( mTpvIndexes.contains(region) );

    return mTpvIndexes[ region ];
}
void deviceMRQ::accTpvIndex( pvt_region )
{
    DELOAD_REGION();

    Q_ASSERT( mTpvIndexes.contains(region) );

    //! turn around
    mTpvIndexes[ region ] = mTpvIndexes[ region ] + 1;
    if ( mTpvIndexes[ region ] >= mTpvCaps[region] )
    {
        mTpvIndexes[ region ] = 0;
    }
    else
    {}
}

bool deviceMRQ::pvtVerify( pvt_region,
                QList<tpvRow *> &list )
{
    //! region ax
    if ( region.axes() < 0 || region.axes() >= axes() )
    {
        sysError( QObject::tr("Invalid axes %1").arg( region.axes() ) );
        return false;
    }

    //! region page
    if ( region.page() < 0 || region.page() >= regions() )
    {
        sysError( QObject::tr("Invalid page %1").arg( region.page() ) );
        return false;
    }

    //! sum the dist
    if ( list.size() < 2 )
    {
        sysError( QObject::tr("Inefficient data %1").arg( list.size()) );
        return false;
    }

    float dist = 0;
    for( int i = 1; i < list.size(); i++ )
    {
        dist += qAbs( list.at(i)->mP - list.at(i-1)->mP );
    }

    Q_ASSERT( stepAngle( region.axes() ) > 0 );

    //! calc the mem
    //! dist * slow ratio * micro / step angle
    float memDot = dist * deviceMRQ::_mPBase
                    * slowRatio( region.axes() )
                    * microStep( region.axes() )
                    / stepAngle( region.axes() );
    if ( memDot < 0 )
    {
        Q_ASSERT( memDot >= 0 );
        logDbg()<<dist<<deviceMRQ::_mPBase<<slowRatio( region.axes() )<<microStep( region.axes() )<<stepAngle( region.axes() );
    }

    if ( memDot > getTpvBuf( region ) )
    {
        sysError( QObject::tr("Over pvt memory"), QString::number(memDot), QString::number( getTpvBuf(region) ) );
        return false;
    }
    else
    {
//        sysLog( QString::number(memDot), QString::number( getTpvBuf(region) ),
//                QString::number(region.axes()),
//                QString::number(list.size()) );
        return true;
    }
}

}
