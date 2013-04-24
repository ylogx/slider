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
    ui->checkBoxMute->setChecked(false);    // XXX
    //ui->dial->scroll(1,1);
    checkAvailablePlayer();
    connect(ui->comboBox, SIGNAL(activated(int)),// SIGNAL(currentIndexChanged(int)),
            this, SLOT(reconnect()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(reconnect()));
}//end constructor

MainWindow::~MainWindow()
{
    delete ui;
}//end destructor

void MainWindow::reconnect(){
    ui->pushButtonPlay->disconnect();
    ui->pushButtonNext->disconnect();
    ui->pushButtonPrev->disconnect();
    ui->pushButtonShow->disconnect();
    ui->checkBoxMute->disconnect();

    if(ui->comboBox->currentText()=="Amarok"){
        connectAmarok();
    }else if(ui->comboBox->currentText()=="Clementine"){
        connectClementine();
    }else if(ui->comboBox->currentText()=="Audacious"){
        connectAudacious();
    }
}

void MainWindow::connectAmarok(){
    ui->labelPlayer->setText("Amarok");
    connect(ui->pushButtonPlay, SIGNAL(clicked()),
            this, SLOT(pauseAmarok()));
    connect(ui->pushButtonNext, SIGNAL(clicked()),
            this, SLOT(nextAmarok()));
    connect(ui->pushButtonPrev, SIGNAL(clicked()),
            this, SLOT(prevAmarok()));
    connect(ui->checkBoxMute, SIGNAL(stateChanged(int)),
            this, SLOT(muteAmarok()));
    connect(ui->pushButtonShow, SIGNAL(clicked()),
            this, SLOT(showAmarok()));
}
void MainWindow::connectClementine(){
    ui->labelPlayer->setText("Clementine");
    connect(ui->pushButtonPlay, SIGNAL(clicked()),
            this, SLOT(pauseClementine()));
    connect(ui->pushButtonNext, SIGNAL(clicked()),
            this, SLOT(nextClementine()));
    connect(ui->pushButtonPrev, SIGNAL(clicked()),
            this, SLOT(prevClementine()));
    connect(ui->checkBoxMute, SIGNAL(stateChanged(int)),
            this, SLOT(muteClementine()));
    connect(ui->pushButtonShow, SIGNAL(clicked()),
            this, SLOT(showClementine()));
}
void MainWindow::connectAudacious(){
    ui->labelPlayer->setText("Audacious");
    connect(ui->pushButtonPlay, SIGNAL(clicked()),
            this, SLOT(pauseAudacious()));
    connect(ui->pushButtonNext, SIGNAL(clicked()),
            this, SLOT(nextAudacious()));
    connect(ui->pushButtonPrev, SIGNAL(clicked()),
            this, SLOT(prevAudacious()));
    connect(ui->checkBoxMute, SIGNAL(toggled(bool muteState)),
            this, SLOT(muteAudacious(muteState)));
    connect(ui->pushButtonShow, SIGNAL(clicked()),
            this, SLOT(showAudacious()));
}
void MainWindow::checkAvailablePlayer(){
    QDBusConnection bus=QDBusConnection::sessionBus();
// * * * Amarok * * *
    QDBusInterface *interface=new QDBusInterface("org.mpris.amarok",
                                                 "/org/mpris/MediaPlayer2",
                                                 "org.freedesktop.DBus.Introspectable",
                                                 bus);
    QDBusReply<QString> amarokReply= interface->call("Introspect");
    if(amarokReply.isValid()){
        ui->comboBox->addItem("Amarok");
        connectAmarok();    //by default
    }
    //amarok::checkAvailable();
// * * * Audacious * * *
    interface=new QDBusInterface("org.mpris.audacious",
                                 "/Player",
                                 "org.freedesktop.DBus.Introspectable",
                                 bus,
                                 this);
    QDBusReply<QString> audaciousReply= interface->call("Introspect");
    if(audaciousReply.isValid()){
        ui->comboBox->addItem("Audacious");
    }
// * * * Clementine * * *
    interface=new QDBusInterface("org.mpris.clementine",
                                 "/Player",
                                 "org.freedesktop.DBus.Introspectable",
                                 bus,
                                 this);
    QDBusReply<QString> clementineReply= interface->call("Introspect");
    if(clementineReply.isValid()){
        ui->comboBox->addItem("Clementine");

    }
// * * * Decibel Audio Player * * *
    interface=new QDBusInterface("org.mpris.dap",
                                 "/Player",
                                 "org.freedesktop.DBus.Introspectable",
                                 bus,
                                 this);
    QDBusReply<QString> dapReply= interface->call("Introspect");
    if(dapReply.isValid()){
        ui->comboBox->addItem("Decibel Audio Player (dap)");
    }
// * * * Dragon Player * * *
    //! XXX changing process-id here
    interface=new QDBusInterface("org.mpris.dragonplayer-15134",
                                 "/Player",
                                 "org.freedesktop.DBus.Introspectable",
                                 bus,
                                 this);
    QDBusReply<QString> dragonReply= interface->call("Introspect");
    if(dragonReply.isValid()){
        ui->comboBox->addItem("Dragon Player");
    }
// * * * Juk * * *
    interface=new QDBusInterface("org.kde.juk",
                                  "/Player",
                                  "org.freedesktop.DBus.Introspectable",
                                  bus,
                                  this);
    QDBusReply<QString> jukReply= interface->call("Introspect");
    if(jukReply.isValid()){
        ui->comboBox->addItem("Juk");
    }
}//end checkAvailable

//****************************
//***********SLOTS************
//****************************
//---------------------Amarok-----------------------
void MainWindow::pauseAmarok(){
    //QDBusConnection bus = QDBusConnection::sessionBus();
    //qtdbus org.kde.amarok /Player org.freedesktop.MediaPlayer.Pause
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    bool queued=QDBusConnection::sessionBus().send(message);
}
void MainWindow::nextAmarok(){
    char str[20]="Next";
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player",str);
    //qDebug()<<str<<" mess: "<<message;
    bool queued=QDBusConnection::sessionBus().send(message);
}
void MainWindow::prevAmarok(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.kde.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","Previous");
    bool queued=QDBusConnection::sessionBus().send(message);
    //qDebug()<<" mess: "<<message;
}
void MainWindow::muteAmarok(){
    // XXX working
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer","Mute");
    QDBusMessage volumeAmarok=QDBusConnection::sessionBus().call(getVolume);
    //bool queued=QDBusConnection::sessionBus().send(getVolume);
    qDebug()<<"volume: "<<volumeAmarok;
    //ui->checkBoxMute->set
}
void MainWindow::showAmarok(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.amarok",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Raise");
    bool queued=QDBusConnection::sessionBus().send(message);
}

//---------------------Clementine-----------------------
void MainWindow::pauseClementine(){
    //QDBusConnection bus = QDBusConnection::sessionBus();
    //qtdbus org.kde.amarok /Player org.freedesktop.MediaPlayer.Pause
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    bool queued=QDBusConnection::sessionBus().send(message);
}
void MainWindow::nextClementine(){
    char str[20]="Next";
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player",str);
    //qDebug()<<str<<" mess: "<<message;
    bool queued=QDBusConnection::sessionBus().send(message);
}
void MainWindow::prevClementine(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","Previous");
    bool queued=QDBusConnection::sessionBus().send(message);
    //qDebug()<<" mess: "<<message;
}
void MainWindow::muteClementine(){
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer","Mute");
    bool queued=QDBusConnection::sessionBus().send(getVolume);
}
void MainWindow::showClementine(){
    // xxx not supported
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.clementine",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Raise");
    bool queued=QDBusConnection::sessionBus().send(message);
}


//--------------Audacious-----------------------------------
void MainWindow::pauseAudacious(){
    //QDBusConnection bus = QDBusConnection::sessionBus();
    //qtdbus org.kde.amarok /Player org.freedesktop.MediaPlayer.Pause
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.MediaPlayer2.audacious",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2.Player","PlayPause");
    bool queued=QDBusConnection::sessionBus().send(message);
    //qDebug()<<"pause mess:"<<message;
}
void MainWindow::nextAudacious(){
    char str[20]="Next";
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.audacious",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer",str);
    //qDebug()<<str<<" mess: "<<message;
    bool queued=QDBusConnection::sessionBus().send(message);
}
void MainWindow::prevAudacious(){
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.audacious",
                                                         "/Player",
                                                         "org.freedesktop.MediaPlayer","Prev");
    bool queued=QDBusConnection::sessionBus().send(message);
    //qDebug()<<" mess: "<<message;
}
void MainWindow::muteAudacious(bool muteState){
    // XXX working
    QDBusMessage getVolume= QDBusMessage::createMethodCall("org.mpris.audacious",
                                                           "/Player",
                                                           "org.freedesktop.MediaPlayer","VolumeSet");

    QList<QVariant> args;
    if(muteState){
        args<<0;
    }
    getVolume.setArguments(args);
    //QDBusMessage volumeAmarok=QDBusConnection::sessionBus().call(getVolume);
    bool queued=QDBusConnection::sessionBus().send(getVolume);
    //qDebug()<<"volume: "<<volumeAmarok;
    //ui->checkBoxMute->set
}
void MainWindow::showAudacious(){
    //ui->pushButtonShow->setText("Can't Raise");
    QDBusMessage message= QDBusMessage::createMethodCall("org.mpris.MediaPlayer2.audacious",
                                                         "/org/mpris/MediaPlayer2",
                                                         "org.mpris.MediaPlayer2","Raise");
    bool queued=QDBusConnection::sessionBus().send(message);
    qDebug()<<"raise mess: "<<message;
    //    QDBusMessage m= QDBusMessage::createMethodCall("org.mpris.amarok",
    //                                                   "/org/mpris/MediaPlayer2",
    //                                                   "org.mpris.MediaPlayer2.Player","SetPosition");
    //    QList<QVariant> args;     // QList of QVariant objects
    //    args.append(7);
    //    args.append(30);
    //    m.setArguments(args);     //can also use overloaded << directly
    //    bool queued=QDBusConnection::sessionBus().send(m);
    //    qDebug()<<queued<<" mess: "<<m;
    //    QDBusMessage m= QDBusMessage::createMethodCall("org.mpris.amarok",
    //                                                   "/Tracklist",
    //                                                   "org.freedesktop.MediaPlayer","GetLength");//"GetCurrentTrack");
    //    QDBusReply<int> response=QDBusConnection::sessionBus().call(m);
    //    qDebug()<<" mess: "<<response;
    //    QList<QVariant> list=response.arguments(); //QDBusMessage::arguments();
    //    qDebug()<<"0: "<<list[0].toInt();
}
