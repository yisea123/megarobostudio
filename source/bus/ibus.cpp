
#include "./ibus.h"
#include "./receivecache.h"

#define hw_hb( d )  (byte)(((d)>>24)&0xff)
#define hw_lb( d )  (byte)(((d)>>16)&0xff)
#define lw_hb( d )  (byte)(((d)>>8)&0xff)
#define lw_lb( d )  (byte)(((d)>>0)&0xff)

#define expand_dw( dw ) lw_lb( dw ), lw_hb( dw ), hw_lb( dw ), hw_hb( dw )
#define expand_w( w )   lw_lb( w ),  lw_hb( w )

#define READ_LOOP_TRY        ( failTry() + 1 )

#define LOCK_QUERY()        lockQuery();
#define UNLOCK_QUERY()      unlockQuery();

namespace MegaDevice {


IBus::IBus()
{
    mWtInterval = time_us(100);
    mFailTry = 2;

    mRdTmo = time_ms(200);
    mRdInterval = time_us( 100 );
    mRecvTmo = 1;                //!  \note can not be 1ms for -E WIN7 Fail

    mRdTick = time_us(500);

    mEnumerateTmo = time_ms( 50 );     //! ref to the device count, each = 200us

    m_pRecvCache = NULL;

    mBusType = e_bus_unk;
    mSpeed = 1000000;
    mPId = 0;
    mDevId = 0;
    mDefRM = 0;

    mLinkType = 0;
}

void IBus::setName( const QString & name )
{
    mName = name;
}
QString IBus::name()
{ return mName; }

void IBus::setBusType( IBus::eBusType type )
{
    mBusType = type;
}
IBus::eBusType IBus::busType()
{ return mBusType; }

void IBus::setSpeed( int speed )
{ mSpeed = speed; }
int IBus::speed()
{ return mSpeed; }

void IBus::setPId( int pid )
{ mPId = pid; }
int IBus::pId()
{ return mPId; }

void IBus::setDevId( int devId )
{ mDevId = devId; }
int IBus::devId()
{ return mDevId; }

void IBus::setDeviceId( DeviceId &id )
{ mDeviceId = id; }
DeviceId IBus::deviceId()
{ return mDeviceId; }

//int IBus::open(QString dev)
//{ return 0; }
int IBus::open( const modelSysPref &pref, int devType, int devId, int seqId, int canId, const QString &desc )
{ return 0; }
void IBus::close()
{ return; }

int IBus::size()
{ return 0;}
int IBus::flush( DeviceId &id )
{ return 0; }
int IBus::clear()
{ return 0; }
int IBus::doSend( const QString &buf )
{ return 0; }

int IBus::doWrite( byte *pBuf, int len )
{ return -1; }
int IBus::doRead( byte *pOutBuf, int len, int tmo, int &retLen )
{ return -1; }

int IBus::doWrite( DeviceId &nodeId, byte *pBuf, int len )
{ return -1; }
int IBus::doWrite( QList<frameData> &canFrames )
{ return -1; }
int IBus::doReceive( int *pFrameId, byte *pBuf, int *pLen )
{ return -1; }
int IBus::doReceive( QList< frameData > &receiveFrames )
{ return -1; }

//int IBus::doRead( DeviceId &nodeId, byte *pBuf, int cap, int *pLen )
//{ return -1; }

//int IBus::doFrameRead( DeviceId &nodeId, int *pFrameId, byte *pBuf, int *pLen )
//{ return -1; }
//int IBus::doFrameRead( DeviceId &nodeId, int *pFrameId, byte *pBuf, int eachFrameSize, int n )
//{ return -1; }
//int IBus::doSplitRead( DeviceId &nodeId, int packOffset, byte *pBuf, int cap, int *pLen )
//{ return -1; }

//! read from cache
int IBus::doRead( DeviceId &nodeId, byte *pBuf, int cap, int *pLen )
{
    Q_ASSERT( pBuf != NULL );
    Q_ASSERT( pLen != NULL );

    int ret, retLen, frameId;
    byte frameBuf[ FRAME_LEN ];
    ret = doFrameRead( nodeId, &frameId, frameBuf, &retLen );
    if ( ret != 0 )
    {
        *pLen = 0;logDbg();
        return ret;
    }

    if ( cap != retLen )
    {
        for( int i = 0; i < retLen; i++ )
        { logDbg()<<QString::number( frameBuf[i], 16 ); }
        *pLen = retLen;logDbg()<<retLen<<cap<<frameId<<nodeId.sendId()<<nodeId.recvId();
        return -2;
    }

    *pLen = cap;
    memcpy( pBuf, frameBuf, *pLen );

    return 0;
}

//! read from cache
//! nodeId -- device recv id
int IBus::doFrameRead( DeviceId &nodeId, int *pFrameId, byte *pBuf, int *pLen )
{
    //! read from cache by timeout
    Q_ASSERT( NULL != m_pRecvCache );

    return m_pRecvCache->readAFrame( nodeId, pFrameId, pBuf, pLen, mRdTmo );
}

//! read a few frame
int IBus::doFrameRead( DeviceId &nodeId, int *pFrameId, byte *pBuf, int eachFrameSize, int n )
{
    frameHouse frames;

    //! read frames
    m_pRecvCache->readFrame( nodeId, frames );

    int i = 0;
    for ( i = 0; i < frames.size() && i < n ; i++ )
    {
        pFrameId[i] = frames[i].frameId();
        memcpy( pBuf + i * eachFrameSize,
                frames[i].data(),
                qMin( frames[i].size(), eachFrameSize )
                );
    }

    return i;
}

int IBus::doSplitRead( DeviceId &nodeId, int packOffset, byte *pBuf, int cap, int *pLen )
{
    int ret, retLen;
    byte frameBuf[ FRAME_LEN ];

    int slice, total;

    int outLen = 0;
    int frameId;
    do
    {
        ret = doFrameRead( nodeId, &frameId, frameBuf, &retLen );
        if ( ret != 0 )
        { return ret; }

        if ( retLen <= packOffset )
        { return -1; }

        total = frameBuf[ packOffset ] & 0x0f;
        slice = ( frameBuf[ packOffset ] >> 4 ) & 0x0f;

        //! cat the data
        for ( int i = packOffset + 1; i < retLen && outLen < cap; i++, outLen++ )
        {
            pBuf[ outLen ] = frameBuf[ i ];
        }
    }while( slice < total );

    *pLen = outLen;

    return 0;
}

int IBus::enumerate( const modelSysPref &pref )
{
    return 0;
}

void IBus::lock()
{
    mbus_mutext.lock();
}
void IBus::unlock()
{
    mbus_mutext.unlock();
}

void IBus::lockQuery()
{ mbus_query_mutext.lock(); }
void IBus::unlockQuery()
{ mbus_query_mutext.unlock(); }

//void IBus::attachReceiveCache( receiveCache *pCache )
//{
//    Q_ASSERT( NULL != pCache );
//    m_pRecvCache = pCache;

//    m_pRecvCache->attachBus( this );
//}

int IBus::write( byte *pData, int len )
{ return doWrite( pData, len ); }
int IBus::read( byte *pOut, int len, int tmo, int &retLen )
{ return doRead( pOut, len, tmo, retLen );  }

//! write
//! buffer
int IBus::write( DeviceId &nodeId, byte *pData, int len )
{
    return doWrite( nodeId, pData, len );
}

//! write
//! no para
int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode)
{
    byte buf[] = { mainCode, subCode };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

//! 1 para
int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0 )
{
    byte buf[] = { mainCode, subCode, v0 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt16 v0)
{
    byte buf[] = { mainCode, subCode, expand_w(v0) };

    return doWrite( nodeId, buf, sizeof( buf ) );

}

int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt32 v0)
{
    byte buf[] = { mainCode, subCode,
                   expand_dw( v0 )
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            float v0 )
{
    uint32 byts;

    memcpy( &byts, &v0, 4 );

    byte buf[] = { mainCode, subCode,
                   expand_dw(byts),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

//! 2 para
int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte v1)
{
    byte buf[] = { mainCode, subCode,
                   v0, v1
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            UInt16 v1)
{
    byte buf[] = { mainCode, subCode,
                   v0,
                   expand_w(v1),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            UInt32 v1)
{
    byte buf[] = { mainCode, subCode,
                   v0,
                   expand_dw(v1),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            Int32 v1)
{
    byte buf[] = { mainCode, subCode,
                   v0,
                   expand_dw(v1),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            float v1)
{
    uint32 byts;

    memcpy( &byts, &v1, 4 );

    byte buf[] = { mainCode, subCode,
                   v0,
                   expand_dw(byts),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt16 v0,
            float v1)
{
    uint32 byts;
    memcpy( &byts, &v1, 4 );

    byte buf[] = { mainCode, subCode,
                   expand_w(v0),
                   expand_dw(byts),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus:: write( DeviceId &id, byte mainCode,
            byte subCode,
            UInt16 v0,
            UInt32 v1)
{
    uint32 byts;
    memcpy( &byts, &v1, 4 );

    byte buf[] = { mainCode, subCode,
                   expand_w(v0),
                   expand_dw(byts),
                 };

    return doWrite( id, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId,
           byte mainCode,
           byte subCode,
           byte ary[],
           int len )
{
    byte buf[8] = { mainCode, subCode };

    Q_ASSERT( len <= 6 );

    //! attach data
    memcpy( buf + 2, ary, len );

    return doWrite( nodeId, buf, len + 2 );
}

//! 3 para
int IBus::write( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte v1,
            byte v2 )
{
    byte buf[] = { mainCode, subCode,
                   v0, v1, v2
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           sbyte v2)
{
    byte byts;

    memcpy( &byts, &v2, 1 );

    byte buf[] = { mainCode, subCode,
                   v0, v1, byts
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           Int16 v2)
{
    UInt16 byts;

    memcpy( &byts, &v2, 2 );

    byte buf[] = { mainCode, subCode,
                   v0, v1,
                   expand_w(byts),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           UInt16 v2)
{
    byte buf[] = { mainCode, subCode,
                   v0, v1,
                   expand_w(v2),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           UInt16 v1,
           UInt16 v2)
{
    byte buf[] = { mainCode, subCode,
                   v0,
                   expand_w(v1),
                   expand_w(v2),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           UInt32 v2)
{

    byte buf[] = { mainCode, subCode,
                   v0, v1,
                   expand_dw(v2),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

int IBus::write( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           float v2)
{
    UInt32 byts;

    memcpy( &byts, &v2, 4 );

    byte buf[] = { mainCode, subCode,
                   v0, v1,
                   expand_dw(byts),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

//! 4 para
int IBus::write( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           byte v2,
           float f3 )
{
    UInt32 byts;

    memcpy( &byts, &f3, 4 );

    byte buf[] = { mainCode, subCode,
                   v0, v1, v2,
                   expand_dw(byts),
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

//! 5 para
int IBus::write( DeviceId &id, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           uint16 v2,
           uint16 v3
            )
{
    byte buf[8] = { mainCode, subCode, v0, v1 };
    memcpy( buf + 4, &v2, sizeof(uint16) );
    memcpy( buf + 6, &v3, sizeof(uint16) );

    return doWrite( id, buf, sizeof(buf) );
}

//! 6 para
int IBus::write( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           byte v2,
           byte v3,
           byte v4,
           byte v5
           )
{
    byte buf[] = { mainCode, subCode,
                   v0, v1, v2,
                   v3, v4, v5,
                 };

    return doWrite( nodeId, buf, sizeof( buf ) );
}

//! no para
int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            bool bQuery  )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &id, byte mainCode,
            byte subCode,
            byte * v0,
            quint32 * v1,
            bool bQuery  )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( id, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            byte * v2,
            bool bQuery)
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            byte * v2,
            byte * v3,
            bool bQuery)
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, v3, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            quint32 * v2,
            bool bQuery)
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            byte * v2,
            byte * v3,
            byte * v4,
            byte * v5,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, v3, v4, v5, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt16 * v0,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt32 * v0,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            f32 * v0,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

//! 1 para
int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            byte * v2,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            int8 * v2,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            int32 * v2,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &id, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            quint32 * v2,
            bool bQuery  )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( id, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            byte * v2,
            byte * v3,
            byte * v4,
            byte * v5,
            bool bQuery
            )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, v3, v4, v5, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            UInt16 * v1,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            UInt32 * v1,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            Int16 * v1,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            Int32 * v1,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            f32 * v1,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt16 v0,
            f32 * v1,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            uint16 * v1,
            uint16 * v2,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

//! 2 para
int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte v1,
            byte * v2,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte v1,
            byte * v2,
            byte * v3,
            byte * v4,
            byte * v5,
            bool bQuery
            )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, v3, v4, v5, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           sbyte * v2,
           bool bQuery)
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           Int16 * v2,
           bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           UInt16 * v2,
           bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           UInt32 * v2,
           bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();
    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           f32 * v2,
           bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();

    return ret;
}

int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte v1,
            UInt16 *v2,
            UInt16 *v3,

            bool bQuery  )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, v3, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();

    return ret;
}

//! 3 para
int IBus::read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            UInt16 v1,
            UInt16 v2,
            byte * v3,
            bool bQuery )
{
    int ret;
    LOCK_QUERY();
    for ( int i = 0; i < READ_LOOP_TRY; i++ )
    {
        ret = _read( nodeId, mainCode, subCode, v0, v1, v2, v3, bQuery );
        if ( 0 == ret )
        { break; }
    }
    UNLOCK_QUERY();

    return ret;
}

//! ******* sub apis ********

bool IBus::verifyCode( byte mainCode,
                 byte subCode,
                 byte *pBuf )
{
    Q_ASSERT( NULL != pBuf );

    if ( mainCode != pBuf[0] ||
         subCode != pBuf[1] )
    { return false; }

    return true;
}

bool IBus::verifyCode( byte mainCode,
                 byte subCode,
                 byte v0,
                 byte *pBuf )
{
    Q_ASSERT( NULL != pBuf );

    if ( mainCode != pBuf[0] ||
         subCode != pBuf[1] ||
         v0 != pBuf[2] )
    { return false; }

    return true;
}

bool IBus::verifyCode( byte mainCode,
                 byte subCode,
                 UInt16 v0,
                 byte *pBuf )
{
    UInt16 val;

    memcpy( &val, pBuf + 2, 2 );

    if ( mainCode != pBuf[0] ||
         subCode != pBuf[1] ||
         v0 != val )
    { return false; }

    return true;
}

bool IBus::verifyCode( byte mainCode,
                 byte subCode,
                 byte v0,
                 byte v1,
                 byte *pBuf )
{
    if ( mainCode != pBuf[0] ||
         subCode != pBuf[1] ||
         v0 != pBuf[2] ||
         v1 != pBuf[3] )
    { return false; }

    return true;
}

bool IBus::verifyCode( byte mainCode,
                 byte subCode,
                 byte v0,
                 UInt16 v1,
                 UInt16 v2,
                 byte *pBuf )
{
    UInt16 val1, val2;

    memcpy( &val1, pBuf + 3, 2 );
    memcpy( &val2, pBuf + 5, 2 );

    if ( mainCode != pBuf[0] ||
         subCode != pBuf[1] ||
         v0 != pBuf[2] ||
         v1 != val1 ||
         v2 != val2 )
    { return false; }

    return true;
}

#define VERIFY_CODE()   if ( verifyCode( mainCode, subCode, readBuf ) ){} \
                        else{ return -1; }

#define VERIFY_CODE_3()   if ( verifyCode( mainCode, subCode, v0, readBuf ) ){} \
                        else{ return -1; }

#define VERIFY_CODE_4()   if ( verifyCode( mainCode, subCode, v0, v1, readBuf ) ){} \
                        else{ return -1; }

#define VERIFY_CODE_5()   if ( verifyCode( mainCode, subCode, v0, v1, v2, readBuf ) ){} \
                        else{ return -1; }

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            bool bQuery  )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );
        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[3];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    *v0 = readBuf[2];
    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );
        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    *v0 = readBuf[2];
    *v1 = readBuf[3];
    return 0;
}

int IBus::_read( DeviceId &id, byte mainCode,
            byte subCode,
            byte * v0,
            quint32 * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( id );
        ret = write( id, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+4];
    ret = doRead( id, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    *v0 = readBuf[2];
    memcpy( v1, readBuf + 3, 4 );

    return 0;
}


int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            byte * v2,
            bool bQuery)
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );
        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[5];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    *v0 = readBuf[2];
    *v1 = readBuf[3];
    *v2 = readBuf[4];
    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            byte * v2,
            byte * v3,
            bool bQuery)
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );
        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    *v0 = readBuf[2];
    *v1 = readBuf[3];
    *v2 = readBuf[4];
    *v3 = readBuf[5];
    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            quint32 * v2,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );
        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[6];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    *v0 = readBuf[2];
    *v1 = readBuf[3];

    memcpy( v2, readBuf + 2, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte * v0,
            byte * v1,
            byte * v2,
            byte * v3,
            byte * v4,
            byte * v5,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );
        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+6];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    *v0 = readBuf[2];
    *v1 = readBuf[3];
    *v2 = readBuf[4];

    *v3 = readBuf[5];
    *v4 = readBuf[6];
    *v5 = readBuf[7];

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt16 * v0,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );
        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    memcpy( v0, readBuf + 2, 2 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt32 * v0,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );
        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    memcpy( v0, readBuf + 2, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            f32 * v0,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE();

    memcpy( v0, readBuf + 2, 4 );

    return 0;
}

//! 1 para
int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+1];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 1 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            byte * v2,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+3];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 1 );
    memcpy( v2, readBuf + 4, 1 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            int8 * v2,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+3];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 1 );
    memcpy( v2, readBuf + 4, 1 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            int32 * v2,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 1 );
    memcpy( v2, readBuf + 4, 4 );

    return 0;
}

int IBus::_read( DeviceId &id, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            quint32 * v2,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( id );

        ret = write( id, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+1+4];
    ret = doRead( id, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 1 );
    memcpy( v2, readBuf + 4, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte * v1,
            byte * v2,
            byte * v3,
            byte * v4,
            byte * v5,
            bool bQuery
            )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+6];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 1 );
    memcpy( v2, readBuf + 4, 1 );
    memcpy( v3, readBuf + 5, 1 );
    memcpy( v4, readBuf + 6, 1 );
    memcpy( v5, readBuf + 7, 1 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            UInt16 * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+2];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 2 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            UInt32 * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            Int16 * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+2];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 2 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            Int32 * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            f32 * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            UInt16 v0,
            f32 * v1,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 4, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            uint16 * v1,
            uint16 * v2,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+2+2];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_3();

    memcpy( v1, readBuf + 3, 2 );
    memcpy( v2, readBuf + 5, 2 );

    return 0;
}

//! 2 para
int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte v1,
            byte * v2,
            bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+1];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_4();

    memcpy( v2, readBuf + 4, 1 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
            byte subCode,
            byte v0,
            byte v1,
            byte * v2,
            byte * v3,
            byte * v4,
            byte * v5,
            bool bQuery
            )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_4();

    *v2 = readBuf[4];
    *v3 = readBuf[5];
    *v4 = readBuf[6];
    *v5 = readBuf[7];

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           sbyte * v2,
           bool bQuery)
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+1];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_4();

    *v2 = readBuf[4];

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           Int16 * v2,
           bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+2];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_4();

    memcpy( v2, readBuf + 4, 2 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           UInt16 * v2,
           bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+2];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_4();

    memcpy( v2, readBuf + 4, 2 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           UInt32 * v2,
           bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_4();

    memcpy( v2, readBuf + 4, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           f32 * v2,
           bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+2+4];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_4();

    memcpy( v2, readBuf + 4, 4 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           UInt16 v1,
           UInt16 v2,
           byte * v3,
           bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1, v2 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[2+1+2+2+1];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_5();

    memcpy( v3, readBuf + 7, 1 );

    return 0;
}

int IBus::_read( DeviceId &nodeId, byte mainCode,
           byte subCode,
           byte v0,
           byte v1,
           UInt16 *v2,
           UInt16 *v3,
           bool bQuery )
{
    int ret;

    if( bQuery )
    {
        flush( nodeId );

        ret = write( nodeId, mainCode, subCode, v0, v1 );
        if ( ret != 0 )
        { return ret; }
    }

    int retLen;
    byte readBuf[1+1+1+1+2+2];
    ret = doRead( nodeId, readBuf, sizeof(readBuf), &retLen );
    if ( ret != 0 )
    { return ret; }

    VERIFY_CODE_4();

    memcpy( v2, readBuf + 4, sizeof(UInt16) );
    memcpy( v3, readBuf + 6, sizeof(UInt16) );

    return 0;
}

}

