#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>

class BatteryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryWidget(QWidget *parent = nullptr);

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
    QPointF getWidgetFrameOffset(QSizeF);

public slots:
    void setValue(int);

signals:

};

#endif // BATTERYWIDGET_H
