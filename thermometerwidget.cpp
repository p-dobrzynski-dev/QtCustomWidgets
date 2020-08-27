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



    float scaleValue = 0.8;
    QSizeF topTankRectSize = QSizeF(widgetFrame.width()*0.1, widgetFrame.height()*scaleValue);
    topTankRect.setSize(topTankRectSize);

    QPointF topTankPoint = QPointF(widgetFrame.center().x()-widgetFrame.width()/2, widgetFrame.top());
    topTankRect.setTopLeft(topTankPoint);

}

QPointF ThermometerWidget:: getWidgetFrameOffset(QSizeF widSize){
    float xOffset = this->width()/2-widSize.width()/2;
    float yOffset = this->height()/2-widSize.height()/2;

    return QPointF(xOffset,yOffset);
}

void ThermometerWidget:: paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);
    QBrush brush = QBrush(Qt::white);

    painter.setPen(pen);

    // Delete this in the end
        painter.drawRect(widgetFrame);
    //
    painter.drawRect(topTankRect);
}
