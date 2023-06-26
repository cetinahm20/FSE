#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#pragma pack(push,1)
typedef struct tTelemetri{

    int pakNo =0;
    unsigned char state = 3;
    unsigned char hataKodu = 0 <<0 | 0<< 1 | 0 << 2| 0 << 3| 0 << 4;
    long long zaman;
    double bas1 =1019.45;
    double bas2 =1010;
    double yuk1 =251;
    double yuk2 = 241;
    double fark = 0.25;
    double hiz =9.81;
    double sic =28.3;
    double ger = 5;
    double lat =41.31;
    double lon =29.08;
    double alt = 431.21;
    double pitch =52;
    double roll = 4.28;
    double yaw =30.3 ;
    int takNo =222558 ;


}Telemetri;
#pragma pack(pop)


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Telemetri telemetri;

private slots:

    void on_pushButton_toggled(bool checked);
    void timerFunc();
    void writeData();
    void readData();


private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QUdpSocket *socket;
    QUdpSocket *socket2;


};
#endif // MAINWINDOW_H
