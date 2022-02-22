#include "vbox_main.h"
#include <iostream>

vbox_mainw::vbox_mainw(QObject *parent, const char * name)
{
    makeProperSizeForButtons();
    makeProperLabelsForButtons();
    setupLabels();
    connectToSlots(parent);
    addEverythingToWidget();
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

    // -- minimum --
    LoadAVRFiles->setMinimumSize(0, 0);
    LoadFITSFiles->setMinimumSize(0, 0);
    Reload->setMinimumSize(0, 0);
    DynamicSpectrum->setMinimumSize(0, 0);
    SingleSpectrum->setMinimumSize(0, 0);
    RMSSection->setMinimumSize(0, 0);
    Integrate->setMinimumSize(0, 0);
    AverOverVelocity->setMinimumSize(0, 0);
    AverOverTime->setMinimumSize(0, 0);
    SpectralIndex->setMinimumSize(0, 0);
    ExportDynamicSpectrum->setMinimumSize(0, 0);
    Calibrate->setMinimumSize(0, 0);
    Quit->setMinimumSize(0, 0);
}

void vbox_mainw::makeProperLabelsForButtons()
{
    int butSize = 60;
    // ---
    LoadAVRFiles->setToolTip("Load AVR files");
    LoadAVRFiles->setIcon(QIcon(":/images/loadFitsAVRIcon.svg"));
    LoadAVRFiles->setIconSize(QSize(butSize,butSize));
    LoadAVRFiles->setMaximumSize(butSize,butSize);
    LoadAVRFiles->setFlat(true);
    // ---
    LoadFITSFiles->setToolTip("Load FITS files");
    LoadFITSFiles->setIcon(QIcon(":/images/loadFitsFilesIcon.svg"));
    LoadFITSFiles->setIconSize(QSize(butSize,butSize));
    LoadFITSFiles->setMaximumSize(butSize,butSize);
    LoadFITSFiles->setFlat(true);
    // ---
    Reload->setToolTip("Reload");
    Reload->setIcon(QIcon(":/images/reloadIcon.svg"));
    Reload->setIconSize(QSize(butSize,butSize));
    Reload->setMaximumSize(butSize,butSize);
    Reload->setFlat(true);
    // ---
    DynamicSpectrum->setToolTip("Open Dynamic Spectrum");
    DynamicSpectrum->setIcon(QIcon(":/images/openDynSpecIcon.svg"));
    DynamicSpectrum->setIconSize(QSize(butSize,butSize));
    DynamicSpectrum->setMaximumSize(butSize,butSize);
    DynamicSpectrum->setFlat(true);
    // --
    SingleSpectrum->setToolTip("Open Single Spectrum");
    SingleSpectrum->setIcon(QIcon(":/images/openSingleSpecIcon.svg"));
    SingleSpectrum->setIconSize(QSize(butSize,butSize));
    SingleSpectrum->setMaximumSize(butSize,butSize);
    SingleSpectrum->setFlat(true);
    // --
    RMSSection->setToolTip("Open RMS section");
    RMSSection->setIcon(QIcon(":/images/openRmsSection.svg"));
    RMSSection->setIconSize(QSize(butSize,butSize));
    RMSSection->setMaximumSize(butSize,butSize);
    RMSSection->setFlat(true);
    // --
    Integrate->setToolTip("Integrate time series");
    Integrate->setIcon(QIcon(":/images/integrateIcon.svg"));
    Integrate->setIconSize(QSize(butSize,butSize));
    Integrate->setMaximumSize(butSize,butSize);
    Integrate->setFlat(true);
    // --
    AverOverVelocity->setToolTip("Average time series over velocity");
    AverOverVelocity->setIcon(QIcon(":/images/averOverVelIcon.svg"));
    AverOverVelocity->setIconSize(QSize(butSize,butSize));
    AverOverVelocity->setMaximumSize(butSize,butSize);
    AverOverVelocity->setFlat(true);
    // --
    AverOverTime->setToolTip("Average velocity series over time");
    AverOverTime->setIcon(QIcon(":/images/averOverTimeIcon.svg"));
    AverOverTime->setIconSize(QSize(butSize,butSize));
    AverOverTime->setMaximumSize(butSize,butSize);
    AverOverTime->setFlat(true);
    // --
    SpectralIndex->setToolTip("Calculate variability coefficients (VI, FI, CHi2Red)");
    SpectralIndex->setIcon(QIcon(":/images/chiRedIcon.svg"));
    SpectralIndex->setIconSize(QSize(butSize,butSize));
    SpectralIndex->setMaximumSize(butSize,butSize);
    SpectralIndex->setFlat(true);
    // --
    ExportDynamicSpectrum->setToolTip("Export Dynamic spectrum file");
    ExportDynamicSpectrum->setIcon(QIcon(":/images/exportDynspecIcon.svg"));
    ExportDynamicSpectrum->setIconSize(QSize(butSize,butSize));
    ExportDynamicSpectrum->setMaximumSize(butSize,butSize);
    ExportDynamicSpectrum->setFlat(true);
    // --
    Calibrate->setToolTip("Calibrate currently displayed data");
    Calibrate->setIcon(QIcon(":/images/calibrateIcon.svg"));
    Calibrate->setIconSize(QSize(butSize,butSize));
    Calibrate->setMaximumSize(butSize,butSize);
    Calibrate->setFlat(true);
    // --
    Quit->setToolTip("Exit the program");
    Quit->setIcon(QIcon(":/images/exitIcon.svg"));
    Quit->setIconSize(QSize(butSize,butSize));
    Quit->setMaximumSize(butSize,butSize);
    Quit->setFlat(true);
}

void vbox_mainw::setupLabels()
{
    // font
    QFont f ("Arial", 10, QFont::Bold);
    // setting up labels
    LoadingSectionlabel->setText("Loading");
    VisualSectionLabel->setText("Visualisation");
    ExportAndAnalysisLabel->setText("Export & analysis");
    OthersLabel->setText("Others");
    // fonts
    LoadingSectionlabel->setFont(f);
    VisualSectionLabel->setFont(f);
    ExportAndAnalysisLabel->setFont(f);
    OthersLabel->setFont(f);

    // checkbox
    DarthMode->setChecked(true);
}

void vbox_mainw::addEverythingToWidget()
{
    persistentGrid->addWidget(LoadingSectionlabel,    0,0, 1, 2);
    persistentGrid->addWidget(LoadAVRFiles,           1,0, 1, 1);
    persistentGrid->addWidget(LoadFITSFiles,          1,1, 1, 1);
    persistentGrid->addWidget(Reload,                 2,0, 1, 1);
    persistentGrid->addWidget(DarthMode,              3,0, 1, 2);

    persistentGrid->addWidget(VisualSectionLabel,     4,0, 1, 2);
    persistentGrid->addWidget(DynamicSpectrum,        5,0, 1, 1);
    persistentGrid->addWidget(SingleSpectrum,         5,1, 1, 1);
    persistentGrid->addWidget(RMSSection,             6,0, 1, 1);

    persistentGrid->addWidget(ExportAndAnalysisLabel, 7,0, 1, 2);
    persistentGrid->addWidget(Integrate,              8,0, 1, 1);
    persistentGrid->addWidget(AverOverVelocity,       8,1, 1, 1);
    persistentGrid->addWidget(AverOverTime,           9,0, 1, 1);
    persistentGrid->addWidget(SpectralIndex,          9,1, 1, 1);
    persistentGrid->addWidget(ExportDynamicSpectrum, 10,0, 1, 1);
    persistentGrid->addWidget(IsotimeInclude,        11,0, 1, 2);

    persistentGrid->addWidget(OthersLabel,           12,0, 1, 2);
    persistentGrid->addWidget(Calibrate,             13,0, 1, 1);
    persistentGrid->addWidget(Quit,                  13,1, 1, 1);

    persistentButtons->setMaximumSize(300, 720);
    VboxGrid->addWidget(persistentButtons, 0,0);
    VboxGrid->setAlignment(Qt::AlignTop);
}

void vbox_mainw::appendWidget(QWidget *widget)
{
    // liczymy rowy i kolumny
    int row_count = this->VboxGrid->rowCount();

    this->VboxGrid->addWidget(widget, row_count + 1, 0, 1, 2);
}

void vbox_mainw::deleteWidgetFromList(QWidget *widget)
{
    this->VboxGrid->removeWidget(widget);
}


void vbox_mainw::connectToSlots(QObject *parent)
{
    QObject::connect(Quit, SIGNAL(clicked()), qApp, SLOT(quit()), Qt::QueuedConnection);
    QObject::connect(LoadAVRFiles, SIGNAL(clicked()), parent, SLOT(load_time_series()));
    QObject::connect(LoadFITSFiles, SIGNAL(clicked()), parent, SLOT(load_time_series()));
    QObject::connect(Integrate, SIGNAL(clicked()), parent, SLOT(openIntegrateSection()));
    QObject::connect(SingleSpectrum, SIGNAL(clicked()), parent, SLOT(display_single_spectrum()));
    QObject::connect(DynamicSpectrum, SIGNAL(clicked()), parent, SLOT(display_dynamic_spectrum()));
    QObject::connect(AverOverVelocity, SIGNAL(clicked()), parent, SLOT(openAOVSection()));
    QObject::connect(AverOverTime, SIGNAL(clicked()), parent, SLOT(openAOTSection()));
    QObject::connect(SpectralIndex, SIGNAL(clicked()), parent, SLOT(openSPINDSection()));
    QObject::connect(Reload, SIGNAL(clicked()), parent, SLOT(reload_slot()));
    QObject::connect(Calibrate, SIGNAL(clicked()), parent, SLOT(openCALSection()));
    QObject::connect(ExportDynamicSpectrum, SIGNAL(clicked()), parent, SLOT(openWDSection()));
    QObject::connect(RMSSection, SIGNAL(clicked()), parent, SLOT(open_rms_section_slot()));
    QObject::connect(DarthMode, SIGNAL(clicked()), parent, SLOT(set_dark_mode()));
}
// ---------------------------------------------------------------

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
