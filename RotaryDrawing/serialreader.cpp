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
#include <QSerialPortInfo>
#include <QTextStream>
#include <QThread>





SerialReader::SerialReader()
{

    //set start position and color
    point.x=5;
    point.y=5;
    point.colorCounter=0;

    int tryCounter = 50;
    bool found = 0;

    QTextStream out(stdout);
	QString portName;

    //Try (max 50 times) to find available serial ports
    while (tryCounter && !(found))
    {
        const auto serialPortInfos = QSerialPortInfo::availablePorts();
        std::cout << "Total number of ports available: " << serialPortInfos.count() << std::endl;
        //if success iterate trough
        if(serialPortInfos.count() >= 1)
        {
            for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
                      portName = serialPortInfo.portName();
                      out << "Portname: "<<portName<<endl;

                        serial.setPortName(portName);
                        if(!serial.setBaudRate(QSerialPort::Baud9600))
                            qDebug() << serial.errorString();
                        if(!serial.setDataBits(QSerialPort::Data8))
                            qDebug() << serial.errorString();
                        if(!serial.setParity(QSerialPort::NoParity))  //even
                            qDebug() << serial.errorString();
                        if(!serial.setFlowControl(QSerialPort::HardwareControl))
                            qDebug() << serial.errorString();
                        if(!serial.setStopBits(QSerialPort::OneStop))
                            qDebug() << serial.errorString();
                        if(!serial.open(QIODevice::ReadWrite))
                            qDebug() << serial.errorString();
                         qDebug() << serial.bytesAvailable();
                             QByteArray datastrash = serial.readAll();
                             qDebug()<<datastrash;
                       //try to communicate two times: in case if first time we would get junk data
                       for (int loop=0;loop<3;loop++)
                       {
                        if(serial.isWritable())
                        {
                            QByteArray output;
                            QByteArray input;

                            //send a space character
                            output = " ";
                            serial.write(output);
                            serial.flush();

                            serial.waitForBytesWritten(1000);
                            serial.waitForReadyRead(1000);

                            input = serial.readAll();
                            qDebug()<<input;

                            //check if the received char is a dot
                            if(input==".")
                            {
                                std::cout<<"EQUAL"<<std::endl;
                                found = true;
                                serial.close();
                                break;
                            }
                            else
                            {
                                std::cout<<"Try next port..."<<std::endl;
                            }
                        }
                       }
                      if(found)
                      {
                          break;
                      }
             }
            //found
        }
        tryCounter--;
    }
    if(tryCounter == 0)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No USB connection!");
        messageBox.setFixedSize(500,200);
        exit(1);
    }
    std::cout<<"SUCCESS Connection!"<<std::endl;
    serial.setPortName(portName);
    if(!serial.setBaudRate(QSerialPort::Baud9600))
        qDebug() << serial.errorString();
    if(!serial.setDataBits(QSerialPort::Data8))
        qDebug() << serial.errorString();
    if(!serial.setParity(QSerialPort::NoParity))  //even
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
                qDebug() << datas[i];                

                //if the first bit is 1 then right rotary data came
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
                //left..
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
            //emit serial reading
             emit serialIsReady();
        }
);
        QObject::connect(&serial,
                         static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
                         (&QSerialPort::error),
                         [&](QSerialPort::SerialPortError error)
        {
            //this is called when a serial communication error occurs
            qDebug() << "An error occured: " << error;
        });   
}
