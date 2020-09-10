#include "thermometerwidget.h"

# include <QPainter>
# include <QDebug>
# include <QTextDocument>
# include <QAbstractTextDocumentLayout>


ThermometerWidget::ThermometerWidget(QWidget *)
{
    minValue = -20;
    maxValue = 60;
}

void ThermometerWidget:: resizeEvent(QResizeEvent *){

    // Making widget aspect ratio 1:1 (Square)
    widgetFrame = getFrame();

    float scaleValue = 0.1;
    QSizeF topTankRectSize = QSizeF(widgetFrame.width()*scaleValue, widgetFrame.height());
    tankRect.setSize(topTankRectSize);

    QPointF topTankPoint = QPointF(widgetFrame.center().x() - widgetFrame.width()*scaleValue/2, widgetFrame.top());
    tankRect.moveTopLeft(topTankPoint);

}

void ThermometerWidget::validateValue(float newValue) {
    if ((newValue >= minValue) && (newValue <=maxValue)){
        value = newValue;
    } else if (newValue < minValue) {
        value = minValue;
    } else if (newValue > maxValue) {
        value = maxValue;
    } else {
        return;
    }
}

void ThermometerWidget:: paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);
    QBrush brush = QBrush(Qt::white);

    painter.setPen(pen);

    float cornerRadius = widgetFrame.width()/60;

    // Infill Path
    QPainterPath infillPath;
    QRectF infillRect = QRectF(tankRect);

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
    painter.drawRect(tankRect);


    QPainterPath path;
    path.addRoundedRect(tankRect, cornerRadius,cornerRadius);

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
    painter.drawText(QPointF(widgetFrame.center().x() - widgetFrame.width()/2,tankRect.topRight().y()+textHeight), QString("%1°C").arg(QString::number(value,'f',1)));

    // Drawing lines
    pen.setWidth(widgetFrame.width()/100);
    painter.setPen(pen);

    int numberOfLines = (maxValue - minValue) / 10;

    float lineInterval = tankRect.height()/numberOfLines;

    for (int i = 1; i < numberOfLines; i++) {

        if (i == 6) {
            pen.setWidth(widgetFrame.width()/50);
            painter.setPen(pen);
        } else {
            pen.setWidth(widgetFrame.width()/100);
            painter.setPen(pen);
        }
        QPointF lineBegining = QPointF(tankRect.center().x()-tankRect.width()/1.5,widgetFrame.top() + lineInterval * i);
        QPointF lineEnding = QPointF(tankRect.center().x()+tankRect.width()/1.5,widgetFrame.top() + lineInterval * i);
        QLineF line =  QLineF(lineBegining,lineEnding);
        painter.drawLine(line);
        painter.drawText(QPointF(lineEnding.x()+widgetFrame.width()/20,lineEnding.y()),QString("%1").arg(maxValue - 10*i));
    }

}
