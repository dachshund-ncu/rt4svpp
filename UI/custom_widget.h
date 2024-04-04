#ifndef CUSTOM_WIDGET_H
#define CUSTOM_WIDGET_H

#include <QWidget>

class custom_widget : public QWidget
{
    Q_OBJECT
public:
    explicit custom_widget(){
        setAttribute(Qt::WA_StyledBackground);
        QString styleSheet = R"(
            background-color: rgba(255,255,255, 9);
            heat_map_widget {
                background-color: rgba(255,255,255, 9);
            }
            QWidget {
                background-color: transparent;
                border-radius: 4px; /* border radius */
            }
            QLabel {
                background-color: transparent;
            }
        )";
        setStyleSheet(styleSheet);
    };

signals:

};

#endif // CUSTOM_WIDGET_H
