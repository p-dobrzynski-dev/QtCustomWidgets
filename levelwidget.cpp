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

    QPointF outsideCircleFramePoint = QPointF(0, 0);
    outsideCircleFrame.moveTopLeft(outsideCircleFramePoint);

    scaleValue = 0.5;
    QSizeF insideCircleFrameSize = QSizeF(widgetFrame.width()*scaleValue,widgetFrame.height()*scaleValue);
    insideCircleFrame.setSize(insideCircleFrameSize);
}

QPointF LevelWidget:: getWidgetFrameOffset(QSizeF widSize){
    float xOffset = this->width()/2-widSize.width()/2;
    float yOffset = this->height()/2-widSize.height()/2;

    return QPointF(xOffset,yOffset);
}

void LevelWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);
    QBrush brush = QBrush(Qt::white);

    painter.setPen(pen);

    //    // Delete this in the end
        painter.drawRect(widgetFrame);
    //    //
    painter.drawEllipse(widgetFrame);
    painter.drawEllipse(outsideCircleFrame);
    painter.drawEllipse(insideCircleFrame);

}
