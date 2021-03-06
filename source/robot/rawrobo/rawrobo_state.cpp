#include "rawrobo.h"
#include "../../device/mrq/devicemrq_state.h"
#include "../../device/board/_MRQ_enum.h"

#define status_timer_id     2
//#define status_timer_tmo    time_s( 1 )    //! us
//#define status_timer_prepare    time_s( 2 )

//#define status_timer_tmo    time_ms( 500 )    //! us
#define status_timer_tmo    time_s( 4 )    //! us
#define status_timer_prepare    time_ms( 500 )

//! state unit
RawRoboUnit::RawRoboUnit( MegaDevice::RoboFsm *pFsm,
                          int members )
{
    mMemberCount = members;

    initState();
}
RawRoboUnit::~RawRoboUnit()
{}
void RawRoboUnit::toState( int stat, RoboMsg &detail )
{
    selfFsm()->toState( stat, detail );

    //! to robot
    //! \todo page
    sysQueue()->postMsg( e_robot_status,
                         selfFsm()->Robot()->name(),
                         stat );

//    sysLog( __FUNCTION__,
//            QString::number( __LINE__ ),
//            QString::number( stat )
//            );
//    logDbg()<<selfFsm()->Robot()->name();
}

void RawRoboUnit::onEnter( RoboMsg &detail )
{
    initState();
}

//! rst state
void RawRoboUnit::onExit( RoboMsg &detail )
{
    initState();
}

void RawRoboUnit::proc( int msg, RoboMsg &detail )
{
    //! member state
    if ( msg == e_robot_member_state )  //! subax, region, stat
    {
        int subAx;
        tpvRegion region;
        int state;

        if ( detail.size() < 3 )
        { logDbg(); return; }

        subAx = detail.at(0).toInt();
        region = detail.at(1).value<tpvRegion>();
        state= detail.at(2).toInt();

        setMemberState( subAx, region, state, detail );
    }

    //! ops
    else if ( msg == MegaDevice::mrq_msg_run )  //! region
    {
        selfFsm()->reqRun( true );

        toState( MegaDevice::mrq_state_run_reqed, detail );
//        toState( MegaDevice::mrq_state_calcend, detail );
    }

    else if ( msg == MegaDevice::mrq_msg_stop )
    {
        selfFsm()->reqRun( false );

        //! \todo stop downloading
        selfFsm()->Robot()->switchStop();

        toState( MegaDevice::mrq_state_idle, detail );

        logDbg();
    }

    else if ( msg == MegaDevice::mrq_msg_call )
    {
        selfFsm()->reqRun( true );          //! request run

                                            //! start timer
        toState( MegaDevice::mrq_state_calcend, detail );
    }

    //! \todo not used now
    else if ( msg == MegaDevice::mrq_msg_force_stop )
    {
        //! \todo stop downloading
        selfFsm()->Robot()->switchEmergStop();

        toState( MegaDevice::mrq_state_prestop, detail );
    }

    else if ( msg == MegaDevice::mrq_msg_rst )
    { toState( MegaDevice::mrq_state_idle, detail ); }

    else if ( msg == MegaDevice::mrq_msg_program )
    { toState( MegaDevice::mrq_state_program, detail ); }

    //! device status
    else if ( msg == MegaDevice::mrq_msg_idle )
    { toState( MegaDevice::mrq_state_idle, detail ); }

    else if ( msg == MegaDevice::mrq_msg_calcing )
    { toState( MegaDevice::mrq_state_calcing, detail ); }

    else if ( msg == MegaDevice::mrq_msg_calcend )
    { Q_ASSERT(false); toState( MegaDevice::mrq_state_calcend, detail ); }

    else if ( msg == MegaDevice::mrq_msg_standby )
    { toState( MegaDevice::mrq_state_standby, detail ); }

    else if ( msg == MegaDevice::mrq_msg_running )
    { toState( MegaDevice::mrq_state_running, detail ); }

    else if ( msg == MegaDevice::mrq_msg_error )
    { toState( MegaDevice::mrq_state_idle, detail ); }

    else    //! keep
    { }
}

void RawRoboUnit::onTimer( int id )
{
    //! query status
    if ( status_timer_id == id )
    {
        selfFsm()->Robot()->queryState( selfFsm()->region() );
    }
}

RawRoboFsm *RawRoboUnit::selfFsm()
{
    return (RawRoboFsm*)Fsm();
}

void RawRoboUnit::setMemberState( int subAx,
                                  const tpvRegion &region,
                                  int stat,
                                  RoboMsg &detail )
{/*logDbg()<<stat<<subAx;*/
    mMemberStates[ subAx ] = stat;

//    sysLog( __FUNCTION__,
//            QString("%1/%2/%3/%4/%5")
//             .arg( mMemberStates[0] )
//             .arg( mMemberStates[1] )
//             .arg( mMemberStates[2] )
//             .arg( mMemberStates[3] )
//             .arg( mMemberStates[4] )
//            ,
//            QString::number(region.axes()),
//            QString::number(region.page()) );

    int preVal = mMemberStates[0];
    foreach (int val, mMemberStates)
    {
        //! value match
        if ( val == preVal )
        {}
        else
        { /*logDbg()<<mMemberStates;*/ return; }
    }
//logDbg()<<preVal;
//logDbg()<<mMemberStates;

    //! full match
    mState = preVal;

//    sysLog( __FUNCTION__,
//            QString::number( mState ),
//            QString::number(region.axes()),
//            QString::number(region.page()) );

    toState( mState, detail );
}
int RawRoboUnit::memberState( int subAx,
                              const tpvRegion &region )
{
    Q_ASSERT( mMemberStates.contains(subAx) );

    return mMemberStates[ subAx ];
}

int RawRoboUnit::state()
{ return mState; }

void RawRoboUnit::initState()
{
    mState = MegaDevice::mrq_state_unk;
    for ( int i = 0; i < mMemberCount; i++ )
    { mMemberStates.insert( i, mState ); }
}

UnkRawRoboUnit::UnkRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
    mName = "UnkRawRoboUnit";
}

void UnkRawRoboUnit::proc( int msg, RoboMsg &detail )
{
    RawRoboUnit::proc( msg, detail );
}

//! real states
//! idle
IdleRawRoboUnit::IdleRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
    mName = "IdleRawRoboUnit";
}

void IdleRawRoboUnit::proc( int msg, RoboMsg &detail )
{
    RawRoboUnit::proc( msg, detail );
}

void IdleRawRoboUnit::onEnter( RoboMsg &detail )
{
    RawRoboUnit::onEnter( detail );

    selfFsm( )->reqRun( false );

    killTimer( status_timer_id );

    selfFsm( )->Robot()->offLine( selfFsm()->region() );
}

//! run reqed
RunReqedRawRoboUnit::RunReqedRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
    mName = "RunReqedRawRoboUnit";
}

//! program
ProgramRawRoboUnit::ProgramRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
    mName = "ProgramRawRoboUnit";
}

//! calcing
CalcingRawRoboUnit::CalcingRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
    mName = "CalcingRawRoboUnit";
}

//! calcend
CalcendRawRoboUnit::CalcendRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
    mName = "CalcendRawRoboUnit";
}

void CalcendRawRoboUnit::proc( int msg, RoboMsg &detail )
{
    //! ops
    if ( msg == MegaDevice::mrq_msg_run
         || msg == MegaDevice::mrq_msg_call )
    {
//        sysLog( __FUNCTION__, QString::number(__LINE__) );logDbg();
        selfFsm()->reqRun( true );
        selfFsm()->Robot()->switchPrepare( selfFsm()->region() );
        startTimer( status_timer_id, status_timer_prepare );

    }
    else
    {
        RawRoboUnit::proc( msg, detail );
    }
}

void CalcendRawRoboUnit::onEnter( RoboMsg &detail )
{
    RawRoboUnit::onEnter( detail );

    if ( selfFsm()->runReqed() )
    {
//        sysLog( __FUNCTION__, QString::number(__LINE__) );logDbg();
        selfFsm()->Robot()->switchPrepare( selfFsm()->region() );
        startTimer( status_timer_id, status_timer_prepare );
    }
}

//! standby
StandbyRawRoboUnit::StandbyRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
     mName = "StandbyRawRoboUnit";
}
void StandbyRawRoboUnit::proc( int msg, RoboMsg &detail )
{//logDbg()<<msg;
    //! ops
    if ( msg == MegaDevice::mrq_msg_run
         || msg == MegaDevice::mrq_msg_call )
    {
        selfFsm()->Robot()->switchRun( selfFsm()->region() );
        toState( MegaDevice::mrq_state_prerun, detail );
    }
    else
    {
        RawRoboUnit::proc( msg, detail );
    }
}
void StandbyRawRoboUnit::onEnter( RoboMsg &detail )
{
    RawRoboUnit::onEnter( detail );

    if ( selfFsm()->runReqed() )
    {
        selfFsm()->Robot()->switchRun( selfFsm()->region() );
        toState( MegaDevice::mrq_state_prerun, detail );

        startTimer( status_timer_id, status_timer_tmo );
    }
    else
    {
        killTimer( status_timer_id );
    }
}
void StandbyRawRoboUnit::onExit( RoboMsg &detail )
{
    RawRoboUnit::onExit( detail );

    selfFsm()->reqRun( false );
}
//! pre run
PreRunRawRoboUnit::PreRunRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
    mName = "PreRunRawRoboUnit";
}

void PreRunRawRoboUnit::onEnter( RoboMsg &detail )
{
    RawRoboUnit::onEnter( detail );

    startTimer( status_timer_id, status_timer_tmo );
}

//! running
RunningRawRoboUnit::RunningRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{
    mName = "RunningRawRoboUnit";
}

void RunningRawRoboUnit::onEnter( RoboMsg &detail )
{
    RawRoboUnit::onEnter( detail );

    startTimer( status_timer_id, status_timer_tmo );
}

//! pre stop
PreStopRawRoboUnit::PreStopRawRoboUnit( MegaDevice::RoboFsm *pFsm,
                     int members ) : RawRoboUnit( pFsm, members )
{    
    mName = "PreStopRawRoboUnit";
}

void PreStopRawRoboUnit::onEnter( RoboMsg &detail )
{
    RawRoboUnit::onEnter( detail );

    startTimer( status_timer_id, status_timer_tmo );
}
