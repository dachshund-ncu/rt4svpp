#include "heat_map_widget.h"

// -- konstruktor widgetu --
// -- od razu ustala wskaźnik na kontener z danymi --
heat_map_widget::heat_map_widget(spectral_container * dataTable, QCheckBox * isotime)
{
    this->setVisible(false);
    this->dataTable = dataTable;
    this->isotime = isotime;
    setButtonsProperties();
    processTextEdits();
    placeWidgets();
    managePlottables();
    setLabelTexts();
    connectForAxis();
    setDownPolButtons();
    //this->setGeometry(200,200, 1366, 720);
}

void heat_map_widget::setButtonsProperties()
{
    // -- rozmiary --
//    yDownBorder->setMaximumSize(10000,30);
//    yUpBorder->setMaximumSize(10000,30);
//    xDownBorder->setMaximumSize(10000,30);
//    xUpBorder->setMaximumSize(10000,30);
//    Ibut->setMaximumSize(10000,30);
//    Vbut->setMaximumSize(10000,30);
//    LHCbut->setMaximumSize(10000,30);
//    RHCbut->setMaximumSize(10000,30);
//    flag->setMaximumSize(10000,10000);
//    makeLcsButton->setMaximumSize(10000,10000);
//    recreateIButton->setMaximumSize(10000,10000);
//    rotate->setMaximumSize(10000,10000);
//    rotate_minus->setMaximumSize(10000,10000);
//    saveEdition->setMaximumSize(10000,10000);

//    yDownBorder->setMinimumSize(0,0);
//    yUpBorder->setMinimumSize(0,0);
//    xDownBorder->setMinimumSize(0,0);
//    xUpBorder->setMinimumSize(0,0);
//    Ibut->setMinimumSize(0,0);
//    Vbut->setMinimumSize(0,0);
//    LHCbut->setMinimumSize(0,0);
//    RHCbut->setMinimumSize(0,0);
//    flag->setMinimumSize(0,0);
//    makeLcsButton->setMinimumSize(0,0);
//    recreateIButton->setMinimumSize(0,0);
//    rotate->setMinimumSize(0,0);
//    rotate_minus->setMinimumSize(0,0);
//    saveEdition->setMinimumSize(0,0);
    // -------------------------
    // -- teksty --
//    yDownBorder->setText("Down");
//    yUpBorder->setText("Up");
//    xDownBorder->setText("->|");
//    xUpBorder->setText("|<-");
//    Ibut->setText("I");
//    Vbut->setText("V");
//    LHCbut->setText("LHC");
//    RHCbut->setText("RHC");
    flag->setText("Flag");
    makeLcsButton->setText("Make LCS");
    recreateIButton->setText("Recal IV");
    rotate->setText("Rotate+");
    rotate_minus->setText("Rotate-");
    saveEdition->setText("Save");
    // -------------------------
    // -- action icons --
    yDownBorder->setIcon(QIcon(":/images/DOWNicon.svg"));
    yDownBorder->setToolTip("Set actually selected channel's velocity as MINIMUM on heat map");
    yUpBorder->setIcon(QIcon(":/images/UPicon.svg"));
    yUpBorder->setToolTip("Set actually selected channel's velocity as MAXIMUM on heat map");
    xDownBorder->setIcon(QIcon(":/images/LEFTicon.svg"));
    xDownBorder->setToolTip("Set actually selected epoch as MINIMUM on heat map");
    xUpBorder->setIcon(QIcon(":/images/RIGHTicon.svg"));
    xUpBorder->setToolTip("Set actually selected epoch as MAXIMUM on heat map");
    // --
    Ibut->setIcon(QIcon(":/images/IDSicon2.svg"));
    Vbut->setIcon(QIcon(":/images/VDSicon.svg"));
    LHCbut->setIcon(QIcon(":/images/LHCDSicon.svg"));
    RHCbut->setIcon(QIcon(":/images/RHDSicon.svg"));
    Ibut->setToolTip("Show STOKES I");
    Vbut->setToolTip("Show STOKES V");
    LHCbut->setToolTip("Show STOKES LHC");
    RHCbut->setToolTip("Show STOKES RHC");
    // -- checkboxy --
    rotateAllPols->setChecked(true);
    setLogScale->setVisible(false);
    rotateAllPols->setVisible(false);
    // -- button --
    Ibut->setCheckable(true);
    Vbut->setCheckable(true);
    LHCbut->setCheckable(true);
    RHCbut->setCheckable(true);
    Ibut->setChecked(true);
}

void heat_map_widget::processTextEdits()
{
    numberOfRotatedChannelsTexted->setMaximumSize(60,30);
    numberOfRotatedChannelsTexted->setText("1");
}

void heat_map_widget::placeWidgets()
{
    // -- rozmieszczamy przyciski --
//    topDynSpecButtons->addWidget(Ibut);
//    topDynSpecButtons->addWidget(Vbut);
//    topDynSpecButtons->addWidget(LHCbut);
//    topDynSpecButtons->addWidget(RHCbut);
//    // --
//    topDynSpecButtons->addWidget(yDownBorder);
//    topDynSpecButtons->addWidget(yUpBorder);
//    topDynSpecButtons->addWidget(xDownBorder);
//    topDynSpecButtons->addWidget(xUpBorder);
    bottomToolBar->addAction(Ibut);
    bottomToolBar->addAction(Vbut);
    bottomToolBar->addAction(LHCbut);
    bottomToolBar->addAction(RHCbut);
    bottomToolBar->addSeparator();
    bottomToolBar->addAction(yDownBorder);
    bottomToolBar->addAction(yUpBorder);
    bottomToolBar->addAction(xDownBorder);
    bottomToolBar->addAction(xUpBorder);
    bottomToolBar->addSeparator();
    bottomToolBar->addAction(recreateIButton);
    bottomToolBar->addAction(flag);
    bottomToolBar->addSeparator();
    bottomToolBar->addAction(rotate);
    bottomToolBar->addAction(rotate_minus);
    bottomToolBar->addWidget(numberOfRotatedChannelsTexted);
    bottomToolBar->addSeparator();
    bottomToolBar->addAction(saveEdition);
    bottomToolBar->addSeparator();
    bottomToolBar->addAction(makeLcsButton);
    // --
//    bottomDynSpecButtons->addWidget(numberOfRotatedChannelsTexted);
//    bottomDynSpecButtons->addWidget(recreateIButton);
//    bottomDynSpecButtons->addWidget(flag);
//    bottomDynSpecButtons->addWidget(rotate);
//    bottomDynSpecButtons->addWidget(saveEdition);
//    bottomDynSpecButtons->addWidget(rotate_minus);
//    bottomDynSpecButtons->addWidget(makeLcsButton);
//    checkboxesOnDynspec->addWidget(setLogScale);
//    checkboxesOnDynspec->addWidget(rotateAllPols);
//    bottomDynSpecButtons->addItem(checkboxesOnDynspec);
    // --
    //topDynSpecButtons->setSpacing(1);
    bottomDynSpecButtons->setSpacing(1);
    // --
    //onDynSpecButtons->addLayout(bottomDynSpecButtons);
    //onDynSpecButtons->addLayout(topDynSpecButtons);
    //onDynSpecButtons->addWidget(bottomToolBar);
    // -- dodajemy do gridu --
    // -- umierszczamy ploty na gridzie --
    grid->addWidget(heatMapPlot, 1,0,7,6);
    grid->addWidget(spectrumPlot, 0,6,4,4);
    grid->addWidget(lcsPlot, 4,6,4,4);
    grid->addWidget(colorbarWidget, 0, 0, 1, 6);
    // -- przyciski --
    //grid->addLayout(onDynSpecButtons,8,0,1,6);
    grid->addWidget(bottomToolBar,8,0,1,6);
    grid->addWidget(leftLabel, 8,6);
    grid->addWidget(rightLabel, 8,8);
    // -- ustalamy column stretch --
    for(int i = 0; i < grid->columnCount(); i++)
        grid->setColumnStretch(i, 1);
    for(int i = 0; i < grid->rowCount(); i++)
        grid->setRowStretch(i, 1);

}

void heat_map_widget::managePlottables()
{
    // -- dodajemy potrzebne graphy --
    addGraphs();
    // --- colorbar --
    // -- widget --
    colorbarWidget->clearPlottables();
    colorbarWidget->plotLayout()->clear();
    colorbarWidget->plotLayout()->addElement(0,0,colorbar);
    colorbarWidget->setMaximumSize(9999999,70);
    colorbarWidget->resize(1,1);
    // -- bar --
    colorbar->setType(QCPAxis::atTop);
    colorbar->setDataRange(heatMap->dataRange());
    colorbar->setMinimumMargins(QMargins(6, 0, 6, 0));
    // ---------------
    QCPMarginGroup * grupa_marginesowa = new QCPMarginGroup(heatMapPlot);
    heatMapPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, grupa_marginesowa);
    colorbar->setMarginGroup(QCP::msLeft|QCP::msRight, grupa_marginesowa);
    colorbarWidget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    heatMap->setColorScale(colorbar);
    // ---------------
    heatMapPlot->addLayer("linex");
    heatMapPlot->addLayer("liney");
    heatMapPlot->addLayer("pixmap");
    heatMapPlot->addLayer("prectangle");
    heatMapPlot->addLayer("flags");
    // --
    heatMap->setLayer("pixmap");
    x_axis_line->setLayer("linex");
    y_axis_line->setLayer("liney");
    rectangle->setLayer("prectangle");
    heatMapPlot->moveLayer(x_axis_line->layer(), heatMap->layer(), QCustomPlot::limAbove );
    heatMapPlot->moveLayer(y_axis_line->layer(), heatMap->layer(), QCustomPlot::limAbove );
    heatMapPlot->moveLayer(rectangle ->layer(), heatMap->layer(), QCustomPlot::limAbove );
    // ----------------
    // nudne rzeczy w plotach
    heatMapPlot->axisRect()->setupFullAxesBox(false);
    heatMapPlot->xAxis->setLabel("Observation number");
    heatMapPlot->yAxis->setLabel("Vel");
    heatMap->setInterpolate(false);
    heatMap->setTightBoundary(true);
    heatMapPlot->setCursor(QCursor(Qt::CrossCursor));
    // ----------------

    // dane
    QPen pendane;
    pendane.setColor(QColor(0,0,255));

    QPen penkropka;
    penkropka.setColor(QColor(182,26,26));

    QPen penerrory;
    penerrory.setColor(QColor(105,105,105));

    // teraz widmo singlowe
    // -- dodajemy podpis --
    spectrumPlot->xAxis->setLabel("Velocity (km/s)");
    // -- pokazujemy ticki po prawej stronie i na górnej osi --
    spectrumPlot->xAxis2->setVisible(true);
    spectrumPlot->yAxis2->setVisible(true);
    spectrumPlot->xAxis2->setTickLabels(false);
    spectrumPlot->yAxis2->setTickLabels(false);
    // -- setujemy interakcje --
    spectrumPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // -- kolory --
    spectrumPlot->graph(0)->setPen(pendane);
    //spectrumPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    //spectrumPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    spectrumPlot->graph(1)->setPen(penkropka);
    spectrumPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    spectrumPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));
    lcsVline->setPen(penkropka);
    // ------------------

    // teraz krzywa blasku
    // -- dodajemy podpis --
    lcsPlot->xAxis->setLabel("MJD");
    // -- pokazujemy ticki po prawej stronie i na górnej osi --
    lcsPlot->xAxis2->setVisible(true);
    lcsPlot->yAxis2->setVisible(true);
    lcsPlot->xAxis2->setTickLabels(false);
    lcsPlot->yAxis2->setTickLabels(false);
    // -- setujemy interakcje --
    lcsPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // -- kolory --
    lcsPlot->graph(0)->setPen(pendane);
    lcsPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    lcsPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    lcsPlot->graph(1)->setPen(penkropka);
    lcsPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    lcsPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));
    errorBars->setPen(penerrory);
    spectrumVline->setPen(penkropka);

    // -- crosshair --
    QPen pen;
    pen.setColor(QColor(255,255,255));
    x_axis_line->setPen(pen);
    y_axis_line->setPen(pen);
    rectangle->setPen(pen);
    // ---------------

}

void heat_map_widget::setLabelTexts()
{
    QFont f( "Arial", 11, QFont::Bold);
    leftLabel->setFont(f);
    rightLabel->setFont(f);
    leftLabel->setText("MJD = \nChannel = \nVel = ");
    rightLabel->setText("Date: \nValue: \nNumber: ");
}

void heat_map_widget::firstPlotOnDynamicSpectrum()
{
    // -- pierwsze zabezpieczenie --
    if (!dataTable->loadedData)
        return;
    // -----------------------------

    resetHeatMap();
    gradient.loadPreset(QCPColorGradient::gpJet);
    heatMap->setGradient(gradient);
    heatMap->setDataScaleType(QCPAxis::stLinear);
    heatMap->setTightBoundary(false);
    firstPlotDone = true;
    updateHeatMap();
}

void heat_map_widget::connectForAxis()
{
    // single
    connect(spectrumPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), spectrumPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(spectrumPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), spectrumPlot->yAxis2, SLOT(setRange(QCPRange)));
    // lcs
    connect(lcsPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), lcsPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(lcsPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), lcsPlot->yAxis2, SLOT(setRange(QCPRange)));
    // colorbar
    connect(colorbar, SIGNAL(dataRangeChanged(QCPRange)), heatMap, SLOT(setDataRange(QCPRange)));
    connect(colorbar, SIGNAL(dataRangeChanged(QCPRange)), heatMapPlot, SLOT(replot()));

    // klikałke
    QObject::connect(heatMapPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(pressMap(QMouseEvent*)) );

    // -- zasięgi --
    // skróty
    yDownBorder_shrt->setKey(QKeySequence("d"));
    yUpBorder_shrt->setKey(QKeySequence("g"));
    xDownBorder_shrt->setKey(QKeySequence("l"));
    xUpBorder_shrt->setKey(QKeySequence("p"));
    heatMapReset->setKey(QKeySequence("b"));
    nextEpochKey->setKey(QKeySequence(Qt::Key_Right));
    prevEpochKey->setKey(QKeySequence(Qt::Key_Left));
    nextChanKey->setKey(QKeySequence(Qt::Key_Up));
    prevChanKey->setKey(QKeySequence(Qt::Key_Down));
    // -
    QObject::connect(yDownBorder, SIGNAL(triggered()), this, SLOT(setMinVelOnHeatMap()));
    QObject::connect(yUpBorder, SIGNAL(triggered()), this, SLOT(setMaxVelOnHeatMap()));
    QObject::connect(xDownBorder, SIGNAL(triggered()), this, SLOT(setMinEpochOnHeatMap()));
    QObject::connect(xUpBorder, SIGNAL(triggered()), this, SLOT(setMaxEpochOnHeatMap()));
    //-
    QObject::connect(yDownBorder_shrt, SIGNAL(activated()), this, SLOT(setMinVelOnHeatMap()));
    QObject::connect(yUpBorder_shrt, SIGNAL(activated()), this, SLOT(setMaxVelOnHeatMap()));
    QObject::connect(xDownBorder_shrt, SIGNAL(activated()), this, SLOT(setMinEpochOnHeatMap()));
    QObject::connect(xUpBorder_shrt, SIGNAL(activated()), this, SLOT(setMaxEpochOnHeatMap()));
    QObject::connect(heatMapReset, SIGNAL(activated()), this, SLOT(resetHeatMap()));
    // - polaryzacje -

    // - rotacja -
    QObject::connect(rotate, SIGNAL(triggered()), this, SLOT(rotatePlus()));
    QObject::connect(rotate_minus, SIGNAL(triggered()), this, SLOT(rotateMinus()));
    QObject::connect(saveEdition, SIGNAL(triggered()), this, SLOT(saveEditedSpectra()));
    QObject::connect(recreateIButton, SIGNAL(triggered()), this, SLOT(recal()));
    // - krzywa blasku -
    QObject::connect(makeLcsButton, SIGNAL(triggered()), this, SLOT(makeLCS()));
    // - widmo dynamiczne -

    // - flagowanie -
    QObject::connect(flag, SIGNAL(triggered()), this, SLOT(flagActualEpoch()));
    // - klikanie -
    QObject::connect(nextEpochKey, SIGNAL(activated()), this, SLOT(nextEpoch()));
    QObject::connect(prevEpochKey, SIGNAL(activated()), this, SLOT(prevEpoch()));
    QObject::connect(nextChanKey, SIGNAL(activated()), this, SLOT(nextChan()));
    QObject::connect(prevChanKey, SIGNAL(activated()), this, SLOT(prevChan()));
}

void heat_map_widget::tmp_plot()
{
    firstPlotOnDynamicSpectrum();
    heatMapPlot->replot();
    colorbarWidget->replot();
}

void heat_map_widget::pressMap(QMouseEvent *event)
{
    // przechwytujemy pozycję kliknięcia
    double x,y;
    x = heatMapPlot->xAxis->pixelToCoord(event->pos().x());
    y = heatMapPlot->yAxis->pixelToCoord(event->pos().y());
    // określamy jaki to indeks
    unsigned long int xind = searchForClickedX(x);
    unsigned long int yind = searchForClickedY(y);
    // wywołujemy metodę
    setMapPressed(xind, yind);
    setDownPolButtons();
}

void heat_map_widget::setMapPressed(unsigned long x, unsigned long y)
{
    // bierzemy odpowiednią polaryzację
    std::vector < std::vector < double > > * poltab = getPoltab();
    std::vector < double > * errtab = getErrtab();
    // ustawiamy crosshair
    setCrosshair(x,y);
    // ustawiamy widmo
    plotSingleSpectrum(x,y);
    // ustawiamy LCS
    plotLCS(x,y, *errtab);
    // ustalamy labele
    setLabelClicked(x,y);
    // updatujemy graphy
    heatMapPlot->layer(QString::fromStdString("linex"))->replot();
    heatMapPlot->layer(QString::fromStdString("liney"))->replot();
    heatMapPlot->layer(QString::fromStdString("prectangle"))->replot();
    spectrumPlot->replot();
    lcsPlot->replot();
    // setujemy do zmiennych globalnych co jest kliknięte
    xIndex = x;
    yIndex = y;
}

// metody pomocnicze do klikałke
unsigned long int  heat_map_widget::searchForClickedX(double x)
{
    if (x < 0.0)
        x = 0.0;
    unsigned long int tmpx = (unsigned long int) round(x);
    if( tmpx < minObsNumber)
        tmpx = minObsNumber;
    else if (tmpx > maxObsNumber)
        tmpx = maxObsNumber;

    return tmpx;
}

unsigned long int  heat_map_widget::searchForClickedY(double y)
{
    unsigned long int yind = 0;
    // zabezpieczenie przed błędami
    if(y < dataTable->velocityTable[xIndex][minRangeVelIndex])
    {
        return (unsigned long int) minRangeVelIndex;
    }
    else if (y > dataTable->velocityTable[xIndex][maxRangeVelIndex])
    {
        return maxRangeVelIndex;
    }

    // następnie musimy przeszukać tablicę Vel, by znaleźć indeks, odpowiadający klikniętemu Y:
    for(int i=0; i < dataTable->velocityTable[xIndex].size(); i++)
    {
        if (dataTable->velocityTable[xIndex][i] > y+0.5*(dataTable->velocityTable[xIndex][1]-dataTable->velocityTable[xIndex][0]))
        {
            yind = i-1;
            break;
        }
    }
    return yind;
}

void heat_map_widget::addGraphs()
{
    // --- single spectrum ---
    spectrumPlot->addGraph(); // linie widma
    spectrumPlot->addGraph(); // kropka
    // --- LCS ---
    lcsPlot->addGraph(); // krzywa blasku
    lcsPlot->addGraph(); // kropka
}

void heat_map_widget::setCrosshair(unsigned long x, unsigned long y)
{
    // pionowa
    x_axis_line->start->setCoords(x, -QCPRange::maxRange);
    x_axis_line->end->setCoords(x, QCPRange::maxRange);
    // pozioma
    y_axis_line->start->setCoords(-QCPRange::maxRange, dataTable->velocityTable[x][y]);
    y_axis_line->end->setCoords(QCPRange::maxRange, dataTable->velocityTable[x][y]);
    // kwadrat
    double h = abs(dataTable->velocityTable[x][0] - dataTable->velocityTable[x][1]); // odstęp między kanałami
    rectangle->topLeft->setCoords(double(x) - 0.5, dataTable->velocityTable[x][y] + 0.5*h);
    rectangle->bottomRight->setCoords(double(x) + 0.5, dataTable->velocityTable[x][y] - 0.5*h);
}

void heat_map_widget::plotSingleSpectrum(unsigned long x, unsigned long y)
{
    // skrowidz: x - epoka y - kanał
    // tutaj idziemy po kanałach, stała prędkość
    // -- będziemy na piechotkę przypisywać wartości do kontenerów --
    // widmo
    QVector <double> vels(rozmiarY), fluxes(rozmiarY);
    for(unsigned long int i = 0; i < rozmiarY; i++)
    {
        vels[i] = dataTable->velocityTable[x][minRangeVelIndex + i];
        fluxes[i] = heatMap->data()->cell(x - minObsNumber,i);// poltab[x][minRangeVelIndex + i];
    }
    QVector < double > flux(1) ,vel(1);
    flux[0] = heatMap->data()->cell(x - minObsNumber,y-minRangeVelIndex); //poltab[x][y];
    vel[0] = dataTable->velocityTable[x][y];
    // setujemy
    spectrumPlot->graph(0)->setData(vels, fluxes); // całe dane
    spectrumPlot->graph(1)->setData(vel, flux); // kropka
    spectrumVline->start->setCoords(dataTable->velocityTable[x][y], -QCPRange::maxRange);
    spectrumVline->end->setCoords(dataTable->velocityTable[x][y], QCPRange::maxRange);
    rescaleGraph(spectrumPlot);
}

void heat_map_widget::plotLCS(unsigned long x, unsigned long y,std::vector<double> &errtab)
{
    // skrowidz: x - epoka y - kanał
    // tutaj idziemy po epokach, kanał stały
    // -- będziemy na piechotkę przypisywać wartości do kontenerów --
    QVector <double> epochs(rozmiarX), fluxes(rozmiarX), errors(rozmiarX);
    for(unsigned long int i = 0; i < rozmiarX; i++)
    {
        epochs[i] = dataTable->mjdTable[i + minObsNumber];
        fluxes[i] = heatMap->data()->cell(i, y-minRangeVelIndex);//poltab[i + minObsNumber][y];
        errors[i] = errtab[i + minObsNumber];
    }
    QVector < double > flux(1) ,epoch(1);
    flux[0] = heatMap->data()->cell(x - minObsNumber,y-minRangeVelIndex);//poltab[x][y];
    epoch[0] = dataTable->mjdTable[x];
    // setujemy
    lcsPlot->graph(0)->setData(epochs, fluxes); // całe dane
    lcsPlot->graph(1)->setData(epoch, flux); // kropka
    errorBars->setDataPlottable(lcsPlot->graph(0));// errory
    errorBars->setData(errors); // errory
    errorBars->setVisible(!normalizationB);
    lcsVline->start->setCoords(dataTable->mjdTable[x], -QCPRange::maxRange);
    lcsVline->end->setCoords(dataTable->mjdTable[x], QCPRange::maxRange);
    rescaleGraph(lcsPlot);
}

void heat_map_widget::setLabelClicked(unsigned long x, unsigned long y)
{
    // -- setujemy tekst do displayowania informacji --
    // --------------
    // Lewy
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(std::to_string(int(dataTable->mjdTable[x])));
    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(std::to_string((int) dataTable->channelTable[x][y]));
    text_mjdlabel.append(string("\nVel: "));
    // Tworzymy ostringstream
    std::ostringstream streamObjvel;
    // ustalamy notację o stałej liczbie po przecinku
    streamObjvel << std::fixed;
    streamObjvel << std::setprecision(3);
    // zapisujemy double do ostringstreama
    streamObjvel << dataTable->velocityTable[x][y];
    // wyłuskujemy to jako stringi
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);

    // --------------
    // ---------------
    // Prawy
    string cocochanel_txt = "";
    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(std::to_string(int(dataTable->datetimeTable[x][0])));
    cocochanel_txt.append(string(" "));
    if (int(dataTable->datetimeTable[x][1]) < 10)
        cocochanel_txt.append("0" + std::to_string(int(dataTable->datetimeTable[x][1])));
    else
        cocochanel_txt.append(std::to_string(int(dataTable->datetimeTable[x][1])));
    cocochanel_txt.append(string(" "));
    if (int(dataTable->datetimeTable[x][2]) < 10)
        cocochanel_txt.append("0" + std::to_string(int(dataTable->datetimeTable[x][2])));
    else
        cocochanel_txt.append(std::to_string(int(dataTable->datetimeTable[x][2])));
    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    //value
    std::ostringstream streamObj3;
    streamObj3 << std::fixed;
    streamObj3 << std::setprecision(3);
    if (heatMap->data()->cell(x - minObsNumber,y-minRangeVelIndex) > 1e6 )
        streamObj3 << std::scientific;
    streamObj3 << heatMap->data()->cell(x - minObsNumber,y-minRangeVelIndex);//poltab[x][y];
    cocochanel_txt.append(streamObj3.str());
    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(std::to_string(x+1));

    leftLabel->setText(QString::fromStdString(text_mjdlabel));
    rightLabel->setText(QString::fromStdString(cocochanel_txt));
}

void heat_map_widget::rescaleGraph(QCustomPlot * plot)
{
    plot->rescaleAxes(true); // <-- TRUE is for only visible plottables
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

void heat_map_widget::updateHeatMap()
{
    // sekcja ustawiania informacji na kolor mapie
    heatMap->data()->clear();
    // rozmiar
    heatMap->data()->setSize(rozmiarX, rozmiarY);
    // zakres danych - od najmniejsej do największej -0.5 * krok prędkości
    double minVelocity = dataTable->velocityTable[minObsNumber][minRangeVelIndex];
    double maxVelocity = dataTable->velocityTable[minObsNumber][maxRangeVelIndex];// - abs(dataTable->velocityTable[minObsNumber][1]-dataTable->velocityTable[minObsNumber][0]);
    // rozmiar
    if (rozmiarX != 1)
        heatMap->data()->setRange(QCPRange(minObsNumber, maxObsNumber), QCPRange(minVelocity, maxVelocity ) );
    else
        heatMap->data()->setRange(QCPRange(-0.5, 0.5), QCPRange(minVelocity, maxVelocity ) );
    // bierzemy tablicę z konkretną polaryzacją
    std::vector < std::vector < double > > *poltab = getPoltab();
    std::vector < double > *errtab = getErrtab();
    std::vector < double > *normtab = getNormtab();
    // zapełniamy heat mapę
    for (unsigned long int indexWX = 0; indexWX < rozmiarX; indexWX++)
    {
        double normCoeff = (*normtab)[minObsNumber + indexWX];
        for (unsigned long int indexWY = 0; indexWY < rozmiarY; indexWY++)
        {
            if(!normalizationB)
                heatMap->data()->setCell(indexWX, indexWY, (*poltab)[minObsNumber+indexWX][minRangeVelIndex + indexWY]);
            else
                heatMap->data()->setCell(indexWX, indexWY, (*poltab)[minObsNumber+indexWX][minRangeVelIndex + indexWY] / normCoeff);
        }
    }
    // reskalujemy widmo dynamiczne
    scaleHeatMap();
    // robimy również update widm
    plotSingleSpectrum(xIndex, yIndex);
    plotLCS(xIndex, yIndex, *errtab);
    setLabelClicked(xIndex, yIndex);
    // robimy na koniec replot
    heatMapPlot->replot();
    colorbarWidget->replot();
    spectrumPlot->replot();
    lcsPlot->replot();
    // sprawiamy, że wybrana polaryzacja nie znika
    setDownPolButtons();
}

std::vector < std::vector < double > > * heat_map_widget::getPoltab()
{
    if(polI)
        return &dataTable->spectraTableI;
    else if(polV)
        return &dataTable->spectraTableV;
    else if (polLHC)
        return &dataTable->spectraTableLHC;
    else if (polRHC)
        return  &dataTable->spectraTableRHC;
    else
        return &dataTable->spectraTableI;
}

std::vector < double > * heat_map_widget::getErrtab()
{
    if(polI)
        return &dataTable->spectraTableIERR;
    else if(polV)
        return &dataTable->spectraTableVERR;
    else if (polLHC)
        return &dataTable->spectraTableLHCERR;
    else if (polRHC)
        return  &dataTable->spectraTableRHCERR;
    else
        return &dataTable->spectraTableIERR;
}

std::vector < double > * heat_map_widget::getNormtab()
{
    if(polI)
        return &dataTable->normalizationCoeffsI;
    else if(polV)
        return &dataTable->normalizationCoeffsV;
    else if (polLHC)
        return &dataTable->normalizationCoeffsLHC;
    else if (polRHC)
        return  &dataTable->normalizationCoeffsRHC;
    else
        return &dataTable->normalizationCoeffsI;
}

void heat_map_widget::setMinVelOnHeatMap()
{
    minRangeVelIndex = yIndex;
    rozmiarY = maxRangeVelIndex - minRangeVelIndex + 1;
    updateHeatMap();
}

void heat_map_widget::setMaxVelOnHeatMap()
{
    maxRangeVelIndex = yIndex;
    rozmiarY = maxRangeVelIndex - minRangeVelIndex + 1;
    updateHeatMap();
}

void heat_map_widget::setMinEpochOnHeatMap()
{
    minObsNumber = xIndex;
    rozmiarX = maxObsNumber - minObsNumber + 1;
    updateHeatMap();
}

void heat_map_widget::setMaxEpochOnHeatMap()
{
    maxObsNumber = xIndex;
    rozmiarX = maxObsNumber - minObsNumber + 1;
    updateHeatMap();
}

void heat_map_widget::resetHeatMap()
{
    minRangeVelIndex = 0;
    maxRangeVelIndex = dataTable->velocityTable[0].size()-1;
    minObsNumber = 0;
    maxObsNumber = dataTable->mjdTable.size()-1;
    rozmiarX = dataTable->mjdTable.size();
    rozmiarY = dataTable->velocityTable[0].size();
    updateHeatMap();
}

void heat_map_widget::choosePolI()
{
    polI = true;
    polV = false;
    polLHC = false;
    polRHC = false;
    setDownPolButtons();
    updateHeatMap();
}
void heat_map_widget::choosePolV()
{
    polI = false;
    polV = true;
    polLHC = false;
    polRHC = false;
    setDownPolButtons();
    updateHeatMap();
}
void heat_map_widget::choosePolLHC()
{
    polI = false;
    polV = false;
    polLHC = true;
    polRHC = false;
    setDownPolButtons();
    updateHeatMap();
}
void heat_map_widget::choosePolRHC()
{
    polI = false;
    polV = false;
    polLHC = false;
    polRHC = true;
    setDownPolButtons();
    updateHeatMap();
}
void heat_map_widget::setDownPolButtons()
{
    Ibut->setChecked(polI);
    Vbut->setChecked(polV);
    LHCbut->setChecked(polLHC);
    RHCbut->setChecked(polRHC);
}

void heat_map_widget::rotateSpectrum(bool direction)
{
    // -- czytamy z texteda o ile mamy rotować --
    int noOfRotatedChannels = readNumberOfRotatedChannels();
    if (noOfRotatedChannels < 0)
        return;
    // -- sprawdzamy, która to epoka --
    int rotatedEpoch = xIndex;
    // -- wywołujemy rotację --
    if(rotateAllPols->isChecked())
        dataTable->rotate(rotatedEpoch+1, noOfRotatedChannels, direction, 1,1,1,1);
    else
        dataTable->rotate(rotatedEpoch+1, noOfRotatedChannels, direction, polI, polV, polLHC, polRHC);
    // updatujemy
    updateHeatMap();
}

int heat_map_widget::readNumberOfRotatedChannels()
{
    // Qstring, do którego zgrywamy tekst z text edit
    QString numberInString = numberOfRotatedChannelsTexted->toPlainText();
    // -- sprawdzamy, czy text edit jest wypełniony --
    if (numberInString == "")
    {
        // jeśli nie, nic nie robimy
        return -1;
    }

    // -- konwertujemy wartość z texedit na int--
    try
    {
        int number_of_rotated_channels = std::stoi(numberInString.toStdString());
        return number_of_rotated_channels;
    }
    catch(...)
    {
        return -1;
    }
}
void heat_map_widget::rotatePlus()
{
    rotateSpectrum(true);
}
void heat_map_widget::rotateMinus()
{
    rotateSpectrum(false);
}

void heat_map_widget::saveEditedSpectra()
{
    // -- warunek podstawowy - sprawdza, czy została wykonana jakaś edycja na widmie dynamicznym (w domyśle rotacja albo przeliczenie I/V ) --
    if (!dataTable->madeRotation)
    {
        QMessageBox::information(this, tr("Error!"), tr("There are no edited spectras, so nothing will be saved"));
        return;
    }
    // -- okno do upewniania sie, ze na pewno chcesz --
    QMessageBox::StandardButton upewka;
    upewka = QMessageBox::question(this, "Are you sure?", QString::fromStdString("Do you realy want to save edited spectras (non - rotated versions will be stored at *noedt.DAT)?"), QMessageBox::Yes| QMessageBox::No);
    if (upewka == QMessageBox::No)
    {
        // -- jeśli klikniesz nie, nie pójdzie dalej --
        return;
    }
    // -- konstruujemy wiadomość --
    string message = "Saved edited spectra for: ";
    for (auto &i : dataTable->listOfModified)
    {
        message += " " + dataTable->fileNamesTab[i] + "\n";
    }
    // -- faktycznie zapisujemy --
    dataTable->saveModifiedEpochs();
    // -- wyświetlamy wiadomość --
    QMessageBox::information(this, tr("Message to you"), QString::fromStdString(message));
}

void heat_map_widget::recal()
{
    dataTable->recalculateIfromPols();
    updateHeatMap();
}


void heat_map_widget::makeLCS()
{
    dataTable->averageOverVelocity4Pols(yIndex+1, yIndex+1, isotime->isChecked());
    string message = "";
    message = "Created lc over channel " + std::to_string(yIndex+1) + "\n" + "Saved to " + dataTable->getAverOverVelFileName(yIndex+1, yIndex+1);
    QMessageBox::information(this, tr("Message to you"), QString::fromStdString(message));
}

void heat_map_widget::setLogScale_slot()
{
    if(setLogScale->isChecked())
    {
        // bierzemy średni RMS
        double dno = average(*getErrtab());
        // ustalamy color mapę
        heatMap->data()->recalculateDataBounds();
        QCPRange zasieg(dno, heatMap->data()->dataBounds().upper);
        colorbar->setDataRange(zasieg);
        // zmieniamy scale type
        heatMap->setDataScaleType(QCPAxis::stLogarithmic);
        colorbar->setDataScaleType(QCPAxis::stLogarithmic);
        colorbar->axis()->setTicker(QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog));
        colorbarWidget->replot();
        heatMapPlot->replot();
        setDownPolButtons();
    }
    else
    {
        // -- zmieniamy na skale liniowa --
        heatMap->setDataScaleType(QCPAxis::stLinear);
        heatMap->setDataScaleType(QCPAxis::stLinear);
        // -- skalujemy od 0 do max --
        heatMap->rescaleDataRange();
        // -- replotujemy --
        heatMapPlot->replot();
        setDownPolButtons();
        colorbar->setDataRange(heatMap->dataRange());
        //colorbar->axis()->rescale();
        colorbar->axis()->setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker));
        colorbarWidget->replot();
    }
}

double heat_map_widget::average(std::vector<double> table)
{
    double suma = 0.0;
    for(auto &i : table)
        suma += i;
    return suma / table.size();
}

void heat_map_widget::scaleHeatMap()
{
    heatMap->rescaleKeyAxis();
    heatMap->rescaleValueAxis();
    if(setLogScale->isChecked())
    {
        double dno = average(*getErrtab());
        heatMap->data()->recalculateDataBounds();
        QCPRange zasieg(dno, heatMap->data()->dataBounds().upper);
        colorbar->setDataRange(zasieg);
    }
    else
    {
        heatMap->rescaleDataRange();
        colorbar->setDataRange(heatMap->dataRange());
    }
}

void heat_map_widget::colorGraphs(QPen dataPen, QPen errorPen, QPen dotPen)
{
    spectrumPlot->graph(0)->setPen(dataPen);
    spectrumPlot->graph(1)->setPen(dotPen);
    lcsPlot->graph(0)->setPen(dataPen);
    lcsPlot->graph(1)->setPen(dotPen);
    errorBars->setPen(errorPen);
}

void heat_map_widget::colorSpines(QCustomPlot *plot, QPen pendulum)
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

void heat_map_widget::colorCanvas(QPen background, QPen spines)
{
    // -- tła --
    spectrumPlot->setBackground(background.color());
    spectrumPlot->axisRect()->setBackground(background.color());
    lcsPlot->setBackground(background.color());
    lcsPlot->axisRect()->setBackground(background.color());
    heatMapPlot->setBackground(background.color());
    heatMapPlot->axisRect()->setBackground(background.color());
    colorbarWidget->setBackground(background.color());
    // -- spines --
    colorSpines(spectrumPlot, spines);
    colorSpines(lcsPlot, spines);
    // szczególne przypadki
    // - heat map --
    heatMapPlot->xAxis->setTickLabelColor(spines.color());
    heatMapPlot->xAxis2->setTickLabelColor(spines.color());
    heatMapPlot->yAxis->setTickLabelColor(spines.color());
    heatMapPlot->yAxis2->setTickLabelColor(spines.color());
    // label
    heatMapPlot->xAxis->setLabelColor(spines.color());
    heatMapPlot->xAxis2->setLabelColor(spines.color());
    heatMapPlot->yAxis->setLabelColor(spines.color());
    heatMapPlot->yAxis2->setLabelColor(spines.color());
    // - colorbar -
    // ticklabele
    colorbar->axis()->setTickPen(spines);
    colorbar->axis()->setSubTickPen(spines);
    colorbar->axis()->setTickLabelColor(spines.color());
}

void heat_map_widget::setDarkMode()
{
    // -- odpowiednie długopisy --
    QPen dataPen(QColor(135,206,250));
    dataPen.setWidth(2);
    QPen errorPen(QColor(128,128,128));
    QPen dotPen(Qt::magenta);
    // -- kolorujemy wykresy --
    colorGraphs(dataPen, errorPen, dotPen);
    // ------------------------
    QPen spinesPen(Qt::white);
    QPen background(Qt::black);
    colorCanvas(background, spinesPen);
}

void heat_map_widget::setLightMode()
{
    // -- odpowiednie długopisy --
    QPen dataPen(QColor(0,0,255)); // graph
    dataPen.setWidth(2);
    QPen errorPen(QColor(105,105,105)); // errorbary
    QPen dotPen(QColor(182,26,26));
    // -- kolorujemy wykresy --
    colorGraphs(dataPen, errorPen, dotPen);
    // ------------------------
    QPen spinesPen(Qt::black);
    QPen background(Qt::white);
    colorCanvas(background, spinesPen);
}

void heat_map_widget::darthMode(bool enabled)
{
    if(enabled)
        setDarkMode();
    else
        setLightMode();
    heatMapPlot->replot();
    colorbarWidget->replot();
    spectrumPlot->replot();
    lcsPlot->replot();
}

void heat_map_widget::flagActualEpoch()
{
    dataTable->flag(xIndex + 1);
//    std::string message = "";
//    message += "File " + dataTable->fileNamesTab[xIndex] + " is flagged. RELOAD the data to see changes.";
//    QMessageBox::information(this, tr("Message to you"), QString::fromStdString(message));
}

void heat_map_widget::nextEpoch()
{
    if(xIndex+1 < dataTable->spectraTableI.size())
        xIndex++;
    else
        xIndex = 0;
    setMapPressed(xIndex, yIndex);
}

void heat_map_widget::prevEpoch()
{
    if(xIndex == 0)
        xIndex = dataTable->spectraTableI.size()-1;
    else
        xIndex--;
    setMapPressed(xIndex, yIndex);
}

void heat_map_widget::nextChan()
{
    if(yIndex+1 < dataTable->spectraTableI[xIndex].size())
        yIndex++;
    else
        yIndex = 0;
    setMapPressed(xIndex, yIndex);
}

void heat_map_widget::prevChan()
{
    if(yIndex == 0)
        yIndex = dataTable->spectraTableI[xIndex].size()-1;
    else
        yIndex--;
    setMapPressed(xIndex, yIndex);
}
