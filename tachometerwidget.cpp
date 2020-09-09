#include "tachometerwidget.h"

# include <QPainter>
# include <QDebug>
# include <cmath>

#define PI 3.141592653589793238

TachometerWidget::TachometerWidget(QWidget *parent) :
    QWidget(parent)
{    

}

void TachometerWidget:: resizeEvent(QResizeEvent *){

    // Making widget aspect ratio 1:1 (Square)
    widgetFrame = getFrame(this->size());

    //Setting inner arc rect
    float scaleValue = 0.85;
    QSizeF innerArcSize = QSizeF(widgetFrame.width()*scaleValue,widgetFrame.height()*scaleValue);
    innerArcFrame.setSize(innerArcSize);

    QPointF innerArcOffsetPoint = getWidgetFrameOffset(this->size(), innerArcSize);
    innerArcFrame.moveTopLeft(innerArcOffsetPoint);

    //Setting tip circle rect
    scaleValue = 0.1;
    QSizeF tipCircleSize = QSizeF(widgetFrame.width()*scaleValue,widgetFrame.height()*scaleValue);
    tipCircleFrame.setSize(tipCircleSize);

    QPointF tipCircleOffsetPoint = getWidgetFrameOffset(this->size(), tipCircleSize);
    tipCircleFrame.moveTopLeft(tipCircleOffsetPoint);

    //Setting tip rect
    scaleValue = 0.05;
    QSizeF tipSize = QSizeF(widgetFrame.width()*scaleValue,widgetFrame.height()/3);
    tipFrame.setSize(tipSize);

    QPointF tipOffsetPoint = QPointF(-tipSize.width()/2,-tipSize.height());
    tipFrame.moveTopLeft(tipOffsetPoint);
}



float getRadians(float Degrees){
    float radians = Degrees * PI / 180.;
    return radians;
}

void TachometerWidget::setValue(int newValue){
    if (newValue >= maxValue) {
        value = maxValue;
    } else if (newValue <= minValue) {
        value = minValue;
    }
    else {
        value = newValue;
    }
    this->update();
    this->repaint();
}

void TachometerWidget::setMaxValue(int value){
    maxValue = value;
    this->update();
    this->repaint();
}

int TachometerWidget::getValue() {
    return value;
}

int TachometerWidget::getMaxValue() {
    return maxValue;
}

void TachometerWidget:: paintEvent(QPaintEvent *){

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        QPen pen = QPen(Qt::red);
        QBrush brush = QBrush(Qt::white);

        painter.setPen(pen);

        // Delete this in the end
//        painter.drawRect(widgetFrame);
        //

        //Drawing main circle
        float outPenWidth = widgetFrame.width()/50;

        pen.setWidthF(outPenWidth);
        pen.setColor(Qt::gray);
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.drawEllipse(widgetFrame);


        //Drawing inner arc
        float innerPenWidth = widgetFrame.width()/75;
        pen.setWidthF(innerPenWidth);
        painter.setPen(pen);

        int startAngle = -45 * 16;
        int spanAngle = 270 * 16;
        painter.drawArc(innerArcFrame,startAngle,spanAngle);

        //Drawing tip

        painter.translate(this->width()/2,this->height()/2);
        painter.rotate(value-135);

        // Delete this in the end
//        pen.setColor(Qt::red);
//        pen.setWidth(1);
//        painter.setPen(pen);
//        painter.setBrush(Qt::NoBrush);
//        painter.drawRect(tipFrame);
        //

        QPainterPath tipPath = QPainterPath();
        QPointF tipOfTip = QPointF(tipFrame.left() + tipFrame.width()/2,tipFrame.top());

        QPointF tipPoints[3] = {tipFrame.bottomLeft(),tipOfTip,tipFrame.bottomRight()};

        pen.setColor(Qt::red);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.setBrush(Qt::red);
        painter.drawPolygon(tipPoints,3);
        painter.resetTransform();

        //Drawing tipcicle
        pen.setColor(Qt::NoPen);
        painter.setPen(pen);
        brush.setColor(Qt::black);
        painter.setBrush(brush);
        painter.drawEllipse(tipCircleFrame);

        //Drawing lines and numbers
        pen.setColor(Qt::red);
        painter.setPen(pen);

        int interval = 20;
        int numberOfLines = maxValue/interval;
        double degreesPerLine = double(270)/double(numberOfLines);
        textFont.setPixelSize(widgetFrame.height()/20);
        painter.setFont(textFont);

        for (int i = 0; i<numberOfLines+1; i++){
            float radAngle = getRadians(45-degreesPerLine*i);
            float xEndCoord = innerArcFrame.center().x() + cos(radAngle) * innerArcFrame.width()/2;
            float yEndCoord = innerArcFrame.center().y() + sin(radAngle) * innerArcFrame.width()/2;

            QPointF endCoord = QPointF(xEndCoord,yEndCoord);

            float xBeginCoord;
            float yBeginCoord;

            if (i%2){
                xBeginCoord = innerArcFrame.center().x() + cos(radAngle) * innerArcFrame.width()/2.15;
                yBeginCoord = innerArcFrame.center().y() + sin(radAngle) * innerArcFrame.width()/2.15;
                pen.setWidth(widgetFrame.width()/100);
                pen.setColor(Qt::gray);
                painter.setPen(pen);
                painter.drawLine(QLineF(QPointF(xBeginCoord,yBeginCoord),endCoord));
            }else {
                xBeginCoord = innerArcFrame.center().x() + cos(radAngle) * innerArcFrame.width()/2.3;
                yBeginCoord = innerArcFrame.center().y() + sin(radAngle) * innerArcFrame.width()/2.3;
                pen.setWidth(widgetFrame.width()/75);
                pen.setColor(Qt::gray);
                painter.setPen(pen);
                painter.drawLine(QLineF(QPointF(xBeginCoord,yBeginCoord),endCoord));


                QFontMetricsF fm(textFont);
                float textWidth = fm.width(QString::number(maxValue - i*interval));
                float textHeight = fm.height();

                float textXOffset = innerArcFrame.center().x() + cos(radAngle) * innerArcFrame.width()/2.8 - textWidth/2;
                float textYOffset = innerArcFrame.center().y() + sin(radAngle) * innerArcFrame.width()/2.8 + textHeight/2;

                QPointF textOffsetPoint = QPointF(textXOffset,textYOffset);

                painter.drawText(textOffsetPoint, QString::number(maxValue - i*interval));

            }



        }



        painter.end();
}


