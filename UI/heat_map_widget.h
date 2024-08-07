#ifndef HEAT_MAP_WIDGET_H
#define HEAT_MAP_WIDGET_H
/*
   Klasa, porzechowująca interfejs do dynamic spectrum (heat map)
   Ma dostęp do spectral_container (dataTable)
*/
#include <QtGui>
#include <QWidget>
#include <iostream>
#include "libs/qcustomplot.h"
#include "data/spectral_container.h"
#include "UI/contentviewer.h"
#include "UI/custom_ui_elements.h"
// -- definiujemy klasę, która będzie używana późneij --

class heat_map_widget : public customWidget
{
    Q_OBJECT

public:
    // wskaźnik na kontener z danymi
    spectral_container * dataTable = new spectral_container;
    QCheckBox * isotime = new QCheckBox();
    // konstruktor
    explicit heat_map_widget(spectral_container * dataTable, QCheckBox * isotime);

    // główne miejsca
    // grid
    QGridLayout * grid = new QGridLayout(this);
    // checkboxy
    //QVBoxLayout * checkboxesOnDynspec = new QVBoxLayout();
    QCheckBox * setLogScale = new QCheckBox("Log scale", this);
    QCheckBox * rotateAllPols = new QCheckBox("Rotate IVLR", this);
    // buttony

    //-
    QShortcut * yDownBorder_shrt = new QShortcut(this);
    QShortcut * yUpBorder_shrt = new QShortcut(this);
    QShortcut * xDownBorder_shrt = new QShortcut(this);
    QShortcut * xUpBorder_shrt = new QShortcut(this);
    QShortcut * heatMapReset = new QShortcut(this);
    QShortcut * nextEpochKey = new QShortcut(this);
    QShortcut * prevEpochKey = new QShortcut(this);
    QShortcut * nextChanKey = new QShortcut(this);
    QShortcut * prevChanKey = new QShortcut(this);
    // -- toolbar: bottom --
    QToolBar * bottomToolBar = new QToolBar(this);
    // -- polaryzacje --
    QAction * Ibut = new QAction(this);
    QAction * Vbut = new QAction(this);
    QAction * LHCbut = new QAction(this);
    QAction * RHCbut = new QAction(this);
    // -- bordery --
    QAction * yDownBorder = new QAction(this);
    QAction * yUpBorder = new QAction(this);
    QAction * xDownBorder = new QAction(this);
    QAction * xUpBorder = new QAction(this);
    // -- pozostałe opcje --
    QAction * flag = new QAction(this);
    QAction * makeLcsButton = new QAction(this);
    QAction * recreateIButton = new QAction(this);
    // -- rotacja widm --
    QAction * rotate = new QAction(this);
    QAction * rotate_minus = new QAction(this);
    QTextEdit * numberOfRotatedChannelsTexted = new QTextEdit(this);
    QAction * saveEdition = new QAction;
    // -- layouty --
    //QVBoxLayout * onDynSpecButtons = new QVBoxLayout();
    //QHBoxLayout * topDynSpecButtons = new QHBoxLayout();
    QHBoxLayout * bottomDynSpecButtons = new QHBoxLayout();
    // -- labele --
    QLabel * leftLabel = new QLabel(this);
    QLabel * rightLabel = new QLabel(this);

    // -- zestay widgetów QCustomPlot --
    // - heat map -
    QWidget * heatMapWidget_w = new QWidget(this);
    QVBoxLayout * heatMapLayout = new QVBoxLayout(heatMapWidget_w);
    QCustomPlot * heatMapPlot = new QCustomPlot(this);
    QCPColorMap * heatMap = new QCPColorMap(heatMapPlot->xAxis, heatMapPlot->yAxis);
    QCPItemLine * x_axis_line = new QCPItemLine(heatMapPlot);
    QCPItemLine * y_axis_line = new QCPItemLine(heatMapPlot);
    QCPItemRect * rectangle = new QCPItemRect(heatMapPlot);
    QCPColorGradient gradient;
    // - colorbar -
    QWidget * colorbarWidget_w = new QWidget(this);
    QVBoxLayout * colorbarLayout = new QVBoxLayout(colorbarWidget_w);
    QCustomPlot * colorbarWidget = new QCustomPlot(this);
    QCPColorScale * colorbar = new QCPColorScale(colorbarWidget);
    // - widmo -
    QWidget * spectrum_w = new QWidget(this);
    QVBoxLayout * spectrumLayout = new QVBoxLayout(spectrum_w);
    QCustomPlot * spectrumPlot = new QCustomPlot(this);
    QCPItemLine * spectrumVline = new QCPItemLine(spectrumPlot);
    // - krzywa blasku -
    QWidget * lcs_w = new QWidget(this);
    QVBoxLayout * lcsLayout = new QVBoxLayout(lcs_w);
    QCustomPlot * lcsPlot = new QCustomPlot(this);
    QCPErrorBars * errorBars = new QCPErrorBars(lcsPlot->xAxis, lcsPlot->yAxis);
    QCPItemLine * lcsVline = new QCPItemLine(lcsPlot);

    // -- zestawy parametrów --
    unsigned long int minRangeVelIndex = 0;
    unsigned long int minObsNumber = 0;
    unsigned long int maxRangeVelIndex = 0;
    unsigned long int maxObsNumber = 0;
    unsigned long int rozmiarY = 0;
    unsigned long int rozmiarX = 0;
    unsigned long int xIndex = 0;
    unsigned long int yIndex = 0;
    // -- boole polaryzacji --
    bool polI = true;
    bool polV = false;
    bool polLHC = false;
    bool polRHC = false;
    // -- inne --
    bool firstPlotDone = false;
    bool normalizationB = false;
    bool darkMode = false;

    // -- custom widgets --
    contentViewer * cv = new contentViewer(this);

public:
    void darthMode(bool enabled = false);
    void firstPlotOnDynamicSpectrum();
    void setMapPressed(unsigned long int x, unsigned long int y);

public slots:
    void resetHeatMap();
    void replotPixLayer();

public slots:
    void updateHeatMap();
        void setMinVelOnHeatMap();
        void setMaxVelOnHeatMap();
        void setMinEpochOnHeatMap();
        void setMaxEpochOnHeatMap();  
        void choosePolI();
        void choosePolV();
        void choosePolLHC();
        void choosePolRHC();
    void rotatePlus();
    void rotateMinus();
    void saveEditedSpectra();
    void recal();
    void makeLCS();
    void setLogScale_slot();
    void tmp_plot();
    void pressMap(QMouseEvent * event);
    void flagActualEpoch();
    void nextEpoch();
    void prevEpoch();
    void nextChan();
    void prevChan();
    //void updateDynamicSpectrum();
    //void onClick();
    //void setClickedPoint(unsigned long int x, unsigned long int y);


private:
    void setButtonsProperties();
    void processTextEdits();
    void placeWidgets();
    void managePlottables();
    void setLabelTexts();
    void connectAllSlots();
    void connectForAxis();
    void addGraphs();
    // klikanie widma dynamicznego
    unsigned long int searchForClickedX(double x);
    unsigned long int searchForClickedY(double y);
    //void setMapPressed(unsigned long int x, unsigned long int y);
        void setCrosshair(unsigned long int x, unsigned long int y);
        void plotSingleSpectrum(unsigned long int x, unsigned long int y);
        void plotLCS(unsigned long int x, unsigned long int y, std::vector < double > & errtab);
        void setLabelClicked(unsigned long int x, unsigned long int y);
    // ogólne do skalowania wykresu etc.
    void rescaleGraph(QCustomPlot * plot);
    std::vector < std::vector < double > > * getPoltab();
    std::vector < double > * getErrtab();
    std::vector < double > * getNormtab();
    void setDownPolButtons();
    // rotacja widma
    void rotateSpectrum(bool direction);
    int readNumberOfRotatedChannels();
    double average(std::vector < double > table);
    void scaleHeatMap();
    void setDarkMode();
    void setLightMode();
    void colorGraphs(QPen dataPen, QPen errorPen, QPen dotPen);
    void colorCanvas(QPen background, QPen spines);
    void colorSpines(QCustomPlot * plot, QPen pendulum);
    void customizeApperance();
    void customizeApperanceLight();
    void setIconsLight();
    void setIconsDark();
};

#endif // HEAT_MAP_WIDGET_H
