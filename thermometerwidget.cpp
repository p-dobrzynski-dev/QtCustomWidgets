#include "thermometerwidget.h"

# include <QPainter>
# include <QDebug>

ThermometerWidget::ThermometerWidget(QWidget *parent) : QWidget(parent)
{

}

void ThermometerWidget:: resizeEvent(QResizeEvent *){

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

    float scaleValue = 0.1;
    QSizeF topTankRectSize = QSizeF(widgetFrame.width()*scaleValue, widgetFrame.height());
    topTankRect.setSize(topTankRectSize);

    QPointF topTankPoint = QPointF(widgetFrame.center().x() - widgetFrame.width()*scaleValue/2, widgetFrame.top());
    topTankRect.moveTopLeft(topTankPoint);

}

QPointF ThermometerWidget:: getWidgetFrameOffset(QSizeF widSize){
    float xOffset = this->width()/2-widSize.width()/2;
    float yOffset = this->height()/2-widSize.height()/2;

    return QPointF(xOffset,yOffset);
}

void ThermometerWidget::setValue(double newValue){
    if ((newValue >= minValue) && (newValue <=maxValue)){
        value = newValue;
    } else if (newValue < minValue) {
        value = minValue;
    } else if (newValue > maxValue) {
        value = maxValue;
    } else {
        return;
    }
    this->update();
}

void ThermometerWidget:: paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);
    QBrush brush = QBrush(Qt::white);

    painter.setPen(pen);

    // Delete this in the end
//    painter.drawRect(widgetFrame);
    //
    float cornerRadius = widgetFrame.width()/60;

    // Infill Path
    QPainterPath infillPath;
    QRectF infillRect = QRectF(topTankRect);

    float stepHeightValue = widgetFrame.height()/(maxValue - minValue);
    infillRect.setTop(widgetFrame.top() - value*stepHeightValue + maxValue*stepHeightValue);
    infillPath.addRoundedRect(infillRect,cornerRadius,cornerRadius);
    pen.setColor(Qt::transparent);
    painter.setPen(pen);

    if (value > 0) {
        painter.fillPath(infillPath,Qt::red);
    } else {
        painter.fillPath(infillPath,Qt::blue);
    }
    painter.drawPath(infillPath);

    // Drawing tank
    painter.drawRect(topTankRect);


    QPainterPath path;
    path.addRoundedRect(topTankRect, cornerRadius,cornerRadius);

    pen.setColor(QColor("#2f3640"));
    pen.setWidth(widgetFrame.width()/80);
    painter.setPen(pen);
    painter.fillPath(path,Qt::transparent);
    painter.drawPath(path);

    //Drawing 0 line
    pen.setWidth(widgetFrame.width()/100);
    painter.setPen(pen);
    QLineF zeroLine = QLineF(QPointF(topTankRect.center().x()-topTankRect.width()/1.5,widgetFrame.top() + maxValue*stepHeightValue),
                             QPointF(topTankRect.center().x()+topTankRect.width()/1.5,widgetFrame.top() + maxValue*stepHeightValue));
    painter.drawLine(zeroLine);
}
