#ifndef WIDGETENGINE_H
#define WIDGETENGINE_H

#include <QObject>
#include <QWidget>

class WidgetEngine
{
public:
    WidgetEngine();
    QRectF getFrame(QSize widgetSize);
    QPointF getWidgetFrameOffset(QSize widgetSize, QSizeF newWidgetSize);
private:
};

#endif // WIDGETENGINE_H
