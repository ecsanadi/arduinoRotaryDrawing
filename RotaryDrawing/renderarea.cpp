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
    int myHeight = screenSize.height();
    int myWidth =screenSize.width();
    return QSize(myWidth, myHeight);
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

    if (serial->getDoDelete())
    {
        int lastColorCount = serial->getPointColorCount();
        pointList.clear();
        serial->setPointX(0);
        serial->setPointY(0);
        serial->setPointColorCount(lastColorCount);
        serial->setDoDelete(false);
    }
    point.x=serial->getPointX();
    point.y=serial->getPointY();
    point.colorCounter=serial->getPointColorCount();

    //keep drawing inside of the window
    if (point.x < 0)
    {
        serial->setPointX(0);
    }
    if (point.x > width())
    {
        serial->setPointX(width());
    }

   if (point.y > height())
    {
        serial->setPointY(height());
    }
    if (point.y < 0)
    {
        serial->setPointY(0);
    }

    //restart color counter if the end is reached
    if (point.colorCounter>=17)
    {
        serial->setPointColorCount(0);
    }

    //save into a vector and draw each point
    pointList.push_back(point);
    for(std::vector<Points>::iterator it = pointList.begin(); it != pointList.end(); ++it) {
        if (it != pointList.end())
        {
            std::vector<Points>::iterator it2 = it;
            it2++;
            if (it2!=pointList.end())
            {
              serial->setMyColor(it->colorCounter);
              int w = 4;
              painter.setPen(QPen(static_cast<QColor>(serial->getMyColor()), w, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
              painter.drawLine(it->x,it->y,it2->x,it2->y);
            }
        }else{
            break;
        }
    }

    //draw a "cursor" point
    int penWidth = 5;
    serial->setMyColor(point.colorCounter);
    painter.setPen(QPen(static_cast<QColor>(serial->getMyColor()), penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawPoint(serial->getPointX(),serial->getPointY());

    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
