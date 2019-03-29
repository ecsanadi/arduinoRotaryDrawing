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
    std::cout << __FILE__ <<": "<< __LINE__ << std::endl;

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

   /* while(serial.isOpen())
    {
        std::cout << __FILE__ <<": "<< __LINE__ << std::endl;

        if(!serial.waitForReadyRead(-1)) //block until new data arrives
            qDebug() << "error: " << serial.errorString();
        else{
           // qDebug() << "New data available: " << serial.bytesAvailable();
            QByteArray datas = serial.readAll();
         //   qDebug() << datas;



            const char* input = datas.data();

            std::cout<<"Processing serial data"<<std::endl;

            if (!strncmp(input, "RM", 2))
            {
                point_last.y = point.y;
                point.y -= 1;
                std::cout<<"point.y: "<<point.y<<std::endl;
            }
            else if (!strncmp(input, "RP",2))
            {
                point_last.y = point.y;
                point.y += 1;
                std::cout<<"point.y: "<<point.y<<std::endl;
            }
            else if (!strncmp(input, "LM",2))
            {
                point_last.x = point.x;
                point.x -= 1;
                std::cout<<"point.x: "<<point.x<<std::endl;
            }
            else if (!strncmp(input, "LP",2))
            {
                point_last.x = point.x;
                point.x += 1;
                 std::cout<<"point.x: "<<point.x<<std::endl;
            }
            else if (!strncmp(input, "BL", 2))
            {
                std::cout << "Left button clicked!"<<std::endl;
            }
            else if (!strncmp(input, "BR", 2))
            {
                std::cout << "Right button clicked!"<<std::endl;
            }


            emit serialIsReady();
            painter.drawLine(point_last.x, point_last.y, point.x, point.y);
            if (pointList.size() >= 20)
            {
              pointList.pop_front();
            }
            pointList.push_back(point_last);
            if (pointList.size() >= 20)
            {
              pointList.pop_front();
            }
            pointList.push_back(point);*/



      /*  }

    }*/


}
