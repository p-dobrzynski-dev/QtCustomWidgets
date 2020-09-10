#ifndef TACHOMETERWIDGET_H
#define TACHOMETERWIDGET_H

#include <QWidget>
#include <widgetengine.h>

class TachometerWidget :public WidgetEngine
{
    Q_OBJECT
public:
    TachometerWidget(QWidget *parent = nullptr);
private:

    QRectF widgetFrame;
    QRectF innerArcFrame;
    QRectF tipCircleFrame;
    QRectF tipFrame;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void validateValue(float newValue) override;
};

#endif // TACHOMETERWIDGET_H
