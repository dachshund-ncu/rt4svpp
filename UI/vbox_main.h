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

    // -- główne sekcje --
    QAction * DynamicSpectrum = new QAction(this);
    QAction * SingleSpectrum = new QAction(this);
    QAction * RMSSection = new QAction(this);
    // -- pomniejsze sekcje --
    spacer * spacer1 = new spacer();
    // -- dół --
    QAction * Quit = new QAction(this);

    // checkboxy
    QCheckBox * DarthMode = new QCheckBox("Darth Mode", this);
    QCheckBox * IsotimeInclude = new QCheckBox("Iso time", this);

    bool setctionOpened = 0;

public:
    void darthMode(bool enabled = false);

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
