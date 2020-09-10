#include "levelwidget.h"

# include <QPainter>
# include <QDebug>
# include <cmath>


LevelWidget::LevelWidget(QWidget *)
{
}

void LevelWidget::resizeEvent(QResizeEvent *) {
    // Making widget aspect ratio 1:1 (Square)
    widgetFrame = getFrame();

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
    this->repaint();
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
    this->repaint();
}

float LevelWidget::getXAngle() {
    return xAngle;
}

float LevelWidget::getYAngle() {
    return yAngle;
}

void LevelWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);

    painter.setPen(pen);

    float outsideFrameWidth = widgetFrame.width()/35;
    pen.setColor(QColor("#4b4b4b"));
    pen.setWidth(outsideFrameWidth);
    painter.setPen(pen);
    QBrush brush = QBrush(QColor("#3ae374"));
    painter.setBrush(brush);

    painter.drawEllipse(widgetFrame);

    pen.setColor(QColor("#3d3d3d"));
    pen.setWidth(widgetFrame.width()/70);
    painter.setPen(pen);

    brush.setColor(Qt::white);
    painter.setBrush(brush);


    // Level circle position
    QPointF levelCirclePosition;

    if (xAngle == 0 && yAngle == 0) {
        levelCirclePosition = widgetFrame.center();
    } else {
        double angle = atan(yAngle/xAngle);
        float xNewPos = widgetFrame.center().x() + cos(angle)* xAngle/(maxAngle) * (widgetFrame.width() - levelCircleFrame.width() - outsideFrameWidth)/2;
        float yNewPos = widgetFrame.center().y() + sin(angle)* yAngle/(maxAngle) * (widgetFrame.width() - levelCircleFrame.height() - outsideFrameWidth)/2;
        levelCirclePosition = QPointF(xNewPos,yNewPos);
    }

    levelCircleFrame.moveCenter(levelCirclePosition);

    painter.drawEllipse(levelCircleFrame);

    brush.setColor(Qt::transparent);
    painter.setBrush(brush);

    painter.drawEllipse(outsideCircleFrame);
    painter.drawEllipse(insideCircleFrame);


}
