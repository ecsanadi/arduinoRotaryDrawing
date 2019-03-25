#include <QtCore/QCoreApplication>
#include <iostream>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QDebug>
#include <QtSerialPort/QtSerialPort>
#include <string>
#include <QPainter>


class Widget : public QWidget
{
protected:
	void paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
		painter.drawLine(0, 0, 200, 200);
	}
};

int main(int argc, char *argv[])
{ 

        QCoreApplication a(argc, argv);
        QSerialPort serial;
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

        int lRotaryCounter = 0;
        int rRotaryCounter = 0;
		int lRotaryCounter_last = 0;
		int rRotaryCounter_last = 0;

		Widget w;
		w.show();

		QPainter painter(&w);
		painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));

        while(serial.isOpen())
        {
            if(!serial.waitForReadyRead(-1)) //block until new data arrives
                qDebug() << "error: " << serial.errorString();
            else{
               // qDebug() << "New data available: " << serial.bytesAvailable();
                QByteArray datas = serial.readAll();
             //   qDebug() << datas;


                const char* input = datas.data();

                if (!strncmp(input, "RM", 2))
                {
					rRotaryCounter_last = rRotaryCounter;
					rRotaryCounter--;
                    std::cout << "rRotaryCounter: " << rRotaryCounter << std::endl;
                }
                else if (!strncmp(input, "RP",2))
                {
					rRotaryCounter:last = rRotaryCounter;
					rRotaryCounter++;
                    std::cout << "rRotaryCounter: " << rRotaryCounter << std::endl;
                }
                else if (!strncmp(input, "LM",2))
                {
					lRotaryCounter_last = lRotaryCounter;
					lRotaryCounter--;
                    std::cout << "lRotaryCounter: " << lRotaryCounter << std::endl;
                }
                else if (!strncmp(input, "LP",2))
                {
					lRotaryCounter_last = lRotaryCounter;
					lRotaryCounter++;
                    std::cout << "lRotaryCounter: " << lRotaryCounter << std::endl;
                }
                else if (!strncmp(input, "BL", 2))
                {
                    std::cout << "Left button clicked!"<<std::endl;
                }
                else if (!strncmp(input, "BR", 2))
                {
                    std::cout << "Right button clicked!"<<std::endl;
                }


				painter.drawLine(lRotaryCounter_last, rRotaryCounter_last, lRotaryCounter, rRotaryCounter);

            }
        }
        return 0;

}
