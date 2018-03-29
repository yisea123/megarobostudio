#include "_MRQ_model.h"
namespace MegaDevice
{
static value_desc _value_desc_MRQ_LINK_INTFC[] = {
	{0,"NONE",},
	{1,"CAN",},
	{2,"RS232",},
};
static value_desc _value_desc_MRQ_LINK_DEVICEINFO[] = {
	{0,"MRQ",},
	{1,"MRV",},
};
static value_desc _value_desc_MRQ_LINK_DEVICEINFO_1[] = {
	{0,"C23D",},
	{1,"C23S",},
	{2,"M2304",},
	{3,"M2305",},
};
static value_desc _value_desc_MRQ_SYSTEM_WORKMODE[] = {
	{0,"NORMAL",},
	{1,"NONE",},
};
static value_desc _value_desc_MRQ_SYSTEM_POWERON[] = {
	{0,"DEFAULT",},
	{1,"LAST",},
};
static value_desc _value_desc_MRQ_RS232_BAUD[] = {
	{0,"4800",},
	{1,"7200",},
	{2,"9600",},
	{3,"14400",},
	{4,"19200",},
	{5,"38400",},
	{6,"57600",},
	{7,"115200",},
	{8,"128000",},
};
static value_desc _value_desc_MRQ_RS232_WORDLEN[] = {
	{0,"8",},
	{1,"9",},
};
static value_desc _value_desc_MRQ_RS232_FLOWCTL[] = {
	{0,"NONE",},
	{1,"RTS",},
	{2,"CTS",},
	{3,"RTS&CTS",},
};
static value_desc _value_desc_MRQ_RS232_PARITY[] = {
	{0,"NONE",},
	{1,"EVEN",},
	{2,"ODD",},
};
static value_desc _value_desc_MRQ_RS232_STOPBIT[] = {
	{0,"1",},
	{1,"0.5",},
	{2,"2",},
	{3,"1.5",},
};
static value_desc _value_desc_MRQ_CAN_TYPE[] = {
	{0,"A",},
	{1,"B",},
};
static value_desc _value_desc_MRQ_CAN_BAUD[] = {
	{0,"1000",},
	{1,"500",},
	{2,"250",},
	{3,"125",},
	{4,"100",},
	{5,"50",},
	{6,"20",},
	{7,"10",},
};
static value_desc _value_desc_MRQ_CAN_NETMANAGELED[] = {
	{0,"OFF",},
	{1,"ON",},
};
static value_desc _value_desc_MRQ_CAN_NETMANAGESTATE[] = {
	{0,"IDLE",},
	{1,"HASH",},
	{2,"SIGNATURE",},
};
static value_desc _value_desc_MRQ_CAN_NETMANAGEID[] = {
	{0,"NONE",},
	{1,"SENDID",},
	{2,"RECEIVEID",},
};
static value_desc _value_desc_MRQ_CLOCK_STARTTYPE[] = {
	{0,"RADIOID",},
	{1,"RECEIVEID",},
	{2,"GROUPID1",},
	{3,"GROUPID2",},
};
static value_desc _value_desc_MRQ_CLOCK_SYNCSTATE[] = {
	{0,"END",},
	{1,"START",},
};
static value_desc _value_desc_MRQ_MOTION_SWITCH[] = {
	{0,"RESET",},
	{1,"STOP",},
	{2,"RUN",},
	{3,"PREPARE",},
	{4,"EMERGSTOP",},
};
static value_desc _value_desc_MRQ_MOTION_SWITCH_1[] = {
	{0,"MAIN",},
	{1,"SMALL",},
	{2,"P1",},
	{3,"P2",},
	{4,"P3",},
	{5,"P4",},
	{6,"P5",},
	{7,"P6",},
	{8,"P7",},
	{9,"P8",},
};
static value_desc _value_desc_MRQ_MOTION_STATE_2[] = {
	{0,"POWERON",},
	{1,"IDLE",},
	{2,"CALCING",},
	{3,"CALCEND",},
	{4,"STANDBY",},
	{5,"RUNNING",},
	{6,"ERROR",},
};
static value_desc _value_desc_MRQ_MOTION_STATEREPORT[] = {
	{0,"ACTIVE",},
	{1,"QUERY",},
};
static value_desc _value_desc_MRQ_MOTION_STARTSOURCE[] = {
	{0,"SOFTWARE",},
	{1,"DIGITALIO",},
	{2,"CAN",},
	{3,"ALL",},
};
static value_desc _value_desc_MRQ_IDENTITY_GROUP[] = {
	{0,"GROUP1",},
	{1,"GROUP2",},
};
static value_desc _value_desc_MRQ_IDENTITY_LABEL[] = {
	{0,"SINANJU",},
	{1,"MEGATRON",},
	{2,"GOUF",},
};
static value_desc _value_desc_MRQ_IDENTITY_LABEL_1[] = {
	{0,"S1",},
	{1,"S2",},
	{2,"S3",},
	{3,"S4",},
};
static value_desc _value_desc_MRQ_MOTOR_STEPANGLE[] = {
	{0,"1.8",},
	{1,"0.9",},
	{2,"15",},
	{3,"7.5",},
};
static value_desc _value_desc_MRQ_MOTOR_TYPE[] = {
	{0,"ROTARY",},
	{1,"LINEAR",},
};
static value_desc _value_desc_MRQ_MOTOR_POSITIONUNIT[] = {
	{0,"ANGLE",},
	{1,"RADIAN",},
	{2,"MILLIMETER",},
};
static value_desc _value_desc_MRQ_MOTOR_SIZE[] = {
	{0,"8",},
	{1,"11",},
	{2,"14",},
	{3,"17",},
	{4,"23",},
	{5,"24",},
};
static value_desc _value_desc_MRQ_ENCODER_CHANNELNUM[] = {
	{0,"1",},
	{1,"3",},
};
static value_desc _value_desc_MRQ_ENCODER_TYPE[] = {
	{0,"INCREMENTAL",},
	{1,"ABSOLUTE",},
};
static value_desc _value_desc_MRQ_ENCODER_MULTIPLE[] = {
	{0,"SINGLE",},
	{1,"DOUBLE",},
	{2,"QUADRUPLE",},
};
static value_desc _value_desc_MRQ_ENCODER_STATE[] = {
	{0,"NONE",},
	{1,"OFF",},
	{2,"ON",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_PVTCONFIG_1[] = {
	{0,"END",},
	{1,"CLEAR",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_PRESETSTATE_1[] = {
	{0,"OFF",},
	{1,"ON",},
	{2,"CALC",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_EXECUTEMODE_1[] = {
	{0,"CYCLE",},
	{1,"FIFO",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_PLANMODE_1[] = {
	{0,"CUBICPOLY",},
	{1,"LINEAR",},
	{2,"UNIFORM",},
	{3,"TRAPEZOID",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_MOTIONMODE_1[] = {
	{0,"PVT",},
	{1,"LVT_CORRECT",},
	{2,"LVT_NOCORRECT",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_MODIFYDUTY_1[] = {
	{0,"1/4",},
	{1,"1/8",},
	{2,"1/16",},
	{3,"1/32",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_ENDSTATE_1[] = {
	{0,"STOP",},
	{1,"HOLD",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_STOPMODE_1[] = {
	{0,"IMMEDIATE",},
	{1,"DISTANCE",},
};
static value_desc _value_desc_MRQ_MOTIONPLAN_OOSLINERESPONSE_1[] = {
	{0,"NONE",},
	{1,"ALARM",},
	{2,"STOP",},
	{3,"ALARM&STOP",},
};
static value_desc _value_desc_MRQ_REPORT_STATE[] = {
	{0,"TORQUE",},
	{1,"CYCLE",},
	{2,"XANGLE",},
	{3,"YANGLE",},
	{4,"ZANGLE",},
	{5,"XVEL",},
	{6,"YVEL",},
	{7,"ZVEL",},
	{8,"XACC",},
	{9,"YACC",},
	{10,"ZACC",},
	{11,"SGALL",},
	{12,"SGSE",},
	{13,"DIST",},
	{14,"ABSENC",},
};
static value_desc _value_desc_MRQ_TRIGGER_MODE[] = {
	{0,"PATTERN",},
	{1,"LEVEL",},
};
static value_desc _value_desc_MRQ_TRIGGER_PATTERN[] = {
	{0,"X",},
	{1,"L",},
	{2,"R",},
	{3,"F",},
	{4,"H",},
};
static value_desc _value_desc_MRQ_TRIGGER_PATTSMODE[] = {
	{0,"CONTINUED",},
	{1,"INTERVAL",},
	{2,"SINGLE",},
};
static value_desc _value_desc_MRQ_TRIGGER_LEVELSTATE[] = {
	{0,"TRIGL",},
	{1,"TRIGR",},
};
static value_desc _value_desc_MRQ_TRIGGER_LEVELTYPE_1[] = {
	{0,"RESERVE",},
	{1,"LOW",},
	{2,"RISE",},
	{3,"FALL",},
	{4,"HIGH",},
};
static value_desc _value_desc_MRQ_DRIVER_TYPE[] = {
	{0,"D17",},
	{1,"D23",},
};
static value_desc _value_desc_MRQ_DRIVER_STATEREG[] = {
	{0,"R0",},
	{1,"R1",},
	{2,"R2",},
};
static value_desc _value_desc_MRQ_DRIVER_MICROSTEPS[] = {
	{0,"256",},
	{1,"128",},
	{2,"64",},
	{3,"32",},
	{4,"16",},
	{5,"8",},
	{6,"4",},
	{7,"2",},
	{8,"1",},
};
static value_desc _value_desc_MRQ_DRIVER_SGLIMIT[] = {
	{0,"UPLIMIT",},
	{1,"DOWNLIMIT",},
};
static value_desc _value_desc_MRQ_DRIVER_SGPARASET[] = {
	{0,"SG0",},
	{1,"SGT",},
	{2,"SEMAX",},
	{3,"SEMIN",},
};
static value_desc _value_desc_MRQ_DRIVER_MINICURRRATIO[] = {
	{0,"1/2",},
	{1,"1/4",},
};
static value_desc _value_desc_MRQ_DRIVER_REGCONFIG[] = {
	{0,"DRVCTRL",},
	{1,"CHOPCONF",},
	{2,"SMARTEN",},
	{3,"SGCSCONF",},
	{4,"DRVCONF",},
};
static value_desc _value_desc_MRQ_DIGITALOUTPUT_STATE[] = {
	{0,"DO1",},
	{1,"DO2",},
	{2,"DO3",},
	{3,"DO4",},
};
static value_desc _value_desc_MRQ_DIGITALOUTPUT_STATE_1[] = {
	{0,"DISABLE",},
	{1,"ENABLE",},
};
static value_desc _value_desc_MRQ_DIGITALOUTPUT_SIGNAL_1[] = {
	{0,"LEVEL",},
	{1,"NONE",},
};
static value_desc _value_desc_MRQ_DIGITALOUTPUT_POLARITY_1[] = {
	{0,"POSITIVE",},
	{1,"NEGATIVE",},
};
static value_desc _value_desc_MRQ_DIGITALOUTPUT_CONDITION_1[] = {
	{0,"AUTO",},
	{1,"NONE",},
};
static value_desc _value_desc_MRQ_ISOLATOROUTPUT_STATE[] = {
	{0,"YO1",},
	{1,"YO2",},
};
static value_desc _value_desc_MRQ_ISOLATOROUTPUT_RESPONSE_1[] = {
	{0,"TURNON",},
	{1,"CUTOFF",},
};
static value_desc _value_desc_MRQ_SENSORUART_BAUD[] = {
	{0,"UART1",},
	{1,"UART2",},
};
static value_desc _value_desc_MRQ_SENSORUART_BAUD_1[] = {
	{0,"4800",},
	{1,"7200",},
	{2,"9600",},
	{3,"14400",},
	{4,"19200",},
	{5,"38400",},
	{6,"57600",},
	{7,"115200",},
	{8,"128000",},
	{9,"2000000",},
	{10,"2500000",},
};
static value_desc _value_desc_MRQ_ABSENCALARM_ZEROPOSITION_1[] = {
	{0,"NONE",},
	{1,"EXIS",},
};
_MRQ_model::_MRQ_model()
{
	loadOtp();
}
void _MRQ_model::loadOtp()
{
	mLINK_INTFC = (MRQ_LINK_INTFC)0;
	mLINK_DEVICEINFO = (MRQ_LINK_DEVICEINFO)0;
	mLINK_DEVICEINFO1 = (MRQ_LINK_DEVICEINFO_1)0;
	mLINK_DEVICEINFO2 = (uint32)0;

	mSYSTEM_WORKMODE = (MRQ_SYSTEM_WORKMODE)0;
	mSYSTEM_POWERON = (MRQ_SYSTEM_POWERON)0;
	mSYSTEM_SN = (byte)0;
	mSYSTEM_SN1 = (char)0;

	mSYSTEM_SN2 = (char)0;
	mSYSTEM_SN3 = (char)0;
	mSYSTEM_SN4 = (char)0;
	mSYSTEM_SN5 = (char)0;

	mSYSTEM_TYPE = (MRQ_LINK_DEVICEINFO)0;
	mSYSTEM_TYPE1 = (MRQ_LINK_DEVICEINFO_1)0;
	mSYSTEM_SOFTVER = (char)0;
	mSYSTEM_SOFTVER1 = (char)0;

	mSYSTEM_SOFTVER2 = (char)0;
	mSYSTEM_FPGAVER = (char)0;
	mSYSTEM_FPGAVER1 = (char)0;
	mSYSTEM_FPGAVER2 = (char)0;

	mSYSTEM_HARDVER = (char)0;
	mSYSTEM_HARDVER1 = (char)0;
	mSYSTEM_BOOTVER = (char)0;
	mSYSTEM_BOOTVER1 = (char)0;

	mSYSTEM_EVENTCODE = (char)0;
	mSYSTEM_EVENTCODE1 = (char)0;
	mSYSTEM_EVENTCODE2 = (char)0;
	mSYSTEM_EVENTCODE3 = (char)0;

	mSYSTEM_EVENTCODE4 = (char)0;
	mSYSTEM_EVENTCODE5 = (char)0;
	mSYSTEM_DIOSTATE = (uint16)0;
	mRS232_BAUD = (MRQ_RS232_BAUD)0;

	mRS232_WORDLEN = (MRQ_RS232_WORDLEN)0;
	mRS232_FLOWCTL = (MRQ_RS232_FLOWCTL)0;
	mRS232_PARITY = (MRQ_RS232_PARITY)0;
	mRS232_STOPBIT = (MRQ_RS232_STOPBIT)0;

	mCAN_TYPE = (MRQ_CAN_TYPE)0;
	mCAN_BAUD = (MRQ_CAN_BAUD)0;
	mCAN_GROUP = (byte)0;
	mCAN_SENDID = (uint32)0;

	mCAN_RECEIVEID = (uint32)0;
	mCAN_GROUPID1 = (uint32)0;
	mCAN_GROUPID2 = (uint32)0;
	mCAN_BROADCASTID = (uint32)0;

	mCAN_NETMANAGESTATE = (MRQ_CAN_NETMANAGESTATE)0;
for ( int i0=0; i0 < 3; i0++ )
{
mCAN_NETMANAGEID[i0] = (uint32)0;
}
	mCAN_NETMANAGEHASH = (uint32)0;
	mCLOCK_FREQUENCY = (uint32)0;

	mCLOCK_SYNCREGISTER = (MRQ_CAN_NETMANAGELED)0;
	mCLOCK_STARTTYPE = (MRQ_CLOCK_STARTTYPE)0;
	mCLOCK_SYNCSTATE = (MRQ_CLOCK_SYNCSTATE)0;
	mCLOCK_COUNT = (uint32)0;

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTION_STATE[i0][i1] = (MRQ_MOTION_STATE_2)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_STATEREPORT[i0] = (MRQ_MOTION_STATEREPORT)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_STARTSOURCE[i0] = (MRQ_MOTION_STARTSOURCE)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_STARTTYPE[i0] = (MRQ_CLOCK_STARTTYPE)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_MAXSPEED[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_MINSPEED[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_MAXPOSITION[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_MINPOSITION[i0] = (f32)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_MAXTORQUE[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_MINTORQUE[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_MAXACCELERATION[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_MINACCELERATION[i0] = (f32)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_ORIGIN[i0] = (uint32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_OFFSETSTATE[i0] = (MRQ_CAN_NETMANAGELED)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_COUNTCIRCLE[i0] = (int16)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_ABCOUNT[i0] = (int32)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mMOTION_REVMOTION[i0] = (MRQ_CAN_NETMANAGELED)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 2; i1++ )
{
mIDENTITY_GROUP[i0][i1] = (byte)0;
}
}
	mIDENTITY_DISTDEVICE = (MRQ_CAN_NETMANAGELED)0;
for ( int i0=0; i0 < 10; i0++ )
{
mIDENTITY_LABEL[i0] = (MRQ_IDENTITY_LABEL)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mIDENTITY_LABEL1[i0] = (MRQ_IDENTITY_LABEL_1)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_STEPANGLE[i0] = (MRQ_MOTOR_STEPANGLE)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_TYPE[i0] = (MRQ_MOTOR_TYPE)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_POSITIONUNIT[i0] = (MRQ_MOTOR_POSITIONUNIT)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_GEARRATIONUM[i0] = (uint16)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_GEARRATIODEN[i0] = (uint16)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_LEAD[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_PEAKSPEED[i0] = (f32)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_PEAKACCELERATION[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_SIZE[i0] = (MRQ_MOTOR_SIZE)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_VOLTAGE[i0] = (byte)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_CURRENT[i0] = (byte)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mMOTOR_BACKLASH[i0] = (f32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mENCODER_LINENUM[i0] = (uint32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mENCODER_CHANNELNUM[i0] = (MRQ_ENCODER_CHANNELNUM)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mENCODER_TYPE[i0] = (MRQ_ENCODER_TYPE)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mENCODER_MULTIPLE[i0] = (MRQ_ENCODER_MULTIPLE)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mENCODER_STATE[i0] = (MRQ_ENCODER_STATE)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mENCODER_FEEDBACKRATIO[i0] = (byte)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_PVTCONFIG[i0][i1] = (MRQ_MOTIONPLAN_PVTCONFIG_1)0;
}
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_PRESETSTATE[i0][i1] = (MRQ_MOTIONPLAN_PRESETSTATE_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_EXECUTEMODE[i0][i1] = (MRQ_MOTIONPLAN_EXECUTEMODE_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_PLANMODE[i0][i1] = (MRQ_MOTIONPLAN_PLANMODE_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_MOTIONMODE[i0][i1] = (MRQ_MOTIONPLAN_MOTIONMODE_1)0;
}
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_MODIFYDUTY[i0][i1] = (MRQ_MOTIONPLAN_MODIFYDUTY_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_REMAINPOINT[i0][i1] = (uint16)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_CYCLENUM[i0][i1] = (uint32)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_WARNPOINT[i0][i1] = (byte)0;
}
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_ENDSTATE[i0][i1] = (MRQ_MOTIONPLAN_ENDSTATE_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_BUFFERSIZE[i0][i1] = (uint32)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_ACCSCALE[i0][i1] = (uint16)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_DECSCALE[i0][i1] = (uint16)0;
}
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_STOPMODE[i0][i1] = (MRQ_MOTIONPLAN_STOPMODE_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_STOPDISTANCE[i0][i1] = (f32)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_STOPTIME[i0][i1] = (f32)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_OOSLINESTATE[i0][i1] = (MRQ_CAN_NETMANAGELED)0;
}
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_OOSLINEOUTNUM[i0][i1] = (uint16)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_OOSLINERESPONSE[i0][i1] = (MRQ_MOTIONPLAN_OOSLINERESPONSE_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_OOSTOTALSTATE[i0][i1] = (MRQ_CAN_NETMANAGELED)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_OOSTOTALOUTNUM[i0][i1] = (uint32)0;
}
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
mMOTIONPLAN_OOSTOTALRESPONSE[i0][i1] = (MRQ_MOTIONPLAN_OOSLINERESPONSE_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
for ( int i2=0; i2 < 10; i2++ )
{
mPOSITION[i0][i1][i2] = (f32)0;
}
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
for ( int i2=0; i2 < 10; i2++ )
{
mVELOCITY[i0][i1][i2] = (f32)0;
}
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 10; i1++ )
{
for ( int i2=0; i2 < 10; i2++ )
{
mTIME[i0][i1][i2] = (f32)0;
}
}
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 15; i1++ )
{
mREPORT_STATE[i0][i1] = (MRQ_CAN_NETMANAGELED)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 15; i1++ )
{
mREPORT_PERIOD[i0][i1] = (uint32)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 15; i1++ )
{
mREPORT_DATA[i0][i1] = (uint32)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
mTRIGGER_MODE[i0] = (MRQ_TRIGGER_MODE)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mTRIGGER_PATTSTATE[i0] = (MRQ_CAN_NETMANAGELED)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mTRIGGER_PATTERN[i0] = (MRQ_TRIGGER_PATTERN)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mTRIGGER_PATTERN1[i0] = (MRQ_TRIGGER_PATTERN)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mTRIGGER_PATTRESP[i0] = (MRQ_MOTIONPLAN_OOSLINERESPONSE_1)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mTRIGGER_PATTSMODE[i0] = (MRQ_TRIGGER_PATTSMODE)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mTRIGGER_PATTSPERIOD[i0] = (uint32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 2; i1++ )
{
mTRIGGER_LEVELSTATE[i0][i1] = (MRQ_CAN_NETMANAGELED)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 2; i1++ )
{
mTRIGGER_LEVELTYPE[i0][i1] = (MRQ_TRIGGER_LEVELTYPE_1)0;
}
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 2; i1++ )
{
mTRIGGER_LEVELRESP[i0][i1] = (MRQ_MOTIONPLAN_OOSLINERESPONSE_1)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 2; i1++ )
{
mTRIGGER_LEVELSMODE[i0][i1] = (MRQ_TRIGGER_PATTSMODE)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 2; i1++ )
{
mTRIGGER_LEVELSPERIOD[i0][i1] = (f32)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_TYPE[i0] = (MRQ_DRIVER_TYPE)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 3; i1++ )
{
mDRIVER_STATEREG[i0][i1] = (uint32)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_CURRENT[i0] = (byte)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_MICROSTEPS[i0] = (MRQ_DRIVER_MICROSTEPS)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_STATE[i0] = (MRQ_CAN_NETMANAGELED)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_SGLIMIT[i0] = (MRQ_DRIVER_SGLIMIT)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_SGLIMIT1[i0] = (int8)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mDRIVER_SGPARASET[i0][i1] = (int16)0;
}
}
for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_IDLECURRENT[i0] = (byte)0;
}

for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_SWITCHTIME[i0] = (uint32)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
mDRIVER_MINICURRRATIO[i0] = (MRQ_DRIVER_MINICURRRATIO)0;
}
for ( int i0=0; i0 < 10; i0++ )
{
for ( int i1=0; i1 < 5; i1++ )
{
mDRIVER_REGCONFIG[i0][i1] = (uint32)0;
}
}
for ( int i0=0; i0 < 4; i0++ )
{
mDIGITALOUTPUT_STATE[i0] = (MRQ_DIGITALOUTPUT_STATE_1)0;
}

for ( int i0=0; i0 < 4; i0++ )
{
mDIGITALOUTPUT_SIGNAL[i0] = (MRQ_DIGITALOUTPUT_SIGNAL_1)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mDIGITALOUTPUT_POLARITY[i0] = (MRQ_DIGITALOUTPUT_POLARITY_1)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mDIGITALOUTPUT_SOURCE[i0] = (byte)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mDIGITALOUTPUT_CONDITION[i0] = (MRQ_DIGITALOUTPUT_CONDITION_1)0;
}

for ( int i0=0; i0 < 4; i0++ )
{
mDIGITALOUTPUT_PERIOD[i0] = (uint32)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mDIGITALOUTPUT_DUTY[i0] = (uint16)0;
}
for ( int i0=0; i0 < 2; i0++ )
{
mISOLATOROUTPUT_STATE[i0] = (MRQ_DIGITALOUTPUT_STATE_1)0;
}
for ( int i0=0; i0 < 2; i0++ )
{
mISOLATOROUTPUT_SOURCE[i0] = (byte)0;
}

for ( int i0=0; i0 < 2; i0++ )
{
mISOLATOROUTPUT_CONDITION[i0] = (MRQ_DIGITALOUTPUT_CONDITION_1)0;
}
for ( int i0=0; i0 < 2; i0++ )
{
mISOLATOROUTPUT_RESPONSE[i0] = (MRQ_ISOLATOROUTPUT_RESPONSE_1)0;
}
for ( int i0=0; i0 < 2; i0++ )
{
mSENSORUART_BAUD[i0] = (MRQ_SENSORUART_BAUD_1)0;
}
for ( int i0=0; i0 < 2; i0++ )
{
mSENSORUART_WORDLEN[i0] = (MRQ_RS232_WORDLEN)0;
}

for ( int i0=0; i0 < 2; i0++ )
{
mSENSORUART_FLOWCTL[i0] = (MRQ_RS232_FLOWCTL)0;
}
for ( int i0=0; i0 < 2; i0++ )
{
mSENSORUART_PARITY[i0] = (MRQ_RS232_PARITY)0;
}
for ( int i0=0; i0 < 2; i0++ )
{
mSENSORUART_STOPBIT[i0] = (MRQ_RS232_STOPBIT)0;
}
for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_STATE[i0][i1] = (MRQ_CAN_NETMANAGELED)0;
}
}

for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_SOF[i0][i1] = (byte)0;
}
}
for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_FRAMELEN[i0][i1] = (byte)0;
}
}
for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_RECEIVENUM[i0][i1] = (byte)0;
}
}
for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_SWITCHTIME[i0][i1] = (uint32)0;
}
}

for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_DATA[i0][i1] = (byte)0;
}
}
for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_DATA1[i0][i1] = (char)0;
}
}
for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_DATA2[i0][i1] = (char)0;
}
}
for ( int i0=0; i0 < 2; i0++ )
{
for ( int i1=0; i1 < 4; i1++ )
{
mSENSORUART_DATA3[i0][i1] = (char)0;
}
}

	mISOLATORIN_STATE = (MRQ_CAN_NETMANAGELED)0;
	mISOLATORIN_TYPE = (MRQ_TRIGGER_LEVELTYPE_1)0;
	mISOLATORIN_RESPONSE = (MRQ_MOTIONPLAN_OOSLINERESPONSE_1)0;
	mISOLATORIN_RESPCHAN = (byte)0;

	mISOLATORIN_SMODE = (MRQ_TRIGGER_PATTSMODE)0;
	mISOLATORIN_SPERIOD = (uint32)0;
for ( int i0=0; i0 < 4; i0++ )
{
mABSENCALARM_STATE[i0] = (MRQ_CAN_NETMANAGELED)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mABSENCALARM_UPLIMIT[i0] = (uint32)0;
}

for ( int i0=0; i0 < 4; i0++ )
{
mABSENCALARM_DOWNLIMIT[i0] = (uint32)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mABSENCALARM_ZEROVALUE[i0] = (uint32)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mABSENCALARM_ZEROPOSITION[i0] = (MRQ_ABSENCALARM_ZEROPOSITION_1)0;
}
	mABSENCALARM_RESPONSE = (MRQ_MOTIONPLAN_OOSLINERESPONSE_1)0;

for ( int i0=0; i0 < 4; i0++ )
{
mDISTANCEALARM_STATE[i0] = (MRQ_CAN_NETMANAGELED)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mDISTANCEALARM_ALARM1DIST[i0] = (uint16)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mDISTANCEALARM_ALARM2DIST[i0] = (uint16)0;
}
for ( int i0=0; i0 < 4; i0++ )
{
mDISTANCEALARM_ALARM3DIST[i0] = (uint16)0;
}

}
QString _MRQ_model::toString( MRQ_LINK_INTFC eType )
{
	return QString( MRQ_LINK_INTFC_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_LINK_DEVICEINFO eType )
{
	return QString( MRQ_LINK_DEVICEINFO_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_LINK_DEVICEINFO_1 eType )
{
	return QString( MRQ_LINK_DEVICEINFO_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_SYSTEM_WORKMODE eType )
{
	return QString( MRQ_SYSTEM_WORKMODE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_SYSTEM_POWERON eType )
{
	return QString( MRQ_SYSTEM_POWERON_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_RS232_BAUD eType )
{
	return QString( MRQ_RS232_BAUD_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_RS232_WORDLEN eType )
{
	return QString( MRQ_RS232_WORDLEN_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_RS232_FLOWCTL eType )
{
	return QString( MRQ_RS232_FLOWCTL_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_RS232_PARITY eType )
{
	return QString( MRQ_RS232_PARITY_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_RS232_STOPBIT eType )
{
	return QString( MRQ_RS232_STOPBIT_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_CAN_TYPE eType )
{
	return QString( MRQ_CAN_TYPE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_CAN_BAUD eType )
{
	return QString( MRQ_CAN_BAUD_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_CAN_NETMANAGELED eType )
{
	return QString( MRQ_CAN_NETMANAGELED_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_CAN_NETMANAGESTATE eType )
{
	return QString( MRQ_CAN_NETMANAGESTATE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_CAN_NETMANAGEID eType )
{
	return QString( MRQ_CAN_NETMANAGEID_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_CLOCK_STARTTYPE eType )
{
	return QString( MRQ_CLOCK_STARTTYPE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_CLOCK_SYNCSTATE eType )
{
	return QString( MRQ_CLOCK_SYNCSTATE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTION_SWITCH eType )
{
	return QString( MRQ_MOTION_SWITCH_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTION_SWITCH_1 eType )
{
	return QString( MRQ_MOTION_SWITCH_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTION_STATE_2 eType )
{
	return QString( MRQ_MOTION_STATE_2_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTION_STATEREPORT eType )
{
	return QString( MRQ_MOTION_STATEREPORT_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTION_STARTSOURCE eType )
{
	return QString( MRQ_MOTION_STARTSOURCE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_IDENTITY_GROUP eType )
{
	return QString( MRQ_IDENTITY_GROUP_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_IDENTITY_LABEL eType )
{
	return QString( MRQ_IDENTITY_LABEL_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_IDENTITY_LABEL_1 eType )
{
	return QString( MRQ_IDENTITY_LABEL_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTOR_STEPANGLE eType )
{
	return QString( MRQ_MOTOR_STEPANGLE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTOR_TYPE eType )
{
	return QString( MRQ_MOTOR_TYPE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTOR_POSITIONUNIT eType )
{
	return QString( MRQ_MOTOR_POSITIONUNIT_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTOR_SIZE eType )
{
	return QString( MRQ_MOTOR_SIZE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_ENCODER_CHANNELNUM eType )
{
	return QString( MRQ_ENCODER_CHANNELNUM_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_ENCODER_TYPE eType )
{
	return QString( MRQ_ENCODER_TYPE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_ENCODER_MULTIPLE eType )
{
	return QString( MRQ_ENCODER_MULTIPLE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_ENCODER_STATE eType )
{
	return QString( MRQ_ENCODER_STATE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_PVTCONFIG_1 eType )
{
	return QString( MRQ_MOTIONPLAN_PVTCONFIG_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_PRESETSTATE_1 eType )
{
	return QString( MRQ_MOTIONPLAN_PRESETSTATE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_EXECUTEMODE_1 eType )
{
	return QString( MRQ_MOTIONPLAN_EXECUTEMODE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_PLANMODE_1 eType )
{
	return QString( MRQ_MOTIONPLAN_PLANMODE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_MOTIONMODE_1 eType )
{
	return QString( MRQ_MOTIONPLAN_MOTIONMODE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_MODIFYDUTY_1 eType )
{
	return QString( MRQ_MOTIONPLAN_MODIFYDUTY_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_ENDSTATE_1 eType )
{
	return QString( MRQ_MOTIONPLAN_ENDSTATE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_STOPMODE_1 eType )
{
	return QString( MRQ_MOTIONPLAN_STOPMODE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_MOTIONPLAN_OOSLINERESPONSE_1 eType )
{
	return QString( MRQ_MOTIONPLAN_OOSLINERESPONSE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_REPORT_STATE eType )
{
	return QString( MRQ_REPORT_STATE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_TRIGGER_MODE eType )
{
	return QString( MRQ_TRIGGER_MODE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_TRIGGER_PATTERN eType )
{
	return QString( MRQ_TRIGGER_PATTERN_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_TRIGGER_PATTSMODE eType )
{
	return QString( MRQ_TRIGGER_PATTSMODE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_TRIGGER_LEVELSTATE eType )
{
	return QString( MRQ_TRIGGER_LEVELSTATE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_TRIGGER_LEVELTYPE_1 eType )
{
	return QString( MRQ_TRIGGER_LEVELTYPE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DRIVER_TYPE eType )
{
	return QString( MRQ_DRIVER_TYPE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DRIVER_STATEREG eType )
{
	return QString( MRQ_DRIVER_STATEREG_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DRIVER_MICROSTEPS eType )
{
	return QString( MRQ_DRIVER_MICROSTEPS_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DRIVER_SGLIMIT eType )
{
	return QString( MRQ_DRIVER_SGLIMIT_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DRIVER_SGPARASET eType )
{
	return QString( MRQ_DRIVER_SGPARASET_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DRIVER_MINICURRRATIO eType )
{
	return QString( MRQ_DRIVER_MINICURRRATIO_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DRIVER_REGCONFIG eType )
{
	return QString( MRQ_DRIVER_REGCONFIG_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DIGITALOUTPUT_STATE eType )
{
	return QString( MRQ_DIGITALOUTPUT_STATE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DIGITALOUTPUT_STATE_1 eType )
{
	return QString( MRQ_DIGITALOUTPUT_STATE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DIGITALOUTPUT_SIGNAL_1 eType )
{
	return QString( MRQ_DIGITALOUTPUT_SIGNAL_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DIGITALOUTPUT_POLARITY_1 eType )
{
	return QString( MRQ_DIGITALOUTPUT_POLARITY_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_DIGITALOUTPUT_CONDITION_1 eType )
{
	return QString( MRQ_DIGITALOUTPUT_CONDITION_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_ISOLATOROUTPUT_STATE eType )
{
	return QString( MRQ_ISOLATOROUTPUT_STATE_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_ISOLATOROUTPUT_RESPONSE_1 eType )
{
	return QString( MRQ_ISOLATOROUTPUT_RESPONSE_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_SENSORUART_BAUD eType )
{
	return QString( MRQ_SENSORUART_BAUD_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_SENSORUART_BAUD_1 eType )
{
	return QString( MRQ_SENSORUART_BAUD_1_toString( eType ) );
}
QString _MRQ_model::toString( MRQ_ABSENCALARM_ZEROPOSITION_1 eType )
{
	return QString( MRQ_ABSENCALARM_ZEROPOSITION_1_toString( eType ) );
}
int _MRQ_model::toValue( const QString &str, MRQ_LINK_INTFC *pEVal )
{
	return ( MRQ_LINK_INTFC_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_LINK_DEVICEINFO *pEVal )
{
	return ( MRQ_LINK_DEVICEINFO_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_LINK_DEVICEINFO_1 *pEVal )
{
	return ( MRQ_LINK_DEVICEINFO_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_SYSTEM_WORKMODE *pEVal )
{
	return ( MRQ_SYSTEM_WORKMODE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_SYSTEM_POWERON *pEVal )
{
	return ( MRQ_SYSTEM_POWERON_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_RS232_BAUD *pEVal )
{
	return ( MRQ_RS232_BAUD_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_RS232_WORDLEN *pEVal )
{
	return ( MRQ_RS232_WORDLEN_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_RS232_FLOWCTL *pEVal )
{
	return ( MRQ_RS232_FLOWCTL_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_RS232_PARITY *pEVal )
{
	return ( MRQ_RS232_PARITY_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_RS232_STOPBIT *pEVal )
{
	return ( MRQ_RS232_STOPBIT_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_CAN_TYPE *pEVal )
{
	return ( MRQ_CAN_TYPE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_CAN_BAUD *pEVal )
{
	return ( MRQ_CAN_BAUD_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_CAN_NETMANAGELED *pEVal )
{
	return ( MRQ_CAN_NETMANAGELED_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_CAN_NETMANAGESTATE *pEVal )
{
	return ( MRQ_CAN_NETMANAGESTATE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_CAN_NETMANAGEID *pEVal )
{
	return ( MRQ_CAN_NETMANAGEID_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_CLOCK_STARTTYPE *pEVal )
{
	return ( MRQ_CLOCK_STARTTYPE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_CLOCK_SYNCSTATE *pEVal )
{
	return ( MRQ_CLOCK_SYNCSTATE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTION_SWITCH *pEVal )
{
	return ( MRQ_MOTION_SWITCH_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTION_SWITCH_1 *pEVal )
{
	return ( MRQ_MOTION_SWITCH_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTION_STATE_2 *pEVal )
{
	return ( MRQ_MOTION_STATE_2_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTION_STATEREPORT *pEVal )
{
	return ( MRQ_MOTION_STATEREPORT_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTION_STARTSOURCE *pEVal )
{
	return ( MRQ_MOTION_STARTSOURCE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_IDENTITY_GROUP *pEVal )
{
	return ( MRQ_IDENTITY_GROUP_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_IDENTITY_LABEL *pEVal )
{
	return ( MRQ_IDENTITY_LABEL_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_IDENTITY_LABEL_1 *pEVal )
{
	return ( MRQ_IDENTITY_LABEL_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTOR_STEPANGLE *pEVal )
{
	return ( MRQ_MOTOR_STEPANGLE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTOR_TYPE *pEVal )
{
	return ( MRQ_MOTOR_TYPE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTOR_POSITIONUNIT *pEVal )
{
	return ( MRQ_MOTOR_POSITIONUNIT_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTOR_SIZE *pEVal )
{
	return ( MRQ_MOTOR_SIZE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_ENCODER_CHANNELNUM *pEVal )
{
	return ( MRQ_ENCODER_CHANNELNUM_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_ENCODER_TYPE *pEVal )
{
	return ( MRQ_ENCODER_TYPE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_ENCODER_MULTIPLE *pEVal )
{
	return ( MRQ_ENCODER_MULTIPLE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_ENCODER_STATE *pEVal )
{
	return ( MRQ_ENCODER_STATE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_PVTCONFIG_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_PVTCONFIG_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_PRESETSTATE_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_PRESETSTATE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_EXECUTEMODE_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_EXECUTEMODE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_PLANMODE_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_PLANMODE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_MOTIONMODE_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_MOTIONMODE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_MODIFYDUTY_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_MODIFYDUTY_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_ENDSTATE_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_ENDSTATE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_STOPMODE_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_STOPMODE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_MOTIONPLAN_OOSLINERESPONSE_1 *pEVal )
{
	return ( MRQ_MOTIONPLAN_OOSLINERESPONSE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_REPORT_STATE *pEVal )
{
	return ( MRQ_REPORT_STATE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_TRIGGER_MODE *pEVal )
{
	return ( MRQ_TRIGGER_MODE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_TRIGGER_PATTERN *pEVal )
{
	return ( MRQ_TRIGGER_PATTERN_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_TRIGGER_PATTSMODE *pEVal )
{
	return ( MRQ_TRIGGER_PATTSMODE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_TRIGGER_LEVELSTATE *pEVal )
{
	return ( MRQ_TRIGGER_LEVELSTATE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_TRIGGER_LEVELTYPE_1 *pEVal )
{
	return ( MRQ_TRIGGER_LEVELTYPE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DRIVER_TYPE *pEVal )
{
	return ( MRQ_DRIVER_TYPE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DRIVER_STATEREG *pEVal )
{
	return ( MRQ_DRIVER_STATEREG_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DRIVER_MICROSTEPS *pEVal )
{
	return ( MRQ_DRIVER_MICROSTEPS_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DRIVER_SGLIMIT *pEVal )
{
	return ( MRQ_DRIVER_SGLIMIT_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DRIVER_SGPARASET *pEVal )
{
	return ( MRQ_DRIVER_SGPARASET_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DRIVER_MINICURRRATIO *pEVal )
{
	return ( MRQ_DRIVER_MINICURRRATIO_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DRIVER_REGCONFIG *pEVal )
{
	return ( MRQ_DRIVER_REGCONFIG_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DIGITALOUTPUT_STATE *pEVal )
{
	return ( MRQ_DIGITALOUTPUT_STATE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DIGITALOUTPUT_STATE_1 *pEVal )
{
	return ( MRQ_DIGITALOUTPUT_STATE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DIGITALOUTPUT_SIGNAL_1 *pEVal )
{
	return ( MRQ_DIGITALOUTPUT_SIGNAL_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DIGITALOUTPUT_POLARITY_1 *pEVal )
{
	return ( MRQ_DIGITALOUTPUT_POLARITY_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_DIGITALOUTPUT_CONDITION_1 *pEVal )
{
	return ( MRQ_DIGITALOUTPUT_CONDITION_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_ISOLATOROUTPUT_STATE *pEVal )
{
	return ( MRQ_ISOLATOROUTPUT_STATE_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_ISOLATOROUTPUT_RESPONSE_1 *pEVal )
{
	return ( MRQ_ISOLATOROUTPUT_RESPONSE_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_SENSORUART_BAUD *pEVal )
{
	return ( MRQ_SENSORUART_BAUD_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_SENSORUART_BAUD_1 *pEVal )
{
	return ( MRQ_SENSORUART_BAUD_1_toValue( str.toLatin1().data(), pEVal) );
}
int _MRQ_model::toValue( const QString &str, MRQ_ABSENCALARM_ZEROPOSITION_1 *pEVal )
{
	return ( MRQ_ABSENCALARM_ZEROPOSITION_1_toValue( str.toLatin1().data(), pEVal) );
}
//! ENUM
//! NONE|CAN|RS232
int _MRQ_model::setLINK_INTFC( MRQ_LINK_INTFC val0 )
{
	//! 1 0
	int ret=0; 
	mLINK_INTFC = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getLINK_INTFC(  MRQ_LINK_INTFC * val0, bool bQuery )
{
	//! 1 1
	int ret = 0;

	byte lval0 = 0;
	*val0 = mLINK_INTFC;
	return 0;
}
//! 
//! 
int _MRQ_model::getLINK_DEVICEINFO(  MRQ_LINK_DEVICEINFO * val0, MRQ_LINK_DEVICEINFO_1 * val1, uint32 * val2, bool bQuery )
{
	//! 1 2
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	uint32 lval2 = 0;
	*val0 = mLINK_DEVICEINFO;
	*val1 = mLINK_DEVICEINFO1;
	*val2 = mLINK_DEVICEINFO2;
	return 0;
}
//! ENUM
//! NORMAL|NONE
int _MRQ_model::setSYSTEM_WORKMODE( MRQ_SYSTEM_WORKMODE val0 )
{
	//! 2 0
	int ret=0; 
	mSYSTEM_WORKMODE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getSYSTEM_WORKMODE(  MRQ_SYSTEM_WORKMODE * val0, bool bQuery )
{
	//! 2 1
	int ret = 0;

	byte lval0 = 0;
	*val0 = mSYSTEM_WORKMODE;
	return 0;
}
//! ENUM
//! DEFAULT|LAST
int _MRQ_model::setSYSTEM_POWERON( MRQ_SYSTEM_POWERON val0 )
{
	//! 2 2
	int ret=0; 
	mSYSTEM_POWERON = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getSYSTEM_POWERON(  MRQ_SYSTEM_POWERON * val0, bool bQuery )
{
	//! 2 3
	int ret = 0;

	byte lval0 = 0;
	*val0 = mSYSTEM_POWERON;
	return 0;
}
//! 
//! 
int _MRQ_model::getSYSTEM_SN(  byte * val0, char * val1, char * val2, char * val3, char * val4, char * val5, bool bQuery )
{
	//! 2 4
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	byte lval2 = 0;
	byte lval3 = 0;
	byte lval4 = 0;
	byte lval5 = 0;
	*val0 = mSYSTEM_SN;
	*val1 = mSYSTEM_SN1;
	*val2 = mSYSTEM_SN2;
	*val3 = mSYSTEM_SN3;
	*val4 = mSYSTEM_SN4;
	*val5 = mSYSTEM_SN5;
	return 0;
}
//! 
//! 
int _MRQ_model::getSYSTEM_TYPE(  MRQ_LINK_DEVICEINFO * val0, MRQ_LINK_DEVICEINFO_1 * val1, bool bQuery )
{
	//! 2 5
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	*val0 = mSYSTEM_TYPE;
	*val1 = mSYSTEM_TYPE1;
	return 0;
}
//! 
//! 
int _MRQ_model::getSYSTEM_SOFTVER(  char * val0, char * val1, char * val2, bool bQuery )
{
	//! 2 6
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	byte lval2 = 0;
	*val0 = mSYSTEM_SOFTVER;
	*val1 = mSYSTEM_SOFTVER1;
	*val2 = mSYSTEM_SOFTVER2;
	return 0;
}
//! 
//! 
int _MRQ_model::getSYSTEM_FPGAVER(  char * val0, char * val1, char * val2, bool bQuery )
{
	//! 2 7
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	byte lval2 = 0;
	*val0 = mSYSTEM_FPGAVER;
	*val1 = mSYSTEM_FPGAVER1;
	*val2 = mSYSTEM_FPGAVER2;
	return 0;
}
//! 
//! 
int _MRQ_model::getSYSTEM_HARDVER(  char * val0, char * val1, bool bQuery )
{
	//! 2 8
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	*val0 = mSYSTEM_HARDVER;
	*val1 = mSYSTEM_HARDVER1;
	return 0;
}
//! 
//! 
int _MRQ_model::getSYSTEM_BOOTVER(  char * val0, char * val1, bool bQuery )
{
	//! 2 9
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	*val0 = mSYSTEM_BOOTVER;
	*val1 = mSYSTEM_BOOTVER1;
	return 0;
}
//! 
//! 
int _MRQ_model::getSYSTEM_EVENTCODE(  char * val0, char * val1, char * val2, char * val3, char * val4, char * val5, bool bQuery )
{
	//! 2 10
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	byte lval2 = 0;
	byte lval3 = 0;
	byte lval4 = 0;
	byte lval5 = 0;
	*val0 = mSYSTEM_EVENTCODE;
	*val1 = mSYSTEM_EVENTCODE1;
	*val2 = mSYSTEM_EVENTCODE2;
	*val3 = mSYSTEM_EVENTCODE3;
	*val4 = mSYSTEM_EVENTCODE4;
	*val5 = mSYSTEM_EVENTCODE5;
	return 0;
}
//! 
//! 
int _MRQ_model::getSYSTEM_DIOSTATE(  uint16 * val0, bool bQuery )
{
	//! 2 11
	int ret = 0;

	uint16 lval0 = 0;
	*val0 = mSYSTEM_DIOSTATE;
	return 0;
}
//! ENUM
//! 4800|7200|9600|14400|19200|38400|57600|115200|128000
int _MRQ_model::setRS232_BAUD( MRQ_RS232_BAUD val0 )
{
	//! 3 0
	int ret=0; 
	mRS232_BAUD = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getRS232_BAUD(  MRQ_RS232_BAUD * val0, bool bQuery )
{
	//! 3 1
	int ret = 0;

	byte lval0 = 0;
	*val0 = mRS232_BAUD;
	return 0;
}
//! ENUM
//! 8|9
int _MRQ_model::setRS232_WORDLEN( MRQ_RS232_WORDLEN val0 )
{
	//! 3 2
	int ret=0; 
	mRS232_WORDLEN = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getRS232_WORDLEN(  MRQ_RS232_WORDLEN * val0, bool bQuery )
{
	//! 3 3
	int ret = 0;

	byte lval0 = 0;
	*val0 = mRS232_WORDLEN;
	return 0;
}
//! ENUM
//! NONE|RTS|CTS|RTS&CTS
int _MRQ_model::setRS232_FLOWCTL( MRQ_RS232_FLOWCTL val0 )
{
	//! 3 4
	int ret=0; 
	mRS232_FLOWCTL = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getRS232_FLOWCTL(  MRQ_RS232_FLOWCTL * val0, bool bQuery )
{
	//! 3 5
	int ret = 0;

	byte lval0 = 0;
	*val0 = mRS232_FLOWCTL;
	return 0;
}
//! ENUM
//! NONE|EVEN|ODD
int _MRQ_model::setRS232_PARITY( MRQ_RS232_PARITY val0 )
{
	//! 3 6
	int ret=0; 
	mRS232_PARITY = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getRS232_PARITY(  MRQ_RS232_PARITY * val0, bool bQuery )
{
	//! 3 7
	int ret = 0;

	byte lval0 = 0;
	*val0 = mRS232_PARITY;
	return 0;
}
//! ENUM
//! 1|0.5|2|1.5
int _MRQ_model::setRS232_STOPBIT( MRQ_RS232_STOPBIT val0 )
{
	//! 3 8
	int ret=0; 
	mRS232_STOPBIT = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getRS232_STOPBIT(  MRQ_RS232_STOPBIT * val0, bool bQuery )
{
	//! 3 9
	int ret = 0;

	byte lval0 = 0;
	*val0 = mRS232_STOPBIT;
	return 0;
}
//! 
//! 
int _MRQ_model::setRS232_APPLYPARA(  )
{
	//! 3 10
	int ret=0; 

	return ret;
}
//! ENUM
//! A|B
int _MRQ_model::setCAN_TYPE( MRQ_CAN_TYPE val0 )
{
	//! 4 0
	int ret=0; 
	mCAN_TYPE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_TYPE(  MRQ_CAN_TYPE * val0, bool bQuery )
{
	//! 4 1
	int ret = 0;

	byte lval0 = 0;
	*val0 = mCAN_TYPE;
	return 0;
}
//! ENUM
//! 1000|500|250|125|100|50|20|10
int _MRQ_model::setCAN_BAUD( MRQ_CAN_BAUD val0 )
{
	//! 4 2
	int ret=0; 
	mCAN_BAUD = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_BAUD(  MRQ_CAN_BAUD * val0, bool bQuery )
{
	//! 4 3
	int ret = 0;

	byte lval0 = 0;
	*val0 = mCAN_BAUD;
	return 0;
}
//! U8
//! 
int _MRQ_model::setCAN_GROUP( byte val0 )
{
	//! 4 4
	int ret=0; 
	mCAN_GROUP = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_GROUP(  byte * val0, bool bQuery )
{
	//! 4 5
	int ret = 0;

	byte lval0 = 0;
	*val0 = mCAN_GROUP;
	return 0;
}
//! U32
//! 
int _MRQ_model::setCAN_SENDID( uint32 val0 )
{
	//! 4 6
	int ret=0; 
	mCAN_SENDID = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_SENDID(  uint32 * val0, bool bQuery )
{
	//! 4 7
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mCAN_SENDID;
	return 0;
}
//! U32
//! 
int _MRQ_model::setCAN_RECEIVEID( uint32 val0 )
{
	//! 4 8
	int ret=0; 
	mCAN_RECEIVEID = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_RECEIVEID(  uint32 * val0, bool bQuery )
{
	//! 4 9
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mCAN_RECEIVEID;
	return 0;
}
//! U32
//! 
int _MRQ_model::setCAN_GROUPID1( uint32 val0 )
{
	//! 4 10
	int ret=0; 
	mCAN_GROUPID1 = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_GROUPID1(  uint32 * val0, bool bQuery )
{
	//! 4 11
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mCAN_GROUPID1;
	return 0;
}
//! U32
//! 
int _MRQ_model::setCAN_GROUPID2( uint32 val0 )
{
	//! 4 12
	int ret=0; 
	mCAN_GROUPID2 = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_GROUPID2(  uint32 * val0, bool bQuery )
{
	//! 4 13
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mCAN_GROUPID2;
	return 0;
}
//! U32
//! 
int _MRQ_model::setCAN_BROADCASTID( uint32 val0 )
{
	//! 4 14
	int ret=0; 
	mCAN_BROADCASTID = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_BROADCASTID(  uint32 * val0, bool bQuery )
{
	//! 4 15
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mCAN_BROADCASTID;
	return 0;
}
//! 
//! 
int _MRQ_model::setCAN_APPLYPARA(  )
{
	//! 4 16
	int ret=0; 

	return ret;
}
//! ENUM
//! OFF|ON
int _MRQ_model::setCAN_NETMANAGELED( MRQ_CAN_NETMANAGELED val0 )
{
	//! 4 17
	int ret=0; 

	return ret;
}
//! ENUM
//! IDLE|HASH|SIGNATURE
int _MRQ_model::setCAN_NETMANAGESTATE( MRQ_CAN_NETMANAGESTATE val0 )
{
	//! 4 18
	int ret=0; 
	mCAN_NETMANAGESTATE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_NETMANAGESTATE(  MRQ_CAN_NETMANAGESTATE * val0, bool bQuery )
{
	//! 4 19
	int ret = 0;

	byte lval0 = 0;
	*val0 = mCAN_NETMANAGESTATE;
	return 0;
}
//! ENUM,U32
//! NONE|SENDID|RECEIVEID
int _MRQ_model::setCAN_NETMANAGEID( MRQ_CAN_NETMANAGEID val0
,uint32 val1 )
{
	//! 4 20
	int ret=0; 
	mCAN_NETMANAGEID[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! NONE|SENDID|RECEIVEID
int _MRQ_model::getCAN_NETMANAGEID( MRQ_CAN_NETMANAGEID val0, uint32 * val1, bool bQuery )
{
	//! 4 21
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mCAN_NETMANAGEID[ (int)val0 ];
	return 0;
}
//! U32
//! 
int _MRQ_model::setCAN_NETMANAGEHASH( uint32 val0 )
{
	//! 4 22
	int ret=0; 
	mCAN_NETMANAGEHASH = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCAN_NETMANAGEHASH(  uint32 * val0, bool bQuery )
{
	//! 4 23
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mCAN_NETMANAGEHASH;
	return 0;
}
//! U32
//! 
int _MRQ_model::setCLOCK_FREQUENCY( uint32 val0 )
{
	//! 5 0
	int ret=0; 
	mCLOCK_FREQUENCY = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCLOCK_FREQUENCY(  uint32 * val0, bool bQuery )
{
	//! 5 1
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mCLOCK_FREQUENCY;
	return 0;
}
//! ENUM
//! OFF|ON
int _MRQ_model::setCLOCK_SYNCREGISTER( MRQ_CAN_NETMANAGELED val0 )
{
	//! 5 2
	int ret=0; 
	mCLOCK_SYNCREGISTER = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCLOCK_SYNCREGISTER(  MRQ_CAN_NETMANAGELED * val0, bool bQuery )
{
	//! 5 3
	int ret = 0;

	byte lval0 = 0;
	*val0 = mCLOCK_SYNCREGISTER;
	return 0;
}
//! ENUM
//! RADIOID|RECEIVEID|GROUPID1|GROUPID2
int _MRQ_model::setCLOCK_STARTTYPE( MRQ_CLOCK_STARTTYPE val0 )
{
	//! 5 4
	int ret=0; 
	mCLOCK_STARTTYPE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCLOCK_STARTTYPE(  MRQ_CLOCK_STARTTYPE * val0, bool bQuery )
{
	//! 5 5
	int ret = 0;

	byte lval0 = 0;
	*val0 = mCLOCK_STARTTYPE;
	return 0;
}
//! ENUM
//! END|START
int _MRQ_model::setCLOCK_SYNCSTATE( MRQ_CLOCK_SYNCSTATE val0 )
{
	//! 5 6
	int ret=0; 
	mCLOCK_SYNCSTATE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getCLOCK_SYNCSTATE(  MRQ_CLOCK_SYNCSTATE * val0, bool bQuery )
{
	//! 5 7
	int ret = 0;

	byte lval0 = 0;
	*val0 = mCLOCK_SYNCSTATE;
	return 0;
}
//! 
//! 
int _MRQ_model::getCLOCK_COUNT(  uint32 * val0, bool bQuery )
{
	//! 5 8
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mCLOCK_COUNT;
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],RESET|STOP|RUN|PREPARE|EMERGSTOP,MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTION_SWITCH( byte val0
,MRQ_MOTION_SWITCH val1
,MRQ_MOTION_SWITCH_1 val2 )
{
	//! 21 0
	int ret=0; 

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTION_STATE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTION_STATE_2 * val2, bool bQuery )
{
	//! 21 1
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTION_STATE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],ACTIVE|QUERY
int _MRQ_model::setMOTION_STATEREPORT( byte val0
,MRQ_MOTION_STATEREPORT val1 )
{
	//! 21 2
	int ret=0; 
	mMOTION_STATEREPORT[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_STATEREPORT( byte val0, MRQ_MOTION_STATEREPORT * val1, bool bQuery )
{
	//! 21 3
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTION_STATEREPORT[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],SOFTWARE|DIGITALIO|CAN|ALL
int _MRQ_model::setMOTION_STARTSOURCE( byte val0
,MRQ_MOTION_STARTSOURCE val1 )
{
	//! 21 4
	int ret=0; 
	mMOTION_STARTSOURCE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_STARTSOURCE( byte val0, MRQ_MOTION_STARTSOURCE * val1, bool bQuery )
{
	//! 21 5
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTION_STARTSOURCE[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],RADIOID|RECEIVEID|GROUPID1|GROUPID2
int _MRQ_model::setMOTION_STARTTYPE( byte val0
,MRQ_CLOCK_STARTTYPE val1 )
{
	//! 21 6
	int ret=0; 
	mMOTION_STARTTYPE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_STARTTYPE( byte val0, MRQ_CLOCK_STARTTYPE * val1, bool bQuery )
{
	//! 21 7
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTION_STARTTYPE[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTION_MAXSPEED( byte val0
,f32 val1 )
{
	//! 21 8
	int ret=0; 
	mMOTION_MAXSPEED[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_MAXSPEED( byte val0, f32 * val1, bool bQuery )
{
	//! 21 9
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTION_MAXSPEED[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTION_MINSPEED( byte val0
,f32 val1 )
{
	//! 21 10
	int ret=0; 
	mMOTION_MINSPEED[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_MINSPEED( byte val0, f32 * val1, bool bQuery )
{
	//! 21 11
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTION_MINSPEED[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTION_MAXPOSITION( byte val0
,f32 val1 )
{
	//! 21 12
	int ret=0; 
	mMOTION_MAXPOSITION[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_MAXPOSITION( byte val0, f32 * val1, bool bQuery )
{
	//! 21 13
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTION_MAXPOSITION[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTION_MINPOSITION( byte val0
,f32 val1 )
{
	//! 21 14
	int ret=0; 
	mMOTION_MINPOSITION[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_MINPOSITION( byte val0, f32 * val1, bool bQuery )
{
	//! 21 15
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTION_MINPOSITION[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTION_MAXTORQUE( byte val0
,f32 val1 )
{
	//! 21 16
	int ret=0; 
	mMOTION_MAXTORQUE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_MAXTORQUE( byte val0, f32 * val1, bool bQuery )
{
	//! 21 17
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTION_MAXTORQUE[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTION_MINTORQUE( byte val0
,f32 val1 )
{
	//! 21 18
	int ret=0; 
	mMOTION_MINTORQUE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_MINTORQUE( byte val0, f32 * val1, bool bQuery )
{
	//! 21 19
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTION_MINTORQUE[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTION_MAXACCELERATION( byte val0
,f32 val1 )
{
	//! 21 20
	int ret=0; 
	mMOTION_MAXACCELERATION[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_MAXACCELERATION( byte val0, f32 * val1, bool bQuery )
{
	//! 21 21
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTION_MAXACCELERATION[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTION_MINACCELERATION( byte val0
,f32 val1 )
{
	//! 21 22
	int ret=0; 
	mMOTION_MINACCELERATION[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_MINACCELERATION( byte val0, f32 * val1, bool bQuery )
{
	//! 21 23
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTION_MINACCELERATION[ (int)val0 ];
	return 0;
}
//! U8,U32
//! [CHANNUM]
int _MRQ_model::setMOTION_ORIGIN( byte val0
,uint32 val1 )
{
	//! 21 24
	int ret=0; 
	mMOTION_ORIGIN[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_ORIGIN( byte val0, uint32 * val1, bool bQuery )
{
	//! 21 25
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mMOTION_ORIGIN[ (int)val0 ];
	return 0;
}
//! U8
//! [CHANNUM]
int _MRQ_model::setMOTION_GOORIGIN( byte val0 )
{
	//! 21 26
	int ret=0; 

	return ret;
}
//! U8,ENUM
//! [CHANNUM],OFF|ON
int _MRQ_model::setMOTION_OFFSETSTATE( byte val0
,MRQ_CAN_NETMANAGELED val1 )
{
	//! 21 27
	int ret=0; 
	mMOTION_OFFSETSTATE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_OFFSETSTATE( byte val0, MRQ_CAN_NETMANAGELED * val1, bool bQuery )
{
	//! 21 28
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTION_OFFSETSTATE[ (int)val0 ];
	return 0;
}
//! U8,S32
//! [CHANNUM]
int _MRQ_model::setMOTION_OFFSET( byte val0
,int32 val1 )
{
	//! 21 29
	int ret=0; 

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_COUNTCIRCLE( byte val0, int16 * val1, bool bQuery )
{
	//! 21 30
	int ret = 0;

	int16 lval0 = 0;
	*val1 = mMOTION_COUNTCIRCLE[ (int)val0 ];
	return 0;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_ABCOUNT( byte val0, int32 * val1, bool bQuery )
{
	//! 21 31
	int ret = 0;

	int32 lval0 = 0;
	*val1 = mMOTION_ABCOUNT[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],OFF|ON
int _MRQ_model::setMOTION_REVMOTION( byte val0
,MRQ_CAN_NETMANAGELED val1 )
{
	//! 21 32
	int ret=0; 
	mMOTION_REVMOTION[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTION_REVMOTION( byte val0, MRQ_CAN_NETMANAGELED * val1, bool bQuery )
{
	//! 21 33
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTION_REVMOTION[ (int)val0 ];
	return 0;
}
//! U8,ENUM,U8
//! [CHANNUM],GROUP1|GROUP2
int _MRQ_model::setIDENTITY_GROUP( byte val0
,MRQ_IDENTITY_GROUP val1
,byte val2 )
{
	//! 22 0
	int ret=0; 
	mIDENTITY_GROUP[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],GROUP1|GROUP2
int _MRQ_model::getIDENTITY_GROUP( byte val0
,MRQ_IDENTITY_GROUP val1, byte * val2, bool bQuery )
{
	//! 22 1
	int ret = 0;

	byte lval0 = 0;
	*val2 = mIDENTITY_GROUP[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! ENUM
//! OFF|ON
int _MRQ_model::setIDENTITY_DISTDEVICE( MRQ_CAN_NETMANAGELED val0 )
{
	//! 22 2
	int ret=0; 
	mIDENTITY_DISTDEVICE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getIDENTITY_DISTDEVICE(  MRQ_CAN_NETMANAGELED * val0, bool bQuery )
{
	//! 22 3
	int ret = 0;

	byte lval0 = 0;
	*val0 = mIDENTITY_DISTDEVICE;
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],SINANJU|MEGATRON|GOUF,S1|S2|S3|S4
int _MRQ_model::setIDENTITY_LABEL( byte val0
,MRQ_IDENTITY_LABEL val1
,MRQ_IDENTITY_LABEL_1 val2 )
{
	//! 22 4
	int ret=0; 
	mIDENTITY_LABEL[ (int)val0 ] = val1;
	mIDENTITY_LABEL1[ (int)val0 ] = val2;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getIDENTITY_LABEL( byte val0, MRQ_IDENTITY_LABEL * val1, MRQ_IDENTITY_LABEL_1 * val2, bool bQuery )
{
	//! 22 5
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	*val1 = mIDENTITY_LABEL[ (int)val0 ];
	*val2 = mIDENTITY_LABEL1[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],1.8|0.9|15|7.5
int _MRQ_model::setMOTOR_STEPANGLE( byte val0
,MRQ_MOTOR_STEPANGLE val1 )
{
	//! 51 0
	int ret=0; 
	mMOTOR_STEPANGLE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_STEPANGLE( byte val0, MRQ_MOTOR_STEPANGLE * val1, bool bQuery )
{
	//! 51 1
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTOR_STEPANGLE[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],ROTARY|LINEAR
int _MRQ_model::setMOTOR_TYPE( byte val0
,MRQ_MOTOR_TYPE val1 )
{
	//! 51 2
	int ret=0; 
	mMOTOR_TYPE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_TYPE( byte val0, MRQ_MOTOR_TYPE * val1, bool bQuery )
{
	//! 51 3
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTOR_TYPE[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],ANGLE|RADIAN|MILLIMETER
int _MRQ_model::setMOTOR_POSITIONUNIT( byte val0
,MRQ_MOTOR_POSITIONUNIT val1 )
{
	//! 51 4
	int ret=0; 
	mMOTOR_POSITIONUNIT[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_POSITIONUNIT( byte val0, MRQ_MOTOR_POSITIONUNIT * val1, bool bQuery )
{
	//! 51 5
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTOR_POSITIONUNIT[ (int)val0 ];
	return 0;
}
//! U8,U16
//! [CHANNUM]
int _MRQ_model::setMOTOR_GEARRATIONUM( byte val0
,uint16 val1 )
{
	//! 51 6
	int ret=0; 
	mMOTOR_GEARRATIONUM[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_GEARRATIONUM( byte val0, uint16 * val1, bool bQuery )
{
	//! 51 7
	int ret = 0;

	uint16 lval0 = 0;
	*val1 = mMOTOR_GEARRATIONUM[ (int)val0 ];
	return 0;
}
//! U8,U16
//! [CHANNUM]
int _MRQ_model::setMOTOR_GEARRATIODEN( byte val0
,uint16 val1 )
{
	//! 51 8
	int ret=0; 
	mMOTOR_GEARRATIODEN[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_GEARRATIODEN( byte val0, uint16 * val1, bool bQuery )
{
	//! 51 9
	int ret = 0;

	uint16 lval0 = 0;
	*val1 = mMOTOR_GEARRATIODEN[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTOR_LEAD( byte val0
,f32 val1 )
{
	//! 51 10
	int ret=0; 
	mMOTOR_LEAD[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_LEAD( byte val0, f32 * val1, bool bQuery )
{
	//! 51 11
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTOR_LEAD[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTOR_PEAKSPEED( byte val0
,f32 val1 )
{
	//! 51 12
	int ret=0; 
	mMOTOR_PEAKSPEED[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_PEAKSPEED( byte val0, f32 * val1, bool bQuery )
{
	//! 51 13
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTOR_PEAKSPEED[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTOR_PEAKACCELERATION( byte val0
,f32 val1 )
{
	//! 51 14
	int ret=0; 
	mMOTOR_PEAKACCELERATION[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_PEAKACCELERATION( byte val0, f32 * val1, bool bQuery )
{
	//! 51 15
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTOR_PEAKACCELERATION[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],8|11|14|17|23|24
int _MRQ_model::setMOTOR_SIZE( byte val0
,MRQ_MOTOR_SIZE val1 )
{
	//! 51 16
	int ret=0; 
	mMOTOR_SIZE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_SIZE( byte val0, MRQ_MOTOR_SIZE * val1, bool bQuery )
{
	//! 51 17
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTOR_SIZE[ (int)val0 ];
	return 0;
}
//! U8,U8
//! [CHANNUM]
int _MRQ_model::setMOTOR_VOLTAGE( byte val0
,byte val1 )
{
	//! 51 18
	int ret=0; 
	mMOTOR_VOLTAGE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_VOLTAGE( byte val0, byte * val1, bool bQuery )
{
	//! 51 19
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTOR_VOLTAGE[ (int)val0 ];
	return 0;
}
//! U8,U8
//! [CHANNUM]
int _MRQ_model::setMOTOR_CURRENT( byte val0
,byte val1 )
{
	//! 51 20
	int ret=0; 
	mMOTOR_CURRENT[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_CURRENT( byte val0, byte * val1, bool bQuery )
{
	//! 51 21
	int ret = 0;

	byte lval0 = 0;
	*val1 = mMOTOR_CURRENT[ (int)val0 ];
	return 0;
}
//! U8,F32
//! [CHANNUM]
int _MRQ_model::setMOTOR_BACKLASH( byte val0
,f32 val1 )
{
	//! 51 22
	int ret=0; 
	mMOTOR_BACKLASH[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getMOTOR_BACKLASH( byte val0, f32 * val1, bool bQuery )
{
	//! 51 23
	int ret = 0;

	f32 lval0 = 0;
	*val1 = mMOTOR_BACKLASH[ (int)val0 ];
	return 0;
}
//! U8,U32
//! [CHANNUM]
int _MRQ_model::setENCODER_LINENUM( byte val0
,uint32 val1 )
{
	//! 52 0
	int ret=0; 
	mENCODER_LINENUM[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getENCODER_LINENUM( byte val0, uint32 * val1, bool bQuery )
{
	//! 52 1
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mENCODER_LINENUM[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],1|3
int _MRQ_model::setENCODER_CHANNELNUM( byte val0
,MRQ_ENCODER_CHANNELNUM val1 )
{
	//! 52 2
	int ret=0; 
	mENCODER_CHANNELNUM[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getENCODER_CHANNELNUM( byte val0, MRQ_ENCODER_CHANNELNUM * val1, bool bQuery )
{
	//! 52 3
	int ret = 0;

	byte lval0 = 0;
	*val1 = mENCODER_CHANNELNUM[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],INCREMENTAL|ABSOLUTE
int _MRQ_model::setENCODER_TYPE( byte val0
,MRQ_ENCODER_TYPE val1 )
{
	//! 52 4
	int ret=0; 
	mENCODER_TYPE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getENCODER_TYPE( byte val0, MRQ_ENCODER_TYPE * val1, bool bQuery )
{
	//! 52 5
	int ret = 0;

	byte lval0 = 0;
	*val1 = mENCODER_TYPE[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],SINGLE|DOUBLE|QUADRUPLE
int _MRQ_model::setENCODER_MULTIPLE( byte val0
,MRQ_ENCODER_MULTIPLE val1 )
{
	//! 52 6
	int ret=0; 
	mENCODER_MULTIPLE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getENCODER_MULTIPLE( byte val0, MRQ_ENCODER_MULTIPLE * val1, bool bQuery )
{
	//! 52 7
	int ret = 0;

	byte lval0 = 0;
	*val1 = mENCODER_MULTIPLE[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],NONE|OFF|ON
int _MRQ_model::setENCODER_STATE( byte val0
,MRQ_ENCODER_STATE val1 )
{
	//! 52 8
	int ret=0; 
	mENCODER_STATE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getENCODER_STATE( byte val0, MRQ_ENCODER_STATE * val1, bool bQuery )
{
	//! 52 9
	int ret = 0;

	byte lval0 = 0;
	*val1 = mENCODER_STATE[ (int)val0 ];
	return 0;
}
//! U8,U8
//! [CHANNUM]
int _MRQ_model::setENCODER_FEEDBACKRATIO( byte val0
,byte val1 )
{
	//! 52 10
	int ret=0; 
	mENCODER_FEEDBACKRATIO[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getENCODER_FEEDBACKRATIO( byte val0, byte * val1, bool bQuery )
{
	//! 52 11
	int ret = 0;

	byte lval0 = 0;
	*val1 = mENCODER_FEEDBACKRATIO[ (int)val0 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,END|CLEAR
int _MRQ_model::setMOTIONPLAN_PVTCONFIG( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_PVTCONFIG_1 val2 )
{
	//! 53 0
	int ret=0; 
	mMOTIONPLAN_PVTCONFIG[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_PVTCONFIG( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_PVTCONFIG_1 * val2, bool bQuery )
{
	//! 53 1
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_PVTCONFIG[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,OFF|ON|CALC
int _MRQ_model::setMOTIONPLAN_PRESETSTATE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_PRESETSTATE_1 val2 )
{
	//! 53 2
	int ret=0; 
	mMOTIONPLAN_PRESETSTATE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_PRESETSTATE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_PRESETSTATE_1 * val2, bool bQuery )
{
	//! 53 3
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_PRESETSTATE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,CYCLE|FIFO
int _MRQ_model::setMOTIONPLAN_EXECUTEMODE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_EXECUTEMODE_1 val2 )
{
	//! 53 4
	int ret=0; 
	mMOTIONPLAN_EXECUTEMODE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_EXECUTEMODE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_EXECUTEMODE_1 * val2, bool bQuery )
{
	//! 53 5
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_EXECUTEMODE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,CUBICPOLY|LINEAR|UNIFORM|TRAPEZOID
int _MRQ_model::setMOTIONPLAN_PLANMODE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_PLANMODE_1 val2 )
{
	//! 53 6
	int ret=0; 
	mMOTIONPLAN_PLANMODE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_PLANMODE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_PLANMODE_1 * val2, bool bQuery )
{
	//! 53 7
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_PLANMODE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,PVT|LVT_CORRECT|LVT_NOCORRECT
int _MRQ_model::setMOTIONPLAN_MOTIONMODE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_MOTIONMODE_1 val2 )
{
	//! 53 8
	int ret=0; 
	mMOTIONPLAN_MOTIONMODE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_MOTIONMODE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_MOTIONMODE_1 * val2, bool bQuery )
{
	//! 53 9
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_MOTIONMODE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,1/4|1/8|1/16|1/32
int _MRQ_model::setMOTIONPLAN_MODIFYDUTY( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_MODIFYDUTY_1 val2 )
{
	//! 53 10
	int ret=0; 
	mMOTIONPLAN_MODIFYDUTY[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_MODIFYDUTY( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_MODIFYDUTY_1 * val2, bool bQuery )
{
	//! 53 11
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_MODIFYDUTY[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_REMAINPOINT( byte val0
,MRQ_MOTION_SWITCH_1 val1, uint16 * val2, bool bQuery )
{
	//! 53 12
	int ret = 0;

	uint16 lval0 = 0;
	*val2 = mMOTIONPLAN_REMAINPOINT[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,U32
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTIONPLAN_CYCLENUM( byte val0
,MRQ_MOTION_SWITCH_1 val1
,uint32 val2 )
{
	//! 53 13
	int ret=0; 
	mMOTIONPLAN_CYCLENUM[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_CYCLENUM( byte val0
,MRQ_MOTION_SWITCH_1 val1, uint32 * val2, bool bQuery )
{
	//! 53 14
	int ret = 0;

	uint32 lval0 = 0;
	*val2 = mMOTIONPLAN_CYCLENUM[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,U8
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTIONPLAN_WARNPOINT( byte val0
,MRQ_MOTION_SWITCH_1 val1
,byte val2 )
{
	//! 53 15
	int ret=0; 
	mMOTIONPLAN_WARNPOINT[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_WARNPOINT( byte val0
,MRQ_MOTION_SWITCH_1 val1, byte * val2, bool bQuery )
{
	//! 53 16
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_WARNPOINT[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,STOP|HOLD
int _MRQ_model::setMOTIONPLAN_ENDSTATE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_ENDSTATE_1 val2 )
{
	//! 53 17
	int ret=0; 
	mMOTIONPLAN_ENDSTATE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_ENDSTATE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_ENDSTATE_1 * val2, bool bQuery )
{
	//! 53 18
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_ENDSTATE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_BUFFERSIZE( byte val0
,MRQ_MOTION_SWITCH_1 val1, uint32 * val2, bool bQuery )
{
	//! 53 19
	int ret = 0;

	uint32 lval0 = 0;
	*val2 = mMOTIONPLAN_BUFFERSIZE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,U16
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTIONPLAN_ACCSCALE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,uint16 val2 )
{
	//! 53 20
	int ret=0; 
	mMOTIONPLAN_ACCSCALE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_ACCSCALE( byte val0
,MRQ_MOTION_SWITCH_1 val1, uint16 * val2, bool bQuery )
{
	//! 53 21
	int ret = 0;

	uint16 lval0 = 0;
	*val2 = mMOTIONPLAN_ACCSCALE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,U16
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTIONPLAN_DECSCALE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,uint16 val2 )
{
	//! 53 22
	int ret=0; 
	mMOTIONPLAN_DECSCALE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_DECSCALE( byte val0
,MRQ_MOTION_SWITCH_1 val1, uint16 * val2, bool bQuery )
{
	//! 53 23
	int ret = 0;

	uint16 lval0 = 0;
	*val2 = mMOTIONPLAN_DECSCALE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,IMMEDIATE|DISTANCE
int _MRQ_model::setMOTIONPLAN_STOPMODE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_STOPMODE_1 val2 )
{
	//! 53 24
	int ret=0; 
	mMOTIONPLAN_STOPMODE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_STOPMODE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_STOPMODE_1 * val2, bool bQuery )
{
	//! 53 25
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_STOPMODE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,F32
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTIONPLAN_STOPDISTANCE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,f32 val2 )
{
	//! 53 26
	int ret=0; 
	mMOTIONPLAN_STOPDISTANCE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_STOPDISTANCE( byte val0
,MRQ_MOTION_SWITCH_1 val1, f32 * val2, bool bQuery )
{
	//! 53 27
	int ret = 0;

	f32 lval0 = 0;
	*val2 = mMOTIONPLAN_STOPDISTANCE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,F32
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTIONPLAN_STOPTIME( byte val0
,MRQ_MOTION_SWITCH_1 val1
,f32 val2 )
{
	//! 53 28
	int ret=0; 
	mMOTIONPLAN_STOPTIME[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_STOPTIME( byte val0
,MRQ_MOTION_SWITCH_1 val1, f32 * val2, bool bQuery )
{
	//! 53 29
	int ret = 0;

	f32 lval0 = 0;
	*val2 = mMOTIONPLAN_STOPTIME[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,OFF|ON
int _MRQ_model::setMOTIONPLAN_OOSLINESTATE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_CAN_NETMANAGELED val2 )
{
	//! 53 30
	int ret=0; 
	mMOTIONPLAN_OOSLINESTATE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_OOSLINESTATE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_CAN_NETMANAGELED * val2, bool bQuery )
{
	//! 53 31
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_OOSLINESTATE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,U16
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTIONPLAN_OOSLINEOUTNUM( byte val0
,MRQ_MOTION_SWITCH_1 val1
,uint16 val2 )
{
	//! 53 32
	int ret=0; 
	mMOTIONPLAN_OOSLINEOUTNUM[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_OOSLINEOUTNUM( byte val0
,MRQ_MOTION_SWITCH_1 val1, uint16 * val2, bool bQuery )
{
	//! 53 33
	int ret = 0;

	uint16 lval0 = 0;
	*val2 = mMOTIONPLAN_OOSLINEOUTNUM[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,NONE|ALARM|STOP|ALARM&STOP
int _MRQ_model::setMOTIONPLAN_OOSLINERESPONSE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_OOSLINERESPONSE_1 val2 )
{
	//! 53 34
	int ret=0; 
	mMOTIONPLAN_OOSLINERESPONSE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_OOSLINERESPONSE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_OOSLINERESPONSE_1 * val2, bool bQuery )
{
	//! 53 35
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_OOSLINERESPONSE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,OFF|ON
int _MRQ_model::setMOTIONPLAN_OOSTOTALSTATE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_CAN_NETMANAGELED val2 )
{
	//! 53 36
	int ret=0; 
	mMOTIONPLAN_OOSTOTALSTATE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_OOSTOTALSTATE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_CAN_NETMANAGELED * val2, bool bQuery )
{
	//! 53 37
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_OOSTOTALSTATE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,U32
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::setMOTIONPLAN_OOSTOTALOUTNUM( byte val0
,MRQ_MOTION_SWITCH_1 val1
,uint32 val2 )
{
	//! 53 38
	int ret=0; 
	mMOTIONPLAN_OOSTOTALOUTNUM[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_OOSTOTALOUTNUM( byte val0
,MRQ_MOTION_SWITCH_1 val1, uint32 * val2, bool bQuery )
{
	//! 53 39
	int ret = 0;

	uint32 lval0 = 0;
	*val2 = mMOTIONPLAN_OOSTOTALOUTNUM[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,NONE|ALARM|STOP|ALARM&STOP
int _MRQ_model::setMOTIONPLAN_OOSTOTALRESPONSE( byte val0
,MRQ_MOTION_SWITCH_1 val1
,MRQ_MOTIONPLAN_OOSLINERESPONSE_1 val2 )
{
	//! 53 40
	int ret=0; 
	mMOTIONPLAN_OOSTOTALRESPONSE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8
int _MRQ_model::getMOTIONPLAN_OOSTOTALRESPONSE( byte val0
,MRQ_MOTION_SWITCH_1 val1, MRQ_MOTIONPLAN_OOSLINERESPONSE_1 * val2, bool bQuery )
{
	//! 53 41
	int ret = 0;

	byte lval0 = 0;
	*val2 = mMOTIONPLAN_OOSTOTALRESPONSE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,U8,F32
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,[INDEX]
int _MRQ_model::setPOSITION( byte val0
,MRQ_MOTION_SWITCH_1 val1
,byte val2
,f32 val3 )
{
	//! 54 -1
	int ret=0; 

	return ret;
}
//! U8,ENUM,U8
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,[INDEX]
int _MRQ_model::getPOSITION( byte val0
,MRQ_MOTION_SWITCH_1 val1
,byte val2, f32 * val3, bool bQuery )
{
	//! 55 -1
	int ret = 0;

	f32 lval0 = 0;
	*val3 = mPOSITION[ (int)val0 ][ (int)val1 ][ (int)val2 ];
	return 0;
}
//! U8,ENUM,U8,F32
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,[INDEX]
int _MRQ_model::setVELOCITY( byte val0
,MRQ_MOTION_SWITCH_1 val1
,byte val2
,f32 val3 )
{
	//! 56 -1
	int ret=0; 

	return ret;
}
//! U8,ENUM,U8
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,[INDEX]
int _MRQ_model::getVELOCITY( byte val0
,MRQ_MOTION_SWITCH_1 val1
,byte val2, f32 * val3, bool bQuery )
{
	//! 57 -1
	int ret = 0;

	f32 lval0 = 0;
	*val3 = mVELOCITY[ (int)val0 ][ (int)val1 ][ (int)val2 ];
	return 0;
}
//! U8,ENUM,U8,F32
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,[INDEX]
int _MRQ_model::setTIME( byte val0
,MRQ_MOTION_SWITCH_1 val1
,byte val2
,f32 val3 )
{
	//! 58 -1
	int ret=0; 

	return ret;
}
//! U8,ENUM,U8
//! [CHANNUM],MAIN|SMALL|P1|P2|P3|P4|P5|P6|P7|P8,[INDEX]
int _MRQ_model::getTIME( byte val0
,MRQ_MOTION_SWITCH_1 val1
,byte val2, f32 * val3, bool bQuery )
{
	//! 59 -1
	int ret = 0;

	f32 lval0 = 0;
	*val3 = mTIME[ (int)val0 ][ (int)val1 ][ (int)val2 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],TORQUE|CYCLE|XANGLE|YANGLE|ZANGLE|XVEL|YVEL|ZVEL|XACC|YACC|ZACC|SGALL|SGSE|DIST|ABSENC,OFF|ON
int _MRQ_model::setREPORT_STATE( byte val0
,MRQ_REPORT_STATE val1
,MRQ_CAN_NETMANAGELED val2 )
{
	//! 60 0
	int ret=0; 
	mREPORT_STATE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],TORQUE|CYCLE|XANGLE|YANGLE|ZANGLE|XVEL|YVEL|ZVEL|XACC|YACC|ZACC|SGALL|SGSE|DIST|ABSENC
int _MRQ_model::getREPORT_STATE( byte val0
,MRQ_REPORT_STATE val1, MRQ_CAN_NETMANAGELED * val2, bool bQuery )
{
	//! 60 1
	int ret = 0;

	byte lval0 = 0;
	*val2 = mREPORT_STATE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,U32
//! [CHANNUM],TORQUE|CYCLE|XANGLE|YANGLE|ZANGLE|XVEL|YVEL|ZVEL|XACC|YACC|ZACC|SGALL|SGSE|DIST|ABSENC
int _MRQ_model::setREPORT_PERIOD( byte val0
,MRQ_REPORT_STATE val1
,uint32 val2 )
{
	//! 60 2
	int ret=0; 
	mREPORT_PERIOD[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],TORQUE|CYCLE|XANGLE|YANGLE|ZANGLE|XVEL|YVEL|ZVEL|XACC|YACC|ZACC|SGALL|SGSE|DIST|ABSENC
int _MRQ_model::getREPORT_PERIOD( byte val0
,MRQ_REPORT_STATE val1, uint32 * val2, bool bQuery )
{
	//! 60 3
	int ret = 0;

	uint32 lval0 = 0;
	*val2 = mREPORT_PERIOD[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],TORQUE|CYCLE|XANGLE|YANGLE|ZANGLE|XVEL|YVEL|ZVEL|XACC|YACC|ZACC|SGALL|SGSE|DIST|ABSENC
int _MRQ_model::getREPORT_DATA( byte val0
,MRQ_REPORT_STATE val1, uint32 * val2, bool bQuery )
{
	//! 60 4
	int ret = 0;

	uint32 lval0 = 0;
	*val2 = mREPORT_DATA[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],PATTERN|LEVEL
int _MRQ_model::setTRIGGER_MODE( byte val0
,MRQ_TRIGGER_MODE val1 )
{
	//! 61 0
	int ret=0; 
	mTRIGGER_MODE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getTRIGGER_MODE( byte val0, MRQ_TRIGGER_MODE * val1, bool bQuery )
{
	//! 61 1
	int ret = 0;

	byte lval0 = 0;
	*val1 = mTRIGGER_MODE[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],OFF|ON
int _MRQ_model::setTRIGGER_PATTSTATE( byte val0
,MRQ_CAN_NETMANAGELED val1 )
{
	//! 61 2
	int ret=0; 
	mTRIGGER_PATTSTATE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getTRIGGER_PATTSTATE( byte val0, MRQ_CAN_NETMANAGELED * val1, bool bQuery )
{
	//! 61 3
	int ret = 0;

	byte lval0 = 0;
	*val1 = mTRIGGER_PATTSTATE[ (int)val0 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],X|L|R|F|H,X|L|R|F|H
int _MRQ_model::setTRIGGER_PATTERN( byte val0
,MRQ_TRIGGER_PATTERN val1
,MRQ_TRIGGER_PATTERN val2 )
{
	//! 61 4
	int ret=0; 
	mTRIGGER_PATTERN[ (int)val0 ] = val1;
	mTRIGGER_PATTERN1[ (int)val0 ] = val2;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getTRIGGER_PATTERN( byte val0, MRQ_TRIGGER_PATTERN * val1, MRQ_TRIGGER_PATTERN * val2, bool bQuery )
{
	//! 61 5
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	*val1 = mTRIGGER_PATTERN[ (int)val0 ];
	*val2 = mTRIGGER_PATTERN1[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],NONE|ALARM|STOP|ALARM&STOP
int _MRQ_model::setTRIGGER_PATTRESP( byte val0
,MRQ_MOTIONPLAN_OOSLINERESPONSE_1 val1 )
{
	//! 61 6
	int ret=0; 
	mTRIGGER_PATTRESP[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getTRIGGER_PATTRESP( byte val0, MRQ_MOTIONPLAN_OOSLINERESPONSE_1 * val1, bool bQuery )
{
	//! 61 7
	int ret = 0;

	byte lval0 = 0;
	*val1 = mTRIGGER_PATTRESP[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],CONTINUED|INTERVAL|SINGLE
int _MRQ_model::setTRIGGER_PATTSMODE( byte val0
,MRQ_TRIGGER_PATTSMODE val1 )
{
	//! 61 8
	int ret=0; 
	mTRIGGER_PATTSMODE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getTRIGGER_PATTSMODE( byte val0, MRQ_TRIGGER_PATTSMODE * val1, bool bQuery )
{
	//! 61 9
	int ret = 0;

	byte lval0 = 0;
	*val1 = mTRIGGER_PATTSMODE[ (int)val0 ];
	return 0;
}
//! U8,U32
//! [CHANNUM]
int _MRQ_model::setTRIGGER_PATTSPERIOD( byte val0
,uint32 val1 )
{
	//! 61 10
	int ret=0; 
	mTRIGGER_PATTSPERIOD[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getTRIGGER_PATTSPERIOD( byte val0, uint32 * val1, bool bQuery )
{
	//! 61 11
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mTRIGGER_PATTSPERIOD[ (int)val0 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],TRIGL|TRIGR,OFF|ON
int _MRQ_model::setTRIGGER_LEVELSTATE( byte val0
,MRQ_TRIGGER_LEVELSTATE val1
,MRQ_CAN_NETMANAGELED val2 )
{
	//! 61 12
	int ret=0; 
	mTRIGGER_LEVELSTATE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],TRIGL|TRIGR
int _MRQ_model::getTRIGGER_LEVELSTATE( byte val0
,MRQ_TRIGGER_LEVELSTATE val1, MRQ_CAN_NETMANAGELED * val2, bool bQuery )
{
	//! 61 13
	int ret = 0;

	byte lval0 = 0;
	*val2 = mTRIGGER_LEVELSTATE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],TRIGL|TRIGR,RESERVE|LOW|RISE|FALL|HIGH
int _MRQ_model::setTRIGGER_LEVELTYPE( byte val0
,MRQ_TRIGGER_LEVELSTATE val1
,MRQ_TRIGGER_LEVELTYPE_1 val2 )
{
	//! 61 14
	int ret=0; 
	mTRIGGER_LEVELTYPE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],TRIGL|TRIGR
int _MRQ_model::getTRIGGER_LEVELTYPE( byte val0
,MRQ_TRIGGER_LEVELSTATE val1, MRQ_TRIGGER_LEVELTYPE_1 * val2, bool bQuery )
{
	//! 61 15
	int ret = 0;

	byte lval0 = 0;
	*val2 = mTRIGGER_LEVELTYPE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],TRIGL|TRIGR,NONE|ALARM|STOP|ALARM&STOP
int _MRQ_model::setTRIGGER_LEVELRESP( byte val0
,MRQ_TRIGGER_LEVELSTATE val1
,MRQ_MOTIONPLAN_OOSLINERESPONSE_1 val2 )
{
	//! 61 16
	int ret=0; 
	mTRIGGER_LEVELRESP[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],TRIGL|TRIGR
int _MRQ_model::getTRIGGER_LEVELRESP( byte val0
,MRQ_TRIGGER_LEVELSTATE val1, MRQ_MOTIONPLAN_OOSLINERESPONSE_1 * val2, bool bQuery )
{
	//! 61 17
	int ret = 0;

	byte lval0 = 0;
	*val2 = mTRIGGER_LEVELRESP[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,ENUM
//! [CHANNUM],TRIGL|TRIGR,CONTINUED|INTERVAL|SINGLE
int _MRQ_model::setTRIGGER_LEVELSMODE( byte val0
,MRQ_TRIGGER_LEVELSTATE val1
,MRQ_TRIGGER_PATTSMODE val2 )
{
	//! 61 18
	int ret=0; 
	mTRIGGER_LEVELSMODE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],TRIGL|TRIGR
int _MRQ_model::getTRIGGER_LEVELSMODE( byte val0
,MRQ_TRIGGER_LEVELSTATE val1, MRQ_TRIGGER_PATTSMODE * val2, bool bQuery )
{
	//! 61 19
	int ret = 0;

	byte lval0 = 0;
	*val2 = mTRIGGER_LEVELSMODE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,ENUM,F32
//! [CHANNUM],TRIGL|TRIGR
int _MRQ_model::setTRIGGER_LEVELSPERIOD( byte val0
,MRQ_TRIGGER_LEVELSTATE val1
,f32 val2 )
{
	//! 61 20
	int ret=0; 
	mTRIGGER_LEVELSPERIOD[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],TRIGL|TRIGR
int _MRQ_model::getTRIGGER_LEVELSPERIOD( byte val0
,MRQ_TRIGGER_LEVELSTATE val1, f32 * val2, bool bQuery )
{
	//! 61 21
	int ret = 0;

	f32 lval0 = 0;
	*val2 = mTRIGGER_LEVELSPERIOD[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getDRIVER_TYPE( byte val0, MRQ_DRIVER_TYPE * val1, bool bQuery )
{
	//! 62 0
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDRIVER_TYPE[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],R0|R1|R2
int _MRQ_model::getDRIVER_STATEREG( byte val0
,MRQ_DRIVER_STATEREG val1, uint32 * val2, bool bQuery )
{
	//! 62 1
	int ret = 0;

	uint32 lval0 = 0;
	*val2 = mDRIVER_STATEREG[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,U8
//! [CHANNUM]
int _MRQ_model::setDRIVER_CURRENT( byte val0
,byte val1 )
{
	//! 62 2
	int ret=0; 
	mDRIVER_CURRENT[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getDRIVER_CURRENT( byte val0, byte * val1, bool bQuery )
{
	//! 62 3
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDRIVER_CURRENT[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],256|128|64|32|16|8|4|2|1
int _MRQ_model::setDRIVER_MICROSTEPS( byte val0
,MRQ_DRIVER_MICROSTEPS val1 )
{
	//! 62 4
	int ret=0; 
	mDRIVER_MICROSTEPS[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getDRIVER_MICROSTEPS( byte val0, MRQ_DRIVER_MICROSTEPS * val1, bool bQuery )
{
	//! 62 5
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDRIVER_MICROSTEPS[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],OFF|ON
int _MRQ_model::setDRIVER_STATE( byte val0
,MRQ_CAN_NETMANAGELED val1 )
{
	//! 62 6
	int ret=0; 
	mDRIVER_STATE[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getDRIVER_STATE( byte val0, MRQ_CAN_NETMANAGELED * val1, bool bQuery )
{
	//! 62 7
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDRIVER_STATE[ (int)val0 ];
	return 0;
}
//! U8,ENUM,S8
//! [CHANNUM],UPLIMIT|DOWNLIMIT
int _MRQ_model::setDRIVER_SGLIMIT( byte val0
,MRQ_DRIVER_SGLIMIT val1
,int8 val2 )
{
	//! 62 8
	int ret=0; 
	mDRIVER_SGLIMIT[ (int)val0 ] = val1;
	mDRIVER_SGLIMIT1[ (int)val0 ] = val2;

	return ret;
}
//! U8
//! [CHANNUM],UPLIMIT|DOWNLIMIT
int _MRQ_model::getDRIVER_SGLIMIT( byte val0, MRQ_DRIVER_SGLIMIT * val1, int8 * val2, bool bQuery )
{
	//! 62 9
	int ret = 0;

	byte lval0 = 0;
	int8 lval1 = 0;
	*val1 = mDRIVER_SGLIMIT[ (int)val0 ];
	*val2 = mDRIVER_SGLIMIT1[ (int)val0 ];
	return 0;
}
//! U8,ENUM,S16
//! [CHANNUM],SG0|SGT|SEMAX|SEMIN
int _MRQ_model::setDRIVER_SGPARASET( byte val0
,MRQ_DRIVER_SGPARASET val1
,int16 val2 )
{
	//! 62 10
	int ret=0; 
	mDRIVER_SGPARASET[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],SG0|SGT|SEMAX|SEMIN
int _MRQ_model::getDRIVER_SGPARASET( byte val0
,MRQ_DRIVER_SGPARASET val1, int16 * val2, bool bQuery )
{
	//! 62 11
	int ret = 0;

	int16 lval0 = 0;
	*val2 = mDRIVER_SGPARASET[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! U8,U8
//! [CHANNUM]
int _MRQ_model::setDRIVER_IDLECURRENT( byte val0
,byte val1 )
{
	//! 62 12
	int ret=0; 
	mDRIVER_IDLECURRENT[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getDRIVER_IDLECURRENT( byte val0, byte * val1, bool bQuery )
{
	//! 62 13
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDRIVER_IDLECURRENT[ (int)val0 ];
	return 0;
}
//! U8,U32
//! [CHANNUM]
int _MRQ_model::setDRIVER_SWITCHTIME( byte val0
,uint32 val1 )
{
	//! 62 14
	int ret=0; 
	mDRIVER_SWITCHTIME[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getDRIVER_SWITCHTIME( byte val0, uint32 * val1, bool bQuery )
{
	//! 62 15
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mDRIVER_SWITCHTIME[ (int)val0 ];
	return 0;
}
//! U8,ENUM
//! [CHANNUM],1/2|1/4
int _MRQ_model::setDRIVER_MINICURRRATIO( byte val0
,MRQ_DRIVER_MINICURRRATIO val1 )
{
	//! 62 16
	int ret=0; 
	mDRIVER_MINICURRRATIO[ (int)val0 ] = val1;

	return ret;
}
//! U8
//! [CHANNUM]
int _MRQ_model::getDRIVER_MINICURRRATIO( byte val0, MRQ_DRIVER_MINICURRRATIO * val1, bool bQuery )
{
	//! 62 17
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDRIVER_MINICURRRATIO[ (int)val0 ];
	return 0;
}
//! U8,ENUM,U32
//! [CHANNUM],DRVCTRL|CHOPCONF|SMARTEN|SGCSCONF|DRVCONF
int _MRQ_model::setDRIVER_REGCONFIG( byte val0
,MRQ_DRIVER_REGCONFIG val1
,uint32 val2 )
{
	//! 62 18
	int ret=0; 
	mDRIVER_REGCONFIG[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! U8,ENUM
//! [CHANNUM],DRVCTRL|CHOPCONF|SMARTEN|SGCSCONF|DRVCONF
int _MRQ_model::getDRIVER_REGCONFIG( byte val0
,MRQ_DRIVER_REGCONFIG val1, uint32 * val2, bool bQuery )
{
	//! 62 19
	int ret = 0;

	uint32 lval0 = 0;
	*val2 = mDRIVER_REGCONFIG[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! ENUM,ENUM
//! DO1|DO2|DO3|DO4,DISABLE|ENABLE
int _MRQ_model::setDIGITALOUTPUT_STATE( MRQ_DIGITALOUTPUT_STATE val0
,MRQ_DIGITALOUTPUT_STATE_1 val1 )
{
	//! 63 0
	int ret=0; 
	mDIGITALOUTPUT_STATE[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! DO1|DO2|DO3|DO4
int _MRQ_model::getDIGITALOUTPUT_STATE( MRQ_DIGITALOUTPUT_STATE val0, MRQ_DIGITALOUTPUT_STATE_1 * val1, bool bQuery )
{
	//! 63 1
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDIGITALOUTPUT_STATE[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! DO1|DO2|DO3|DO4,LEVEL|NONE
int _MRQ_model::setDIGITALOUTPUT_SIGNAL( MRQ_DIGITALOUTPUT_STATE val0
,MRQ_DIGITALOUTPUT_SIGNAL_1 val1 )
{
	//! 63 2
	int ret=0; 
	mDIGITALOUTPUT_SIGNAL[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! DO1|DO2|DO3|DO4
int _MRQ_model::getDIGITALOUTPUT_SIGNAL( MRQ_DIGITALOUTPUT_STATE val0, MRQ_DIGITALOUTPUT_SIGNAL_1 * val1, bool bQuery )
{
	//! 63 3
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDIGITALOUTPUT_SIGNAL[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! DO1|DO2|DO3|DO4,POSITIVE|NEGATIVE
int _MRQ_model::setDIGITALOUTPUT_POLARITY( MRQ_DIGITALOUTPUT_STATE val0
,MRQ_DIGITALOUTPUT_POLARITY_1 val1 )
{
	//! 63 4
	int ret=0; 
	mDIGITALOUTPUT_POLARITY[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! DO1|DO2|DO3|DO4
int _MRQ_model::getDIGITALOUTPUT_POLARITY( MRQ_DIGITALOUTPUT_STATE val0, MRQ_DIGITALOUTPUT_POLARITY_1 * val1, bool bQuery )
{
	//! 63 5
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDIGITALOUTPUT_POLARITY[ (int)val0 ];
	return 0;
}
//! ENUM,U8
//! DO1|DO2|DO3|DO4,[CHANNUM]
int _MRQ_model::setDIGITALOUTPUT_SOURCE( MRQ_DIGITALOUTPUT_STATE val0
,byte val1 )
{
	//! 63 6
	int ret=0; 
	mDIGITALOUTPUT_SOURCE[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! DO1|DO2|DO3|DO4
int _MRQ_model::getDIGITALOUTPUT_SOURCE( MRQ_DIGITALOUTPUT_STATE val0, byte * val1, bool bQuery )
{
	//! 63 7
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDIGITALOUTPUT_SOURCE[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! DO1|DO2|DO3|DO4,AUTO|NONE
int _MRQ_model::setDIGITALOUTPUT_CONDITION( MRQ_DIGITALOUTPUT_STATE val0
,MRQ_DIGITALOUTPUT_CONDITION_1 val1 )
{
	//! 63 8
	int ret=0; 
	mDIGITALOUTPUT_CONDITION[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! DO1|DO2|DO3|DO4
int _MRQ_model::getDIGITALOUTPUT_CONDITION( MRQ_DIGITALOUTPUT_STATE val0, MRQ_DIGITALOUTPUT_CONDITION_1 * val1, bool bQuery )
{
	//! 63 9
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDIGITALOUTPUT_CONDITION[ (int)val0 ];
	return 0;
}
//! ENUM,U32
//! DO1|DO2|DO3|DO4
int _MRQ_model::setDIGITALOUTPUT_PERIOD( MRQ_DIGITALOUTPUT_STATE val0
,uint32 val1 )
{
	//! 63 10
	int ret=0; 
	mDIGITALOUTPUT_PERIOD[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! DO1|DO2|DO3|DO4
int _MRQ_model::getDIGITALOUTPUT_PERIOD( MRQ_DIGITALOUTPUT_STATE val0, uint32 * val1, bool bQuery )
{
	//! 63 11
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mDIGITALOUTPUT_PERIOD[ (int)val0 ];
	return 0;
}
//! ENUM,U16
//! DO1|DO2|DO3|DO4
int _MRQ_model::setDIGITALOUTPUT_DUTY( MRQ_DIGITALOUTPUT_STATE val0
,uint16 val1 )
{
	//! 63 12
	int ret=0; 
	mDIGITALOUTPUT_DUTY[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! DO1|DO2|DO3|DO4
int _MRQ_model::getDIGITALOUTPUT_DUTY( MRQ_DIGITALOUTPUT_STATE val0, uint16 * val1, bool bQuery )
{
	//! 63 13
	int ret = 0;

	uint16 lval0 = 0;
	*val1 = mDIGITALOUTPUT_DUTY[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! YO1|YO2,DISABLE|ENABLE
int _MRQ_model::setISOLATOROUTPUT_STATE( MRQ_ISOLATOROUTPUT_STATE val0
,MRQ_DIGITALOUTPUT_STATE_1 val1 )
{
	//! 64 0
	int ret=0; 
	mISOLATOROUTPUT_STATE[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! YO1|YO2
int _MRQ_model::getISOLATOROUTPUT_STATE( MRQ_ISOLATOROUTPUT_STATE val0, MRQ_DIGITALOUTPUT_STATE_1 * val1, bool bQuery )
{
	//! 64 1
	int ret = 0;

	byte lval0 = 0;
	*val1 = mISOLATOROUTPUT_STATE[ (int)val0 ];
	return 0;
}
//! ENUM,U8
//! YO1|YO2,[CHANNUM]
int _MRQ_model::setISOLATOROUTPUT_SOURCE( MRQ_ISOLATOROUTPUT_STATE val0
,byte val1 )
{
	//! 64 2
	int ret=0; 
	mISOLATOROUTPUT_SOURCE[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! YO1|YO2
int _MRQ_model::getISOLATOROUTPUT_SOURCE( MRQ_ISOLATOROUTPUT_STATE val0, byte * val1, bool bQuery )
{
	//! 64 3
	int ret = 0;

	byte lval0 = 0;
	*val1 = mISOLATOROUTPUT_SOURCE[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! YO1|YO2,AUTO|NONE
int _MRQ_model::setISOLATOROUTPUT_CONDITION( MRQ_ISOLATOROUTPUT_STATE val0
,MRQ_DIGITALOUTPUT_CONDITION_1 val1 )
{
	//! 64 4
	int ret=0; 
	mISOLATOROUTPUT_CONDITION[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! YO1|YO2
int _MRQ_model::getISOLATOROUTPUT_CONDITION( MRQ_ISOLATOROUTPUT_STATE val0, MRQ_DIGITALOUTPUT_CONDITION_1 * val1, bool bQuery )
{
	//! 64 5
	int ret = 0;

	byte lval0 = 0;
	*val1 = mISOLATOROUTPUT_CONDITION[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! YO1|YO2,TURNON|CUTOFF
int _MRQ_model::setISOLATOROUTPUT_RESPONSE( MRQ_ISOLATOROUTPUT_STATE val0
,MRQ_ISOLATOROUTPUT_RESPONSE_1 val1 )
{
	//! 64 6
	int ret=0; 
	mISOLATOROUTPUT_RESPONSE[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! YO1|YO2
int _MRQ_model::getISOLATOROUTPUT_RESPONSE( MRQ_ISOLATOROUTPUT_STATE val0, MRQ_ISOLATOROUTPUT_RESPONSE_1 * val1, bool bQuery )
{
	//! 64 7
	int ret = 0;

	byte lval0 = 0;
	*val1 = mISOLATOROUTPUT_RESPONSE[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! UART1|UART2,4800|7200|9600|14400|19200|38400|57600|115200|128000|2000000|2500000
int _MRQ_model::setSENSORUART_BAUD( MRQ_SENSORUART_BAUD val0
,MRQ_SENSORUART_BAUD_1 val1 )
{
	//! 65 0
	int ret=0; 
	mSENSORUART_BAUD[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! UART1|UART2
int _MRQ_model::getSENSORUART_BAUD( MRQ_SENSORUART_BAUD val0, MRQ_SENSORUART_BAUD_1 * val1, bool bQuery )
{
	//! 65 1
	int ret = 0;

	byte lval0 = 0;
	*val1 = mSENSORUART_BAUD[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! UART1|UART2,8|9
int _MRQ_model::setSENSORUART_WORDLEN( MRQ_SENSORUART_BAUD val0
,MRQ_RS232_WORDLEN val1 )
{
	//! 65 2
	int ret=0; 
	mSENSORUART_WORDLEN[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! UART1|UART2
int _MRQ_model::getSENSORUART_WORDLEN( MRQ_SENSORUART_BAUD val0, MRQ_RS232_WORDLEN * val1, bool bQuery )
{
	//! 65 3
	int ret = 0;

	byte lval0 = 0;
	*val1 = mSENSORUART_WORDLEN[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! UART1|UART2,NONE|RTS|CTS|RTS&CTS
int _MRQ_model::setSENSORUART_FLOWCTL( MRQ_SENSORUART_BAUD val0
,MRQ_RS232_FLOWCTL val1 )
{
	//! 65 4
	int ret=0; 
	mSENSORUART_FLOWCTL[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! UART1|UART2
int _MRQ_model::getSENSORUART_FLOWCTL( MRQ_SENSORUART_BAUD val0, MRQ_RS232_FLOWCTL * val1, bool bQuery )
{
	//! 65 5
	int ret = 0;

	byte lval0 = 0;
	*val1 = mSENSORUART_FLOWCTL[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! UART1|UART2,NONE|EVEN|ODD
int _MRQ_model::setSENSORUART_PARITY( MRQ_SENSORUART_BAUD val0
,MRQ_RS232_PARITY val1 )
{
	//! 65 6
	int ret=0; 
	mSENSORUART_PARITY[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! UART1|UART2
int _MRQ_model::getSENSORUART_PARITY( MRQ_SENSORUART_BAUD val0, MRQ_RS232_PARITY * val1, bool bQuery )
{
	//! 65 7
	int ret = 0;

	byte lval0 = 0;
	*val1 = mSENSORUART_PARITY[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! UART1|UART2,1|0.5|2|1.5
int _MRQ_model::setSENSORUART_STOPBIT( MRQ_SENSORUART_BAUD val0
,MRQ_RS232_STOPBIT val1 )
{
	//! 65 8
	int ret=0; 
	mSENSORUART_STOPBIT[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! UART1|UART2
int _MRQ_model::getSENSORUART_STOPBIT( MRQ_SENSORUART_BAUD val0, MRQ_RS232_STOPBIT * val1, bool bQuery )
{
	//! 65 9
	int ret = 0;

	byte lval0 = 0;
	*val1 = mSENSORUART_STOPBIT[ (int)val0 ];
	return 0;
}
//! ENUM
//! UART1|UART2
int _MRQ_model::setSENSORUART_APPLYPARA( MRQ_SENSORUART_BAUD val0 )
{
	//! 65 10
	int ret=0; 

	return ret;
}
//! ENUM,ENUM,ENUM
//! UART1|UART2,S1|S2|S3|S4,OFF|ON
int _MRQ_model::setSENSORUART_STATE( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1
,MRQ_CAN_NETMANAGELED val2 )
{
	//! 65 11
	int ret=0; 
	mSENSORUART_STATE[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! ENUM,ENUM
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::getSENSORUART_STATE( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1, MRQ_CAN_NETMANAGELED * val2, bool bQuery )
{
	//! 65 12
	int ret = 0;

	byte lval0 = 0;
	*val2 = mSENSORUART_STATE[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! ENUM,ENUM,U8
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::setSENSORUART_SOF( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1
,byte val2 )
{
	//! 65 13
	int ret=0; 
	mSENSORUART_SOF[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! ENUM,ENUM
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::getSENSORUART_SOF( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1, byte * val2, bool bQuery )
{
	//! 65 14
	int ret = 0;

	byte lval0 = 0;
	*val2 = mSENSORUART_SOF[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! ENUM,ENUM,U8
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::setSENSORUART_FRAMELEN( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1
,byte val2 )
{
	//! 65 15
	int ret=0; 
	mSENSORUART_FRAMELEN[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! ENUM,ENUM
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::getSENSORUART_FRAMELEN( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1, byte * val2, bool bQuery )
{
	//! 65 16
	int ret = 0;

	byte lval0 = 0;
	*val2 = mSENSORUART_FRAMELEN[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! ENUM,ENUM,U8
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::setSENSORUART_RECEIVENUM( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1
,byte val2 )
{
	//! 65 17
	int ret=0; 
	mSENSORUART_RECEIVENUM[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! ENUM,ENUM
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::getSENSORUART_RECEIVENUM( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1, byte * val2, bool bQuery )
{
	//! 65 18
	int ret = 0;

	byte lval0 = 0;
	*val2 = mSENSORUART_RECEIVENUM[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! ENUM,ENUM,U32
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::setSENSORUART_SWITCHTIME( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1
,uint32 val2 )
{
	//! 65 19
	int ret=0; 
	mSENSORUART_SWITCHTIME[ (int)val0 ][ (int)val1 ] = val2;

	return ret;
}
//! ENUM,ENUM
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::getSENSORUART_SWITCHTIME( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1, uint32 * val2, bool bQuery )
{
	//! 65 20
	int ret = 0;

	uint32 lval0 = 0;
	*val2 = mSENSORUART_SWITCHTIME[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! ENUM,ENUM
//! UART1|UART2,S1|S2|S3|S4
int _MRQ_model::getSENSORUART_DATA( MRQ_SENSORUART_BAUD val0
,MRQ_IDENTITY_LABEL_1 val1, byte * val2, char * val3, char * val4, char * val5, bool bQuery )
{
	//! 65 21
	int ret = 0;

	byte lval0 = 0;
	byte lval1 = 0;
	byte lval2 = 0;
	byte lval3 = 0;
	*val2 = mSENSORUART_DATA[ (int)val0 ][ (int)val1 ];
	*val3 = mSENSORUART_DATA1[ (int)val0 ][ (int)val1 ];
	*val4 = mSENSORUART_DATA2[ (int)val0 ][ (int)val1 ];
	*val5 = mSENSORUART_DATA3[ (int)val0 ][ (int)val1 ];
	return 0;
}
//! ENUM
//! OFF|ON
int _MRQ_model::setISOLATORIN_STATE( MRQ_CAN_NETMANAGELED val0 )
{
	//! 72 0
	int ret=0; 
	mISOLATORIN_STATE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getISOLATORIN_STATE(  MRQ_CAN_NETMANAGELED * val0, bool bQuery )
{
	//! 72 1
	int ret = 0;

	byte lval0 = 0;
	*val0 = mISOLATORIN_STATE;
	return 0;
}
//! ENUM
//! RESERVE|LOW|RISE|FALL|HIGH
int _MRQ_model::setISOLATORIN_TYPE( MRQ_TRIGGER_LEVELTYPE_1 val0 )
{
	//! 72 2
	int ret=0; 
	mISOLATORIN_TYPE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getISOLATORIN_TYPE(  MRQ_TRIGGER_LEVELTYPE_1 * val0, bool bQuery )
{
	//! 72 3
	int ret = 0;

	byte lval0 = 0;
	*val0 = mISOLATORIN_TYPE;
	return 0;
}
//! ENUM
//! NONE|ALARM|STOP|ALARM&STOP
int _MRQ_model::setISOLATORIN_RESPONSE( MRQ_MOTIONPLAN_OOSLINERESPONSE_1 val0 )
{
	//! 72 4
	int ret=0; 
	mISOLATORIN_RESPONSE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getISOLATORIN_RESPONSE(  MRQ_MOTIONPLAN_OOSLINERESPONSE_1 * val0, bool bQuery )
{
	//! 72 5
	int ret = 0;

	byte lval0 = 0;
	*val0 = mISOLATORIN_RESPONSE;
	return 0;
}
//! U8
//! [CHANNUM]
int _MRQ_model::setISOLATORIN_RESPCHAN( byte val0 )
{
	//! 72 6
	int ret=0; 
	mISOLATORIN_RESPCHAN = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getISOLATORIN_RESPCHAN(  byte * val0, bool bQuery )
{
	//! 72 7
	int ret = 0;

	byte lval0 = 0;
	*val0 = mISOLATORIN_RESPCHAN;
	return 0;
}
//! ENUM
//! CONTINUED|INTERVAL|SINGLE
int _MRQ_model::setISOLATORIN_SMODE( MRQ_TRIGGER_PATTSMODE val0 )
{
	//! 72 8
	int ret=0; 
	mISOLATORIN_SMODE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getISOLATORIN_SMODE(  MRQ_TRIGGER_PATTSMODE * val0, bool bQuery )
{
	//! 72 9
	int ret = 0;

	byte lval0 = 0;
	*val0 = mISOLATORIN_SMODE;
	return 0;
}
//! U32
//! 
int _MRQ_model::setISOLATORIN_SPERIOD( uint32 val0 )
{
	//! 72 10
	int ret=0; 
	mISOLATORIN_SPERIOD = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getISOLATORIN_SPERIOD(  uint32 * val0, bool bQuery )
{
	//! 72 11
	int ret = 0;

	uint32 lval0 = 0;
	*val0 = mISOLATORIN_SPERIOD;
	return 0;
}
//! ENUM,ENUM
//! S1|S2|S3|S4,OFF|ON
int _MRQ_model::setABSENCALARM_STATE( MRQ_IDENTITY_LABEL_1 val0
,MRQ_CAN_NETMANAGELED val1 )
{
	//! 73 0
	int ret=0; 
	mABSENCALARM_STATE[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getABSENCALARM_STATE( MRQ_IDENTITY_LABEL_1 val0, MRQ_CAN_NETMANAGELED * val1, bool bQuery )
{
	//! 73 1
	int ret = 0;

	byte lval0 = 0;
	*val1 = mABSENCALARM_STATE[ (int)val0 ];
	return 0;
}
//! ENUM,U32
//! S1|S2|S3|S4
int _MRQ_model::setABSENCALARM_UPLIMIT( MRQ_IDENTITY_LABEL_1 val0
,uint32 val1 )
{
	//! 73 2
	int ret=0; 
	mABSENCALARM_UPLIMIT[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getABSENCALARM_UPLIMIT( MRQ_IDENTITY_LABEL_1 val0, uint32 * val1, bool bQuery )
{
	//! 73 3
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mABSENCALARM_UPLIMIT[ (int)val0 ];
	return 0;
}
//! ENUM,U32
//! S1|S2|S3|S4
int _MRQ_model::setABSENCALARM_DOWNLIMIT( MRQ_IDENTITY_LABEL_1 val0
,uint32 val1 )
{
	//! 73 4
	int ret=0; 
	mABSENCALARM_DOWNLIMIT[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getABSENCALARM_DOWNLIMIT( MRQ_IDENTITY_LABEL_1 val0, uint32 * val1, bool bQuery )
{
	//! 73 5
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mABSENCALARM_DOWNLIMIT[ (int)val0 ];
	return 0;
}
//! ENUM,U32
//! S1|S2|S3|S4
int _MRQ_model::setABSENCALARM_ZEROVALUE( MRQ_IDENTITY_LABEL_1 val0
,uint32 val1 )
{
	//! 73 6
	int ret=0; 
	mABSENCALARM_ZEROVALUE[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getABSENCALARM_ZEROVALUE( MRQ_IDENTITY_LABEL_1 val0, uint32 * val1, bool bQuery )
{
	//! 73 7
	int ret = 0;

	uint32 lval0 = 0;
	*val1 = mABSENCALARM_ZEROVALUE[ (int)val0 ];
	return 0;
}
//! ENUM,ENUM
//! S1|S2|S3|S4,NONE|EXIS
int _MRQ_model::setABSENCALARM_ZEROPOSITION( MRQ_IDENTITY_LABEL_1 val0
,MRQ_ABSENCALARM_ZEROPOSITION_1 val1 )
{
	//! 73 8
	int ret=0; 
	mABSENCALARM_ZEROPOSITION[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getABSENCALARM_ZEROPOSITION( MRQ_IDENTITY_LABEL_1 val0, MRQ_ABSENCALARM_ZEROPOSITION_1 * val1, bool bQuery )
{
	//! 73 9
	int ret = 0;

	byte lval0 = 0;
	*val1 = mABSENCALARM_ZEROPOSITION[ (int)val0 ];
	return 0;
}
//! ENUM
//! NONE|ALARM|STOP|ALARM&STOP
int _MRQ_model::setABSENCALARM_RESPONSE( MRQ_MOTIONPLAN_OOSLINERESPONSE_1 val0 )
{
	//! 73 10
	int ret=0; 
	mABSENCALARM_RESPONSE = val0;

	return ret;
}
//! 
//! 
int _MRQ_model::getABSENCALARM_RESPONSE(  MRQ_MOTIONPLAN_OOSLINERESPONSE_1 * val0, bool bQuery )
{
	//! 73 11
	int ret = 0;

	byte lval0 = 0;
	*val0 = mABSENCALARM_RESPONSE;
	return 0;
}
//! ENUM,ENUM
//! S1|S2|S3|S4,OFF|ON
int _MRQ_model::setDISTANCEALARM_STATE( MRQ_IDENTITY_LABEL_1 val0
,MRQ_CAN_NETMANAGELED val1 )
{
	//! 74 0
	int ret=0; 
	mDISTANCEALARM_STATE[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getDISTANCEALARM_STATE( MRQ_IDENTITY_LABEL_1 val0, MRQ_CAN_NETMANAGELED * val1, bool bQuery )
{
	//! 74 1
	int ret = 0;

	byte lval0 = 0;
	*val1 = mDISTANCEALARM_STATE[ (int)val0 ];
	return 0;
}
//! ENUM,U16
//! S1|S2|S3|S4
int _MRQ_model::setDISTANCEALARM_ALARM1DIST( MRQ_IDENTITY_LABEL_1 val0
,uint16 val1 )
{
	//! 74 2
	int ret=0; 
	mDISTANCEALARM_ALARM1DIST[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getDISTANCEALARM_ALARM1DIST( MRQ_IDENTITY_LABEL_1 val0, uint16 * val1, bool bQuery )
{
	//! 74 3
	int ret = 0;

	uint16 lval0 = 0;
	*val1 = mDISTANCEALARM_ALARM1DIST[ (int)val0 ];
	return 0;
}
//! ENUM,U16
//! S1|S2|S3|S4
int _MRQ_model::setDISTANCEALARM_ALARM2DIST( MRQ_IDENTITY_LABEL_1 val0
,uint16 val1 )
{
	//! 74 4
	int ret=0; 
	mDISTANCEALARM_ALARM2DIST[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getDISTANCEALARM_ALARM2DIST( MRQ_IDENTITY_LABEL_1 val0, uint16 * val1, bool bQuery )
{
	//! 74 5
	int ret = 0;

	uint16 lval0 = 0;
	*val1 = mDISTANCEALARM_ALARM2DIST[ (int)val0 ];
	return 0;
}
//! ENUM,U16
//! S1|S2|S3|S4
int _MRQ_model::setDISTANCEALARM_ALARM3DIST( MRQ_IDENTITY_LABEL_1 val0
,uint16 val1 )
{
	//! 74 6
	int ret=0; 
	mDISTANCEALARM_ALARM3DIST[ (int)val0 ] = val1;

	return ret;
}
//! ENUM
//! S1|S2|S3|S4
int _MRQ_model::getDISTANCEALARM_ALARM3DIST( MRQ_IDENTITY_LABEL_1 val0, uint16 * val1, bool bQuery )
{
	//! 74 7
	int ret = 0;

	uint16 lval0 = 0;
	*val1 = mDISTANCEALARM_ALARM3DIST[ (int)val0 ];
	return 0;
}
}
