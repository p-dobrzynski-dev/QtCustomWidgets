#ifndef WIDGETENGINE_H
#define WIDGETENGINE_H

#include <QObject>
#include <QWidget>

class WidgetEngine: public QWidget
{
public:
    explicit WidgetEngine(QWidget *parent = nullptr);
    QRectF getFrame();
    QPointF getWidgetFrameOffset(QSizeF newWidgetSize);
    void setValue(float newValue);
    void setMaxValue(float maxValue);
    float value = 0;
    float maxValue = 0;
    float minValue = 0;

    float getValue();
    float getMaxValue();
    float getMinValue();

private:
    virtual void validateValue(float newValue);
};

#endif // WIDGETENGINE_H
