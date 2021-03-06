#include "motionedit.h"

#include "ui_motionedit.h"

#include "../../model/tpvgroup.h"

#include "../../device/mrq/deviceMRQ.h"


motionEdit::motionEdit(QWidget *parent) : tableEdit(parent),
    ui(new Ui::motionEdit)
{
    ui->setupUi(this);

    mDlySaveTime.setInterval( 5000 );
    mDlySaveTime.setSingleShot( true );

    buildConnection();

    mFilePattern<<motion_desc<<motion_ext;

    m_pPlot = NULL;

    m_pActionDelegate = NULL;

    //! debug
    setAgent( "test_2" );
    setLink( true );
}

void motionEdit::buildConnection()
{
    connect( this, SIGNAL(sig_joints_trace_changed()),
             this, SLOT(slot_joints_trace_changed()) );

    connect( &mDlySaveTime, SIGNAL(timeout()),
             this, SLOT(slot_timeout()) );
}

motionEdit::~motionEdit()
{
    delete ui;

    delete_all( mJointsTpvGroup );
}

void motionEdit::setModelObj( mcModelObj *pObj )
{
    Q_ASSERT( NULL != pObj );

    modelView::setModelObj( pObj );

    m_pMotionGroup = (MegaTableModel*)(pObj->getObj());
    Q_ASSERT( NULL != m_pMotionGroup );
    ui->tableView->setModel( m_pMotionGroup );

    //! connect
    connect( m_pMotionGroup, SIGNAL(signal_data_changed()),
             this, SLOT(slot_data_changed()) );

    //! update ui
    QString strRoboName;
    strRoboName = m_pMotionGroup->className();
    VRobot * pRobo = robotFact::createRobot( strRoboName );
    Q_ASSERT( NULL != pRobo );
    QImage img = pRobo->getImage();
    ui->labelIcon->setToolTip( strRoboName );
    ui->labelIcon->setPixmap( QPixmap::fromImage(img) );
    delete pRobo;

    //! step
    ui->labelStep->setVisible( m_pMotionGroup->stepAble() );
    ui->spinStep->setVisible( m_pMotionGroup->stepAble() );
    ui->labelInterp->setVisible( m_pMotionGroup->stepAble() );
    ui->cmbInterp->setVisible( m_pMotionGroup->stepAble() );

    ui->btnPref->setVisible( m_pMotionGroup->prefAble() );

    //! autotime able
    ui->btnAutoTime->setVisible( m_pMotionGroup->autoTimeAble() );
    ui->spinSpeed->setVisible( m_pMotionGroup->autoTimeAble() );

    setExportOpt( m_pMotionGroup->exportOptList() );

    //! smart edit
    ui->btnSmartEdit->setVisible( m_pMotionGroup->smartEditable() );

    //! robo change
    slot_robo_changed( m_pmcModel->mConn.getRoboName() );

    slot_data_changed();
}

int motionEdit::save( QString &outFileName )
{
    Q_ASSERT( NULL != m_pMotionGroup );
    outFileName = m_pMotionGroup->getPath() +QDir::separator() + m_pMotionGroup->getName();
    outFileName = QDir::toNativeSeparators( outFileName );
    return m_pMotionGroup->save( outFileName );
}

int motionEdit::saveAs( QString &outFileName )
{
    Q_ASSERT( NULL != m_pMotionGroup );

    return m_pMotionGroup->save( outFileName );
}

void motionEdit::onNetEvent(const QString &name,
                            int axes,
                            RoboMsg &msg)
{
    if ( msg.getMsg() == e_robot_status )
    {
        int stat;
        stat = msg.at(1).toInt();

        onMotionStatus( -1, (MRQ_MOTION_STATE)stat );
    }

    else
    {}
}

#define down_start_stop( bdown, bstart, bstop )     \
                                                ui->btnDown->setEnabled( bdown );\
                                                ui->btnStart->setEnabled( bstart );\
                                                ui->btnStop->setEnabled( bstop );
void motionEdit::onMotionStatus( int axes,
                                 MRQ_MOTION_STATE_2 stat )
{
//    logDbg()<<stat;

//    MRQ_MOTION_STATE_POWERON,
//	MRQ_MOTION_STATE_IDLE,
//	MRQ_MOTION_STATE_CALCING,
//	MRQ_MOTION_STATE_CALCEND,
//	MRQ_MOTION_STATE_STANDBY,
//	MRQ_MOTION_STATE_RUNNING,
//	MRQ_MOTION_STATE_ERROR,

//    mrq_state_idle,
//    mrq_state_run_reqed,
//    mrq_state_program,

//    mrq_state_calcing,
//    mrq_state_calcend,
//    mrq_state_standby,

//    mrq_state_prerun,
//    mrq_state_running,
//    mrq_state_prestop,

    MegaDevice::mrqState cvtStat = (MegaDevice::mrqState)stat;
    //! dis link
//    if ( MegaDevice::mrq_state_idle == cvtStat )
//    {
//        setLink( false );
//    }

    if ( MegaDevice::mrq_state_idle == cvtStat )
    {
//        down_start_stop( true, false, false );
        down_start_stop( true, true, false );
    }
    else if ( MegaDevice::mrq_state_run_reqed == cvtStat )
    {
        down_start_stop( true, false, false );
    }
    else if ( MegaDevice::mrq_state_program == cvtStat )
    {
        down_start_stop( false, false, false );
    }
    else if ( MegaDevice::mrq_state_calcing == cvtStat )
    {
        down_start_stop( false, false, false );
    }
    else if ( MegaDevice::mrq_state_calcend == cvtStat )
    {
        down_start_stop( true, true, false );
    }
    else if ( MegaDevice::mrq_state_standby == cvtStat )
    {
        down_start_stop( true, false, false );
    }
    else if ( MegaDevice::mrq_state_prerun == cvtStat )
    {
        down_start_stop( true, false, true );
    }
    else if ( MegaDevice::mrq_state_running == cvtStat )
    {
        down_start_stop( true, false, true );
    }
    else if ( MegaDevice::mrq_state_prestop == cvtStat )
    {
        down_start_stop( true, false, true );
    }
    else
    { Q_ASSERT(false); }
}

void motionEdit::onRequest( RpcRequest &req )
{
    //! check type
    if ( req.checkRequest( m_pMotionGroup->rpcRequest(),
                           m_pMotionGroup->rpcParaType() ) )
    {}
    else
    { return; }

    //! get value
    int curRow;

    //! current
    curRow = ui->tableView->currentIndex().row();

    Q_ASSERT( NULL != m_pMotionGroup );
    m_pMotionGroup->insertRow( curRow + 1  );

    m_pMotionGroup->setRpc( curRow + 1, req );

    ui->tableView->setCurrentIndex( m_pMotionGroup->index( curRow + 1, 0) );
}

VRobot *motionEdit::currentRobot()
{
    return m_pmcModel->m_pInstMgr->findRobot( m_pmcModel->mConn.getRoboName() );
}

void motionEdit::setExportOpt( const QStringList &optList )
{
    for ( int i = 0; i < optList.size(); i++ )
    {
        ui->cmbExport->addItem( optList.at(i) );
    }
}

void motionEdit::testDownload()
{
    //! prepare data
    QList< tpvGroup * > groups;
    groups.append( tpvGroup::createDemoGroup1() );
    groups.append( tpvGroup::createDemoGroup2() );
    groups.append( tpvGroup::createDemoGroup3() );
    groups.append( tpvGroup::createDemoGroup4() );
    groups.append( tpvGroup::createDemoGroup5() );
logDbg();
    QList< int > joints;
    joints.append( 0 );
    joints.append( 1 );
    joints.append( 2 );
    joints.append( 3 );
    joints.append( 4 );
logDbg();

    doDownload( groups, joints );
}



