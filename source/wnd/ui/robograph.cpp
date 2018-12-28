#include "robograph.h"
#include "ui_robograph.h"

#include "../model/mrggraphmodel.h"

#include "../widget/lineentity.h"
#include "../widget/rectentity.h"
#include "../widget/imageentity.h"

RoboGraph::RoboGraph(QWidget *parent) :
    modelView(parent),
    ui(new Ui::RoboGraph)
{
    ui->setupUi(this);

//    //! debug
//    m_pLineWidget = new LineEntity( this );
//    m_pLineWidget->setVisible( true );
//    connect( m_pLineWidget, SIGNAL(signal_link_changed(EntityWidget*,Anchor::anchorType,QRect)),
//             this, SLOT(slot_link_changed(EntityWidget*,Anchor::anchorType,QRect)));

//    m_pRectWidget = new RectEntity(this);
//    m_pRectWidget->setVisible( true );
//    connect( m_pRectWidget, SIGNAL(signal_anchor_changed(EntityWidget*,Anchor::anchorType,QPoint)),
//             this, SLOT(slot_anchor_changed(EntityWidget*,Anchor::anchorType,QPoint)));

//    m_pRectWidget->setGeometry( 200,200,100,50);

//    mChildWidgets.append( m_pLineWidget );
//    mChildWidgets.append( m_pRectWidget );

//    EntityWidget *pWig;
//    pWig = new ImageEntity( this );
//    pWig->setGeometry( 300,10,100,100 );

//    connect( pWig, SIGNAL(signal_anchor_changed(EntityWidget*,Anchor::anchorType,QPoint)),
//             this, SLOT(slot_anchor_changed(EntityWidget*,Anchor::anchorType,QPoint)));

//    mChildWidgets.append( pWig );
//    setMouseTracking( true );
}

RoboGraph::~RoboGraph()
{
    delete ui;
}

void RoboGraph::mousePressEvent(QMouseEvent *event)
{
    //! save now
    mPtMouse = event->pos();

    //! selected
    QRect wigRect;
    QPoint ptChild;
    for ( int i = 0; i < mChildWidgets.size(); i++ )
    {
        ptChild = mChildWidgets.at(i)->mapFromParent( mPtMouse );

        if ( mChildWidgets.at(i)->mouseOver(ptChild) )
        { mChildWidgets[i]->setSelected( true ); }
        else
        { mChildWidgets[i]->setSelected( false ); }
    }

    modelView::mousePressEvent( event );
}
void RoboGraph::mouseReleaseEvent( QMouseEvent *event )
{
    modelView::mouseReleaseEvent( event );
}
void RoboGraph::mouseMoveEvent(QMouseEvent *event)
{
    QPoint ptNow = event->pos();

    //! move
    int dx, dy, x, y;
    dx = ptNow.x() - mPtMouse.x();
    dy = ptNow.y() - mPtMouse.y();

    QRect wigRect;
    ShiftContext context;
    for ( int i = 0; i < mChildWidgets.size(); i++ )
    {
        if ( mChildWidgets.at(i)->selected() )
        {
            wigRect = mChildWidgets.at(i)->geometry();

            mChildWidgets.at(i)->shift(  wigRect, QPoint( dx, dy ), context );
            mChildWidgets.at(i)->setGeometry( wigRect );
            mChildWidgets.at(i)->shiftEnd( context );

            //! link
            mChildWidgets.at(i)->anchorProc();
        }
    }

    //! save now
    mPtMouse = ptNow;

    //! restore cursor

    modelView::mouseMoveEvent( event );
}

void RoboGraph::mouseDoubleClickEvent( QMouseEvent *event )
{
    if ( event->buttons() == Qt::LeftButton )
    {
        createEntityWidget( EntityWidget::entity_widget_line, event->pos() );
    }
    else
    { return; }

    //! add line
}

void RoboGraph::keyReleaseEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Delete )
    {logDbg();
        deleteSelected();
    }
}

void RoboGraph::dragEnterEvent(QDragEnterEvent *event)
{
    logDbg()<<event->mimeData()->formats();

    if (event->mimeData()->hasFormat("devicemgr/robot"))
    { event->acceptProposedAction(); }
    else if ( event->mimeData()->hasFormat("oplib/operator") )
    { event->acceptProposedAction(); }
    else
    {}
}
void RoboGraph::dropEvent(QDropEvent *event)
{
    //! point
    QPoint pt;
    pt = mapFrom( this, event->pos() );

    //! robot
    if (event->mimeData()->hasFormat("devicemgr/robot"))
    {
        logDbg()<<event->mimeData()->data("devicemgr/robot");

        event->acceptProposedAction();


        //! add
        EntityWidget *pWig = addRoboEntity(  event->mimeData()->data("devicemgr/robot"),
                                             event->mimeData()->text(),
                                             pt );
        if ( NULL == pWig )
        { return; }
    }
    //! operator
    else if ( event->mimeData()->hasFormat("oplib/operator") )
    {
        event->acceptProposedAction();

        EntityWidget *pWig = addOperatorEntity( event->mimeData()->text(),
                                                event->mimeData()->data( "oplib/operator"),
                                                pt );

        if ( NULL == pWig )
        { return; }
    }
    else
    {

    }
}

//QSize RoboGraph::sizeHint()
//{
//    if ( mChildWidgets.size() > 0 )
//    {
//        QPolygon poly;

//        for( int i = 0; i < mChildWidgets.size(); i++ )
//        {
//            poly<<QPolygon( mChildWidgets[i]->geometry() );
//        }

//        return poly.boundingRect().size();
//    }
//    else
//    { return modelView::sizeHint(); }
//}

int RoboGraph::save( QString &outFileName )
{
    //! get obj

    MrgGraphModel *pModel = dynamic_cast< MrgGraphModel*>( m_pModelObj );
    if ( NULL == pModel )
    { logDbg(); return -1; }

    //! build name
    outFileName = m_pModelObj->getPath() + QDir::separator() + m_pModelObj->getName();
    outFileName = QDir::toNativeSeparators( outFileName );

    return pModel->save( outFileName );
}
int RoboGraph::saveAs( QString &name )
{
    return save( name );
}

//! rect in parent
void RoboGraph::slot_link_changed( EntityWidget *pWig,
                                   Anchor::anchorType tpe,
                                   QRect rect )
{
    Q_ASSERT( NULL != pWig );

    //! detect success
    EntityWidget *pAttachWig;

    if ( crossDetect( pWig, rect, &pAttachWig ) )
    {logDbg();}
    else
    {logDbg();
        pWig->delink( tpe );
        return;
    }

    //! stick to border
    QRect geo;
    geo = pAttachWig->geometry();

    QPoint pt = rect.center();

    QPoint ptStick;
    ptStick.setX( qMin( geo.right(), qMax( geo.left(), pt.x() ) ) );
    ptStick.setY( qMin( geo.bottom(), qMax( geo.top(), pt.y() ) ) );
logDbg()<<rect<<ptStick<<geo;
    //! pt stick ref to the widget
    pAttachWig->attachWidget( pWig, tpe, ptStick - geo.topLeft() );
}

void RoboGraph::slot_anchor_changed( EntityWidget *pWig,
                          Anchor::anchorType tpe,
                          QPoint ptParent )
{
    Q_ASSERT( NULL != pWig );

    QPoint ptRef;
    QRect rect;
    Anchor::anchorType refType;
    if ( tpe == Anchor::anchor_line_from )
    {logDbg();
        ptRef = pWig->toAnchor();
        refType = Anchor::anchor_line_to;
    }
    else if ( tpe == Anchor::anchor_line_to )
    {
        ptRef = pWig->fromAnchor();
        refType = Anchor::anchor_line_from;
    }
    else
    { return; }

    //! gen
    rect = EntityWidget::genBoundingRect( ptParent, ptRef );
logDbg()<<rect<<ptParent<<ptRef;
    //! geo
    pWig->setGeometry( rect );
    pWig->setAnchor( tpe, pWig->mapFromParent( ptParent ) );
    pWig->setAnchor( refType, pWig->mapFromParent( ptRef ) );
}

void RoboGraph::slot_request_delete( EntityWidget *pWig )
{
    deleteSelected();
}

EntityWidget* RoboGraph::createEntityWidget( EntityWidget::EntityWidgetType tpe,
                                             const QPoint &pt )
{
    EntityWidget *pWig;
    if ( tpe == EntityWidget::entity_widget_line )
    {
        pWig = new LineEntity( this );
        if ( NULL == pWig )
        { return pWig; }

        mChildWidgets.append( pWig );

        pWig->setVisible( true );
        pWig->move( pt );

        connect( pWig, SIGNAL(signal_link_changed(EntityWidget*,Anchor::anchorType,QRect)),
                 this, SLOT(slot_link_changed(EntityWidget*,Anchor::anchorType,QRect)));

        connect( pWig, SIGNAL(signal_request_delete(EntityWidget*)),
                 this, SLOT(slot_request_delete(EntityWidget*)) );

        return pWig;
    }
    else if ( tpe == EntityWidget::entity_widget_rect )
    {
        pWig = new RectEntity(this);
    }
    else if ( tpe == EntityWidget::entity_widget_image )
    {
        pWig = new ImageEntity(this);
    }
    else
    { return NULL; }

    //! invalid
    if ( NULL != pWig )
    {}
    else
    { return NULL; }

    //! post proc
    pWig->setVisible( true );
    pWig->move( pt );

    connect( pWig, SIGNAL(signal_anchor_changed(EntityWidget*,Anchor::anchorType,QPoint)),
             this, SLOT(slot_anchor_changed(EntityWidget*,Anchor::anchorType,QPoint)));

    connect( pWig, SIGNAL(signal_request_delete(EntityWidget*)),
             this, SLOT(slot_request_delete(EntityWidget*)) );

    mChildWidgets.append( pWig );
    return pWig;
}

void RoboGraph::deleteSelected()
{
    QList<EntityWidget*> delList;

    //! collect
    foreach (EntityWidget *pWig, mChildWidgets)
    {
        if ( pWig->selected() )
        { delList.append( pWig ); }
    }
logDbg();
    //! delete
    foreach( EntityWidget *pWig, delList )
    {logDbg();
        //! \note link and attach are conflict
        pWig->cleanAttach();

        pWig->cleanLink();

        mChildWidgets.removeAll( pWig );

        delete pWig;
    }
}

EntityWidget* RoboGraph::addRoboEntity( const QString &className,
                                        const QString &name,
                                        const QPoint &pt )
{
    //! create a new robot
    VRobot *pNewRobot = robotFact::createRobot( className );
    Q_ASSERT( NULL != pNewRobot );

    ImageEntity *pWig = (ImageEntity *)createEntityWidget( EntityWidget::entity_widget_image, pt );
    if ( NULL != pWig )
    {
        pWig->setLabel( name );
        pWig->setImage( pNewRobot->getImage() );
    }
    else
    { }

    delete pNewRobot;

    return pWig;
}

EntityWidget* RoboGraph::addOperatorEntity( const QString &className,
                                            const QString &icon,
                                            const QPoint &pt )
{
    ImageEntity *pWig = (ImageEntity *)createEntityWidget( EntityWidget::entity_widget_image, pt );
    if ( NULL != pWig )
    {
        pWig->setLabel( className );
        pWig->setImage( QImage( icon ) );
    }
    else
    { }

    return pWig;
}

bool RoboGraph::crossDetect( EntityWidget *pSrc,
                             const QRect &rect,
                             EntityWidget **pWig )
{
    QRect geo;
    for ( int i = 0; i < mChildWidgets.size(); i++ )
    {
        if ( pSrc != mChildWidgets.at(i) )
        {}
        else
        { continue; }

        geo = mChildWidgets.at(i)->geometry();
        logDbg()<<geo<<rect;
        if ( geo.intersects( rect ) )
        {
            *pWig = mChildWidgets.at(i);
            return true;
        }
    }

    return false;
}

void RoboGraph::on_btnGen_clicked()
{

}

void RoboGraph::on_btnRun_clicked()
{

}

void RoboGraph::on_btnStop_clicked()
{

}
