#ifndef THERMOMETERWIDGET_H
#define THERMOMETERWIDGET_H

#include <QWidget>

class ThermometerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThermometerWidget(QWidget *parent = nullptr);
private:
    QRectF widgetFrame;

    QRectF bottomTankRect;
    QRectF topTankRect;

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);
    QPointF getWidgetFrameOffset(QSizeF);

signals:

};

#endif // THERMOMETERWIDGET_H
