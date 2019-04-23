#include "renderarea.h"
#include "window.h"
#include "serialreader.h"

#include <QtWidgets>

const int IdRole = Qt::UserRole;

Window::Window(SerialReader* pserial)
{
    renderArea = new RenderArea;

    shapeComboBox = new QComboBox;

    serial = pserial;
    renderArea->setSerialReader(serial);

    otherOptionsLabel = new QLabel(tr("Options:"));
    antialiasingCheckBox = new QCheckBox(tr("&Antialiasing"));
    transformationsCheckBox = new QCheckBox(tr("&Transformations"));


    connect(serial, SIGNAL(serialIsReady()),
            this, SLOT(shapeChanged()));

    connect(antialiasingCheckBox, SIGNAL(toggled(bool)),
            renderArea, SLOT(setAntialiased(bool)));
    connect(transformationsCheckBox, SIGNAL(toggled(bool)),
            renderArea, SLOT(setTransformed(bool)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);

    mainLayout->addWidget(otherOptionsLabel, 5, 0, Qt::AlignRight);
    mainLayout->addWidget(antialiasingCheckBox, 5, 1, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(transformationsCheckBox, 5, 2, 1, 2, Qt::AlignRight);
    setLayout(mainLayout);

    shapeChanged();
    penChanged();

    antialiasingCheckBox->setChecked(true);

    setWindowTitle(tr("Rotary Drawing"));

}

void Window::setSerialReader(SerialReader* pserial)
{
    serial = pserial;
    renderArea->setSerialReader(serial);
}

void Window::setScreenSize(QSize scnsize)
{
    renderArea->setScreenSize(scnsize);
}


void Window::shapeChanged()
{
    renderArea->setShape(RenderArea::Line);
}

void Window::penChanged()
{
    int penWidth = 10;
    renderArea->setPen(QPen(static_cast<QColor>(serial->getMyColor()), penWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
}

