#include "receivecache.h"

frameEvent::frameEvent()
{
    mEventId = event_none;
    mbEn = false;

    mPatternLen = 0;
    for ( int i = 0; i < sizeof_array( mPatterns); i++ )
    {
        mPatterns[i] = -1;
    }
}

void frameEvent::setId( eventId id )
{
    mEventId = id;
}
eventId frameEvent::getId()
{
    return mEventId;
}

void frameEvent::setEnable( bool b )
{ mbEn = b; }
bool frameEvent::getEnable()
{ return mbEn; }

void frameEvent::setMainSubCode( int mainCode,
                                 int subCode )
{
    clear();
    append( (char)(mainCode & 0xff) );
    append( (char)(subCode & 0xff) );
}

void frameEvent::setMainSubCode( int mainCode,
                     int subCode,
                     int patterns[],
                     int pattLen )
{
    setMainSubCode( mainCode, subCode );

    Q_ASSERT( pattLen <= sizeof_array(mPatterns) );
    for ( int i = 0; i < pattLen; i++ )
    {
        mPatterns[i] = patterns[i];
    }
    mPatternLen = pattLen;
}

bool frameEvent::match( QByteArray &ary )
{
    if ( ary.length() < 2 + mPatternLen )
    { return false; }

    do
    {
        if ( ary.at(0) != at(0) )
        { break; }

        if ( ary.at(1) != at(1) )
        { break; }


        for ( int i = 0; i < mPatternLen; i++ )
        {
            if ( mPatterns[i] != -1 )
            {
                 if ( (byte)mPatterns[i] != ary.at(i+2) )
                 { return false; }
            }
            else
            {}
        }

        return true;

    }while( 0 );

    return false;
}

//! -- frame data
frameData::frameData()
{
    mFrameId = 0;
    mTimeStamp = 0;
}

void frameData::setFrameId( int frameId )
{ mFrameId = frameId; }
int frameData::frameId()
{ return mFrameId; }

void frameData::setTimeStamp( quint64 t )
{ mTimeStamp = t; }
quint64 frameData::timeStamp()
{ return mTimeStamp; }

//! -- frame house
frameHouse::frameHouse()
{
    mSendId = 0;
    mRecvId = 0;
}

void frameHouse::setId( int sendId, int recvId )
{
    mSendId = sendId;
    mRecvId = recvId;
}
void frameHouse::setSendId( int sendId )
{ mSendId = sendId; }
void frameHouse::setRecvId( int recvId )
{ mRecvId = recvId; }
int frameHouse::sendId()
{
    return mSendId;
}
int frameHouse::recvId()
{
    return mRecvId;
}

void frameHouse::lock()
{
    mMutex.lock();
}
void frameHouse::unlock()
{
    mMutex.unlock();
}

void frameHouse::clear()
{
    frameHouse::lock();

    QQueue<frameData>::clear();

    frameHouse::unlock();
}

//! -- frame warehouse
frameWarehouse::frameWarehouse()
{}

frameWarehouse::~frameWarehouse()
{
    delete_all( mHouses );
}

void frameWarehouse::inFrame( frameData & data )
{
    //! find the house
    frameHouse *pHouse = findHouseBySendId( data.frameId() );
    if ( NULL == pHouse )
    {
        pHouse = new frameHouse();
        Q_ASSERT( NULL != pHouse );
        pHouse->setSendId( data.frameId());

        pHouse->lock();
        pHouse->append( data );
        pHouse->unlock();

        mHouses.append( pHouse );
    }
    else
    {
        pHouse->lock();
        pHouse->append( data );
        pHouse->unlock();
    }

//    logDbg()<<pHouse->sendId()<<data.getFrameId()<<pHouse->size()<<QThread::currentThreadId();
}

frameHouse *frameWarehouse::findHouseByRecvId( int recvId )
{
    foreach( frameHouse *pHouse, mHouses )
    {
        Q_ASSERT( NULL != pHouse );

        if ( pHouse->recvId() == recvId )
        { return pHouse; }
    }

    return NULL;
}
frameHouse *frameWarehouse::findHouseBySendId( int sendId )
{
    foreach( frameHouse *pHouse, mHouses )
    {
        Q_ASSERT( NULL != pHouse );

        if ( pHouse->sendId() == sendId )
        { return pHouse; }
    }

    return NULL;
}

QList< frameHouse *> *frameWarehouse::houses()
{ return &mHouses; }

//! -- receive cache
QMutex receiveCache::_threadMutex;
quint64 receiveCache::_timeStamp = 0;
void receiveCache::lock()
{ _threadMutex.lock(); }
void receiveCache::unlock()
{ _threadMutex.unlock(); }

quint64 receiveCache::timeStamp()
{ return receiveCache::_timeStamp; }

receiveCache::receiveCache( QObject *parent ) : QThread( parent )
{
    m_pBus = NULL;
}
receiveCache::~receiveCache()
{
    delete_all( mEvents );
}
void receiveCache::attachBus( MegaDevice::IBus *pBus
                               )
{
    Q_ASSERT( NULL != pBus );

    receiveCache::lock();
    m_pBus = pBus;
    receiveCache::unlock();
}
void receiveCache::detachBus()
{
    receiveCache::lock();
    m_pBus = NULL;
    receiveCache::unlock();
}

int receiveCache::setFrameEventEnable( frameEvent &evt, bool b )
{
    frameEvent *pEvt;

    //! find
    pEvt = findFrameEvent( evt );
    if ( NULL != pEvt )
    {
        pEvt->setEnable(b);
        return 0;
    }
    //! add a new one
    else
    {
        pEvt = new frameEvent();
        Q_ASSERT( NULL != pEvt );

        *pEvt = evt;
        pEvt->setEnable( b );
        mEvents.append( pEvt );

        return 0;
    }
}
bool receiveCache::getFrameEventEnable( frameEvent &evt )
{
    frameEvent *pEvt;

    pEvt = findFrameEvent( evt );
    if ( NULL != pEvt )
    { return pEvt->getEnable(); }
    else
    { return false; }
}

frameEvent* receiveCache::findFrameEvent( frameEvent &evt )
{
    return findFrameEvent( evt.getId() );
}

frameEvent* receiveCache::findFrameEvent( eventId id )
{
    foreach( frameEvent *pEvt, mEvents )
    {
        if ( pEvt->getId() == id )
        { return pEvt; }
    }

    return NULL;
}

void receiveCache::append( frameData &ary )
{
    //! signal on some event
    if ( detectEvent( ary ) )
    { logDbg()<<ary.frameId()<<ary.size(); }
    else
    {
        lockWarehouse();
        mFrameWarehouse.inFrame( ary );
        unlockWarehouse();
    }
}

//int receiveCache::readAFrame( frameData &ary, int tmous )
//{
//    int ret;

//    //! try to read
//    do
//    {
//        mCacheMutex.lock();
//        if ( mRecvCache.size() > 0 )
//        {
//            ret = 0;
//            ary = mRecvCache.dequeue();
//            mCacheMutex.unlock();

//            return 0;
//        }
//        else
//        { ret = -1; }
//        mCacheMutex.unlock();

//        tmous -= m_pBus->getTick();
//        m_pBus->wait_us( m_pBus->getTick() );

//    }while( tmous>0 );

//    return ret;
//}

int receiveCache::readAFrame( MegaDevice::DeviceId &nodeId,
                              int *pFrameId,
                              byte *pBuf,
                              int *pLen,
                              int tmous )
{
    Q_ASSERT( NULL != pFrameId && NULL != pBuf && NULL != pLen );

    int ret = -1;
    frameHouse *pHouse;
    Q_ASSERT( NULL != m_pBus );
    logDbg()<<tmous<<m_pBus->rdTick()<<nodeId.sendId();
    do
    {
        do
        {
            //! 1. find house
            //! \note send id is from the device
            pHouse = mFrameWarehouse.findHouseBySendId( nodeId.sendId() );
            if ( NULL == pHouse )
            { break; }

            //! 2. find
            pHouse->lock();
            if ( pHouse->size() > 0 )
            {
                frameData ary;
                ary = pHouse->dequeue();
                pHouse->unlock();
logDbg();
                *pFrameId = ary.frameId();
                memcpy( pBuf, ary.data(), ary.length() );

                *pLen = ary.length();
                return 0;
            }
            else
            {
                pHouse->unlock();
            }

        }while(0);

        Q_ASSERT( NULL != m_pBus );
        tmous -= m_pBus->rdTick();
        m_pBus->wait_us( m_pBus->rdTick() );


    }while( tmous > 0 );
logDbg()<<pHouse->size()<<pHouse->sendId()<<nodeId.sendId()<<QThread::currentThreadId();
    return ret;
}

//! read all
int receiveCache::readFrame( MegaDevice::DeviceId &nodeId, frameHouse &frames )
{
    //! no node id
    foreach( frameHouse *pHouse, *mFrameWarehouse.houses() )
    {
        Q_ASSERT( NULL != pHouse );

        frames.append( *pHouse );

        pHouse->clear();
    }

    return frames.size();
}

//! flush some house
void receiveCache::flush( MegaDevice::DeviceId &nodeId )
{
    frameHouse *pHouse = mFrameWarehouse.findHouseBySendId( nodeId.sendId() );
    if ( NULL == pHouse )
    { return; }
logDbg()<<nodeId.sendId()<<nodeId.recvId()<<pHouse->size();
    pHouse->clear();
}

//! clear all house
void receiveCache::clear()
{
    lockWarehouse();

    foreach( frameHouse *pHouse, *mFrameWarehouse.houses() )
    {
        Q_ASSERT( pHouse != NULL );
        pHouse->clear();
    }

//    qDeleteAll( *mFrameWarehouse.houses() );

    unlockWarehouse();
}

//! all houses count
int receiveCache::frameCount()
{
//    return mRecvCache.size();

    int sum = 0;
    foreach( frameHouse *pHouse, *mFrameWarehouse.houses() )
    {
        Q_ASSERT( NULL != pHouse );

        sum += pHouse->size();
        logDbg()<<sum;
    }

    return sum;
}

void receiveCache::lockWarehouse()
{ mCacheMutex.lock(); }
void receiveCache::unlockWarehouse()
{ mCacheMutex.unlock(); }

void receiveCache::run()
{
    Q_ASSERT( NULL!=m_pBus );

    //! highest
    QThread::setPriority( QThread::TimeCriticalPriority );

    int ret;
    QList< frameData > frameCache;
    Q_FOREVER
    {
        do
        {
            frameCache.clear();

            receiveCache::lock();
            //! have detatched
            if ( m_pBus == NULL )
            {
                receiveCache::unlock();
                QThread::msleep( 10 );
                break;
            }

            //! try to read a frame
            Q_ASSERT( NULL != m_pBus );
            ret = m_pBus->doReceive( frameCache );
            receiveCache::unlock();

            //! success
            if ( ret == 0 )
            {
                //! acc the stamp
                receiveCache::_timeStamp++;

                for ( int i = 0; i < frameCache.size(); i++ )
                {
//                    append( frameCache.at(i) );
                    frameCache[i].setTimeStamp( receiveCache::_timeStamp );
                    logDbg()<<frameCache[i].timeStamp();
                    append( frameCache[i] );
//                    logDbg()<< frameCache.at(i).length() << QString::number( frameCache.at(i).getFrameId(), 16 );
                }
            }
//            else
//            {
//                //! read interval
//                //! the shortest reply time: 160us
//                m_pBus->wait_us( m_pBus->rdInterval() );
//            }

        }while( 0 );
    }
}

bool receiveCache::detectEvent( frameData &ary )
{
    bool bEvent = false;
    foreach( frameEvent *pEvt, mEvents )
    {
        Q_ASSERT( NULL != pEvt );
        //! find event
//        if ( ary.startsWith( *pEvt) && pEvt->getEnable() )
        if ( pEvt->getEnable() && pEvt->match(ary) )
        {
            emit sig_event( pEvt->getId(), ary );
            logDbg()<<QString::number( ary.frameId(), 16)<<ary.toHex(' ')<<ary.timeStamp();
            bEvent = true;
        }
    }
logDbg()<<mEvents.size();
    return bEvent;
}
