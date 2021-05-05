#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    system_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//系统初始化函数
void MainWindow::system_init(){
    ui->lcd_vout->display("00.00");
    ui->lcd_iout->display("00.00");
    ui->lcd_pout->display("00.00");
    //port config
    global_port.setParity(QSerialPort::NoParity);
    global_port.setDataBits(QSerialPort::Data8);
    global_port.setStopBits(QSerialPort::OneStop);



}

//槽函数
void MainWindow::on_btn_output_clicked()
{

}

void MainWindow::on_btn_connect_clicked()
{
    /*--------------printf-----------------*/
       qDebug() << ui->cmb_port_name->currentText();
    /* ------------port--------------------*/
       global_port.setPortName(ui->cmb_port_name->currentText());
    /*------------baud rate------------------*/
       switch(ui->cmb_baud_rate->currentIndex()){
       case 0:
           global_port.setBaudRate(QSerialPort::Baud115200);
           break;
       case 1:
           global_port.setBaudRate(QSerialPort::Baud57600);
           break;
       case 2:
           global_port.setBaudRate(QSerialPort::Baud38400);
           break;
       case 3:
           global_port.setBaudRate(QSerialPort::Baud19200);
           break;
       case 4:
           global_port.setBaudRate(QSerialPort::Baud9600);
           break;
       case 5:
           global_port.setBaudRate(QSerialPort::Baud2400);
           break;
       case 6:
           global_port.setBaudRate(QSerialPort::Baud1200);
           break;
       default:
           break;
       }

       //open
       if(global_port.open(QIODevice::ReadWrite)!=false){
           ui->btn_connect->setFlat(1);
           qDebug() << "COM OPEN";
       }else{

           qDebug() << "COM OPEN Fail";
       }
       //ui->lab_status->setText("Connected");
       //test
       //global_port.write("1");

}

void MainWindow::on_btn_flash_clicked()
{
    QStringList list_avail_sp;
    ui ->cmb_port_name ->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        char i=0;
        if (serial.open(QIODevice::ReadWrite))
        {
            list_avail_sp.append(serial.portName());
            ui ->cmb_port_name ->insertItem(i,serial.portName());
            serial.close();
            i++;
        }
    }
    qDebug() << list_avail_sp;

//    ui ->cmb_port_name ->setItemText(0,"list_avail_sp");
}



void MainWindow::on_btn_disconnect_clicked()
{
    global_port.close();
    ui->btn_connect->setFlat(0);
    qDebug() << "COM CLOSE";
}

void MainWindow::on_dial_vout_actionTriggered(int action)
{
      //ui->lab_vset->setFont();
      ui->lab_vset->setNum(ui->dial_vout->value());

}
