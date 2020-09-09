#include "batterywidget.h"

#include <QPainter>
#include <QDebug>

BatteryWidget::BatteryWidget(QWidget *parent) :
    QWidget(parent)
{

}

void BatteryWidget::resizeEvent(QResizeEvent *)
{
    // Making widget aspect ratio 2:1 (Rectangle)
    widgetFrame = getFrame(this->size());

    widgetFrame.setSize(QSize(widgetFrame.width(),widgetFrame.height()/2));
    widgetFrame.moveTop(widgetFrame.center().y());

    float scaleValue = 0.95;
    QSizeF mainBatteryFrameSize = QSizeF(widgetFrame.width()*scaleValue,widgetFrame.height());
    mainBatteryFrame.setSize(mainBatteryFrameSize);

    mainBatteryFrame.moveTopLeft(widgetFrame.topLeft());

    QSizeF tipBatteryFrameSize = QSizeF(widgetFrame.width()/3,widgetFrame.height()/2);
    tipBatteryFrame.setSize(tipBatteryFrameSize);

    QPointF tipBatteryFramePoint = QPointF(widgetFrame.topRight().x()-tipBatteryFrameSize.width(), widgetFrame.topRight().y()+tipBatteryFrameSize.height()/2);
    tipBatteryFrame.moveTopLeft(tipBatteryFramePoint);


    float batteryLevelOffset = mainBatteryFrame.height()/20;
    QSizeF batteryLevelFrameSize = QSizeF(mainBatteryFrame.width() - 2*batteryLevelOffset, mainBatteryFrame.height() - 2*batteryLevelOffset);
    batteryLevelFrame.setSize(batteryLevelFrameSize);

    QPointF batteryFramePoint = QPointF(mainBatteryFrame.topLeft().x() + batteryLevelOffset,mainBatteryFrame.topLeft().y() + batteryLevelOffset);
    batteryLevelFrame.moveTopLeft(batteryFramePoint);
}

void BatteryWidget::setValue(int newValue){
    if (newValue >= maxValue){
        value = maxValue;
    }
    else if (newValue <= minValue) {
        value = minValue;
    }
    else{
        value = newValue;
    }
    this->update();
    this->repaint();
}

int BatteryWidget::getValue() {
    return value;
}

void BatteryWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen = QPen(Qt::red);
    QBrush brush = QBrush(Qt::white);

    painter.setPen(pen);

//    // Delete this in the end
//    painter.drawRect(widgetFrame);
//    //


    //Drawing battery frame

    float widgetCorner = widgetFrame.height()/15;

    QPainterPath FramePath;
    FramePath.setFillRule(Qt::WindingFill);
    FramePath.addRoundedRect(mainBatteryFrame,widgetCorner, widgetCorner);
    FramePath.addRoundedRect(tipBatteryFrame, widgetCorner,widgetCorner);
    FramePath = FramePath.simplified();

    pen.setColor(Qt::gray);
    pen.setWidth(widgetFrame.width()/75);
    painter.setPen(pen);
    painter.drawPath(FramePath);

    painter.setBrush(QBrush(QColor("#44bd32")));
    painter.setPen(Qt::NoPen);
    QRectF batteryLevelRect = QRectF();
    QSize batterySizeRect = QSize(batteryLevelFrame.width() * value/maxValue, batteryLevelFrame.height());
    batteryLevelRect.setSize(batterySizeRect);
    batteryLevelRect.moveTo(batteryLevelFrame.topLeft());
    painter.drawRoundedRect(batteryLevelRect, widgetCorner,widgetCorner);

    pen.setColor(Qt::white);
    painter.setPen(pen);
    textFont.setPixelSize(widgetFrame.height()/3);
    painter.setFont(textFont);
    QFontMetricsF fm(textFont);
    QString percentageLevelString = QString("%1%").arg(value);
    float textWidth = fm.width(percentageLevelString);
    float textHeight = fm.height();

    QPointF textPosition = QPointF(widgetFrame.center().x()-textWidth/2,widgetFrame.center().y()+textHeight/3);

    painter.drawText(textPosition, percentageLevelString);
    }
