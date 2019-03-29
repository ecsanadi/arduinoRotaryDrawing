#ifndef READSERIAL_H
#define READSERIAL_H
#include "points.h"
#include <QObject>
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



class SerialReader : public QObject
{
    Q_OBJECT
public:
    SerialReader();
   // ~readSerial(){}
    Points point;
    Points point_last;
    QSerialPort serial;
    int getPointX(){return this->point.x;}
    int getPointY(){return this->point.y;}
    int getPointLastX(){return this->point_last.x;}
    int getPointLastY(){return this->point_last.y;}
    void setPointX(int iValue){this->point.x = iValue;}
    void setPointY(int iValue){this->point.y = iValue;}

    void readingSerial();
signals:
    void serialIsReady();
};

#endif // READSERIAL_H
