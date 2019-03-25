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


class Points
{
public:
	int x;
	int y;
};

class MyWidget : public QWidget
{
	Q_OBJECT
protected:
	void paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
		painter.drawLine(point_last.x, point_last.y, point.x, point.y);
	}
public:

	Points point;
	Points point_last;
	std::list<Points> pointList;

	void undo()
	{
		/*QPainter painter(this);
		for (std::list<Points>::iterator it=pointList.end(); it!=pointList.begin(); --it)
		{
			std::cout << ' ' << it->x << " " << it->y << std::endl;
			if (it!=pointList.begin()){
			  std::list<Points>::iterator itPrev = it;
			  itPrev--;
			  painter.eraseRect(it->x - itPrev->x, it->y - itPrev->y,1,1);
			}
		}*/
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


		//int lRotaryCounter_last = 0;
		//int rRotaryCounter_last = 0;

		//Points point;
		//Points point_last;



		MyWidget mywidget;
		mywidget.point.x = 0;
		mywidget.point.y = 0;
		mywidget.point_last.x = 0;
		mywidget.point_last.y = 0;

	//	QPainter painter(&w);
	//	painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));

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
					/*rRotaryCounter_last = rRotaryCounter;
					rRotaryCounter--;
					std::cout << "rRotaryCounter: " << rRotaryCounter << std::endl;*/
					//point_last.y = point.y;
					//point.y -= 1;
					mywidget.point_last.y = mywidget.point.y;
					mywidget.point.y -= 1;
                }
                else if (!strncmp(input, "RP",2))
                {
					/*rRotaryCounter_last = rRotaryCounter;
					rRotaryCounter++;
					std::cout << "rRotaryCounter: " << rRotaryCounter << std::endl;*/
					mywidget.point_last.y = mywidget.point.y;
					mywidget.point.y += 1;
                }
                else if (!strncmp(input, "LM",2))
                {
					/*lRotaryCounter_last = lRotaryCounter;
					lRotaryCounter--;
					std::cout << "lRotaryCounter: " << lRotaryCounter << std::endl;*/
					mywidget.point_last.x = mywidget.point.x;
					mywidget.point.x -= 1;
                }
                else if (!strncmp(input, "LP",2))
                {
					/*lRotaryCounter_last = lRotaryCounter;
					lRotaryCounter++;
					std::cout << "lRotaryCounter: " << lRotaryCounter << std::endl;*/
					mywidget.point_last.x = mywidget.point.x;
					mywidget.point.x += 1;
                }
                else if (!strncmp(input, "BL", 2))
                {
                    std::cout << "Left button clicked!"<<std::endl;


                }
                else if (!strncmp(input, "BR", 2))
                {
                    std::cout << "Right button clicked!"<<std::endl;
                }

				mywidget.show();

				/*painter.drawLine(point_last.x, point_last.y, point.x, point.y);
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

            }
        }
        return 0;

}
