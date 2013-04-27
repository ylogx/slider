#include <QtGui>

#include "inheritedslider.h"

InheritedSlider::InheritedSlider(QWidget *parent)
    : QSlider(parent)
{
}

InheritedSlider::InheritedSlider(Qt::Orientation orientation, QWidget *parent)
    :QSlider(orientation,parent)
{
}
void InheritedSlider::paintEvent(QPaintEvent *event)
{
    QSlider::paintEvent(event);
    // uncomment to draw the parent first. Comment out to just ignore it.
    //QSlider::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //painter.translate(width() / 2, height() / 2);
    //painter.scale(100 / 200.0, 100 / 200.0);

    QPainterPath volPath;
    volPath.moveTo(60.0, 40.0);
    volPath.arcTo(20.0, 20.0, 40.0, 40.0, 0.0, 360.0);
    volPath.moveTo(40.0, 40.0);
    volPath.lineTo(40.0, 80.0);
    volPath.lineTo(80.0, 80.0);
    volPath.lineTo(80.0, 40.0);
    volPath.closeSubpath();
    painter.drawPath(volPath);
}
