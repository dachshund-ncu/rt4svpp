#include "export_dynamic_spectrum_widget.h"

export_dynamic_spectrum_widget::export_dynamic_spectrum_widget(QObject * parent, const char * name)
{
    setUpWidgets(name);
}

void export_dynamic_spectrum_widget::setUpWidgets(const char * name)
{
    // - size policy -
    this->setMaximumSize(100000,200);

    // - przy starcie nie chcemy go widziec -
    this->setVisible(false);

    // - rozmiaty text editow -
    startChannelTextEd->setMaximumSize(100,30);
    endChannelTextEd->setMaximumSize(100,30);
    startEpochTextEd->setMaximumSize(100,30);
    endEpochTextEd->setMaximumSize(100,30);

    startChannelTextEd->setMinimumSize(0,0);
    endChannelTextEd->setMinimumSize(0,0);
    startEpochTextEd->setMinimumSize(0,0);
    endEpochTextEd->setMinimumSize(0,0);

    // - rozmiaty przyciskow -
    cancel->setMaximumSize(100000,100000);
    make->setMaximumSize(100000,100000);
    cancel->setMinimumSize(0,0);
    make->setMinimumSize(0,0);

    // - teksty na przyciskach i labelach -
    widgetLabel->setText(name);
    startChannelLabel->setText("Start Channel");
    endChannelLabel->setText("End Channel");
    make->setText("Export dynspec.");
    cancel->setText("Cancel");
    startEpochLabel->setText("Start epoch");
    endEpochLabel->setText("End epoch");

    // - dodajemy do layoutow -
    // start chan
    startChannelLayout->addWidget(startChannelLabel,Qt::AlignHCenter);
    startChannelLayout->addWidget(startChannelTextEd,Qt::AlignHCenter);
    // end chan
    endChannelLayout->addWidget(endChannelLabel,Qt::AlignHCenter);
    endChannelLayout->addWidget(endChannelTextEd,Qt::AlignHCenter);
    // start epoch
    startEpochLayout->addWidget(startEpochLabel, Qt::AlignHCenter);
    startEpochLayout->addWidget(startEpochTextEd, Qt::AlignHCenter);
    // end epoch
    endEpochlayout->addWidget(endEpochLabel, Qt::AlignHCenter);
    endEpochlayout->addWidget(endEpochTextEd, Qt::AlignHCenter);
    // przyciski
    buttonsLayout->addWidget(cancel,Qt::AlignHCenter);
    buttonsLayout->addWidget(make,Qt::AlignHCenter);
    // do integrate
    layout->addWidget(widgetLabel, Qt::AlignHCenter);
    layout->addLayout(startChannelLayout,Qt::AlignHCenter);
    layout->addLayout(endChannelLayout,Qt::AlignHCenter);
    layout->addLayout(startEpochLayout,Qt::AlignHCenter);
    layout->addLayout(endEpochlayout,Qt::AlignHCenter);
    layout->addLayout(buttonsLayout,Qt::AlignHCenter);
}
