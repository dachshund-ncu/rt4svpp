#include "rms_sec_widget.h"

Rms_sec_widget::Rms_sec_widget(spectral_container * dataTable)
               : dataTable(dataTable)
{
    // -- procesujemy odpowiednie rzeczy --
    setUpButtons();
    setUpLabels();
    setUpPlottables();
    placeOnGrid();
    // -- dajemy nowe rzeczy do roboty --
    this->setGeometry(300, 300, 1280, 720);
    this->setVisible(true);
}

void Rms_sec_widget::setUpButtons()
{
    // -- rozmiary --
    recalculateIntegration->setMaximumSize(10000,10000);
    exportRmsVsTme->setMaximumSize(10000,10000);
    exportTintVsTme->setMaximumSize(10000,10000);
    exportTsysVsTme->setMaximumSize(10000,10000);
    exportAllVSTme->setMaximumSize(10000,10000);
    showSelectedSpectrum->setMaximumSize(10000,10000);
    recalculateIntegration->setMinimumSize(0,0);
    exportRmsVsTme->setMinimumSize(0,0);
    exportTintVsTme->setMinimumSize(0,0);
    exportTsysVsTme->setMinimumSize(0,0);
    exportAllVSTme->setMinimumSize(0,0);
    showSelectedSpectrum->setMinimumSize(0,0);
    // -- teksty --
    recalculateIntegration->setText("Recalculate integration");
    exportRmsVsTme->setText("Export rms vs time");
    exportTintVsTme->setText("Export Tsys vs time");
    exportTsysVsTme->setText("Export Integrated flux vs time");
    exportAllVSTme->setText("Export all of the above");
    showSelectedSpectrum->setText("Show selected spectrum");
    // -- text edity --
    RmsIntStart->setMaximumSize(100,40);
    RmsIntEnd->setMaximumSize(100,40);
    RmsIntStart->setText("500");
    RmsIntEnd->setText("1500");
    // -- checkboxy --
    IOnRms->setChecked(true);
    VOnRms->setChecked(false);
    LHCOnRms->setChecked(false);
    RHCOnRms->setChecked(false);

}

void Rms_sec_widget::setUpLabels()
{
    // -- czcionka --
    QFont f( "Arial", 10, QFont::Bold);
    // -- teksty labeli --
    stokesParams->setText("Stokes parameters");
    intParamsLabel->setText("Integration parameters");
    exportingSecLabel->setText("Exporting");
    graphParamsLabel->setText("Plot properties");
    // -- fonty --
    stokesParams->setFont(f);
    intParamsLabel->setFont(f);
    exportingSecLabel->setFont(f);
    graphParamsLabel->setFont(f);
}

void Rms_sec_widget::setUpPlottables()
{

}

void Rms_sec_widget::placeOnGrid()
{
    // -- grid ma szerokość 16x16 --
    // -- dodajemy trzy ploty --
    grid->addWidget(RmsVsTime, 0, 0, 8, 8);
    grid->addWidget(tsysVsTime, 8, 0, 8, 8);
    grid->addWidget(intVsTime, 0, 8, 8, 8);
    // -- stokes params --
    grid->addWidget(stokesParams, 8,8, 1,4);
    grid->addWidget(IOnRms, 9,8,1,1);
    grid->addWidget(VOnRms, 9,9,1,1);
    grid->addWidget(LHCOnRms, 9,10,1,1);
    grid->addWidget(RHCOnRms, 9,11,1,1);
    // -- integration parameters --
    grid->addWidget(intParamsLabel, 10,8,1,4);
    grid->addWidget(RmsIntStart, 11,11,1,1);
    grid->addWidget(RmsIntEnd, 12,11,1,1);
    grid->addWidget(recalculateIntegration, 13,8,1,4);
    // -- exporting --
    grid->addWidget(exportingSecLabel,      8,12,1,4);
    grid->addWidget(exportRmsVsTme,        9,12,1,4);
    grid->addWidget(exportTsysVsTme,      10,12,1,4);
    grid->addWidget(exportTintVsTme,      11,12,1,4);
    grid->addWidget(exportAllVSTme,       12,12,1,4);
    // -- plot properties --
    grid->addWidget(graphParamsLabel,     13,12,1,4);
    grid->addWidget(showPoints,           14,12,1,1);
    grid->addWidget(showLines,            14,14,1,1);
    grid->addWidget(rectZoom,             15,12,1,1);
    grid->addWidget(selectionOfPoint,     15,14,1,1);
    grid->addWidget(showSelectedSpectrum, 14,8,2,4);
    // ---- row stretche ---
    for(int i = 0; i < grid->rowCount(); i++)
        grid->setRowStretch(i,1);
    for(int i = 0; i < grid->columnCount(); i++)
        grid->setColumnStretch(i,1);
}
