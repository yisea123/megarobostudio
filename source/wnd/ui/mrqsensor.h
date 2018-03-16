#ifndef MRQSENSOR_H
#define MRQSENSOR_H

#include <QWidget>
#include "mrqview.h"

namespace Ui {
class mrqSensor;
}

class mrqSensor : public mrqView
{
    Q_OBJECT

public:
    explicit mrqSensor(QWidget *parent = 0);
    ~mrqSensor();

public:
    virtual int setApply();
protected:
    virtual void modelChanged();

protected:
    void setupUi();
    void desetupUi();

    int apply();
    int updateUi();


private slots:
    void on_btnApply_clicked();

private:
    Ui::mrqSensor *ui;
};

#endif // MRQSENSOR_H
