#include "megatron.h"

void robotMegatron::setZeroAttr( double zeroTime, double zeroAngle, double zeroSpeed )
{
    mZeroTime = zeroTime;
    mZeroAngle = zeroAngle;
    mZeroSpeed = zeroSpeed;
}
void robotMegatron::zeroAttr( double &zeroTime, double &zeroAngle, double &zeroSpeed )
{
    zeroTime = mZeroTime;
    zeroAngle = mZeroAngle;
    zeroSpeed = mZeroSpeed;
}

int robotMegatron::goZero( int jTabId, bool bCcw )
{
    MegaDevice::deviceMRQ *pMrq;
    int subAx;

    pMrq = jointDevice( jTabId, &subAx );
    if ( NULL == pMrq )
    {
        sysError( QObject::tr("Invalid device") );
        return -1;
    }
    Q_ASSERT( NULL != pMrq );

    //! to stop mode
    pMrq->setMOTIONPLAN_ENDSTATE( subAx, MRQ_MOTION_SWITCH_1_MAIN, MRQ_MOTIONPLAN_ENDSTATE_1_STOP );
    pMrq->lightCouplingZero( tpvRegion(subAx,0),
                             mZeroTime,
                             bCcw ? (-mZeroAngle) : ( mZeroAngle ),
                             mZeroSpeed );

    return 0;
}

int robotMegatron::goZero( const QList<int> &jointList,
                    const QList<bool> &ccwList )
{
    Q_ASSERT( jointList.size() == ccwList.size() );

    int ret=0;
    for ( int i = 0; i < jointList.size(); i++ )
    {
        ret = goZero( jointList.at(i), ccwList.at(i) );
        if ( ret != 0 )
        { return ret; }
    }

    return 0;
}