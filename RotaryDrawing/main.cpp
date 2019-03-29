#include "window.h"
#include <QApplication>
#include "serialreader.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(testrotary);

    QApplication app(argc, argv);

    SerialReader serialReader;  

    Window window(&serialReader);

    window.show();

    serialReader.readingSerial();

    return app.exec();
}
