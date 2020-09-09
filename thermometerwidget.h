#ifndef THERMOMETERWIDGET_H
#define THERMOMETERWIDGET_H

#include <QWidget>
#include <widgetengine.h>

class ThermometerWidget : public QWidget, public WidgetEngine
{
    Q_OBJECT
public:
    explicit ThermometerWidget(QWidget *parent = nullptr);
    int getValue();
private:
    QRectF widgetFrame;

    QRectF bottomTankRect;
    QRectF topTankRect;
    QRectF valueRect;

    double minValue = -20.0;
    double maxValue = 60.0;
    double value = 0.0;

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

public slots:
    void setValue(double);

signals:

};

#endif // THERMOMETERWIDGET_H
