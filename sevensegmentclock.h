#ifndef SEVENSEGMENTCLOCK_H
#define SEVENSEGMENTCLOCK_H

#include <QWidget>
#include <widgetengine.h>

class SevenSegmentClock : public WidgetEngine
{
    Q_OBJECT
public:
    SevenSegmentClock(QWidget *parent = nullptr);
private:
    QRectF widgetFrame;
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void validateValue(float newValue) override;

    QList<QRectF> getSingleSegment(QRectF forRect, int number);
    QList<QRectF> calculateRectsForSegments();
    QList<int> getListOfSingleDigitsFrom(int number);
};

#endif // SEVENSEGMENTCLOCK_H
