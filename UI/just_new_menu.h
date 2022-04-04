#ifndef JUST_NEW_MENU_H
#define JUST_NEW_MENU_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QObject>
#include <QAction>

class just_new_menu : public QMenuBar
{
public:
    just_new_menu();
    // menus
    QMenu * filesM = new QMenu(tr("&File"));
    QMenu * advancedM = new QMenu(tr("&Advanced"));
    QMenu * dynSpecM = new QMenu(tr("&Dynamic spectrum"));
    QMenu * singSpecM = new QMenu(tr("&Single spectrum"));
    QMenu * rmsSecM = new QMenu(tr("&RMS section"));
    // actions
    // FILE
    QAction * loadAVRFile = new QAction(filesM);
    QAction * loadFITSFile = new QAction(filesM);
    QAction * reload = new QAction(filesM);
    QAction * quit = new QAction(filesM);
    // ADVANCED
    QAction * openDynamicSpectrumA = new QAction(advancedM);
    QAction * openSingleSpectrumA = new QAction(advancedM);
    QAction * openRmsSectionA = new QAction(advancedM);
    QAction * openIntegrationA = new QAction(advancedM);
    QAction * openAverOverVelA = new QAction(advancedM);
    QAction * openAverOverTimeA = new QAction(advancedM);
    QAction * openSpindicateA = new QAction(advancedM);
    QAction * openExportDynSpectrumA = new QAction(advancedM);
    QAction * openCalibrateSectionA = new QAction(advancedM);
    QAction * darthModeA = new QAction(advancedM);
    QAction * isoTimeA = new QAction(advancedM);
    // DYNAMIC SPECTRUM
    QAction * recalIVA = new QAction(dynSpecM);
    QAction * flagA = new QAction(dynSpecM);
    QAction * rotatePlus = new QAction(dynSpecM);
    QAction * rotateMinus = new QAction(dynSpecM);
    QAction * save = new QAction(dynSpecM);
    QAction * makeLCS = new QAction(dynSpecM);
    QAction * logScale = new QAction(dynSpecM);
    QAction * rotate_IVLR = new QAction(dynSpecM);


    // bools
    bool dynSpecOpened = false;
    bool singSpecOpened = false;
    bool rmsSpecOpened = false;
private:
    void createMenuEntries();
    void updateBar();
    void makeActions();
public:
    void addDynspec();
    void addSingspec();
    void addRmssec();
    void hideAll();
};

#endif // JUST_NEW_MENU_H
