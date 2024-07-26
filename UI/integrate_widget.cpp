#include "integrate_widget.h"

integrate_widget::integrate_widget(QObject * parent, const char * name, const char * window_title)
{
    this->setWindowTitle(window_title);
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

    setUpWidget(name);
}

void integrate_widget::setUpWidget(const char * name)
{
    this->setVisible(false);
    // - size policy -
    this->setMaximumSize(200,150);
    // - rozmiary text editów -
    startingChannelInt->setMaximumSize(100,30);
    endingChannelInt->setMaximumSize(100,30);
    startingChannelInt->setMinimumSize(0,0);
    endingChannelInt->setMinimumSize(0,0);
    // - rozmiary przycisków -
    make->setMinimumSize(100,50);
    cancel->setMinimumSize(100,50);
    // - teksty -
    startChannelLabel->setText("Start");
    endChannelLabel->setText("End");
    make->setText("Go");
    cancel->setText("Cancel");
    sectionLabel->setText(name);
    // --------------------------------------
    // start
    startChannels->addWidget(startChannelLabel,Qt::AlignHCenter);
    startChannels->addWidget(startingChannelInt,Qt::AlignHCenter);
    // end
    endChannels->addWidget(endChannelLabel,Qt::AlignHCenter);
    endChannels->addWidget(endingChannelInt,Qt::AlignHCenter);
    // przyciski
    buttonsLayout->addWidget(cancel,Qt::AlignHCenter);
    buttonsLayout->addWidget(make,Qt::AlignHCenter);
    // do integrate
    Layout->addWidget(sectionLabel,Qt::AlignHCenter);
    Layout->addLayout(startChannels,Qt::AlignHCenter);
    Layout->addLayout(endChannels,Qt::AlignHCenter);
    Layout->addLayout(buttonsLayout,Qt::AlignHCenter);
}
