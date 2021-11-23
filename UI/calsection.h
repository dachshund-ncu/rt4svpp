#ifndef CALSECTION_H
#define CALSECTION_H

#include <QtGui>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class calsection : public QWidget
{
public:
    // konstruktor
    calsection(QObject * parent = 0, const char * name = 0);

    // - button do glownego vboxa -
    // buttony do widgetu
    QPushButton * loadCaltabL1 = new QPushButton(this);
    QPushButton * loadCaltabR1 = new QPushButton(this);
    QPushButton * make = new QPushButton(this);
    QPushButton * cancel = new QPushButton(this);
    // layouty
    QVBoxLayout * layout = new QVBoxLayout(this);
    QHBoxLayout * l1LoadLayout = new QHBoxLayout();
    QHBoxLayout * r1LoadLayout = new QHBoxLayout();
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    // labele
    QLabel * widgetLabel = new QLabel(this);
    QLabel * caltabL1LoadedLabel = new QLabel(this); // tekst pokazujacy czy zaladowano caltab
    QLabel * caltabR1LoadedLabel = new QLabel(this); // tekst pokazujacy czy zaladowano caltab
private:
    void setUpWidget(const char * name = 0);
};

#endif // CALSECTION_H
