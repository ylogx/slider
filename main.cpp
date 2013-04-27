#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>

#include "inheritedslider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("QSlider { height: 30px}"
                      "QSlider::groove:horizontal {"
                      "border: 1px solid #999999;"
                      "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                      "height: 26px;"
                      "margin: 0 0 0 0;}"
                      "QSlider::handle:horizontal {"
                      "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                      "border: 1px solid #5c5c5c;"
                      "width: 30px;"
                      "margin: -2px 0 -2px 0;"
                      "border-radius: 3px;}");
    InheritedSlider mySlider;
    mySlider.setWindowTitle(QObject::tr("My Slider"));
    mySlider.show();
    QWidget widget;
    QVBoxLayout *layout = new QVBoxLayout;
    QSlider *slider;
    slider = new InheritedSlider(Qt::Horizontal);
//    layout->addWidget(slider,0,Qt::AlignCenter);
//    slider = new QSlider(Qt::Horizontal);
    layout->addWidget(slider, 0, Qt::AlignBottom);
    slider = new QSlider(Qt::Horizontal);
    layout->addWidget(slider, 0, Qt::AlignTop);
    layout->setSpacing(0);
    widget.setLayout(layout);
    widget.show();
    return app.exec();
}
