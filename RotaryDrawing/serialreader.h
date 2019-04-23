#ifndef READSERIAL_H
#define READSERIAL_H
#include "points.h"
#include <QObject>
#include <iostream>
#include <QtSerialPort/QSerialPort>
#include <QtWidgets>


class SerialReader : public QObject
{
    Q_OBJECT

public:
    SerialReader();
    QSerialPort serial;
    int getPointX(){return this->point.x;}
    int getPointY(){return this->point.y;}
    int getPointColorCount(){return this->point.colorCounter;}
    int getPointLastX(){return this->point_last.x;}
    int getPointLastY(){return this->point_last.y;}
    bool getDoDelete(){return this->doDelete;}
    QColor getMyColor(){return this->myColor;}
    void setPointX(int iValue){this->point.x = iValue;}
    void setPointY(int iValue){this->point.y = iValue;}
    void setPointColorCount(int cc){this->point.colorCounter = cc;}    
    void setDoDelete(bool wdo){this->doDelete = wdo;}
    bool setSerialDevice(QString portName);
    bool checkSerialDevice();
    void setMyColor(int x);
    void readingSerial();

signals:
    void serialIsReady();

private:
    Points point;
    Points point_last;
    bool doDelete = 0;
    int colorIdx = 0;
    QColor myColor = Qt::blue;
};

#endif // READSERIAL_H
