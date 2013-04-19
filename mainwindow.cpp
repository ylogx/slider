#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), QDBusMessage(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelPlayer->setText("No Player Found :(");
// * * * Amarok * * *
    QDBusMessage getPlayer=QDBusMessage::createMethodCall("org.kde.amarok",
                                                       "/org/mpris/MediaPlayer2",
                                                       "org.mpris.MediaPlayer2",
                                                       "Identity");
    bool amarokReplied=QDBusConnection::sessionBus().send(getPlayer);
    //QDBusMessage responseAmarok=QDBusConnection::sessionBus().call(getPlayer);
    //qDebug()<<"response: "<<responseAmarok;
    if(amarokReplied){
        ui->labelPlayer->setText("Amarok");
        ui->comboBox->addItem("Amarok");
        connect(ui->pushButtonPlay, SIGNAL(clicked()),
                this, SLOT(pauseMedia()));
        connect(ui->pushButtonNext, SIGNAL(clicked()),
                this, SLOT(nextMedia()));
        connect(ui->pushButtonPrev, SIGNAL(clicked()),
                this, SLOT(prevMedia()));
        connect(ui->checkBoxMute, SIGNAL(toggled(bool)),
                this, SLOT(muteMedia()));
    }
    //qDebug()<<"getPlayer: "<<getPlayer<<" rep: "<<rep;

    //ui->dial->setSliderPosition(cur_vol);
// * * * Juk * * *
    QDBusMessage checkJuk=QDBusMessage::createMethodCall("org.kde.juk",
                                                       "/Player",
                                                       "org.kde.juk.player",
                                                       "status");
    bool jukReplied=QDBusConnection::sessionBus().send(checkJuk);
    //QDBusMessage responseJuk=QDBusConnection::sessionBus().call(checkJuk);
    if(jukReplied){
        //ui->labelPlayer->setText("Amarok");
        ui->comboBox->addItem("Juk");
//        connect(ui->pushButtonPlay, SIGNAL(clicked()),
//                this, SLOT(pauseMedia()));
//        connect(ui->pushButtonNext, SIGNAL(clicked()),
//                this, SLOT(nextMedia()));
//        connect(ui->pushButtonPrev, SIGNAL(clicked()),
//                this, SLOT(prevMedia()));
    }
// * * * GMusicBrowser * * *
    //org.gmusicbrowser /org/mpris/MediaPlayer2
    QDBusMessage checkGMusic=QDBusMessage::createMethodCall("org.gmusicbrowser",
                                                       "/org/mpris/MediaPlayer2",
                                                       "org.mpris.MediaPlayer2",
                                                       "Identity");
    bool gmusicReplied=QDBusConnection::sessionBus().send(checkGMusic);
    if(gmusicReplied){
        //ui->labelPlayer->setText("Amarok");
        ui->comboBox->addItem("GMusicBrowser");
//        connect(ui->pushButtonPlay, SIGNAL(clicked()),
//                this, SLOT(pauseMedia()));
//        connect(ui->pushButtonNext, SIGNAL(clicked()),
//                this, SLOT(nextMedia()));
//        connect(ui->pushButtonPrev, SIGNAL(clicked()),
//                this, SLOT(prevMedia()));
    }
}//end constructor

MainWindow::~MainWindow()
{
    delete ui;
}//end destructor

//***********SLOTS************
void MainWindow::pauseMedia(){
    //QDBusConnection bus = QDBusConnection::sessionBus();
    //qtdbus org.kde.amarok /Player org.freedesktop.MediaPlayer.Pause
    QDBusMessage message= QDBusMessage::createMethodCall("org.kde.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    bool queued=QDBusConnection::sessionBus().send(message);
}
void MainWindow::nextMedia(){
    char str[20]="Next";
    QDBusMessage message= QDBusMessage::createMethodCall("org.kde.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player",str);
    //qDebug()<<str<<" mess: "<<message;
    bool queued=QDBusConnection::sessionBus().send(message);
}
void MainWindow::prevMedia(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.kde.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","Previous");
    bool queued=QDBusConnection::sessionBus().send(message);
    //qDebug()<<" mess: "<<message;
}
void MainWindow::muteMedia(){
    // XXX working
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.kde.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Muted");
    QDBusMessage volumeAmarok=QDBusConnection::sessionBus().call(getVolume);
    //bool queued=QDBusConnection::sessionBus().send(getVolume);
    qDebug()<<"volume: "<<volumeAmarok;
    //ui->checkBoxMute->set
}
