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
    startIntegrateLabel->setText("Integration start channel");
    endIntegrateLabel->setText("Integration end channel");
    // -- fonty --
    stokesParams->setFont(f);
    intParamsLabel->setFont(f);
    exportingSecLabel->setFont(f);
    graphParamsLabel->setFont(f);
}

void Rms_sec_widget::setUpPlottables()
{
    // -- robimy setup --
    // --- pens ---
    QPen penLHC(Qt::red);
    QPen penRHC(Qt::green);
    QPen penV (Qt::black); // Qt::white used in case of dark mode
    QPen penI (QColor(0,0,255)); // QColor(135,206,250)) used in case of dark mode
    QPen pensForGraphs[4] = {penI, penV, penLHC, penRHC};
    std::string names[4] = {"I", "V", "LHC", "RHC"};
    // -- dodajemy graphy z polaryzacjami --
    for(int i = 0; i < 4; i++)
    {
        // -- adding graphs --
        RmsVsTime->addGraph();
        intVsTime->addGraph();
        // -- setting properties --
        RmsVsTime->graph(i)->setLineStyle(QCPGraph::lsNone);
        RmsVsTime->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        intVsTime->graph(i)->setLineStyle(QCPGraph::lsNone);
        intVsTime->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        // -- setting pens --
        RmsVsTime->graph(i)->setPen(pensForGraphs[i]);
        intVsTime->graph(i)->setPen(pensForGraphs[i]);
        // -- setting visibilities --
        if (i != 0)
        {
            RmsVsTime->graph(i)->setVisible(false);
            intVsTime->graph(i)->setVisible(false);
        }
        // -- setting names --
        RmsVsTime->graph(i)->setName(names[i].c_str());
        intVsTime->graph(i)->setName(names[i].c_str());
        // ---------------------------
    }
    // -- setup tsys vs time --
    tsysVsTime->addGraph();
    tsysVsTime->graph(0)->setLineStyle(QCPGraph::lsNone);
    tsysVsTime->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    tsysVsTime->graph(0)->setPen(pensForGraphs[0]);

    // -- dodajemy graphy z kółeczkami zaznaczenia --
    for(int i = 0; i < 4; i++)
    {
        RmsVsTime->addGraph();
        intVsTime->addGraph();
        // --
        if (i != 2)
        {
            RmsVsTime->graph(4+i)->setPen(QPen(Qt::red));
            intVsTime->graph(4+i)->setPen(QPen(Qt::red));
        }
        else
        {
            RmsVsTime->graph(4+i)->setPen(QPen(Qt::blue));
            intVsTime->graph(4+i)->setPen(QPen(Qt::blue));
        }
        // --
        RmsVsTime->graph(4+i)->setLineStyle(QCPGraph::lsNone);
        intVsTime->graph(4+i)->setLineStyle(QCPGraph::lsNone);
        // --
        RmsVsTime->graph(4+i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
        intVsTime->graph(4+i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
        // --
        RmsVsTime->graph(4+i)->setVisible(false);
        intVsTime->graph(4+i)->setVisible(false);
        // --
        RmsVsTime->graph(4+i)->removeFromLegend();
        intVsTime->graph(4+i)->removeFromLegend();
    }
    tsysVsTime->addGraph();
    tsysVsTime->graph(1)->setLineStyle(QCPGraph::lsNone);
    tsysVsTime->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    tsysVsTime->graph(1)->setPen(QPen(Qt::red));
    tsysVsTime->graph(1)->setVisible(false);
    tsysVsTime->graph(1)->removeFromLegend();


    // -- labele --
    RmsVsTime->xAxis->setLabel("MJD");
    RmsVsTime->yAxis->setLabel("RMS");
    intVsTime->xAxis->setLabel("MJD");
    intVsTime->yAxis->setLabel("Integrated amplitude");
    tsysVsTime->xAxis->setLabel("MJD");
    tsysVsTime->yAxis->setLabel("Tsys (K)");
    // -- interakcje --
    RmsVsTime->setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
    RmsVsTime->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    RmsVsTime->axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    RmsVsTime->axisRect()->setRangeZoomAxes(RmsVsTime->xAxis, RmsVsTime->yAxis);
    RmsVsTime->setSelectionRectMode(QCP::srmZoom);
    RmsVsTime->setCursor(QCursor(Qt::CrossCursor));

    intVsTime->setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
    intVsTime->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    intVsTime->axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    intVsTime->axisRect()->setRangeZoomAxes(intVsTime->xAxis, intVsTime->yAxis);
    intVsTime->setSelectionRectMode(QCP::srmZoom);
    intVsTime->setCursor(QCursor(Qt::CrossCursor));

    tsysVsTime->setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
    tsysVsTime->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    tsysVsTime->axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    tsysVsTime->axisRect()->setRangeZoomAxes(tsysVsTime->xAxis, tsysVsTime->yAxis);
    tsysVsTime->setSelectionRectMode(QCP::srmZoom);
    tsysVsTime->setCursor(QCursor(Qt::CrossCursor));

    // -- xaxis2 i yaxis2 --
    RmsVsTime->xAxis2->setVisible(true);
    RmsVsTime->yAxis2->setVisible(true);
    RmsVsTime->xAxis2->setTickLabels(false);
    RmsVsTime->yAxis2->setTickLabels(false);

    intVsTime->xAxis2->setVisible(true);
    intVsTime->yAxis2->setVisible(true);
    intVsTime->xAxis2->setTickLabels(false);
    intVsTime->yAxis2->setTickLabels(false);

    tsysVsTime->xAxis2->setVisible(true);
    tsysVsTime->yAxis2->setVisible(true);
    tsysVsTime->xAxis2->setTickLabels(false);
    tsysVsTime->yAxis2->setTickLabels(false);

    // -- legenda --
    QFont f( "Arial", 10, QFont::Bold);
    RmsVsTime->legend->setVisible(true);
    RmsVsTime->legend->setFont(f);
    intVsTime->legend->setVisible(true);
    intVsTime->legend->setFont(f);
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
    grid->addWidget(startIntegrateLabel, 11,8,1,3);
    grid->addWidget(endIntegrateLabel, 12,8,1,3);
    grid->addWidget(recalculateIntegration, 13,8,1,4);
    // -- exporting --
    grid->addWidget(exportingSecLabel,      8,12,1,4);
    // ---- export vbox ----
    exportVbox->addWidget(exportRmsVsTme);
    exportVbox->addWidget(exportTsysVsTme);
    exportVbox->addWidget(exportTintVsTme);
    exportVbox->addWidget(exportAllVSTme);
    grid->addLayout(exportVbox, 9,12,4,4);
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
