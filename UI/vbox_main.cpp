#include "vbox_main.h"

vbox_mainw::vbox_mainw(QWidget *parent, const char * name)
{
    makeProperSizeForButtons();
    makeProperLabelsForButtons();
    setupLabels();

    addEverythingToWidget();
    this->setGeometry(this->x(), this->y(), 300, 720);
    this->setVisible(true);
}

void vbox_mainw::makeProperSizeForButtons()
{
    // -- maximum --
    LoadAVRFiles->setMaximumSize(10000, 10000);
    LoadFITSFiles->setMaximumSize(10000, 10000);
    Reload->setMaximumSize(10000, 10000);
    DynamicSpectrum->setMaximumSize(10000, 10000);
    SingleSpectrum->setMaximumSize(10000, 10000);
    RMSSection->setMaximumSize(10000, 10000);
    GaussFitting->setMaximumSize(10000, 10000);
    Integrate->setMaximumSize(10000, 10000);
    AverOverVelocity->setMaximumSize(10000, 10000);
    AverOverTime->setMaximumSize(10000, 10000);
    SpectralIndex->setMaximumSize(10000, 10000);
    ExportDynamicSpectrum->setMaximumSize(10000, 10000);
    Calibrate->setMaximumSize(10000, 10000);
    Quit->setMaximumSize(10000, 10000);

    // -- minimum --
    LoadAVRFiles->setMinimumSize(0, 0);
    LoadFITSFiles->setMinimumSize(0, 0);
    Reload->setMinimumSize(0, 0);
    DynamicSpectrum->setMinimumSize(0, 0);
    SingleSpectrum->setMinimumSize(0, 0);
    RMSSection->setMinimumSize(0, 0);
    GaussFitting->setMinimumSize(0, 0);
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
    LoadAVRFiles->setText("A");
    LoadFITSFiles->setText("R");
    Reload->setText("R");

    DynamicSpectrum->setText("DS");
    SingleSpectrum->setText("SP");
    RMSSection->setText("RMS");
    GaussFitting->setText("GS");

    Integrate->setText("INT");
    AverOverVelocity->setText("AOV");
    AverOverTime->setText("AOT");
    SpectralIndex->setText("SPI");
    ExportDynamicSpectrum->setText("EDS");

    Calibrate->setText("CAL");
    Quit->setText("QT");
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
}

void vbox_mainw::addEverythingToWidget()
{
    VboxGrid->addWidget(LoadingSectionlabel,    0,0, 1, 2);
    VboxGrid->addWidget(LoadAVRFiles,           1,0, 1, 1);
    VboxGrid->addWidget(LoadFITSFiles,          1,1, 1, 1);
    VboxGrid->addWidget(Reload,                 2,0, 1, 1);
    VboxGrid->addWidget(DarthMode,              3,0, 1, 2);

    VboxGrid->addWidget(VisualSectionLabel,     4,0, 1, 2);
    VboxGrid->addWidget(DynamicSpectrum,        5,0, 1, 1);
    VboxGrid->addWidget(SingleSpectrum,         5,1, 1, 1);
    VboxGrid->addWidget(RMSSection,             6,0, 1, 1);
    VboxGrid->addWidget(GaussFitting,           6,1, 1, 1);


    VboxGrid->addWidget(ExportAndAnalysisLabel, 7,0, 1, 2);
    VboxGrid->addWidget(Integrate,              8,0, 1, 1);
    VboxGrid->addWidget(AverOverVelocity,       8,1, 1, 1);
    VboxGrid->addWidget(AverOverTime,           9,0, 1, 1);
    VboxGrid->addWidget(SpectralIndex,          9,1, 1, 1);
    VboxGrid->addWidget(ExportDynamicSpectrum, 10,0, 1, 1);
    VboxGrid->addWidget(IsotimeInclude,        11,0, 1, 2);

    VboxGrid->addWidget(OthersLabel,           12,0, 1, 2);
    VboxGrid->addWidget(Calibrate,             13,0, 1, 1);
    VboxGrid->addWidget(Quit,                  13,1, 1, 1);




}
