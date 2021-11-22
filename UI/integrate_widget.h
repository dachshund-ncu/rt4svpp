#ifndef INTEGRATE_WIDGET_H
#define INTEGRATE_WIDGET_H
/*
 * Taka sobei klasa do wielokrotnego użytku - będzie przechowywać prosty interfejs z text editami do wpisania
 * channelów
 */
#include "vbox_main.h"
#include <iostream>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <vector>
#include <string>
#include <QtGui>
#include <data/spectral_container.h>

class integrate_widget : public QWidget
{
public:
    // konstruktor
    integrate_widget(QObject * parent = 0, const char * name = 0);

    // -- elementy interfejsu --
    // buttony
    QPushButton * make = new QPushButton(this);
    QPushButton * cancel = new QPushButton(this);
    // layouty
    QVBoxLayout * Layout = new QVBoxLayout(this);
    QHBoxLayout * startChannels = new QHBoxLayout();
    QHBoxLayout * endChannels = new QHBoxLayout();
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    // text edity
    QTextEdit * startingChannelInt = new QTextEdit(this);
    QTextEdit * endingChannelInt = new QTextEdit(this);
    // labele
    QLabel * sectionLabel = new QLabel(this);
    QLabel * startChannelLabel = new QLabel(this);
    QLabel * endChannelLabel = new QLabel(this);
// prywatne metody
private:
    void setUpWidget(const char * name = 0);
public:
    std::vector < int > readValuesFromTextEd();
public slots:
    void addToParentWidget();
    void removeFromParentWidget();
    void makeIntegration();

};

#endif // INTEGRATE_WIDGET_H
