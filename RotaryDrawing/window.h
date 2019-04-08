#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>

class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;

class RenderArea;

class SerialReader;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(SerialReader *);
    void setSerialReader(SerialReader *);
    void setScreenSize(QSize scnsize);

private slots:
    void shapeChanged();
    void penChanged();

private:
    RenderArea *renderArea;
    QLabel *shapeLabel;
    QLabel *penWidthLabel;
    QLabel *penStyleLabel;
    QLabel *otherOptionsLabel;
    QComboBox *shapeComboBox;
    QSpinBox *penWidthSpinBox;
    QComboBox *penStyleComboBox;
    QCheckBox *antialiasingCheckBox;
    QCheckBox *transformationsCheckBox;
    SerialReader* serial;

};

#endif // WINDOW_H
