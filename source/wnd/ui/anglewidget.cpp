#include "anglewidget.h"
#include "ui_anglewidget.h"

AngleWidget::AngleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AngleWidget)
{
    ui->setupUi(this);

    setAttribute( Qt::WA_DeleteOnClose );
}

AngleWidget::~AngleWidget()
{
    delete ui;
}

void AngleWidget::setConnections( const QStringList &conns )
{
    ui->cmbConn->clear();
    ui->cmbConn->addItems( conns );
}

QString AngleWidget::connection()
{
    return ui->cmbConn->currentText();
}

void AngleWidget::setValue( float val )
{
    ui->angleValue->display( val );
}
float AngleWidget::value()
{
    return ui->angleValue->value();
}

void AngleWidget::on_btnClose_clicked()
{
    emit signal_close( this );
}
