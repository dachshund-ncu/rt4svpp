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

class vbox_mainw : public QWidget
{
public:
    // konstruktor
    vbox_mainw(QObject *parent = 0, const char * name = 0);

    // dzieci - buttony
    // -- load --
    QPushButton * LoadAVRFiles = new QPushButton(this);
    QPushButton * LoadFITSFiles = new QPushButton(this);
    QPushButton * Reload = new QPushButton(this);
    // -- główne sekcje --
    QPushButton * DynamicSpectrum = new QPushButton(this);
    QPushButton * SingleSpectrum = new QPushButton(this);
    QPushButton * RMSSection = new QPushButton(this);
    QPushButton * GaussFitting = new QPushButton(this);
    // -- pomniejsze sekcje --
    QPushButton * Integrate = new QPushButton(this);
    QPushButton * AverOverVelocity = new QPushButton(this);
    QPushButton * AverOverTime = new QPushButton(this);
    QPushButton * SpectralIndex = new QPushButton(this);
    QPushButton * ExportDynamicSpectrum = new QPushButton(this);
    // -- dół --
    QPushButton * Calibrate =  new QPushButton(this);
    QPushButton * Quit = new QPushButton(this);

    // layouty
    QGridLayout * VboxGrid = new QGridLayout(this);

    // checkboxy
    QCheckBox * DarthMode = new QCheckBox("Darth Mode", this);
    QCheckBox * IsotimeInclude = new QCheckBox("Include time in isoformat", this);

    // labele
    QLabel * LoadingSectionlabel = new QLabel(this);
    QLabel * VisualSectionLabel = new QLabel(this);
    QLabel * ExportAndAnalysisLabel = new QLabel(this);
    QLabel * OthersLabel = new QLabel(this);

    bool setctionOpened = 0;

public:
    void appendWidget(QWidget * widget);
    void deleteWidgetFromList(QWidget * widget);
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
};

#endif // VBOX_MAIN_H
