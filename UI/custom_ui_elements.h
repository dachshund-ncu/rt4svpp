#ifndef CUSTOM_UI_ELEMENTS_H
#define CUSTOM_UI_ELEMENTS_H

#include <QWidget>
#include <QSizePolicy>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class customWidget : public QWidget
{
public:
    QString styleSheetDark = R"(
            QWidget {
                background-color: rgba(255,255,255,5%);
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
    QString styleSheetLight = R"(
            QWidget {
                background-color: rgba(0,0,0,5%);
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
    customWidget(){
        setAttribute(Qt::WA_StyledBackground);
        this->setLightModeW();
    }
    customWidget(QWidget * parent){
        customWidget();
        this->setParent(parent);
    }

    void setLightModeW(){
        this->setStyleSheet(this->styleSheetLight);
    }

    void setDarkModeW(){
        this->setStyleSheet(this->styleSheetDark);
    }
};



class spacer : public QWidget {
public:
    spacer() {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QString styleSheet = R"(
            QWidget {
                background-color: transparent;
                border-radius: 8px; /* border radius */
            }
        )";
        setStyleSheet(styleSheet);
    }
};

class CustomMessageBox : public QDialog
{
public:
    CustomMessageBox(
            const QString& title,
            const QString& text,
            QWidget *parent = nullptr,
            bool isDarkMode = true)
        : QDialog(parent)
    {
        setWindowFlags(Qt::FramelessWindowHint); // Remove window frame
        this->setMinimumSize(300, 150);

        QLabel *titleLabel = new QLabel(title, this);
        titleLabel->setObjectName("customMessageBoxTitle");
        titleLabel->setAlignment(Qt::AlignCenter);

        QLabel *messageLabel = new QLabel(text, this);
        messageLabel->setObjectName("customMessageBoxMessage");
        messageLabel->setWordWrap(true);

        QPushButton *okButton = new QPushButton("OK", this);
        okButton->setObjectName("customMessageBoxButton");
        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(titleLabel);
        mainLayout->addWidget(messageLabel);
        mainLayout->addWidget(okButton);
        QString styleSheetDark = R"(
            QWidget {
                background-color: #121212;
                border-radius: 8px; /* border radius */
            }
            QPushButton {
                background-color: transparent; /* background color */
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
            QLabel {
                background-color: transparent;
                color: white; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
        )";
        QString styleSheetLight = R"(
            QWidget {
                background-color: #DEE4E7;
                border-radius: 8px; /* border radius */
            }
            QPushButton {
                background-color: transparent; /* background color */
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
            QLabel {
                background-color: transparent;
                color: black; /* text color */
                font-size: 15px; /* font size */
                text-align: left;
                font-family: silka;
            }
        )";
        if (isDarkMode){
            setStyleSheet(styleSheetDark);
        }
        else{
            setStyleSheet(styleSheetLight);
        }
        setWindowTitle(title);
    }
};

#endif // CUSTOM_UI_ELEMENTS_H
