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

    // -- ustawiamy rozmiary okna --
    window.setGeometry(300,300,300,720);
    // -- ustawiamy tytul okna --
    window.setWindowTitle("RT4SV++");
    // -- sizepolicy --
    kill_singspec->setMaximumSize(10000,10000);
    kill_rms_section->setMaximumSize(10000,10000);
    kill_gauss->setMaximumSize(10000,10000);
    kill_dynspec->setMaximumSize(10000,10000);

    kill_singspec->setMinimumSize(0,0);
    kill_rms_section->setMinimumSize(0,0);
    kill_gauss->setMinimumSize(0,0);
    kill_dynspec->setMinimumSize(0,0);

    grid->addWidget(left_hand_list, 0,0,9,1);
    grid->setColumnStretch(0,1);

    kill_dynspec->setText("Kill dynamic spectrum");
    kill_singspec->setText("Kill single spectrum");
    kill_rms_section->setText("Kill RMS section");
    kill_singspec->setVisible(false);
    kill_dynspec->setVisible(false);
    kill_rms_section->setVisible(false);

    QObject::connect(kill_rms_section, SIGNAL(clicked()), this, SLOT(close_rms_section_slot()));
    QObject::connect(kill_dynspec, SIGNAL(clicked()), this, SLOT(kill_dynamic_spectrum()));
    QObject::connect(kill_singspec, SIGNAL(clicked()), this, SLOT(kill_single_spectrum()));

    // -- setujemy widgety roznych sekcji --
    set_gauss_widget();
    connectSectionsToSlots();

    // -- probojemy czytac liste --
    if ( strncmp(nazwa, "", 300) != 0)
    {
        std::cout << "Loading list file " << "\"" << nazwa << "\"..." << std::endl;
        dataTable->loadDataFromList(string(nazwa));
        if(dataTable->loadedData)
        {
            list_filename = string(nazwa);
            window.setGeometry(window.x(), window.y(),1360,720);
            display_dynamic_spectrum();
            geometry_window_set = 1;
            loaded_data = true;
        }
        else
        {
            std::cout << "Could not read list file \"" << nazwa << "\"" << std::endl;
        }
    }
    // -- domyślnie ustawiamy dark mode --
    set_dark_mode();
    // -- pokazujemy okno --
    window.show();
}

// --- connectujemy ---
// łączymy buttony z innymi metodami


// -------------------------------------------------------------------------------
// -- funkcje, ustawiajace widgety (wywolywane na poczatku programu i tylko wtedy)

void body::set_gauss_widget()
{
    // -- ustalamy maksima --
    fitted_params_gb->setMinimumSize(200,200);
    starting_fit_params_gb->setMinimumSize(200,200);

    //scroll_fitted_params->setWidget(fitted_params_gb);
    //scroll_starting_params->setWidget(starting_fit_params_gb);

    //scroll_fitted_params->setBackgroundRole(QPalette::Light);
    //scroll_starting_params->setBackgroundRole(QPalette::Light);

    //scroll_fitted_params->setWidgetResizable(true);
    //scroll_starting_params->setWidgetResizable(true);

    // --- ustalaby visibilities ---
    gauss_fitting_widget->setVisible(false);
    kill_gauss->setVisible(false);

    // -- ustalamy teksty na labelach --
    actual_mjd_gauss->setText("Obs. 1");
    actual_epoch_nr_gauss->setText("MJD: ");
    /*
    amp_starting->setText("Sv 1:");
    vel_starting->setText("Vel 1:");
    fwhm_starting->setText("FWHM 1:");
    amp_fitted->setText("Sv 1:");
    vel_fitted->setText("Vel 1:");
    fwhm_fitted->setText("FWHM 1:");
    pm->setText("+/-");
    pm2->setText("+/-");
    pm3->setText("+/-");
    pm4->setText("+/-");
    pm5->setText("+/-");
    pm6->setText("+/-");
    */
    // -- ustalamy czcionkę na labelach
    QFont f( "Arial", 10, QFont::Bold);
    actual_mjd_gauss->setFont(f);
    actual_epoch_nr_gauss->setFont(f);
    /*
    amp_starting->setFont(f);
    vel_starting->setFont(f);
    fwhm_starting->setFont(f);
    amp_fitted->setFont(f);
    vel_fitted->setFont(f);
    fwhm_fitted->setFont(f);
    */
    // --- ustalamy teksty na przyciskach ---
    fit_gauss->setText("Fit gauss");
    kill_gauss->setText("Kill gaussian section");
    prev_epoch->setText("<--");
    next_epoch->setText("-->");
    set_clicker_gauss->setText("Toggle click");
    change_bounds->setText("Change fit limits");
    range_lbl->setText("Fit Vlsr: ");
    lt->setText(" to ");
    set_range_to_fit_limits->setText("Set range to fit limits");
    set_range_to_data->setText("Set range to data");

    // --- ustalamy rozmiary text editów --
    /*
    amp_starting_texed->setMaximumSize(100,30);
    vel_starting_texed->setMaximumSize(100,30);
    fwhm_starting_texed->setMaximumSize(100,30);
    amp_fitted_texed->setMaximumSize(100,30);
    vel_fitted_texed->setMaximumSize(100,30);
    fwhm_fitted_texed->setMaximumSize(100,30);
    */
    min_fit_range->setMaximumSize(100,30);
    max_fit_range->setMaximumSize(100,30);

    /*
    amp_starting_err_texed->setMaximumSize(100,30);
    vel_starting_err_texed->setMaximumSize(100,30);
    fwhm_starting_err_texed->setMaximumSize(100,30);
    amp_fitted_err_texed->setMaximumSize(100,30);
    vel_fitted_err_texed->setMaximumSize(100,30);
    fwhm_fitted_err_texed->setMaximumSize(100,30);
    */
    // -- ustalamy rozmiary --
    fit_gauss->setMaximumSize(100000,100000);
    prev_epoch->setMaximumSize(100000,100000);
    next_epoch->setMaximumSize(100000,100000);
    set_clicker_gauss->setMaximumSize(100000,100000);
    change_bounds->setMaximumSize(100000,100000);
    set_range_to_fit_limits->setMaximumSize(100000,100000);
    set_range_to_data->setMaximumSize(100000,100000);

    fit_gauss->setMinimumSize(0,0);
    prev_epoch->setMinimumSize(0,0);
    next_epoch->setMinimumSize(0,0);
    set_clicker_gauss->setMinimumSize(0,0);
    change_bounds->setMinimumSize(0,0);
    set_range_to_fit_limits->setMinimumSize(0,0);
    set_range_to_data->setMinimumSize(0,0);

    // -- ustalamy wygląd naszego widgetu
    // - w skrócie - dajemy grid 10 x 10

    // buttony na górze
    checkboxes_on_left_top->addWidget(set_lines_gauss);
    checkboxes_on_left_top->addWidget(set_points_gauss);
    checkboxes_on_left_top->addWidget(set_crosshair_gauss);
    labels_over_plot_gauss->addWidget(actual_mjd_gauss);
    labels_over_plot_gauss->addWidget(actual_epoch_nr_gauss);
    range_buttons->addWidget(set_range_to_fit_limits);
    range_buttons->addWidget(set_range_to_data);
    top_left_buttons_gauss->addItem(checkboxes_on_left_top);
    top_left_buttons_gauss->addItem(labels_over_plot_gauss);
    top_left_buttons_gauss->addItem(range_buttons);
    top_left_buttons_gauss->addWidget(prev_epoch);
    top_left_buttons_gauss->addWidget(next_epoch);

    // buttony na górze po prawej
    top_right_buttons_gauss->addWidget(set_clicker_gauss);
    top_right_buttons_gauss->addWidget(change_bounds);
    top_right_buttons_gauss->addWidget(fit_gauss);
    fit_range_managment->addWidget(range_lbl);
    fit_range_managment->addWidget(min_fit_range);
    fit_range_managment->addWidget(lt);
    fit_range_managment->addWidget(max_fit_range);

    top_right_buttons_gauss_V->addItem(top_right_buttons_gauss);
    top_right_buttons_gauss_V->addItem(fit_range_managment);

    // sekcja z dopasowanymi wartościami
    /*
    first_gauss_amp_fitted->addWidget(amp_fitted);
    first_gauss_amp_fitted->addWidget(amp_fitted_texed);
    first_gauss_amp_fitted->addWidget(pm);
    first_gauss_amp_fitted->addWidget(amp_fitted_err_texed);

    first_gauss_vel_fitted->addWidget(vel_fitted);
    first_gauss_vel_fitted->addWidget(vel_fitted_texed);
    first_gauss_vel_fitted->addWidget(pm2);
    first_gauss_vel_fitted->addWidget(vel_fitted_err_texed);

    first_gauss_fwhm_fitted->addWidget(fwhm_fitted);
    first_gauss_fwhm_fitted->addWidget(fwhm_fitted_texed);
    first_gauss_fwhm_fitted->addWidget(pm3);
    first_gauss_fwhm_fitted->addWidget(fwhm_fitted_err_texed);


    fitted_params->addItem(first_gauss_amp_fitted);
    fitted_params->addItem(first_gauss_vel_fitted);
    fitted_params->addItem(first_gauss_fwhm_fitted);
    */
    fitted_params->addWidget(fitted_params_texted);
    fitted_params_gb->setLayout(fitted_params);

    // sekcja ze startowymi wartościami
    /*
    first_gauss_amp_start->addWidget(amp_starting);
    first_gauss_amp_start->addWidget(amp_starting_texed);
    first_gauss_amp_start->addWidget(pm4);
    first_gauss_amp_start->addWidget(amp_starting_err_texed);

    first_gauss_vel_start->addWidget(vel_starting);
    first_gauss_vel_start->addWidget(vel_starting_texed);
    first_gauss_vel_start->addWidget(pm5);
    first_gauss_vel_start->addWidget(vel_starting_err_texed);

    first_gauss_fwhm_start->addWidget(fwhm_starting);
    first_gauss_fwhm_start->addWidget(fwhm_starting_texed);
    first_gauss_fwhm_start->addWidget(pm6);
    first_gauss_fwhm_start->addWidget(fwhm_starting_err_texed);

    starting_fit_params->addItem(first_gauss_amp_start);
    starting_fit_params->addItem(first_gauss_vel_start);
    starting_fit_params->addItem(first_gauss_fwhm_start);
    */
    starting_fit_params->addWidget(starting_params_texted);
    starting_fit_params_gb->setLayout(starting_fit_params);

    // --- dodajemy do gridu ---
    grid_for_gauss->addWidget(spectrum_w_gauss, 1,0,9,7);
    grid_for_gauss->addItem(top_left_buttons_gauss, 0,0,1,7);
    grid_for_gauss->addItem(top_right_buttons_gauss_V, 0,7,1,3);
    grid_for_gauss->addWidget(fitted_params_gb, 1,7,5,3);
    grid_for_gauss->addWidget(starting_fit_params_gb, 6,7,4,3);

    grid_for_gauss->setColumnStretch(0, 1);
    grid_for_gauss->setColumnStretch(1, 1);
    grid_for_gauss->setColumnStretch(2, 1);
    grid_for_gauss->setColumnStretch(3, 1);
    grid_for_gauss->setColumnStretch(4, 1);
    grid_for_gauss->setColumnStretch(5, 1);
    grid_for_gauss->setColumnStretch(6, 1);
    grid_for_gauss->setColumnStretch(7, 1);
    grid_for_gauss->setColumnStretch(8, 1);
    grid_for_gauss->setColumnStretch(9, 1);

    grid_for_gauss->setRowStretch(0,1);
    grid_for_gauss->setRowStretch(1,1);
    grid_for_gauss->setRowStretch(2,1);
    grid_for_gauss->setRowStretch(3,1);
    grid_for_gauss->setRowStretch(4,1);
    grid_for_gauss->setRowStretch(5,1);
    grid_for_gauss->setRowStretch(6,1);
    grid_for_gauss->setRowStretch(7,1);
    grid_for_gauss->setRowStretch(8,1);
    grid_for_gauss->setRowStretch(9,1);
    //grid_for_gauss->addWidget(fit_gauss, 5,0,1,2);

    // -- ustalamy sobie plot, by były w nim rezydua --
    spectrum_w_gauss->plotLayout()->clear();
    spectrum_w_gauss->clearGraphs();
    // setujemy spacing
    spectrum_w_gauss->plotLayout()->setRowSpacing(0);
    // dodajemy axis recty
    gorne_widmo_gauss->setupFullAxesBox(true);
    dolne_widmo_gauss->setupFullAxesBox(true);

    spectrum_w_gauss->plotLayout()->addElement(0,0, gorne_widmo_gauss);
    spectrum_w_gauss->plotLayout()->addElement(1,0, dolne_widmo_gauss);
    spectrum_w_gauss->plotLayout()->setRowStretchFactor(0,5);
    spectrum_w_gauss->plotLayout()->setRowStretchFactor(1,1);

    // margin group
    QCPMarginGroup * margin_group = new QCPMarginGroup(spectrum_w_gauss);
    gorne_widmo_gauss->setMarginGroup(QCP::msLeft|QCP::msRight, margin_group);
    dolne_widmo_gauss->setMarginGroup(QCP::msLeft|QCP::msRight, margin_group);
    // marginesy
    gorne_widmo_gauss->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msTop);
    gorne_widmo_gauss->setMargins(QMargins(0,0,0,0));
    dolne_widmo_gauss->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
    dolne_widmo_gauss->setMargins(QMargins(0,0,0,0));

    // - gridy -
    gorne_widmo_gauss->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    dolne_widmo_gauss->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    gorne_widmo_gauss->axis(QCPAxis::atLeft)->grid()->setVisible(true);
    dolne_widmo_gauss->axis(QCPAxis::atLeft)->grid()->setVisible(true);

    // - wylaczamy labele na dolnej osi gornego plotu -
    gorne_widmo_gauss->axis(QCPAxis::atBottom, 0)->setTickLabels(false);

    // - ustalamy interakcje -
    spectrum_w_gauss->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    // connectujemy zmiane zasiegu w jednym i drugim
    connect(gorne_widmo_gauss->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), dolne_widmo_gauss->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(dolne_widmo_gauss->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), gorne_widmo_gauss->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    //connect(dolne_widmo_gauss->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), gorne_widmo_gauss->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));

    // przypisujemy metody do buttonów
    QObject::connect(prev_epoch, SIGNAL(clicked()), this, SLOT(previous_gauss_spec()));
    QObject::connect(next_epoch, SIGNAL(clicked()), this, SLOT(next_gauss_spec()));
    QObject::connect(set_range_to_data, SIGNAL(clicked()), this, SLOT(scale_fit_plot_to_data()));
    QObject::connect(set_range_to_fit_limits, SIGNAL(clicked()), this, SLOT(scale_fit_plot_to_txt()));
    QObject::connect(set_lines_gauss, SIGNAL(clicked()), this, SLOT(show_lines_gauss()));
    QObject::connect(set_points_gauss, SIGNAL(clicked()), this, SLOT(show_points_gauss()));
    QObject::connect(spectrum_w_gauss, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(cross_hair_gauss(QMouseEvent *)));
    QObject::connect(set_crosshair_gauss, SIGNAL(clicked()), this, SLOT(show_crosshair_gauss()));


    // -- dodajemy do gaussa graphy --
    // na początek - dwa na rezyduach
    QCPGraph * residuals_zeros = spectrum_w_gauss->addGraph(dolne_widmo_gauss->axis(QCPAxis::atBottom), dolne_widmo_gauss->axis(QCPAxis::atLeft));
    QCPGraph * residuals_accurate = spectrum_w_gauss->addGraph(dolne_widmo_gauss->axis(QCPAxis::atBottom), dolne_widmo_gauss->axis(QCPAxis::atLeft));
    // następnie - jeden na dane, jeden na fit, dwa na crosshair, wszystkie pozostałe - na dopasowania
    QCPGraph * spectrum_data = spectrum_w_gauss->addGraph(gorne_widmo_gauss->axis(QCPAxis::atBottom), gorne_widmo_gauss->axis(QCPAxis::atLeft));
    QCPGraph * fit_line = spectrum_w_gauss->addGraph(gorne_widmo_gauss->axis(QCPAxis::atBottom), gorne_widmo_gauss->axis(QCPAxis::atLeft));
    QCPGraph * crosshair_v_gauss = spectrum_w_gauss->addGraph(gorne_widmo_gauss->axis(QCPAxis::atBottom), gorne_widmo_gauss->axis(QCPAxis::atLeft));
    QCPGraph * crosshair_h_gauss = spectrum_w_gauss->addGraph(gorne_widmo_gauss->axis(QCPAxis::atBottom), gorne_widmo_gauss->axis(QCPAxis::atLeft));

    // -- skrowidz --
    // 0 - linia dopasowania na rezyduach
    // 1 - linia widma na rezyduach
    // 2 - widmo na wykresie wimda
    // 3 - linia dopasowania na wykresie widma
    // 4 - linia pionowa crosshair
    // 5 - linia pozioma crosshair

    // -- ustawiamy prezydenty --
    set_gauss_light_mode_pens();

    set_lines_gauss->setChecked(true);
    set_points_gauss->setChecked(false);
    set_crosshair_gauss->setChecked(true);


}
// --------------------------------------------------------------------------------

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
    else if (gauss_section_opened)
        close_gauss_widget();
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
}

// -- to samo robi, co read time series - ale po wcisnieciu przycisku --
void body::load_time_series()
{
    string nazwa_pliku; // string z nazwa pliku
    QStringList fileName1;// qstring z nazwa pliku
    QString fileName;

    QFileDialog dialog(&window,tr("Select AVR files or/and FITS file"), tr(""), tr("All Files (*);;AVR files (*AVR.DAT);;FITS files(*fits)"));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if(dialog.exec())
    {
        fileName1 = dialog.selectedFiles();
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
    else if (gauss_section_opened == 1)
        close_gauss_widget();
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
}

// -- zamyka widmo dynamiczne --
void body::kill_dynamic_spectrum()
{
    dynspecWidget->setVisible(false);
    kill_dynspec->setVisible(false);
    left_hand_list->deleteWidgetFromList(kill_dynspec);
    grid->removeWidget(dynspecWidget);
    dynamic_spectrum_opened = false;

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
    // wypisujemy co chcemy
    std::vector < int > minmax = readMinMaxValuesFromEpochs(*SpectralIndexWidget->startingChannelInt, *SpectralIndexWidget->endingChannelInt);
    int min = minmax[0];
    int max = minmax[1];
    if (min == -1 and max == -1)
        return;

    dataTable->spectralIndex4Pol(min, max, 0.0);

    string message;
    message = "Spectral-indexed over epochs: " + to_string(min) + " " + " -> " + to_string(max) + "\n";
    message = message + "VI Saved to " + dataTable->getVIFileName(min, max) + "\n";
    message = message + "FI Saved to " + dataTable->getFIFileName(min, max) + "\n";
    message = message + "Chi2Red Saved to " + dataTable->getChi2RedFileName(min, max) + "\n";
    //message = message + "chi2 Saved to " + filenamechi2 + "\n";
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
        display_dynamic_spectrum();
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

    // -- ustalamy visibilities --
    rms_sec_w->setVisible(true);
    kill_rms_section->setVisible(true);
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

        // -- single dynamic spectrum --
        // - tło -
        spectrum_w_gauss->setBackground(Qt::black);
        spectrum_w_gauss->axisRect()->setBackground(Qt::black);
        // - kwadracik -
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setBasePen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setBasePen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setBasePen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setBasePen(duda);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setBasePen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setBasePen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setBasePen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setTickLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setTickLabelColor(Qt::white);
        // subtick
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setSubTickPen(duda);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setSubTickPen(duda);
        // tick
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setTickPen(duda);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setTickPen(duda);
        // label
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setLabelColor(Qt::white);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setLabelColor(Qt::white);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setLabelColor(Qt::white);
        // prezydenty
        set_gauss_dark_mode_pens();

        spectrum_w_gauss->replot();

        // -- ustawiamy styl okna --
        //qApp->setStyleSheet("theme: Dark");

        // -- ustawiamy boola --
        dark_mode_enabled = 1;
    }
    else
    {
        // -- deklarujemy biały qpen
        QPen duda;
        duda.setColor(Qt::black);

        // -- single dynamic spectrum --
        // - tło -
        spectrum_w_gauss->setBackground(Qt::white);
        spectrum_w_gauss->axisRect()->setBackground(Qt::white);
        // - kwadracik -
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setBasePen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setBasePen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setBasePen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setBasePen(duda);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setBasePen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setBasePen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setBasePen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setTickLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setTickLabelColor(Qt::black);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setTickLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setTickLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setTickLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setTickLabelColor(Qt::black);
        // subtick
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setSubTickPen(duda);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setSubTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setSubTickPen(duda);
        // tick
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setTickPen(duda);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setTickPen(duda);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setTickPen(duda);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setTickPen(duda);
        // label
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atTop)->setLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atRight)->setLabelColor(Qt::black);

        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atTop)->setLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setLabelColor(Qt::black);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atRight)->setLabelColor(Qt::black);
        // prezydenty
        set_gauss_light_mode_pens();

        spectrum_w_gauss->replot();

        dark_mode_enabled = 0;
    }
}


void body::open_gauss_widget()
{
    QMessageBox::information(&window, tr("Error!"), tr("Not ready to use. Maybe it will be in the future ;)"));
    return;

    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    if (dynamic_spectrum_opened == 1)
    {
        kill_dynamic_spectrum();
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        //QMessageBox::information(&window, tr("Error!"), tr("Please, close the DYNAMIC SPECTRUM window"));
        //return;
    }
    else if (single_spectrum_opened == 1)
    {
        kill_single_spectrum();
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        //QMessageBox::information(&window, tr("Error!"), tr("Please, close the SINGLE SPECTRUM window"));
        //return;
    }
    else if (rms_section_opened == 1)
    {
        close_rms_section_slot();
    }
    else if (gauss_section_opened == 1)
    {
        return;
    }

    // dodajemy do grida widget sekcji
    grid->addWidget(gauss_fitting_widget, 0, 1, 9, 5);


    // dodajemy zamykający button do głównego panelu
    left_hand_list->appendWidget(kill_gauss);

    // ustalamy visibilities
    gauss_fitting_widget->setVisible(true);
    kill_gauss->setVisible(true);

    // -- ustalamy boole --
    gauss_section_opened = 1;

    // -- plotujemy aktualną obserwację --
    actual_gauss_spec();

}

void body::close_gauss_widget()
{
    // -- ustalamy visibilities --
    gauss_fitting_widget->setVisible(false);
    kill_gauss->setVisible(false);

    // -- odpinamy od rozmiarowkarzow --
    left_hand_list->deleteWidgetFromList(kill_gauss);
    grid->removeWidget(gauss_fitting_widget);

    // -- ustawiamy boole --
    gauss_section_opened = 0;
}

void body::previous_gauss_spec()
{
    // -- na wejściu zmieniamy wartość markera --
    // robimy takie fikołki, żeby nie szukało danych gdzie ich kurwa nie ma xD
    if (actual_obs_index_gauss == 0)
    {
        return;
    }
    else if (actual_obs_index_gauss == dataTable->spectraTableI.size()-1)
    {
        actual_obs_index_gauss = actual_obs_index_gauss-1;
    }
    else
    {
        actual_obs_index_gauss = actual_obs_index_gauss-1;
    }

    // wektor z danymi
    QVector < double > x(dataTable->spectraTableI[actual_obs_index_gauss].size()), y(dataTable->spectraTableI[actual_obs_index_gauss].size());
    // zapelniamy wektor
    for(unsigned int i = 0; i < dataTable->spectraTableI[actual_obs_index_gauss].size(); i++)
    {
        x[i] = dataTable->velocityTable[actual_obs_index_gauss][i];
        y[i] = dataTable->spectraTableI[actual_obs_index_gauss][i];
    }
    // dodajemy grafikę do naszego kochanego wykresu
    spectrum_w_gauss->graph(2)->setData(x,y);
    // skalujemy wykres na nowo
    autoscale_gauss_graph();
    // replotujemy
    spectrum_w_gauss->replot();

    // -- ustawiamy labele --
    string mjd_gauss;
    mjd_gauss = "MJD: " + to_string(int(dataTable->mjdTable[actual_obs_index_gauss]));
    actual_mjd_gauss->setText(QString::fromStdString(mjd_gauss));

    string obsn;
    obsn = "Obs. " + to_string(actual_obs_index_gauss+1);
    actual_epoch_nr_gauss->setText(QString::fromStdString(obsn));

}


void body::next_gauss_spec()
{
    // -- na wejściu zmieniamy wartość markera --
    // robimy takie fikołki, żeby nie szukało danych gdzie ich kurwa nie ma xD
    if (actual_obs_index_gauss == 0)
    {
        actual_obs_index_gauss = actual_obs_index_gauss+1;
    }
    else if (actual_obs_index_gauss == dataTable->spectraTableI.size()-1)
    {
        return;
    }
    else
    {
        actual_obs_index_gauss = actual_obs_index_gauss+1;
    }

    // wektor z danymi
    QVector < double > x(dataTable->spectraTableI[actual_obs_index_gauss].size()), y(dataTable->spectraTableI[actual_obs_index_gauss].size());
    // zapelniamy wektor
    for(unsigned int i = 0; i < dataTable->spectraTableI[actual_obs_index_gauss].size(); i++)
    {
        x[i] = dataTable->velocityTable[actual_obs_index_gauss][i];
        y[i] = dataTable->spectraTableI[actual_obs_index_gauss][i];
    }
    // dodajemy grafikę do naszego kochanego wykresu
    spectrum_w_gauss->graph(2)->setData(x,y);
    // skalujemy wykres na nowo
    autoscale_gauss_graph();
    // replotujemy
    spectrum_w_gauss->replot();

    // -- ustawiamy labele --
    string mjd_gauss;
    mjd_gauss = "MJD: " + to_string(int(dataTable->mjdTable[actual_obs_index_gauss]));
    actual_mjd_gauss->setText(QString::fromStdString(mjd_gauss));

    string obsn;
    obsn = "Obs. " + to_string(actual_obs_index_gauss+1);
    actual_epoch_nr_gauss->setText(QString::fromStdString(obsn));

}

void body::actual_gauss_spec()
{
    // wektor z danymi
    QVector < double > x(dataTable->spectraTableI[actual_obs_index_gauss].size()), y(dataTable->spectraTableI[actual_obs_index_gauss].size());
    // zapelniamy wektor
    for(unsigned int i = 0; i < dataTable->spectraTableI[actual_obs_index_gauss].size(); i++)
    {
        x[i] = dataTable->velocityTable[actual_obs_index_gauss][i];
        y[i] = dataTable->spectraTableI[actual_obs_index_gauss][i];
    }
    // dodajemy grafikę do naszego kochanego wykresu
    spectrum_w_gauss->graph(2)->setData(x,y);
    // skalujemy wykres na nowo
    autoscale_gauss_graph();
    // replotujemy
    spectrum_w_gauss->replot();

    // -- ustawiamy labele --
    string mjd_gauss;
    mjd_gauss = "MJD: " + to_string(int(dataTable->mjdTable[actual_obs_index_gauss]));
    actual_mjd_gauss->setText(QString::fromStdString(mjd_gauss));

    string obsn;
    obsn = "Obs. " + to_string(actual_obs_index_gauss+1);
    actual_epoch_nr_gauss->setText(QString::fromStdString(obsn));
}

void body::plot_initial_fit()
{

}

void body::plot_fitted_fit()
{

}

void body::autoscale_gauss_graph()
{
    // -- czyścimy crosshair - nie chcemy szkalować do niego --
    spectrum_w_gauss->graph(4)->data()->clear();
    spectrum_w_gauss->graph(5)->data()->clear();

    // -- warunki --
    if (range_to_fit_set == 1)
    {
        // -- jeśli uda się przeczytać pola tekstowe - czytamy z nich zasięgi
        if (read_gauss_range_from_txt() == 1)
        {
            // -- reksalujemy tylko oś y
            spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->rescale();
            spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->rescale();

            // -- bierzemy wartości z tej skali --
            double max_y, min_y, max_y2, min_y2;
            max_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().upper;
            min_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().lower;
            max_y2 = spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->range().upper;
            min_y2 = spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->range().lower;

            // -- ustalamy roznice
            double diffrence_y = max_y - min_y;
            double diffrence_y2 = max_y - min_y;

            // -- skalujemy oś y
            spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setRange(min_y - (0.05 * diffrence_y), max_y + (0.05 * diffrence_y));
            spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setRange(min_y2 - (0.05 * diffrence_y2), max_y2 + (0.05 * diffrence_y2));

            // -- skalujemy oś x - zgodnie z wartościami z pól tekstowych
            spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setRange(min_fit_range_d, max_fit_range_d);
            spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setRange(min_fit_range_d, max_fit_range_d);

        }
        //  -- jak nie - robimy po staremu (szkalujemy do danych)
        else
        {
            // -- reskalujemy górne widmo --
            spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->rescale();
            spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->rescale();
            spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->rescale();
            spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->rescale();

            // -- bierzemy wartości --
            double max_x, min_x;
            double max_y, min_y, max_y2, min_y2;
            max_x = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->range().upper;
            min_x = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->range().lower;
            max_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().upper;
            min_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().lower;
            max_y2 = spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->range().upper;
            min_y2 = spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->range().lower;

            double diffrence_y = max_y - min_y;
            double diffrence_y2 = max_y - min_y;
            spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setRange(min_x, max_x);
            spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setRange(min_x, max_x);
            spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setRange(min_y - (0.05 * diffrence_y), max_y + (0.05 * diffrence_y));
            spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setRange(min_y2 - (0.05 * diffrence_y2), max_y2 + (0.05 * diffrence_y2));
        }
    }
    else
    {
        // -- reskalujemy górne widmo --
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->rescale();
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->rescale();
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->rescale();
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->rescale();

        // -- bierzemy wartości --
        double max_x, min_x;
        double max_y, min_y, max_y2, min_y2;
        max_x = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->range().upper;
        min_x = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->range().lower;
        max_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().upper;
        min_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().lower;
        max_y2 = spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->range().upper;
        min_y2 = spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->range().lower;

        double diffrence_y = max_y - min_y;
        double diffrence_y2 = max_y - min_y;
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->setRange(min_x, max_x);
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atBottom)->setRange(min_x, max_x);
        spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->setRange(min_y - (0.05 * diffrence_y), max_y + (0.05 * diffrence_y));
        spectrum_w_gauss->axisRect(1)->axis(QCPAxis::atLeft)->setRange(min_y2 - (0.05 * diffrence_y2), max_y2 + (0.05 * diffrence_y2));
    }
}

bool body::read_gauss_range_from_txt()
{
    QString minsg,maxsg;
    minsg = min_fit_range->toPlainText();
    maxsg = max_fit_range->toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (minsg.toStdString() == "" || maxsg.toStdString() == "")
    {
        //cout << "Empty txt!" << endl;
        return 0;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min_fit_range_d = stod(minsg.toStdString());
        max_fit_range_d = stod(maxsg.toStdString());
        return 1;
    }
    catch(...)
    {
        //cout << "Some other error" << endl;
        return 0;
    }

}

void body::scale_fit_plot_to_data()
{
    range_to_data_set = 1;
    range_to_fit_set = 0;
    autoscale_gauss_graph();
    spectrum_w_gauss->replot();
}

void body::scale_fit_plot_to_txt()
{
    range_to_data_set = 0;
    range_to_fit_set = 1;
    autoscale_gauss_graph();
    spectrum_w_gauss->replot();
}

void body::set_gauss_dark_mode_pens()
{
    // -- skrowidz --
    // 0 - linia dopasowania na rezyduach
    // 1 - linia widma na rezyduach
    // 2 - widmo na wykresie wimda
    // 3 - linia dopasowania na wykresie widma
    // 4 - linia pionowa crosshair
    // 5 - linia pozioma crosshair

    // pomocnicze prezydenty
    QPen spectrum;
    spectrum.setColor(QColor(135,206,250));
    spectrum.setWidth(2);

    QPen fitted_gausses;
    fitted_gausses.setColor(QColor(Qt::red));
    fitted_gausses.setWidth(2);

    QPen crosshairpen;
    crosshairpen.setColor(QColor(Qt::white));
    crosshairpen.setStyle(Qt::DashLine);

    // -- ustawiamy prezydenty --
    spectrum_w_gauss->graph(0)->setPen(fitted_gausses);
    spectrum_w_gauss->graph(1)->setPen(spectrum);
    spectrum_w_gauss->graph(2)->setPen(spectrum);
    spectrum_w_gauss->graph(3)->setPen(fitted_gausses);
    spectrum_w_gauss->graph(4)->setPen(crosshairpen);
    spectrum_w_gauss->graph(5)->setPen(crosshairpen);

    //gauss_spec_csh_label->setColor(Qt::white);

}

void body::set_gauss_light_mode_pens()
{
    // -- skrowidz --
    // 0 - linia dopasowania na rezyduach
    // 1 - linia widma na rezyduach
    // 2 - widmo na wykresie wimda
    // 3 - linia dopasowania na wykresie widma
    // 4 - linia pionowa crosshair
    // 5 - linia pozioma crosshair

    // pomocnicze prezydenty
    QPen spectrum;
    spectrum.setColor(QColor(0,0,255));
    spectrum.setWidth(2);

    QPen fitted_gausses;
    fitted_gausses.setColor(QColor(Qt::red));
    fitted_gausses.setWidth(2);

    QPen crosshairpen;
    crosshairpen.setColor(QColor(Qt::black));
    crosshairpen.setStyle(Qt::DashLine);

    // -- ustawiamy prezydenty --
    spectrum_w_gauss->graph(0)->setPen(fitted_gausses);
    spectrum_w_gauss->graph(1)->setPen(spectrum);
    spectrum_w_gauss->graph(2)->setPen(spectrum);
    spectrum_w_gauss->graph(3)->setPen(fitted_gausses);
    spectrum_w_gauss->graph(4)->setPen(crosshairpen);
    spectrum_w_gauss->graph(5)->setPen(crosshairpen);

    //gauss_spec_csh_label->setColor(Qt::black);
}

void body::show_lines_gauss()
{
    if (!set_lines_gauss->isChecked())
    {
        spectrum_w_gauss->graph(1)->setLineStyle(QCPGraph::lsNone);
        spectrum_w_gauss->graph(2)->setLineStyle(QCPGraph::lsNone);
    }
    else
    {
        spectrum_w_gauss->graph(1)->setLineStyle(QCPGraph::lsLine);
        spectrum_w_gauss->graph(2)->setLineStyle(QCPGraph::lsLine);
    }
    spectrum_w_gauss->replot();

}

void body::show_points_gauss()
{
    if (!set_points_gauss->isChecked())
    {
        spectrum_w_gauss->graph(1)->setScatterStyle(QCPScatterStyle::ssNone);
        spectrum_w_gauss->graph(2)->setScatterStyle(QCPScatterStyle::ssNone);
    }
    else
    {
        spectrum_w_gauss->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
        spectrum_w_gauss->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    }
    spectrum_w_gauss->replot();
}

void body::cross_hair_gauss(QMouseEvent * event)
{
    // nie wykonujemy nic, jeśli nie oglądamy crosshair
    if(!set_crosshair_gauss->isChecked())
    {
        return;
    }

    // -- przejmujemy pozycję kursora --
    double x,y;

    //max_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().upper;
    x = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->pixelToCoord(event->pos().x());
    y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->pixelToCoord(event->pos().y());

    // -- czytamy zasięgi --
    double max_y, min_y, max_x, min_x;
    max_x = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->range().upper;
    min_x = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atBottom)->range().lower;
    max_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().upper;
    min_y = spectrum_w_gauss->axisRect(0)->axis(QCPAxis::atLeft)->range().lower;

    // -- deklarujemy wektory --
    QVector < double > hline(2), vline(2), hline_y(2), vline_x(2);
    // zapełniamy je
    hline[0] = min_x;
    hline[1] = max_x;
    vline[0] = min_y;
    vline[1] = max_y;
    hline_y[0] = y;
    hline_y[1] = y;
    vline_x[0] = x;
    vline_x[1] = x;

    // dajemy do grafiki
    spectrum_w_gauss->graph(4)->setData(hline, hline_y);
    spectrum_w_gauss->graph(5)->setData(vline_x, vline);

    // -- aktualizujemy wykres widma --
    spectrum_w_gauss->replot();
}

void body::show_crosshair_gauss()
{
    if (!set_crosshair_gauss->isChecked())
    {
        spectrum_w_gauss->graph(4)->setVisible(false);
        spectrum_w_gauss->graph(5)->setVisible(false);
        spectrum_w_gauss->graph(4)->data()->clear();
        spectrum_w_gauss->graph(5)->data()->clear();

    }
    else
    {
        spectrum_w_gauss->graph(4)->setVisible(true);
        spectrum_w_gauss->graph(5)->setVisible(true);
    }
    spectrum_w_gauss->replot();
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
    left_hand_list->appendWidget(intWidget);
    intWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeIntegrateSection()
{
    // - znikamy widget -
    intWidget->setVisible(false);
    // - odpinamy od vboxa -
    left_hand_list->deleteWidgetFromList(intWidget);
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
        averOverVelocityWidget->startingChannelInt->setText(QString::fromStdString(to_string(dynspecWidget->minRangeVelIndex+1)));
        averOverVelocityWidget->endingChannelInt->setText((QString::fromStdString(to_string(dynspecWidget->maxRangeVelIndex+1))));
    }

    // - ustawiamy boola, informującego o otwarciu sekcji -
    aver_over_velocity_window_opened = 1;

    // - przypinamy do vboxa -
    left_hand_list->appendWidget(averOverVelocityWidget);

    // - pokazujemy -
    averOverVelocityWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeAOVSection()
{
    // - znikamy widget -
    averOverVelocityWidget->setVisible(false);
    // - odpinamy od vboxa -
    left_hand_list->deleteWidgetFromList(averOverVelocityWidget);
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
    left_hand_list->appendWidget(averOverTimeWidget);

    // - pokazujemy -
    averOverTimeWidget->setVisible(true);
}

// -----------------------------------------------------------------------------------
void body::closeAOTSection()
{
    // - znikamy -
    averOverTimeWidget->setVisible(false);

    // - odpinamy od vboxa -
    left_hand_list->deleteWidgetFromList(averOverTimeWidget);

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
    left_hand_list->appendWidget(SpectralIndexWidget);

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
    left_hand_list->deleteWidgetFromList(SpectralIndexWidget);

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
    left_hand_list->appendWidget(exDynspWidget);
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
    left_hand_list->deleteWidgetFromList(exDynspWidget);
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
    left_hand_list->appendWidget(calibrateWidget);
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
    left_hand_list->deleteWidgetFromList(calibrateWidget);
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
    QObject::connect(calibrateWidget->cancel, SIGNAL(clicked()), this, SLOT(closeWDSection()));
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
