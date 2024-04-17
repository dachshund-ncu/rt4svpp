#ifndef VARCOEFSCALCWIDGET_H
#define VARCOEFSCALCWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <UI/custom_ui_elements.h>

class varCoefsCalcWidget : public customWidget
{
    Q_OBJECT
public:
    // konstruktor
    varCoefsCalcWidget(QObject * parent = nullptr, const char * name = 0, const char * window_title = 0);
    // -- elementy interfejsu --
    // buttony
    QPushButton * make = new QPushButton(this);
    QPushButton * cancel = new QPushButton(this);
    // layouty
    QVBoxLayout * Layout = new QVBoxLayout(this);
    QHBoxLayout * startChannels = new QHBoxLayout();
    QHBoxLayout * endChannels = new QHBoxLayout();
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    QHBoxLayout * absCalLayout = new QHBoxLayout();
    // text edity
    QTextEdit * startingChannelInt = new QTextEdit(this);
    QTextEdit * endingChannelInt = new QTextEdit(this);
    QTextEdit * absoluteErrorBox = new QTextEdit(this);
    // labele
    QLabel * sectionLabel = new QLabel(this);
    QLabel * startChannelLabel = new QLabel(this);
    QLabel * endChannelLabel = new QLabel(this);
    QLabel * absoluteCalibrationLabel = new QLabel(this);
private:
    void setUpWidget(const char * name = 0);
};

#endif // VARCOEFSCALCWIDGET_H
