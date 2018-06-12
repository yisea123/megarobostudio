#include "vrobot.h"

QString & VRobot::getClass()
{ return mClass; }
QString & VRobot::getDetail()
{ return mDetail; }
VRobot::robotEnum VRobot::getId()
{ return mId; }
VRobot::robotEnum VRobot::robotId()
{ return mId; }

int VRobot::setAxes(int n)
{
    //! gc
    gcWorker();

    //! create the workers for each axes
    m_pAxesWorkers = new RoboWorker[ n ];
    Q_ASSERT( NULL != m_pAxesWorkers );
    for( int i = 0; i < n; i++ )
    { m_pAxesWorkers[i].attachRobot( this, i ); }

    //! init the angle
    mJointAngleMask.clear();
    mJointCcwMask.clear();
    for ( int i = 0; i <n; i++ )
    {
        mJointAngleMask.append( false );
        mJointCcwMask.append( true );
    }

    mAxes = n;

    return 0;
}
int VRobot::axes()
{ return mAxes; }
QImage & VRobot::getImage()
{ return mImage; }

void VRobot::setPlanAttr( const PlanAttr &attr )
{
    mPlanAttr = attr;
}
PlanAttr VRobot::planAttr()
{
    return mPlanAttr;
}

void VRobot::setRegions( int regions )
{ mRegions = regions; }
int VRobot::regions()
{ return mRegions; }

void VRobot::setDcAxes( int n )
{ mDCAxes = n; }
int VRobot::dcAxes()
{ return mDCAxes; }

void VRobot::setOutputs( int n )
{ mOutputs = n; }
int VRobot::outputs()
{ return mOutputs; }

void VRobot::setInputs( int n )
{ mInputs = n; }
int VRobot::inputs()
{ return mInputs; }

void VRobot::setDOs( int n )
{ mDOs = n; }
int VRobot::dos()
{ return mDOs; }

void VRobot::setDIs( int n )
{ mDIs = n; }
int VRobot::dis()
{ return mDIs; }

void VRobot::setIsos( int n )
{ mISOs = n; }
int VRobot::isos()
{ return mISOs; }

void VRobot::setIsis( int n )
{ mISIs = n; }
int VRobot::isis()
{ return mISIs; }

void VRobot::setAins( int n )
{ mAINs = n; }
int VRobot::ains()
{ return mAINs; }

void VRobot::setMosos( int n )
{ mMosos = n; }
int VRobot::mosos()
{ return mMosos; }

void VRobot::setEncoderAble( bool b )
{ mbEncoderAble = b; }
bool VRobot::encoderAble( )
{ return mbEncoderAble; }

void VRobot::setDriverId( int id )
{ mDriverId = id; }
int VRobot::driverId()
{ return mDriverId; }

void VRobot::setTemperatures( int n)
{ mTemperatures = n; }
int VRobot::temperatures()
{ return mTemperatures; }

void VRobot::setUarts( int n )
{ mUARTs = n; }
int VRobot::uarts()
{ return mUARTs; }

void VRobot::setUartSensors( int n )
{ mUART_Sensors = n; }
int VRobot::uartSensors()
{ return mUART_Sensors; }

QStringList VRobot::uartSensorList()
{ return mSensorNameList; }

void VRobot::setAbsEncAlarms( int n )
{ mAbsEncoderAlarms = n; }
int VRobot::absEncAlarms()
{ return mAbsEncoderAlarms; }

void VRobot::setDistanceAlarms( int n)
{ mDistanceAlarms = n; }
int VRobot::distanceAlarms()
{ return mDistanceAlarms; }

void VRobot::setAlarms( int n)
{ mAlarms = n; }
int VRobot::alarms()
{ return mAlarms; }

void VRobot::setTrigSrcs( int srcs )
{
    mTrigSrcs = srcs;

}
int VRobot::trigSrcs()
{ return mTrigSrcs; }

QString VRobot::trigSrcAlias( int ax, int iTrig )
{
    return QString("TRIG%1").arg( iTrig + 1 );
}

QList<bool> VRobot::jointZeroCcwList()
{ return mJointZeroCcw; }

void VRobot::setPoseCount( int pos )
{ mPoseCount = pos; }
int VRobot::poseCount()
{ return mPoseCount; }

bool VRobot::interpAble()
{ return mbInterpAble; }

void VRobot::microStepAttr( QStringList &stepList, int &base )
{
    stepList = mMicrostepsList;
    base = mMicrostepBase;
}

//void VRobot::setZeroSpeed( double spd )
//{
//    mZeroSpeed = spd;
//}
//double VRobot::zeroSpeed()
//{
//    return mZeroSpeed;
//}

void VRobot::setZeroPref( double spd, int tmo, int tick )
{
    mZeroSpeed = spd;
    mZeroTmo = tmo;
    mZeroTick = tick;
}
void VRobot::zeroPref( double &spd, int &tmo, int &tick )
{
    spd = mZeroSpeed;
    tmo = mZeroTmo;
    tick = mZeroTick;
}

RoboWorker *VRobot::lpc( int ax )
{
    Q_ASSERT( NULL != m_pAxesWorkers );
    Q_ASSERT( ax >= 0 && ax < axes() );

    return m_pAxesWorkers + ax;
}

RoboWorker *VRobot::lpc( )
{
    return m_pRoboWoker;
}
