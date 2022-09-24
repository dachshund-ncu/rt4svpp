#ifndef SINGLE_SPEC_WIDGET_H
#define SINGLE_SPEC_WIDGET_H
/*
 * Klasa, której zadaniem będzie wyświetlanie pojedynczego widma, wybieranego z listy
 * po prawej stronie
 * Utworzona 17.01.2022
 * Autor: Michał Durjasz
 * W argumentach powinna dostawać wskaźnik na kontener z danymi (spectral_container *)
*/
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include "data/spectral_container.h"
#include "libs/qcustomplot.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <vector>
#include <string>

class single_spec_widget : public QWidget
{
    Q_OBJECT
public:
    // -- wskaźnik na obiekt, przechowujący dane --
    spectral_container * dataTable;
    explicit single_spec_widget(spectral_container * dataTable);

    // -- grid --
    QGridLayout * grid = new QGridLayout(this);
    // -- buttony --
    QPushButton * savePlotsOnSingleSpectrum = new QPushButton(this);
    QPushButton * displayPlotOnSingleSpectrum = new QPushButton(this);
    QPushButton * setDefaultRangeButton = new QPushButton(this);
    QPushButton * eraseLastGraph = new QPushButton(this);
    QPushButton * saveAllSpectraToGnuplot = new QPushButton(this);
    // -- lista --
    QListWidget * listOfObservations = new QListWidget(this);
    // -- ploty --
    QCustomPlot * SingleSpectrumWidget = new QCustomPlot(this);
    // -- kontenery --
    std::vector < int > epochsPlotted;
    // -- boole --
    bool listOfObservationsFIlled = 0;
private:
    void setUpButtons();
    void placeEverythingTogether();
    void setUpPlots();
    void connectEv();
    void setUpGraphs();
    void rescaleGraph(QCustomPlot * plot);
    void addSpectrumToPlot(int epochNo);
    void setDarkMode();
    void setLightMode();
    void colorCanvas(QPen background, QPen spines);
    void colorSpines(QCustomPlot * plot, QPen pendulum);
public:
    void darthMode(bool enabled = false);
    void reset();

signals:

public slots:
     void fillListWithObservations();
     void add();
     void pop();
     void setDefaultRangeSlot();
     void savePlotsOnSingleSpectrumSlot();
     void saveAllSpectraToGnuplotSlot();

};

#endif // SINGLE_SPEC_WIDGET_H
