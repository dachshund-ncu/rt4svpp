#include "calsection.h"

calsection::calsection(QObject * parent, const char * name)
{
    setUpWidget(name);
}

void calsection::setUpWidget(const char * name)
{
    // - size policy -
    this->setMaximumSize(100000,150);

    // - visibility -
    this->setVisible(false);

    // - setujemy tekst -
    cancel->setText("Cancel");
    make->setText("Calibrate");
    loadCaltabL1->setText("LHC");
    loadCaltabR1->setText("RHC");
    widgetLabel->setText(name);
    // - rozmiarówka -
    loadCaltabL1 -> setMinimumSize(100000,100000);
    loadCaltabR1 -> setMinimumSize(100000,100000);
    make -> setMinimumSize(100000,100000);
    cancel -> setMinimumSize(100000,100000);

    loadCaltabL1 -> setMinimumSize(0,0);
    loadCaltabR1 -> setMinimumSize(0,0);
    make -> setMinimumSize(0,0);
    cancel -> setMinimumSize(0,0);

    // - konstrukcja widgetu -
    l1LoadLayout->addWidget(loadCaltabL1,Qt::AlignHCenter);
    l1LoadLayout->addWidget(caltabL1LoadedLabel,Qt::AlignHCenter);
    r1LoadLayout->addWidget(loadCaltabR1,Qt::AlignHCenter);
    r1LoadLayout->addWidget(caltabR1LoadedLabel,Qt::AlignHCenter);
    buttonsLayout->addWidget(make,Qt::AlignHCenter);
    buttonsLayout->addWidget(cancel,Qt::AlignHCenter);
    layout->addWidget(widgetLabel, Qt::AlignHCenter);
    layout->addLayout(l1LoadLayout,Qt::AlignHCenter);
    layout->addLayout(r1LoadLayout,Qt::AlignHCenter);
    layout->addLayout(buttonsLayout,Qt::AlignHCenter);
}
