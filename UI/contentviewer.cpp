#include "contentviewer.h"
#include <QString>
contentViewer::contentViewer(QWidget * parent = NULL)
{
    initializeLayout();
    this->setVisible(false);
}

void contentViewer::initializeLayout()
{
    this->layout->addWidget(label);
}

void contentViewer::setContent(std::string text)
{
    this->label->setText(QString::fromStdString(text));
}

void contentViewer::show()
{
    this->setVisible(true);
}

