#include "vrobot.h"

#include "../../app/systimer.h"

//! action
int VRobot::transform( int axes )
{ return 0; }

int VRobot::download( tpvGroup *pGroup,
                      const tpvRegion &region )
{
    Q_ASSERT( NULL != pGroup );

    return 0;
}
int VRobot::download( motionGroup *pGroup,
                      const tpvRegion &region )
{
    Q_ASSERT( NULL != pGroup );

    return 0;
}
int VRobot::download( QList<tpvGroup*> &groups,
                      QList<int> &joints,
                      const tpvRegion &region )
{
    return 0;
}
int VRobot::download( VRobot *pSetup )
{
    Q_ASSERT( NULL != pSetup );

    return 0;
}

int VRobot::run( const tpvRegion &region )
{
    return 0;
}
int VRobot::stop( const tpvRegion &region  )
{
    return 0;
}

int VRobot::setLoop( int n, const tpvRegion &region )
{ return 0;  }
int VRobot::loopNow()
{ return 0; }

void VRobot::startTimer( void *pContext, int id, int tmous )
{
    SysTimerThread::sysStartTimer( this, pContext, id, tmous );
}
void VRobot::killTimer( void *pContext, int id )
{
    SysTimerThread::sysStopTimer( this, pContext, id );
}

void VRobot::onTimer( void *pContext, int id )
{

}

void VRobot::attachCondition( const tpvRegion &region,
                              MegaDevice::RoboCondition *pCond )
{

}

bool VRobot::waitCondition( const tpvRegion &region,
                            MegaDevice::RoboCondition *pCond,
                            int tmoms )
{
   return false;
}

//void VRobot::attachCondition(
//                              MegaDevice::RoboCondition *pCond )
//{

//}

//bool VRobot::waitCondition(
//                            MegaDevice::RoboCondition *pCond,
//                            int tmoms )
//{
//   return false;
//}
