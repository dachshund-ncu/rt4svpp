#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QtGui>
#include "body.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    // -- zaczynamy program --
    QApplication program (argc, argv);
    program.setWindowIcon(QIcon(":/images/deathstaradder.svg"));
    //program.setStyle(new QWindowsVistaStyle);
    // -- tworzymy okno programu --
    if (argc > 1)
    {
        body * okno = new body(argv[1]);
        return program.exec();

    }
    else
    {
        body * okno = new body("");
        return program.exec();
    }
    // -- probojemy czytac podane w argumencie --
    //return program.exec();
}
