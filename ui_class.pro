QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = rt4sv++

TEMPLATE = app

SOURCES += \
    body.cpp \
    data/spectral_container.cpp \
    libs/qcustomplot.cpp \
    main.cpp \
    data/averovervelocity.cpp \
    data/integrate.cpp

HEADERS += \
    body.h \
    data/spectral_container.h \
    libs/qcustomplot.h \

RESOURCES += \
    resources.qrc

unix:!macx: LIBS += -L /usr/local/lib/ -lCCfits

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: LIBS += /usr/local/lib/ -lcfitsio
