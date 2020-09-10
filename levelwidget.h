#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>
#include <widgetengine.h>

class LevelWidget :public WidgetEngine
{
    Q_OBJECT
public:
    LevelWidget(QWidget *parent = nullptr);
    float getXAngle();
    float getYAngle();
    void setXAngle(double);
    void setYAngle(double);
private:
    QRectF widgetFrame;
    QRectF outsideCircleFrame;
    QRectF insideCircleFrame;
    QRectF levelCircleFrame;

    float xAngle = 0.0;
    float yAngle = 0.0;

    float minAngle = -10.0;
    float maxAngle = 10.0;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *) override;

protected:
    using WidgetEngine::setValue;
};

#endif // LEVELWIDGET_H
