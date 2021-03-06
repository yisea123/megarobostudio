#ifndef DEVICEID_H
#define DEVICEID_H

#include "../../include/mcstd.h"

namespace MegaDevice {

class DeviceId
{
public:
    DeviceId( int rId=1, int sId = 0 );

public:
    int setSendId( int id );
    int getSendId();
    int sendId();

    int setRecvId( int id );
    int getRecvId();
    int recvId();

    int setBroadId( int id );
    int getBroadId();

    int setSignature( uint32 sig );
    uint32 getSignature( );

public:
    int mSendId;
    int mRecvId;
    int mBroadcastId;
    int mGroupId[2];

    uint32 mSignature;
};

inline bool operator<( const DeviceId &id1,
                const DeviceId &id2 )
{
    return id1.mSignature < id2.mSignature;
}

bool deviceIdLessThan( const DeviceId *id1,
                       const DeviceId *id2 );
}

#endif // DEVICEID_H
