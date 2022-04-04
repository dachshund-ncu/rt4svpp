#include "body.h"
#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <deque>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <thread>
#include <CCfits/CCfits>

using namespace std;
using namespace CCfits;
// -- konstruktor klasy programu --
body::body(const char * nazwa)
{
    Q_INIT_RESOURCE(resources);
    window.setVisible(false);
    // -- ustawiamy rozmiary okna --
    window.setGeometry(300,300,300,720);
    // -- ustawiamy tytul okna --
    window.setWindowTitle("RT4SV++");
    // --
    window.layout()->setMenuBar(superMegaMenuBar);
    // -- sizepolicy --
    kill_singspec->setMaximumSize(10000,10000);
    kill_rms_section->setMaximumSize(10000,10000);
    kill_dynspec->setMaximumSize(10000,10000);

    kill_singspec->setMinimumSize(0,0);
    kill_rms_section->setMinimumSize(0,0);
    kill_dynspec->setMinimumSize(0,0);

    grid->addWidget(left_hand_list, 0,0,9,1);
    grid->setColumnStretch(0,1);

    kill_dynspec->setText("Kill -->");
    kill_singspec->setText("Kill -->");
    kill_rms_section->setText("Kill -->");
    kill_singspec->setVisible(false);
    kill_dynspec->setVisible(false);
    kill_rms_section->setVisible(false);

    QObject::connect(kill_rms_section, SIGNAL(clicked()), this, SLOT(close_rms_section_slot()));
    QObject::connect(kill_dynspec, SIGNAL(clicked()), this, SLOT(kill_dynamic_spectrum()));
    QObject::connect(kill_singspec, SIGNAL(clicked()), this, SLOT(kill_single_spectrum()));

    // -- setujemy widgety roznych sekcji --
    connectSectionsToSlots();

    // -- probojemy czytac liste --
    if ( strncmp(nazwa, "", 300) != 0)
    {
        if (checkIfFits(nazwa) )
        {
            std::cout << "---> Fits file provided, loading..." << std::endl;
            QStringList lista;
            lista.append(QString(nazwa));
            dataTable->loadDataFromList(lista);
        }
        else
        {
            std::cout << "--> List of files provided, loading..." << std::endl;
            std::cout << "Loading list file " << "\"" << nazwa << "\"..." << std::endl;
            dataTable->loadDataFromList(string(nazwa));
        }


        if(dataTable->loadedData)
        {
            list_filename = string(nazwa);
            window.setGeometry(window.x(), window.y(),1360,720);
            display_dynamic_spectrum();
            dynspecWidget->setMapPressed(0,0);
            geometry_window_set = 1;
            loaded_data = true;
            window.setWindowTitle(QString::fromStdString("RT4SV++: " + dataTable->nameOfSource));
        }
        else
        {
            std::cout << "Could not read list file \"" << nazwa << "\"" << std::endl;
        }
    }
    // -- domyślnie ustawiamy dark mode --
    set_dark_mode();
    // -- pokazujemy okno --
    window.setVisible(true);
    window.show();
}


void body::setCheckedProperButtons()
{
    left_hand_list->DynamicSpectrum->setChecked(dynamic_spectrum_opened);
    left_hand_list->SingleSpectrum->setChecked(single_spectrum_opened);
    left_hand_list->RMSSection->setChecked(rms_section_opened);
}

bool body::checkIfFits(const char * filename)
{
    try
    {
        CCfits::FITS pies(filename, CCfits::Read);
        CCfits::ExtHDU & table = pies.extension(1);
        return true;
    }
    catch (...)
    {
        return false;
    }
}


// -------------------------------------------------------------------------------

// - wyswietla w programie sekcje "single spectrum"
void body::display_single_spectrum()
{
    // --- zmiana
    // -- obwarowanie warunkami --
    if (!dataTable->loadedData)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (dynamic_spectrum_opened)
       kill_dynamic_spectrum();
    else if (rms_section_opened)
        close_rms_section_slot();
    else if (single_spectrum_opened)
        return;

    // -- dodajemy widget do głównego gridu --
    grid->addWidget(ssWidget, 0,1,9,5);
    // -- dodajemy kill singspec do vboxa --
    left_hand_list->appendWidget(kill_dynspec);
    // -- ustalamy szerokości kolumny --
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);
    // -- zapelniamy wstepnie single spectrum --
    ssWidget->fillListWithObservations();
    // -- ustawiamy visibility naszego widgetu --
    left_hand_list->appendWidget(kill_singspec);
    ssWidget->setVisible(true);
    kill_singspec->setVisible(true);
    // -- ustawiamy boola, informujacego co jest akurat otwarte --
    single_spectrum_opened=1;
    // -----------
    setCheckedProperButtons();

    superMegaMenuBar->addSingspec();
}

// - zamyka sekcję "single spectrum"
void body::kill_single_spectrum()
{
    // - odpinamy od grida -
    grid->removeWidget(ssWidget);
    // - odpinamy od vboxa -
    left_hand_list->deleteWidgetFromList(kill_singspec);
    // - znikamy -
    ssWidget->setVisible(false);
    kill_singspec->setVisible(false);
    // - ustawiamy widoczność -
    single_spectrum_opened=0;
    //
    setCheckedProperButtons();

    superMegaMenuBar->hideAll();
}

void body::loadTimeSeriesWrapper(QFileDialog * dialog)
{
    string nazwa_pliku; // string z nazwa pliku
    QStringList fileName1;// qstring z nazwa pliku
    QString fileName;
    dialog->setFileMode(QFileDialog::ExistingFiles);


    if(dialog->exec())
    {
        fileName1 = dialog->selectedFiles();
    }

    if (fileName1.size() > 0)
    {
        fileName = fileName1[0];

    }
    else
    {
        return;
    }

    nazwa_pliku = fileName.toStdString(); // ustalamy nazwe pliku
    if (nazwa_pliku == "")
    {
        return;
    }

    QFileInfo info(fileName);

    //cout << info.absolutePath().toStdString() << endl; // ustalamy sciezke dzialania programu
    if (info.absolutePath().toStdString() != "")
    {
        working_directory = info.absolutePath().toStdString();
        //cout << working_directory << endl;

    }

    dataTable->loadDataFromList(fileName1);
    //cout << fileName1.size() << endl;
    loaded_data = 1;

    if (single_spectrum_opened == 1)
    {
        kill_single_spectrum();
        display_single_spectrum();
    }

    if (dynamic_spectrum_opened == 1)
    {
        display_dynamic_spectrum();
    }

    if (geometry_window_set == 0)
    {
        window.setGeometry(window.x(), window.y(),1360,720);
        display_dynamic_spectrum();
        geometry_window_set = 1;
    }
    dynspecWidget->setMapPressed(0,0);
    window.setWindowTitle(QString::fromStdString("RT4SV++: " + dataTable->nameOfSource));
}

// -- to samo robi, co read time series - ale po wcisnieciu przycisku --
void body::load_time_series_AVR()
{
    QFileDialog dialog(&window,tr("Select AVR files"), tr(""), tr("AVR files (*AVR.DAT);;All Files (*);;FITS files(*fits)"));
    loadTimeSeriesWrapper(&dialog);
}

void body::load_time_series_FITS()
{
    QFileDialog dialog(&window,tr("Select FITS files"), tr(""), tr("FITS files(*fits);;All Files (*);;AVR files (*AVR.DAT)"));
    loadTimeSeriesWrapper(&dialog);
}


// -- liczy calke z wszystkich widm --
void body::integrate_time_series()
{
    std::vector < int > minmax = readMinMaxValuesFromChannels(*intWidget->startingChannelInt, *intWidget->endingChannelInt);
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;
    // --- całka właściwa ---
    dataTable->integrate4Pols(min, max, left_hand_list->IsotimeInclude->isChecked());
    // --- wiadomość końcowa ---
    string message = "";
    message = "Integrated over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getIntegrationFileName(min, max);
    closeIntegrateSection();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));
}


// -- wyswietla widmo dynamiczne --
void body::display_dynamic_spectrum()
{
    if (!dataTable->loadedData)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (single_spectrum_opened == 1)
        kill_single_spectrum();
    else if (rms_section_opened == 1)
        close_rms_section_slot();
    else if (dynamic_spectrum_opened == 1)
        dynspecWidget->resetHeatMap();
    // -- chwilunia --
    if (!dynspecWidget->firstPlotDone)
        dynspecWidget->firstPlotOnDynamicSpectrum();
    // -- dodajemy widget do grida --
    grid->addWidget(dynspecWidget, 0,1,9,5);
    // -- dodajemy do vbox maina przycisk killujacy dynspec --
    left_hand_list->appendWidget(kill_dynspec);
    // -- ustalamy szerokości kolumny --
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);
    // -- visibility --
    dynspecWidget->setVisible(true);
    kill_dynspec->setVisible(true);
    // -- bool --
    dynamic_spectrum_opened = true;

    setCheckedProperButtons();

    superMegaMenuBar->addDynspec();
}

// -- zamyka widmo dynamiczne --
void body::kill_dynamic_spectrum()
{
    dynspecWidget->setVisible(false);
    kill_dynspec->setVisible(false);
    left_hand_list->deleteWidgetFromList(kill_dynspec);
    grid->removeWidget(dynspecWidget);
    dynamic_spectrum_opened = false;

    setCheckedProperButtons();

    superMegaMenuBar->hideAll();
}

// -- czyta kanały do liczenia rms z pliku 'chan4rms.sv' --
void body::read_chan4rms()
{
    // na początek - sprawdzamy rozmiar pliku:
    ifstream fle_check_tmp( (working_directory + "/" + "chan4rms.sv").c_str(), ios::binary | ios::ate);
    //cout << "rozmiar: " << fle_check_tmp.tellg() << endl;
    if (fle_check_tmp.tellg() < 10)
    {
        fle_check_tmp.close();
        chan4rms_loaded = 0;
        cout << " ---> Are you sure, that \"chan4rms.sv\" contains what it should? It's too small to be correct!" << endl;
        return;
    }
    fle_check_tmp.close();
    // obiekt pliku chan4rms
    ifstream chan4rms_file;
    // otwieramy chan4rms
    chan4rms_file.open((working_directory + "/" + "chan4rms.sv").c_str());
    // bufor
    string bufor;
    // char do sprawdzania, czy linia zaczyna się od #
    char spr;
    // umieszczamy w otoczeniu try... catch... by złapać ewentualny błąd w czytaniu pliku
    try
    {

        if (chan4rms_file.good())
        {
                chan4rms_file.get(spr);
                if (spr != '#')
                {
                    chan4rms_file.seekg(-1, ios::cur);
                    chan4rms_file >> rms_start_channel1;
                    chan4rms_file >> rms_end_channel1;
                    chan4rms_file >> rms_start_channel2;
                    chan4rms_file >> rms_end_channel1;
                }
                else
                {

                    getline(chan4rms_file, bufor);
                    //cout << bufor << endl;
                    chan4rms_file >> rms_start_channel1 >> rms_end_channel1;
                    chan4rms_file >> rms_start_channel2 >> rms_end_channel2;
                }
           chan4rms_loaded = 1;
           cout << "---> chan4rms.sv loaded!\n";
         }
        chan4rms_file.close();
    }

    catch (...)
    {
        chan4rms_file.close();
        chan4rms_loaded = 0;
        cout << " ---> found chan4rms.sv, but did not manage to read it" << endl;
    }

}

// -- czyta wartości kanałów z pliku 'chan4int.sv' --
bool body::read_chan4int()
{
    // na początek - sprawdzamy rozmiar pliku:
    ifstream fle_check_tmp( (working_directory + "/" + "chan4int.sv").c_str(), ios::binary | ios::ate);
    //cout << "rozmiar: " << fle_check_tmp.tellg() << endl;
    if (fle_check_tmp.tellg() < 10)
    {
        fle_check_tmp.close();
        //chan4rms_loaded = 0;
        cout << " ---> Are you sure, that \"chan4int.sv\" contains what it should? It's too small to be correct!" << endl;
        return 0;
    }
    fle_check_tmp.close();

    ifstream chan4int;
    chan4int.open((working_directory + "/" + "chan4int.sv").c_str());
    string bufor;
    char spr;

    try
    {
        if (chan4int.good())
        {
            chan4int.get(spr);
            if (spr != '#')
            {
                chan4int.seekg(-1, ios::cur);
                chan4int >> chan4int_start;
                chan4int >> chan4int_end;
            }
            else
            {
                getline(chan4int, bufor);
                chan4int >> chan4int_start;
                chan4int >> chan4int_end;
            }
        }
        else
        {
            //cout << endl;
            //cout << "----> Could not find chan4int.sv!" << endl;
            chan4int.close();
            return 0;
        }
        chan4int.close();
        return 1;
     }
    catch (...)
    {
        chan4int.close();
        return 0;
    }

}

// -- liczy srednia po predkosci - dla wszystkich epok --
void body::calculate_aver_over_velocity()
{
    std::vector < int > minmax = readMinMaxValuesFromChannels(*averOverVelocityWidget->startingChannelInt, *averOverVelocityWidget->endingChannelInt);
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;

    // liczymy aver over velocity
    dataTable->averageOverVelocity4Pols(min, max, left_hand_list->IsotimeInclude->isChecked());

    string message = "";
    message = "Averaged over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getAverOverVelFileName(min, max);
    closeAOVSection();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}

// -- liczy srednia po czasie - dla jednej epoki --
vector < double > body::average_over_time(int min_epoch, int max_epoch, vector < double > time_series, vector < double >  error)
{
    double suma = 0.0;
    int number_of_epochs;
    number_of_epochs = max_epoch - min_epoch + 1;
    if (number_of_epochs <= 0)
        number_of_epochs = 1;

    // petla liczaca srednia
    for (int i = 0; i < number_of_epochs; i++)
    {
        suma = suma + time_series[min_epoch + i];
    }
    suma = suma / number_of_epochs;

    // peyla liczaca blad
    double sumaer = 0.0;
    for (int i = 0; i < number_of_epochs; i++)
    {
        sumaer = sumaer + error[min_epoch + i];
    }

    sumaer = sumaer / number_of_epochs;

    vector < double > wyniki (2);
    wyniki[0] = suma;
    wyniki[1] = sumaer;

    return wyniki;
}

// -- liczy srednia po czasie - dla wszystkich epok --
void body::calculate_aver_over_time()
{
    // wypisujemy co chcemy
    std::vector < int > minmax = readMinMaxValuesFromEpochs(*averOverTimeWidget->startingChannelInt, *averOverTimeWidget->endingChannelInt);
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;

    // wykonujemy właściwej transformacji
    dataTable->averOverTime4Pols(min, max);

    // wiadomość dla usera
    string message;
    message = "Averaged over epochs: " + to_string(min) + " " + " -> " + to_string(max) + "\n";
    message = message + "Saved to " + dataTable->getAverOverTimeFileName(min, max);
    closeAOTSection();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));
}


// -- liczy VI, FI i chi2red dla wszystkich kanałów --
void body::calculate_spectral_index()
{
    /*
     * Celem tej metody jest policzenie współczynników VI, FI i Chi^2_red
     * Oraz zapisanie ich do plików tekstowych (robi to klasa spectral_container, tutaj tylko wywołujemy jej metodę)
    */
    // --------------
    std::vector < int > minmax = readMinMaxValuesFromEpochs(*SpectralIndexWidget->startingChannelInt, *SpectralIndexWidget->endingChannelInt);
    double absoluteErr = readNumberFromQTextEdit(SpectralIndexWidget->absoluteErrorBox);
    //std::cout << absoluteErr << std::endl;
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;
    // --------------
    dataTable->spectralIndex4Pol(min, max, absoluteErr);
    // --------------
    string message;
    message = "Spectral-indexed over epochs: " + to_string(min) + " " + " -> " + to_string(max) + "\n";
    message = message + "VI Saved to " + dataTable->getVIFileName(min, max) + "\n";
    message = message + "FI Saved to " + dataTable->getFIFileName(min, max) + "\n";
    message = message + "Chi2Red Saved to " + dataTable->getChi2RedFileName(min, max) + "\n";
    // --------------
    closeSPINDSection();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));
}

void body::save_all_to_gnuplot_slot()
{
    dataTable->saveAllSpectra();
    // - zapisujemy wiadomość -
    std::string message = "Saved all spectra to directory: " + dataTable->saveDirectory;
    // - wyświetlamy -
    QMessageBox::information(&window, tr("Message to you!"), QString::fromStdString(message));
}

// -- przeładowuje obecnie załadowane dane --
void body::reload_slot()
{
    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    if (dataTable->fileNamesTab.size() != 0)
    {
        // --- tymczasowo ---
        QStringList tmpqstringlist;
        for(unsigned long int wplw = 0; wplw < dataTable->fileNamesTab.size(); wplw++)
        {
            tmpqstringlist.push_back(QString::fromStdString(dataTable->fileNamesTab[wplw]));
        }
        // -------------------
        dataTable->loadDataFromList(tmpqstringlist);
        // -- zapełniamy danymi sekcję RMS --
        rms_sec_w->fillWithData();
    }
    // -- jeśli widmo dynamiczne było otwarte - updatujemy je --
    if (dynamic_spectrum_opened)
    {
        dynspecWidget->setMapPressed(0,0);
        display_dynamic_spectrum();
    }
}

// -- czyta nazwy plików z pliku 'flagged_obs.dat' --
bool body::read_flagged_files()
{
    flagged_avr_files.clear();
    ifstream flagfile;
    flagfile.open((working_directory + "/" + "flagged_obs.dat").c_str());
    if (!flagfile.good())
    {
        cout << "No flagfile_obs.dat file" << endl;
        return false;
    }

    string bufor_do_listy; // maly bufor do przechowywania linii z listy

    // - petla wczytujaca pliki z obserwacjami -
    while(flagfile.good())
    {
      // czytamy linie z pliku
      getline(flagfile, bufor_do_listy);
      // jesli jest zerowej dlugosci, to mamy koniec pliku i wywalamy z petli
      if(bufor_do_listy.size() < 1)
      {
        break;
      }
      // czytamy plik z listy
      flagged_avr_files.push_back(bufor_do_listy);

    }
    return true;
}

// -- sprawdza, czy podana w argumencie nazwa pliku nie widnieje jako zaflagowana --
bool body::check_if_flagged(string avr_filename)
{
    // jesli nie ma zaladowanych flag to zawsze zwracamy false
    if (flagged_files_loaded == 0)
        return false;

    for (int i = 0; i < flagged_avr_files.size(); i++)
    {
        // albo zwykłe nazwy plików - jak wybieramy z listy
        if (avr_filename == flagged_avr_files[i])
            return true; // jesli znajdziemy na liscie nasza obserwacje - konczymy
        // albo nazwy z pełną ścieżką - jak wybieramy same pliki
        if (avr_filename == working_directory + "/" + flagged_avr_files[i])
            return true; // jesli znajdziemy na liscie nasza obserwacje - konczymy
    }


    return false;
}

/*
// -- funkcja do flagowania zaznaczonej na widmie dynamicznym epoki --
void body::flag_slot()
{
    // zapisujemy nazwe oflagowanego pliku
    string flagged_filename = dataTable->fileNamesTab[xind];

    // -- okno do upewniania sie, ze na pewno chcesz --
    QMessageBox::StandardButton upewka;
    upewka = QMessageBox::question(&window, "Are you sure?", QString::fromStdString("Do you realy want to flag " + flagged_filename + "?"), QMessageBox::Yes| QMessageBox::No);
    if (upewka == QMessageBox::No)
    {
        return;
    }


    flags_number = flags_number + 1;



    // dopisujemy jego nazwe do pliku z flagami
    ofstream flagfile;
    flagfile.open((working_directory + "/" + "flagged_obs.dat").c_str(), ios::app);
    if (!flagfile.good())
        flagfile.open((working_directory + "/" + "flagged_obs.dat").c_str());

    flagfile << flagged_filename << endl;

    cout << endl << "----> flagged " << flagged_filename << endl;

    flagfile.close();

    // oznaczamy obserwacje na widmie dynamicznym
    //QCPItemRect * rectangleflag = new QCPItemRect(&dynamic_spectrum_pl);
    QCPItemRect * tmp = new QCPItemRect(&dynamic_spectrum_pl);
    flagi.push_back(tmp);
    QBrush pen;
    QPen pennywise;
    pen.setColor(Qt::black);
    pennywise.setColor(Qt::black);
    flagi[flags_number-1]->setBrush(pen);
    flagi[flags_number-1]->setPen(pennywise);
    flagi[flags_number-1]->topLeft->setCoords(double(xind)-0.5, dataTable->velocityTable[xind][0]);
    //cout << dataTable->velocityTable[xind][0] << endl;
    //cout << dataTable->velocityTable[xind][dataTable->velocityTable[xind].size()-1] << endl;
    flagi[flags_number-1]->bottomRight->setCoords(double(xind)+0.5, dataTable->velocityTable[xind][dataTable->velocityTable[xind].size()-1]);

    flagi[flags_number-1]->setLayer("flags");
    dynamic_spectrum_pl.moveLayer(flagi[flags_number-1]->layer(), colorMap->layer(), QCustomPlot::limAbove );
    dynamic_spectrum_pl.replot();
    flagged_files_on_spectrum = 1;
    string message;
    message = "Flagged " + flagged_filename + "\nRELOAD the data to make changes";
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}
*/


void body::export_file_for_dynamic_spectrum()
{
    // -- inty z przechowywanymi granicami --
    std::vector < int > minmaxchannels = readMinMaxValuesFromChannels(*exDynspWidget->startChannelTextEd, *exDynspWidget->endChannelTextEd);
    std::vector < int > minmaxepochs = readMinMaxValuesFromEpochs(*exDynspWidget->startEpochTextEd, *exDynspWidget->endEpochTextEd);

    int min, max, min_epoch, max_epoch;
    min = minmaxchannels[0];
    max = minmaxchannels[1];
    min_epoch = minmaxepochs[0];
    max_epoch = minmaxepochs[1];
    if(min == -1 || max == -1 || min_epoch == -1 || max_epoch == -1)
        return;
    dataTable->saveDynamicSpectrumToFile(min_epoch, max_epoch, min, max, left_hand_list->IsotimeInclude->isChecked());

    // wiadomość końcowa
    string message = "";
    message = "Dynamic spectrum over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getDynSpecFileName(min_epoch, max_epoch);
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

    // -- zamykamy sekcje dynspec --
    closeWDSection();
}

void body::open_rms_section_slot()
{
    // -- obwarowanie warunkami --
    if (!dataTable->loadedData)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (dynamic_spectrum_opened)
       kill_dynamic_spectrum();
    else if (single_spectrum_opened)
        kill_single_spectrum();
    else if (rms_section_opened)
        return;
    // ----------------------------

    if(rms_sec_w->popupWindowOpened)
    {
        rms_sec_w->closePopupWindowSlot();
        rms_sec_w->popupWindowOpened = false;
    }

    // dodajemy do grida widget sekcji
    grid->addWidget(rms_sec_w, 0, 1, 9, 5);

    // dodajemy zamykający button do głównego panelu
    left_hand_list->appendWidget(kill_rms_section);

    // zapełniamy danymi
    rms_sec_w->fillWithData();

    // ustalamy szerokość kolumn
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);

    rms_section_opened = true;
    setCheckedProperButtons();
    // -- ustalamy visibilities --
    rms_sec_w->setVisible(true);
    kill_rms_section->setVisible(true);

    superMegaMenuBar->addRmssec();
}

void body::close_rms_section_slot()
{
    // ustalamy visibilities
    kill_rms_section->setVisible(false);
    rms_sec_w->setVisible(false);

    // odpinamy od grida
    left_hand_list->deleteWidgetFromList(kill_rms_section);
    grid->removeWidget(rms_sec_w);

    // ustalamy wartość boola
    rms_section_opened = false;
    setCheckedProperButtons();

    superMegaMenuBar->hideAll();
}


//void body::autorange_plot(QCustomPlot * plot)
//{
//    plot->rescaleAxes();
//    double max_x, min_x, max_y, min_y;
//    max_x = plot->xAxis->range().upper;
//    min_x = plot->xAxis->range().lower;
//    max_y = plot->yAxis->range().upper;
//    min_y = plot->yAxis->range().lower;
//    double diffrence_x = max_x - min_x;
//    double diffrence_y = max_y - min_y;
//    plot->xAxis->setRange(min_x - (0.05 * diffrence_x), max_x + (0.05 * diffrence_x));
//    plot->yAxis->setRange(min_y - (0.05 * diffrence_y), max_y + (0.05 * diffrence_y));
//    plot->replot();
//}

void body::set_dark_mode()
{
    dynspecWidget->darthMode(!dark_mode_enabled);
    ssWidget->darthMode(!dark_mode_enabled);
    rms_sec_w->darthMode(!dark_mode_enabled);
    /*
    // pomocnicze prezydenty
    QPen graph_dark;
    graph_dark.setColor(QColor(135,206,250));
    graph_dark.setWidth(2);

    QPen graph_light;
    graph_light.setColor(QColor(0,0,255));
    graph_light.setWidth(2);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));

    if (dark_mode_enabled == 0)
    {
        // -- tutaj ustawiamy coś, co nazywa się dark mode --

        // -- deklarujemy biały qpen
        QPen duda;
        duda.setColor(Qt::white);
        // -- ustawiamy boola --
        dark_mode_enabled = 1;
    }
    else
    {
        // -- deklarujemy biały qpen
        QPen duda;
        duda.setColor(Qt::black);
        dark_mode_enabled = 0;
    }
    */
}



// -----------------------------------------------------------------------------------
void body::openIntegrateSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        intWidget->startingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->minRangeVelIndex+1)));
        intWidget->endingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->maxRangeVelIndex+1)));
    }

    // - ustawiamy boola, informującego o otwarciu sekcji -
    integrate_window_opened = 1;

    // - przypinamy do vboxa -
    //left_hand_list->appendWidget(intWidget);
    intWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeIntegrateSection()
{
    // - znikamy widget -
    intWidget->setVisible(false);
    // - odpinamy od vboxa -
    //left_hand_list->deleteWidgetFromList(intWidget);
    // - ustalamy boola -
    integrate_window_opened = 0;
}

// -----------------------------------------------------------------------------------
void body::openAOVSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        averOverVelocityWidget->startingChannelInt->setText(QString::fromStdString(to_string((dynspecWidget->yIndex+1)-1) ));
        averOverVelocityWidget->endingChannelInt->setText(QString::fromStdString(to_string((dynspecWidget->yIndex+1)+1) ));
    }

    // - ustawiamy boola, informującego o otwarciu sekcji -
    aver_over_velocity_window_opened = 1;

    // - przypinamy do vboxa -
    //left_hand_list->appendWidget(averOverVelocityWidget);

    // - pokazujemy -
    averOverVelocityWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeAOVSection()
{
    // - znikamy widget -
    averOverVelocityWidget->setVisible(false);
    // - odpinamy od vboxa -
    //left_hand_list->deleteWidgetFromList(averOverVelocityWidget);
    // - ustalamy boola -
    aver_over_velocity_window_opened = 0;
}

// -----------------------------------------------------------------------------------
void body::openAOTSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        averOverTimeWidget->startingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->minObsNumber+1)));
        averOverTimeWidget->endingChannelInt->setText((QString::fromStdString(to_string(dynspecWidget->maxObsNumber+1))));
    }

    // ustalamy boola
    aver_over_time_window_opened = 1;

    // - przypinamy do vboxa -
    //left_hand_list->appendWidget(averOverTimeWidget);

    // - pokazujemy -
    averOverTimeWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeAOTSection()
{
    // - znikamy -
    averOverTimeWidget->setVisible(false);

    // - odpinamy od vboxa -
    //left_hand_list->deleteWidgetFromList(averOverTimeWidget);

    // - zmieniamy boola -
    aver_over_time_window_opened = 0;
}

// -- layout do liczenia VI FI i chi2red --
void body::openSPINDSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        SpectralIndexWidget->startingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->minObsNumber+1)));
        SpectralIndexWidget->endingChannelInt->setText((QString::fromStdString(to_string(dynspecWidget->maxObsNumber+1))));
    }

    // - przypinamy do vboxa -
    //left_hand_list->appendWidget(SpectralIndexWidget);

    // - pokazujemy -
    SpectralIndexWidget->setVisible(true);

    // - ustawiamy boola -
    spind_window_opened = 1;
}

// -- zamyka layout do liczenia VI FI i chi2red --
void body::closeSPINDSection()
{
    // - znikamy widget -
    SpectralIndexWidget->setVisible(false);

    // - odpinamy od vboxa -
    //left_hand_list->deleteWidgetFromList(SpectralIndexWidget);

    // - usrtawiamy boola -
    spind_window_opened = 0;
}
void body::openWDSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();

    // dla otwarteg owidma dynczmicznego - zapełniamy text edity
    if(dynamic_spectrum_opened== 1)
    {
        exDynspWidget->startChannelTextEd->setText(QString::fromStdString(to_string(dynspecWidget->minRangeVelIndex+1)));
        exDynspWidget->endChannelTextEd->setText(QString::fromStdString(to_string(dynspecWidget->maxRangeVelIndex+1)));
        exDynspWidget->startEpochTextEd->setText(QString::fromStdString(to_string(dynspecWidget->minObsNumber+1)));
        exDynspWidget->endEpochTextEd->setText(QString::fromStdString(to_string(dynspecWidget->maxObsNumber+1)));
    }

    // przypinamy do vboxa
    //left_hand_list->appendWidget(exDynspWidget);
    // ustalamy visibility
    exDynspWidget->setVisible(true);

    // ustalamy boola
    wd_section_opened = 1;
}

void body::closeWDSection()
{
    // -- znikamy --
    exDynspWidget->setVisible(false);
    // -- odpinamy od vboxa --
    //left_hand_list->deleteWidgetFromList(exDynspWidget);
    // -- ustalamy boola --
    wd_section_opened = 0;
}

void body::openCALSection()
{
    // jeśli dane nie są załadowane
    if (dataTable->loadedData == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    // zamykamy inne otwarte sekcje
    closeOtherSections();
    // ------------------------------------------------------------
    // -- setujemy default na labele --
    if (caltabs_loaded == 0)
    {
        calibrateWidget->caltabL1LoadedLabel->setText(QString::fromStdString("Not loaded!"));
        calibrateWidget->caltabR1LoadedLabel->setText(QString::fromStdString("Not loaded!"));
    }
    else
    {
        calibrateWidget->caltabL1LoadedLabel->setText(QString::fromStdString("Loaded"));
        calibrateWidget->caltabR1LoadedLabel->setText(QString::fromStdString("Loaded"));
    }
    // ------------------------------------------------------------
    // -- ustawiamy napis na przycisku, w zależności od tego czy kalibrowaliśmy czy nie --
    if (calibration_done == 0)
    {
        calibrateWidget->make->setText("Calibrate");
        calibrateWidget->make->setDown(false);
    }
    else if (calibration_done == 1)
    {
        calibrateWidget->make->setText("Uncalibrate");
        calibrateWidget->make->setDown(true);
    }
    // ------------------------------------------------------------
    // -- dodajemy do vboxa --
    //left_hand_list->appendWidget(calibrateWidget);
    // -- ustawiamy visibility --
    calibrateWidget->setVisible(true);
    // -- ustawiamy boola --
    calibration_section_opened = 1;
}

void body::closeCALSection()
{
    // -- znikamy --
    calibrateWidget->setVisible(false);
    // -- odpinamy od vboxa --
    //left_hand_list->deleteWidgetFromList(calibrateWidget);
    // -- ustawiamy boola --
    calibration_section_opened = 0;
}

// -----------------------------------------------------------------------------------
std::vector <int> body::readMinMaxValuesFromChannels(QTextEdit &minChannelTE, QTextEdit &maxChannelTE)
{
    std::vector <int> returnedValues = {-1,-1};
    unsigned int min, max;
    QString mins = minChannelTE.toPlainText();
    QString maxs = maxChannelTE.toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return returnedValues;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString());
        max = stoi(maxs.toStdString());
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return returnedValues;
    }

    // -- obsługujemy kilka przypadków błędnego wpisania paramatrów --
    // początkowy channel większy od końcowego
    if (min > max)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel > max channel!"));
        return returnedValues;
    }
    // początkowy channel mniejszy od 1
    if (min < 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel < 1!"));
        return returnedValues;
    }
    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > dataTable->spectraTableI[0].size())
        max = dataTable->spectraTableI[0].size();

    // ustalamy wartości zwracanego wektora
    returnedValues[0] = min;
    returnedValues[1] = max;

    return returnedValues;
}

// -----------------------------------------------------------------------------------
std::vector <int> body::readMinMaxValuesFromEpochs(QTextEdit &minEpochlTE, QTextEdit &maxEpochlTE)
{
    std::vector <int> returnedValues = {-1,-1};
    unsigned int min, max;
    QString mins = minEpochlTE.toPlainText();
    QString maxs = maxEpochlTE.toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return returnedValues;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString());
        max = stoi(maxs.toStdString());
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return returnedValues;
    }

    // -- obsługujemy kilka przypadków błędnego wpisania paramatrów --
    // początkowy channel większy od końcowego
    if (min > max)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel > max channel!"));
        return returnedValues;
    }
    // początkowy channel mniejszy od 1
    if (min < 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel < 1!"));
        return returnedValues;
    }
    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > dataTable->spectraTableI.size())
        max = dataTable->spectraTableI.size();

    // ustalamy wartości zwracanego wektora
    returnedValues[0] = min;
    returnedValues[1] = max;

    return returnedValues;
}

// -----------------------------------------------------------------------------------
void body::connectSectionsToSlots()
{
    // integrate
    QObject::connect(intWidget->make, SIGNAL(clicked()), this, SLOT(integrate_time_series()));
    QObject::connect(intWidget->cancel, SIGNAL(clicked()), this, SLOT(closeIntegrateSection()));
    // AOV
    QObject::connect(averOverVelocityWidget->make, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity()));
    QObject::connect(averOverVelocityWidget->cancel, SIGNAL(clicked()), this, SLOT(closeAOVSection()));
    // AOT
    QObject::connect(averOverTimeWidget->make, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time()));
    QObject::connect(averOverTimeWidget->cancel, SIGNAL(clicked()), this, SLOT(closeAOTSection()));
    // SPIND
    QObject::connect(SpectralIndexWidget->make, SIGNAL(clicked()), this, SLOT(calculate_spectral_index()));
    QObject::connect(SpectralIndexWidget->cancel, SIGNAL(clicked()), this, SLOT(closeSPINDSection()));
    // WD
    QObject::connect(exDynspWidget->make, SIGNAL(clicked()), this, SLOT(export_file_for_dynamic_spectrum()));
    QObject::connect(exDynspWidget->cancel, SIGNAL(clicked()), this, SLOT(closeWDSection()));
    // CAL
    QObject::connect(calibrateWidget->make, SIGNAL(clicked()), this, SLOT(calibrate_button()));
    QObject::connect(calibrateWidget->cancel, SIGNAL(clicked()), this, SLOT(closeCALSection()));
    QObject::connect(calibrateWidget->loadCaltabL1, SIGNAL(clicked()), this, SLOT(load_l1_caltab_button()));
    QObject::connect(calibrateWidget->loadCaltabR1, SIGNAL(clicked()), this, SLOT(load_r1_caltab_button()));
}

// -----------------------------------------------------------------------------------
void body::closeOtherSections()
{
    if(wd_section_opened)
       closeWDSection();
    if (calibration_section_opened)
       closeCALSection();
    if (integrate_window_opened)
       closeIntegrateSection();
    if (aver_over_time_window_opened)
        closeAOTSection();
    if (spind_window_opened)
        closeSPINDSection();
    if (aver_over_velocity_window_opened)
        closeAOVSection();
}
// -- do przycisku --
void body::load_l1_caltab_button()
{
    string nazwa_pliku; // string z nazwa pliku
    QString fileName;// qstring z nazwa pliku
    // otwieramy file selectora
    fileName = QFileDialog::getOpenFileName(&window,tr("Select LHC caltab"), tr(""), tr("All Files (*)")); // qfile dialog
    // eksportujemy nazwę pliku do zmiennej string
    nazwa_pliku = fileName.toStdString();
    // ladujemy caltab
    dataTable->loadLHCCaltab(nazwa_pliku);
}

// -- do przycisku --
void body::load_r1_caltab_button()
{
    string nazwa_pliku; // string z nazwa pliku
    QString fileName;// qstring z nazwa pliku
    // otwieramy file selectora
    fileName = QFileDialog::getOpenFileName(&window,tr("Select RHC caltab"), tr(""), tr("All Files (*)")); // qfile dialog
    // eksportujemy nazwę pliku do zmiennej string
    nazwa_pliku = fileName.toStdString();
    // ladujemy caltab
    dataTable->loadRHCCaltab(nazwa_pliku);
}

void body::calibrate_button()
{
    dataTable->calibrateAll(true);
}

double body::readNumberFromQTextEdit(QTextEdit *box)
{
    /*
     * Prosta metoda, czytająca numer z QTextEdit i konwertująca go na double
     * Dodatkowo posiada kilka zabezpieczeń na wypadek nieprawidłowego wypełnienia
     */
    double returnedValue;
    QString bufor = box->toPlainText();
    if (bufor.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return 0.0;
    }
    try
    {
        returnedValue = bufor.toDouble();
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return 0.0;
    }
    return returnedValue;
}
