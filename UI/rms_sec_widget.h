#ifndef RMS_SEC_WIDGET_H
#define RMS_SEC_WIDGET_H

#include <QObject>
#include <QWidget>
#include "libs/qcustomplot.h"
#include "data/spectral_container.h"

class Rms_sec_widget : public QWidget
{
    Q_OBJECT
public:
    spectral_container * dataTable;
    Rms_sec_widget(spectral_container * dataTable);

    // -- buttony --
    QPushButton * recalculateIntegration = new QPushButton(this);
    QPushButton * exportRmsVsTme = new QPushButton(this);
    QPushButton * exportTintVsTme = new QPushButton(this);
    QPushButton * exportTsysVsTme = new QPushButton(this);
    QPushButton * exportAllVSTme = new QPushButton(this);
    QPushButton * showSelectedSpectrum = new QPushButton(this);
    // -- wykresy --
    QCustomPlot * RmsVsTime = new QCustomPlot(this);
    QCustomPlot * tsysVsTime = new QCustomPlot(this);
    QCustomPlot * intVsTime = new QCustomPlot(this);
    // -- crosshairs --
    QCPItemLine * RmsXAxisLine = new QCPItemLine(RmsVsTime);
    QCPItemLine * RmsYAxisLine = new QCPItemLine(RmsVsTime);
    QCPItemLine * tsysXAxisLine = new QCPItemLine(tsysVsTime);
    QCPItemLine * tsysYAxisLine = new QCPItemLine(tsysVsTime);
    QCPItemLine * tintXAxisLine = new QCPItemLine(intVsTime);
    QCPItemLine * tintYAxisLine = new QCPItemLine(intVsTime);
    // -- checkboxy --
    QCheckBox * IOnRms = new QCheckBox("I", this);
    QCheckBox * VOnRms = new QCheckBox("V", this);
    QCheckBox * LHCOnRms = new QCheckBox("LHC", this);
    QCheckBox * RHCOnRms = new QCheckBox("RHC", this);
    QCheckBox * showPoints = new QCheckBox("Show points", this);
    QCheckBox * showLines = new QCheckBox("Show lines", this);
    QCheckBox * rectZoom = new QCheckBox("Rectangle zoom", this);
    QCheckBox * selectionOfPoint = new QCheckBox("Select", this);
    // -- text edity --
    QTextEdit * RmsIntStart = new QTextEdit(this);
    QTextEdit * RmsIntEnd = new QTextEdit(this);
    // -- grid --
    QGridLayout * grid = new QGridLayout(this);
    QVBoxLayout * exportVbox = new QVBoxLayout();
    // -- labele --
    QLabel * stokesParams = new QLabel(this);
    QLabel * intParamsLabel = new QLabel(this);
    QLabel * exportingSecLabel = new QLabel(this);
    QLabel * graphParamsLabel = new QLabel(this);
    QLabel * startIntegrateLabel = new QLabel(this);
    QLabel * endIntegrateLabel = new QLabel(this);
    // boole
    bool selectable = false;
    // -----------------------------------------------------
    // -- show Points --
private:
    void setUpButtons();
    void setUpLabels();
    void setUpPlottables();
    void placeOnGrid();
    void connectElementsToSlots();
    void replotGraphs();
    void autoscaleGraph(QCustomPlot * plot);
    std::vector < std::vector < double > > getIntegrateFromDataTable();
    int getChannel(QTextEdit * pole);
private slots:
    void changeInteractions();
    void showPointsSlot();
    void showLinesSlot();
    void showIVLR();
    void switchSelect();
    void fillWithData();

};

#endif // RMS_SEC_WIDGET_H
