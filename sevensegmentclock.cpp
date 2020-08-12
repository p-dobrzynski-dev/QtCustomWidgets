#include "sevensegmentclock.h"

#include <QPainter>
#include <QDebug>

SevenSegmentClock::SevenSegmentClock(QWidget *parent) : QWidget(parent)
{

}

void SevenSegmentClock::resizeEvent(QResizeEvent *) {
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
}

QPointF SevenSegmentClock:: getWidgetFrameOffset(QSizeF widSize){
    float xOffset = this->width()/2-widSize.width()/2;
    float yOffset = this->height()/2-widSize.height()/2;

    return QPointF(xOffset,yOffset);
}

void SevenSegmentClock:: paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);
    QBrush brush = QBrush(Qt::white);

    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(widgetFrame);

    QList <QRectF> segmentsRects = calculateRectsForSegments();

    foreach(QRectF rect, segmentsRects) {
        painter.drawRect(rect);
    }

}

QList<QRectF> SevenSegmentClock::calculateRectsForSegments(){

    float spacing = widgetFrame.width()/20;

    float singleClockWidth = (widgetFrame.width() - 3 * spacing) / 4;
    float singleClockHeight = (widgetFrame.height() / 2);

    QList<QRectF> listOfRects = QList<QRectF>();

    for (int i = 0; i< 4; i++) {
        QRectF tempRect = QRectF(QPointF((singleClockWidth+ spacing) * i, widgetFrame.topLeft().y()+singleClockHeight/2), QSize(singleClockWidth, singleClockHeight));
        listOfRects.append(tempRect);
    }
    return listOfRects;
}

QList<QRectF> SevenSegmentClock::getSingleSegment(QRectF forRect){
    QList <QRectF> tempRects = QList<QRectF>();

    QRectF firstSegment = QRectF(forRect.topLeft(), QSize(forRect.width(),50));
    tempRects.append(firstSegment);

//    QRectF secondSegment = QRectF(forRect.topLeft(), QSize(forRect.width(),10));
    return tempRects;

}
