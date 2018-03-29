#ifndef ROBOAXES_H
#define ROBOAXES_H

#include <QDateTime>
#include <QDialog>
#include <QLabel>
#include <QLCDNumber>
#include "../../device/vrobot.h"
#include "dlgview.h"
#include "robojoint.h"
namespace Ui {
class roboAxes;
}


class roboAxes : public DlgView
{
    Q_OBJECT

public:
    explicit roboAxes( mcModel *pModel,
                       QWidget *parent = 0);
    ~roboAxes();

Q_SIGNALS:
    void sig_close();

protected Q_SLOTS:
    void on_chkAngle_toggled(bool checked);
    void on_sampleTimer_valueChanged( int val );

    void slot_timeout();
    void slot_joint_action( int id, float dt, float angle );
    void slot_joint_zero( int id );

    void slot_robo_changed( const QString &roboName );

protected:
    VRobot *Robot();
    void adapteUiToRobot( VRobot *pRobo );

protected:
    void buildConnection();

    void rotate( int jointId,
                 float t1, float a1,
                 float t2, float a2 );

private:
    Ui::roboAxes *ui;
    QTimer mTimer;

//    QDateTime mFromTime, mEndTime;
//    float mAngleFrom, mAngleTo;

//    QLabel *mJointLabels[ 5 ];
//    QList< QLCDNumber *> mAngleNumbers;

    QList< RoboJoint* > mJoints;
};

#endif // ROBOAXES_H
