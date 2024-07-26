#ifndef CONTENTVIEWER_H
#define CONTENTVIEWER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <string>
#include <UI/custom_ui_elements.h>

class contentViewer : public customPopupWidget
{
public:
    contentViewer(customWidget * parent = nullptr);
    // methods
    void setContent( std::string text );
    void show();
private:
    // methods
    void initializeLayout();
    QVBoxLayout * layout = new QVBoxLayout(this);
    QLabel * label = new QLabel(this);
};

#endif // CONTENTVIEWER_H
