#include "serialreader.h"
#include <QtCore/QCoreApplication>
#include <iostream>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QDebug>
#include <QtSerialPort/QtSerialPort>
#include <string>
#include <QPainter>
#include <QtWidgets>
#include <iterator>
#include <vector>
#include <list>
#include <QtGui>
#include <QWidget>
#include <random>




SerialReader::SerialReader()
{

    point_last.x=0;
    point_last.y=0;
    point.x=5;
    point.y=5;

    std::cout << __FILE__ <<": "<< __LINE__ << std::endl;

    serial.setPortName("ttyUSB0");
    if(!serial.setBaudRate(QSerialPort::Baud9600))
        qDebug() << serial.errorString();
    if(!serial.setDataBits(QSerialPort::Data7))
        qDebug() << serial.errorString();
    if(!serial.setParity(QSerialPort::EvenParity))
        qDebug() << serial.errorString();
    if(!serial.setFlowControl(QSerialPort::HardwareControl))
        qDebug() << serial.errorString();
    if(!serial.setStopBits(QSerialPort::OneStop))
        qDebug() << serial.errorString();
    if(!serial.open(QIODevice::ReadOnly))
        qDebug() << serial.errorString();
    qDebug() << serial.bytesAvailable();

    std::cout << __FILE__ <<": "<< __LINE__ << std::endl;


}



void SerialReader::readingSerial()
{


    QObject::connect(&serial, &QSerialPort::readyRead, [&]
        {
            //this is called when readyRead() is emitted
            qDebug() << "New data available: " << serial.bytesAvailable();
            int counter = serial.bytesAvailable();

            QByteArray datas = serial.readAll();

            for (int i=0; i<counter;i++)
            {
                if (datas[i]&8)
                {
                    std::cout<<"lm"<<std::endl;
                    point.x-=1;
                }
                if (datas[i]&4)
                {
                    std::cout<<"lp"<<std::endl;
                    point.x+=1;
                }
                if (datas[i]&2)
                {
                    std::cout<<"rm"<<std::endl;
                    point.y-=1;
                }
                if (datas[i]&1)
                {
                    std::cout<<"rp"<<std::endl;
                    point.y+=1;
                }
                if (datas[i]&32)
                {
                    std::cout<<"lb"<<std::endl;
                    //myColor = static_cast<Color>(myColor + 1);
                    colorIdx+=1;
                }
                if (datas[i]&16)
                {
                    std::cout<<"rb"<<std::endl;
                    setDoDelete(true);
                }

                if (colorIdx<=17)
                {
                    setMyColor(colorIdx);
                }else{colorIdx=0;}

            }
             emit serialIsReady();
        });
        QObject::connect(&serial,
                         static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                         (&QSerialPort::error),
                         [&](QSerialPort::SerialPortError error)
        {
            //this is called when a serial communication error occurs
            qDebug() << "An error occured: " << error;
            //a.quit();
        });   
}
