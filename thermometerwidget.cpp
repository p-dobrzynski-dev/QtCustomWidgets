#include "thermometerwidget.h"

# include <QPainter>
# include <QDebug>
# include <QTextDocument>
# include <QAbstractTextDocumentLayout>


ThermometerWidget::ThermometerWidget(QWidget *parent) : QWidget(parent)
{

}

void ThermometerWidget:: resizeEvent(QResizeEvent *){

    // Making widget aspect ratio 1:1 (Square)
    widgetFrame = getFrame(this->size());

    float scaleValue = 0.1;
    QSizeF topTankRectSize = QSizeF(widgetFrame.width()*scaleValue, widgetFrame.height());
    topTankRect.setSize(topTankRectSize);

    QPointF topTankPoint = QPointF(widgetFrame.center().x() - widgetFrame.width()*scaleValue/2, widgetFrame.top());
    topTankRect.moveTopLeft(topTankPoint);

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
    this->repaint();
}

int ThermometerWidget::getValue() {
    return value;
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

    // Drawing thermometer value
    QFont font = painter.font();
    font.setPointSize(widgetFrame.height()/10);
    QFontMetrics fm(font);
    int textHeight = fm.height();
    painter.setFont(font);
    painter.drawText(QPointF(widgetFrame.center().x() - widgetFrame.width()/2,topTankRect.topRight().y()+textHeight), QString("%1°C").arg(QString::number(value,'f',1)));

    // Drawing lines
    pen.setWidth(widgetFrame.width()/100);
    painter.setPen(pen);

    int numberOfLines = (maxValue - minValue) / 10;

    float lineInterval = topTankRect.height()/numberOfLines;

    for (int i = 1; i < numberOfLines; i++) {

        if (i == 6) {
            pen.setWidth(widgetFrame.width()/50);
            painter.setPen(pen);
        } else {
            pen.setWidth(widgetFrame.width()/100);
            painter.setPen(pen);
        }
        QPointF lineBegining = QPointF(topTankRect.center().x()-topTankRect.width()/1.5,widgetFrame.top() + lineInterval * i);
        QPointF lineEnding = QPointF(topTankRect.center().x()+topTankRect.width()/1.5,widgetFrame.top() + lineInterval * i);
        QLineF line =  QLineF(lineBegining,lineEnding);
        painter.drawLine(line);
        painter.drawText(QPointF(lineEnding.x()+widgetFrame.width()/20,lineEnding.y()),QString("%1").arg(maxValue - 10*i));
    }

}
