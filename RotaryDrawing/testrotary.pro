#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T17:34:04
#
#-------------------------------------------------

QT += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

requires(qtConfig(combobox))

TARGET = testrotary
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS       = renderarea.h \
                window.h \
    points.h \
    serialreader.h

SOURCES       = main.cpp \
    renderarea.cpp \
    window.cpp \
    points.cpp \
    serialreader.cpp

RESOURCES     =  testrotary.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/basicdrawing
INSTALLS += target
