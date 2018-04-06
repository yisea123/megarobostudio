#ifndef MRQSENSORPAGE_H
#define MRQSENSORPAGE_H

#include <QWidget>

namespace Ui {
class MrqSensorPage;
}
#include "mrquart.h"
#include "mrqsubuart.h"
class MrqSensorPage : public QWidget
{
    Q_OBJECT

public:
    explicit MrqSensorPage(QWidget *parent = 0);
    ~MrqSensorPage();

    void setUartConfig(
                     uartConfig &cfg
                     );
    void getUartConfig(
            uartConfig &cfg
                     );

    void setSubUartConfig(
                     int index,
                     subUartConfig &cfg
                     );
    void getSubUartConfig(
                    int index,
                    subUartConfig &cfg
                     );

private:
    Ui::MrqSensorPage *ui;


};

#endif // MRQSENSORPAGE_H