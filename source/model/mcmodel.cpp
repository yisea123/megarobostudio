#include "mcmodel.h"

mcModel::mcModel()
{
    init();
}

mcModel::~mcModel()
{
    deinit();

}

//! load data from file
void mcModel::preload()
{
    mDeviceDbs.load( DEVICE_TALBE_NAME );
}

void mcModel::postload()
{
    if ( m_pInstMgr->isListening() )
    {
        m_pInstMgr->stop();
        sysLog( QObject::tr("port closed") );
    }

    if ( mSysPref.mMisaEn )
    {
        Q_ASSERT( NULL != m_pInstMgr );
        m_pInstMgr->start( mSysPref.mMisaSocket );
        sysLog( QObject::tr("port"), QString::number( mSysPref.mMisaSocket ), QObject::tr("opened") );
    }
}

mcConnection& mcModel::getConnection()
{
    return mConn;
}

void mcModel::init()
{
    m_pInstMgr = MegaDevice::InstMgr::proxy();

    Q_ASSERT( NULL != m_pInstMgr );


}
void mcModel::deinit()
{
    MegaDevice::InstMgr::free();
}
