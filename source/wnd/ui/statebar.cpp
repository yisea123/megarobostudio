#include "statebar.h"
#include "ui_statebar.h"

stateBar::stateBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stateBar)
{
    ui->setupUi(this);

    ui->progressBar->hide();
    ui->labeIInfo->hide();
}

stateBar::~stateBar()
{
    delete ui;
}

void stateBar::showInfo( const QString &str )
{ ui->labeIInfo->setText(str); }

void stateBar::showProgress( int from, int to, int now,
                   const QString &info )
{
    ui->progressBar->setRange(from,to);
    ui->progressBar->setValue( now );
}
void stateBar::showState( const QString &str )
{ ui->labelState->setText( str ); }

QProgressBar *stateBar::progressBar()
{ return ui->progressBar; }
QLabel *stateBar::progressInfo()
{ return ui->labeIInfo; }
QLabel *stateBar::statusLabel()
{ return ui->labelState; }


