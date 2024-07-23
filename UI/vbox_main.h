#ifndef VBOX_MAIN_H
#define VBOX_MAIN_H
/*
 * Klasa, odpowiadająca za pionową kolumnę interfejsu po lewej stronie - ma w sobie przyciski,
 * dwa checkboxy etc.
 * layout będzie oparty na gridzie, nie jak poprzednio na QVboxLayout
 */
#include "integrate_widget.h"
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QtGui>
#include <QSize>
#include "UI/custom_ui_elements.h"
class vbox_mainw : public QToolBar
{
public:
    // konstruktor
    vbox_mainw(QObject *parent = 0, const char * name = 0);

    // dzieci - buttony
    // -- load --
//    QAction * LoadAVRFiles = new QAction(this);
//    QAction * LoadFITSFiles = new QAction(this);
//    QAction * Reload = new QAction(this);
    // -- główne sekcje --
    QAction * DynamicSpectrum = new QAction(this);
    QAction * SingleSpectrum = new QAction(this);
    QAction * RMSSection = new QAction(this);
    // -- pomniejsze sekcje --
    spacer * spacer1 = new spacer();
//    spacer * spacer2 = new spacer();
//    QAction * Integrate = new QAction(this);
//    QAction * AverOverVelocity = new QAction(this);
//    QAction * AverOverTime = new QAction(this);
//    QAction * SpectralIndex = new QAction(this);
//    QAction * ExportDynamicSpectrum = new QAction(this);
    // -- dół --
    QAction * Quit = new QAction(this);

    // layouty
    //QGridLayout * VboxGrid = new QGridLayout(this);
    //QGridLayout * persistentGrid = new QGridLayout(persistentButtons);

    // checkboxy
    QCheckBox * DarthMode = new QCheckBox("Darth Mode", this);
    QCheckBox * IsotimeInclude = new QCheckBox("Iso time", this);

    // labele
    //QLabel * LoadingSectionlabel = new QLabel(this);
    //QLabel * VisualSectionLabel = new QLabel(this);
    //QLabel * ExportAndAnalysisLabel = new QLabel(this);
    //QLabel * OthersLabel = new QLabel(this);

    bool setctionOpened = 0;

public:
    //void appendWidget(QWidget * widget);
    //void deleteWidgetFromList(QWidget * widget);
    void darthMode(bool enabled = false);
public slots:
    // -- integrate --
    //void openInt();
    //void closeInt();
    // -- averOverVel --
    // i tak dalej...
private:
    void makeProperSizeForButtons();
    void makeProperLabelsForButtons();
    void setupLabels();
    void addEverythingToWidget();
    void connectToSlots(QObject * parent);
    void closeAnySection();
    void setLightMode();
    void setDarkMode();
};

#endif // VBOX_MAIN_H
