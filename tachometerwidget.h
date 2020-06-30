#ifndef TACHOMETERWIDGET_H
#define TACHOMETERWIDGET_H

#include <QWidget>

class TachometerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TachometerWidget(QWidget *parent = nullptr);
private:

    QRectF widgetFrame;
    QRectF innerArcFrame;
    QRectF tipCircleFrame;
    QRectF tipFrame;

    int value = 0;

    int maxValue = 280;
    int minValue = 0;

    QFont textFont = QFont();

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    QPointF getWidgetFrameOffset(QSizeF);

public slots:
    void setValue(int);

signals:

};

#endif // TACHOMETERWIDGET_H
