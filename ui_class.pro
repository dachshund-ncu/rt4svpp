QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = rt4sv++

TEMPLATE = app

SOURCES += \
    body.cpp \
    main.cpp \
    qcustomplot.cpp

HEADERS += \
    body.h \
    qcustomplot.h

RESOURCES += \
    resources.qrc

unix:!macx: LIBS += -L /usr/local/lib/ -lCCfits

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: LIBS += -lcfitsio
