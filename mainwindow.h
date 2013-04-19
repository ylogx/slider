#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, QDBusMessage
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
public slots:
    void pauseMedia();
    void nextMedia();
    void prevMedia();
    void muteMedia();
};

#endif // MAINWINDOW_H
