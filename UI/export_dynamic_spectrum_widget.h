#ifndef EXPORT_DYNAMIC_SPECTRUM_WIDGET_H
#define EXPORT_DYNAMIC_SPECTRUM_WIDGET_H
/*
 * Klasa, przechowująca interfejs do export_dynamic_spectrum (WD)
 * Ogólnie jest podobna do integrate_widget
 * Tylko że ma dwa dodatkowe pola jest inna xD
 */
#include <QtGui>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>

class export_dynamic_spectrum_widget : public QWidget
{
public:
    // konstruktor
    export_dynamic_spectrum_widget(QObject * parent = 0, const char * name = 0);

    // -- elementy interfejsu --
    // buttony do widgetu
    QPushButton * make = new QPushButton(this);
    QPushButton * cancel = new QPushButton(this);
    // layouty do widgetu
    QVBoxLayout * layout = new QVBoxLayout(this);
    QHBoxLayout * startChannelLayout = new QHBoxLayout();
    QHBoxLayout * endChannelLayout = new QHBoxLayout();
    QHBoxLayout * startEpochLayout = new QHBoxLayout();
    QHBoxLayout * endEpochlayout = new QHBoxLayout();
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    // text edity
    QTextEdit * startChannelTextEd = new QTextEdit(this);
    QTextEdit *   endChannelTextEd = new QTextEdit(this);
    QTextEdit *   startEpochTextEd = new QTextEdit(this);
    QTextEdit *     endEpochTextEd = new QTextEdit(this);
    // labele
    QLabel *       widgetLabel = new QLabel(this);
    QLabel * startChannelLabel = new QLabel(this);
    QLabel *   endChannelLabel = new QLabel(this);
    QLabel *   startEpochLabel = new QLabel(this);
    QLabel *     endEpochLabel = new QLabel(this);
private:
    void setUpWidgets(const char * name = 0);
};

#endif // EXPORT_DYNAMIC_SPECTRUM_WIDGET_H
