QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = rt4sv++

TEMPLATE = app

QTPLUGIN += qsvg

SOURCES += \
    UI/varcoefscalcwidget.cpp \
    body.cpp \
    data/calibration.cpp \
    data/exportvaroiusdata.cpp \
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
    UI/calsection.cpp \
    UI/heat_map_widget.cpp \
    UI/single_spec_widget.cpp \
    UI/rms_sec_widget.cpp \
    UI/rms_selector.cpp \
    data/extractlcs.cpp \
    UI/contentviewer.cpp

HEADERS += \
    UI/custom_ui_elements.h \
    UI/varcoefscalcwidget.h \
    body.h \
    data/spectral_container.h \
    libs/qcustomplot.h \
    UI/vbox_main.h \
    UI/integrate_widget.h \
    UI/export_dynamic_spectrum_widget.h \
    UI/calsection.h \
    UI/heat_map_widget.h \
    UI/single_spec_widget.h \
    UI/rms_sec_widget.h \
    UI/rms_selector.h \
    UI/contentviewer.h

RESOURCES += \
    resources.qrc

unix:!macx: LIBS += -L /usr/local/lib/ -lCCfits

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: LIBS += /usr/local/lib/ -lcfitsio
