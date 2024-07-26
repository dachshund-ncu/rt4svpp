#include "vbox_main.h"

vbox_mainw::vbox_mainw(QObject *parent, const char * name)
{
    this->setOrientation(Qt::Vertical);
    this->setDarkMode();
    // this->setLightMode();

    QSize *sz = new QSize(25,25);
    this->setIconSize(*sz);
    makeProperLabelsForButtons();
    setupLabels();
    connectToSlots(parent);
    addEverythingToWidget();
    this->setVisible(true);
}

void vbox_mainw::makeProperLabelsForButtons()
{
    DynamicSpectrum->setToolTip("Open Dynamic Spectrum");
    SingleSpectrum->setToolTip("Open Single Spectrum");
    RMSSection->setToolTip("Open RMS section");
    Quit->setToolTip("Exit the program");
}

void vbox_mainw::setupLabels()
{
    DarthMode->setChecked(true);
    DarthMode->setVisible(false);
    IsotimeInclude->setVisible(false);
}

void vbox_mainw::addEverythingToWidget()
{
    this->addAction(DynamicSpectrum);
    this->addAction(SingleSpectrum);
    this->addAction(RMSSection);
    this->addWidget(spacer1);
    this->addAction(Quit);
    DynamicSpectrum->setCheckable(true);
    SingleSpectrum->setCheckable(true);
    RMSSection->setCheckable(true);
}

void vbox_mainw::connectToSlots(QObject *parent)
{
    QObject::connect(Quit, SIGNAL(triggered()), qApp, SLOT(quit()), Qt::QueuedConnection);
    QObject::connect(SingleSpectrum, SIGNAL(triggered()), parent, SLOT(display_single_spectrum()));
    QObject::connect(DynamicSpectrum, SIGNAL(triggered()), parent, SLOT(display_dynamic_spectrum()));
    QObject::connect(RMSSection, SIGNAL(triggered()), parent, SLOT(open_rms_section_slot()));
}


void vbox_mainw::setDarkMode(){
    QString styleSheet = R"(

        QWidget {
            margin: 0px;
            background-color: transparent;
            border-radius: 8px; /* border radius */
        }
        QToolButton {
            background-color: transparent; /* background color */
            color: white; /* text color */
            padding: 6px; /* padding */
            font-size: 15px; /* font size */
            border-radius: 6px; /* border radius */
            text-align: left;
            font-family: silka;
            margin-top: 4px;
            margin-bottom: 4px;
            border-left: 3px solid transparent;
        }

        QToolButton:hover {
            background-color: rgba(255,255,255,9%);
        }
        QToolButton:pressed {
            background-color: rgba(255,255,255,9%);
        }
        QToolButton:checked {
            border-left-color: #C2185B;
            background-color: rgba(255,255,255,9%);/*#C2185B;*/
        }
        QToolTip {
            background-color: #141414;
            color: white; /* text color */
            padding: 4px; /* padding */
            font-size: 15px; /* font size */
            border-radius: 4px; /* border radius */
            text-align: left;
            font-family: silka;
        }
    )";

    this->setStyleSheet(styleSheet);
    RMSSection->setIcon(QIcon(":/images/openRmsSection.svg"));
    SingleSpectrum->setIcon(QIcon(":/images/openSingleSpecIcon.svg"));
    DynamicSpectrum->setIcon(QIcon(":/images/openDynSpecIcon.svg"));
    Quit->setIcon(QIcon(":/images/exitIcon.svg"));
}

void vbox_mainw::setLightMode(){
    QString styleSheet = R"(

        QWidget {
            margin: 0px;
            background-color: transparent;
            border-radius: 8px; /* border radius */
        }
        QToolButton {
            background-color: transparent; /* background color */
            color: black; /* text color */
            padding: 6px; /* padding */
            font-size: 15px; /* font size */
            border-radius: 6px; /* border radius */
            text-align: left;
            font-family: silka;
            margin-top: 4px;
            margin-bottom: 4px;
            border-left: 3px solid transparent;
        }

        QToolButton:hover {
            background-color: rgba(0,0,0,9%);
        }
        QToolButton:pressed {
            background-color: rgba(0,0,0,18%);
        }
        QToolButton:checked {
            border-left-color: #C2185B;
            background-color: rgba(0,0,0,18%);/*#C2185B;*/
        }
        QToolTip {
            background-color: #141414;
            color: white; /* text color */
            padding: 4px; /* padding */
            font-size: 15px; /* font size */
            border-radius: 4px; /* border radius */
            text-align: left;
            font-family: silka;
        }
    )";

    this->setStyleSheet(styleSheet);
    RMSSection->setIcon(QIcon(":/images/openRmsSection_black.svg"));
    SingleSpectrum->setIcon(QIcon(":/images/openSingleSpecIcon_black.svg"));
    DynamicSpectrum->setIcon(QIcon(":/images/openDynSpecIcon_black.svg"));
    Quit->setIcon(QIcon(":/images/exitIcon_black.svg"));
}

void vbox_mainw::darthMode(bool enabled){
    if(enabled){
        this->setDarkMode();
    }
    else{
        this->setLightMode();
    }
}
