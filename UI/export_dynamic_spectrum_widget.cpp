#include "export_dynamic_spectrum_widget.h"

export_dynamic_spectrum_widget::export_dynamic_spectrum_widget(QObject * parent, const char * name)
{
    this->setWindowTitle("Export file for dynamic spectrum");
    styleSheetDark = R"(
            QWidget {
                background-color: #121212;
                border-radius: 8px; /* border radius */
            }
            QPushButton {
                background-color: rgba(255,255,255,5%); /* background color */
                color: white; /* text color */
                padding: 12px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }

            QPushButton:hover {
                background-color: rgba(255,255,255,10%);
                border: 1px solid rgba(255,255,255, 15%);
            }
            QPushButton:pressed {
                background-color: rgba(255,255,255,18%);
                border: 1px solid rgba(255,255,255, 15%);
            }
            QPushButton:checked {
                background-color: rgba(255,255,255,18%);
                border: 1px solid rgba(255,255,255, 15%);
            }
            QToolButton {
                background-color: transparent; /* background color */
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }

            QToolButton:hover {
                background-color: rgba(255,255,255,5%);
            }
            QToolButton:pressed {
                background-color: rgba(255,255,255,10%);
            }
            QToolButton:checked {
                background-color: rgba(255,255,255,10%);
            }
            QToolTip {
                background-color: #141414;
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QTextEdit {
                background-color: rgba(255,255,255,5%);
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QCheckBox {
                background-color: transparent;
                color: white; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
            QCheckBox::indicator {
                background-color: #000000;
                padding: 4px; /* padding */
                border-radius: 4px; /* border radius */
            }
            QCheckBox::indicator::checked {
                background-color: #C2185B;
            }
            QLabel {
                background-color: transparent;
                color: white; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
            QTabWidget::pane {
                background-color: transparent; /* background color */
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QTabBar::tab {
                background-color: transparent; /* background color */
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
                min-width: 100px;
            }
            QTabBar::tab:selected {
                background-color: #C2185B;
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
                min-width: 100px;
            }
            QListWidget {
                background-color: rgba(255,255,255,5%);
            }
            QListWidget::item {
                background-color: transparent;
                color: white; /* text color */
                padding: 4px;
                font-size: 12px;
                font-family: silka;
                padding: 8px 12px;
                border-radius: 4px; /* border radius */
            }
            QListWidget::item:hover {
                background-color: rgba(255,255,255,5%);
                border: 1px solid rgba(255,255,255, 15%);
            }
            QListWidget::item:selected {
                background-color: #C2185B;
            }
            QSpinBox {
                background-color: rgba(255,255,255,5%);
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
            }
            QSpinBox::up-button, QSpinBox::down-button {
                background-color: transparent;
                color: red; /* text color */
                border: 1px solid rgba(255,255,255,5%);
                padding: 2px;
            }
            QSpinBox::up-button:pressed, QSpinBox::down-button:pressed  {
                background-color: #C2185B;
            }
            QSpinBox::up-arrow, QSpinBox::down-arrow {
                color: white; /* text color */
                padding: 2px;
            }
        )";
    styleSheetLight = R"(
            QWidget {
                background-color: #DEE4E7;
                border-radius: 8px; /* border radius */
            }
            QPushButton {
                background-color: rgba(0,0,0,9%); /* background color */
                color: black; /* text color */
                padding: 12px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }

            QPushButton:hover {
                background-color: rgba(0,0,0, 10%);
                border: 1px solid rgba(0,0,0, 15%);
            }
            QPushButton:pressed {
                background-color: rgba(0,0,0, 18%);
                border: 1px solid rgba(0,0,0, 15%);
            }
            QPushButton:checked {
                background-color: rgba(0,0,0, 18%);
                border: 1px solid rgba(0,0,0, 15%);
            }
            QToolButton {
                background-color: transparent; /* background color */
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }

            QToolButton:hover {
                background-color: rgba(0,0,0,5%);
            }
            QToolButton:pressed {
                background-color: rgba(0,0,0,10%);
            }
            QToolButton:checked {
                background-color: rgba(0,0,0,10%);
            }
            QToolTip {
                background-color: #141414;
                color: white; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QTextEdit {
                background-color: rgba(0,0,0,5%);
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QCheckBox {
                background-color: transparent;
                color: black; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
            QCheckBox::indicator {
                background-color: rgba(255,255,255,100%);;
                padding: 4px; /* padding */
                border-radius: 4px; /* border radius */
            }
            QCheckBox::indicator::checked {
                background-color: #C2185B;
            }
            QLabel {
                background-color: transparent;
                color: black; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
            QTabWidget::pane {
                background-color: transparent; /* background color */
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 4px; /* border radius */
                text-align: left;
                font-family: silka;
            }
            QTabBar::tab {
                background-color: transparent; /* background color */
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
                min-width: 100px;
            }
            QTabBar::tab:selected {
                background-color: #C2185B;
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
                min-width: 100px;
            }
            QListWidget {
                background-color: rgba(0,0,0,5%);
            }
            QListWidget::item {
                background-color: transparent;
                color: black; /* text color */
                padding: 4px;
                font-size: 12px;
                font-family: silka;
                padding: 8px 12px;
                border-radius: 4px; /* border radius */
            }
            QListWidget::item:hover {
                background-color: rgba(0,0,0,5%);
                border: 1px solid rgba(0,0,0, 15%);
            }
            QListWidget::item:selected {
                background-color: #C2185B;
            }
            QSpinBox {
                background-color: rgba(0,0,0,5%);
                color: black; /* text color */
                padding: 4px; /* padding */
                font-size: 15px; /* font size */
                border-radius: 8px; /* border radius */
                text-align: left;
                font-family: silka;
                padding: 8px 12px;
            }
            QSpinBox::up-button, QSpinBox::down-button {
                background-color: transparent;
                color: red; /* text color */
                border: 1px solid rgba(0,0,0,5%);
                padding: 2px;
            }
            QSpinBox::up-button:pressed, QSpinBox::down-button:pressed  {
                background-color: #C2185B;
            }
            QSpinBox::up-arrow, QSpinBox::down-arrow {
                color: black; /* text color */
                padding: 2px;
            }
        )";
    setUpWidgets(name);
}

void export_dynamic_spectrum_widget::setUpWidgets(const char * name)
{
    // - przy starcie nie chcemy go widziec -
    this->setVisible(false);

    // - size policy -
    this->setMaximumSize(100000,200);

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
