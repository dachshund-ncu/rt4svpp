#include "single_spec_widget.h"
single_spec_widget::single_spec_widget(spectral_container * dataTable) : dataTable(dataTable)
{
    this->setVisible(false);
    setUpButtons();
    placeEverythingTogether();
    connectEv();
    setUpGraphs();
    this->setGeometry(300,300, 1260, 720);
}

void single_spec_widget::setUpButtons()
{
    // -- rozmiary --
    savePlotsOnSingleSpectrum->setMinimumSize(0,0);
    displayPlotOnSingleSpectrum->setMinimumSize(0,0);
    setDefaultRangeButton->setMinimumSize(0,0);
    eraseLastGraph->setMinimumSize(0,0);
    saveAllSpectraToGnuplot->setMinimumSize(0,0);
    savePlotsOnSingleSpectrum->setMaximumSize(10000,10000);
    displayPlotOnSingleSpectrum->setMaximumSize(10000,10000);
    setDefaultRangeButton->setMaximumSize(10000,10000);
    eraseLastGraph->setMaximumSize(10000,10000);
    saveAllSpectraToGnuplot->setMaximumSize(10000,10000);
    // -- teksty --
    savePlotsOnSingleSpectrum->setText("Save plots from single spectrum");
    displayPlotOnSingleSpectrum->setText("Display plot on single spectrum");
    setDefaultRangeButton->setText("Set default range");
    eraseLastGraph->setText("Erase last graph");
    saveAllSpectraToGnuplot->setText("Save all spectra for gnuplot");
}

void single_spec_widget::placeEverythingTogether()
{
    // -- dodajemy widgety do grida --
    grid->addWidget(SingleSpectrumWidget, 0,0,18,4);
    grid->addWidget(savePlotsOnSingleSpectrum, 0,4,1,1);
    grid->addWidget(displayPlotOnSingleSpectrum, 1,4,1,1);
    grid->addWidget(setDefaultRangeButton, 2,4,1,1);
    grid->addWidget(eraseLastGraph, 3,4,1,1);
    grid->addWidget(saveAllSpectraToGnuplot, 4,4,1,1);
    grid->addWidget(listOfObservations, 5,4,13,1);
    // -- usztywniamy szerokość kolumny --
    grid->setColumnStretch(0,2);
    grid->setColumnStretch(1,2);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
}

void single_spec_widget::fillListWithObservations()
{
    if(!dataTable->loadedData)
        return;

    if(listOfObservationsFIlled)
    {
        listOfObservations->clear();
    }

    for(unsigned long int i = 0; i < dataTable->isotimeTable.size(); i++)
    {
         new QListWidgetItem( (std::string("[") + std::to_string(i) + std::string("]   ") + dataTable->isotimeTable[i] ).c_str(), listOfObservations );
    }

    if (!listOfObservationsFIlled)
        listOfObservationsFIlled = 1;
}

void single_spec_widget::connectEv()
{
    //

    // -- przyciski --
    connect(displayPlotOnSingleSpectrum, SIGNAL(clicked()), this, SLOT(add() ));
    connect(savePlotsOnSingleSpectrum, SIGNAL(clicked()), this, SLOT(savePlotsOnSingleSpectrumSlot() ));
    connect(setDefaultRangeButton, SIGNAL(clicked()), this, SLOT(setDefaultRangeSlot() ));
    connect(eraseLastGraph, SIGNAL(clicked()), this, SLOT(pop() ));
    connect(saveAllSpectraToGnuplot, SIGNAL(clicked()), this, SLOT(saveAllSpectraToGnuplotSlot() ));

    // -- akcje na widmie single spectrum --
    connect(SingleSpectrumWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), SingleSpectrumWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect(SingleSpectrumWidget->yAxis, SIGNAL(rangeChanged(QCPRange)), SingleSpectrumWidget->yAxis2, SLOT(setRange(QCPRange)));
}

void single_spec_widget::setUpGraphs()
{
    // -- podpis osi x --
    SingleSpectrumWidget->xAxis->setLabel("Velocity (km/s)");
    // -- ticki na górnej i prawej osi --
    SingleSpectrumWidget->yAxis2->setVisible(true);
    SingleSpectrumWidget->xAxis2->setVisible(true);
    SingleSpectrumWidget->xAxis2->setTickLabels(false);
    SingleSpectrumWidget->yAxis2->setTickLabels(false);
    // -- interakcje --
    SingleSpectrumWidget->setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
    SingleSpectrumWidget->axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    SingleSpectrumWidget->axisRect()->setRangeZoomAxes(SingleSpectrumWidget->xAxis, SingleSpectrumWidget->yAxis);
    SingleSpectrumWidget->setSelectionRectMode(QCP::srmZoom);
    // -- krzyżyk --
    SingleSpectrumWidget->setCursor(QCursor(Qt::CrossCursor));
}

void single_spec_widget::rescaleGraph(QCustomPlot * plot)
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

void single_spec_widget::addSpectrumToPlot(int epochNo)
{
    // -- zapełniamy kontenery --
    QVector < double > x(dataTable->velocityTable[epochNo].size()), y(dataTable->spectraTableI[epochNo].size());
    for (unsigned long int i = 0; i < dataTable->velocityTable[epochNo].size(); i++)
    {
        x[i] = dataTable->velocityTable[epochNo][i];
        y[i] = dataTable->spectraTableI[epochNo][i];
    }
    // -- wrzucamy je na wykres --
    SingleSpectrumWidget->addGraph();
    SingleSpectrumWidget->graph(epochsPlotted.size())->setData(x,y);
    // -- kolor (losowy xD) --
    QPen pen;
    pen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    pen.setWidth(2);
    SingleSpectrumWidget->graph(epochsPlotted.size())->setPen(pen);
    // -- reskalujemy --
    if (epochsPlotted.size() == 0)
        rescaleGraph(SingleSpectrumWidget);
    SingleSpectrumWidget->replot();
    // -- dodajemy do listy z epokami --
    epochsPlotted.push_back(epochNo);
}

void single_spec_widget::add()
{
    if (listOfObservations->currentRow() == -1)
        return;
    addSpectrumToPlot(listOfObservations->currentRow());
}

void single_spec_widget::pop()
{
    if (epochsPlotted.size() == 0)
        return;
    // -- usuwamy z kontenera --
    epochsPlotted.pop_back();
    // -- usuwamy z grafiki --
    SingleSpectrumWidget->removeGraph(epochsPlotted.size());
    // -- reskalujemy wykres --
    //rescaleGraph(SingleSpectrumWidget);
    SingleSpectrumWidget->replot();
}
void single_spec_widget::setDefaultRangeSlot()
{
    rescaleGraph(SingleSpectrumWidget);
    SingleSpectrumWidget->replot();
}
void single_spec_widget::savePlotsOnSingleSpectrumSlot()
{
    if(epochsPlotted.size() <= 0)
        return;

    std::string message;
    message = "Saved to: ";
    for(int &i : epochsPlotted)
    {
        dataTable->saveSpectrum(i+1);
        message += dataTable->getFileNameForAsciiSave(i+1) + "\n";
    }
    QMessageBox::information(this, tr("Message to you!"), QString::fromStdString(message));
}
void single_spec_widget::saveAllSpectraToGnuplotSlot()
{
    dataTable->saveAllSpectra();
    QMessageBox::information(this, tr("Message to you!"), tr("Saved all spectra succesfully!"));
}

void single_spec_widget::darthMode(bool enabled)
{
    if(enabled)
        setDarkMode();
    else
        setLightMode();
    SingleSpectrumWidget->replot();
}

void single_spec_widget::setDarkMode()
{
    QPen spinesPen(Qt::white);
    QPen background(Qt::black);
    colorCanvas(background, spinesPen);
}

void single_spec_widget::setLightMode()
{
    QPen spinesPen(Qt::black);
    QPen background(Qt::white);
    colorCanvas(background, spinesPen);
}

void single_spec_widget::colorCanvas(QPen background, QPen spines)
{
    // -- tło --
    SingleSpectrumWidget->setBackground(background.color());
    SingleSpectrumWidget->axisRect()->setBackground(background.color());
    // -- spines --
    colorSpines(SingleSpectrumWidget, spines);
    // -- replot --
    SingleSpectrumWidget->replot();
}
void single_spec_widget::colorSpines(QCustomPlot *plot, QPen pendulum)
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

void single_spec_widget::reset()
{
    unsigned long int limit = epochsPlotted.size();
    for(unsigned long int i = 0; i < limit; i++)
    {
        pop();
    }
    fillListWithObservations();
}
