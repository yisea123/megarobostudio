#include "scpi/scpi.h"

#include "deviceMRQ.h"
#include "scpi_obj.h"
#include "../_scpi_xxx_device.h"

#include "../board/_MRQ_scpi_callback.cpp"

#include "../../com/comassist.h"

#define DEF_MRQ()   MegaDevice::deviceMRQ* _localMrq = (GET_OBJ(context));
#define LOCALMRQ()  _localMrq

static scpi_result_t _scpi_testAdd( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    int val1, val2, ret;

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &val1, true ) )
    { return SCPI_RES_ERR; }

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &val2, true ) )
    { return SCPI_RES_ERR; }

    ret = ((MegaDevice::deviceMRQ*)context->user_context)->testAdd( val1, val2 );
    SCPI_ResultInt32( context, ret );

    return SCPI_RES_OK;
}

static scpi_result_t _scpi_idn( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    qDebug()<<__FUNCTION__<<__LINE__;

    QString str;

    str = ((MegaDevice::deviceMRQ*)context->user_context)->getModel()->getSN();

    qDebug()<<str<<__FUNCTION__<<__LINE__;
    SCPI_ResultText( context, str.toLatin1().data() );

    return SCPI_RES_OK;
}

//! ax
static scpi_result_t _scpi_run( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    int ax;

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &ax, true ) )
    { return SCPI_RES_ERR; }

    DEF_MRQ();

    LOCALMRQ()->run(ax);

    return SCPI_RES_OK;
}

//! int, float, float
//! ax, t, angle
static scpi_result_t _scpi_rotate( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    int val1;
    float val2, val3;

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &val1, true ) )
    { return SCPI_RES_ERR; }

    if ( SCPI_RES_OK != SCPI_ParamFloat( context, &val2, true ) )
    { return SCPI_RES_ERR; }

    if ( SCPI_RES_OK != SCPI_ParamFloat( context, &val3, true ) )
    { return SCPI_RES_ERR; }

    ((MegaDevice::deviceMRQ*)context->user_context)->rotate( val1, val2, val3 );

    return SCPI_RES_OK;
}

//! CALL ax, page
static scpi_result_t _scpi_call( _scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    int ax, page;

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &ax, true ) )
    { return SCPI_RES_ERR; }

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &page, true ) )
    { return SCPI_RES_ERR; }

    DEF_MRQ();

    LOCALMRQ()->prepare( ax, page );

    return SCPI_RES_OK;
}


//! TPV ax,page,e:/ddd.csv
static scpi_result_t _scpi_tpv( scpi_t * context )
{logDbg();
    // read
    DEF_LOCAL_VAR();

    int ax, page;

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &ax, true ) )
    { return SCPI_RES_ERR; }logDbg()<<ax;

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &page, true ) )
    { return SCPI_RES_ERR; }logDbg()<<page;

    if ( SCPI_ParamCharacters(context, &pLocalStr, &strLen, true) != true )
    { return SCPI_RES_ERR; }logDbg()<<strLen<<pLocalStr;
    if (strLen < 1)
    { return SCPI_RES_ERR; }

    //! load
    QList<float> dataSets;
    int col = 3;
    if ( 0 != comAssist::loadDataset( pLocalStr, strLen, col, dataSets ) )
    { return SCPI_RES_ERR; }

    int dotSize = dataSets.size()/col;
    if ( (dotSize < 2) )
    { return SCPI_RES_ERR; }logDbg()<<dotSize;

    //! t,p,v
    tpvRow *pDots = new tpvRow[ dotSize ];

    if ( NULL == pDots )
    { logDbg(); return SCPI_RES_ERR; }

    //! move data
    for( int i = 0; i < dotSize; i++ )
    {
        for ( int j = 0; j < col; j++ )
        {
            pDots[i].datas[j] = dataSets.at(i*col+j);
            pDots[i].setGc( true );
        }
    }

    //! send
    int ret = -1;
    ret = ((MegaDevice::deviceMRQ*)context->user_context)->tpvWrite( ax, page, pDots, dotSize );

    gc_array( pDots );

    if ( ret != 0 )
    { return SCPI_RES_ERR; }
    else
    { return SCPI_RES_OK; }
}

//! xxx ax
static scpi_result_t _scpi_fsmState( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    int val1, ret;

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &val1, true ) )
    { return SCPI_RES_ERR; }

    ret = ((MegaDevice::deviceMRQ*)context->user_context)->fsmState(  val1 );

    SCPI_ResultInt32( context, ret );

    return SCPI_RES_OK;
}

//! XXX ax
static scpi_result_t _scpi_angle( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    int val1;

    if ( SCPI_RES_OK != SCPI_ParamInt32( context, &val1, true ) )
    { return SCPI_RES_ERR; }

    float val = 0;
    val = ((MegaDevice::deviceMRQ*)context->user_context)->getAngle( val1 );

    SCPI_ResultFloat( context, val );

    return SCPI_RES_OK;
}

static scpi_command_t _mrq_scpi_cmds[]=
{
    #include "../board/_MRQ_scpi_cmd.h"

    CMD_ITEM( "*IDN?", _scpi_idn ),

    CMD_ITEM( "TEST:ADD", _scpi_testAdd ),

    CMD_ITEM( "RUN", _scpi_run ),

    CMD_ITEM( "ROTATE", _scpi_rotate ),

    CMD_ITEM( "STATE?", _scpi_fsmState ),

    CMD_ITEM( "ANGLE?", _scpi_angle ),

    CMD_ITEM( "PROGRAM", _scpi_tpv ),

    CMD_ITEM( "CALL", _scpi_call ),

    SCPI_CMD_LIST_END
};

namespace MegaDevice
{
const void* deviceMRQ::loadScpiCmd()
{
    return _mrq_scpi_cmds;
}
}



