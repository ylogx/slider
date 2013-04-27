#ifndef INHERITEDSLIDER_H
#define INHERITEDSLIDER_H

#include <QSlider>

class InheritedSlider : public QSlider
{
    Q_OBJECT

public:
    InheritedSlider(QWidget* parent=0);// : QSlider();
    InheritedSlider(Qt::Orientation orientation, QWidget *parent=0);
protected:
    void paintEvent(QPaintEvent *event);
private:
};

#endif
