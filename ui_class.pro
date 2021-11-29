QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = rt4sv++

TEMPLATE = app

SOURCES += \
    body.cpp \
    data/calibration.cpp \
    data/spectral_container.cpp \
    libs/qcustomplot.cpp \
    main.cpp \
    data/averovervelocity.cpp \
    data/integrate.cpp \
    data/averovertime.cpp \
    data/wd.cpp \
    data/spectralindex.cpp \
    data/rotation.cpp \
    data/savespectrumtoascii.cpp \
    UI/vbox_main.cpp \
    UI/integrate_widget.cpp \
    UI/export_dynamic_spectrum_widget.cpp \
    UI/calsection.cpp

HEADERS += \
    body.h \
    data/spectral_container.h \
    libs/qcustomplot.h \
    UI/vbox_main.h \
    UI/integrate_widget.h \
    UI/export_dynamic_spectrum_widget.h \
    UI/calsection.h

RESOURCES += \
    resources.qrc

unix:!macx: LIBS += -L /usr/local/lib/ -lCCfits

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: LIBS += /usr/local/lib/ -lcfitsio
