#include "varcoefscalcwidget.h"

varCoefsCalcWidget::varCoefsCalcWidget(QObject * parent, const char * name, const char * window_title)
{
    this->setWindowTitle(window_title);
    setUpWidget(name);
}
void varCoefsCalcWidget::setUpWidget(const char * name)
{
    this->setVisible(false);
    // - size policy -
    this->setMaximumSize(200,200);
    // - rozmiary text editów -
    startingChannelInt->setMaximumSize(100,30);
    endingChannelInt->setMaximumSize(100,30);
    absoluteErrorBox->setMaximumSize(100,30);
    startingChannelInt->setMinimumSize(0,0);
    endingChannelInt->setMinimumSize(0,0);
    absoluteErrorBox->setMinimumSize(0,0);
    // - rozmiary przycisków -
    make->setMinimumSize(0,0);
    cancel->setMinimumSize(0,0);
    // - teksty -
    startChannelLabel->setText("Start");
    endChannelLabel->setText("End");
    make->setText("Go");
    cancel->setText("Cancel");
    sectionLabel->setText(name);
    absoluteCalibrationLabel->setText("Cal. error: ");
    absoluteErrorBox->setText("0.1");
    // --------------------------------------
    // start
    startChannels->addWidget(startChannelLabel,Qt::AlignHCenter);
    startChannels->addWidget(startingChannelInt,Qt::AlignHCenter);
    // end
    endChannels->addWidget(endChannelLabel,Qt::AlignHCenter);
    endChannels->addWidget(endingChannelInt,Qt::AlignHCenter);
    // abs. cal
    absCalLayout->addWidget(absoluteCalibrationLabel, Qt::AlignHCenter);
    absCalLayout->addWidget(absoluteErrorBox, Qt::AlignHCenter);
    // przyciski
    buttonsLayout->addWidget(cancel, Qt::AlignHCenter);
    buttonsLayout->addWidget(make, Qt::AlignHCenter);
    // do integrate
    Layout->addWidget(sectionLabel, Qt::AlignHCenter);
    Layout->addLayout(startChannels, Qt::AlignHCenter);
    Layout->addLayout(endChannels, Qt::AlignHCenter);
    Layout->addLayout(absCalLayout, Qt::AlignHCenter);
    Layout->addLayout(buttonsLayout, Qt::AlignHCenter);
}
