#include "window.h"
#include <QApplication>
#include "serialreader.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(testrotary);

    QApplication app(argc, argv);

    QSize screenSize = app.desktop()->availableGeometry().size();

    SerialReader serialReader;  

    Window window(&serialReader);

    window.setScreenSize(screenSize);
    int myHeight = screenSize.height();
    int myWidth =screenSize.width();
    myHeight *= 0.9;
    myWidth *= 0.9;
    screenSize *= 0.9;

    window.resize(myWidth,myHeight);


    window.show();

    serialReader.readingSerial();

    return app.exec();
}
