#include "rms_sec_widget.h"

Rms_sec_widget::Rms_sec_widget(spectral_container * dataTable)
               : dataTable(dataTable)
{
    this->setVisible(false);
    // -- procesujemy odpowiednie rzeczy --
    setUpButtons();
    setUpLabels();
    setUpPlottables();
    placeOnGrid();
    connectElementsToSlots();
    setUpPopupWindow();
}

void Rms_sec_widget::customizeApperance()
{
    /*
     * Customizes apperance of this widget
     */
    this->setDarkModeW();
    setCustomSSDarkOnPopupWindow();
}

void Rms_sec_widget::customizeApperanceLight(){
    /*
     * Customizes apperance of this widget for light mode
     */
    this->setLightModeW();
    setCustomSSLightOnPopupWindow();
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
    autoscaleGraphs->setMaximumSize(10000,10000);
    recalculateIntegration->setMinimumSize(0,0);
    exportRmsVsTme->setMinimumSize(0,0);
    exportTintVsTme->setMinimumSize(0,0);
    exportTsysVsTme->setMinimumSize(0,0);
    exportAllVSTme->setMinimumSize(0,0);
    showSelectedSpectrum->setMinimumSize(0,0);
    autoscaleGraphs->setMinimumSize(0,0);
    // -- teksty --
    recalculateIntegration->setText("Recalculate integration");
    exportRmsVsTme->setText("Export rms vs time");
    exportTintVsTme->setText("Export Tsys vs time");
    exportTsysVsTme->setText("Export Integrated flux vs time");
    exportAllVSTme->setText("Export all of the above");
    showSelectedSpectrum->setText("Show selected spectrum");
    closePopupWIndow->setText("Close");
    flagOnPopupWindow->setText("Flag");
    autoscaleGraphs->setText("Rescale");
    // -- text edity --
    RmsIntStart->setMaximumSize(100,40);
    RmsIntEnd->setMaximumSize(100,40);
    RmsIntStart->setMaximum(9999999);
    RmsIntEnd->setMaximum(9999999);
    RmsIntStart->setValue(500);
    RmsIntEnd->setValue(1500);
    // -- checkboxy --
    IOnRms->setChecked(true);
    VOnRms->setChecked(false);
    LHCOnRms->setChecked(false);
    RHCOnRms->setChecked(false);
    rectZoom->setChecked(true);
    showPoints->setChecked(true);
    showCross->setChecked(true);
}

void Rms_sec_widget::setUpLabels()
{
    // -- czcionka --
    QFont f( "Arial", 10, QFont::Bold);
    // -- teksty labeli --
    stokesParams->setText("Stokes");
    intParamsLabel->setText("Integration parameters");
    //exportingSecLabel->setText("Exporting");
    graphParamsLabel->setText("Plot properties");
    startIntegrateLabel->setText("Integration start channel");
    endIntegrateLabel->setText("Integration end channel");
    // -- fonty --
    stokesParams->setFont(f);
    intParamsLabel->setFont(f);
    //exportingSecLabel->setFont(f);
    graphParamsLabel->setFont(f);
}

void Rms_sec_widget::setUpPlottables()
{
    // -- clearujemy wszystko --
    //RmsVsTime->clearItems();
    //intVsTime->clearItems();
    //tsysVsTime->clearItems();
    // -- robimy setup --
    // -- interakcje --
    RmsVsTime->setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
    RmsVsTime->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    RmsVsTime->axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    RmsVsTime->axisRect()->setRangeZoomAxes(RmsVsTime->xAxis, RmsVsTime->yAxis);
    RmsVsTime->setSelectionRectMode(QCP::srmZoom);
    RmsVsTime->setCursor(QCursor(Qt::CrossCursor));

    intVsTime->setInteractions(QCP::iRangeZoom| QCP::iSelectPlottables);
    intVsTime->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    intVsTime->axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    intVsTime->axisRect()->setRangeZoomAxes(intVsTime->xAxis, intVsTime->yAxis);
    intVsTime->setSelectionRectMode(QCP::srmZoom);
    intVsTime->setCursor(QCursor(Qt::CrossCursor));

    tsysVsTime->setInteractions(QCP::iRangeZoom| QCP::iSelectPlottables);
    tsysVsTime->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    tsysVsTime->axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    tsysVsTime->axisRect()->setRangeZoomAxes(tsysVsTime->xAxis, tsysVsTime->yAxis);
    tsysVsTime->setSelectionRectMode(QCP::srmZoom);
    tsysVsTime->setCursor(QCursor(Qt::CrossCursor));

    spectrumOnPopupWindow->setInteractions(QCP::iRangeZoom| QCP::iSelectPlottables);
    spectrumOnPopupWindow->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    spectrumOnPopupWindow->axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    spectrumOnPopupWindow->axisRect()->setRangeZoomAxes(spectrumOnPopupWindow->xAxis, spectrumOnPopupWindow->yAxis);
    spectrumOnPopupWindow->setSelectionRectMode(QCP::srmZoom);
    spectrumOnPopupWindow->setCursor(QCursor(Qt::CrossCursor));

    // -- labele --
    RmsVsTime->xAxis->setLabel("MJD");
    RmsVsTime->yAxis->setLabel("RMS");
    intVsTime->xAxis->setLabel("MJD");
    intVsTime->yAxis->setLabel("Integrated amplitude");
    tsysVsTime->xAxis->setLabel("MJD");
    tsysVsTime->yAxis->setLabel("Tsys (K)");
    spectrumOnPopupWindow->xAxis->setLabel("Velocity");

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

    spectrumOnPopupWindow->xAxis2->setVisible(true);
    spectrumOnPopupWindow->yAxis2->setVisible(true);
    spectrumOnPopupWindow->xAxis2->setTickLabels(false);
    spectrumOnPopupWindow->yAxis2->setTickLabels(false);

    // -- legenda --
    QFont f( "Arial", 10, QFont::Bold);
    RmsVsTime->legend->setVisible(true);
    RmsVsTime->legend->setFont(f);
    RmsVsTime->legend->setBrush(QColor(255, 255, 255, 50));
    RmsVsTime->legend->setBorderPen(QPen(Qt::transparent));
    intVsTime->legend->setVisible(true);
    intVsTime->legend->setFont(f);
    intVsTime->legend->setBrush(QColor(255, 255, 255, 50));
    intVsTime->legend->setBorderPen(QPen(Qt::transparent));


    // -- connecting the axis --
    connect(RmsVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), RmsVsTime->xAxis2, SLOT(setRange(QCPRange)) );
    connect(RmsVsTime->yAxis, SIGNAL(rangeChanged(QCPRange)), RmsVsTime->yAxis2, SLOT(setRange(QCPRange)) );
    connect(tsysVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), tsysVsTime->xAxis2, SLOT(setRange(QCPRange)) );
    connect(tsysVsTime->yAxis, SIGNAL(rangeChanged(QCPRange)), tsysVsTime->yAxis2, SLOT(setRange(QCPRange)) );
    connect(intVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), intVsTime->xAxis2, SLOT(setRange(QCPRange)) );
    connect(intVsTime->yAxis, SIGNAL(rangeChanged(QCPRange)), intVsTime->yAxis2, SLOT(setRange(QCPRange)) );
    connect(spectrumOnPopupWindow->xAxis, SIGNAL(rangeChanged(QCPRange)), spectrumOnPopupWindow->xAxis2, SLOT(setRange(QCPRange)) );
    connect(spectrumOnPopupWindow->yAxis, SIGNAL(rangeChanged(QCPRange)), spectrumOnPopupWindow->yAxis2, SLOT(setRange(QCPRange)) );
    // -- connecting axes between each other --
    connect(RmsVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), tsysVsTime->xAxis, SLOT(setRange(QCPRange)) );
    connect(RmsVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), intVsTime->xAxis, SLOT(setRange(QCPRange)) );
    connect(tsysVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), RmsVsTime->xAxis, SLOT(setRange(QCPRange)) );
    connect(tsysVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), intVsTime->xAxis, SLOT(setRange(QCPRange)) );
    connect(intVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), RmsVsTime->xAxis, SLOT(setRange(QCPRange)) );
    connect(intVsTime->xAxis, SIGNAL(rangeChanged(QCPRange)), tsysVsTime->xAxis, SLOT(setRange(QCPRange)) );


    // -- connecting crosshairs --
    QObject::connect(RmsVsTime, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(crossHairRmsVsTime(QMouseEvent*)));
    QObject::connect(tsysVsTime, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(crossHairTsysVsTime(QMouseEvent*)));
    QObject::connect(intVsTime, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(crossHairTintVsTime(QMouseEvent*)));

    // --- pens ---
    QPen penLHC(Qt::red);
    QPen penRHC(Qt::green);
    QPen penV (Qt::black); // Qt::white used in case of dark mode
    QPen penI (QColor(0,0,255)); // QColor(135,206,250)) used in case of dark mode
    QPen pensForGraphs[4] = {penI, penV, penLHC, penRHC};
    std::string names[4] = {"I", "V", "LHC", "RHC"};
    // -- selection decorator --
    dekorator->setPen(QPen(Qt::magenta));
    //dekorator->setUsedScatterProperties(QCPScatterStyle::ScatterProperty::spSize);
    dekorator->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 8),  QCPScatterStyle::ScatterProperty::spSize);

    // -- dodajemy graphy z polaryzacjami --
    for(int i = 0; i < 4; i++)
    {
        // -- adding graphs --
        RmsVsTime->addGraph();
        intVsTime->addGraph();
        spectrumOnPopupWindow->addGraph();
        // -- setting properties --
        RmsVsTime->graph(i)->setLineStyle(QCPGraph::lsNone);
        RmsVsTime->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        intVsTime->graph(i)->setLineStyle(QCPGraph::lsNone);
        intVsTime->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        spectrumOnPopupWindow->graph(i)->setLineStyle(QCPGraph::lsNone);
        spectrumOnPopupWindow->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        // -- selected pens --
        QCPSelectionDecorator * dekRMS = new QCPSelectionDecorator();
        dekRMS->copyFrom(dekorator);
        QCPSelectionDecorator * dekINT = new QCPSelectionDecorator();
        dekINT->copyFrom(dekorator);
        RmsVsTime->graph(i)->setSelectionDecorator(dekRMS);
        intVsTime->graph(i)->setSelectionDecorator(dekINT);
        // -- setting pens --
        RmsVsTime->graph(i)->setPen(pensForGraphs[i]);
        intVsTime->graph(i)->setPen(pensForGraphs[i]);
        spectrumOnPopupWindow->graph(i)->setPen(pensForGraphs[i]);
        // -- setting visibilities --
        if (i != 0)
        {
            RmsVsTime->graph(i)->setVisible(false);
            intVsTime->graph(i)->setVisible(false);
            spectrumOnPopupWindow->graph(i)->setVisible(false);
        }
        // -- setting names --
        RmsVsTime->graph(i)->setName(names[i].c_str());
        intVsTime->graph(i)->setName(names[i].c_str());
        spectrumOnPopupWindow->graph(i)->setName(names[i].c_str());
        // ---------------------------
        // -- selection --
        RmsVsTime->graph(i)->setSelectable(QCP::stSingleData);
        intVsTime->graph(i)->setSelectable(QCP::stSingleData);
        spectrumOnPopupWindow->graph(i)->setSelectable(QCP::stSingleData);
    }

    // -- setup tsys vs time --
    tsysVsTime->addGraph();
    tsysVsTime->graph(0)->setLineStyle(QCPGraph::lsNone);
    tsysVsTime->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    tsysVsTime->graph(0)->setPen(pensForGraphs[0]);
    tsysVsTime->graph(0)->setSelectable(QCP::stSingleData);
    QCPSelectionDecorator * dekTSYS = new QCPSelectionDecorator();
    dekTSYS->copyFrom(dekorator);
    tsysVsTime->graph(0)->setSelectionDecorator(dekTSYS);

    connect(RmsVsTime, SIGNAL( selectionChangedByUser() ), this, SLOT(setSelectionOnRms() ) );
    connect(tsysVsTime, SIGNAL( selectionChangedByUser() ), this, SLOT(setSelectionOnTsys() ) );
    connect(intVsTime, SIGNAL( selectionChangedByUser() ), this, SLOT(setSelectionOnInt() ) );
}

void Rms_sec_widget::placeOnGrid()
{
    RmsVsTime_layout->addWidget(RmsVsTime);
    tsysVsTime_layout->addWidget(tsysVsTime);
    intVsTime_layout->addWidget(intVsTime);

    // -- grid ma szerokość 16x16 --
    // -- dodajemy trzy ploty --
    grid->addWidget(RmsVsTime_w, 0, 0, 8, 8);
    grid->addWidget(tsysVsTime_w, 8, 0, 8, 8);
    grid->addWidget(intVsTime_w, 0, 8, 8, 8);
    grid->setSpacing(10);
    // -- stokes params --
    plotSettingsGrid->addWidget(stokesParams, 0,0);
    plotSettingsGrid->addWidget(IOnRms,       1,0,1,1);
    plotSettingsGrid->addWidget(VOnRms,       1,1,1,1);
    plotSettingsGrid->addWidget(LHCOnRms,     1,2,1,1);
    plotSettingsGrid->addWidget(RHCOnRms,     1,3,1,1);

    plotSettingsGrid->addWidget(graphParamsLabel,     2,0,1,4);
    plotSettingsGrid->addWidget(showPoints,           3,0,1,1);
    plotSettingsGrid->addWidget(showLines,            3,1,1,1);
    plotSettingsGrid->addWidget(rectZoom,             3,2,1,1);
    plotSettingsGrid->addWidget(showCross,             3,3,1,1);
    plotSettingsGrid->addWidget(showSelectedSpectrum, 4,0,1,2);
    plotSettingsGrid->addWidget(autoscaleGraphs,      4,2,1,2);

    // -- data export --
    exportVbox->addWidget(exportRmsVsTme);
    exportVbox->addWidget(exportTsysVsTme);
    exportVbox->addWidget(exportTintVsTme);
    exportVbox->addWidget(exportAllVSTme);
    dataExportGrid->addLayout(exportVbox, 0,0);
    // ---- row stretche ---
    for(int i = 0; i < plotSettingsGrid->rowCount(); i++)
        plotSettingsGrid->setRowStretch(i,1);
    for(int i = 0; i < plotSettingsGrid->columnCount(); i++)
        plotSettingsGrid->setColumnStretch(i,1);

    // -- integration parameters --
    otherToolsGrid->addWidget(intParamsLabel,         0,0,1,4);
    otherToolsGrid->addWidget(startIntegrateLabel,    1,0,1,3);
    otherToolsGrid->addWidget(RmsIntStart,            1,3,1,1);
    otherToolsGrid->addWidget(endIntegrateLabel,      2,0,1,3);
    otherToolsGrid->addWidget(RmsIntEnd,              2,3,1,1);
    otherToolsGrid->addWidget(recalculateIntegration, 3,0,1,4);


//
//    grid->addWidget(stokesParams, 8,8, 1,4);
//    grid->addWidget(IOnRms, 9,8,1,1);
//    grid->addWidget(VOnRms, 9,9,1,1);
//    grid->addWidget(LHCOnRms, 9,10,1,1);
//    grid->addWidget(RHCOnRms, 9,11,1,1);
//    // -- integration parameters --
//    grid->addWidget(intParamsLabel, 10,8,1,4);
//    grid->addWidget(RmsIntStart, 11,11,1,1);
//    grid->addWidget(RmsIntEnd, 12,11,1,1);
//    grid->addWidget(startIntegrateLabel, 11,8,1,3);
//    grid->addWidget(endIntegrateLabel, 12,8,1,3);
//    grid->addWidget(recalculateIntegration, 13,8,1,4);
//    // -- exporting --
//    grid->addWidget(exportingSecLabel,      8,12,1,4);
//    // ---- export vbox ----
//    exportVbox->addWidget(exportRmsVsTme);
//    exportVbox->addWidget(exportTsysVsTme);
//    exportVbox->addWidget(exportTintVsTme);
//    exportVbox->addWidget(exportAllVSTme);
//    grid->addLayout(exportVbox, 9,12,4,4);
//    // -- plot properties --
//    grid->addWidget(graphParamsLabel,     13,12,1,4);
//    grid->addWidget(showPoints,           14,12,1,1);
//    grid->addWidget(showLines,            14,14,1,1);
//    grid->addWidget(rectZoom,             15,12,1,1);
//    grid->addWidget(showSelectedSpectrum, 14,8,2,2);
//    grid->addWidget(autoscaleGraphs,      14,10,2,2);
    tabTools->addTab(plotSettings, "Plot settings");
    tabTools->addTab(dataExport, "Data export");
    tabTools->addTab(otherTools, "Others");
    grid->addWidget(tabTools, 8,8,8,8);
    // ---- row stretche ---
    for(int i = 0; i < grid->rowCount(); i++)
        grid->setRowStretch(i,1);
    for(int i = 0; i < grid->columnCount(); i++)
        grid->setColumnStretch(i,1);
}

void Rms_sec_widget::connectElementsToSlots()
{
    QObject::connect(rectZoom, SIGNAL(clicked()), this, SLOT(changeInteractions()));

    QObject::connect(IOnRms, SIGNAL(clicked()), this, SLOT(showIVLR()));
    QObject::connect(VOnRms, SIGNAL(clicked()), this, SLOT(showIVLR()));
    QObject::connect(LHCOnRms, SIGNAL(clicked()), this, SLOT(showIVLR()));
    QObject::connect(RHCOnRms, SIGNAL(clicked()), this, SLOT(showIVLR()));

    QObject::connect(showPoints, SIGNAL(clicked()), this, SLOT(showPointsSlot()));
    QObject::connect(showLines, SIGNAL(clicked()), this, SLOT(showLinesSlot()));

    QObject::connect(exportRmsVsTme, SIGNAL(clicked()), this, SLOT(exportRmsVsTimeSlot()));
    QObject::connect(exportTintVsTme, SIGNAL(clicked()), this, SLOT(exportTintVsTimeSlot()));
    QObject::connect(exportTsysVsTme, SIGNAL(clicked()), this, SLOT(exportTsysVsTimeSlot()));
    QObject::connect(exportAllVSTme, SIGNAL(clicked()), this, SLOT(exportAllAboveSlot()));

    QObject::connect(recalculateIntegration, SIGNAL(clicked()), this, SLOT(recalculateIntegrationSlot()) );

    QObject::connect(showSelectedSpectrum, SIGNAL(clicked()), this, SLOT(showPopupWindowSlot()) );

    QObject::connect(closePopupWIndow, SIGNAL(clicked()), this, SLOT(closePopupWindowSlot()));
    QObject::connect(autoscaleGraphs, SIGNAL(clicked()), this, SLOT(rescaleGraphs()));

    QObject::connect(flagOnPopupWindow, SIGNAL(clicked()), this, SLOT(flagActualEpoch()));

    QObject::connect(showCross, SIGNAL(clicked()), this, SLOT(showCrosshairSlot()));
}

void Rms_sec_widget::setUpPopupWindow()
{
    popupWindow->setVisible(false);
    popupWindow->setGeometry(300, 300, 1320, 720);

    spectrumOnPopupWindow_layout->addWidget(spectrumOnPopupWindow);
    // -- dodajemy plot do gridu --
    gridOfPopupWindow->addWidget(spectrumOnPopupWindow_w, 0, 0, 6,6);
    gridOfPopupWindow->addWidget(flagOnPopupWindow, 6, 0, 1, 3);
    gridOfPopupWindow->addWidget(closePopupWIndow, 6, 3, 1,3);
    gridOfPopupWindow->addWidget(labelOnPopupWindow, 0, 6, 6, 3);
}

void Rms_sec_widget::changeInteractions()
{
    if(rectZoom->isChecked())
    {
        RmsVsTime->setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
        RmsVsTime->setSelectionRectMode(QCP::srmZoom);
        RmsVsTime->setCursor(QCursor(Qt::CrossCursor));
        tsysVsTime->setInteractions(QCP::iRangeZoom| QCP::iSelectPlottables);
        tsysVsTime->setSelectionRectMode(QCP::srmZoom);
        tsysVsTime->setCursor(QCursor(Qt::CrossCursor));
        intVsTime->setInteractions(QCP::iRangeZoom| QCP::iSelectPlottables);
        intVsTime->setSelectionRectMode(QCP::srmZoom);
        intVsTime->setCursor(QCursor(Qt::CrossCursor));
        spectrumOnPopupWindow->setInteractions(QCP::iRangeZoom| QCP::iSelectPlottables);
        spectrumOnPopupWindow->setSelectionRectMode(QCP::srmZoom);
        spectrumOnPopupWindow->setCursor(QCursor(Qt::CrossCursor));
    }
    else
    {
        RmsVsTime->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectPlottables);
        RmsVsTime->setSelectionRectMode(QCP::srmNone);
        RmsVsTime->setCursor(QCursor(Qt::ArrowCursor));
        tsysVsTime->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectPlottables);
        tsysVsTime->setSelectionRectMode(QCP::srmNone);
        tsysVsTime->setCursor(QCursor(Qt::ArrowCursor));
        intVsTime->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectPlottables);
        intVsTime->setSelectionRectMode(QCP::srmNone);
        intVsTime->setCursor(QCursor(Qt::ArrowCursor));
        spectrumOnPopupWindow->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectPlottables);
        spectrumOnPopupWindow->setSelectionRectMode(QCP::srmNone);
        spectrumOnPopupWindow->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void Rms_sec_widget::showPointsSlot()
{
    QCPScatterStyle style;
    if(!showPoints->isChecked())
    {
        style.setShape(QCPScatterStyle::ssNone);
    }
    else
    {
        style.setShape(QCPScatterStyle::ssDisc);
        style.setSize(4);
    }

    for(int i =0; i < 4; i++)
    {
        RmsVsTime->graph(i)->setScatterStyle(style);
        intVsTime->graph(i)->setScatterStyle(style);
        spectrumOnPopupWindow->graph(i)->setScatterStyle(style);
    }
    tsysVsTime->graph(0)->setScatterStyle(style);
    replotGraphs();
}

void Rms_sec_widget::showLinesSlot()
{
    if (!showLines->isChecked())
    {
        for(int i =0; i < 4; i++)
        {
            RmsVsTime->graph(i)->setLineStyle(QCPGraph::lsNone);
            intVsTime->graph(i)->setLineStyle(QCPGraph::lsNone);
            spectrumOnPopupWindow->graph(i)->setLineStyle(QCPGraph::lsNone);
        }
        tsysVsTime->graph(0)->setLineStyle(QCPGraph::lsNone);
    }
    else
    {
        for(int i =0; i < 4; i++)
        {
            RmsVsTime->graph(i)->setLineStyle(QCPGraph::lsLine);
            intVsTime->graph(i)->setLineStyle(QCPGraph::lsLine);
            spectrumOnPopupWindow->graph(i)->setLineStyle(QCPGraph::lsLine);
        }
        tsysVsTime->graph(0)->setLineStyle(QCPGraph::lsLine);
    }
    replotGraphs();
}

void Rms_sec_widget::showIVLR()
{
    bool vis[4] = {false, false, false, false};
    if(IOnRms->isChecked())
        vis[0] = true;
    if(VOnRms->isChecked())
        vis[1] = true;
    if(LHCOnRms->isChecked())
        vis[2] = true;
    if(RHCOnRms->isChecked())
        vis[3] = true;
    for(int i = 0; i < 4; i++)
    {
        RmsVsTime->graph(i)->setVisible(vis[i]);
        intVsTime->graph(i)->setVisible(vis[i]);
        spectrumOnPopupWindow->graph(i)->setVisible(vis[i]);
    }
    replotGraphs();
}

void Rms_sec_widget::fillWithData()
{

    // -- gdy nie załadowano danych --
    if (!dataTable->loadedData)
        return;

    /* BUGFIX */
    // -- czyścimy zaznaczenia --
    clearGraphSelections();
    indexOfTheSpectrum = 0;
    if (popupWindow->isVisible())
        popupWindow->setVisible(false);

    // -- zaczynamy pisać --
    // - w stylue c: deklarujemy kontenery -
    unsigned long int size = dataTable->spectraTableIERR.size();
    QVector < double > mjdTab(size), iRms(size), vRms(size), lhcRms(size), rhcRms(size), tsys(size);
    // - zapełniamy wektory -
    for(unsigned long int i = 0; i < size; i++)
    {
        // --
        mjdTab[i] = dataTable->mjdTable[i];
        // --
        iRms[i] = dataTable->spectraTableIERR[i];
        vRms[i] = dataTable->spectraTableVERR[i];
        lhcRms[i] = dataTable->spectraTableLHCERR[i];
        rhcRms[i] = dataTable->spectraTableRHCERR[i];
        // --
        tsys[i] = dataTable->tsysTable[i];
    }
    recalculateIntegrationSlot();
    // -- dodajemy do graphów --
    // - RMS -
    RmsVsTime->graph(0)->setData(mjdTab, iRms);
    RmsVsTime->graph(1)->setData(mjdTab, vRms);
    RmsVsTime->graph(2)->setData(mjdTab, lhcRms);
    RmsVsTime->graph(3)->setData(mjdTab, rhcRms);
    // - tsys -
    tsysVsTime->graph(0)->setData(mjdTab, tsys);
    // - skalowanie wykresów -
    autoscaleGraph(RmsVsTime);
    autoscaleGraph(tsysVsTime);
    replotGraphs();
}

void Rms_sec_widget::replotGraphs()
{
    RmsVsTime->replot();
    tsysVsTime->replot();
    intVsTime->replot();
    spectrumOnPopupWindow->replot();
}

void Rms_sec_widget::autoscaleGraph(QCustomPlot * plot)
{
    plot->rescaleAxes();
    double max_x, min_x, max_y, min_y;
    max_x = plot->xAxis->range().upper;
    min_x = plot->xAxis->range().lower;
    max_y = plot->yAxis->range().upper;
    min_y = plot->yAxis->range().lower;
    double diffrence_x = max_x - min_x;
    double diffrence_y = max_y - min_y;
    plot->xAxis->setRange(min_x - (0.05 * diffrence_x), max_x + (0.05 * diffrence_x));
    plot->yAxis->setRange(min_y - (0.05 * diffrence_y), max_y + (0.05 * diffrence_y));
}

std::vector < std::vector < double > > Rms_sec_widget::getIntegrateFromDataTable()
{
    int min = getChannel(RmsIntStart);
    int max = getChannel(RmsIntEnd);
    if(min < 1)
    {
        min = 1;
        RmsIntStart->setValue(1);
    }
    if (max > (int) dataTable->spectraTableI[0].size())
    {
        max = (int) dataTable->spectraTableI[0].size();
        RmsIntEnd->setValue( (int) dataTable->spectraTableI[0].size());
    }
    return dataTable->getIntegrate(min,max);
}

int Rms_sec_widget::getChannel(QSpinBox * pole)
{
    return pole->value();
}

void Rms_sec_widget::setDarkMode()
{
    // -- wykresy, tła --
    QPen spinesPen(Qt::white);
    QPen background(Qt::transparent);
    colorCanvas(background, spinesPen);
    // -- dane --
    QPen dataPen(QColor(135,206,250));
    RmsVsTime->graph(0)->setPen(dataPen);
    RmsVsTime->graph(1)->setPen(QPen(Qt::white));
    intVsTime->graph(0)->setPen(dataPen);
    intVsTime->graph(1)->setPen(QPen(Qt::white));
    tsysVsTime->graph(0)->setPen(dataPen);
    spectrumOnPopupWindow->graph(0)->setPen(dataPen);
    spectrumOnPopupWindow->graph(1)->setPen(QPen(Qt::white));
    // -- crosshair --
    QPen crossPen(Qt::white);
    crossPen.setStyle(Qt::DashLine);
    setCrosshairPen(crossPen);
    rmsCshLabel->setColor(Qt::white);
    tsysCshLabel->setColor(Qt::white);
    tintCshLabel->setColor(Qt::white);
    // --------------
    customizeApperance();
    // replotujemy
    replotGraphs();
}

void Rms_sec_widget::setLightMode()
{
    QPen spinesPen(Qt::black);
    QPen background(Qt::transparent);
    colorCanvas(background, spinesPen);
    QPen dataPen(QColor(0,0,255));
    RmsVsTime->graph(0)->setPen(dataPen);
    RmsVsTime->graph(1)->setPen(QPen(Qt::black));
    intVsTime->graph(0)->setPen(dataPen);
    intVsTime->graph(1)->setPen(QPen(Qt::black));
    tsysVsTime->graph(0)->setPen(dataPen);
    spectrumOnPopupWindow->graph(0)->setPen(dataPen);
    spectrumOnPopupWindow->graph(1)->setPen(QPen(Qt::black));
    // -- crosshair --
    QPen crossPen(Qt::black);
    crossPen.setStyle(Qt::DashLine);
    setCrosshairPen(crossPen);
    rmsCshLabel->setColor(Qt::black);
    tsysCshLabel->setColor(Qt::black);
    tintCshLabel->setColor(Qt::black);
    // --------------
    customizeApperanceLight();
    // replotujemy
    replotGraphs();
}

void Rms_sec_widget::colorCanvas(QPen background, QPen spines)
{
    // -- tło --
    RmsVsTime->setBackground(background.color());
    RmsVsTime->axisRect()->setBackground(background.color());
    // -- spines --
    colorSpines(RmsVsTime, spines);
    // ---------------------------------
    // -- tło --
    tsysVsTime->setBackground(background.color());
    tsysVsTime->axisRect()->setBackground(background.color());
    // -- spines --
    colorSpines(tsysVsTime, spines);
    // ---------------------------------
    // -- tło --
    intVsTime->setBackground(background.color());
    intVsTime->axisRect()->setBackground(background.color());
    // -- spines --
    colorSpines(intVsTime, spines);
    // ---------------------------------
    // -- tło --
    spectrumOnPopupWindow->setBackground(background.color());
    spectrumOnPopupWindow->axisRect()->setBackground(background.color());
    // -- spines --
    colorSpines(spectrumOnPopupWindow, spines);
}

void Rms_sec_widget::colorSpines(QCustomPlot *plot, QPen pendulum)
{
    plot->axisRect()->axis(QCPAxis::atTop)->setBasePen(pendulum);
    plot->axisRect()->axis(QCPAxis::atLeft)->setBasePen(pendulum);
    plot->axisRect()->axis(QCPAxis::atBottom)->setBasePen(pendulum);
    plot->axisRect()->axis(QCPAxis::atRight)->setBasePen(pendulum);
    // - zmiana kolorów czcionki -
    // ticklabele
    plot->xAxis->setTickLabelColor(pendulum.color());
    plot->xAxis2->setTickLabelColor(pendulum.color());
    plot->yAxis->setTickLabelColor(pendulum.color());
    plot->yAxis2->setTickLabelColor(pendulum.color());
    // subtick
    plot->xAxis->setSubTickPen(pendulum);
    plot->xAxis2->setSubTickPen(pendulum);
    plot->yAxis->setSubTickPen(pendulum);
    plot->yAxis2->setSubTickPen(pendulum);
    // tick
    plot->xAxis->setTickPen(pendulum);
    plot->xAxis2->setTickPen(pendulum);
    plot->yAxis->setTickPen(pendulum);
    plot->yAxis2->setTickPen(pendulum);
    // label
    plot->xAxis->setLabelColor(pendulum.color());
    plot->xAxis2->setLabelColor(pendulum.color());
    plot->yAxis->setLabelColor(pendulum.color());
    plot->yAxis2->setLabelColor(pendulum.color());
}

void Rms_sec_widget::darthMode(bool darthModeEnabled)
{
    if(darthModeEnabled)
        setDarkMode();
    else
        setLightMode();
}

void Rms_sec_widget::crossHairRmsVsTime(QMouseEvent* event)
{
    // setting visibilities
    RmsXAxisLine->setVisible(showCross->isChecked());
    RmsYAxisLine->setVisible(showCross->isChecked());
    tsysXAxisLine->setVisible(false);
    tsysYAxisLine->setVisible(false);
    tintXAxisLine->setVisible(false);
    tintYAxisLine->setVisible(false);
    // ----
    rmsCshLabel->setVisible(showCross->isChecked());
    tsysCshLabel->setVisible(false);
    tintCshLabel->setVisible(false);
    // ----

    // -- pozycja --
    double x,y;
    x = RmsVsTime->xAxis->pixelToCoord(event->pos().x());
    y = RmsVsTime->yAxis->pixelToCoord(event->pos().y());
    RmsXAxisLine->start->setCoords(x, -QCPRange::maxRange);
    RmsXAxisLine->end->setCoords(x, QCPRange::maxRange);
    RmsYAxisLine->start->setCoords(-QCPRange::maxRange,y);
    RmsYAxisLine->end->setCoords(QCPRange::maxRange,y);

    // -- label --
    rmsCshLabel->position->setCoords(x,y);
    rmsCshLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    string tekst;
    tekst = "X: " + std::to_string(x) + "\n" + "Y: " + std::to_string(y) + "\n\n";
    rmsCshLabel->setText(tekst.c_str());

    // -- reploty --
    RmsVsTime->replot();
    tsysVsTime->replot();
    intVsTime->replot();
}

void Rms_sec_widget::crossHairTsysVsTime(QMouseEvent* event)
{
    // setting visibilities
    RmsXAxisLine->setVisible(false);
    RmsYAxisLine->setVisible(false);
    tsysXAxisLine->setVisible(showCross->isChecked());
    tsysYAxisLine->setVisible(showCross->isChecked());
    tintXAxisLine->setVisible(false);
    tintYAxisLine->setVisible(false);
    // ----
    rmsCshLabel->setVisible(false);
    tsysCshLabel->setVisible(showCross->isChecked());
    tintCshLabel->setVisible(false);
    // ----

    // -- pozycja --
    double x,y;
    x = tsysVsTime->xAxis->pixelToCoord(event->pos().x());
    y = tsysVsTime->yAxis->pixelToCoord(event->pos().y());
    tsysXAxisLine->start->setCoords(x, -QCPRange::maxRange);
    tsysXAxisLine->end->setCoords(x, QCPRange::maxRange);
    tsysYAxisLine->start->setCoords(-QCPRange::maxRange,y);
    tsysYAxisLine->end->setCoords(QCPRange::maxRange,y);

    // -- label --
    tsysCshLabel->position->setCoords(x,y);
    tsysCshLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    string tekst;
    tekst = "X: " + std::to_string(x) + "\n" + "Y: " + std::to_string(y) + "\n\n";
    tsysCshLabel->setText(tekst.c_str());

    // -- reploty --
    RmsVsTime->replot();
    tsysVsTime->replot();
    intVsTime->replot();
}

void Rms_sec_widget::crossHairTintVsTime(QMouseEvent* event)
{
    // setting visibilities
    RmsXAxisLine->setVisible(false);
    RmsYAxisLine->setVisible(false);
    tsysXAxisLine->setVisible(false);
    tsysYAxisLine->setVisible(false);
    tintXAxisLine->setVisible(showCross->isChecked());
    tintYAxisLine->setVisible(showCross->isChecked());
    // ----
    rmsCshLabel->setVisible(false);
    tsysCshLabel->setVisible(false);
    tintCshLabel->setVisible(showCross->isChecked());
    // ----

    // -- pozycja --
    double x,y;
    x = intVsTime->xAxis->pixelToCoord(event->pos().x());
    y = intVsTime->yAxis->pixelToCoord(event->pos().y());
    tintXAxisLine->start->setCoords(x, -QCPRange::maxRange);
    tintXAxisLine->end->setCoords(x, QCPRange::maxRange);
    tintYAxisLine->start->setCoords(-QCPRange::maxRange,y);
    tintYAxisLine->end->setCoords(QCPRange::maxRange,y);

    // -- label --
    tintCshLabel->position->setCoords(x,y);
    tintCshLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    string tekst;
    tekst = "X: " + std::to_string(x) + "\n" + "Y: " + std::to_string(y) + "\n\n";
    tintCshLabel->setText(tekst.c_str());

    // -- reploty --
    RmsVsTime->replot();
    tsysVsTime->replot();
    intVsTime->replot();
}

void Rms_sec_widget::setCrosshairPen(QPen pen)
{
    // -- axis linesy --
    RmsXAxisLine->setPen(pen);
    RmsYAxisLine->setPen(pen);
    tsysXAxisLine->setPen(pen);
    tsysYAxisLine->setPen(pen);
    tintXAxisLine->setPen(pen);
    tintYAxisLine->setPen(pen);
}

void Rms_sec_widget::exportRmsVsTimeSlot()
{
    dataTable->exportRmsData();
    string message = "Saved Rms vs Time to\n" + dataTable->getFileNameForExportedRms();
    QMessageBox::information(this, tr("Message to you"), QString::fromStdString(message));
}

void Rms_sec_widget::exportTintVsTimeSlot()
{
    int min = getChannel(RmsIntStart);
    int max = getChannel(RmsIntEnd);
    dataTable->integrate4Pols(min, max, 0);
    // --- wiadomość końcowa ---
    string message = "";
    message = "Integrated over channels " + std::to_string(min) + " -> " + std::to_string(max) + "\n" + "Saved to " + dataTable->getIntegrationFileName(min, max);
    QMessageBox::information(this, tr("Message to you"), QString::fromStdString(message));

}

void Rms_sec_widget::exportTsysVsTimeSlot()
{
    dataTable->exportTsysData();
    string message = "Saved Tsys vs Time to\n" + dataTable->getFileNameForExportedTsys();
    QMessageBox::information(this, tr("Message to you"), QString::fromStdString(message));
}

void Rms_sec_widget::exportAllAboveSlot()
{
    exportRmsVsTimeSlot();
    exportTsysVsTimeSlot();
    exportTintVsTimeSlot();
}

void Rms_sec_widget::recalculateIntegrationSlot()
{
    std::vector < std::vector < double > > calki = getIntegrateFromDataTable();
    unsigned long int size = dataTable->spectraTableIERR.size();
    QVector < double > mjdTab(size), sintI(size), sintV(size), sintLhc(size), sintRhc(size);
    // - zapełniamy wektory -
    for(unsigned long int i = 0; i < size; i++)
    {
        // --
        mjdTab[i] = dataTable->mjdTable[i];
        // --
        sintI[i] = calki[0][i];
        sintV[i] = calki[1][i];
        sintLhc[i] = calki[2][i];
        sintRhc[i] = calki[3][i];
    }
    // - INT -
    intVsTime->graph(0)->setData(mjdTab, sintI);
    intVsTime->graph(1)->setData(mjdTab, sintV);
    intVsTime->graph(2)->setData(mjdTab, sintLhc);
    intVsTime->graph(3)->setData(mjdTab, sintRhc);
    autoscaleGraph(intVsTime);
    intVsTime->replot();
}

void Rms_sec_widget::setSelectionOnRms()
{
  // -- gdy klinkie się tak, żeby selection się wyzerowało --
  if(RmsVsTime->selectedGraphs().size() == 0)
  {
      QCPDataSelection selection;
      for(int i = 0; i < 4; i++)
          {
              RmsVsTime->graph(i)->setSelection(selection);
              intVsTime->graph(i)->setSelection(selection);
          }
          tsysVsTime->graph(0)->setSelection(selection);
      replotGraphs();
      return;
  }
  setSelectionForPlot(RmsVsTime, tsysVsTime, intVsTime);
  replotGraphs();
}

void Rms_sec_widget::setSelectionOnTsys()
{
    // -- gdy klinkie się tak, żeby selection się wyzerowało --
    if(tsysVsTime->selectedGraphs().size() == 0)
    {
        QCPDataSelection selection;
        for(int i = 0; i < 4; i++)
            {
                RmsVsTime->graph(i)->setSelection(selection);
                intVsTime->graph(i)->setSelection(selection);
            }
            tsysVsTime->graph(0)->setSelection(selection);
        replotGraphs();
        return;
    }
    setSelectionForPlot(tsysVsTime, RmsVsTime, intVsTime);
    replotGraphs();
}

void Rms_sec_widget::setSelectionOnInt()
{
    // -- gdy klinkie się tak, żeby selection się wyzerowało --
    if(intVsTime->selectedGraphs().size() == 0)
    {
        QCPDataSelection selection;
        for(int i = 0; i < 4; i++)
            {
                RmsVsTime->graph(i)->setSelection(selection);
                intVsTime->graph(i)->setSelection(selection);
            }
            tsysVsTime->graph(0)->setSelection(selection);
        replotGraphs();
        return;
    }
    setSelectionForPlot(intVsTime, RmsVsTime, tsysVsTime);
    replotGraphs();
}

void Rms_sec_widget::setSelectionForPlot(QCustomPlot *plotSelection, QCustomPlot *plot1, QCustomPlot *plot2)
{
    // -- bierzemy selection --
    QCPDataSelection selection = plotSelection->selectedGraphs().constFirst()->selection();
    // -- zaznaczamy selection na graphah --
    for(int i = 0; i < plotSelection->graphCount(); i++)
        plotSelection->graph(i)->setSelection(selection);
    for(int i = 0; i < plot1->graphCount(); i++)
        plot1->graph(i)->setSelection(selection);
    for(int i = 0; i < plot2->graphCount(); i++)
        plot2->graph(i)->setSelection(selection);
}

void Rms_sec_widget::showPopupWindowSlot()
{
    // -- zabezpieczenie --
    if(RmsVsTime->selectedGraphs().size() == 0)
        return;

    // wyciągamy indeks (xD ile tego)
    int index = RmsVsTime->selectedGraphs().constFirst()->selection().dataRange().begin();

    if (index > (int) dataTable->spectraTableI.size()-1)
        return;

    // zapełniamy popup window danymi
    fillPopupWindowWithData(index);
    popupWindow->setVisible(true);
    popupWindowOpened = true;
}

void Rms_sec_widget::closePopupWindowSlot()
{
    popupWindow->setVisible(false);
    popupWindowOpened = false;
}

void Rms_sec_widget::fillPopupWindowWithData(int index)
{

    // -- gdy nie załadowano danych --
    if (!dataTable->loadedData)
        return;

    if((int) dataTable->spectraTableI.size()-1 < index)
        return;

    indexOfTheSpectrum = index;
    // -- zaczynamy pisać --
    // - w stylue c: deklarujemy kontenery -
    unsigned long int size = dataTable->spectraTableI[index].size();
    QVector < double > velTab(size), Itab(size), vTab(size), lhcTab(size), rhcTab(size);
    // - zapełniamy wektory -
    for(unsigned long int i = 0; i < size; i++)
    {
        // --
        velTab[i] = dataTable->velocityTable[index][i];
        // --
        Itab[i] = dataTable->spectraTableI[index][i];
        vTab[i] = dataTable->spectraTableV[index][i];
        lhcTab[i] = dataTable->spectraTableLHC[index][i];
        rhcTab[i] = dataTable->spectraTableRHC[index][i];
    }
    // -- dodajemy do graphów --
    // - RMS -
    spectrumOnPopupWindow->graph(0)->setData(velTab, Itab);
    spectrumOnPopupWindow->graph(1)->setData(velTab, vTab);
    spectrumOnPopupWindow->graph(2)->setData(velTab, lhcTab);
    spectrumOnPopupWindow->graph(3)->setData(velTab, rhcTab);
    // - label na popup window -
    setLabelOnPopupWindow(index);
    // - skalowanie wykresów -
    autoscaleGraph(spectrumOnPopupWindow);
    spectrumOnPopupWindow->replot();
}

void Rms_sec_widget::setLabelOnPopupWindow(int index)
{
    std::string label_to_popup_window;
    label_to_popup_window = "Filename: " + dataTable->getFileNameFromFullPath(dataTable->fileNamesTab[index]) + "\n";
    label_to_popup_window += "MJD: " + std::to_string(dataTable->mjdTable[index]) + "\n";

    label_to_popup_window += "Date (YYYY MM DD): " + dataTable->isotimeTable[index] +  "\n\n";

    label_to_popup_window += "Tsys: " + std::to_string(dataTable->tsysTable[index]) +"\n\n";
    label_to_popup_window += "RMS (I): " + std::to_string(dataTable->spectraTableIERR[index]) +"\n";
    label_to_popup_window += "RMS (V): " + std::to_string(dataTable->spectraTableVERR[index]) +"\n";
    label_to_popup_window += "RMS (LHC): " + std::to_string(dataTable->spectraTableLHCERR[index]) +"\n";
    label_to_popup_window += "RMS (RHC): " + std::to_string(dataTable->spectraTableRHCERR[index]) +"\n\n";

    labelOnPopupWindow->setText(QString::fromStdString(label_to_popup_window));
}

void Rms_sec_widget::rescaleGraphs()
{
    autoscaleGraph(RmsVsTime);
    autoscaleGraph(tsysVsTime);
    autoscaleGraph(intVsTime);
    autoscaleGraph(spectrumOnPopupWindow);
    replotGraphs();
}

void Rms_sec_widget::flagActualEpoch()
{
    dataTable->flag(indexOfTheSpectrum + 1);
}

void Rms_sec_widget::clearGraphSelections()
{
    for(auto &i: RmsVsTime->selectedGraphs())
        i->selection().clear();
    for(auto &i: tsysVsTime->selectedGraphs())
        i->selection().clear();
    for(auto &i: intVsTime->selectedGraphs())
        i->selection().clear();
}


void Rms_sec_widget::showCrosshairSlot()
{
    if (!showCross->isChecked())
    {
        RmsXAxisLine->setVisible(false);

        RmsYAxisLine->setVisible(false);
        tsysXAxisLine->setVisible(false);
        tsysYAxisLine->setVisible(false);
        tintXAxisLine->setVisible(false);
        tintYAxisLine->setVisible(false);
        rmsCshLabel->setVisible(false);
        tsysCshLabel->setVisible(false);
        tintCshLabel->setVisible(false);
        // -- replotting ==
        RmsVsTime->replot();
        tsysVsTime->replot();
        intVsTime->replot();
    }
}

void Rms_sec_widget::setCustomSSDarkOnPopupWindow(){
    QString ssDark = R"(
            QWidget {
                background-color: #121212;
                border-radius: 8px; /* border radius */
            }
            QPushButton {
                background-color: rgba(255,255,255,5%); /* background color */
                color: white; /* text color */
                padding: 12px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }

            QPushButton:hover {
                background-color: rgba(255,255,255,10%);
                border: 1px solid rgba(255,255,255, 15%);
            }
            QPushButton:pressed {
                background-color: rgba(255,255,255,18%);
                border: 1px solid rgba(255,255,255, 15%);
            }
            QPushButton:checked {
                background-color: rgba(255,255,255,18%);
                border: 1px solid rgba(255,255,255, 15%);
            }
            QToolButton {
                background-color: transparent; /* background color */
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }

            QToolButton:hover {
                background-color: rgba(255,255,255,5%);
            }
            QToolButton:pressed {
                background-color: rgba(255,255,255,10%);
            }
            QToolButton:checked {
                background-color: rgba(255,255,255,10%);
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
            QTextEdit {
                background-color: rgba(255,255,255,5%);
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QCheckBox {
                background-color: transparent;
                color: white; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
            QCheckBox::indicator {
                background-color: #000000;
                padding: 4px; /* padding */
                border-radius: 4px; /* border radius */
            }
            QCheckBox::indicator::checked {
                background-color: #C2185B;
            }
            QLabel {
                background-color: transparent;
                color: white; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
            QTabWidget::pane {
                background-color: transparent; /* background color */
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QTabBar::tab {
                background-color: transparent; /* background color */
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
                min-width: 100px;
            }
            QTabBar::tab:selected {
                background-color: #C2185B;
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
                min-width: 100px;
            }
            QListWidget {
                background-color: rgba(255,255,255,5%);
            }
            QListWidget::item {
                background-color: transparent;
                color: white; /* text color */
                padding: 4px;
                font-size: 12px;
                font-family: silka;
                padding: 8px 12px;
                border-radius: 4px; /* border radius */
            }
            QListWidget::item:hover {
                background-color: rgba(255,255,255,5%);
                border: 1px solid rgba(255,255,255, 15%);
            }
            QListWidget::item:selected {
                background-color: #C2185B;
            }
            QSpinBox {
                background-color: rgba(255,255,255,5%);
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
            }
            QSpinBox::up-button, QSpinBox::down-button {
                background-color: transparent;
                color: red; /* text color */
                border: 1px solid rgba(255,255,255,5%);
                padding: 2px;
            }
            QSpinBox::up-button:pressed, QSpinBox::down-button:pressed  {
                background-color: #C2185B;
            }
            QSpinBox::up-arrow, QSpinBox::down-arrow {
                color: white; /* text color */
                padding: 2px;
            }
        )";
    this->popupWindow->setStyleSheet(ssDark);
}

void Rms_sec_widget::setCustomSSLightOnPopupWindow(){
    QString ssLight = R"(
            QWidget {
                background-color: #DEE4E7;
                border-radius: 8px; /* border radius */
            }
            QPushButton {
                background-color: rgba(0,0,0,5%); /* background color */
                color: black; /* text color */
                padding: 12px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }

            QPushButton:hover {
                background-color: rgba(0,0,0, 10%);
                border: 1px solid rgba(0,0,0, 15%);
            }
            QPushButton:pressed {
                background-color: rgba(0,0,0, 18%);
                border: 1px solid rgba(0,0,0, 15%);
            }
            QPushButton:checked {
                background-color: rgba(0,0,0, 18%);
                border: 1px solid rgba(0,0,0, 15%);
            }
            QToolButton {
                background-color: transparent; /* background color */
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }

            QToolButton:hover {
                background-color: rgba(0,0,0,5%);
            }
            QToolButton:pressed {
                background-color: rgba(0,0,0,10%);
            }
            QToolButton:checked {
                background-color: rgba(0,0,0,10%);
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
            QTextEdit {
                background-color: rgba(0,0,0,5%);
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QCheckBox {
                background-color: transparent;
                color: black; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
            QCheckBox::indicator {
                background-color: rgba(255,255,255,100%);;
                padding: 4px; /* padding */
                border-radius: 4px; /* border radius */
            }
            QCheckBox::indicator::checked {
                background-color: #C2185B;
            }
            QLabel {
                background-color: transparent;
                color: black; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
            QTabWidget::pane {
                background-color: transparent; /* background color */
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QTabBar::tab {
                background-color: transparent; /* background color */
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
                min-width: 100px;
            }
            QTabBar::tab:selected {
                background-color: #C2185B;
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
                min-width: 100px;
            }
            QListWidget {
                background-color: rgba(0,0,0,5%);
            }
            QListWidget::item {
                background-color: transparent;
                color: black; /* text color */
                padding: 4px;
                font-size: 12px;
                font-family: silka;
                padding: 8px 12px;
                border-radius: 4px; /* border radius */
            }
            QListWidget::item:hover {
                background-color: rgba(0,0,0,5%);
                border: 1px solid rgba(0,0,0, 15%);
            }
            QListWidget::item:selected {
                background-color: #C2185B;
            }
            QSpinBox {
                background-color: rgba(0,0,0,5%);
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
            }
            QSpinBox::up-button, QSpinBox::down-button {
                background-color: transparent;
                color: red; /* text color */
                border: 1px solid rgba(0,0,0,5%);
                padding: 2px;
            }
            QSpinBox::up-button:pressed, QSpinBox::down-button:pressed  {
                background-color: #C2185B;
            }
            QSpinBox::up-arrow, QSpinBox::down-arrow {
                color: black; /* text color */
                padding: 2px;
            }
        )";
    this->popupWindow->setStyleSheet(ssLight);
}
