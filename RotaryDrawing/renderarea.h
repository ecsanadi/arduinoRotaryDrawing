#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include "serialreader.h"
#include <vector>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    enum Shape { Line/*, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                 Chord, Pie, Path, Text, Pixmap */};

    RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    QSize screenSize;


    void setSerialReader(SerialReader *);

    //SerialReader serialo;


public slots:
    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialiased(bool antialiased);
    void setTransformed(bool transformed);
    void setScreenSize(QSize scnsize){this->screenSize = scnsize;}

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
    SerialReader* serial;
    Points point;
    Points iniPoint;
    std::vector<Points> pointList;
};

#endif // RENDERAREA_H
