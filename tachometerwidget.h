#ifndef TACHOMETERWIDGET_H
#define TACHOMETERWIDGET_H

#include <QWidget>
#include <widgetengine.h>

class TachometerWidget : public QWidget, public WidgetEngine
{
    Q_OBJECT
public:
    explicit TachometerWidget(QWidget *parent = nullptr);
    int getValue();
    int getMaxValue();
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

public slots:
    void setValue(int);
    void setMaxValue(int);
signals:

};

#endif // TACHOMETERWIDGET_H
