#ifndef HEAT_MAP_WIDGET_H
#define HEAT_MAP_WIDGET_H

#include <QtGui>
#include <QWidget>
#include <iostream>
#include "libs/qcustomplot.h"

class heat_map_widget : public QWidget
{
public:
    // konstruktor
    heat_map_widget();

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
    // - colorbar -
    QCustomPlot * colorbarWidget = new QCustomPlot(this);
    QCPColorScale * colorbar = new QCPColorScale(colorbarWidget);
    // - widmo -
    QCustomPlot * spectrumPlot = new QCustomPlot(this);
    // - krzywa blasku -
    QCustomPlot * lcsPlot = new QCustomPlot(this);
    QCPErrorBars * errorBars = new QCPErrorBars(lcsPlot->xAxis, lcsPlot->yAxis);

private:
    void setButtonsProperties();
    void processTextEdits();
    void placeWidgets();
    void managePlottables();
    void setLabelTexts();

};

#endif // HEAT_MAP_WIDGET_H
