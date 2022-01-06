#ifndef HEAT_MAP_WIDGET_H
#define HEAT_MAP_WIDGET_H

#include <QtGui>
#include <QWidget>
#include <iostream>
#include "libs/qcustomplot.h"
#include "data/spectral_container.h"
// -- definiujemy klasę, która będzie używana późneij --

class heat_map_widget : public QWidget
{
    Q_OBJECT

public:
    // wskaźnik na kontener z danymi
    spectral_container * dataTable = new spectral_container;
    // konstruktor
    heat_map_widget(spectral_container * dataTable);
    // destruktor
    virtual ~heat_map_widget() {}

    // główne miejsca
    // grid
    QGridLayout * grid = new QGridLayout(this);
    // checkboxy
    QVBoxLayout * checkboxesOnDynspec = new QVBoxLayout();
    QCheckBox * setLogScale = new QCheckBox("Log scale", this);
    QCheckBox * rotateAllPols = new QCheckBox("Rotate IVLR", this);
    // buttony
    // -- bordery --
    QPushButton * yDownBorder = new QPushButton(this);
    QPushButton * yUpBorder = new QPushButton(this);
    QPushButton * xDownBorder = new QPushButton(this);
    QPushButton * xUpBorder = new QPushButton(this);
    // -- polaryzacje --
    QPushButton * Ibut = new QPushButton(this);
    QPushButton * Vbut = new QPushButton(this);
    QPushButton * LHCbut = new QPushButton(this);
    QPushButton * RHCbut = new QPushButton(this);
    // -- pozostałe opcje --
    QPushButton * flag = new QPushButton(this);
    QPushButton * makeLcsButton = new QPushButton(this);
    QPushButton * recreateIButton = new QPushButton(this);
    // -- rotacja widm --
    QPushButton * rotate = new QPushButton(this);
    QPushButton * rotate_minus = new QPushButton(this);
    QTextEdit * numberOfRotatedChannelsTexted = new QTextEdit(this);
    QPushButton * saveEdition = new QPushButton;
    // -- layouty --
    QVBoxLayout * onDynSpecButtons = new QVBoxLayout();
    QHBoxLayout * topDynSpecButtons = new QHBoxLayout();
    QHBoxLayout * bottomDynSpecButtons = new QHBoxLayout();
    // -- labele --
    QLabel * leftLabel = new QLabel(this);
    QLabel * rightLabel = new QLabel(this);

    // -- zestay widgetów QCustomPlot --
    // - heat map -
    QCustomPlot * heatMapPlot = new QCustomPlot(this);
    QCPColorMap * heatMap = new QCPColorMap(heatMapPlot->xAxis, heatMapPlot->yAxis);
    QCPItemLine * x_axis_line = new QCPItemLine(heatMapPlot);
    QCPItemLine * y_axis_line = new QCPItemLine(heatMapPlot);
    QCPItemRect * rectangle = new QCPItemRect(heatMapPlot);
    QCPColorGradient gradient;
    // - colorbar -
    QCustomPlot * colorbarWidget = new QCustomPlot(this);
    QCPColorScale * colorbar = new QCPColorScale(colorbarWidget);
    // - widmo -
    QCustomPlot * spectrumPlot = new QCustomPlot(this);
    QCPItemLine * spectrumVline = new QCPItemLine(spectrumPlot);
    // - krzywa blasku -
    QCustomPlot * lcsPlot = new QCustomPlot(this);
    QCPErrorBars * errorBars = new QCPErrorBars(lcsPlot->xAxis, lcsPlot->yAxis);
    QCPItemLine * lcsVline = new QCPItemLine(lcsPlot);

    // -- zesrawy parametrów --
    unsigned long int minRangeVelIndex = 0;
    unsigned long int minObsNumber = 0;
    unsigned long int maxRangeVelIndex = 0;
    unsigned long int maxObsNumber = 0;
    unsigned long int rozmiarY = 0;
    unsigned long int rozmiarX = 0;
    unsigned long int xIndex = 0;
    unsigned long int yIndex = 0;

public slots:
    void tmp_plot();
    void pressMap(QMouseEvent * event);

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
    void firstPlotOnDynamicSpectrum();
    void connectForAxis();
    void addGraphs();
    // klikanie widma dynamicznego
    unsigned long int searchForClickedX(double x);
    unsigned long int searchForClickedY(double y);
    void setMapPressed(unsigned long int x, unsigned long int y);
        void setCrosshair(unsigned long int x, unsigned long int y);
        void plotSingleSpectrum(unsigned long int x, unsigned long int y, std::vector < std::vector < double > > & poltab);
        void plotLCS(unsigned long int x, unsigned long int y);
        void setLabelClicked(unsigned long int x, unsigned long int y);
};

#endif // HEAT_MAP_WIDGET_H
