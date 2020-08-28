#include "levelwidget.h"

# include <QPainter>
# include <QDebug>

LevelWidget::LevelWidget(QWidget *parent) : QWidget(parent)
{

}

void LevelWidget::resizeEvent(QResizeEvent *) {
    // Making widget aspect ratio 1:1 (Square)
    if (this->width() > this->height()){
        QSizeF widgetSize = QSizeF(this->height(),this->height());
        widgetFrame.setSize(widgetSize);

        QPointF widgetFrameOffsetPoint = getWidgetFrameOffset(widgetSize);
        widgetFrame.moveTopLeft(widgetFrameOffsetPoint);
    }else {
        QSizeF widgetSize = QSizeF(this->width(),this->width());
        widgetFrame.setSize(widgetSize);

        QPointF widgetOffsetPoint = getWidgetFrameOffset(widgetSize);
        widgetFrame.moveTopLeft(widgetOffsetPoint);
    }

    float scaleValue = 0.75;
    QSizeF outsideCircleFrameSize = QSizeF(widgetFrame.width()*scaleValue,widgetFrame.height()*scaleValue);
    outsideCircleFrame.setSize(outsideCircleFrameSize);
    outsideCircleFrame.moveCenter(widgetFrame.center());

    scaleValue = 0.5;
    QSizeF insideCircleFrameSize = QSizeF(widgetFrame.width()*scaleValue,widgetFrame.height()*scaleValue);
    insideCircleFrame.setSize(insideCircleFrameSize);
    insideCircleFrame.moveCenter(widgetFrame.center());

    scaleValue = 0.1;
    QSizeF levelCircleFrameSize =  QSizeF(widgetFrame.width()*scaleValue,widgetFrame.height()*scaleValue);
    levelCircleFrame.setSize(levelCircleFrameSize);

}

QPointF LevelWidget:: getWidgetFrameOffset(QSizeF widSize){
    float xOffset = this->width()/2-widSize.width()/2;
    float yOffset = this->height()/2-widSize.height()/2;

    return QPointF(xOffset,yOffset);
}

void LevelWidget::setXAngle(double newValue){
    if (( minAngle <= newValue) && (newValue <= maxAngle)) {
        xAngle = newValue;
    } else if (newValue < minAngle){
        xAngle = minAngle;
    } else if (newValue > maxAngle) {
        xAngle = maxAngle;
    } else {
        return;
    }
    this->update();
}

void LevelWidget::setYAngle(double newValue){

    if (( minAngle <= newValue) && (newValue <= maxAngle)) {
        yAngle = newValue;
    } else if (newValue < minAngle){
        yAngle = minAngle;
    } else if (newValue > maxAngle) {
        yAngle = maxAngle;
    } else {
        return;
    }
    this->update();
}


void LevelWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);

    painter.setPen(pen);

    //    // Delete this in the end
//        painter.drawRect(widgetFrame);
    //    //

    pen.setColor(QColor("#4b4b4b"));
    pen.setWidth(5);
    painter.setPen(pen);
    QBrush brush = QBrush(QColor("#3ae374"));
    painter.setBrush(brush);

    painter.drawEllipse(widgetFrame);

    pen.setColor(QColor("#3d3d3d"));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawEllipse(outsideCircleFrame);
    painter.drawEllipse(insideCircleFrame);

    brush.setColor(Qt::white);
    painter.setBrush(brush);


    // Level circle position
    float xPosition = widgetFrame.center().x() + (xAngle/(maxAngle*2)) * widgetFrame.width();
    float yPosition = widgetFrame.center().y() + (yAngle/(maxAngle*2)) * widgetFrame.height();

    QPointF levelCirclePosition = QPointF(xPosition,yPosition);
    levelCircleFrame.moveCenter(levelCirclePosition);

    painter.drawEllipse(levelCircleFrame);



}
