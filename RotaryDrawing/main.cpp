#include "window.h"
#include <QApplication>
#include "serialreader.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(testrotary);

    QApplication app(argc, argv);

    SerialReader serialReader;
     std::cout << __FILE__ <<": "<< __LINE__ << std::endl;

    Window window(&serialReader);
     std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
    //window.setSerialReader(&serialReader);
     std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
    window.show();
    serialReader.readingSerial();
     std::cout << __FILE__ <<": "<< __LINE__ << std::endl;
    return app.exec();
}
