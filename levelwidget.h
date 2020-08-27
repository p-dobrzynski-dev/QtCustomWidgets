#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>

class LevelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LevelWidget(QWidget *parent = nullptr);
private:
    QRectF widgetFrame;
    QRectF outsideCircleFrame;
    QRectF insideCircleFrame;
    QRectF levelCircleFrame;

    float xAngle = 0.0;
    float yAngle = 0.0;

    float minAngle = -10.0;
    float maxAngle = 10.0;

    void resizeEvent(QResizeEvent *event);

    void paintEvent(QPaintEvent *);
    QPointF getWidgetFrameOffset(QSizeF);

public slots:
    void setXAngle(double);
    void setYAngle(double);

signals:

};

#endif // LEVELWIDGET_H
