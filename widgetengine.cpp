#include "widgetengine.h"

WidgetEngine::WidgetEngine()
{

}

QRectF WidgetEngine::getFrame(QSize widgetSize) {
    QRectF frame = QRectF();
    QSizeF newWidgetSize;
    // Making widget aspect ratio 1:1 (Square)
    if (widgetSize.width() > widgetSize.height()){
        newWidgetSize = QSizeF(widgetSize.height()*0.95,widgetSize.height()*0.95);
        frame.setSize(newWidgetSize);

        QPointF widgetFrameOffsetPoint = getWidgetFrameOffset(widgetSize, newWidgetSize);
        frame.moveTopLeft(widgetFrameOffsetPoint);
    }else {
        newWidgetSize = QSizeF(widgetSize.width()*0.95,widgetSize.width() * 0.95);
        frame.setSize(newWidgetSize);

        QPointF widgetOffsetPoint = getWidgetFrameOffset(widgetSize, newWidgetSize);
        frame.moveTopLeft(widgetOffsetPoint);
    }

    return frame;
}

QPointF WidgetEngine::getWidgetFrameOffset(QSize widgetSize, QSizeF newWidgetSize){
    float xOffset = widgetSize.width()/2-newWidgetSize.width()/2;
    float yOffset = widgetSize.height()/2-newWidgetSize.height()/2;

    return QPointF(xOffset,yOffset);
}
