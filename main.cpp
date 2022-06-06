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
#include <CCfits/CCfits>
#include <ctime>
using namespace CCfits;

#define version 1.40

void onWelcome()
{
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "-----> Welcome to RT4SV++ (RT4 Spectra Visualizer ++)" << std::endl;
}

void onHelp()
{
    std::cout << "-----> RT4SV++ help: " << std::endl;
    std::cout << "-----> Usage: " << std::endl;
    std::cout << "       rt4sv++ list_of_files [OPTIONS] " << std::endl;
    std::cout << "       or " << std::endl;
    std::cout << "       rt4sv++ [OPTIONS] " << std::endl;
    std::cout << "       OPTIONS: " << std::endl;
    std::cout << "       -h, --help      | Display this message " << std::endl;
    std::cout << "       -v, --version   | Display version info " << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
}

void onVersion()
{
    std::cout << "-----> RT4SV++ version: " << version << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
}

int main(int argc, char *argv[])
{
    /*
     * This is MAIN function of the RT4SV++ app
     * It starts main object of the program - body (defined in body.h)
     * Also handles help and version printing, depending on arguments passed in argv
     */

    srand(time(NULL));
    Q_INIT_RESOURCE(resources);
    FITS::setVerboseMode(false);
    // -- zaczynamy program --
    QApplication program (argc, argv);
    program.setWindowIcon(QIcon(":/images/deathstaradder.svg"));
    program.setStyle("GTK2");

    onWelcome();

    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            std::string arg = std::string(argv[i]);
            if(arg == "-v" || arg == "--version") // -v or --version
            {
                onVersion();
                exit(0);
            }
            else if (arg == "-h" || arg == "--help") // -h or --help
            {
                onHelp();
                exit(0);
            }
            else // everything else
            {
                body * okno = new body(arg.c_str());
                break;
            }
        }
    }
    else
    {
        body * okno = new body("");
    }
    return program.exec();
}
