#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <widgetengine.h>

class BatteryWidget : public QWidget, public WidgetEngine
{
    Q_OBJECT
public:
    explicit BatteryWidget(QWidget *parent = nullptr);
    int getValue();
private:

    QRectF widgetFrame;
    QRectF mainBatteryFrame;
    QRectF tipBatteryFrame;
    QRectF batteryLevelFrame;

    int value = 0;

    int maxValue = 100;
    int minValue = 0;

    QFont textFont = QFont();

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

public slots:
    void setValue(int);

signals:

};

#endif // BATTERYWIDGET_H
