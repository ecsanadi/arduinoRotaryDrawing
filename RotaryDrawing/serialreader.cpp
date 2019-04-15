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


QTextStream out(stdout);


SerialReader::SerialReader()
{

    //set start position and color
    point.x=5;
    point.y=5;
    point.colorCounter=0;

    int tryCounter = 50;
    int portcounter = 0;
    bool found = 0;


	QString portName;

    //Try (max 50 times) to find available serial ports
    while (tryCounter && !(found))
    {
        const auto serialPortInfos = QSerialPortInfo::availablePorts();
        std::cout << "Total number of ports available: " << serialPortInfos.count() << std::endl;

        //if success iterate trough
        if(serialPortInfos.count() >= 1)
        {
            tryCounter = 1;
            for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
                      portName = serialPortInfo.portName();
                      out << "Try to set "<<portcounter<<". port, named: "<<portName<<endl;
                      portcounter++;
                      out<<"Call setSerialDevice("<<portName<<")"<<endl;
                      if(setSerialDevice(portName))
                      {
                          out << "setSerialDevice("<<portName<<") was SUCCESS."<<endl;
                          found = checkSerialDevice();
                          out << "found is "<<found<<endl;
                      }

                      if(!found)
                      {
                          serial.close();
                          out<<"Close serial and try next."<<endl;
                          continue;
                      }
                      else
                      {
                          out<<"Device is found, break from for."<<endl;
                          break;
                      }

             }
            //found
        }
        tryCounter--;
    }

    if(tryCounter == 0 && !(found))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No USB connection!");
        messageBox.setFixedSize(500,200);
        exit(1);
    }

    std::cout<<"SUCCESS Connection!"<<std::endl;
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

bool SerialReader::setSerialDevice(QString portName)
{

    this->serial.setPortName(portName);
    if(!this->serial.setBaudRate(QSerialPort::Baud9600))
        qDebug() << this->serial.errorString();
    if(!this->serial.setDataBits(QSerialPort::Data8))
        qDebug() << this->serial.errorString();
    if(!this->serial.setParity(QSerialPort::NoParity))  //even
        qDebug() << this->serial.errorString();
    if(!this->serial.setFlowControl(QSerialPort::HardwareControl))
        qDebug() << this->serial.errorString();
    if(!this->serial.setStopBits(QSerialPort::OneStop))
        qDebug() << this->serial.errorString();
    if(!this->serial.open(QIODevice::ReadWrite))
    {
        qDebug() << this->serial.errorString();
        out<<"Set " << portName << " was NOT success."<<endl;
        return false;
    }
     qDebug() << this->serial.bytesAvailable();
         QByteArray datastrash = this->serial.readAll();
     //qDebug()<<datastrash<<"was sent to a trash var.";
     out<<"first read is deleted: "<<datastrash<<endl;
     out<<"Set " << portName << " was SUCCESS."<<endl;
     return true;
}

bool SerialReader::checkSerialDevice()
{
    out<<"Checking if this device is the Arduino..."<<endl;
    for (int loop=0;loop<4;loop++)
    {
     out<<loop<<". try: "<<endl;
     if(serial.isWritable())
     {
         QByteArray output;
         QByteArray input;

         out<<"Send a space."<<endl;
         output = " ";
         this->serial.write(output);
         this->serial.flush();

         this->serial.waitForBytesWritten(1000);
         this->serial.waitForReadyRead(1000);


         input = this->serial.readAll();
         //qDebug()<<input;
         out<<"receive input is: \""<<input<<"\""<<endl;


         //check if the received char is a dot
         if(input==".")
         {
             std::cout<<"Received data is EQUAL, returning true.."<<std::endl;
             return true;
         }
         else
         {
             std::cout<<"Received data was NOT EQUAL. Try again..."<<std::endl;
         }
     }
    }
    out<<"Device detection was not success. Try next port..."<<endl;
    return false;
}


