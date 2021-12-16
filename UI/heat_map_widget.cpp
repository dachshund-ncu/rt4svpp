#include "heat_map_widget.h"

heat_map_widget::heat_map_widget()
{
    setButtonsProperties();
    processTextEdits();
    placeWidgets();
    managePlottables();
    setLabelTexts();
    this->setGeometry(200,200, 1366, 720);
    this->setVisible(true);
}

void heat_map_widget::setButtonsProperties()
{
    // -- rozmiary --
    yDownBorder->setMaximumSize(10000,30);
    yUpBorder->setMaximumSize(10000,30);
    xDownBorder->setMaximumSize(10000,30);
    xUpBorder->setMaximumSize(10000,30);
    Ibut->setMaximumSize(10000,30);
    Vbut->setMaximumSize(10000,30);
    LHCbut->setMaximumSize(10000,30);
    RHCbut->setMaximumSize(10000,30);
    flag->setMaximumSize(10000,10000);
    makeLcsButton->setMaximumSize(10000,10000);
    recreateIButton->setMaximumSize(10000,10000);
    rotate->setMaximumSize(10000,10000);
    rotate_minus->setMaximumSize(10000,10000);
    saveEdition->setMaximumSize(10000,10000);

    yDownBorder->setMinimumSize(0,0);
    yUpBorder->setMinimumSize(0,0);
    xDownBorder->setMinimumSize(0,0);
    xUpBorder->setMinimumSize(0,0);
    Ibut->setMinimumSize(0,0);
    Vbut->setMinimumSize(0,0);
    LHCbut->setMinimumSize(0,0);
    RHCbut->setMinimumSize(0,0);
    flag->setMinimumSize(0,0);
    makeLcsButton->setMinimumSize(0,0);
    recreateIButton->setMinimumSize(0,0);
    rotate->setMinimumSize(0,0);
    rotate_minus->setMinimumSize(0,0);
    saveEdition->setMinimumSize(0,0);
    // -------------------------
    // -- teksty --
    yDownBorder->setText("Down");
    yUpBorder->setText("Up");
    xDownBorder->setText("|<-");
    xUpBorder->setText("->|");
    Ibut->setText("I");
    Vbut->setText("V");
    LHCbut->setText("LHC");
    RHCbut->setText("RHC");
    flag->setText("Flag");
    makeLcsButton->setText("Make LCS");
    recreateIButton->setText("Recal IV");
    rotate->setText("Rotate+");
    rotate_minus->setText("Rotate-");
    saveEdition->setText("Save");
    // -------------------------
}

void heat_map_widget::processTextEdits()
{
    numberOfRotatedChannelsTexted->setMaximumSize(60,30);
}

void heat_map_widget::placeWidgets()
{
    // -- rozmieszczamy przyciski --
    topDynSpecButtons->addWidget(Ibut);
    topDynSpecButtons->addWidget(Vbut);
    topDynSpecButtons->addWidget(LHCbut);
    topDynSpecButtons->addWidget(RHCbut);
    // --
    topDynSpecButtons->addWidget(yDownBorder);
    topDynSpecButtons->addWidget(yUpBorder);
    topDynSpecButtons->addWidget(xDownBorder);
    topDynSpecButtons->addWidget(xUpBorder);
    // --
    bottomDynSpecButtons->addWidget(numberOfRotatedChannelsTexted);
    bottomDynSpecButtons->addWidget(recreateIButton);
    bottomDynSpecButtons->addWidget(flag);
    bottomDynSpecButtons->addWidget(rotate);
    bottomDynSpecButtons->addWidget(saveEdition);
    bottomDynSpecButtons->addWidget(rotate_minus);
    bottomDynSpecButtons->addWidget(makeLcsButton);
    checkboxesOnDynspec->addWidget(setLogScale);
    checkboxesOnDynspec->addWidget(rotateAllPols);
    bottomDynSpecButtons->addItem(checkboxesOnDynspec);
    // --
    topDynSpecButtons->setSpacing(1);
    bottomDynSpecButtons->setSpacing(1);
    // --
    onDynSpecButtons->addLayout(bottomDynSpecButtons);
    onDynSpecButtons->addLayout(topDynSpecButtons);
    // -- dodajemy do gridu --
    // -- umierszczamy ploty na gridzie --
    grid->addWidget(heatMapPlot, 1,0,7,6);
    grid->addWidget(spectrumPlot, 0,6,4,4);
    grid->addWidget(lcsPlot, 4,6,4,4);
    grid->addWidget(colorbarWidget, 0, 0, 1, 6);
    // -- przyciski --
    grid->addLayout(onDynSpecButtons,8,0,1,6);
    grid->addWidget(leftLabel, 8,6);
    grid->addWidget(rightLabel, 8,8);
    // -- ustalamy column stretch --
    grid->setColumnStretch(0,1);
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,1);
    grid->setColumnStretch(3,1);
    grid->setColumnStretch(4,1);
    grid->setColumnStretch(5,1);
    grid->setColumnStretch(6,1);
    grid->setColumnStretch(7,1);
    grid->setColumnStretch(8,1);
    grid->setColumnStretch(9,1);
}

void heat_map_widget::managePlottables()
{
    // --- colorbar --
    // -- widget --
    colorbarWidget->clearPlottables();
    colorbarWidget->plotLayout()->clear();
    colorbarWidget->plotLayout()->addElement(0,0,colorbar);
    colorbarWidget->setMaximumSize(9999999,70);
    colorbarWidget->resize(1,1);
    // -- bar --
    colorbar->setType(QCPAxis::atTop);
    colorbar->setDataRange(heatMap->dataRange());
    colorbar->setMinimumMargins(QMargins(6, 0, 6, 0));
    // ---------------
    QCPMarginGroup * grupa_marginesowa = new QCPMarginGroup(heatMapPlot);
    heatMapPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, grupa_marginesowa);
    colorbar->setMarginGroup(QCP::msLeft|QCP::msRight, grupa_marginesowa);
    colorbarWidget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
}

void heat_map_widget::setLabelTexts()
{
    QFont f( "Arial", 10, QFont::Bold);
    leftLabel->setFont(f);
    rightLabel->setFont(f);
    leftLabel->setText("MJD = \nChannel = \nVel = ");
    rightLabel->setText("Date: \nValue: \nNumber: ");
}
