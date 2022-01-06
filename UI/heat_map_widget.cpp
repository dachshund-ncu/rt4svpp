#include "heat_map_widget.h"

// -- konstruktor widgetu --
// -- od razu ustala wskaźnik na kontener z danymi --
heat_map_widget::heat_map_widget(spectral_container * dataTable)
{
    this->dataTable = dataTable;
    setButtonsProperties();
    processTextEdits();
    placeWidgets();
    managePlottables();
    setLabelTexts();
    connectForAxis();
    this->setGeometry(200,200, 1366, 720);
    this->setVisible(true);
}

void heat_map_widget::setButtonsProperties()
{
    // -- rozmiary --
    yDownBorder->setMaximumSize(10000,30);
    yUpBorder->setMaximumSize(10000,30);
    xDownBorder->setMaximumSize(10000,30);
    xUpBorder->setMaximumSize(10000,30);
    Ibut->setMaximumSize(10000,30);
    Vbut->setMaximumSize(10000,30);
    LHCbut->setMaximumSize(10000,30);
    RHCbut->setMaximumSize(10000,30);
    flag->setMaximumSize(10000,10000);
    makeLcsButton->setMaximumSize(10000,10000);
    recreateIButton->setMaximumSize(10000,10000);
    rotate->setMaximumSize(10000,10000);
    rotate_minus->setMaximumSize(10000,10000);
    saveEdition->setMaximumSize(10000,10000);

    yDownBorder->setMinimumSize(0,0);
    yUpBorder->setMinimumSize(0,0);
    xDownBorder->setMinimumSize(0,0);
    xUpBorder->setMinimumSize(0,0);
    Ibut->setMinimumSize(0,0);
    Vbut->setMinimumSize(0,0);
    LHCbut->setMinimumSize(0,0);
    RHCbut->setMinimumSize(0,0);
    flag->setMinimumSize(0,0);
    makeLcsButton->setMinimumSize(0,0);
    recreateIButton->setMinimumSize(0,0);
    rotate->setMinimumSize(0,0);
    rotate_minus->setMinimumSize(0,0);
    saveEdition->setMinimumSize(0,0);
    // -------------------------
    // -- teksty --
    yDownBorder->setText("Down");
    yUpBorder->setText("Up");
    xDownBorder->setText("|<-");
    xUpBorder->setText("->|");
    Ibut->setText("I");
    Vbut->setText("V");
    LHCbut->setText("LHC");
    RHCbut->setText("RHC");
    flag->setText("Flag");
    makeLcsButton->setText("Make LCS");
    recreateIButton->setText("Recal IV");
    rotate->setText("Rotate+");
    rotate_minus->setText("Rotate-");
    saveEdition->setText("Save");
    // -------------------------
}

void heat_map_widget::processTextEdits()
{
    numberOfRotatedChannelsTexted->setMaximumSize(60,30);
}

void heat_map_widget::placeWidgets()
{
    // -- rozmieszczamy przyciski --
    topDynSpecButtons->addWidget(Ibut);
    topDynSpecButtons->addWidget(Vbut);
    topDynSpecButtons->addWidget(LHCbut);
    topDynSpecButtons->addWidget(RHCbut);
    // --
    topDynSpecButtons->addWidget(yDownBorder);
    topDynSpecButtons->addWidget(yUpBorder);
    topDynSpecButtons->addWidget(xDownBorder);
    topDynSpecButtons->addWidget(xUpBorder);
    // --
    bottomDynSpecButtons->addWidget(numberOfRotatedChannelsTexted);
    bottomDynSpecButtons->addWidget(recreateIButton);
    bottomDynSpecButtons->addWidget(flag);
    bottomDynSpecButtons->addWidget(rotate);
    bottomDynSpecButtons->addWidget(saveEdition);
    bottomDynSpecButtons->addWidget(rotate_minus);
    bottomDynSpecButtons->addWidget(makeLcsButton);
    checkboxesOnDynspec->addWidget(setLogScale);
    checkboxesOnDynspec->addWidget(rotateAllPols);
    bottomDynSpecButtons->addItem(checkboxesOnDynspec);
    // --
    topDynSpecButtons->setSpacing(1);
    bottomDynSpecButtons->setSpacing(1);
    // --
    onDynSpecButtons->addLayout(bottomDynSpecButtons);
    onDynSpecButtons->addLayout(topDynSpecButtons);
    // -- dodajemy do gridu --
    // -- umierszczamy ploty na gridzie --
    grid->addWidget(heatMapPlot, 1,0,7,6);
    grid->addWidget(spectrumPlot, 0,6,4,4);
    grid->addWidget(lcsPlot, 4,6,4,4);
    grid->addWidget(colorbarWidget, 0, 0, 1, 6);
    // -- przyciski --
    grid->addLayout(onDynSpecButtons,8,0,1,6);
    grid->addWidget(leftLabel, 8,6);
    grid->addWidget(rightLabel, 8,8);
    // -- ustalamy column stretch --
    grid->setColumnStretch(0,1);
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,1);
    grid->setColumnStretch(3,1);
    grid->setColumnStretch(4,1);
    grid->setColumnStretch(5,1);
    grid->setColumnStretch(6,1);
    grid->setColumnStretch(7,1);
    grid->setColumnStretch(8,1);
    grid->setColumnStretch(9,1);
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
    pendane.setColor(QColor(135,206,250));

    QPen penkropka;
    penkropka.setColor(QColor(182,26,26));

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
    QFont f( "Arial", 10, QFont::Bold);
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

    // -- ustalamy kilka rzeczy na początek --
    maxRangeVelIndex = dataTable->velocityTable[0].size()-1;
    maxObsNumber = dataTable->mjdTable.size()-1;
    rozmiarX = dataTable->mjdTable.size();
    rozmiarY = dataTable->velocityTable[0].size();
    // ---------------------------------------

    double minVelocity = dataTable->velocityTable[0][minRangeVelIndex];
    double maxVelocity = dataTable->velocityTable[0][maxRangeVelIndex];
    std::vector < std::vector < double > > & poltab = dataTable->spectraTableI;
    // -- setujemy size (ilość komórek) --
    heatMap->data()->setSize(rozmiarX, rozmiarY);
    // -- setujemy range --
    if (rozmiarX != 1)
        heatMap->data()->setRange(QCPRange(minObsNumber, maxObsNumber), QCPRange(minVelocity, maxVelocity ) );
    else
        heatMap->data()->setRange(QCPRange(-0.5, 0.5), QCPRange(minVelocity, maxVelocity ) );
    // -- zagnieżdżona pętla z tymi koksowymi cellami --
    for (unsigned long int xIndex = 0; xIndex < rozmiarX; xIndex++)
    {
        for (unsigned long int yIndex = 0; yIndex < rozmiarY; yIndex++)
        {
            heatMap->data()->setCell(xIndex, yIndex, poltab[xIndex][yIndex]);
        }
    }
    // --------------------------------------------------
    // pozostałe ustawienia
    gradient.loadPreset(QCPColorGradient::gpJet);
    heatMap->setGradient(gradient);
    heatMap->setDataScaleType(QCPAxis::stLinear);
    heatMap->rescaleDataRange();
    heatMap->rescaleKeyAxis();
    heatMap->rescaleValueAxis();
    heatMap->setTightBoundary(false);

    colorbar->setDataRange(heatMap->dataRange());
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

    QObject::connect(Ibut, SIGNAL(clicked()), this, SLOT( tmp_plot() ) );

    // klikałke
    QObject::connect(heatMapPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(pressMap(QMouseEvent*)) );
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
}

void heat_map_widget::setMapPressed(unsigned long x, unsigned long y)
{
    // ustawiamy crosshair
    setCrosshair(x,y);
    // ustawiamy widmo
    plotSingleSpectrum(x,y, dataTable->spectraTableI);
    // ustawiamy LCS
    //plotLCS(x,y);
    // ustalamy labele
    //setLabelClicked(x,y);

    // updatujemy graphy
    heatMapPlot->replot();
    spectrumPlot->replot();
    lcsPlot->replot();
    //lcsPlot->layer("linex")->replot();
    //lcsPlot->layer("liney")->replot();
    //lcsPlot->layer("prectangle")->replot();
}

// metody pomocnicze do klikałke
unsigned long int  heat_map_widget::searchForClickedX(double x)
{
    if(x < 0)
        x = 0.0;
    else if (x > dataTable->mjdTable.size()-1)
        x = dataTable->mjdTable.size()-1;
    return (unsigned long int) round(x);
}
unsigned long int  heat_map_widget::searchForClickedY(double y)
{
    unsigned long int yind = 0;
    // zabezpieczenie przed błędami
    if(y < dataTable->velocityTable[0][0])
    {
        y = dataTable->velocityTable[0][0];
        return (unsigned long int) 0;
    }
    else if (y > dataTable->velocityTable[0][dataTable->velocityTable[0].size()-1])
    {
        y = dataTable->velocityTable[0][dataTable->velocityTable[0].size()-1];
        return dataTable->velocityTable[0].size()-1;
    }

    // następnie musimy przeszukać tablicę Vel, by znaleźć indeks, odpowiadający klikniętemu Y:
    for(int i=0; i < dataTable->velocityTable[0].size(); i++)
    {
        if (dataTable->velocityTable[0][i] > y+0.5*(dataTable->velocityTable[0][1]-dataTable->velocityTable[0][0]))
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
    y_axis_line->start->setCoords(-QCPRange::maxRange, dataTable->velocityTable[0][y]);
    y_axis_line->end->setCoords(QCPRange::maxRange, dataTable->velocityTable[0][y]);
    // kwadrat
    double h = abs(dataTable->velocityTable[x][0] - dataTable->velocityTable[x][1]); // odstęp między kanałami
    rectangle->topLeft->setCoords(double(x) - 0.5, dataTable->velocityTable[x][y] + 0.5*h);
    rectangle->bottomRight->setCoords(double(x) + 0.5, dataTable->velocityTable[x][y] - 0.5*h);
}

void heat_map_widget::plotSingleSpectrum(unsigned long x, unsigned long y, std::vector < std::vector < double > > & poltab)
{
    // epoki
    #if QT_VERSION > QT_VERSION_CHECK(5,14,0)
        QVector < double > fluxes = QVector <double> (poltab[x].begin(), poltab[x].end());
        QVector < double > vels = QVector <double> (dataTable->velocityTable[x].begin(), dataTable->velocityTable[x].end());
    #else
        QVector < double > fluxes = QVector <double>::fromStdVector(poltab[x]);
        QVector < double > vels = QVector <double>::fromStdVector(dataTable->velocityTable[x]);
    #endif
    QVector < double > flux(1) ,vel(1);
    flux[0] = poltab[x][y];
    vel[0] = dataTable->velocityTable[x][y];
    // setujemy
    spectrumPlot->graph(0)->setData(vels, fluxes); // całe dane
    spectrumPlot->graph(1)->setData(vel, flux); // kropka
    spectrumVline->start->setCoords(dataTable->velocityTable[x][y], -QCPRange::maxRange);
    spectrumVline->end->setCoords(dataTable->velocityTable[x][y], QCPRange::maxRange);
    spectrumPlot->rescaleAxes();
}
