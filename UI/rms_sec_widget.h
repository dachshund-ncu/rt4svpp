#ifndef RMS_SEC_WIDGET_H
#define RMS_SEC_WIDGET_H
/*
 * Widget, przechowujący interfejs RMS_section
 * na którym wyświetlane są dane, dotyczące T_sys, RMS i integrated_flux_density
 */
#include <QObject>
#include <QWidget>
#include "libs/qcustomplot.h"
#include "data/spectral_container.h"
#include "UI/custom_ui_elements.h"

class Rms_sec_widget : public customWidget
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
    QPushButton * autoscaleGraphs = new QPushButton(this);
    // -- wykresy --
    customWidget * RmsVsTime_w = new customWidget(this);
    QVBoxLayout * RmsVsTime_layout = new QVBoxLayout(RmsVsTime_w);
    QCustomPlot * RmsVsTime = new QCustomPlot(this);
    customWidget * tsysVsTime_w = new customWidget(this);
    QVBoxLayout * tsysVsTime_layout = new QVBoxLayout(tsysVsTime_w);
    QCustomPlot * tsysVsTime = new QCustomPlot(this);
    customWidget * intVsTime_w = new customWidget(this);
    QVBoxLayout * intVsTime_layout = new QVBoxLayout(intVsTime_w);
    QCustomPlot * intVsTime = new QCustomPlot(this);
    // -- crosshairs --
    QCPItemLine * RmsXAxisLine = new QCPItemLine(RmsVsTime);
    QCPItemLine * RmsYAxisLine = new QCPItemLine(RmsVsTime);
    QCPItemLine * tsysXAxisLine = new QCPItemLine(tsysVsTime);
    QCPItemLine * tsysYAxisLine = new QCPItemLine(tsysVsTime);
    QCPItemLine * tintXAxisLine = new QCPItemLine(intVsTime);
    QCPItemLine * tintYAxisLine = new QCPItemLine(intVsTime);
    QCPItemText * rmsCshLabel = new QCPItemText(RmsVsTime);
    QCPItemText * tsysCshLabel = new QCPItemText(tsysVsTime);
    QCPItemText * tintCshLabel = new QCPItemText(intVsTime);
    // -- checkboxy --
    QCheckBox * IOnRms = new QCheckBox("I", this);
    QCheckBox * VOnRms = new QCheckBox("V", this);
    QCheckBox * LHCOnRms = new QCheckBox("LHC", this);
    QCheckBox * RHCOnRms = new QCheckBox("RHC", this);
    QCheckBox * showPoints = new QCheckBox("Show points", this);
    QCheckBox * showLines = new QCheckBox("Show lines", this);
    QCheckBox * rectZoom = new QCheckBox("Rectangle zoom", this);
    QCheckBox * showCross = new QCheckBox("Show crosshair", this);
    // -- text edity --
    QSpinBox * RmsIntStart = new QSpinBox(this);
    QSpinBox * RmsIntEnd = new QSpinBox(this);
    // -- grid --
    QGridLayout * grid = new QGridLayout(this);
    QVBoxLayout * exportVbox = new QVBoxLayout();
    // -- widget, przechowujący opcje etc. --
    QTabWidget * tabTools = new QTabWidget(this);
    QWidget * plotSettings = new QWidget(this);
    QGridLayout * plotSettingsGrid = new QGridLayout(plotSettings);
    QWidget * dataExport = new QWidget(this);
    QGridLayout * dataExportGrid = new QGridLayout(dataExport);
    QWidget * otherTools = new QWidget(this);
    QGridLayout * otherToolsGrid = new QGridLayout(otherTools);
    // -- labele --
    QLabel * stokesParams = new QLabel(this);
    QLabel * intParamsLabel = new QLabel(this);
    //QLabel * exportingSecLabel = new QLabel(this);
    QLabel * graphParamsLabel = new QLabel(this);
    QLabel * startIntegrateLabel = new QLabel(this);
    QLabel * endIntegrateLabel = new QLabel(this);
    // -- dekorator --
    QCPSelectionDecorator * dekorator = new QCPSelectionDecorator();
    // boole
    bool selectable = false;
    // --------------------------
    // -- popup window --
    customWidget * popupWindow = new customWidget();
    QGridLayout * gridOfPopupWindow = new QGridLayout(popupWindow);
    QWidget * spectrumOnPopupWindow_w = new customWidget(popupWindow);
    QVBoxLayout * spectrumOnPopupWindow_layout = new QVBoxLayout(spectrumOnPopupWindow_w);
    QCustomPlot * spectrumOnPopupWindow = new QCustomPlot(popupWindow);
    QPushButton * flagOnPopupWindow = new QPushButton(popupWindow);
    QPushButton * closePopupWIndow = new QPushButton(popupWindow);
    QLabel * labelOnPopupWindow = new QLabel(popupWindow);
    bool popupWindowOpened = false;
    int indexOfTheSpectrum = 0;
    // --------------------------
    // -----------------------------------------------------
private:
    void setUpButtons();
    void setUpLabels();
    void setUpPlottables();
    void placeOnGrid();
    void connectElementsToSlots();
    void autoscaleGraph(QCustomPlot * plot);
    std::vector < std::vector < double > > getIntegrateFromDataTable();
    int getChannel(QSpinBox * pole);
    void colorCanvas(QPen background, QPen spines);
    void colorSpines(QCustomPlot *plot, QPen pendulum);
    void setDarkMode();
    void setLightMode();
    void setCrosshairPen(QPen pen);
    void setSelectionForPlot(QCustomPlot * plotSelection, QCustomPlot * plot1, QCustomPlot * plot2);
    void setUpPopupWindow();
    void fillPopupWindowWithData(int index);
    void setLabelOnPopupWindow(int index);
    void clearGraphSelections();
    void customizeApperance();
    void customizeApperanceLight();
    void setCustomSSDarkOnPopupWindow();
    void setCustomSSLightOnPopupWindow();

private slots:
    void changeInteractions();
    void showPointsSlot();
    void showLinesSlot();


    // cross-hair
    void crossHairRmsVsTime(QMouseEvent* event);
    void crossHairTsysVsTime(QMouseEvent* event);
    void crossHairTintVsTime(QMouseEvent* event);
    // selekcja na wykresie
//    void showSpectrumOnSelectRms(QMouseEvent* event);
//    void showSpectrumOnSelectTsys(QMouseEvent* event);
//    void showSoectrumOnSelextTint(QMouseEvent* event);
    // export danych
    void exportRmsVsTimeSlot();
    void exportTsysVsTimeSlot();
    void exportTintVsTimeSlot();
    void exportAllAboveSlot();
    void recalculateIntegrationSlot();
    void setSelectionOnRms();
    void setSelectionOnTsys();
    void setSelectionOnInt();
    void showPopupWindowSlot();
    void rescaleGraphs();
    void flagActualEpoch();
    void showCrosshairSlot();

public:
    void darthMode(bool darthModeEnabled);
    void replotGraphs();

public slots:
    void closePopupWindowSlot();
    void fillWithData();
    void showIVLR();
};

#endif // RMS_SEC_WIDGET_H
