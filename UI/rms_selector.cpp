#include "rms_selector.h"

rms_selector::rms_selector()
{
    this->setWindowTitle("Choose new RMS Channels");
    this->setVisible(false);
    setUpWidgets();
    this->setMaximumSize(300,300);
    this->setGeometry(300, 300, 300, 300);


}

void rms_selector::setUpWidgets()
{
    perform->setText("Set new RMS chans");
    cancel->setText("Cancel");

    rmsRange1->setText("range 1:");
    rmsRange2->setText("range 2:");
    arrow1->setText("->");
    arrow2->setText("->");

    grid->addWidget(rmsRange1, 0, 0);
    grid->addWidget(rmsRange1Start, 0, 1);
    grid->addWidget(arrow1, 0, 2);
    grid->addWidget(rmsRange1Stop, 0, 3);

    grid->addWidget(rmsRange2, 1, 0);
    grid->addWidget(rmsRange2Start, 1, 1);
    grid->addWidget(arrow2, 1, 2);
    grid->addWidget(rmsRange2Stop, 1, 3);

    grid->addWidget(cancel, 2, 0, 1, 2);
    grid->addWidget(perform, 2, 2, 1, 2);

    rmsRange1Start->setMaximum(9999999);
    rmsRange1Start->setMinimum(1);
    rmsRange1Stop->setMaximum(9999999);
    rmsRange1Stop->setMinimum(1);

    rmsRange2Start->setMaximum(9999999);
    rmsRange2Start->setMinimum(1);
    rmsRange2Stop->setMaximum(9999999);
    rmsRange2Stop->setMinimum(1);

    rmsRange1Start->setMaximumSize(100,30);
    rmsRange1Stop->setMaximumSize(100,30);
    rmsRange2Start->setMaximumSize(100,30);
    rmsRange2Stop->setMaximumSize(100,30);

    rmsRange1Start->setMinimumSize(0,0);
    rmsRange1Stop->setMinimumSize(0,0);
    rmsRange2Start->setMinimumSize(0,0);
    rmsRange2Stop->setMinimumSize(0,0);

    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 6);
    grid->setColumnStretch(2, 1);
    grid->setColumnStretch(3, 6);
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelSlot()));
}

void rms_selector::cancelSlot()
{
    this->setVisible(false);
}

void rms_selector::show()
{
    this->setVisible(true);
}

std::vector < int > rms_selector::getValuesFromBoxes()
{
    std::vector < int > returnedValues(4);
    returnedValues[0] = rmsRange1Start->cleanText().toInt();
    returnedValues[1] = rmsRange1Stop->cleanText().toInt();
    returnedValues[2] = rmsRange2Start->cleanText().toInt();
    returnedValues[3] = rmsRange2Stop->cleanText().toInt();
    return returnedValues;
}

void rms_selector::setValuesOfBoxes(std::vector<unsigned long int> values)
{
    rmsRange1Start->setValue((int)values[0]);
    rmsRange1Stop->setValue((int)values[1]);
    rmsRange2Start->setValue((int)values[2]);
    rmsRange2Stop->setValue((int)values[3]);
}

void rms_selector::setMaximumValues(int value)
{
    rmsRange1Start->setMaximum(value);
    rmsRange1Stop->setMaximum(value);
    rmsRange2Start->setMaximum(value);
    rmsRange2Stop->setMaximum(value);
}
