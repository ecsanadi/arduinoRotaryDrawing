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
    point.colorCounter=0;

    serial.setPortName("ttyUSB0");
    if(!serial.setBaudRate(QSerialPort::Baud9600))
        qDebug() << serial.errorString();
    if(!serial.setDataBits(QSerialPort::Data8))
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

}



void SerialReader::readingSerial()
{


    QObject::connect(&serial, &QSerialPort::readyRead, [&]
        {
            //this is called when readyRead() is emitted
            qDebug() << "New data available: " << serial.bytesAvailable();
            int counter = serial.bytesAvailable();
            for (int i=0; i<counter;i++)
            {
                //QByteArray datas = serial.readAll();
                QByteArray datas = serial.read(1);

                char byte_ch[8];
                if(datas[0] & 1)
                {
                    byte_ch[7]='1';
                }
                else
                {
                    byte_ch[7]='0';
                }
                if(datas[0] & 2)
                {
                    byte_ch[6]='1';
                }
                else
                {
                    byte_ch[6]='0';
                }
                if(datas[0] & 4)
                {
                    byte_ch[5]='1';
                }
                else
                {
                    byte_ch[5]='0';
                }
                if(datas[0] & 8)
                {
                    byte_ch[4]='1';
                }
                else
                {
                    byte_ch[4]='0';
                }
                if(datas[0] & 16)
                {
                    byte_ch[3]='1';
                }
                else
                {
                    byte_ch[3]='0';
                }
                if(datas[0] & 32)
                {
                    byte_ch[2]='1';
                }
                else
                {
                    byte_ch[2]='0';
                }
                if(datas[0] & 64)
                {
                    byte_ch[1]='1';
                }
                else
                {
                    byte_ch[1]='0';
                }
                if(datas[0] & 128)
                {
                    byte_ch[0]='1';
                }
                else
                {
                    byte_ch[0]='0';
                }

                for (int j=0; j<8; j++)
                {
                    std::cout << "byte_ch[" << j << "]: "<<byte_ch[j]<<std::endl;
                }
                std::cout << "" <<std::endl;

                if (datas[0]&128)
                {
                    std::cout<<"RIGHT"<<std::endl;
                    int value = ((signed char)(datas[0]<<1))>>1;
                    std::cout<<"value: "<<value<<std::endl;
                    if(value ==0)
                    {
                        setDoDelete(true);
                    }
                    else
                    {
                        point.y+=value;
                    }

                }
                else
                {
                    std::cout<<"LEFT"<<std::endl;
                    int value = ((signed char)(datas[0]<<1))>>1;
                    std::cout<<"value: "<<value<<std::endl;
                    if(value == 0)
                    {
                        point.colorCounter+=1;
                    }
                    else
                    {
                        point.x+=value;
                    }

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
}
