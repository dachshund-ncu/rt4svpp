#include "vbox_main.h"

vbox_mainw::vbox_mainw(QObject *parent, const char * name)
{
    this->setOrientation(Qt::Vertical);
    this->setDarkMode();
    // this->setLightMode();

    QSize *sz = new QSize(25,25);
    this->setIconSize(*sz);
    makeProperSizeForButtons();
    makeProperLabelsForButtons();
    setupLabels();
    connectToSlots(parent);
    addEverythingToWidget();
    //this->setMinimumSize(120, 600);
    //this->setMaximumSize(120, 720);

    this->setVisible(true);
}

void vbox_mainw::makeProperSizeForButtons()
{
    // -- maximum --
//    LoadAVRFiles->setMaximumSize(10000, 10000);
//    LoadFITSFiles->setMaximumSize(10000, 10000);
//    Reload->setMaximumSize(10000, 10000);
//    DynamicSpectrum->setMaximumSize(10000, 10000);
//    SingleSpectrum->setMaximumSize(10000, 10000);
//    RMSSection->setMaximumSize(10000, 10000);
//    Integrate->setMaximumSize(10000, 10000);
//    AverOverVelocity->setMaximumSize(10000, 10000);
//    AverOverTime->setMaximumSize(10000, 10000);
//    SpectralIndex->setMaximumSize(10000, 10000);
//    ExportDynamicSpectrum->setMaximumSize(10000, 10000);
//    Calibrate->setMaximumSize(10000, 10000);
//    Quit->setMaximumSize(10000, 10000);

//    // -- minimum --
//    LoadAVRFiles->setMinimumSize(0, 0);
//    LoadFITSFiles->setMinimumSize(0, 0);
//    Reload->setMinimumSize(0, 0);
//    DynamicSpectrum->setMinimumSize(0, 0);
//    SingleSpectrum->setMinimumSize(0, 0);
//    RMSSection->setMinimumSize(0, 0);
//    Integrate->setMinimumSize(0, 0);
//    AverOverVelocity->setMinimumSize(0, 0);
//    AverOverTime->setMinimumSize(0, 0);
//    SpectralIndex->setMinimumSize(0, 0);
//    ExportDynamicSpectrum->setMinimumSize(0, 0);
//    Calibrate->setMinimumSize(0, 0);
//    Quit->setMinimumSize(0, 0);
}

void vbox_mainw::makeProperLabelsForButtons()
{
    //int butSizeY = 40;
    //int butSizeX = 40;
    // ---
//    LoadAVRFiles->setToolTip("Load AVR files");
    //LoadAVRFiles->setText("Load AVR files");
//    LoadAVRFiles->setIcon(QIcon(":/images/loadFitsAVRIcon.svg"));
    //LoadAVRFiles->setIconSize(QSize(butSizeX,butSizeY));
    //LoadAVRFiles->setMaximumSize(butSizeX,butSizeY);
    //LoadAVRFiles->setFlat(true);
    // ---
//    LoadFITSFiles->setToolTip("Load FITS files");
    //LoadFITSFiles->setText("Load FITS files");
//    LoadFITSFiles->setIcon(QIcon(":/images/loadFitsFilesIcon.svg"));
//    LoadFITSFiles->setIconSize(QSize(butSizeX,butSizeY));
//    LoadFITSFiles->setMaximumSize(butSizeX,butSizeY);
    //LoadFITSFiles->setFlat(true);
    // ---
//    Reload->setToolTip("Reload");
    //Reload->setText("Reload");
//    Reload->setIcon(QIcon(":/images/reloadIcon.svg"));
//    Reload->setIconSize(QSize(butSizeX,butSizeY));
//    Reload->setMaximumSize(butSizeX,butSizeY);
    //Reload->setFlat(true);
    // ---
    DynamicSpectrum->setToolTip("Open Dynamic Spectrum");
    //DynamicSpectrum->setText("Open Dynamic Spectrum");
    DynamicSpectrum->setIcon(QIcon(":/images/openDynSpecIcon.svg"));
//    DynamicSpectrum->setIconSize(QSize(butSizeX,butSizeY));
//    DynamicSpectrum->setMaximumSize(butSizeX,butSizeY);
    //DynamicSpectrum->setFlat(true);
    // --
    SingleSpectrum->setToolTip("Open Single Spectrum");
    //SingleSpectrum->setText("Open Single Spectrum");
    SingleSpectrum->setIcon(QIcon(":/images/openSingleSpecIcon.svg"));
//    SingleSpectrum->setIconSize(QSize(butSizeX,butSizeY));
//    SingleSpectrum->setMaximumSize(butSizeX,butSizeY);
    //SingleSpectrum->setFlat(true);
    // --
    RMSSection->setToolTip("Open RMS section");
    //RMSSection->setText("Open RMS section");
    RMSSection->setIcon(QIcon(":/images/openRmsSection.svg"));
//    RMSSection->setIconSize(QSize(butSizeX,butSizeY));
//    RMSSection->setMaximumSize(butSizeX,butSizeY);
    //RMSSection->setFlat(true);
    // --
//    Integrate->setToolTip("Integrate time series");
    //Integrate->setText("Integrate time series");
//    Integrate->setIcon(QIcon(":/images/integrateIcon.svg"));
//    Integrate->setIconSize(QSize(butSizeX,butSizeY));
//    Integrate->setMaximumSize(butSizeX,butSizeY);
    //Integrate->setFlat(true);
    // --
//    AverOverVelocity->setToolTip("Average time series over velocity");
    //AverOverVelocity->setText("Aver over velocity");
//    AverOverVelocity->setIcon(QIcon(":/images/averOverVelIcon.svg"));
//    AverOverVelocity->setIconSize(QSize(butSizeX,butSizeY));
//    AverOverVelocity->setMaximumSize(butSizeX,butSizeY);
    //AverOverVelocity->setFlat(true);
    // --
//    AverOverTime->setToolTip("Average velocity series over time");
    //AverOverTime->setText("Aver over time");
//    AverOverTime->setIcon(QIcon(":/images/averOverTimeIcon.svg"));
//    AverOverTime->setIconSize(QSize(butSizeX,butSizeY));
//    AverOverTime->setMaximumSize(butSizeX,butSizeY);
    //AverOverTime->setFlat(true);
    // --
//    SpectralIndex->setToolTip("Calculate variability coefficients (VI, FI, CHi2Red)");
    //SpectralIndex->setText("Var coeffs");
//    SpectralIndex->setIcon(QIcon(":/images/chiRedIcon.svg"));
//    SpectralIndex->setIconSize(QSize(butSizeX,butSizeY));
//    SpectralIndex->setMaximumSize(butSizeX,butSizeY);
    //SpectralIndex->setFlat(true);
    // --
//    ExportDynamicSpectrum->setToolTip("Export Dynamic spectrum file");
    //ExportDynamicSpectrum->setText("Export Dynamic spectrum file");
//    ExportDynamicSpectrum->setIcon(QIcon(":/images/exportDynspecIcon.svg"));
//    ExportDynamicSpectrum->setIconSize(QSize(butSizeX,butSizeY));
//    ExportDynamicSpectrum->setMaximumSize(butSizeX,butSizeY);
    //ExportDynamicSpectrum->setFlat(true);
    // --
    //Calibrate->setToolTip("Calibrate currently displayed data");
    //Calibrate->setText("Calibrate");
    //Calibrate->setIcon(QIcon(":/images/calibrateIcon.svg"));
//    Calibrate->setIconSize(QSize(butSizeX,butSizeY));
//    Calibrate->setMaximumSize(butSizeX,butSizeY);
    //Calibrate->setFlat(true);
    // --
    Quit->setToolTip("Exit the program");
    //Quit->setText("Exit the program");
    Quit->setIcon(QIcon(":/images/exitIcon.svg"));
//    Quit->setIconSize(QSize(butSizeX,butSizeY));
//    Quit->setMaximumSize(butSizeX,butSizeY);
    //Quit->setFlat(true);
}

void vbox_mainw::setupLabels()
{
//    // font
//    QFont f ("Arial", 10, QFont::Bold);
//    // setting up labels
//    LoadingSectionlabel->setText("Loading");
//    VisualSectionLabel->setText("Visualisation");
//    ExportAndAnalysisLabel->setText("Export & analysis");
//    OthersLabel->setText("Others");
//    // fonts
//    LoadingSectionlabel->setFont(f);
//    VisualSectionLabel->setFont(f);
//    ExportAndAnalysisLabel->setFont(f);
//    OthersLabel->setFont(f);

    // checkbox
    DarthMode->setChecked(true);
    DarthMode->setVisible(false);
    IsotimeInclude->setVisible(false);

//    // labels
//    LoadingSectionlabel->setVisible(false);
//    VisualSectionLabel->setVisible(false);
//    ExportAndAnalysisLabel->setVisible(false);
//    OthersLabel->setVisible(false);
}

void vbox_mainw::addEverythingToWidget()
{
//    this->addAction(LoadAVRFiles);
//    this->addAction(LoadFITSFiles);
//    this->addAction(Reload);
//    this->addSeparator();

    this->addAction(DynamicSpectrum);
    this->addAction(SingleSpectrum);
    this->addAction(RMSSection);
    this->addWidget(spacer1);
//    this->addSeparator();
//    this->addWidget(spacer2);
//    this->addAction(Integrate);
//    this->addAction(AverOverVelocity);
//    this->addAction(AverOverTime);
//    this->addAction(SpectralIndex);
//    this->addAction(ExportDynamicSpectrum);
//    this->addSeparator();
    //this->addAction(Calibrate);
    this->addAction(Quit);
//    VboxGrid->addWidget(LoadingSectionlabel,    0,0, 1, 1);
//    VboxGrid->addWidget(LoadAVRFiles,           0,0, 1, 1);
//    VboxGrid->addWidget(LoadFITSFiles,          1,0, 1, 1);
//    VboxGrid->addWidget(Reload,                 2,0, 1, 1);
//    //persistentGrid->addWidget(VisualSectionLabel,     5,0, 1, 1);
//    VboxGrid->addWidget(DynamicSpectrum,        4,0, 1, 1);
//    VboxGrid->addWidget(SingleSpectrum,         5,0, 1, 1);
//    VboxGrid->addWidget(RMSSection,             6,0, 1, 1);

//    //persistentGrid->addWidget(ExportAndAnalysisLabel, 9,0, 1, 1);
//    VboxGrid->addWidget(Integrate,              7,0, 1, 1);
//    VboxGrid->addWidget(AverOverVelocity,       8,0, 1, 1);
//    VboxGrid->addWidget(AverOverTime,           9,0, 1, 1);
//    VboxGrid->addWidget(SpectralIndex,          10,0, 1, 1);
//    VboxGrid->addWidget(ExportDynamicSpectrum, 11,0, 1, 1);

//    //persistentGrid->addWidget(OthersLabel,           16,0, 1, 1);
//    VboxGrid->addWidget(Calibrate,             13,0, 1, 1);
//    VboxGrid->addWidget(Quit,                  14,0, 1, 1);

//    //persistentButtons->setMaximumSize(100, 720);
//    //VboxGrid->addWidget(persistentButtons, 0,0);
//    VboxGrid->setAlignment(Qt::AlignTop);
    // -----
    DynamicSpectrum->setCheckable(true);
    SingleSpectrum->setCheckable(true);
    RMSSection->setCheckable(true);
}

//void vbox_mainw::appendWidget(QWidget *widget)
//{
//    // liczymy rowy i kolumny
//    int row_count = this->VboxGrid->rowCount();

//    this->VboxGrid->addWidget(widget, row_count + 1, 0, 1, 2);
//}

//void vbox_mainw::deleteWidgetFromList(QWidget *widget)
//{
//    this->VboxGrid->removeWidget(widget);
//}


void vbox_mainw::connectToSlots(QObject *parent)
{
    QObject::connect(Quit, SIGNAL(triggered()), qApp, SLOT(quit()), Qt::QueuedConnection);
//    QObject::connect(LoadAVRFiles, SIGNAL(triggered()), parent, SLOT(load_time_series_AVR()));
//    QObject::connect(LoadFITSFiles, SIGNAL(triggered()), parent, SLOT(load_time_series_FITS()));
//    QObject::connect(Integrate, SIGNAL(triggered()), parent, SLOT(openIntegrateSection()));
    QObject::connect(SingleSpectrum, SIGNAL(triggered()), parent, SLOT(display_single_spectrum()));
    QObject::connect(DynamicSpectrum, SIGNAL(triggered()), parent, SLOT(display_dynamic_spectrum()));
//    QObject::connect(AverOverVelocity, SIGNAL(triggered()), parent, SLOT(openAOVSection()));
//    QObject::connect(AverOverTime, SIGNAL(triggered()), parent, SLOT(openAOTSection()));
//    QObject::connect(SpectralIndex, SIGNAL(triggered()), parent, SLOT(openSPINDSection()));
//    QObject::connect(Reload, SIGNAL(triggered()), parent, SLOT(reload_slot()));
    //QObject::connect(Calibrate, SIGNAL(triggered()), parent, SLOT(openCALSection()));
//    QObject::connect(ExportDynamicSpectrum, SIGNAL(triggered()), parent, SLOT(openWDSection()));
    QObject::connect(RMSSection, SIGNAL(triggered()), parent, SLOT(open_rms_section_slot()));
//    QObject::connect(DarthMode, SIGNAL(clicked()), parent, SLOT(darkModeSlot()));
}
// ---------------------------------------------------------------

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
}

void vbox_mainw::setLightMode(){
    QString styleSheet = R"(

        QWidget {
            margin: 0px;
            background-color: transparent;
            border-radius: 8px; /* border radius */
        }
        QToolButton {
            background-color: rgba(0,0,0,18%); /* background color */
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
            background-color: rgba(0,0,0,27%);
        }
        QToolButton:pressed {
            background-color: rgba(0,0,0,27%);
        }
        QToolButton:checked {
            border-left-color: #C2185B;
            background-color: rgba(0,0,0,27%);/*#C2185B;*/
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
}

void vbox_mainw::darthMode(bool enabled){
    if(enabled){
        this->setDarkMode();
    }
    else{
        this->setLightMode();
    }
}

/*
void openInt()
{
    // gdy otwarta jest inna sekcja
    if (sectionOpened)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous section"));
        return;
    }

    // otwieramy sekcję
    appendWidget(intWidget);
    // ustalamy visible
    appendWidget.setVisible(true);
}

void closeInt()
{
    intWidget.setVisible(false);
    deleteWidgetFromList(intWidget);
}
*/
