#include "just_new_menu.h"

just_new_menu::just_new_menu()
{
    createMenuEntries();
    makeActions();
    updateBar();
}

void just_new_menu::createMenuEntries()
{
    this->addMenu(filesM);
    this->addMenu(advancedM);
    this->addMenu(dynSpecM);
    this->addMenu(singSpecM);
    this->addMenu(rmsSecM);
}

void just_new_menu::makeActions()
{
    // -----------------------
    loadAVRFile->setText("Load AVR file");
    loadFITSFile->setText("Load FITS file");
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
    openSpindicateA->setText("Spectral index");
    openExportDynSpectrumA->setText("Export dynamic spectrum");
    openCalibrateSectionA->setText("Open calibrate section");
    darthModeA->setText("Darth Mode");
    isoTimeA->setText("Include isotime");
    darthModeA->setCheckable(true);
    isoTimeA->setCheckable(true);
    darthModeA->setChecked(true);
    // --
    advancedM->addAction(openDynamicSpectrumA);
    advancedM->addAction(openSingleSpectrumA);
    advancedM->addAction(openRmsSectionA);
    advancedM->addSeparator();
    advancedM->addAction(openIntegrationA);
    advancedM->addAction(openAverOverVelA);
    advancedM->addAction(openAverOverTimeA);
    advancedM->addAction(openSpindicateA);
    advancedM->addAction(openExportDynSpectrumA);
    advancedM->addAction(openCalibrateSectionA);
    advancedM->addSeparator();
    advancedM->addAction(darthModeA);
    advancedM->addAction(isoTimeA);
    // -----------------------
    rotatePlus->setText("Rotate +");
    rotateMinus->setText("Rotate -");
    save->setText("Save edited spectra");
    recalIVA->setText("Recalibrate I and V from R/LHC");
    flagA->setText("Flag");
    makeLCS->setText("Export light curve");
    logScale->setText("Set log color scale");
    rotate_IVLR->setText("Rotate L/RHC independently");
    logScale->setCheckable(true);
    rotate_IVLR->setCheckable(true);
    logScale->setChecked(false);
    rotate_IVLR->setChecked(true);
    // --
    dynSpecM->addAction(flagA);
    dynSpecM->addAction(makeLCS);
    dynSpecM->addSeparator();
    dynSpecM->addAction(rotatePlus);
    dynSpecM->addAction(rotateMinus);
    dynSpecM->addAction(save);
    dynSpecM->addAction(recalIVA);
    dynSpecM->addAction(rotate_IVLR);
    dynSpecM->addSeparator();
    dynSpecM->addAction(logScale);

}

void just_new_menu::updateBar()
{
    //dynSpecM->setVisible(dynSpecOpened);
    dynSpecM->menuAction()->setVisible(dynSpecOpened);
    //singSpecM->setVisible(singSpecOpened);
    singSpecM->menuAction()->setVisible(singSpecOpened);
    //rmsSecM->setVisible(rmsSpecOpened);
    rmsSecM->menuAction()->setVisible(rmsSpecOpened);
}

void just_new_menu::addDynspec()
{
    dynSpecOpened = true;
    singSpecOpened = false;
    rmsSpecOpened = false;
    updateBar();
}

void just_new_menu::addSingspec()
{
    dynSpecOpened = false;
    singSpecOpened = true;
    rmsSpecOpened = false;
    updateBar();
}

void just_new_menu::addRmssec()
{
    dynSpecOpened = false;
    singSpecOpened = false;
    rmsSpecOpened = true;
    updateBar();
}

void just_new_menu::hideAll()
{
    dynSpecOpened = false;
    singSpecOpened = false;
    rmsSpecOpened = false;
    updateBar();
}
