#include <QtCore>

#include "scpi/scpi.h"

#include "injectpump.h"
#include "../../com/comassist.h"

#define DEF_ROBO()      robotInject *pRobo;\
                        pRobo = ((robotInject*)context->user_context);\
                        Q_ASSERT( NULL != pRobo );

#define LOCAL_ROBO()    pRobo

#define CHECK_LINK()    if ( pRobo->checkLink() ) \
                        {}\
                        else\
                        { scpi_ret( SCPI_RES_ERR ); }

static scpi_result_t _scpi_idn( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    logDbg();

    QString str;

    DEF_ROBO();
    str = LOCAL_ROBO()->getName();

    logDbg()<<str;
    SCPI_ResultText( context, str.toLatin1().data() );

    return SCPI_RES_OK;
}

//! page
static scpi_result_t _scpi_run( scpi_t * context )
{
    DEF_LOCAL_VAR();
    DEF_ROBO();

    CHECK_LINK();

    LOCAL_ROBO()->run();logDbg();

    return SCPI_RES_OK;
}

//! move ch, page
//! x1,y1, x2,y2,
//! t
static scpi_result_t _scpi_move( scpi_t * context )
{
    DEF_LOCAL_VAR();

    int ax, page;
    float vals[4+1];

    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }
    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    for ( int i = 0; i < sizeof_array(vals); i++ )
    {
        if ( SCPI_RES_OK != SCPI_ParamFloat( context, vals+i, true ) )
        { scpi_ret( SCPI_RES_ERR ); }
    }

    for ( int i = 0; i < sizeof_array(vals); i++ )
    { logDbg()<<vals[i]; }

    //! robo op
    DEF_ROBO();

    CHECK_LINK();

    IPKeyPoint pt1( 0,
                          vals[0], vals[1], 0,0
                            );
    IPKeyPoint pt2( vals[4],
                          vals[2], vals[3], 0,0
                        );

    IPKeyPointList curve;
    curve.append( pt1 );
    curve.append( pt2 );

    if ( 0 != LOCAL_ROBO()->move( curve, tpvRegion(ax,page) ) )
    { scpi_ret( SCPI_RES_ERR ); }

    return SCPI_RES_OK;
}


//! move ch, page
//! x1,y1, x2,y2,
//! t
static scpi_result_t _scpi_preMove( scpi_t * context )
{
    DEF_LOCAL_VAR();

    int ax, page;
    float vals[4+1];

    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }
    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    for ( int i = 0; i < sizeof_array(vals); i++ )
    {
        if ( SCPI_RES_OK != SCPI_ParamFloat( context, vals+i, true ) )
        { scpi_ret( SCPI_RES_ERR ); }
    }

    for ( int i = 0; i < sizeof_array(vals); i++ )
    { logDbg()<<vals[i]; }

    //! robo op
    DEF_ROBO();

    CHECK_LINK();

    IPKeyPoint pt1( 0,
                          vals[0], vals[1], 0,0
                            );
    IPKeyPoint pt2( vals[4],
                          vals[2], vals[3], 0,0
                        );

    IPKeyPointList curve;
    curve.append( pt1 );
    curve.append( pt2 );

    LOCAL_ROBO()->preMove( curve, tpvRegion(ax,page) );

    return SCPI_RES_OK;
}

//! page, file
static scpi_result_t _scpi_program( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    int ax, page;

    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    if ( SCPI_ParamCharacters(context, &pLocalStr, &strLen, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }logDbg()<<strLen<<pLocalStr;
    if (strLen < 1)
    { scpi_ret( SCPI_RES_ERR ); }

    //! t, x1,y1,vx,vy
    QList<float> dataset;
    int col = 5;
    QList<int> dataCols;
    dataCols<<0<<1<<2<<3;
    if ( 0 != comAssist::loadDataset( pLocalStr, strLen, col, dataCols, dataset ) )
    {  scpi_ret( SCPI_RES_ERR ); }

    //! point
    if ( dataset.size() / col < 2 )
    { scpi_ret( SCPI_RES_ERR ); }

    IPKeyPointList curve;
    IPKeyPoint tp;
    for ( int i = 0; i < dataset.size()/col; i++ )
    {
        //! t
        tp.datas[0] = dataset.at( i * col );

        //! xyv
        for ( int j = 1; j < col; j++ )
        {
            tp.datas[j] = dataset.at( i * col + j );
        }

        curve.append( tp );
    }

    //! robo op
    DEF_ROBO();

    CHECK_LINK();

    int ret = LOCAL_ROBO()->program( curve, tpvRegion(ax,page) );

    return SCPI_RES_OK;
}

//! ax, page
static scpi_result_t _scpi_call( scpi_t * context )
{
    // read
    DEF_LOCAL_VAR();

    int ax, page;

    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    //! robo op
    DEF_ROBO();

    CHECK_LINK();

    LOCAL_ROBO()->call( tpvRegion( ax, page) );

    return SCPI_RES_OK;
}

//! ax, page
static scpi_result_t _scpi_fsmState( scpi_t * context )
{
    DEF_LOCAL_VAR();
    DEF_ROBO();

    int ax, page;
    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    int ret = LOCAL_ROBO()->state( tpvRegion(ax,page) );

    SCPI_ResultInt32( context, ret );

    return SCPI_RES_OK;
}

//! int ax, page, jointid
static scpi_result_t _scpi_gozero( scpi_t * context )
{
    DEF_LOCAL_VAR();
    DEF_ROBO();

    CHECK_LINK();

    //! ax, page
    int ax, page;
    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    //! robo
    int joint;
    if ( SCPI_ParamInt32(context, &joint, true) != true )
    {logDbg();
        LOCAL_ROBO()->goZero( tpvRegion(ax,page) );
    }
    //! some joint
    else
    {logDbg();
        LOCAL_ROBO()->goZero( tpvRegion(ax,page), joint, true );
    }

    return SCPI_RES_OK;
}

//! int ax, page
//! float dh, float dt
static scpi_result_t _scpi_line( scpi_t * context )
{
    DEF_LOCAL_VAR();
    DEF_ROBO();

    CHECK_LINK();

    //! ax, page
    int ax, page;
    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    float vals[2];
    for ( int i = 0; i < sizeof_array(vals); i++ )
    {
        if ( SCPI_RES_OK != SCPI_ParamFloat( context, vals+i, true ) )
        { scpi_ret( SCPI_RES_ERR ); }
    }

    if ( 0 != LOCAL_ROBO()->inj_move( tpvRegion(ax,page), vals[0], vals[1] ) )
    { scpi_ret( SCPI_RES_ERR ); }

    return SCPI_RES_OK;
}

//! int ax, page
//! float dv, float dt
static scpi_result_t _scpi_rotate( scpi_t * context )
{
    DEF_LOCAL_VAR();
    DEF_ROBO();

    CHECK_LINK();

    //! ax, page
    int ax, page;
    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    float vals[2];
    for ( int i = 0; i < sizeof_array(vals); i++ )
    {
        if ( SCPI_RES_OK != SCPI_ParamFloat( context, vals+i, true ) )
        { scpi_ret( SCPI_RES_ERR ); }
    }

    if ( 0 != LOCAL_ROBO()->valve_move( tpvRegion(ax,page), vals[0], vals[1] ) )
    { scpi_ret( SCPI_RES_ERR ); }

    return SCPI_RES_OK;
}

//! int ax page
//! float dh, dt
static scpi_result_t _scpi_purge( scpi_t * context )
{
    DEF_LOCAL_VAR();
    DEF_ROBO();

    CHECK_LINK();

    //! ax, page
    int ax, page;
    if ( SCPI_ParamInt32(context, &ax, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    if ( SCPI_ParamInt32(context, &page, true) != true )
    { scpi_ret( SCPI_RES_ERR ); }

    float vals[2];
    for ( int i = 0; i < sizeof_array(vals); i++ )
    {
        if ( SCPI_RES_OK != SCPI_ParamFloat( context, vals+i, true ) )
        { scpi_ret( SCPI_RES_ERR ); }
    }

    //! move
    IPKeyPointList curve;

    IPKeyPoint kp;

    //! p0
    kp.t = 0;
    kp.x = 0;
    kp.y = 0;
    curve.append( kp );

    //! p1
    kp.t = 1 * vals[1];
    kp.x = 0;
    kp.y = vals[0];
    curve.append( kp );

    //! p2
    kp.t = 2 * vals[1];
    kp.x = 0;
    kp.y = 0;
    curve.append( kp );

    if ( 0 != LOCAL_ROBO()->move( curve, tpvRegion(ax,page) ) )
    { scpi_ret( SCPI_RES_ERR ); }

    return SCPI_RES_OK;
}

static scpi_command_t _scpi_cmds[]=
{

    CMD_ITEM( "*IDN?", _scpi_idn ),
    CMD_ITEM( "RUN",  _scpi_run ),

    CMD_ITEM( "MOVE", _scpi_move ),         //! ax,page, v1,i1,v2,i2,t
    CMD_ITEM( "PREMOVE", _scpi_preMove ),   //! ax,page, v1,i1,v2,i2,t


    CMD_ITEM( "STATE?", _scpi_fsmState ),   //! ax,page

    CMD_ITEM( "PROGRAM", _scpi_program ),   //! ax,page,file
                                            //! t,x,y,v

    CMD_ITEM( "CALL", _scpi_call ),         //! ax,page

    CMD_ITEM( "ZERO", _scpi_gozero ),       //! jid
                                            //! or no para

    CMD_ITEM( "LINE", _scpi_line ),
    CMD_ITEM( "ROTATE", _scpi_rotate ),
    CMD_ITEM( "PURGE", _scpi_purge ),       //!

    SCPI_CMD_LIST_END
};

const void* robotInject::loadScpiCmd()
{
    return _scpi_cmds;
}

