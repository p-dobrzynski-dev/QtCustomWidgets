#ifndef THERMOMETERWIDGET_H
#define THERMOMETERWIDGET_H

#include <QWidget>
#include <widgetengine.h>

class ThermometerWidget : public WidgetEngine
{
    Q_OBJECT
public:
    ThermometerWidget(QWidget *parent = nullptr);
private:
    QRectF widgetFrame;
    QRectF tankRect;

    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void validateValue(float newValue) override;
};

#endif // THERMOMETERWIDGET_H
