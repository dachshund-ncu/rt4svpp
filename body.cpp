#include "body.h"
#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <CCfits/CCfits>

using namespace std;
using namespace CCfits;
// -- konstruktor klasy programu --
body::body(QWidget *parent, const char * nazwa)
{

    Q_INIT_RESOURCE(resources);
    customizeApperance();
    customizeApperanceLight();
    window.setVisible(false);
    // -- ustawiamy rozmiary okna --
    this->setGeometry(300, 300, 150, 720);
    // -- ustawiamy tytul okna --
    this->setWindowTitle("RT4SV++");
    // -- setting up SUPER MEGA MENU BAR --
    createMenuEntries();
    makeActions();
    updateBar();
    connectActionsInSuperBar();
    connectSomeButtons();
    // -- RMS SELECTION --
    connectButtonsOnRmsSelection();
    // --
    window.layout()->setMenuBar(superMegaMenuBar);
    grid->addWidget(left_hand_list, 0,0,9,1);
    grid->setColumnStretch(0,1);

    // -- setujemy widgety roznych sekcji --
    connectSectionsToSlots();

    // -- probojemy czytac liste --
    if ( strncmp(nazwa, "", 300) != 0)
    {
        if (checkIfFits(nazwa) )
        {
            std::cout << "---> Fits file provided, loading..." << std::endl;
            QStringList lista;
            lista.append(QString(nazwa));
            dataTable->loadDataFromList(lista);
        }
        else
        {
            std::cout << "--> List of files provided, loading..." << std::endl;
            std::cout << "Loading list file " << "\"" << nazwa << "\"..." << std::endl;
            dataTable->loadDataFromList(string(nazwa));
        }


        if(dataTable->loadedData)
        {
            list_filename = string(nazwa);
            this->setGeometry(this->geometry().x(), this->geometry().y() ,1360,720);
            display_dynamic_spectrum();
            dynspecWidget->setMapPressed(0,0);
            geometry_window_set = 1;
            loaded_data = true;
            this->setWindowTitle(QString::fromStdString("RT4SV++: " + dataTable->nameOfSource));
        }
        else
        {
            std::cout << "Could not read list file \"" << nazwa << "\"" << std::endl;
        }
        selectorOfRMS->setValuesOfBoxes(dataTable->rmsChannelsTab);
        selectorOfRMS->setMaximumValues((int) dataTable->spectraTableI[0].size());
    }

    // -- domyślnie ustawiamy dark mode --
    set_dark_mode(true);
    // -- pokazujemy okno --
    window.setVisible(true);
    this->show();
}

void body::customizeApperance()
{
    /*
     * Aims to customize apperance of the main window of the app
     */
    QString styleSheet_widget = R"(
        QWidget {
            background-color: #121212;
            border-radius: 4px; /* border radius */
        }
    )";
    QString styleSheet_mw = R"(
        QWidget {
            background-color: #121212;
            border-radius: 4px; /* border radius */
        }
    )";
    QString menuSS = R"(
        QMenuBar {
            background-color: transparent;
        }
        QMenuBar::item {
            background-color: transparent;
            padding: 8px; /* padding */
            border-radius: 2px; /* border radius */
            font-size: 12px; /* font size */
            text-align: left;
            font-family: silka;
            color: white; /* text color */
        }
        QMenuBar::item:selected {
            background-color: rgba(255,255,255,9%);
            border: 1px solid rgba(255,255,255, 15%);
        }
        QMenu {
            background-color: transparent;
            color: white; /* text color */
            padding: 4px; /* padding */
            font-size: 12px; /* font size */
            border-radius: 2px; /* border radius */
            text-align: left;
            font-family: silka;
        }
        QAction{
            color: white; /* text color */
            padding: 4px; /* padding */
            font-size: 15px; /* font size */
            border-radius: 2px; /* border radius */
            text-align: left;
            font-family: silka;
        }
        QMenu::item {
            padding: 8px 12px;
            border-radius: 2px; /* border radius */
        }
        QMenu::item:selected {
            background-color: rgba(255,255,255,9%);
            border: 1px solid rgba(255,255,255, 15%);
        }
        QMenu::item:checked {
            background-color: #C2185B;
        }
    )";


    this->setCentralWidget(&window);
    this->window.setStyleSheet(styleSheet_widget);
    this->setStyleSheet(styleSheet_mw);

    superMegaMenuBar->setStyleSheet(menuSS);
    filesM->setStyleSheet(menuSS);
    advancedM->setStyleSheet(menuSS);
    dynSpecM->setStyleSheet(menuSS);
    singSpecM->setStyleSheet(menuSS);
    rmsSecM->setStyleSheet(menuSS);

    // -- customize popup widgets apperance --
    intWidget->setDarkModeW();
    averOverVelocityWidget->setDarkModeW();
    averOverTimeWidget->setDarkModeW();
    normalizationSelector->setDarkModeW();
    lcsExtractorWidget->setDarkModeW();
    SpectralIndexWidget->setDarkModeW();
    exDynspWidget->setDarkModeW();
    selectorOfRMS->setDarkModeW();
}

void body::customizeApperanceLight(){
    /*
     * Aims to customize apperance of the main window of the app
     */
    QString styleSheet_widget = R"(
        QWidget {
            background-color: #DEE4E7;
            border-radius: 4px; /* border radius */
        }
    )";
    QString styleSheet_mw = R"(
        QWidget {
            background-color: #DEE4E7;
            border-radius: 4px; /* border radius */
        }
    )";
    QString menuSS = R"(
        QMenuBar {
            background-color: transparent;
        }
        QMenuBar::item {
            background-color: #DEE4E7;
            padding: 8px; /* padding */
            border-radius: 2px; /* border radius */
            font-size: 12px; /* font size */
            text-align: left;
            font-family: silka;
            color: black; /* text color */
        }
        QMenuBar::item:selected {
            background-color: rgba(0,0,0,9%);
            border: 1px solid rgba(0,0,0, 15%);
        }
        QMenu {
            background-color: #DEE4E7;
            color: black; /* text color */
            padding: 4px; /* padding */
            font-size: 12px; /* font size */
            border-radius: 2px; /* border radius */
            text-align: left;
            font-family: silka;
        }
        QAction{
            color: black; /* text color */
            padding: 4px; /* padding */
            font-size: 15px; /* font size */
            border-radius: 2px; /* border radius */
            text-align: left;
            font-family: silka;
        }
        QMenu::item {
            padding: 8px 12px;
            border-radius: 2px; /* border radius */
        }
        QMenu::item:selected {
            background-color: rgba(0,0,0,9%);
            border: 1px solid rgba(0,0,0, 15%);
        }
        QMenu::item:checked {
            background-color: #C2185B;
        }
    )";


    this->setCentralWidget(&window);
    this->window.setStyleSheet(styleSheet_widget);
    this->setStyleSheet(styleSheet_mw);

    // -- customize menus apperance --
    superMegaMenuBar->setStyleSheet(menuSS);
    filesM->setStyleSheet(menuSS);
    advancedM->setStyleSheet(menuSS);
    dynSpecM->setStyleSheet(menuSS);
    singSpecM->setStyleSheet(menuSS);
    rmsSecM->setStyleSheet(menuSS);

    // -- customize popup widgets apperance --
    intWidget->setLightModeW();
    averOverVelocityWidget->setLightModeW();
    averOverTimeWidget->setLightModeW();
    normalizationSelector->setLightModeW();
    lcsExtractorWidget->setLightModeW();
    SpectralIndexWidget->setLightModeW();
    exDynspWidget->setLightModeW();
    selectorOfRMS->setLightModeW();

}

void body::setCheckedProperButtons()
{
    left_hand_list->DynamicSpectrum->setChecked(dynamic_spectrum_opened);
    left_hand_list->SingleSpectrum->setChecked(single_spectrum_opened);
    left_hand_list->RMSSection->setChecked(rms_section_opened);
}


void body::createMenuEntries()
{
    superMegaMenuBar->addMenu(filesM);
    superMegaMenuBar->addMenu(advancedM);
    superMegaMenuBar->addMenu(dynSpecM);
    superMegaMenuBar->addMenu(singSpecM);
    superMegaMenuBar->addMenu(rmsSecM);
}

void body::makeActions()
{
    // -----------------------
    loadAVRFile->setText("Load AVR files");
    loadFITSFile->setText("Load FITS files");
    reload->setText("Reload");
    quit->setText("Quit");
    // --
    filesM->addAction(loadAVRFile);
    filesM->addAction(loadFITSFile);
    filesM->addAction(reload);
    filesM->addSeparator();
    filesM->addAction(quit);
    // -----------------------
    openDynamicSpectrumA->setText("Show dynamic spectrum");
    openSingleSpectrumA->setText("Show single spectrum");
    openRmsSectionA->setText("Show RMS section");
    openIntegrationA->setText("Integrate");
    openAverOverVelA->setText("Aver over velocity");
    openAverOverTimeA->setText("Aver over time");
    openSpindicateA->setText("Variability coefficients");
    extractLCSA->setText("Extract light curve");
    openExportDynSpectrumA->setText("Export dynamic spectrum");
    //openCalibrateSectionA->setText("Open calibrate section");
    darthModeA->setText("Darth Mode");
    isoTimeA->setText("Include isotime");
    setRmsChannelsA->setText("Set channels for RMS calculation");
    darthModeA->setCheckable(true);
    isoTimeA->setCheckable(true);
    darthModeA->setChecked(true);
    showIonDS->setCheckable(true);
    showVonDS->setCheckable(true);
    showLHConDS->setCheckable(true);
    showRHConDS->setCheckable(true);
    showIonDS->setChecked(true);
    // --
    advancedM->addAction(openDynamicSpectrumA);
    advancedM->addAction(openSingleSpectrumA);
    advancedM->addAction(openRmsSectionA);
    advancedM->addSeparator();
    advancedM->addAction(openIntegrationA);
    advancedM->addAction(openAverOverVelA);
    advancedM->addAction(openAverOverTimeA);
    advancedM->addAction(openSpindicateA);
    advancedM->addAction(extractLCSA);
    advancedM->addAction(openExportDynSpectrumA);
    //advancedM->addAction(openCalibrateSectionA);
    advancedM->addSeparator();
    advancedM->addAction(darthModeA);
    advancedM->addAction(isoTimeA);
    advancedM->addSeparator();
    advancedM->addAction(setRmsChannelsA);
    // -----------------------
    showIonDS->setText("Show I on dynamic spectrum");
    showVonDS->setText("Show V on dynamic spectrum");
    showLHConDS->setText("Show LHC on dynamic spectrum");
    showRHConDS->setText("Show RHC on dynamic spectrum");
    rotatePlus->setText("Rotate +");
    rotateMinus->setText("Rotate -");
    save->setText("Save edited spectra");
    recalIVA->setText("Recalibrate I and V from R/LHC");
    flagA->setText("Flag");
    makeLCS->setText("Export light curve");
    logScale->setText("Set log color scale");
    rotate_IVLR->setText("Rotate L/RHC together");
    resetDS->setText("Reset heat map");
    normalize->setText("Normalize heat map");
    cancelNormalize->setText("Cancel normalization");
    showCV->setText("Show details");
    logScale->setCheckable(true);
    rotate_IVLR->setCheckable(true);
    logScale->setChecked(false);
    rotate_IVLR->setChecked(true);
    cancelNormalize->setEnabled(false);
    // --
    dynSpecM->addAction(showIonDS);
    dynSpecM->addAction(showVonDS);
    dynSpecM->addAction(showLHConDS);
    dynSpecM->addAction(showRHConDS);
    dynSpecM->addSeparator();
    dynSpecM->addAction(flagA);
    dynSpecM->addAction(makeLCS);
    dynSpecM->addSeparator();
    dynSpecM->addAction(rotatePlus);
    dynSpecM->addAction(rotateMinus);
    dynSpecM->addAction(save);
    dynSpecM->addAction(recalIVA);
    dynSpecM->addAction(rotate_IVLR);
    dynSpecM->addSeparator();
    dynSpecM->addAction(resetDS);
    dynSpecM->addAction(logScale);
    dynSpecM->addSeparator();
    dynSpecM->addAction(normalize);
    dynSpecM->addAction(cancelNormalize);
    dynSpecM->addSeparator();
    dynSpecM->addAction(showCV);
    // -----------------------
    exportAllSpectraA->setText("Export all spectra to ASCII");
    displayOnSingleSpecA->setText("Display marked epoch on plot");
    setDefaultRangeA->setText("Autorange plot");
    eraseLastGraphA->setText("Erase last added epoch from plot");
    exportSpectraFromGraphA->setText("Save epochs from plot to ASCII");
    // --
    singSpecM->addAction(displayOnSingleSpecA);
    singSpecM->addAction(eraseLastGraphA);
    singSpecM->addAction(setDefaultRangeA);
    singSpecM->addSeparator();
    singSpecM->addAction(exportSpectraFromGraphA);
    singSpecM->addAction(exportAllSpectraA);
    // -----------------------
    stokesIA->setText("Show I");
    stokesVA->setText("Show V");
    stokesLHCA->setText("Show LHC");
    stokesRHCA->setText("Show RHC");
    stokesIA->setCheckable(true);
    stokesVA->setCheckable(true);
    stokesLHCA->setCheckable(true);
    stokesRHCA->setCheckable(true);
    stokesIA->setChecked(true);
    // -
    showPointsA->setText("Show points");
    showLinesA->setText("Show lines");
    rectangleZoomA->setText("Rectangle zoom");
    showCrosshairA->setText("Show crosshair");
    showPointsA->setCheckable(true);
    showLinesA->setCheckable(true);
    rectangleZoomA->setCheckable(true);
    showCrosshairA->setCheckable(true);
    showPointsA->setChecked(true);
    rectangleZoomA->setChecked(true);
    showCrosshairA->setChecked(true);
    // -
    showSelSpectrumA->setText("Show selected spectrum");
    rescaleA->setText("Rescale");
    // -
    exportRmsVsTimeA->setText("Export RMS vs Time");
    exportSintVsTimeA->setText("Export Sint vs Time");
    exportTsysVsTimeA->setText("Export Tsys vs Time");
    exportAllParameA->setText("Export all of the above");
    // -
    recalculateIntegrationA->setText("Recalculate integration");
    // ---
    rmsSecM->addAction(stokesIA);
    rmsSecM->addAction(stokesVA);
    rmsSecM->addAction(stokesLHCA);
    rmsSecM->addAction(stokesRHCA);
    rmsSecM->addSeparator();
    rmsSecM->addAction(showPointsA);
    rmsSecM->addAction(showLinesA);
    rmsSecM->addAction(rectangleZoomA);
    rmsSecM->addAction(showCrosshairA);
    rmsSecM->addAction(rescaleA);
    rmsSecM->addAction(showSelSpectrumA);
    rmsSecM->addSeparator();
    rmsSecM->addAction(exportRmsVsTimeA);
    rmsSecM->addAction(exportSintVsTimeA);
    rmsSecM->addAction(exportTsysVsTimeA);
    rmsSecM->addAction(exportAllParameA);
    rmsSecM->addSeparator();
    rmsSecM->addAction(recalculateIntegrationA);
}

void body::updateBar()
{
    //dynSpecM->setVisible(dynSpecOpened);
    dynSpecM->menuAction()->setVisible(dynamic_spectrum_opened);
    //singSpecM->setVisible(singSpecOpened);
    singSpecM->menuAction()->setVisible(single_spectrum_opened);
    //rmsSecM->setVisible(rmsSpecOpened);
    rmsSecM->menuAction()->setVisible(rms_section_opened);
}

void body::connectActionsInSuperBar()
{
    // -------
    QObject::connect(loadAVRFile, SIGNAL(triggered()), this, SLOT(load_time_series_AVR()));
    QObject::connect(loadFITSFile, SIGNAL(triggered()), this, SLOT(load_time_series_FITS()));
    QObject::connect(reload, SIGNAL(triggered()), this, SLOT(reload_slot()));
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()), Qt::QueuedConnection);
    // -------
    QObject::connect(openDynamicSpectrumA, SIGNAL(triggered()), this, SLOT(display_dynamic_spectrum()));
    QObject::connect(openSingleSpectrumA, SIGNAL(triggered()), this, SLOT(display_single_spectrum()));
    QObject::connect(openRmsSectionA, SIGNAL(triggered()), this, SLOT(open_rms_section_slot()));
    QObject::connect(openIntegrationA, SIGNAL(triggered()), this, SLOT(openIntegrateSection()));
    QObject::connect(openAverOverVelA, SIGNAL(triggered()), this, SLOT(openAOVSection()));
    QObject::connect(openAverOverTimeA, SIGNAL(triggered()), this, SLOT(openAOTSection()));
    QObject::connect(openSpindicateA, SIGNAL(triggered()), this, SLOT(openSPINDSection()));
    QObject::connect(extractLCSA, SIGNAL(triggered()), this, SLOT(showExtractionWindow()));
    QObject::connect(openExportDynSpectrumA, SIGNAL(triggered()), this, SLOT(openWDSection()));
    //QObject::connect(openCalibrateSectionA, SIGNAL(triggered()), this, SLOT(openCALSection()));
    QObject::connect(darthModeA, SIGNAL(triggered()), this, SLOT(darkModeAction()));
    QObject::connect(isoTimeA, SIGNAL(triggered()), this, SLOT(isoTimeWrapperAction()));
    QObject::connect(setRmsChannelsA, SIGNAL(triggered()), this, SLOT(showRmsSelector()));
    // -------
    QObject::connect(showIonDS, SIGNAL(triggered()), this, SLOT(choosePolIButton()));
    QObject::connect(showVonDS, SIGNAL(triggered()), this, SLOT(choosePolVButton()));
    QObject::connect(showLHConDS, SIGNAL(triggered()), this, SLOT(choosePolLHCButton()));
    QObject::connect(showRHConDS, SIGNAL(triggered()), this, SLOT(choosePolRHCButton()));
    QObject::connect(recalIVA, SIGNAL(triggered()), dynspecWidget, SLOT(recal()));
    QObject::connect(flagA, SIGNAL(triggered()), dynspecWidget, SLOT(flagActualEpoch()));
    QObject::connect(rotatePlus, SIGNAL(triggered()), dynspecWidget, SLOT(rotatePlus()));
    QObject::connect(rotateMinus, SIGNAL(triggered()), dynspecWidget, SLOT(rotateMinus()));
    QObject::connect(save, SIGNAL(triggered()), dynspecWidget, SLOT(saveEditedSpectra()));
    QObject::connect(makeLCS, SIGNAL(triggered()), dynspecWidget, SLOT(makeLCS()));
    QObject::connect(logScale, SIGNAL(triggered()), this, SLOT(setLogScaleForAction()));
    QObject::connect(rotate_IVLR, SIGNAL(triggered()), this, SLOT(setIVLRCheckBox()));
    QObject::connect(resetDS, SIGNAL(triggered()), dynspecWidget, SLOT(resetHeatMap()));
    QObject::connect(showCV, SIGNAL(triggered()), dynspecWidget->cv, SLOT(show()));
    // -------
    QObject::connect(exportAllSpectraA, SIGNAL(triggered()), ssWidget, SLOT(saveAllSpectraToGnuplotSlot()));
    QObject::connect(displayOnSingleSpecA, SIGNAL(triggered()), ssWidget, SLOT(add()));
    QObject::connect(setDefaultRangeA, SIGNAL(triggered()), ssWidget, SLOT(setDefaultRangeSlot()));
    QObject::connect(eraseLastGraphA, SIGNAL(triggered()), ssWidget, SLOT(pop()));
    QObject::connect(exportSpectraFromGraphA, SIGNAL(triggered()), ssWidget, SLOT(savePlotsOnSingleSpectrumSlot()));
    // -------
    QObject::connect(stokesIA, SIGNAL(triggered()), this, SLOT(checkboxPolRmsWrapperAction()));
    QObject::connect(stokesVA, SIGNAL(triggered()), this, SLOT(checkboxPolRmsWrapperAction()));
    QObject::connect(stokesLHCA, SIGNAL(triggered()), this, SLOT(checkboxPolRmsWrapperAction()));
    QObject::connect(stokesRHCA, SIGNAL(triggered()), this, SLOT(checkboxPolRmsWrapperAction()));

    QObject::connect(rms_sec_w->IOnRms, SIGNAL(clicked()), this, SLOT(checkboxPolRmsWrapperButton()));
    QObject::connect(rms_sec_w->VOnRms, SIGNAL(clicked()), this, SLOT(checkboxPolRmsWrapperButton()));
    QObject::connect(rms_sec_w->LHCOnRms, SIGNAL(clicked()), this, SLOT(checkboxPolRmsWrapperButton()));
    QObject::connect(rms_sec_w->RHCOnRms, SIGNAL(clicked()), this, SLOT(checkboxPolRmsWrapperButton()));

    QObject::connect(showPointsA, SIGNAL(triggered()), this, SLOT(otherCheckboxesWrapperAction()));
    QObject::connect(showLinesA, SIGNAL(triggered()), this, SLOT(otherCheckboxesWrapperAction()));
    QObject::connect(rectangleZoomA, SIGNAL(triggered()), this, SLOT(otherCheckboxesWrapperAction()));
    QObject::connect(showCrosshairA, SIGNAL(triggered()), this, SLOT(otherCheckboxesWrapperAction()));

    QObject::connect(rms_sec_w->showPoints, SIGNAL(clicked()), this, SLOT(otherCheckboxesWrapperButton()));
    QObject::connect(rms_sec_w->showLines, SIGNAL(clicked()), this, SLOT(otherCheckboxesWrapperButton()));
    QObject::connect(rms_sec_w->rectZoom, SIGNAL(clicked()), this, SLOT(otherCheckboxesWrapperButton()));
    QObject::connect(rms_sec_w->showCross, SIGNAL(clicked()), this, SLOT(otherCheckboxesWrapperButton()));

    QObject::connect(showPointsA, SIGNAL(triggered()), rms_sec_w, SLOT(showPointsSlot()));
    QObject::connect(showLinesA, SIGNAL(triggered()), rms_sec_w, SLOT(showLinesSlot()));
    QObject::connect(rectangleZoomA, SIGNAL(triggered()), rms_sec_w, SLOT(changeInteractions()));
    QObject::connect(showCrosshairA, SIGNAL(triggered()), rms_sec_w, SLOT(showCrosshairSlot()));

    QObject::connect(showSelSpectrumA, SIGNAL(triggered()), rms_sec_w, SLOT(showPopupWindowSlot()));
    QObject::connect(recalculateIntegrationA, SIGNAL(triggered()), rms_sec_w, SLOT(recalculateIntegrationSlot()));
    QObject::connect(rescaleA, SIGNAL(triggered()), rms_sec_w, SLOT(rescaleGraphs()));

    QObject::connect(exportRmsVsTimeA, SIGNAL(triggered()), rms_sec_w, SLOT(exportRmsVsTimeSlot()));
    QObject::connect(exportSintVsTimeA, SIGNAL(triggered()), rms_sec_w, SLOT(exportTintVsTimeSlot()));
    QObject::connect(exportTsysVsTimeA, SIGNAL(triggered()), rms_sec_w, SLOT(exportTsysVsTimeSlot()));
    QObject::connect(exportAllParameA, SIGNAL(triggered()), rms_sec_w, SLOT(exportAllAboveSlot()));

    QObject::connect(normalize, SIGNAL(triggered()), this, SLOT(showNormalizationWindow()));
    QObject::connect(cancelNormalize, SIGNAL(triggered()), this, SLOT(cancelNormalization()));
    QObject::connect(normalizationSelector->cancel, SIGNAL(clicked()), this, SLOT(hideNormalizationWindow()));
    QObject::connect(normalizationSelector->make, SIGNAL(clicked()), this, SLOT(goWithNormalization()));

    QObject::connect(lcsExtractorWidget->make, SIGNAL(clicked()), this, SLOT(performExtraction()));
    QObject::connect(lcsExtractorWidget->cancel, SIGNAL(clicked()), this, SLOT(hideExtractionWindow()));

}

void body::connectSomeButtons()
{
    QObject::connect(dynspecWidget->Ibut, SIGNAL(triggered()), this, SLOT(choosePolIButton()));
    QObject::connect(dynspecWidget->Vbut, SIGNAL(triggered()), this, SLOT(choosePolVButton()));
    QObject::connect(dynspecWidget->LHCbut, SIGNAL(triggered()), this, SLOT(choosePolLHCButton()));
    QObject::connect(dynspecWidget->RHCbut, SIGNAL(triggered()), this, SLOT(choosePolRHCButton()));

    QObject::connect(dynspecWidget->setLogScale, SIGNAL(clicked()), this, SLOT(setLogScaleSlot()));
    QObject::connect(dynspecWidget->rotateAllPols, SIGNAL(clicked()), this, SLOT(setIVLRAction()));

    QObject::connect(left_hand_list->IsotimeInclude, SIGNAL(clicked()), this, SLOT(isoTimeWrapper()));
}



/*
 * This is for handling checkboxes - so they turn on and off at the same time
*/
void body::isoTimeWrapper()
{
    isoTimeA->setChecked(left_hand_list->IsotimeInclude->isChecked());
}
void body::isoTimeWrapperAction()
{
    left_hand_list->IsotimeInclude->setChecked(isoTimeA->isChecked());
}


void body::setIVLRCheckBox()
{
    dynspecWidget->rotateAllPols->setChecked(rotate_IVLR->isChecked());
}
void body::setIVLRAction()
{
    rotate_IVLR->setChecked(dynspecWidget->rotateAllPols->isChecked());
}

/*
 * This is handler for displaying LOG color scale on a heatmap
 * LOG itself is handled in heat_map_widget class
*/
void body::setLogScaleSlot()
{
    logScale->setChecked(dynspecWidget->setLogScale->isChecked());
    dynspecWidget->setLogScale_slot();
}
void body::setLogScaleForAction()
{
    dynspecWidget->setLogScale->setChecked(logScale->isChecked());
    dynspecWidget->setLogScale_slot();
}

/*
 * This is for choosing STOKES on dynamic spectrum
 * We need this to be cross compatible (change on DS will change also actions in menu)
*/

void body::choosePolIButton()
{
    dynspecWidget->choosePolI();
    setProperActionsChecked();
}
void body::choosePolVButton()
{
    dynspecWidget->choosePolV();
    setProperActionsChecked();
}
void body::choosePolLHCButton()
{
    dynspecWidget->choosePolLHC();
    setProperActionsChecked();
}
void body::choosePolRHCButton()
{
    dynspecWidget->choosePolRHC();
    setProperActionsChecked();
}


void body::setProperActionsChecked()
{
    showIonDS->setChecked(dynspecWidget->polI);
    showVonDS->setChecked(dynspecWidget->polV);
    showLHConDS->setChecked(dynspecWidget->polLHC);
    showRHConDS->setChecked(dynspecWidget->polRHC);
}

/*
 * These two are for controlling, if on RMS_Section checked boxes are
 * consistent with menu
 */
void body::checkboxPolRmsWrapperAction()
{
    rms_sec_w->IOnRms->setChecked(stokesIA->isChecked());
    rms_sec_w->VOnRms->setChecked(stokesVA->isChecked());
    rms_sec_w->LHCOnRms->setChecked(stokesLHCA->isChecked());
    rms_sec_w->RHCOnRms->setChecked(stokesRHCA->isChecked());
    rms_sec_w->showIVLR();
}
void body::checkboxPolRmsWrapperButton()
{
    stokesIA->setChecked(rms_sec_w->IOnRms->isChecked());
    stokesVA->setChecked(rms_sec_w->VOnRms->isChecked());
    stokesLHCA->setChecked(rms_sec_w->LHCOnRms->isChecked());
    stokesRHCA->setChecked(rms_sec_w->RHCOnRms->isChecked());
    // -- no showIVLR(), cause it is already connected in the rms_sec_w widget! --
}

void body::otherCheckboxesWrapperAction()
{
    rms_sec_w->showPoints->setChecked(showPointsA->isChecked());
    rms_sec_w->showLines->setChecked(showLinesA->isChecked());
    rms_sec_w->rectZoom->setChecked(rectangleZoomA->isChecked());
    rms_sec_w->showCross->setChecked(showCrosshairA->isChecked());
}

void body::otherCheckboxesWrapperButton()
{
    showPointsA->setChecked(rms_sec_w->showPoints->isChecked());
    showLinesA->setChecked(rms_sec_w->showLines->isChecked());
    rectangleZoomA->setChecked(rms_sec_w->rectZoom->isChecked());
    showCrosshairA->setChecked(rms_sec_w->showCross->isChecked());
}

//-------------------------------------------------------------------------------
/*
 *Below we will handle the RMS Selecting window
 */
void body::connectButtonsOnRmsSelection()
{
    QObject::connect(selectorOfRMS->perform, SIGNAL(clicked()), this, SLOT(setNewRMSChannels()));
}

void body::setNewRMSChannels()
{
    dataTable->setNewRMSChannels(selectorOfRMS->getValuesFromBoxes());
    selectorOfRMS->setVisible(false);
    dataTable->recalculateRMS();
    // ----------
    dynspecWidget->updateHeatMap();
    if (rms_section_opened)
    {
        rms_sec_w->fillWithData();
        rms_sec_w->replotGraphs();
    }
}

void body::showRmsSelector()
{
    if(!dataTable->loadedData)
    {
        popupMessage("Error!", "Please, load data first!");
//        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    selectorOfRMS->show();
}

//-------------------------------------------------------------------------------
bool body::checkIfFits(const char * filename)
{
    try
    {
        CCfits::FITS pies(filename, CCfits::Read);
        CCfits::ExtHDU & table = pies.extension(1);
        return true;
    }
    catch (...)
    {
        return false;
    }
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
/*
 * Below: normalization slots, connected to "normalize" and "cancelNormalize" menu entries
 */
void body::showNormalizationWindow()
{
    /*
     * Shows simple window with channels, used for normalization
     */
    normalizationSelector->startingChannelInt->setText(std::to_string(dynspecWidget->yIndex).c_str());
    normalizationSelector->endingChannelInt->setText(std::to_string(dynspecWidget->yIndex + 2).c_str());
    normalizationSelector->setVisible(true);
}
void body::hideNormalizationWindow()
{
    /*
     * Hides this normalization window
     */
    normalizationSelector->setVisible(false);
}
void body::goWithNormalization()
{
    dynspecWidget->normalizationB = true;
    cancelNormalize->setEnabled(true);
    // --
    std::vector < int > chns = readMinMaxValuesFromChannels(*(normalizationSelector->startingChannelInt), *(normalizationSelector->endingChannelInt));
    dataTable->setNormalizationCoeffs(chns[0], chns[1]);
    // --
    hideNormalizationWindow();
    // --
    dynspecWidget->updateHeatMap();
}
void body::cancelNormalization()
{
    dynspecWidget->normalizationB = false;
    cancelNormalize->setEnabled(false);
    // --
    dynspecWidget->updateHeatMap();
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
/*
 * BELOW: slots, connected to the Light Curve Extraction widget
 */
void body::showExtractionWindow()
{
    lcsExtractorWidget->startingChannelInt->setText(std::to_string(dynspecWidget->yIndex+1 - 2).c_str());
    lcsExtractorWidget->endingChannelInt->setText(std::to_string(dynspecWidget->yIndex+1 + 2).c_str());
    lcsExtractorWidget->setVisible(true);
}
void body::hideExtractionWindow()
{
    lcsExtractorWidget->setVisible(false);
}
void body::performExtraction()
{
    std::vector < int > chns = readMinMaxValuesFromChannels(*(lcsExtractorWidget->startingChannelInt), *(lcsExtractorWidget->endingChannelInt));
    if (chns[0] < 1) // -- failsafe in case of incorrect channel selection --
    {
        hideExtractionWindow();
        return;
    }
    dataTable->extractLCS4Pol(chns[0], chns[1], left_hand_list->IsotimeInclude->isChecked());
    hideExtractionWindow();
    // -- message to the user --
    string message = "";
    message = "Extracted lifht curve from channels " + std::to_string(chns[0]) + " -> " + std::to_string(chns[1]) + "\n" + "Saved to " + dataTable->getExtractedFileName(chns[0], chns[1]);
    popupMessage("Message to you", message);
}
//-------------------------------------------------------------------------------

// - wyswietla w programie sekcje "single spectrum"
void body::display_single_spectrum()
{
    // --- zmiana
    // -- obwarowanie warunkami --
    if (!dataTable->loadedData)
    {
        popupMessage("Error!", "Please, load data first!");
        left_hand_list->SingleSpectrum->setChecked(false);
        return;
    }
    if (dynamic_spectrum_opened)
       kill_dynamic_spectrum();
    else if (rms_section_opened)
        close_rms_section_slot();
    else if (single_spectrum_opened)
        return;

    // -- dodajemy widget do głównego gridu --
    grid->addWidget(ssWidget, 0,1,9,5);
    // -- dodajemy kill singspec do vboxa --
    // -- ustalamy szerokości kolumny --
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);
    // -- zapelniamy wstepnie single spectrum --
    ssWidget->fillListWithObservations();
    // -- ustawiamy visibility naszego widgetu --
    ssWidget->setVisible(true);
    // -- ustawiamy boola, informujacego co jest akurat otwarte --
    single_spectrum_opened=1;
    // -----------
    setCheckedProperButtons();

    updateBar();
}

// - zamyka sekcję "single spectrum"
void body::kill_single_spectrum()
{
    // - odpinamy od grida -
    grid->removeWidget(ssWidget);
    // - odpinamy od vboxa -
    // - znikamy -
    ssWidget->setVisible(false);
    // - ustawiamy widoczność -
    single_spectrum_opened=0;
    //
    setCheckedProperButtons();

    updateBar();
}

void body::loadTimeSeriesWrapper(QFileDialog * dialog)
{
    string nazwa_pliku; // string z nazwa pliku
    QStringList fileName1;// qstring z nazwa pliku
    QString fileName;
    dialog->setFileMode(QFileDialog::ExistingFiles);


    if(dialog->exec())
    {
        fileName1 = dialog->selectedFiles();
    }

    if (fileName1.size() > 0)
    {
        fileName = fileName1[0];

    }
    else
    {
        return;
    }

    nazwa_pliku = fileName.toStdString(); // ustalamy nazwe pliku
    if (nazwa_pliku == "")
    {
        return;
    }

    QFileInfo info(fileName);

    //cout << info.absolutePath().toStdString() << endl; // ustalamy sciezke dzialania programu
    if (info.absolutePath().toStdString() != "")
    {
        working_directory = info.absolutePath().toStdString();
        //cout << working_directory << endl;

    }

    dataTable->loadDataFromList(fileName1);
    //cout << fileName1.size() << endl;
    loaded_data = 1;

    dynspecWidget->resetHeatMap();
    ssWidget->reset();
    rms_sec_w->fillWithData();

    if (geometry_window_set == 0)
    {
        this->setGeometry(this->geometry().x(), this->geometry().y(), 1360,720);
        display_dynamic_spectrum();
        geometry_window_set = 1;
    }
    dynspecWidget->setMapPressed(0,0);
    this->setWindowTitle(QString::fromStdString("RT4SV++: " + dataTable->nameOfSource));
    selectorOfRMS->setValuesOfBoxes(dataTable->rmsChannelsTab);
    selectorOfRMS->setMaximumValues((int) dataTable->spectraTableI[0].size());
}

// -- to samo robi, co read time series - ale po wcisnieciu przycisku --
void body::load_time_series_AVR()
{
    QFileDialog dialog(nullptr, tr("Select AVR files"), tr(""), tr("AVR files (*AVR.DAT);;All Files (*);;FITS files(*fits)"));
    loadTimeSeriesWrapper(&dialog);
}

void body::load_time_series_FITS()
{
    QFileDialog dialog(nullptr, tr("Select FITS files"), tr(""), tr("FITS files(*fits);;All Files (*);;AVR files (*AVR.DAT)"));
//    dialog.setObjectName("loadFitsFiles");
    loadTimeSeriesWrapper(&dialog);
}


// -- liczy calke z wszystkich widm --
void body::integrate_time_series()
{
    std::vector < int > minmax = readMinMaxValuesFromChannels(*intWidget->startingChannelInt, *intWidget->endingChannelInt);
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;
    // --- całka właściwa ---
    dataTable->integrate4Pols(min, max, left_hand_list->IsotimeInclude->isChecked());
    // --- wiadomość końcowa ---
    string message = "";
    message = "Integrated over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getIntegrationFileName(min, max);
    closeIntegrateSection();
    popupMessage("Message to you", message);
}


// -- wyswietla widmo dynamiczne --
void body::display_dynamic_spectrum()
{
    if (!dataTable->loadedData)
    {
        popupMessage("Error!", "Please, load data first!");
        left_hand_list->DynamicSpectrum->setChecked(false);
        return;
    }
    if (single_spectrum_opened == 1)
        kill_single_spectrum();
    else if (rms_section_opened == 1)
        close_rms_section_slot();
    else if (dynamic_spectrum_opened == 1)
        dynspecWidget->resetHeatMap();
    // -- chwilunia --
    if (!dynspecWidget->firstPlotDone)
        dynspecWidget->firstPlotOnDynamicSpectrum();
    // -- dodajemy widget do grida --
    grid->addWidget(dynspecWidget, 0,1,9,5);
    // -- dodajemy do vbox maina przycisk killujacy dynspec --
    // -- ustalamy szerokości kolumny --
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);
    // -- visibility --
    dynspecWidget->setVisible(true);
    // -- bool --
    dynamic_spectrum_opened = true;

    setCheckedProperButtons();

    updateBar();
}

// -- zamyka widmo dynamiczne --
void body::kill_dynamic_spectrum()
{
    dynspecWidget->setVisible(false);
    grid->removeWidget(dynspecWidget);
    dynamic_spectrum_opened = false;

    setCheckedProperButtons();

    updateBar();
}

// -- czyta kanały do liczenia rms z pliku 'chan4rms.sv' --
void body::read_chan4rms()
{
    // na początek - sprawdzamy rozmiar pliku:
    ifstream fle_check_tmp( (working_directory + "/" + "chan4rms.sv").c_str(), ios::binary | ios::ate);
    //cout << "rozmiar: " << fle_check_tmp.tellg() << endl;
    if (fle_check_tmp.tellg() < 10)
    {
        fle_check_tmp.close();
        chan4rms_loaded = 0;
        cout << " ---> Are you sure, that \"chan4rms.sv\" contains what it should? It's too small to be correct!" << endl;
        return;
    }
    fle_check_tmp.close();
    // obiekt pliku chan4rms
    ifstream chan4rms_file;
    // otwieramy chan4rms
    chan4rms_file.open((working_directory + "/" + "chan4rms.sv").c_str());
    // bufor
    string bufor;
    // char do sprawdzania, czy linia zaczyna się od #
    char spr;
    // umieszczamy w otoczeniu try... catch... by złapać ewentualny błąd w czytaniu pliku
    try
    {

        if (chan4rms_file.good())
        {
                chan4rms_file.get(spr);
                if (spr != '#')
                {
                    chan4rms_file.seekg(-1, ios::cur);
                    chan4rms_file >> rms_start_channel1;
                    chan4rms_file >> rms_end_channel1;
                    chan4rms_file >> rms_start_channel2;
                    chan4rms_file >> rms_end_channel1;
                }
                else
                {

                    getline(chan4rms_file, bufor);
                    //cout << bufor << endl;
                    chan4rms_file >> rms_start_channel1 >> rms_end_channel1;
                    chan4rms_file >> rms_start_channel2 >> rms_end_channel2;
                }
           chan4rms_loaded = 1;
           cout << "---> chan4rms.sv loaded!\n";
         }
        chan4rms_file.close();
    }

    catch (...)
    {
        chan4rms_file.close();
        chan4rms_loaded = 0;
        cout << " ---> found chan4rms.sv, but did not manage to read it" << endl;
    }

}

// -- czyta wartości kanałów z pliku 'chan4int.sv' --
bool body::read_chan4int()
{
    // na początek - sprawdzamy rozmiar pliku:
    ifstream fle_check_tmp( (working_directory + "/" + "chan4int.sv").c_str(), ios::binary | ios::ate);
    //cout << "rozmiar: " << fle_check_tmp.tellg() << endl;
    if (fle_check_tmp.tellg() < 10)
    {
        fle_check_tmp.close();
        //chan4rms_loaded = 0;
        cout << " ---> Are you sure, that \"chan4int.sv\" contains what it should? It's too small to be correct!" << endl;
        return 0;
    }
    fle_check_tmp.close();

    ifstream chan4int;
    chan4int.open((working_directory + "/" + "chan4int.sv").c_str());
    string bufor;
    char spr;

    try
    {
        if (chan4int.good())
        {
            chan4int.get(spr);
            if (spr != '#')
            {
                chan4int.seekg(-1, ios::cur);
                chan4int >> chan4int_start;
                chan4int >> chan4int_end;
            }
            else
            {
                getline(chan4int, bufor);
                chan4int >> chan4int_start;
                chan4int >> chan4int_end;
            }
        }
        else
        {
            //cout << endl;
            //cout << "----> Could not find chan4int.sv!" << endl;
            chan4int.close();
            return 0;
        }
        chan4int.close();
        return 1;
     }
    catch (...)
    {
        chan4int.close();
        return 0;
    }

}

// -- liczy srednia po predkosci - dla wszystkich epok --
void body::calculate_aver_over_velocity()
{
    std::vector < int > minmax = readMinMaxValuesFromChannels(*averOverVelocityWidget->startingChannelInt, *averOverVelocityWidget->endingChannelInt);
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;

    // liczymy aver over velocity
    dataTable->averageOverVelocity4Pols(min, max, left_hand_list->IsotimeInclude->isChecked());

    string message = "";
    message = "Averaged over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getAverOverVelFileName(min, max);
    closeAOVSection();
    popupMessage("Message to you", message);

}

// -- liczy srednia po czasie - dla jednej epoki --
vector < double > body::average_over_time(int min_epoch, int max_epoch, vector < double > time_series, vector < double >  error)
{
    double suma = 0.0;
    int number_of_epochs;
    number_of_epochs = max_epoch - min_epoch + 1;
    if (number_of_epochs <= 0)
        number_of_epochs = 1;

    // petla liczaca srednia
    for (int i = 0; i < number_of_epochs; i++)
    {
        suma = suma + time_series[min_epoch + i];
    }
    suma = suma / number_of_epochs;

    // peyla liczaca blad
    double sumaer = 0.0;
    for (int i = 0; i < number_of_epochs; i++)
    {
        sumaer = sumaer + error[min_epoch + i];
    }

    sumaer = sumaer / number_of_epochs;

    vector < double > wyniki (2);
    wyniki[0] = suma;
    wyniki[1] = sumaer;

    return wyniki;
}

// -- liczy srednia po czasie - dla wszystkich epok --
void body::calculate_aver_over_time()
{
    // wypisujemy co chcemy
    std::vector < int > minmax = readMinMaxValuesFromEpochs(*averOverTimeWidget->startingChannelInt, *averOverTimeWidget->endingChannelInt);
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;

    // wykonujemy właściwej transformacji
    dataTable->averOverTime4Pols(min, max);

    // wiadomość dla usera
    string message;
    message = "Averaged over epochs: " + to_string(min) + " " + " -> " + to_string(max) + "\n";
    message = message + "Saved to " + dataTable->getAverOverTimeFileName(min, max);
    closeAOTSection();
    popupMessage("Message to you", message);
}


// -- liczy VI, FI i chi2red dla wszystkich kanałów --
void body::calculate_spectral_index()
{
    /*
     * Celem tej metody jest policzenie współczynników VI, FI i Chi^2_red
     * Oraz zapisanie ich do plików tekstowych (robi to klasa spectral_container, tutaj tylko wywołujemy jej metodę)
    */
    // --------------
    std::vector < int > minmax = readMinMaxValuesFromEpochs(*SpectralIndexWidget->startingChannelInt, *SpectralIndexWidget->endingChannelInt);
    double absoluteErr = readNumberFromQTextEdit(SpectralIndexWidget->absoluteErrorBox);
    //std::cout << absoluteErr << std::endl;
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;
    // --------------
    dataTable->spectralIndex4Pol(min, max, absoluteErr);
    // --------------
    string message;
    message = "Spectral-indexed over epochs: " + to_string(min) + " " + " -> " + to_string(max) + "\n";
    message = message + "VI Saved to " + dataTable->getVIFileName(min, max) + "\n";
    message = message + "FI Saved to " + dataTable->getFIFileName(min, max) + "\n";
    message = message + "Chi2Red Saved to " + dataTable->getChi2RedFileName(min, max) + "\n";
    // --------------
    closeSPINDSection();
    popupMessage("Message to you", message);
}

void body::save_all_to_gnuplot_slot()
{
    dataTable->saveAllSpectra();
    // - zapisujemy wiadomość -
    std::string message = "Saved all spectra to directory: " + dataTable->saveDirectory;
    // - wyświetlamy -
    popupMessage("Message to you!", message);
}

// -- przeładowuje obecnie załadowane dane --
void body::reload_slot()
{
    if (loaded_data == 0)
    {
        popupMessage("Error!" ,"Please, load data first!");
        return;
    }

    if (dataTable->fileNamesTab.size() != 0)
    {
        // --- tymczasowo ---
        QStringList tmpqstringlist;
        for(unsigned long int wplw = 0; wplw < dataTable->fileNamesTab.size(); wplw++)
        {
            tmpqstringlist.push_back(QString::fromStdString(dataTable->fileNamesTab[wplw]));
        }
        // -------------------
        dataTable->loadDataFromList(tmpqstringlist);
        // -- zapełniamy danymi sekcję RMS --
        rms_sec_w->fillWithData();
        // -- updatujemy widmo dynamiczne --
        dynspecWidget->setMapPressed(0,0);
        dynspecWidget->resetHeatMap();
        // -- i również widmo zwykłe --
        ssWidget->reset();
        // -- i RMS section --
        rms_sec_w->fillWithData();
    }
}

// -- czyta nazwy plików z pliku 'flagged_obs.dat' --
bool body::read_flagged_files()
{
    flagged_avr_files.clear();
    ifstream flagfile;
    flagfile.open((working_directory + "/" + "flagged_obs.dat").c_str());
    if (!flagfile.good())
    {
        cout << "No flagfile_obs.dat file" << endl;
        return false;
    }

    string bufor_do_listy; // maly bufor do przechowywania linii z listy

    // - petla wczytujaca pliki z obserwacjami -
    while(flagfile.good())
    {
      // czytamy linie z pliku
      getline(flagfile, bufor_do_listy);
      // jesli jest zerowej dlugosci, to mamy koniec pliku i wywalamy z petli
      if(bufor_do_listy.size() < 1)
      {
        break;
      }
      // czytamy plik z listy
      flagged_avr_files.push_back(bufor_do_listy);

    }
    return true;
}

// -- sprawdza, czy podana w argumencie nazwa pliku nie widnieje jako zaflagowana --
bool body::check_if_flagged(string avr_filename)
{
    // jesli nie ma zaladowanych flag to zawsze zwracamy false
    if (flagged_files_loaded == 0)
        return false;

    for (int i = 0; i < flagged_avr_files.size(); i++)
    {
        // albo zwykłe nazwy plików - jak wybieramy z listy
        if (avr_filename == flagged_avr_files[i])
            return true; // jesli znajdziemy na liscie nasza obserwacje - konczymy
        // albo nazwy z pełną ścieżką - jak wybieramy same pliki
        if (avr_filename == working_directory + "/" + flagged_avr_files[i])
            return true; // jesli znajdziemy na liscie nasza obserwacje - konczymy
    }


    return false;
}

/*
// -- funkcja do flagowania zaznaczonej na widmie dynamicznym epoki --
void body::flag_slot()
{
    // zapisujemy nazwe oflagowanego pliku
    string flagged_filename = dataTable->fileNamesTab[xind];

    // -- okno do upewniania sie, ze na pewno chcesz --
    QMessageBox::StandardButton upewka;
    upewka = QMessageBox::question(&window, "Are you sure?", QString::fromStdString("Do you realy want to flag " + flagged_filename + "?"), QMessageBox::Yes| QMessageBox::No);
    if (upewka == QMessageBox::No)
    {
        return;
    }


    flags_number = flags_number + 1;



    // dopisujemy jego nazwe do pliku z flagami
    ofstream flagfile;
    flagfile.open((working_directory + "/" + "flagged_obs.dat").c_str(), ios::app);
    if (!flagfile.good())
        flagfile.open((working_directory + "/" + "flagged_obs.dat").c_str());

    flagfile << flagged_filename << endl;

    cout << endl << "----> flagged " << flagged_filename << endl;

    flagfile.close();

    // oznaczamy obserwacje na widmie dynamicznym
    //QCPItemRect * rectangleflag = new QCPItemRect(&dynamic_spectrum_pl);
    QCPItemRect * tmp = new QCPItemRect(&dynamic_spectrum_pl);
    flagi.push_back(tmp);
    QBrush pen;
    QPen pennywise;
    pen.setColor(Qt::black);
    pennywise.setColor(Qt::black);
    flagi[flags_number-1]->setBrush(pen);
    flagi[flags_number-1]->setPen(pennywise);
    flagi[flags_number-1]->topLeft->setCoords(double(xind)-0.5, dataTable->velocityTable[xind][0]);
    //cout << dataTable->velocityTable[xind][0] << endl;
    //cout << dataTable->velocityTable[xind][dataTable->velocityTable[xind].size()-1] << endl;
    flagi[flags_number-1]->bottomRight->setCoords(double(xind)+0.5, dataTable->velocityTable[xind][dataTable->velocityTable[xind].size()-1]);

    flagi[flags_number-1]->setLayer("flags");
    dynamic_spectrum_pl.moveLayer(flagi[flags_number-1]->layer(), colorMap->layer(), QCustomPlot::limAbove );
    dynamic_spectrum_pl.replot();
    flagged_files_on_spectrum = 1;
    string message;
    message = "Flagged " + flagged_filename + "\nRELOAD the data to make changes";
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}
*/


void body::export_file_for_dynamic_spectrum()
{
    // -- inty z przechowywanymi granicami --
    std::vector < int > minmaxchannels = readMinMaxValuesFromChannels(*exDynspWidget->startChannelTextEd, *exDynspWidget->endChannelTextEd);
    std::vector < int > minmaxepochs = readMinMaxValuesFromEpochs(*exDynspWidget->startEpochTextEd, *exDynspWidget->endEpochTextEd);

    int min, max, min_epoch, max_epoch;
    min = minmaxchannels[0];
    max = minmaxchannels[1];
    min_epoch = minmaxepochs[0];
    max_epoch = minmaxepochs[1];
    if(min == -1 || max == -1 || min_epoch == -1 || max_epoch == -1)
        return;
    dataTable->saveDynamicSpectrumToFile(min_epoch, max_epoch, min, max, left_hand_list->IsotimeInclude->isChecked());

    // wiadomość końcowa
    string message = "";
    message = "Dynamic spectrum over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getDynSpecFileName(min_epoch, max_epoch);
    popupMessage("Message to you", message);

    // -- zamykamy sekcje dynspec --
    closeWDSection();
}

void body::open_rms_section_slot()
{
    // -- obwarowanie warunkami --
    if (!dataTable->loadedData)
    {
        popupMessage("Error!", "Please, load data first!");
        left_hand_list->RMSSection->setChecked(false);
        return;
    }
    if (dynamic_spectrum_opened)
       kill_dynamic_spectrum();
    else if (single_spectrum_opened)
        kill_single_spectrum();
    else if (rms_section_opened)
        return;
    // ----------------------------

    if(rms_sec_w->popupWindowOpened)
    {
        rms_sec_w->closePopupWindowSlot();
        rms_sec_w->popupWindowOpened = false;
    }

    // dodajemy do grida widget sekcji
    grid->addWidget(rms_sec_w, 0, 1, 9, 5);

    // dodajemy zamykający button do głównego panelu

    // zapełniamy danymi
    rms_sec_w->fillWithData();

    // ustalamy szerokość kolumn
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);

    rms_section_opened = true;
    setCheckedProperButtons();
    // -- ustalamy visibilities --
    rms_sec_w->setVisible(true);

    updateBar();
}

void body::close_rms_section_slot()
{
    // ustalamy visibilities
    rms_sec_w->setVisible(false);

    // odpinamy od grida
    grid->removeWidget(rms_sec_w);

    // ustalamy wartość boola
    rms_section_opened = false;
    setCheckedProperButtons();

    updateBar();
}


//void body::autorange_plot(QCustomPlot * plot)
//{
//    plot->rescaleAxes();
//    double max_x, min_x, max_y, min_y;
//    max_x = plot->xAxis->range().upper;
//    min_x = plot->xAxis->range().lower;
//    max_y = plot->yAxis->range().upper;
//    min_y = plot->yAxis->range().lower;
//    double diffrence_x = max_x - min_x;
//    double diffrence_y = max_y - min_y;
//    plot->xAxis->setRange(min_x - (0.05 * diffrence_x), max_x + (0.05 * diffrence_x));
//    plot->yAxis->setRange(min_y - (0.05 * diffrence_y), max_y + (0.05 * diffrence_y));
//    plot->replot();
//}


void body::darkModeSlot()
{
    dark_mode_enabled = !dark_mode_enabled;
    set_dark_mode(dark_mode_enabled);
    darthModeA->setChecked(dark_mode_enabled);
}
void body::darkModeAction()
{
    dark_mode_enabled = !dark_mode_enabled;
    set_dark_mode(dark_mode_enabled);
    left_hand_list->DarthMode->setChecked(dark_mode_enabled);
}

void body::set_dark_mode(bool mode)
{
    this->darthMode(mode);
    dynspecWidget->darthMode(mode);
    ssWidget->darthMode(mode);
    rms_sec_w->darthMode(mode);
    left_hand_list->darthMode(mode);

}

void body::darthMode(bool mode){
    if (mode){
        this->customizeApperance();
    }
    else{
        this->customizeApperanceLight();
    }
}

// -----------------------------------------------------------------------------------
void body::openIntegrateSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        popupMessage("Error!", "Please, load data first!");
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        intWidget->startingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->minRangeVelIndex+1)));
        intWidget->endingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->maxRangeVelIndex+1)));
    }

    // - ustawiamy boola, informującego o otwarciu sekcji -
    integrate_window_opened = 1;

    // - przypinamy do vboxa -
    //left_hand_list->appendWidget(intWidget);
    intWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeIntegrateSection()
{
    // - znikamy widget -
    intWidget->setVisible(false);
    // - odpinamy od vboxa -
    //left_hand_list->deleteWidgetFromList(intWidget);
    // - ustalamy boola -
    integrate_window_opened = 0;
}

// -----------------------------------------------------------------------------------
void body::openAOVSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        popupMessage("Error!", "Please, load data first!");
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        averOverVelocityWidget->startingChannelInt->setText(QString::fromStdString(to_string((dynspecWidget->yIndex+1)-1) ));
        averOverVelocityWidget->endingChannelInt->setText(QString::fromStdString(to_string((dynspecWidget->yIndex+1)+1) ));
    }

    // - ustawiamy boola, informującego o otwarciu sekcji -
    aver_over_velocity_window_opened = 1;

    // - przypinamy do vboxa -
    //left_hand_list->appendWidget(averOverVelocityWidget);

    // - pokazujemy -
    averOverVelocityWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeAOVSection()
{
    // - znikamy widget -
    averOverVelocityWidget->setVisible(false);
    // - odpinamy od vboxa -
    //left_hand_list->deleteWidgetFromList(averOverVelocityWidget);
    // - ustalamy boola -
    aver_over_velocity_window_opened = 0;
}

// -----------------------------------------------------------------------------------
void body::openAOTSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        popupMessage("Error!", "Please, load data first!");
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        averOverTimeWidget->startingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->minObsNumber+1)));
        averOverTimeWidget->endingChannelInt->setText((QString::fromStdString(to_string(dynspecWidget->maxObsNumber+1))));
    }

    // ustalamy boola
    aver_over_time_window_opened = 1;

    // - przypinamy do vboxa -
    //left_hand_list->appendWidget(averOverTimeWidget);

    // - pokazujemy -
    averOverTimeWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeAOTSection()
{
    // - znikamy -
    averOverTimeWidget->setVisible(false);

    // - odpinamy od vboxa -
    //left_hand_list->deleteWidgetFromList(averOverTimeWidget);

    // - zmieniamy boola -
    aver_over_time_window_opened = 0;
}

// -- layout do liczenia VI FI i chi2red --
void body::openSPINDSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        popupMessage("Error!", "Please, load data first!");
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        SpectralIndexWidget->startingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->minObsNumber+1)));
        SpectralIndexWidget->endingChannelInt->setText((QString::fromStdString(to_string(dynspecWidget->maxObsNumber+1))));
    }

    // - przypinamy do vboxa -
    //left_hand_list->appendWidget(SpectralIndexWidget);

    // - pokazujemy -
    SpectralIndexWidget->setVisible(true);

    // - ustawiamy boola -
    spind_window_opened = 1;
}

// -- zamyka layout do liczenia VI FI i chi2red --
void body::closeSPINDSection()
{
    // - znikamy widget -
    SpectralIndexWidget->setVisible(false);

    // - odpinamy od vboxa -
    //left_hand_list->deleteWidgetFromList(SpectralIndexWidget);

    // - usrtawiamy boola -
    spind_window_opened = 0;
}
void body::openWDSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        popupMessage("Error!", "Please, load data first!");
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();

    // dla otwarteg owidma dynczmicznego - zapełniamy text edity
    if(dynamic_spectrum_opened== 1)
    {
        exDynspWidget->startChannelTextEd->setText(QString::fromStdString(to_string(dynspecWidget->minRangeVelIndex+1)));
        exDynspWidget->endChannelTextEd->setText(QString::fromStdString(to_string(dynspecWidget->maxRangeVelIndex+1)));
        exDynspWidget->startEpochTextEd->setText(QString::fromStdString(to_string(dynspecWidget->minObsNumber+1)));
        exDynspWidget->endEpochTextEd->setText(QString::fromStdString(to_string(dynspecWidget->maxObsNumber+1)));
    }

    // przypinamy do vboxa
    //left_hand_list->appendWidget(exDynspWidget);
    // ustalamy visibility
    exDynspWidget->setVisible(true);

    // ustalamy boola
    wd_section_opened = 1;
}

void body::closeWDSection()
{
    // -- znikamy --
    exDynspWidget->setVisible(false);
    // -- odpinamy od vboxa --
    //left_hand_list->deleteWidgetFromList(exDynspWidget);
    // -- ustalamy boola --
    wd_section_opened = 0;
}

void body::openCALSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        popupMessage("Error!", "Please, load data first!");
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // ------------------------------------------------------------
    // -- setujemy default na labele --
    if (caltabs_loaded == 0)
    {
        calibrateWidget->caltabL1LoadedLabel->setText(QString::fromStdString("Not loaded!"));
        calibrateWidget->caltabR1LoadedLabel->setText(QString::fromStdString("Not loaded!"));
    }
    else
    {
        calibrateWidget->caltabL1LoadedLabel->setText(QString::fromStdString("Loaded"));
        calibrateWidget->caltabR1LoadedLabel->setText(QString::fromStdString("Loaded"));
    }
    // ------------------------------------------------------------
    // -- ustawiamy napis na przycisku, w zależności od tego czy kalibrowaliśmy czy nie --
    if (calibration_done == 0)
    {
        calibrateWidget->make->setText("Calibrate");
        calibrateWidget->make->setDown(false);
    }
    else if (calibration_done == 1)
    {
        calibrateWidget->make->setText("Uncalibrate");
        calibrateWidget->make->setDown(true);
    }
    // ------------------------------------------------------------
    // -- dodajemy do vboxa --
    //left_hand_list->appendWidget(calibrateWidget);
    // -- ustawiamy visibility --
    calibrateWidget->setVisible(true);
    // -- ustawiamy boola --
    calibration_section_opened = 1;
}

void body::closeCALSection()
{
    // -- znikamy --
    calibrateWidget->setVisible(false);
    // -- odpinamy od vboxa --
    //left_hand_list->deleteWidgetFromList(calibrateWidget);
    // -- ustawiamy boola --
    calibration_section_opened = 0;
}

// -----------------------------------------------------------------------------------
std::vector <int> body::readMinMaxValuesFromChannels(QTextEdit &minChannelTE, QTextEdit &maxChannelTE)
{
    std::vector <int> returnedValues = {-1,-1};
    unsigned int min, max;
    QString mins = minChannelTE.toPlainText();
    QString maxs = maxChannelTE.toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        popupMessage("Error!", "Fill text editors with text!");
        return returnedValues;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString());
        max = stoi(maxs.toStdString());
    }
    catch(...)
    {
        popupMessage("Error!", "Error while converting values");
        return returnedValues;
    }

    // -- obsługujemy kilka przypadków błędnego wpisania paramatrów --
    // początkowy channel większy od końcowego
    if (min > max)
    {
        popupMessage("Error!", "Min channel > max channel!");
        return returnedValues;
    }
    // początkowy channel mniejszy od 1
    if (min < 1)
    {
        popupMessage("Error!", "Min channel < 1!");
        return returnedValues;
    }
    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > dataTable->spectraTableI[0].size())
        max = dataTable->spectraTableI[0].size();

    // ustalamy wartości zwracanego wektora
    returnedValues[0] = min;
    returnedValues[1] = max;

    return returnedValues;
}

// -----------------------------------------------------------------------------------
std::vector <int> body::readMinMaxValuesFromEpochs(QTextEdit &minEpochlTE, QTextEdit &maxEpochlTE)
{
    std::vector <int> returnedValues = {-1,-1};
    unsigned int min, max;
    QString mins = minEpochlTE.toPlainText();
    QString maxs = maxEpochlTE.toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        popupMessage("Error!", "Fill text editors with text!");
        return returnedValues;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString());
        max = stoi(maxs.toStdString());
    }
    catch(...)
    {
        popupMessage("Error!", "Error while converting values");
        return returnedValues;
    }

    // -- obsługujemy kilka przypadków błędnego wpisania paramatrów --
    // początkowy channel większy od końcowego
    if (min > max)
    {
        popupMessage("Error!", "Min channel > max channel!");
        return returnedValues;
    }
    // początkowy channel mniejszy od 1
    if (min < 1)
    {
        popupMessage("Error!", "Min channel < 1!");
        return returnedValues;
    }
    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > dataTable->spectraTableI.size())
        max = dataTable->spectraTableI.size();

    // ustalamy wartości zwracanego wektora
    returnedValues[0] = min;
    returnedValues[1] = max;

    return returnedValues;
}

// -----------------------------------------------------------------------------------
void body::connectSectionsToSlots()
{
    // integrate
    QObject::connect(intWidget->make, SIGNAL(clicked()), this, SLOT(integrate_time_series()));
    QObject::connect(intWidget->cancel, SIGNAL(clicked()), this, SLOT(closeIntegrateSection()));
    // AOV
    QObject::connect(averOverVelocityWidget->make, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity()));
    QObject::connect(averOverVelocityWidget->cancel, SIGNAL(clicked()), this, SLOT(closeAOVSection()));
    // AOT
    QObject::connect(averOverTimeWidget->make, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time()));
    QObject::connect(averOverTimeWidget->cancel, SIGNAL(clicked()), this, SLOT(closeAOTSection()));
    // SPIND
    QObject::connect(SpectralIndexWidget->make, SIGNAL(clicked()), this, SLOT(calculate_spectral_index()));
    QObject::connect(SpectralIndexWidget->cancel, SIGNAL(clicked()), this, SLOT(closeSPINDSection()));
    // WD
    QObject::connect(exDynspWidget->make, SIGNAL(clicked()), this, SLOT(export_file_for_dynamic_spectrum()));
    QObject::connect(exDynspWidget->cancel, SIGNAL(clicked()), this, SLOT(closeWDSection()));
    // CAL
    QObject::connect(calibrateWidget->make, SIGNAL(clicked()), this, SLOT(calibrate_button()));
    QObject::connect(calibrateWidget->cancel, SIGNAL(clicked()), this, SLOT(closeCALSection()));
    QObject::connect(calibrateWidget->loadCaltabL1, SIGNAL(clicked()), this, SLOT(load_l1_caltab_button()));
    QObject::connect(calibrateWidget->loadCaltabR1, SIGNAL(clicked()), this, SLOT(load_r1_caltab_button()));
}

// -----------------------------------------------------------------------------------
void body::closeOtherSections()
{
    if(wd_section_opened)
       closeWDSection();
    if (calibration_section_opened)
       closeCALSection();
    if (integrate_window_opened)
       closeIntegrateSection();
    if (aver_over_time_window_opened)
        closeAOTSection();
    if (spind_window_opened)
        closeSPINDSection();
    if (aver_over_velocity_window_opened)
        closeAOVSection();
}
// -- do przycisku --
void body::load_l1_caltab_button()
{
    string nazwa_pliku; // string z nazwa pliku
    QString fileName;// qstring z nazwa pliku
    // otwieramy file selectora
    fileName = QFileDialog::getOpenFileName(&window,tr("Select LHC caltab"), tr(""), tr("All Files (*)")); // qfile dialog
    // eksportujemy nazwę pliku do zmiennej string
    nazwa_pliku = fileName.toStdString();
    // ladujemy caltab
    dataTable->loadLHCCaltab(nazwa_pliku);
}

// -- do przycisku --
void body::load_r1_caltab_button()
{
    string nazwa_pliku; // string z nazwa pliku
    QString fileName;// qstring z nazwa pliku
    // otwieramy file selectora
    fileName = QFileDialog::getOpenFileName(&window,tr("Select RHC caltab"), tr(""), tr("All Files (*)")); // qfile dialog
    // eksportujemy nazwę pliku do zmiennej string
    nazwa_pliku = fileName.toStdString();
    // ladujemy caltab
    dataTable->loadRHCCaltab(nazwa_pliku);
}

void body::calibrate_button()
{
    dataTable->calibrateAll(true);
}

double body::readNumberFromQTextEdit(QTextEdit *box)
{
    /*
     * Prosta metoda, czytająca numer z QTextEdit i konwertująca go na double
     * Dodatkowo posiada kilka zabezpieczeń na wypadek nieprawidłowego wypełnienia
     */
    double returnedValue;
    QString bufor = box->toPlainText();
    if (bufor.toStdString() == "")
    {
        popupMessage("Error!", "Fill text editors with text!");
        return 0.0;
    }
    try
    {
        returnedValue = bufor.toDouble();
    }
    catch(...)
    {
        popupMessage("Error!", "Error while converting values");
        return 0.0;
    }
    return returnedValue;
}

void body::popupMessage(std::string message_type, std::string message_text)
{
    CustomMessageBox ee(
                QString::fromStdString(message_type),
                QString::fromStdString(message_text),
                nullptr,
                this->dark_mode_enabled);
    ee.exec();
}
