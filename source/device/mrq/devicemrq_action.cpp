
#include "deviceMRQ.h"

namespace MegaDevice
{

int deviceMRQ::run( const tpvRegion &region )
{
    //! start lpc
    lpc( region.axes() )->postMsg(
                            (eRoboMsg)mrq_msg_run,
                            region
                        );
    return 0;
}

int deviceMRQ::stop( const tpvRegion &region )
{
    //! force stop
    setMOTION_SWITCH(  region.axes(),
                       MRQ_MOTION_SWITCH_STOP,
                       (MRQ_MOTION_SWITCH_1)region.page() );

    requestMotionState( region );

    //! request stop as the defer msg
    lpc( region.axes() )->postMsg(
                            (eRoboMsg)mrq_msg_stop,
                            region
                        );

    return 0;
}

int deviceMRQ::setLoop( int n, const tpvRegion &region )
{
    return setMOTIONPLAN_CYCLENUM( region.axes(),
                                   (MRQ_MOTION_SWITCH_1)region.page(),
                                   n  );
}

//MRQ_MOTION_STATE_POWERON,
//MRQ_MOTION_STATE_IDLE,
//MRQ_MOTION_STATE_CALCING,
//MRQ_MOTION_STATE_CALCEND,
//MRQ_MOTION_STATE_STANDBY,
//MRQ_MOTION_STATE_RUNNING,
//MRQ_MOTION_STATE_ERROR,
void deviceMRQ::setStatus( int stat, const tpvRegion &region, frameData &data  )
{
    int ch = region.axes();
    MRQ::setStatus( stat, region, data );

    if ( stat == MRQ_MOTION_STATE_2_POWERON )
    {
        lpc( ch )->postMsg( (eRoboMsg)mrq_msg_idle, region, data.timeStamp() ) ;
    }
    else if ( stat == MRQ_MOTION_STATE_2_IDLE )
    {
        lpc( ch )->postMsg( (eRoboMsg)mrq_msg_idle, region, data.timeStamp() ) ;
    }
    else if ( stat == MRQ_MOTION_STATE_2_CALCING )
    {
        lpc( ch )->postMsg( (eRoboMsg)mrq_msg_calcing, region, data.timeStamp() ) ;
    }
    else if ( stat == MRQ_MOTION_STATE_2_CALCEND )
    {
        lpc( ch )->postMsg( (eRoboMsg)mrq_msg_calcend, region, data.timeStamp() ) ;
    }
    else if ( stat == MRQ_MOTION_STATE_2_STANDBY )
    {
        lpc( ch )->postMsg( (eRoboMsg)mrq_msg_standby, region, data.timeStamp() ) ;
    }
    else if ( stat == MRQ_MOTION_STATE_2_RUNNING )
    {
        lpc( ch )->postMsg( (eRoboMsg)mrq_msg_running, region, data.timeStamp() ) ;
    }
    else if ( stat == MRQ_MOTION_STATE_2_ERROR )
    { sysError( "error", __FUNCTION__, QString::number( region.axes() ), QString::number( region.page() ) );
        lpc( ch )->postMsg( (eRoboMsg)mrq_msg_idle, region, data.timeStamp() ) ;
    }
    else
    {
//        logDbg()<<stat;
//        Q_ASSERT(false);
        sysPrompt( QObject::tr("Invalid status ") + QString::number( ch ) + "/" + QString::number( stat ) );
    }
}

bool deviceMRQ::checkLink( int p1, int p2 )
{
    do
    {
        if ( p1 < 0 || p1 >= axes() )
        { break; }
        if ( p2 < 0 || p2 >= regions() )
        { break; }

        return true;
    }while( 0 );

    sysError( QObject::tr("Invalid region/page"), QString::number( p1 ), QString::number( p2 ) );

    return false;
}

}
