#ifndef H2PREF_H
#define H2PREF_H

#include <QtWidgets>
#include "modelview.h"
namespace Ui {
class H2Pref;
}

class H2Pref : public modelView
{
    Q_OBJECT

public:
    explicit H2Pref(QWidget *parent = 0);
    ~H2Pref();

public:
    virtual void setModelObj( mcModelObj *pObj );
    virtual int setApply();

    virtual void updateScreen();
protected:
    void spyEdited();
    void updateData();
    void updateUi();

    void adaptUi();

    void zeroJoint( int jointId, bool bCcw );

protected Q_SLOTS:
    void slot_joint_zero( int jId, bool bCcw );

Q_SIGNALS:
    void signal_joint_zero( int jointid, bool bCcw );

private slots:

    void on_btnZeroX_clicked();

    void on_btnZeroY_clicked();

    void on_btnZeroBody_clicked();

    void on_btnZeroZ_clicked();

//    void on_chkCcwX_clicked(bool checked);

//    void on_chkCcwY_clicked(bool checked);

//    void on_chkCcw_clicked(bool checked);

private:
    Ui::H2Pref *ui;

};

#endif // H2PREF_H
