#include "renderarea.h"
#include "serialreader.h"
#include "points.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    shape = Line;
    antialiased = false;
    transformed = false;
    pixmap.load(":/images/qt-logo.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    Points iniPoint;
    iniPoint.x=0;
    iniPoint.y=0;
    pointList.push_back(iniPoint);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
    update();
}

void RenderArea::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}

void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}

void RenderArea::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

void RenderArea::setTransformed(bool transformed)
{
    this->transformed = transformed;
    update();
}

void RenderArea::setSerialReader(SerialReader* pserial)
{
    serial = pserial;
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{


    QPainter painter(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    if (antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);

            painter.save();

            if (transformed) {
                painter.translate(50, 50);
                painter.rotate(60.0);
                painter.scale(0.6, 0.9);
                painter.translate(-50, -50);
            }

            switch (shape) {
            case Line:
           //     std::cout << __FILE__ <<": "<< __LINE__ << std::endl;


                point.x=serial->getPointX();
                point.y=serial->getPointY();
                int n = pointList.size();

              /*  if (point.x < 0)
                {
                    serial->setPointX(width());
                    pointList[n-1].x=width();
                    pointList[n-2].x=0;
                }*/
                if (point.x > width())
                {
                    serial->setPointX(0);
                    // pointList.back().x = 0;
                }

               /* if (point.y > height())
                {
                    serial->setPointY(0);
                }
                if (point.y < height())
                {
                    serial->setPointY(height());
                }*/
              //  std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
                pointList.push_back(point);
              //  std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
                for(std::vector<Points>::iterator it = pointList.begin(); it != pointList.end(); ++it) {
                //    std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
                    if (it != pointList.end())
                    {
                //        std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
                        std::vector<Points>::iterator it2 = it;
                        it2++;
                        if (it2!=pointList.end())
                        {
                        painter.drawLine(it->x,it->y,it2->x,it2->y);
                 //       std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
                        }
                    }else{
                        break;
                    }

                 }
          //      std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
                //serialo.readingSerial();
                //painter.drawLine(rect.bottomLeft(), rect.topRight());
                //painter.drawLine(serial->getPointLastX(),serial->getPointLastY(),serial->getPointX(),serial->getPointY());
                //painter.drawLine(readSerial::getPointLastX(),readSerial::getPointLastY(),readSerial::getPointX(),readSerial::getPointY());
               // painter.drawLine(10,10,200,200);
                break;

            }
            painter.restore();
    //    }
   // }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
