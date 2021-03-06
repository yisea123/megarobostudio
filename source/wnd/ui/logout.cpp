#include "logout.h"
#include "ui_logout.h"

logOut::logOut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logOut)
{
    ui->setupUi(this);

    connect( this, SIGNAL(sig_log_item( const QString &)),
             this, SLOT(slot_log_item( const QString &)));

    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
}

logOut::~logOut()
{
    delete ui;
}

QSize logOut::sizeHint() const
{ return QSize(0,60); }

void logOut::on_btnExport_clicked()
{
    QFileDialog fDlg;

    fDlg.setAcceptMode( QFileDialog::AcceptSave );
    fDlg.setNameFilter( tr("log file (*.txt )") );
    if ( QDialog::Accepted != fDlg.exec() )
    { return; }

    QFile file( fDlg.selectedFiles().first() );

    if ( !file.open(QIODevice::WriteOnly) )
    { return; }

    QString str;
    for ( int i = 0; i < ui->listWidget->count(); i++ )
    {
        str = ui->listWidget->item(i)->data(Qt::DisplayRole).toString();
        str.append('\n');
        file.write( str.toLocal8Bit() );
    }
}

void logOut::slot_log_item( const QString &str )
{
    mMutex.lock();
    QListWidgetItem *pItem;
    while ( ui->listWidget->count() >= ui->spinBox->value() )
    {
        pItem = ui->listWidget->takeItem(0);
        Q_ASSERT( NULL != pItem );
        delete pItem;
    }

    //! add to last
    ui->listWidget->addItem( str );
    ui->listWidget->setCurrentRow( ui->listWidget->count() - 1 );
    mMutex.unlock();
}

void logOut::logIn( const QString &str )
{
    if ( !ui->chkLog->isChecked() )
    { return; }

    QString fmtStr = QString("%1:%2").arg( QTime::currentTime().toString("hh:mm:ss.zzz") ).arg(str);
    emit sig_log_item( fmtStr );
}
