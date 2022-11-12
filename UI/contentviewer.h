#ifndef CONTENTVIEWER_H
#define CONTENTVIEWER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>
#include <string>

class contentViewer : public QWidget
{
public:
    contentViewer(QWidget * parent);
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
