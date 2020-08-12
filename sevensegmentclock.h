#ifndef SEVENSEGMENTCLOCK_H
#define SEVENSEGMENTCLOCK_H

#include <QWidget>

class SevenSegmentClock : public QWidget
{
    Q_OBJECT
public:
    explicit SevenSegmentClock(QWidget *parent = nullptr);
private:
    QRectF widgetFrame;
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);
    QPointF getWidgetFrameOffset(QSizeF);

    QList<QRectF> getSingleSegment(QRectF forRect);
    QList<QRectF> calculateRectsForSegments();

signals:

};

#endif // SEVENSEGMENTCLOCK_H
