#include "deviceMRQ.h"

#include "scpi/scpi.h"


#define DEF_TPV_CAP     256
#define INC_ANGLE_TO_DEG( angle )   (360.0f*angle)/(1<<18)
#define ABS_ANGLE_TO_DEG( angle )   (360.0f*angle)/((1<<18)-1)

namespace MegaDevice
{

deviceMRQ::deviceMRQ()
{
    //! downloader in ctor

    //! fsm in post ctor

    //! proxy motor in post ctor

    //! \note only a sema for one device
    mDownloaderSema.release( 1 );
}

deviceMRQ::~deviceMRQ()
{
    //! stop
    foreach( tpvDownloader *value, mDownloaders )
    {
        Q_ASSERT( NULL != value );
        if ( value->isRunning() )
        {
            value->terminate();
            value->wait();
        }
    }

    //! fsm
    foreach (MrqFsm * value, mMrqFsms )
    {
        Q_ASSERT( NULL != value );
        delete value;
    }
    mMrqFsms.clear();

    //! proxy motor
    foreach(deviceProxyMotor *value, mProxyMotors )
    {
        Q_ASSERT( NULL != value );
        delete value;
    }

    //! downloader
    foreach( tpvDownloader *value, mDownloaders )
    {
        Q_ASSERT( NULL != value );
        delete value;
    }
}

void deviceMRQ::postCtor()
{
    tpvRegion region;
    //! fsm
    MrqFsm *pFsm;
    deviceProxyMotor *pProxyMotor;
    tpvDownloader *pLoader;
    for ( int i = 0; i < axes(); i++ )
    {
        for ( int j = 0; j < regions(); j++ )
        {
            region.setRegion( i, j );

            //! fsm
            pFsm = new MrqFsm();
            Q_ASSERT( NULL != pFsm );

            //! set region
            pFsm->setRegion( i, j );

            pFsm->build();
            pFsm->setContext( this );
            pFsm->setId( (quint32)this, i, j );
            mMrqFsms.insert( region, pFsm );

            //! motor proxy
            pProxyMotor = new deviceProxyMotor( this,
                                                region );
            Q_ASSERT( NULL != pProxyMotor );
            mProxyMotors.insert( region, pProxyMotor );

            //! tpv caps
            mTpvCaps.insert( region, DEF_TPV_CAP );logDbg()<<region.axes()<<region.page();
            mTpvIndexes.insert( region, 0 );
        }

        //! \note only axes() downloaders
        pLoader = new tpvDownloader();
        Q_ASSERT( NULL != pLoader );
        pLoader->attachDevice( this, tpvRegion(i,0) );
        mDownloaders.insert( i, pLoader );
    }
}

MRQ_model *deviceMRQ::getModel()
{
    return this;
}

int deviceMRQ::getREPORT_DATA_( byte val0
,MRQ_REPORT_STATE val1, quint8 * val2, bool bQuery )
{
    //! 60 4
    int ret = 0;

    uint8 lval0 = 0;
    ret = m_pBus->read( DEVICE_RECEIVE_ID, mc_REPORT, sc_REPORT_DATA_Q , val0, (byte)val1, &lval0, bQuery);
    if ( ret != 0){ log_device(); }
    if ( ret != 0) return ret;
    *val2 = lval0;
    return 0;
}

int deviceMRQ::getREPORT_DATA_( byte val0
,MRQ_REPORT_STATE val1, quint16 * val2, bool bQuery )
{
    //! 60 4
    int ret = 0;

    uint16 lval0 = 0;
    ret = m_pBus->read( DEVICE_RECEIVE_ID, mc_REPORT, sc_REPORT_DATA_Q , val0, (byte)val1, &lval0, bQuery);
    if ( ret != 0){ log_device(); }
    if ( ret != 0) return ret;
    *val2 = lval0;
    return 0;
}

int deviceMRQ::getREPORT_DATA_( byte val0
,MRQ_REPORT_STATE val1, quint32 * val2, bool bQuery )
{
    //! 60 4
    int ret = 0;

    uint32 lval0 = 0;
    ret = m_pBus->read( DEVICE_RECEIVE_ID, mc_REPORT, sc_REPORT_DATA_Q , val0, (byte)val1, &lval0, bQuery);
    if ( ret != 0){ log_device(); }
    if ( ret != 0) return ret;
    *val2 = lval0;
    return 0;
}

struct reportType
{
    MRQ_REPORT_STATE mStat;
    QMetaType::Type mType;
};

//! const special type
static reportType _report_types[]=
{
    { MRQ_REPORT_STATE_DIST, QMetaType::UShort },

};

QMetaType::Type deviceMRQ::getREPORT_TYPE( MRQ_REPORT_STATE stat )
{
    for( int i = 0; i < sizeof_array(_report_types); i++ )
    {
        if ( stat == _report_types[i].mStat )
        { return _report_types[i].mType; }
    }

    return QMetaType::UInt;
}

//! [0~360)
float deviceMRQ::getIncAngle( int ax )
{
    int ret;
    quint32 xangle;

    ret = MRQ::getREPORT_DATA( ax, MRQ_REPORT_STATE_XANGLE, &xangle );
    if ( ret != 0 )
    { return -1; }
    else
    {
        return INC_ANGLE_TO_DEG( xangle );
    }
}

//! [0~360)
float deviceMRQ::getAbsAngle( int ax )
{
    int ret;
    quint32 xangle;

    ret = MRQ::getREPORT_DATA( ax, MRQ_REPORT_STATE_ABSENC, &xangle );
    if ( ret != 0 )
    { return -1; }
    else
    {
        return ABS_ANGLE_TO_DEG( xangle );
    }
}

//! mm
float deviceMRQ::getDist( int ax )
{
    int ret;
    quint32 dist;

    ret = getREPORT_DATA_( ax, MRQ_REPORT_STATE_DIST, &dist );
    if ( ret != 0 )
    { return -1; }
    else
    {
        //! only lw
        dist = dist & 0xffff;
        return dist;
    }
}

float deviceMRQ::getSensor( int ax, int dataId )
{
    if ( dataId == MRQ_REPORT_STATE_DIST )
    { return getDist( ax); }
    else if ( dataId == MRQ_REPORT_STATE_XANGLE )
    { return getIncAngle( ax ); }
    else if ( dataId == MRQ_REPORT_STATE_ABSENC )
    { return getAbsAngle( ax ); }
    else
    { return 0; }
}

//! only write no read
int deviceMRQ::requestMotionState( pvt_region )
{
    int ret;

    DELOAD_REGION();

    ret = m_pBus->write( DEVICE_RECEIVE_ID,
                         mc_MOTION,
                         sc_MOTION_STATE_Q,
                         (byte)ax,
                         (byte)page );

    return ret;
}

void deviceMRQ::terminate( pvt_region )
{
    tpvDownloader *pLoader;
    pLoader = downloader( region );

    pLoader->terminate();
    pLoader->wait();


    sysQueue()->postMsg( e_download_terminated,
                         pLoader->name(),
                         pLoader->axes() );

}
void deviceMRQ::acquireDownloader()
{
    mDownloaderSema.acquire();
}
void deviceMRQ::releaseDownloader()
{
    mDownloaderSema.release();
}

//! assist api
int deviceMRQ::call( const tpvRegion &region )
{
    lpc( region.axes() )->postMsg(
                            (eRoboMsg)mrq_msg_call,
                            region
                        );
    logDbg();
    return 0;
}

int deviceMRQ::rotate( pvt_region, float t, float ang )
{
    run( pvt_region_p );

    return pvtWrite( pvt_region_p, t, ang );
}

int deviceMRQ::fsmState( pvt_region )
{
    Q_ASSERT( mMrqFsms.contains( region ) );
    return mMrqFsms[ region ]->state();
}

}
