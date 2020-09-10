#include "widgetengine.h"
#include <QDebug>


WidgetEngine::WidgetEngine(QWidget *parent) :
    QWidget(parent)
{

}

QRectF WidgetEngine::getFrame() {
    QRectF frame = QRectF();
    QSizeF newWidgetSize;
    // Making widget aspect ratio 1:1 (Square)
    if (this->width() > this->height()){
        newWidgetSize = QSizeF(this->height()*0.95,this->height()*0.95);
        frame.setSize(newWidgetSize);

        QPointF widgetFrameOffsetPoint = getWidgetFrameOffset(newWidgetSize);
        frame.moveTopLeft(widgetFrameOffsetPoint);
    }else {
        newWidgetSize = QSizeF(this->width()*0.95,this->width() * 0.95);
        frame.setSize(newWidgetSize);

        QPointF widgetOffsetPoint = getWidgetFrameOffset(newWidgetSize);
        frame.moveTopLeft(widgetOffsetPoint);
    }
    return frame;
}

QPointF WidgetEngine::getWidgetFrameOffset(QSizeF newWidgetSize){
    float xOffset = this->width()/2-newWidgetSize.width()/2;
    float yOffset = this->height()/2-newWidgetSize.height()/2;

    return QPointF(xOffset,yOffset);
}

void WidgetEngine::validateValue(float newValue) {
    value = newValue;
}

void WidgetEngine::setValue(float newValue) {
    validateValue(newValue);
    this->update();
    this->repaint();
}

float WidgetEngine::getValue() {
    return value;
}

void WidgetEngine::setMaxValue(float newMaxValue){
    maxValue = newMaxValue;
    this->update();
    this->repaint();
}

float WidgetEngine::getMaxValue() {
    return maxValue;
}
