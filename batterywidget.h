#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <widgetengine.h>

class BatteryWidget: public WidgetEngine
{
    Q_OBJECT
public:
    BatteryWidget(QWidget *parent = nullptr);
    bool getChargingState();
    void setChargingState(bool state);
private:

    QRectF widgetFrame;
    QRectF mainBatteryFrame;
    QRectF tipBatteryFrame;
    QRectF batteryLevelFrame;

    bool isCharging = false;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void validateValue(float newValue) override;
};

#endif // BATTERYWIDGET_H
