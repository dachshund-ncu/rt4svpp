#include "rms_selector.h"

rms_selector::rms_selector()
{
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
