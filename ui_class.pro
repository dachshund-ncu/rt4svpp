QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = mdrt4sv

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
