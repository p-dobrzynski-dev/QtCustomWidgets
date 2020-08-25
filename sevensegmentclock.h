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

    int value = 0;

    QList<QRectF> getSingleSegment(QRectF forRect, int number);
    QList<QRectF> calculateRectsForSegments();
    QList<int> getListOfSingleDigitsFrom(int number);

public slots:
    void setValue(int);

signals:

};

#endif // SEVENSEGMENTCLOCK_H
