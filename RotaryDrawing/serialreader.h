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
    Points point;
    Points point_last;
    QSerialPort serial;
    bool doDelete = 0;
    int getPointX(){return this->point.x;}
    int getPointY(){return this->point.y;}
    int getPointColorCount(){return this->point.colorCounter;}
    int getPointLastX(){return this->point_last.x;}
    int getPointLastY(){return this->point_last.y;}
    void setPointX(int iValue){this->point.x = iValue;}
    void setPointY(int iValue){this->point.y = iValue;}
    void setPointColorCount(int cc){this->point.colorCounter = cc;}
    bool getDoDelete(){return this->doDelete;}
    void setDoDelete(bool wdo){this->doDelete = wdo;}
    bool setSerialDevice(QString portName);
    bool checkSerialDevice();


    QColor myColor = Qt::blue;

    int colorIdx = 0;

    void setMyColor(int x)
    {
        switch (x)
        {
        case 0: this->myColor = Qt::red;       break;
        case 1: this->myColor = Qt::blue;        break;
        case 2: this->myColor =  Qt::gray;       break;
        case 3: this->myColor =  Qt::yellow;     break;
        case 4: this->myColor =  Qt::red;        break;
        case 5: this->myColor =  Qt::green;      break;
        case 6: this->myColor =  Qt::black;       break;
        case 7: this->myColor =  Qt::cyan;       break;
        case 8: this->myColor =  Qt::magenta;    break;
        case 9: this->myColor =  Qt::yellow;     break;
        case 10: this->myColor =  Qt::darkRed;    break;
        case 11: this->myColor =  Qt::darkGreen;  break;
        case 12: this->myColor =  Qt::darkBlue;   break;
        case 13: this->myColor =  Qt::darkCyan;   break;
        case 14: this->myColor =  Qt::darkMagenta;break;
        case 15: this->myColor =  Qt::darkYellow; break;
        case 16: this->myColor =  Qt::transparent; break;
        default: this->myColor =  Qt::blue;       break;
        }
    }

    void readingSerial();
signals:
    void serialIsReady();
};

#endif // READSERIAL_H
