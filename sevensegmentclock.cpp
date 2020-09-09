#include "sevensegmentclock.h"

#include <QPainter>
#include <QDebug>

SevenSegmentClock::SevenSegmentClock(QWidget *parent) : QWidget(parent)
{

}

void SevenSegmentClock::resizeEvent(QResizeEvent *) {
    // Making widget aspect ratio 1:1 (Square)
    widgetFrame = getFrame(this->size());
}


void SevenSegmentClock::setValue(int newValue){
    qDebug() << newValue << "WIDGET";
    if (0 <= newValue && newValue <= 9999) {
        value = newValue;
    } else if (newValue < 0){
        value = 0;
    } else if (newValue > 9999) {
        value = 9999;
    }
    this->update();
    this->repaint();
}

int SevenSegmentClock::getValue() {
    return value;
}

void SevenSegmentClock:: paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);
    QBrush brush = QBrush(Qt::white);

    painter.setPen(pen);
    painter.setBrush(brush);

    QList <QRectF> segmentsRects = calculateRectsForSegments();
    QList<int> digits = getListOfSingleDigitsFrom(value);

    for( int i=0; i<segmentsRects.count(); ++i )
    {
        QList <QRectF> singleSegment = getSingleSegment(segmentsRects[i], digits[i]);
        painter.setBrush(QBrush(Qt::green));
        painter.setBrush(QBrush(Qt::red));
        foreach(QRectF segment, singleSegment) {
            painter.drawRect(segment);
        }
    }

}

QList<int> SevenSegmentClock::getListOfSingleDigitsFrom(int number) {
    QList<int> listOfDigits = QList<int>();
    int tempNum;
    for (int i = 0; i<4; i++) {
        tempNum = number%10;
        number = number/10;
        listOfDigits.append(tempNum);
    }

    // Reversing list of digits
    for(int k = 0; k < (listOfDigits.size()/2); k++) listOfDigits.swap(k,listOfDigits.size()-(1+k));
    return listOfDigits;
}

QList<QRectF> SevenSegmentClock::calculateRectsForSegments(){

    float spacing = widgetFrame.width()/20;

    float singleClockWidth = (widgetFrame.width() - 3 * spacing) / 4;
    float singleClockHeight = (widgetFrame.height() / 2);

    QList<QRectF> listOfRects = QList<QRectF>();

    for (int i = 0; i< 4; i++) {
        QRectF tempRect = QRectF(QPointF(widgetFrame.left() + (singleClockWidth + spacing) * i, widgetFrame.topLeft().y()+singleClockHeight/2), QSize(singleClockWidth, singleClockHeight));
        listOfRects.append(tempRect);
    }
    return listOfRects;
}

QList<QRectF> SevenSegmentClock::getSingleSegment(QRectF forRect, int number){
    QList <QRectF> tempRects = QList<QRectF>();

    float segmentWidth = widgetFrame.width()/20;

    float segmentVHeight = (forRect.height() - 3 * segmentWidth) / 2;

    QRectF ASegment = QRectF(forRect.topLeft(), QSize(forRect.width(),segmentWidth));
    QRectF BSegment = QRectF(QPoint(forRect.topRight().x()-segmentWidth, forRect.topRight().y()+segmentWidth), QSize(segmentWidth,segmentVHeight));
    QRectF CSegment = QRectF(QPoint(forRect.topRight().x()-segmentWidth, forRect.topRight().y()+segmentWidth*2+segmentVHeight), QSize(segmentWidth,segmentVHeight));
    QRectF DSegment = QRectF(QPoint(forRect.bottomLeft().x(), forRect.bottomLeft().y()-segmentWidth), QSize(forRect.width(),segmentWidth));
    QRectF ESegment = QRectF(QPoint(forRect.left(), forRect.top()+segmentWidth*2+segmentVHeight), QSize(segmentWidth,segmentVHeight));
    QRectF FSegment = QRectF(QPoint(forRect.left(), forRect.top()+segmentWidth), QSize(segmentWidth,segmentVHeight));
    QRectF GSegment = QRectF(QPoint(forRect.left(), forRect.top()+segmentWidth+segmentVHeight), QSize(forRect.width(),segmentWidth));

    switch (number) {
    case 0:
        tempRects.append(ASegment);
        tempRects.append(BSegment);
        tempRects.append(CSegment);
        tempRects.append(DSegment);
        tempRects.append(ESegment);
        tempRects.append(FSegment);
        break;
    case 1:
        tempRects.append(BSegment);
        tempRects.append(CSegment);
        break;
    case 2:
        tempRects.append(ASegment);
        tempRects.append(BSegment);
        tempRects.append(GSegment);
        tempRects.append(ESegment);
        tempRects.append(DSegment);
        break;
    case 3:
        tempRects.append(ASegment);
        tempRects.append(BSegment);
        tempRects.append(GSegment);
        tempRects.append(CSegment);
        tempRects.append(DSegment);
        break;
    case 4:
        tempRects.append(FSegment);
        tempRects.append(BSegment);
        tempRects.append(GSegment);
        tempRects.append(CSegment);
        break;
    case 5:
        tempRects.append(ASegment);
        tempRects.append(FSegment);
        tempRects.append(GSegment);
        tempRects.append(CSegment);
        tempRects.append(DSegment);
        break;
    case 6:
        tempRects.append(ASegment);
        tempRects.append(FSegment);
        tempRects.append(GSegment);
        tempRects.append(CSegment);
        tempRects.append(DSegment);
        tempRects.append(ESegment);
        break;
    case 7:
        tempRects.append(ASegment);
        tempRects.append(BSegment);
        tempRects.append(CSegment);
        break;
    case 8:
        tempRects.append(ASegment);
        tempRects.append(BSegment);
        tempRects.append(CSegment);
        tempRects.append(DSegment);
        tempRects.append(ESegment);
        tempRects.append(FSegment);
        tempRects.append(GSegment);
        break;
    case 9:
        tempRects.append(ASegment);
        tempRects.append(BSegment);
        tempRects.append(CSegment);
        tempRects.append(DSegment);
        tempRects.append(FSegment);
        tempRects.append(GSegment);
        break;
    default:
        //jakiś kod
        break;
    }

    return tempRects;

}
