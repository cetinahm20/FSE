#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>





void MainWindow::writeData(){



    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    out<< telemetri.bas1<<telemetri.bas2<<telemetri.yuk1<<telemetri.yuk2<< telemetri.fark<< telemetri.hiz
       <<telemetri.sic<<telemetri.ger<<telemetri.lat<<telemetri.lon<<telemetri.alt<<telemetri.pitch
       <<telemetri.roll<<telemetri.yaw << telemetri.pakNo <<telemetri.takNo<<telemetri.hataKodu
       <<telemetri.state;
    QHostAddress receiverAddress("192.168.1.104");

    socket2->writeDatagram(data,data.size(),receiverAddress, 5005);
}

void MainWindow::readData(){

    while (socket->hasPendingDatagrams()) {
         QByteArray datagram;
         datagram.resize(socket->pendingDatagramSize());
         socket->readDatagram(datagram.data(), datagram.size());

         int ayr = datagram.toInt();

            qDebug()<< QString::number(ayr);

     }


}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL (timeout()),this,SLOT(timerFunc()));


    socket = new QUdpSocket(this);

    socket->bind(QHostAddress::Any, 5010);

    socket2 = new QUdpSocket(this);

    socket2->bind(QHostAddress::Any, 5005);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_toggled(bool checked)
{
    if(checked==true){

  ui->pushButton->setText("Durdur");


   timer->start(1000);


    }

 else{

        ui->pushButton->setText("Başlat");
        timer->stop();


    }
}







void MainWindow::timerFunc(){



        telemetri.zaman= QDateTime::currentSecsSinceEpoch();
        telemetri.pakNo+=1;
        telemetri.bas1+=1;
        telemetri.bas2+=1;
        telemetri.yuk1+=1;
        telemetri.yuk2+=1;
        telemetri.fark+=2.1;
        telemetri.hiz-= 0.5;
        telemetri.sic+= 0.3;
        telemetri.lat+=1;
        telemetri.lon+=1;
        telemetri.alt+=1;
        telemetri.pitch+=1;
        telemetri.roll+=1;
        telemetri.yaw+=1;


        writeData();
        readData();

}
