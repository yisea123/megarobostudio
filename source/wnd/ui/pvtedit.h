#ifndef PVTEDIT_H
#define PVTEDIT_H

#include <QtWidgets>

#include "../../../include/mcstd.h"

#include "../../model/tpvgroup.h"
#include "tableedit.h"

#include "tpvplot.h"

#include "pvtpref.h"

#include "../model/dspindelegate.h"

namespace Ui {
class pvtEdit;
}

#define tpv_type    double
class pvtEdit :  public tableEdit
{
    Q_OBJECT

public:
    explicit pvtEdit(QWidget *parent = 0);
    ~pvtEdit();

public:
    virtual void setModelObj( mcModelObj *pObj );
    virtual int save( QString &outFileName );
    virtual int saveAs( QString &outFileName );

protected:
    virtual void onNetEvent(const QString &name,
                            int axes,
                            RoboMsg &msg);

    void onMotionStatus( int axes, MRQ_MOTION_STATE_2 stat );

protected:
    void setupUi();
    void buildConnection();

    bool checkChan( const QString &name,
                    int axesId );
    bool checkChan();

protected:
    virtual void context_remove();
    virtual void context_add_before();
    virtual void context_add_below();
    virtual void context_clear();

    int postDownload( appMsg msg, void *pPara );
    void beginDownload( void *pPara);
    void endDownload( int ret, void *pPara );
    void progDownload( int now, int from, int to, void *pPara );

    int postStart( appMsg msg, void *pPara );
    void beginStart( void *pPara );
    void endStart( int ret, void *pPara );

    int postStop( appMsg msg, void *pPara );
    void beginStop( void *pPara );
    void endStop( int ret, void *pPara );

    QProgressDialog *progress();

    //! dot->line
    int buildLine( );

    void gcLine();
    int  checkLine();
    int  compileLine();

    void updatePlot();

    void stateIdle();

Q_SIGNALS:
    void sigLineChanged();

protected Q_SLOTS:
    void slot_timeout();
    void on_btnBuild_clicked();     //! build line

    void on_btnDown_clicked();
    void on_btnStart_clicked();
    void on_btnStop_clicked();

    void on_btnAdd_clicked();
    void on_btnDel_clicked();
    void on_btnClr_clicked();
    void on_btnGraph_clicked();

    void slot_download_cancel();

    void on_spinLoop_valueChanged(int arg1);
    void on_cmbPlanMode_currentIndexChanged(int index);
    void on_cmbMotionMode_currentIndexChanged(int index);

    void on_btnPref_clicked();

    void slot_data_changed();
    void slot_line_changed();

private slots:


private:
    Ui::pvtEdit *ui;

    tpvGroup *mTpvGroup;
    QProgressDialog *m_pProgress;

    tpvPlot *m_pPlot;

    int mCurT, mCurP, mCurV;
    int mTStep, mPStep;

    QList< QPointF > mTPs;
    QList< QPointF > mTVs;

    modelPvtPref mPvtPref;

    dSpinDelegate *m_pSpinDelegate;

    QTimer mDlySaveTimer;
};

#endif // PVTEDIT_H
