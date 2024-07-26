#ifndef RMS_SELECTOR_H
#define RMS_SELECTOR_H

/*
 * Very simple class, that allows us to set up custom ranges for calculating observation RMS
 */

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <vector>
#include <UI/custom_ui_elements.h>

class rms_selector : public customPopupWidget
{
    Q_OBJECT
public:
    rms_selector();
    // layout
    QGridLayout * grid = new QGridLayout(this);
    // buttons
    QPushButton * perform = new QPushButton(this);
    QPushButton * cancel = new QPushButton(this);
    // spin boxes
    QSpinBox * rmsRange1Start = new QSpinBox(this);
    QSpinBox * rmsRange1Stop = new QSpinBox(this);
    QSpinBox * rmsRange2Start = new QSpinBox(this);
    QSpinBox * rmsRange2Stop = new QSpinBox(this);
    // labels
    QLabel * rmsRange1 = new QLabel(this);
    QLabel * rmsRange2 = new QLabel(this);
    QLabel * arrow1 = new QLabel(this);
    QLabel * arrow2 = new QLabel(this);
    // methods
    void setUpWidgets();
    void setMaximumValues(int value);
public slots:
    void cancelSlot();
    void show();
    std::vector < int > getValuesFromBoxes();
    void setValuesOfBoxes(std::vector < unsigned long int > values);
};

#endif // RMS_SELECTOR_H
