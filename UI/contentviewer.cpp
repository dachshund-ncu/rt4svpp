#include "contentviewer.h"
#include <QString>
contentViewer::contentViewer(customWidget * parent)
{
    this->setVisible(false);
    this->setWindowTitle("Obs. properties");
    initializeLayout();
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

