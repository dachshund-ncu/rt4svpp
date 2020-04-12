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

using namespace std;
// -- konstruktor klasy programu --
body::body(const char * nazwa)
{
    srand(QDateTime::currentDateTime().toTime_t());
    Q_INIT_RESOURCE(resources);

    // -- ustawiamy rozmiary okna --
    window.setGeometry(300,300,300,720);

    // -- ustawiamy tytul okna --
    window.setWindowTitle("RT4SV++");

    // -- sizepolicy --
    load_data.setMaximumSize(10000,10000);
    dynamic_spectrum.setMaximumSize(10000,10000);
    kill_dynspec.setMaximumSize(10000,10000);
    kill_singspec.setMaximumSize(10000,10000);
    integrate_button.setMaximumSize(10000,10000);
    quit.setMaximumSize(10000,10000);
    aver_over_velocity.setMaximumSize(10000,10000);
    aver_over_time.setMaximumSize(10000,10000);
    spectral_index.setMaximumSize(10000,10000);
    y_down_border.setMaximumSize(10000,30);
    y_up_border.setMaximumSize(10000,30);
    x_left_border.setMaximumSize(10000,30);
    x_right_border.setMaximumSize(10000,30);
    Ibut.setMaximumSize(10000,30);
    Vbut.setMaximumSize(10000,30);
    LHCbut.setMaximumSize(10000,30);
    RHCbut.setMaximumSize(10000,30);
    single_spectrum.setMaximumSize(10000,10000);
    spectral_index.setMaximumSize(10000,10000);
    list_of_observations->setMaximumSize(10000,10000);
    save_plots_on_single_spectrum.setMaximumSize(10000,10000);
    display_plot_on_single_spectrum.setMaximumSize(10000,10000);
    set_default_range_button.setMaximumSize(10000,10000);
    erase_last_graph.setMaximumSize(10000,10000);
    flag.setMaximumSize(10000,30);
    rotate.setMaximumSize(10000,30);
    make_lcs_button.setMaximumSize(10000,30);
    reload.setMaximumSize(10000,10000);
    rotate_minus.setMaximumSize(10000,30);
    save_rotation.setMaximumSize(10000,30);
    number_of_rotated_channels_texted.setMaximumSize(100,30);
    calibrate.setMaximumSize(10000,10000);
    load_caltab_l1.setMaximumSize(10000,30);
    load_caltab_r1.setMaximumSize(10000,30);
    start_calibration.setMaximumSize(10000,30);
    caltab_l1_path.setMaximumSize(10000,30);
    caltab_r1_path.setMaximumSize(10000,30);
    toggle_calibration_button.setMaximumSize(10000,10000);
    WD.setMaximumSize(10000,10000);
    open_rms_section.setMaximumSize(10000,10000);
    kill_rms_section.setMaximumSize(10000,10000);
    recalculate_integration.setMaximumSize(10000,10000);


    load_data.setMinimumSize(0,0);
    dynamic_spectrum.setMinimumSize(0,0);
    kill_dynspec.setMinimumSize(0,0);
    integrate_button.setMinimumSize(0,0);
    quit.setMinimumSize(0,0);
    aver_over_velocity.setMinimumSize(0,0);
    aver_over_time.setMinimumSize(0,0);
    spectral_index.setMinimumSize(0,0);
    y_down_border.setMinimumSize(0,0);
    y_up_border.setMinimumSize(0,0);
    x_left_border.setMinimumSize(0,0);
    x_right_border.setMinimumSize(0,0);
    Ibut.setMinimumSize(0,0);
    Vbut.setMinimumSize(0,0);
    LHCbut.setMinimumSize(0,0);
    RHCbut.setMinimumSize(0,0);
    single_spectrum.setMinimumSize(0,0);
    spectral_index.setMinimumSize(0,0);
    kill_singspec.setMinimumSize(0,0);
    save_plots_on_single_spectrum.setMinimumSize(0,0);
    display_plot_on_single_spectrum.setMinimumSize(0,0);
    set_default_range_button.setMinimumSize(0,0);
    erase_last_graph.setMinimumSize(0,0);
    flag.setMinimumSize(0,0);
    rotate.setMinimumSize(0,0);
    make_lcs_button.setMinimumSize(0,0);
    reload.setMinimumSize(0,0);
    rotate_minus.setMinimumSize(0,0);
    save_rotation.setMinimumSize(0,0);
    number_of_rotated_channels_texted.setMinimumSize(0,0);
    calibrate.setMinimumSize(0,0);
    load_caltab_l1.setMinimumSize(0,0);
    load_caltab_r1.setMinimumSize(0,0);
    start_calibration.setMinimumSize(0,0);
    toggle_calibration_button.setMinimumSize(0,0);
    WD.setMinimumSize(0,0);
    open_rms_section.setMinimumSize(0,0);
    kill_rms_section.setMinimumSize(0,0);
    recalculate_integration.setMinimumSize(0,0);
    //x_right_border.setMaximumSize(10000,10000);
    // -- dodajemy do layoutu przyciski --
    /*
    grid.addWidget(&load_data, 0, 0);
    grid.addWidget(&dynamic_spectrum, 1, 0);
    grid.addWidget(&single_spectrum, 2, 0);
    grid.addWidget(&integrate_button,3, 0);
    grid.addWidget(&aver_over_velocity,4, 0);
    grid.addWidget(&aver_over_time,5, 0);
    grid.addWidget(&spectral_index, 6, 0);
    grid.addWidget(&quit,7, 0);
    */
    QFont f( "Arial", 10, QFont::Bold);
    // -- ustalamy teksty naszych labelow --
    load_data_section_label.setText("Loading");
    load_data_section_label.setFont(f);
    wiev_data_section_label.setText("Visualisation");
    wiev_data_section_label.setFont(f);
    export_data_section_label.setText("Export & analysis");
    export_data_section_label.setFont(f);
    others_section_label.setText("Others");
    others_section_label.setFont(f);

    //loaders.setTitle("loaders");
    //loaders.setVisible(true);
    //loaders_layout.addWidget(&reload);
    //loaders_layout.addWidget(&load_data);
    //loaders_layout.addStretch(1);
    //loaders.setLayout(&loaders_layout);
    // -- dodajemy do głównego paska przycisków --
    //vbox_main.addWidget(butters);

    vbox_main.addWidget(&load_data_section_label);
    //vbox_main.addWidget(&loaders);
    vbox_main.addWidget(&reload);
    vbox_main.addWidget(&load_data);

    vbox_main.addWidget(&wiev_data_section_label);
    vbox_main.addWidget(&dynamic_spectrum);
    vbox_main.addWidget(&single_spectrum);
    vbox_main.addWidget(&open_rms_section);

    vbox_main.addWidget(&export_data_section_label);
    vbox_main.addWidget(include_pytime);
    vbox_main.addWidget(&integrate_button);
    vbox_main.addWidget(&aver_over_velocity);
    vbox_main.addWidget(&aver_over_time);
    vbox_main.addWidget(&spectral_index);
    vbox_main.addWidget(&WD);

    vbox_main.addWidget(&others_section_label);
    vbox_main.addWidget(&calibrate);
    vbox_main.addWidget(&quit);

    grid.addLayout(&vbox_main, 0,0,9,1);
    grid.setColumnStretch(0,1);



    // -- dodajemy napis do przycisku --
    dynamic_spectrum.setText("Dynamic spectrum");
    single_spectrum.setText("Single spectrum");
    load_data.setText("Load AVR files");
    integrate_button.setText("Integrate");
    quit.setText("Quit");
    aver_over_time.setText("Aver over time");
    aver_over_velocity.setText("Aver over velocity");
    spectral_index.setText("Spectral index");
    make_lcs_button.setText("Make lc");
    rotate.setText("Rotate +");
    rotate_minus.setText("Rotate -");
    save_rotation.setText("Save rotation");
    flag.setText("Flag");
    reload.setText("Reload");
    calibrate.setText("Calibrate");
    load_caltab_l1.setText("Load LHC caltab");
    load_caltab_r1.setText("Load RHC caltab");
    start_calibration.setText("START");
    WD.setText("Export file for dynamic spectrum");
    open_rms_section.setText("RMS, Tsys, Sint vs time");

    // -- ustalamy ikony --
    //quit.setIcon(QIcon(":/images/exit.png"));
    // -- dodajemy layout do okna --
    window.setLayout(&grid);


    // -- connectujemy przycisk do slotu --
    QObject::connect(&quit, SIGNAL(clicked()), qApp, SLOT(quit()), Qt::QueuedConnection); // wylaczanie
    QObject::connect(&load_data, SIGNAL(clicked()), this, SLOT(load_time_series()));
    //QObject::connect(&integrate_button, SIGNAL(clicked()), this, SLOT(integrate_time_series()));
    QObject::connect(&integrate_button, SIGNAL(clicked()), this, SLOT(calculate_integrate_for_time_series_with_buttons()));
    QObject::connect(&single_spectrum, SIGNAL(clicked()), this, SLOT(display_single_spectrum()));
    QObject::connect(&dynamic_spectrum, SIGNAL(clicked()), this, SLOT(display_dynamic_spectrum()));
    //QObject::connect(&aver_over_velocity, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity()));
    QObject::connect(&aver_over_velocity, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity_for_time_series_with_buttons()));
    QObject::connect(&aver_over_time, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time_for_time_series_with_buttons()));
    //QObject::connect(&aver_over_time, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time()));
    //QObject::connect(&spectral_index, SIGNAL(clicked()), this, SLOT(calculate_spectral_index()));
    QObject::connect(&spectral_index, SIGNAL(clicked()), this, SLOT(calculate_spectral_index_for_time_series_with_buttons()));
    QObject::connect(&reload, SIGNAL(clicked()), this, SLOT(reload_slot()));
    QObject::connect(&calibrate, SIGNAL(clicked()), this, SLOT(open_cal_layout()));
    QObject::connect(&WD, SIGNAL(clicked()), this, SLOT(open_dynspectum_layout()));
    QObject::connect(&open_rms_section, SIGNAL(clicked()), this, SLOT(open_rms_section_slot()));
    // -- probojemy czytac liste --
    if (strncmp(nazwa, "", 300) == 0)
    {
        lista.open("lista");
        if (lista.good())
        {
            read_time_series();
            list_filename = "lista";
            display_dynamic_spectrum();

        }
        else
        {
            lista.open("list");
            if (lista.good())
            {
                read_time_series();
                list_filename = "lista";
                display_dynamic_spectrum();
            }
        }
     }
    else
    {

        lista.open(nazwa);
        if (lista.good())
        {
            QFile plik;
            QString nazwa_plikueeee;
            nazwa_plikueeee = QString::fromStdString(nazwa);
            QFileInfo info(nazwa_plikueeee);
            if (info.absolutePath().toStdString() != "")
            {
                working_directory = info.absolutePath().toStdString();

            }
            read_time_series();
            list_filename = string(nazwa);
            display_dynamic_spectrum();

        }
    }

    // -- pokazujemy okno --

    I_on_rms->setVisible(false);
    V_on_rms->setVisible(false);
    LHC_on_rms->setVisible(false);
    RHC_on_rms->setVisible(false);
    show_pts->setVisible(false);
    show_lns->setVisible(false);
    window.show();
}

void body::display_single_spectrum()
{
    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (dynamic_spectrum_opened == 1)
    {
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        QMessageBox::information(&window, tr("Error!"), tr("Please, close the DYNAMIC SPECTRUM window"));
        return;
    }
    else if (rms_section_opened == 1)
    {
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        QMessageBox::information(&window, tr("Error!"), tr("Please, close the RMS, Sint & Tsys window"));
        return;
    }
    spectrum.clearGraphs();
    spectrum.replot();
    single_spectrum_opened=1;
    // ustawiamy widzialnosc
    spectrum.setVisible(true);
    kill_singspec.setVisible(true);
    list_of_observations->setVisible(true);
    // przygotowujemy dane
    unsigned int marker = 0;
    // wektor z danymi
    QVector < double > x(n_chanslst[marker]), y(n_chanslst[marker]);
    // zapelniamy wektor
    for(unsigned int i = 0; i < Ilst[marker].size(); i++)
    {
        x[i] = VELlst[marker][i];
        y[i] = Ilst[marker][i];
    }
    // -- dodajemy grafike --
    spectrum.addGraph();
    // -- dodajemy do grafiki dane --
    spectrum.graph(0)->setData(x,y);
    // -- zarzadzamy labelami --
    spectrum.xAxis->setLabel("Vel");
    spectrum.yAxis->setLabel("Flux density (Jy)");
    // -- zarzadzamy rangeami --
    //spectrum.xAxis->setRange(*min_element(x.begin(), x.end()), *max_element(x.begin(), x.end()));
    //spectrum.yAxis->setRange(*min_element(y.begin(), y.end()), *max_element(y.begin(), y.end()));
    double veldiff = *max_element(x.begin(), x.end()) - *min_element(x.begin(), x.end());
    spectrum.xAxis->setRange(*min_element(x.begin(), x.end()) - 0.05 * veldiff, *max_element(x.begin(), x.end())  + 0.05 * veldiff);
    spectrum.yAxis->setRange(*min_element(y.begin(), y.end()) - 0.05 * (*max_element(y.begin(), y.end())), *max_element(y.begin(), y.end())  + 0.05 * (*max_element(y.begin(), y.end())));
    // -- pokazujemy ticki na gornej osi --
    spectrum.xAxis2->setVisible(true);
    spectrum.yAxis2->setVisible(true);
    spectrum.xAxis2->setTickLabels(false);
    spectrum.yAxis2->setTickLabels(false);
    save_plots_on_single_spectrum.setVisible(true);
    display_plot_on_single_spectrum.setVisible(true);
    set_default_range_button.setVisible(true);
    erase_last_graph.setVisible(true);
    // -- dodajemy interakcje --
    spectrum.setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);

    spectrum.axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    spectrum.axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    spectrum.axisRect()->setRangeZoomAxes(spectrum.xAxis, spectrum.yAxis);
    spectrum.setSelectionRectMode(QCP::srmZoom);

    // -- ustawiamy visibility --

    // -- ustawiamy jakies parametry ramki --
    /*
    ramka.setFrameStyle(QFrame::Sunken);
    ramka.setFrameShape(QFrame::StyledPanel);
    ramka.setLineWidth(3);
    ramka.setMidLineWidth(3);
    */
    // -- tworzymy przycisk - do ubijania ramki --
    kill_singspec.setText("Kill single spectrum --->");
    save_plots_on_single_spectrum.setText("Save plots from single spectrum");
    display_plot_on_single_spectrum.setText("Display plot on single spectrum");
    set_default_range_button.setText("Set default range");
    erase_last_graph.setText("Erase last graph");

    // -- dodajemy przycisk do gridu --
    //grid.addWidget(&kill_singspec, 8,0);
    vbox_main.addWidget(&kill_singspec);
    grid.addWidget(&spectrum, 0,1,9,3);


    // -- connectujemy z metodami
    if (single_spectrum_buttons_connected == 0)
    {
        //QObject::connect(list_of_observations, SIGNAL(activated()), this, SLOT(combo_box_display()));
        QObject::connect(&kill_singspec, SIGNAL(clicked()), this, SLOT(kill_single_spectrum()));
        QObject::connect(&display_plot_on_single_spectrum, SIGNAL(clicked()), this, SLOT(combo_box_display()));
        QObject::connect(&set_default_range_button, SIGNAL(clicked()), this, SLOT(set_default_range()));
        QObject::connect(&erase_last_graph, SIGNAL(clicked()), this, SLOT(remove_selected_graph()));
        QObject::connect(&save_plots_on_single_spectrum, SIGNAL(clicked()), this, SLOT(save_plots_from_single_spectrum()));
        single_spectrum_buttons_connected = 1;
    }
    // -- dodajemy combo box z obserwacjami do layoutu --
    //if(layout_single_loaded == 0)
    //{
    //vbox_single->addWidget(list_of_observations);
        //layout_single_loaded = 1;

    grid.addWidget(list_of_observations, 0,4,1,1);
    grid.addWidget(&save_plots_on_single_spectrum, 1,4,1,1);
    grid.addWidget(&display_plot_on_single_spectrum, 2,4,1,1);
    grid.addWidget(&set_default_range_button, 3,4,1,1);
    grid.addWidget(&erase_last_graph, 4,4,1,1);
    if(combo_loaded == 0)
    {
        for(int i = 0; i < mjdlst.size(); i++)
        {
            list_of_observations->addItem(QString::fromStdString(to_string(i+1) + "   " + to_string(mjdlst[i])));
        }
        combo_loaded=1;
    }
    //QObject::connect(list_of_observations, SIGNAL(activated()), this, SLOT(combo_box_display()));
    //grid.ddWidget(list_of_observations,1,1,0,1);
    //QPoint pos = window.mapToGlobal(QPoint(0,0));
    window.setGeometry(window.x(), window.y(),1360,720);
    window.show();
    n_graphs_on_single_spec = 1;
    spectrum.graph(0)->setPen(QPen(Qt::red));
    spectrum.replot();

    /*
    // -- do menu --
    spectrum.setContextMenuPolicy(Qt::CustomContextMenu);
    connect(&spectrum, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(menu_request(QPoint)));
    */
    numbers_of_epochs_on_single_spec.push_back(0);
    grid.setColumnStretch(0,1);
    grid.setColumnStretch(1,3);
    grid.setColumnStretch(2,3);
    grid.setColumnStretch(3,3);
    grid.setColumnStretch(4,1);

}

void body::kill_single_spectrum()
{
    // -- usuwamy widgety z layoutu --
    grid.removeWidget(&spectrum);
    //grid.removeWidget(&kill_singspec);
    grid.removeWidget(list_of_observations);
    grid.removeWidget(&save_plots_on_single_spectrum);
    grid.removeWidget(&display_plot_on_single_spectrum);
    grid.removeWidget(&erase_last_graph);
    grid.removeWidget(&set_default_range_button);
    vbox_main.removeWidget(&kill_singspec);


    // -- czyscimy plotno --
    //spectrum.graph(0)->data().clear();
    //spectrum.clearGraphs();
    spectrum.replot();
    // -- ukrywamy widgety --
    spectrum.setVisible(false);
    kill_singspec.setVisible(false);
    list_of_observations->setVisible(false);
    save_plots_on_single_spectrum.setVisible(false);
    display_plot_on_single_spectrum.setVisible(false);
    set_default_range_button.setVisible(false);
    erase_last_graph.setVisible(false);
    spectrum.clearGraphs();
    // -- zmieniamy rozmiar okna --
    window.setGeometry(window.x(), window.y(),300,720);
    window.setLayout(&grid);
    grid.update();
    window.show();
    single_spectrum_opened=0;
    n_graphs_on_single_spec = 0;
    spectrum.replot();
    numbers_of_epochs_on_single_spec.clear();
    grid.setColumnStretch(0,1);
    grid.setColumnStretch(1,0);
    grid.setColumnStretch(2,0);
    grid.setColumnStretch(3,0);
    grid.setColumnStretch(4,0);
    list_of_observations->clear();
    combo_loaded = 0;
    window.setGeometry(window.x(), window.y(),300,720);
}

// -- czyta plik o podanej nazwie --
void body::czytaj(const char* nazwa_pliku23)
{
  check_if_loading_not_interrupted = 0;
  // otwieramy obiekt z czytanym plikiem
  avr.open(nazwa_pliku23);
  //avr.clear();
  //avr.seekg(0);
  //cout << nazwa_pliku23 << endl;
  string bufor, bufor2; // bufor do jednej linii tekstu
  // --- CZYTAMY EL I AZ ---
  double elaz[4]; // do ladowania wartosci
  // pomijamy trzy linijki w pliku
  for (int i = 0; i < 3; i++)
  {
    getline(avr, bufor);
  }
  // odczytujemy kat elewacji
  for(int i = 0; i < 4; i++)
  {
    avr >> elaz[i]; // azymut to 0 i 1, el to 2 i 3
  }
  // zapisujemy wyniki do danych klasy
  az = elaz[0] + elaz[1] / 60.0;
  el = elaz[2] + elaz[3] / 60.0;
  // przesuwamy kursor z powrotem na początek pliku
  avr.seekg(0);
  // --- KONIEC CZYTANIA EL I AZ ---

  // --- CZYTAMY RA I DEC ---
  double radec[6]; // do przechowywania ra i dec
  getline(avr,bufor); // pomijamy pierwsza linie
  // krotka petla czytajaca co potrzeba
  for(int i = 0; i < 6; i++)
  {
    avr >> radec[i]; // ra to 0,1,2 dec to 3,4,5
  }
  // zapisujemy wartosci ra i dec
  ra = radec[0] + radec[1] / 60.0 + radec[2] / 3600.0;
  dec = radec[3] + radec[4] / 60.0 + radec[5] / 3600.0;
  // przesuwamy kursor na poczatek
  avr.seekg(0);
  // --- KONIEC CZYTANIA RA I DEC ---

  // --- CZYTAMY RESTF I VLSR ---
  double dane[5]; // tymczasowa tablica
  // pomijamy 10 linii
  for(int i = 0; i < 10; i++)
  {
    getline(avr, bufor);
  }
  // czytamy 11
  for(int i = 0; i < 5; i++)
  {
    avr >> dane[i];
  }

  vlsr = dane[3];
  freq = dane[4];
  wst = dane[1];
  n_chans = dane[0];

  getline(avr, bufor);
  avr >> srcname;

  // przesuwamy kursor z powrotem na początek pliku
  avr.seekg(0);
  // --- KONIEC CZYTANIA RESTF I VLSR ---

  // --- CZYTAMY DATE ---
  for(int i = 0; i < 5; i++)
  {
    getline(avr, bufor);
    //cout << bufor << endl;
  }

  double day, month, year;
  //cout << "jestem" << endl;
  //cout << bufor.substr(4,2) << endl;
  day = stod(bufor.substr(4,2));
  month = stod(bufor.substr(6,2));
  year = stod("20" + bufor.substr(8,2));
  //cout << "nie jestem" << endl;
  // co
  for(int i = 0;i<8;i++)
  {
      getline(avr,bufor);
  }
  double hour, min, sec;
  avr >> hour;
  avr >> min;
  avr >> sec;
  double hour2;
  double day2;
  //cout << hour << "  " << min << "  " << sec << endl;
  hour2 = hour + min / 60.0 + sec / 3600.0;
  day2 = day + hour2 / 24.0;
  //string dayp;
  //dayp = bufor.substr(4,2);
  //cout << day << month << year <<endl;
  jd = JD(year, month, day2);
  mjd = jd - 2400000.5;
  double decyr = decimalyear(year, month, day2);
  // kursor
  avr.seekg(0);
  // --- KONIEC CZYTANIA DATY ---

  // -- ZAPELNIAMY HEADERY --
  string headertmp = "";
  for (int i = 0; i < 14; i++)
  {
      getline(avr,bufor);
      headertmp = headertmp+bufor + "\n";
  }
  //header.push_back(headertmp);
  //headertmp = "";
  avr.seekg(0);

  // --- ZAPELNIAMY TSYS ---
  double tsystmp;
  string bufortsystmp;
  for(int i = 0; i < 6; i++)
  {
    getline(avr, bufortsystmp);
  }
  avr >> tsystmp;
  avr.seekg(0);
  tsyslst.push_back(tsystmp);

  // --- ZAPEŁNIAMY KONTERERY ---
  vector < double > tab; // do jednej linii w pliku
  double dbuf; // do jednej liczby
  //char spr;
  // petla czytajaca:

  // -- I --
    for(int i = 0; i < 17; i++)
      getline(avr, bufor); // pomijamy 17 linijek i czytamy dalej

    for(int i = 0; i < 24; i++)
    {
        I.push_back(0.0); // pominelismy 23 kanaly obserwacji, zapelniamy je zamiast tego zerami
    }
    for(int k = 0; k < 250; k++)
    {
      //avr.seekg(-1, ios::cur); // cofamy kursor o 1 pozycje (na poczatek linii)
      getline(avr, bufor); // czytamy linie
      stringstream ss(bufor); // taka zmienna do konwertowania
      while (ss >> dbuf)
        I.push_back(dbuf / 1000.0); // zapisujemy wiersz do kontenera tab
    }
    for(int i = 0; i < 24; i++)
    {
        I.push_back(0.0);
    }
    for(int i = 0; i < 3; i++)
      getline(avr, bufor); // pomijamy 3 linijki i czytamy dalej

    //cout << I.size() << endl;
    // -- V --
    for(int i = 0; i < 17; i++)
      getline(avr, bufor); // pomijamy 14 linijek i czytamy dalej

    for(int i = 0; i < 24; i++)
    {
        V.push_back(0.0); // pominelismy 23 kanaly obserwacji, zapelniamy je zamiast tego zerami
    }
    for(int k = 0; k < 250; k++)
    {

      getline(avr, bufor); // czytamy linie
      stringstream ss(bufor); // taka zmienna do konwertowania
      while (ss >> dbuf)
        V.push_back(dbuf / 1000.0); // zapisujemy wiersz do kontenera tab
     }

      for(int i = 0; i < 24; i++)
      {
          V.push_back(0.0);
      }
      for(int i = 0; i < 3; i++)
        getline(avr, bufor); // pomijamy 3 linijki i czytamy dalej

     //cout << V.size() << endl;

    // -- LHC --
    for(int i = 0; i < 17; i++)
      getline(avr, bufor); // pomijamy 17 linijek i czytamy dalej

    for(int i = 0; i < 24; i++)
    {
        LHC.push_back(0.0); // pominelismy 24 kanaly obserwacji, zapelniamy je zamiast tego zerami
    }
    for(int k = 0; k < 250; k++)
    {
      getline(avr, bufor); // czytamy linie
      stringstream ss(bufor); // taka zmienna do konwertowania
      while (ss >> dbuf)
        LHC.push_back(dbuf / 1000.0); // zapisujemy wiersz do kontenera tab
    }

    for(int i = 0; i < 24; i++)
    {
        LHC.push_back(0.0);
    }

    for(int i = 0; i < 3; i++)
      getline(avr, bufor); // pomijamy 3 linijki i czytamy dalej

    //cout << LHC.size() << endl;

    // -- RHC --
    for(int i = 0; i < 17; i++)
      getline(avr, bufor); // pomijamy 14 linijek i czytamy dalej

    for(int i = 0; i < 24; i++)
    {
        RHC.push_back(0.0); // pominelismy 23 kanaly obserwacji, zapelniamy je zamiast tego zerami
    }
    for(int k = 0; k < 250; k++)
    {
        getline(avr, bufor); // czytamy linie
        stringstream ss(bufor); // taka zmienna do konwertowania
        while (ss >> dbuf)
          RHC.push_back(dbuf / 1000.0); // zapisujemy wiersz do kontenera tab
    }

    for(int i = 0; i < 24; i++)
    {
         RHC.push_back(0.0);
    }

  //cout << RHC.size() << endl;

  if (I.size() < 512)
  {
      return;
  }
  // ZAMYKAMY PLIK
  avr.close();

  // --- Tworzymy tablice z predkosciami radialnymi ---
  double c = 299792.458; // km/s
  double beta = vlsr / c;
  double gamma = 1.0 / sqrt(1.0 - beta*beta);
  double fcentr = freq / (gamma * (1.0 - beta));
  double fbegin = fcentr - wst / 2.0;
  double fend = fcentr + wst / 2.0;
  double h = (fend - fbegin) / 2048.0;
  vector < double > freqs;
  for (int i = 0; i < n_chans; i++)
  {
    freqs.push_back(fbegin + h*i);
  }
  for (int i = 0; i < n_chans; i++)
  {
    VEL.push_back(c * ((freqs[i] - freq) / freq));
  }
  for (int i = 0; i < n_chans; i++)
  {
    CHAN.push_back(i+1);
  }

  // --- liczymy rms ---
  double suma = 0.0;
  //double n = 100.0;
  if(chan4rms_loaded == 0)
  {
      rms_start_channel1 = 100.0;
      rms_end_channel1 = 400.0;
      rms_start_channel2 = CHAN.size() - 400.0;
      rms_end_channel2 = CHAN.size() - 100.0;
  }

  // -- rms I --
  int n = 0;
  for (int i = rms_start_channel1; i < rms_end_channel1; i++)
  {
    suma = suma + I[i]*I[i];
    n = n+1;
  }
  for (int i = rms_start_channel2; i < rms_end_channel2; i++)
  {
    suma = suma + I[i]*I[i];
    n = n+1;
  }
  rms = sqrt(suma / (n-1));

  for(int i = 0; i < n_chans; i++)
  {
    ERR.push_back(rms);
  }

  // -- rms V --
  n = 0;
  suma = 0.0;
  for (int i = rms_start_channel1; i < rms_end_channel1; i++)
  {
    suma = suma + V[i]*V[i];
    n = n+1;
  }
  for (int i = rms_start_channel2; i < rms_end_channel2; i++)
  {
    suma = suma + V[i]*V[i];
    n = n+1;
  }
  rms = sqrt(suma / (n-1));

  for(int i = 0; i < n_chans; i++)
  {
    VERR.push_back(rms);
  }

  // -- rms LHC --
  n = 0;
  suma = 0.0;
  for (int i = rms_start_channel1; i < rms_end_channel1; i++)
  {
    suma = suma + LHC[i]*LHC[i];
    n = n+1;
  }
  for (int i = rms_start_channel2; i < rms_end_channel2; i++)
  {
    suma = suma + LHC[i]*LHC[i];
    n = n+1;
  }
  rms = sqrt(suma / (n-1));

  for(int i = 0; i < n_chans; i++)
  {
    LHCERR.push_back(rms);
  }

  // -- rms RHC --
  n = 0;
  suma = 0.0;
  for (int i = rms_start_channel1; i < rms_end_channel1; i++)
  {
    suma = suma + RHC[i]*RHC[i];
    n = n+1;
  }
  for (int i = rms_start_channel2; i < rms_end_channel2; i++)
  {
    suma = suma + RHC[i]*RHC[i];
    n = n+1;
  }
  rms = sqrt(suma / (n-1));

  for(int i = 0; i < n_chans; i++)
  {
    RHCERR.push_back(rms);
  }

  // -- zapelniamy stale kontenery --
  jdlst.push_back(jd);
  mjdlst.push_back(mjd);
  ellst.push_back(el);
  azlst.push_back(az);
  declst.push_back(dec);
  ralst.push_back(ra);
  freqlst.push_back(freq);
  vlsrlst.push_back(vlsr);
  wstlst.push_back(wst);
  n_chanslst.push_back(n_chans);
  rmslst.push_back(rms);
  dlst.push_back(day);
  mlst.push_back(month);
  ylst.push_back(year);
  hrlst.push_back(hour);
  minutelst.push_back(min);
  seclst.push_back(sec);
  yrlst.push_back(decyr);

  // -- konstruujemy pytime format --
  string time_in_isoformat, yearstr, monthstr, daystr, hourstr, minutestr, secondstr;

  // zapisujemy czas w isoformacie (YYYY-MM-DD)
  //year
  yearstr = to_string((int)year);
  // month
  if (to_string((int)month).length() == 1)
      monthstr = string("0")+to_string((int)month);
  else
      monthstr = to_string((int)month);
  // day
  if (to_string((int)day).length() == 1)
      daystr = string("0") + to_string((int)day);
  else
      daystr = to_string((int)day);
  // hour
  if (to_string((int)hour).length() == 1)
      hourstr = string("0") + to_string((int)hour);
  else
      hourstr = to_string((int)hour);
  // minute
  if (to_string((int)min).length() == 1)
      minutestr = string("0") + to_string((int)min);
  else
      minutestr = to_string((int)min);
  // second
  if (to_string((int)sec).length() == 1)
      secondstr = string("0") + to_string(sec);
  else
      secondstr = to_string(sec);

  // zapisujemy do time...
  time_in_isoformat = yearstr + string("-") + monthstr + string("-") + daystr + string("T") + hourstr + string(":") + minutestr + string(":") + secondstr.replace(2,1,string("."));
  pytime_format.push_back(time_in_isoformat);

  // -- i podwojne --
  headerlst.push_back(headertmp);
  LHClst.push_back(LHC);
  RHClst.push_back(RHC);
  Vlst.push_back(V);
  Ilst.push_back(I);
  VELlst.push_back(VEL);
  CHANlst.push_back(CHAN);
  ERRlst.push_back(ERR);
  VERRlst.push_back(VERR);
  LHCERRlst.push_back(LHCERR);
  RHCERRlst.push_back(RHCERR);
  // -- czyscimy tymczasowe kontenery --
  header.clear();
  LHC.clear();
  RHC.clear();
  V.clear();
  I.clear();
  VEL.clear();
  CHAN.clear();
  ERR.clear();
  VERR.clear();
  LHCERR.clear();
  RHCERR.clear();

  check_if_loading_not_interrupted = 1;
}

// -- czyta pliki z podanej listy plikow --
void body::read_time_series_for_list(QStringList lista_plikow)
{
    // przed czytaniem - czyscimy tablice -
    jdlst.clear();
    mjdlst.clear();
    ellst.clear();
    azlst.clear();
    declst.clear();
    ralst.clear();
    freqlst.clear();
    vlsrlst.clear();
    wstlst.clear();
    n_chanslst.clear();
    rmslst.clear();
    dlst.clear();
    mlst.clear();
    ylst.clear();
    hrlst.clear();
    minutelst.clear();
    seclst.clear();
    pytime_format.clear();
    tsyslst.clear();

    // i kontenery tez
    headerlst.clear();
    LHClst.clear();
    RHClst.clear();
    Vlst.clear();
    Ilst.clear();
    VELlst.clear();
    CHANlst.clear();
    ERRlst.clear();
    VERRlst.clear();
    LHCERRlst.clear();
    RHCERRlst.clear();
    avrnames.clear();
    window.show();

    // -- i tablice z rotowanymi obserwacjami --
    rotated_spectras.clear();

    // -- pobieramy chan4rms jeśli możemy --
    read_chan4rms();

    flagged_files_loaded = read_flagged_files();


    string bufor_do_listy; // maly bufor do przechowywania linii z listy
    int marker = 0; // maly marker, bedzie nam potrzebny

    // -- progressbar --
    //cout << "startujemy" << endl;
    QProgressDialog postep;//(&window);
    postep.setLabelText("Loading files... please wait");
    int pasek_postepu = 0;
    postep.setMinimum(0);
    postep.setMaximum(lista_plikow.size());
    postep.setVisible(true);
    //cout << "zadeklarowany pasek" << endl;
    // - petla wczytujaca pliki z obserwacjami -
    //cout << lista.good() << endl;
    //getline(lista, bufor_do_listy);
    //cout << bufor_do_listy << endl;

    for(int i = 0; i < lista_plikow.size(); i++)
    {
      bufor_do_listy = lista_plikow[i].toStdString();

      // jesli jest zerowej dlugosci, to mamy koniec pliku i wywalamy z petli
      if(bufor_do_listy.size() < 1)
      {
        break;
      }
      // czytamy plik z listy
      if(!check_if_flagged(bufor_do_listy))
      {
          // jesli check if flagged zwraca false to czytamy
          this->czytaj((bufor_do_listy).c_str());

          // sprawdzamy, czy ładowanie nie zostało przerwane w trakcie
         if (check_if_loading_not_interrupted == 0)
             throw 2; // jeśli tak, wyrzucamy exception

          avrnames.push_back(bufor_do_listy);
          // wypisujemy podstawowe dane o obserwacji
          cout << "------>   [" << marker+1 << "]    " << "MJD: " << mjdlst[marker] << " date: " << ylst[marker] << " " << mlst[marker] << " " << dlst[marker] << "   rms: " << rmslst[marker] << endl;
         // inkrementujemy marker
          marker = marker + 1;

      }
      else
      {
          // jesli czeck if flagged zwraca true to pomijamy
          cout << "------> " << bufor_do_listy << " is flagged, so i will not read it" << endl;
      }
      pasek_postepu = pasek_postepu + 1;
      //cout << "zwiekszamy postep paska" << endl;
      postep.setValue(postep.value()+1);
      QCoreApplication::processEvents();

    }

    max_range_vel_index = VELlst[0].size()-1;
    max_obs_number = mjdlst.size()-1;
    rozmiar_w_x = mjdlst.size();
    rozmiar_w_y = CHANlst[0].size();
    string title;
    title = string("RT4SV++: ");
    title.append(srcname);
    window.setWindowTitle(QString::fromStdString(title));
    loaded_data = 1;
    made_rotation = 0;

    // -- obsloga flag --
    if (flagged_files_loaded)
        cout << endl << "----> Loaded flags" << endl;

    if (flagged_files_on_spectrum == 1)
    {
        for(int i = 0; i < flagi.size(); i++)
        {
            dynamic_spectrum_pl.removeItem(flagi[i]);
        }
        flagi.clear();
        flagged_files_on_spectrum = 0;
        flags_number = 0;

    }
    if (dynamic_spectrum_opened)
        display_dynamic_spectrum();

    calibration_done = 0;
    if (calibration_section_opened == 1)
        close_cal_layout();

    // -- jeśli mamy calconfig.sv --
    caltabs_loaded = 0;
    if(read_calconfig())
    {
        load_l1_caltab(caltab_LHC_path);
        load_r1_caltab(caltab_RHC_path);
        if (caltabs_loaded == 0)
        {
            load_l1_caltab(working_directory + "/" + caltab_LHC_path);
            load_r1_caltab(working_directory + "/" + caltab_RHC_path);
            if (caltabs_loaded == 0)
            {
                QMessageBox::information(&window, tr("Error!"), tr("Found calconfig.sv, but failed to load caltabs!"));
            }
            else
            {
                calibrate_method();
                cout << "----> calconfig.sv found! Calibrating observations from caltabs:" << endl;
                cout << "----> " << working_directory + "/" + caltab_LHC_path << endl;
                cout << "----> " << working_directory + "/" + caltab_RHC_path << endl;
            }

        }
        else
        {
            calibrate_method();
            cout << "----> calconfig.sv found! Calibrating observations from caltabs:" << endl;
            cout << "----> " << caltab_LHC_path << endl;
            cout << "----> " << caltab_RHC_path << endl;
        }


    }
}

// -- czyta pliki z calej listy --
void body::read_time_series()
{
  // przed czytaniem - czyscimy tablice -
  jdlst.clear();
  mjdlst.clear();
  ellst.clear();
  azlst.clear();
  declst.clear();
  ralst.clear();
  freqlst.clear();
  vlsrlst.clear();
  wstlst.clear();
  n_chanslst.clear();
  rmslst.clear();
  dlst.clear();
  mlst.clear();
  ylst.clear();
  hrlst.clear();
  minutelst.clear();
  seclst.clear();
  pytime_format.clear();
  tsyslst.clear();

  // i kontenery tez
  headerlst.clear();
  LHClst.clear();
  RHClst.clear();
  Vlst.clear();
  Ilst.clear();
  VELlst.clear();
  CHANlst.clear();
  ERRlst.clear();
  VERRlst.clear();
  LHCERRlst.clear();
  RHCERRlst.clear();
  avrnames.clear();
  window.show();

  // -- i tablice z rotowanymi obserwacjami --
  rotated_spectras.clear();

  // -- pobieramy chan4rms jeśli możemy --
  read_chan4rms();

  flagged_files_loaded = read_flagged_files();


  string bufor_do_listy; // maly bufor do przechowywania linii z listy
  int marker = 0; // maly marker, bedzie nam potrzebny

  int lista_length = 0;

  while(lista.good())
  {
       // czytamy linie z pliku
       getline(lista, bufor_do_listy);
       lista_length = lista_length + 1;
       //cout << bufor_do_listy << endl;
  }

  // wracamy na początek pliku

  lista.clear();
  lista.seekg(0);//1, ios::beg);
  //cout << lista.tellg() << endl;

  // -- progressbar --
  //cout << "startujemy" << endl;
  QProgressDialog postep;//(&window);
  postep.setLabelText("Loading files... please wait");
  int pasek_postepu = 0;
  postep.setMinimum(0);
  postep.setMaximum(lista_length);
  postep.setVisible(true);
  //cout << "zadeklarowany pasek" << endl;
  // - petla wczytujaca pliki z obserwacjami -
  //cout << lista.good() << endl;
  //getline(lista, bufor_do_listy);
  //cout << bufor_do_listy << endl;

  while(lista.good())
  {

    // czytamy linie z pliku
    //cout << "getline" << endl;
    getline(lista, bufor_do_listy);
    //cout << "po getline" << endl;
    // jesli jest zerowej dlugosci, to mamy koniec pliku i wywalamy z petli
    if(bufor_do_listy.size() < 1)
    {
      break;
    }
    // czytamy plik z listy
    if(!check_if_flagged(bufor_do_listy))
    {
        // jesli check if flagged zwraca false to czytamy
        this->czytaj((working_directory + "/" + bufor_do_listy).c_str());

        // sprawdzamy, czy ładowanie nie zostało przerwane w trakcie
       if (check_if_loading_not_interrupted == 0)
           throw 2; // jeśli tak, wyrzucamy exception (funkcja zostanie przerwana)

        avrnames.push_back(bufor_do_listy);
        // wypisujemy podstawowe dane o obserwacji
        cout << "------>   [" << marker+1 << "]    " << "MJD: " << mjdlst[marker] << " date: " << ylst[marker] << " " << mlst[marker] << " " << dlst[marker] << "   rms: " << rmslst[marker] << endl;
       // inkrementujemy marker
        marker = marker + 1;
    }
    else
    {
        // jesli czeck if flagged zwraca true to pomijamy
        cout << "------> " << bufor_do_listy << " is flagged, so i will not read it" << endl;
    }
    pasek_postepu = pasek_postepu + 1;
    //cout << "zwiekszamy postep paska" << endl;
    postep.setValue(postep.value()+1);
    // by na windowsie też postepowal
    QCoreApplication::processEvents();

  }
  lista.close();
  max_range_vel_index = VELlst[0].size()-1;
  max_obs_number = mjdlst.size()-1;
  rozmiar_w_x = mjdlst.size();
  rozmiar_w_y = CHANlst[0].size();
  string title;
  title = string("RT4SV++: ");
  title.append(srcname);
  window.setWindowTitle(QString::fromStdString(title));
  loaded_data = 1;
  made_rotation = 0;

  // -- obsloga flag --
  if (flagged_files_loaded)
      cout << endl << "----> Loaded flags" << endl;

  if (flagged_files_on_spectrum == 1)
  {
      for(int i = 0; i < flagi.size(); i++)
      {
          dynamic_spectrum_pl.removeItem(flagi[i]);
      }
      flagi.clear();
      flagged_files_on_spectrum = 0;
      flags_number = 0;

  }
  if (dynamic_spectrum_opened)
      display_dynamic_spectrum();

  calibration_done = 0;
  if (calibration_section_opened == 1)
      close_cal_layout();

  // -- jeśli mamy calconfig.sv --
  caltabs_loaded = 0;
  if(read_calconfig())
  {
      load_l1_caltab(caltab_LHC_path);
      load_r1_caltab(caltab_RHC_path);
      if (caltabs_loaded == 0)
      {
          load_l1_caltab(working_directory + "/" + caltab_LHC_path);
          load_r1_caltab(working_directory + "/" + caltab_RHC_path);
          if (caltabs_loaded == 0)
          {
              QMessageBox::information(&window, tr("Error!"), tr("Found calconfig.sv, but failed to load caltabs!"));
          }
          else
          {
              calibrate_method();
              cout << "----> calconfig.sv found! Calibrating observations from caltabs:" << endl;
              cout << "----> " << working_directory + "/" + caltab_LHC_path << endl;
              cout << "----> " << working_directory + "/" + caltab_RHC_path << endl;
          }

      }
      else
      {
          calibrate_method();
          cout << "----> calconfig.sv found! Calibrating observations from caltabs:" << endl;
          cout << "----> " << caltab_LHC_path << endl;
          cout << "----> " << caltab_RHC_path << endl;
      }


  }
}

// -- to samo robi, co read time series - ale po wcisnieciu przycisku --
void body::load_time_series()
{
    AVRNAMES_from_load.clear();
    string nazwa_pliku; // string z nazwa pliku
    QStringList fileName1;// qstring z nazwa pliku
    QString fileName;

    QFileDialog dialog(&window,tr("Select a list of AVR files or just AVR files"), tr(""), tr("All Files (*);;AVR files (*AVR.DAT)"));
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
    //fileName = dialog.getOpenFileName(&window, tr("Select a list of AVR files"), tr(""), tr("All Files (*)")); // qfile dialog
    //fileName = dialog.getOpenFileName();
    //dialog.exec();
    //dialog.close();
    //cout << fileName.toStdString() << endl;
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

    }

    // -- wczytujemy: jeśli nasza lista plików to AVR, wczyta się w try, jeśli to plik z listą - w catch --
    try
    {
        cout << "----> Trying to load AVR files (if multiple files chosen)" << endl;
        this->read_time_series_for_list(fileName1);
        cout << "----> Loaded AVR files" << endl;
        AVRNAMES_from_load = fileName1;
    }
    catch(...)
    {
        avr.close();
        cout << "----> List of files probably chosen, loading from it instead" << endl;
        lista.open(nazwa_pliku.c_str());
        //cout << nazwa_pliku << endl;
        if (lista.good() != true)
        {
            //cout << "----> No such file or directory!" << endl;
            return;
        }
        else
        {
            cout << "----> Starting to load AVR files (list of files)" << endl;
            this->read_time_series();
            cout << "----> Loaded AVR files" << endl;
            list_filename = nazwa_pliku;
        }

    }

    if (single_spectrum_opened == 1)
    {
        list_of_observations->clear();
        combo_loaded = 0;
        display_single_spectrum();
    }
    loaded_data = 1;

}

// -- liczy jd z yr,mnth, day --
double body::JD(double year, double month, double day)
{
  // metoda opisana na: https://gist.github.com/jiffyclub/1294443 (dostep: 25.09.2019, 1:00 UTC)
  // maly tweaking
  double yearp, monthp, A,B,C,D;
  if(month == 1 || month == 2)
  {
    yearp = year - 1.0;
    monthp = month + 12.0;
  }
  else
  {
    yearp = year;
    monthp = month;
  }

  // sprawdzamy jak sie ma nasza data w stosunku do 15 pazdziernika 1582, czyli poczatku kalendarza
  // gregorianskiego

  if (year < 1582.0 || (year == 1582.0 && month < 10.0) || (year == 1582.0 && month < 10.0 && day < 15.0) )
  {
    // przed startem gregorianskiego
    B = 0.0;
  }
  else
  {
    // po starcie gregorianskiego
    A = trunc(yearp / 100.0);
    B = 2.0  - A + trunc(A / 4.0);
  }

  if (yearp < 0.0)
  {
    C = trunc((365.25 * yearp) - 0.75);
  }
  else
  {
    C = trunc((365.25 * yearp));
  }

  D = trunc(30.6001 * (monthp + 1.0));

  jd = B+C+D+day + 1720994.5;
  return jd;


}

double body::decimalyear(double year, double month, double day)
{
    double days_in_year = 365.25;
    vector < int > days_in_month(12);
    days_in_month[0] = 31;
    days_in_month[1] = 28;
    days_in_month[2] = 31;
    days_in_month[3] = 30;
    days_in_month[4] = 31;
    days_in_month[5] = 30;
    days_in_month[6] = 31;
    days_in_month[7] = 31;
    days_in_month[8] = 30;
    days_in_month[9] = 31;
    days_in_month[10] = 30;
    days_in_month[11] = 31;

    // sprawdzamy, czy rok jest przestepny
    if (int(year) % 4 == 0)
    {
        if(int(year) % 100 != 0 || int(year) % 400)
        {
            days_in_month[1] = 29;
            days_in_year = 366.25;
        }

    }

    // liczyny days w tym roku
    double days_into_year = 0.0;
    for(int i = 0; i < int(month)-1; i++)
    {
        days_into_year = days_into_year + double(days_in_month[i]);
    }
    days_into_year = days_into_year + day;

    double decim = year + days_into_year / days_in_year;
    return decim;

}
// -- liczy calke z pojedynczego widma --
void body::integrate_single(int min, int max, unsigned int marker)
{
    double sumI = 0.0;
    double sumV = 0.0;
    double sumLHC = 0.0;
    double sumRHC = 0.0; // suma calki

    double sumIer = 0.0;
    double sumVer = 0.0;
    double sumLHCer = 0.0;
    double sumRHCer = 0.0;

    double h = abs(abs(VELlst[marker][1]) - abs(VELlst[marker][0])); // krok
    for(int i = min-1; i < max; i++)
    {
      if(i == 0 || i == max-1)
      {
        sumI = sumI + Ilst[marker][i] / 2.0;
        sumV = sumV + Vlst[marker][i] / 2.0;
        sumLHC = sumLHC + LHClst[marker][i] / 2.0;
        sumRHC = sumRHC + RHClst[marker][i] / 2.0;
      }
      else
      {
        sumI = sumI + Ilst[marker][i];
        sumV = sumV + Vlst[marker][i];
        sumLHC = sumLHC + LHClst[marker][i];
        sumRHC = sumRHC + RHClst[marker][i];
      }
    }
    /*
    for(int i = min-1; i < max; i++)
    {
      if(i == 0 || i == max-1)
      {
        sumIer = sumIer + ERRlst[marker][i] / 2.0;
        sumVer = sumVer + VERRlst[marker][i] / 2.0;
        sumLHCer = sumLHCer + LHCERRlst[marker][i] / 2.0;
        sumRHCer = sumRHCer + RHCERRlst[marker][i] / 2.0;
      }
      else
      {
          sumIer = sumIer + ERRlst[marker][i];
          sumVer = sumVer + VERRlst[marker][i];
          sumLHCer = sumLHCer + LHCERRlst[marker][i];
          sumRHCer = sumRHCer + RHCERRlst[marker][i];
      }
    }
    */
    sumI = sumI * h;
    sumV = sumV * h;
    sumLHC = sumLHC * h;
    sumRHC = sumRHC * h;

    //sumIer = sumIer * h;
    //sumVer = sumVer * h;
    //sumLHCer = sumLHCer * h;
    //sumRHCer = sumRHCer * h;

    integrated_flux_I = sumI;
    integrated_flux_V = sumV;
    integrated_flux_LHC = sumLHC;
    integrated_flux_RHC = sumRHC;

    integrated_flux_I_er = ERRlst[marker][0] * 5.0 * h;
    integrated_flux_V_er = VERRlst[marker][0] * 5.0 * h;
    integrated_flux_LHC_er = LHCERRlst[marker][0] * 5.0 * h;
    integrated_flux_RHC_er = RHCERRlst[marker][0] * 5.0 * h;

}

// -- liczy calke z wszystkich widm --
void body::integrate_time_series()
{

    unsigned int min, max;
    QString mins,maxs;
    mins = starting_channel.toPlainText();
    maxs = ending_channel.toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString())-1;
        max = stoi(maxs.toStdString())-1;
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return;
    }

    // -- obsługujemy kilka przypadków błędnego wpisania paramatrów --
    // początkowy channel większy od końcowego
    if (min > max)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel > max channel!"));
        return;
    }
    // początkowy channel mniejszy od zera
    if (min < 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel < 1!"));
        return;
    }
    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > Ilst[0].size()-1)
        max = Ilst[0].size()-1;

    chan4int_start = min;
    chan4int_end = max;

    // -- czyścimy tablice --
    // czyscimy tablice z int
    integrated_fluxlst_I.clear();
    integrated_fluxlst_V.clear();
    integrated_fluxlst_LHC.clear();
    integrated_fluxlst_RHC.clear();
    integrated_fluxlst_I_er.clear();
    integrated_fluxlst_V_er.clear();
    integrated_fluxlst_LHC_er.clear();
    integrated_fluxlst_RHC_er.clear();

    // -- integrujemy --
    for(unsigned int i = 0; i < Ilst.size(); i++)
    {
        integrate_single(min, max, i);
        integrated_fluxlst_I.push_back(integrated_flux_I);
        integrated_fluxlst_V.push_back(integrated_flux_V);
        integrated_fluxlst_LHC.push_back(integrated_flux_LHC);
        integrated_fluxlst_RHC.push_back(integrated_flux_RHC);
        integrated_fluxlst_I_er.push_back(integrated_flux_I_er);
        integrated_fluxlst_V_er.push_back(integrated_flux_V_er);
        integrated_fluxlst_LHC_er.push_back(integrated_flux_LHC_er);
        integrated_fluxlst_RHC_er.push_back(integrated_flux_RHC_er);
    }
    //cout << "----> Integrated over channels " << chan4int_start << " -> " << chan4int_end << endl;
    //QMessageBox::information(&window, tr("Message to you"), tr("Integrated over channels " + QString::fromStdString(to_string(min)) + " -> " +  QString::fromStdString(to_string(max))));

    // -- zapisujemy do pliku --
    ofstream integ;
    string filename = working_directory + "/" + srcname + "_integrated_flux_density_" + to_string(min+1) + "_to_" + to_string(max+1) +  ".DAT";
    integ.open(filename.c_str());
    //integ << "# MJD year I V LHC RHC" << endl;
    //integ << "# MJD year I err V err LHC err RHC err" << endl;

    if(include_pytime->isChecked())
    {
        // wpisujemy naglowek do pliku
        integ << "# time_in_isoformat MJD year I err V err LHC err RHC err" << endl;
        // petla zapisujaca
        for(int i = 0; i < Ilst.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << pytime_format[i] << "   " << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "   " << integrated_fluxlst_I_er[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_V_er[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_LHC_er[i] << "   " << "   " << integrated_fluxlst_RHC[i] << "   " << integrated_fluxlst_RHC_er[i] << "   " << endl;
            //integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
        //cout << "Zaznaczono pytime" << endl;
    }
    else
    {
        // wpisujemy naglowek do pliku
        integ << "# MJD year I err V err LHC err RHC err" << endl;
        // petla zapisujaca
        for(int i = 0; i < Ilst.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "   " << integrated_fluxlst_I_er[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_V_er[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_LHC_er[i] << "   " << "   " << integrated_fluxlst_RHC[i] << "   " << integrated_fluxlst_RHC_er[i] << "   " << endl;
            //integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
    }

    integ.close();
    //integrated_fluxlst_I.clear();
    //integrated_fluxlst_V.clear();
    //integrated_fluxlst_LHC.clear();
    //integrated_fluxlst_RHC.clear();
    //integrated_fluxlst_I_er.clear();
    //integrated_fluxlst_V_er.clear();
    //integrated_fluxlst_LHC_er.clear();
    //integrated_fluxlst_RHC_er.clear();
   // cout << endl;
    //cout << "----> Saved to " << filename << endl;
    //cout << endl;
    string message = "";
    message = "Integrated over channels " + to_string(min+1) + " -> " + to_string(max+1) + "\n" + "Saved to " + filename;
    close_window_for_integrate();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));
}

// -- wyswietla widmo dynamiczne --
void body::display_dynamic_spectrum()
{
    if (loaded_data == 0)
    {
        //cout << "----> Please, load data first" << endl;
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    if (single_spectrum_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close SINGLE SPECTRUM window"));
        //cout << "Please, close SINGLE SPECTRUM window" << endl;
        return;
    }
    else if (rms_section_opened == 1)
    {
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        QMessageBox::information(&window, tr("Error!"), tr("Please, close the RMS, Sint & Tsys window"));
        return;
    }
    // ee
    //dynamic_spectrum_pl.setOpenGl(true);
    lhc_pressed = 0;
    rhc_pressed = 0;
    I_pressed = 1;
    v_pressed = 0;
    //for_hbox->setVisible(true);

    single_dynamic_spectrum.clearItems();
    lcs_dynamic_spectrum.clearItems();
    // -- kilka rzeczy ustawiamy --
    min_range_vel_index = 0;
    min_obs_number = 0;
    max_range_vel_index = VELlst[0].size()-1;
    max_obs_number = mjdlst.size()-1;
    rozmiar_w_x = mjdlst.size();
    rozmiar_w_y = CHANlst[0].size();
    // -- konfigurujemy plot --
    if (layers_exist == 0)
    {
        dynamic_spectrum_pl.addLayer("linex");
        dynamic_spectrum_pl.addLayer("liney");
        dynamic_spectrum_pl.addLayer("pixmap");
        dynamic_spectrum_pl.addLayer("prectangle");
        dynamic_spectrum_pl.addLayer("flags");
        colorMap->setLayer("pixmap");
        x_axis_line->setLayer("linex");
        y_axis_line->setLayer("liney");
        rectangle -> setLayer("prectangle");
        dynamic_spectrum_pl.moveLayer(x_axis_line->layer(), colorMap->layer(), QCustomPlot::limAbove );
        dynamic_spectrum_pl.moveLayer(y_axis_line->layer(), colorMap->layer(), QCustomPlot::limAbove );
        dynamic_spectrum_pl.moveLayer(rectangle ->layer(), colorMap->layer(), QCustomPlot::limAbove );
        layers_exist = 1;
    }


    //dynamic_spectrum_pl.setInteractions(QCP::iRangeZoom);
    /*
    dynamic_spectrum_pl.axisRect()->setRangeDrag(Qt::Vertical);
    dynamic_spectrum_pl.axisRect()->setRangeZoom(Qt::Vertical);
    dynamic_spectrum_pl.axisRect()->setRangeZoomAxes(dynamic_spectrum_pl.yAxis, NULL);
    dynamic_spectrum_pl.setSelectionRectMode(QCP::srmZoom);
    */
    dynamic_spectrum_pl.axisRect()->setupFullAxesBox(false);

    dynamic_spectrum_pl.xAxis->setLabel("Observation number");
    dynamic_spectrum_pl.yAxis->setLabel("Vel");

    // -- ogarniamy color mape --

    colorMap->setInterpolate(false);
    int nx = mjdlst.size();
    int ny = CHANlst[0].size();
    colorMap->data()->setSize(nx,ny);
    //colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    colorMap->data()->setRange(QCPRange(0, mjdlst.size()-1), QCPRange(VELlst[0][0], VELlst[0][VELlst[0].size()-1]-(VELlst[0][2]-VELlst[0][1])));
    //double x,y,z;

    for (int xIndex = 0; xIndex < nx; xIndex++)
    {
        for (int yIndex = 0; yIndex < ny; yIndex++)
        {
            //colorMap->data()->cellToCoord(xIndex,yIndex, &x, &y);
            if (Ilst[xIndex][yIndex] > 0.0)
                colorMap->data()->setCell(xIndex, yIndex, Ilst[xIndex][yIndex]);
            else
                colorMap->data()->setCell(xIndex, yIndex, 0.0);
        }
    }

    // -- skala kolorow --

    /*
    if (color_scale_indicator == 0)
    {
        //color_scale_plot.plotLayout()->remove(0);
        color_scale_plot->axisRect()->setupFullAxesBox(true);
        color_scale_plot->plotLayout()->addElement(0,1,colorScale);
        //grid.addWidget(&colorScale, 1,1,7,3);
        color_scale_indicator = 1;
    }
    color_scale_plot->setInteractions(QCP::iRangeDrag);//|QCP::iRangeZoom);
    colorScale->setParent(&dynamic_spectrum_pl);
    //colorScale->set
    QMargins my_margins;
    my_margins.setTop(0);
    my_margins.setBottom(0);
    //colorScale->setMargins(my_margins);
    colorMap->setColorScale(colorScale);
    colorScale->setType(QCPAxis::atBottom);

    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    //colorScale->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);


    //colorScale->axis()->setLabel("Flux Density (Jy)");
    */
    // -- color gradient --
    gradient.loadPreset(QCPColorGradient::gpJet);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange();
    colorMap -> rescaleKeyAxis();
    colorMap -> rescaleValueAxis();
    colorMap -> setTightBoundary(false);
    // -- cos jeszcze lul --



    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();
    // -- dodajemy do gridu --



    // -- dodajemy widgety --
    // -- dodajemy widgety --
    if (dynamic_spectrum_opened == 0)
    {
        //cout << "----> DYNAMIC SPECTRUM Window is opened, so I will just reset axis" << endl;
        y_down_border_shrt->setKey(QKeySequence("d"));
        y_up_border_shrt->setKey(QKeySequence("g"));
        x_down_border_shrt->setKey(QKeySequence("l"));
        x_up_border_shrt->setKey(QKeySequence("p"));
        reset_dynamic_spectrum->setKey(QKeySequence("b"));
        kill_dynspec.setText("Kill dynamic spectrum --->");
        QObject::connect(&kill_dynspec, SIGNAL(clicked()), this, SLOT(kill_dynamic_spectrum()));
        QObject::connect(&dynamic_spectrum_pl, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(press_map(QMouseEvent *)));
        QObject::connect(&y_up_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_y_up()));
        QObject::connect(&y_down_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_y_down()));
        QObject::connect(y_up_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_y_up()));
        QObject::connect(y_down_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_y_down()));
        QObject::connect(x_up_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_x_right()));
        QObject::connect(x_down_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_x_left()));
        QObject::connect(&x_right_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_x_right()));
        QObject::connect(&x_left_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_x_left()));
        QObject::connect(&Ibut, SIGNAL(clicked()), this, SLOT(set_I_on_dynamic_spectrum()));
        QObject::connect(&LHCbut, SIGNAL(clicked()), this, SLOT(set_LHC_on_dynamic_spectrum()));
        QObject::connect(&RHCbut, SIGNAL(clicked()), this, SLOT(set_RHC_on_dynamic_spectrum()));
        QObject::connect(&Vbut, SIGNAL(clicked()), this, SLOT(set_V_on_dynamic_spectrum()));
        QObject::connect(&make_lcs_button, SIGNAL(clicked()), this, SLOT(make_lcs_slot()));
        QObject::connect(&flag, SIGNAL(clicked()), this, SLOT(flag_slot()));
        QObject::connect(&rotate, SIGNAL(clicked()), this, SLOT(rotate_slot_plus()));
        QObject::connect(&rotate_minus, SIGNAL(clicked()), this, SLOT(rotate_slot_minus()));
        QObject::connect(&save_rotation, SIGNAL(clicked()), this, SLOT(save_rotated_spectras()));
        QObject::connect(reset_dynamic_spectrum, SIGNAL(activated()), this, SLOT(display_dynamic_spectrum()));
    }
    if (dynamic_spectrum_opened == 1)
    {
        cout << "----> DYNAMIC SPECTRUM Window is opened, so I will just reset axis" << endl;
        return;
    }

    //grid.addWidget(&kill_dynspec, 8,0);
    vbox_main.addWidget(&kill_dynspec);
    //grid.addWidget(color_scale_plot, 0, 1, 1, 3);
    grid.addWidget(&dynamic_spectrum_pl, 0,1,8,3);
    grid.addWidget(&single_dynamic_spectrum, 0,4,4,2);
    grid.addWidget(&lcs_dynamic_spectrum, 4,4,4,2);

    /*
    grid.addWidget(&y_down_border, 3,8);
    grid.addWidget(&y_up_border, 4,8);
    grid.addWidget(&x_left_border, 5,8);
    grid.addWidget(&x_right_border, 6,8);
    */
    //grid.addWidget(&y_up_border, 8,2);

    if (layout_buttons_loaded_dynspec == 0)
    {
        hbox->addWidget(&Ibut);
        hbox->addWidget(&Vbut);
        hbox->addWidget(&LHCbut);
        hbox->addWidget(&RHCbut);
        hbox->addWidget(&y_down_border);
        hbox->addWidget(&y_up_border);
        hbox->addWidget(&x_left_border);
        hbox->addWidget(&x_right_border);
        operations->addWidget(&number_of_rotated_channels_texted);
        operations->addWidget(&flag);
        operations->addWidget(&rotate);
        operations->addWidget(&save_rotation);
        operations->addWidget(&rotate_minus);
        operations->addWidget(&make_lcs_button);
        hbox->setSpacing(1);
        operations->setSpacing(1);
        on_dyn_spec_buttons.addLayout(operations);
        on_dyn_spec_buttons.addLayout(hbox);
        layout_buttons_loaded_dynspec = 1;
    }

    grid.addLayout(&on_dyn_spec_buttons,8,1,1,3);
    grid.addWidget(&mjd_label, 8,4);
    grid.addWidget(&cocochanel, 8,5);
    /*
    grid.addWidget(&Ibut, 0,8);
    grid.addWidget(&Vbut, 1,8);
    grid.addWidget(&LHCbut, 2,8);
    grid.addWidget(&RHCbut, 3,8);
    */
    //mjd_label.setText("mbfa\njedzeniekocham\njamniczka");
    //cocochanel.setText("2137");
    y_down_border.setText("Down");
    y_up_border.setText("Up");
    x_left_border.setText("|->");
    x_right_border.setText("<-|");
    Ibut.setText("I");
    Vbut.setText("V");
    LHCbut.setText("LHC");
    RHCbut.setText("RHC");
    window.setGeometry(window.x(), window.y(),1360,720);
    window.setLayout(&grid);
    Ibut.setDown(true);
    LHCbut.setDown(false);
    RHCbut.setDown(false);
    Vbut.setDown(false);
    lhc_pressed = 0;
    rhc_pressed = 0;
    I_pressed = 1;
    v_pressed = 0;
    window.setLayout(&grid);
    window.show();


    dynamic_spectrum_opened = 1;
    min_range_vel_index = 0;
    min_obs_number = 0;
    max_range_vel_index = VELlst[0].size()-1;
    max_obs_number = mjdlst.size()-1;
    //for_hbox->show();
    press_map_met();
    grid.setColumnStretch(0,1);
    grid.setColumnStretch(1,3);
    grid.setColumnStretch(2,3);
    grid.setColumnStretch(3,3);
    grid.setColumnStretch(4,3);
    grid.setColumnStretch(5,3);
    //dynamic_spectrum_pl.setFixedSize(500, 500);
    dyns_first_open = 0;
    //dynamic_spectrum_pl.clearItems();

    // ustalamy ilość rotowanych kanałów
    QString rot;
    rot = QString::fromStdString(to_string(number_of_rotated_channels));
    number_of_rotated_channels_texted.setText(rot);

    // -- ustalamy visibilities --
    dynamic_spectrum_pl.setVisible(true);
    kill_dynspec.setVisible(true);
    single_dynamic_spectrum.setVisible(true);
    lcs_dynamic_spectrum.setVisible(true);
    y_down_border.setVisible(true);
    y_up_border.setVisible(true);
    mjd_label.setVisible(true);
    cocochanel.setVisible(true);
    x_left_border.setVisible(true);
    x_right_border.setVisible(true);
    Ibut.setVisible(true);
    Vbut.setVisible(true);
    LHCbut.setVisible(true);
    RHCbut.setVisible(true);
    flag.setVisible(true);
    rotate.setVisible(true);
    make_lcs_button.setVisible(true);
    rotate_minus.setVisible(true);
    save_rotation.setVisible(true);
    number_of_rotated_channels_texted.setVisible(true);
}

// -- zamyka widmo dynamiczne --
void body::kill_dynamic_spectrum()
{
    //dynamic_spectrum_pl.clearItems();
    //dynamic_spectrum_pl.clearPlottables();
    //dynamic_spectrum_pl.replot();
    // -- usuwamy widgety z layoutu --
    grid.removeWidget(&dynamic_spectrum_pl);
    //grid.removeWidget(&kill_dynspec);
    vbox_main.removeWidget(&kill_dynspec);
    grid.removeWidget(&single_dynamic_spectrum);
    grid.removeWidget(&lcs_dynamic_spectrum);
    grid.removeWidget(&y_down_border);
    grid.removeWidget(&y_up_border);
    grid.removeWidget(&mjd_label);
    grid.removeWidget(&cocochanel);
    //vbox_main.removeWidget(&number_of_rotated_channels_texted);
    //hbox->removeWidget(&Ibut);
    //hbox->removeWidget(&Vbut);
    //hbox->removeWidget(&LHCbut);
    //hbox->removeWidget(&RHCbut);
    //hbox->removeWidget(&y_down_border);
    //hbox->removeWidget(&y_up_border);
    //hbox->removeWidget(&x_left_border);
    //hbox->removeWidget(&x_right_border);
    //grid.removeItem(hbox);
    grid.removeItem(&on_dyn_spec_buttons);
    grid.update();
    // -- czyscimy plotno --
    //dynamic_spectrum_pl.graph(0)->data().clear();
    //dynamic_spectrum_pl.clearPlottables();
    //dynamic_spectrum_pl.clearItems();


    dynamic_spectrum_pl.replot();
    // -- usuwamy przyciski z layoutu --
    // -- ukrywamy widgety --
    dynamic_spectrum_pl.setVisible(false);
    kill_dynspec.setVisible(false);
    single_dynamic_spectrum.setVisible(false);
    lcs_dynamic_spectrum.setVisible(false);
    y_down_border.setVisible(false);
    y_up_border.setVisible(false);
    x_left_border.setVisible(false);
    x_right_border.setVisible(false);
    Ibut.setVisible(false);
    Vbut.setVisible(false);
    LHCbut.setVisible(false);
    RHCbut.setVisible(false);
    cocochanel.setVisible(false);
    mjd_label.setVisible(false);
    flag.setVisible(false);
    rotate.setVisible(false);
    rotate_minus.setVisible(false);
    save_rotation.setVisible(false);
    make_lcs_button.setVisible(false);
    number_of_rotated_channels_texted.setVisible(false);
    //for_hbox->setVisible(false);

    // -- zmieniamy rozmiar okna --
    window.setGeometry(window.x(), window.y(),300,720);
    window.setLayout(&grid);
    window.show();
    dynamic_spectrum_opened = 0;
    graphs_next_to_dynamical_spectrum = 0;
    vel_line_added = 0;
    lcs_line_added = 0;
    Ibut.setDown(false);
    LHCbut.setDown(false);
    RHCbut.setDown(false);
    Vbut.setDown(false);
    window.setGeometry(window.x(), window.y(),300,720);
    grid.setColumnStretch(0,1);
    grid.setColumnStretch(1,0);
    grid.setColumnStretch(2,0);
    grid.setColumnStretch(3,0);
    grid.setColumnStretch(4,0);
    grid.setColumnStretch(5,0);
    QObject::disconnect(&kill_dynspec, SIGNAL(clicked()), this, SLOT(kill_dynamic_spectrum()));
    QObject::disconnect(&dynamic_spectrum_pl, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(press_map(QMouseEvent *)));
    QObject::disconnect(&y_up_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_y_up()));
    QObject::disconnect(&y_down_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_y_down()));
    QObject::disconnect(y_up_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_y_up()));
    QObject::disconnect(y_down_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_y_down()));
    QObject::disconnect(x_up_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_x_right()));
    QObject::disconnect(x_down_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_x_left()));
    QObject::disconnect(&x_right_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_x_right()));
    QObject::disconnect(&x_left_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_x_left()));
    QObject::disconnect(&Ibut, SIGNAL(clicked()), this, SLOT(set_I_on_dynamic_spectrum()));
    QObject::disconnect(&LHCbut, SIGNAL(clicked()), this, SLOT(set_LHC_on_dynamic_spectrum()));
    QObject::disconnect(&RHCbut, SIGNAL(clicked()), this, SLOT(set_RHC_on_dynamic_spectrum()));
    QObject::disconnect(&Vbut, SIGNAL(clicked()), this, SLOT(set_V_on_dynamic_spectrum()));
    QObject::disconnect(&make_lcs_button, SIGNAL(clicked()), this, SLOT(make_lcs_slot()));
    QObject::disconnect(&flag, SIGNAL(clicked()), this, SLOT(flag_slot()));
    QObject::disconnect(&rotate, SIGNAL(clicked()), this, SLOT(rotate_slot_plus()));
    QObject::disconnect(&rotate_minus, SIGNAL(clicked()), this, SLOT(rotate_slot_minus()));
    QObject::disconnect(&save_rotation, SIGNAL(clicked()), this, SLOT(save_rotated_spectras()));
    QObject::disconnect(reset_dynamic_spectrum, SIGNAL(activated()), this, SLOT(display_dynamic_spectrum()));
    //ew = QSize()
    //QSize ew = QSize(QW)
    //dynamic_spectrum_pl.setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}

// -- obsluguje wcisniecia na widmie dynamicznym --
void body::press_map(QMouseEvent * event)
{
    double x,y;
    x = dynamic_spectrum_pl.xAxis->pixelToCoord(event -> pos().x());
    y = dynamic_spectrum_pl.yAxis->pixelToCoord(event -> pos().y());
    if(x < 0)
    {
        x = 0.0;
    }
    else if (x > mjdlst.size()-1)
    {
        x = mjdlst.size()-1;
    }

    if(y < VELlst[0][0])
    {
        y = VELlst[0][0];
    }
    else if (y > VELlst[0][VELlst[0].size()-1])
    {
        y = VELlst[0][VELlst[0].size()-1];
    }

    //int xind, yind;
    xind = int(round(x));
    //cout << xind << endl;
    for(int i=0; i < VELlst[0].size(); i++)
    {

        if (VELlst[0][i] > y+0.5*(VELlst[0][2]-VELlst[0][1]))
        {
            yind = i-1;
            break;
        }
    }
    if (yind < 0)
    {
        yind = 0;
    }
    QPen pen;
    pen.setColor(QColor(255,255,255));
    x_axis_line->setPen(pen);
    y_axis_line->setPen(pen);
    dynamic_spectrum_pl.setCursor(QCursor(Qt::CrossCursor));
    x_axis_line->start->setCoords(xind, -QCPRange::maxRange);
    x_axis_line->end->setCoords(xind, QCPRange::maxRange);
    y_axis_line->start->setCoords(-QCPRange::maxRange,VELlst[0][yind]);
    y_axis_line->end->setCoords(QCPRange::maxRange,VELlst[0][yind]);
    rectangle->setPen(pen);
    rectangle->topLeft->setCoords(double(xind)-0.5, VELlst[0][yind]+0.5*(VELlst[0][2]-VELlst[0][1]));
    rectangle->bottomRight->setCoords(double(xind)+0.5, VELlst[0][yind]-0.5*(VELlst[0][2]-VELlst[0][1]));
    dynamic_spectrum_pl.replot();
    //cout << "Kliknieto w x: " << xind << " i w y: " << VELlst[0][yind] << endl;
   // single_dynamic_spectrum
    //lcs_dynamic_spectrum

    // -- sprawdzamy, czy byly grafiki juz wczesniej otwierane w oknie --
    if (graphs_next_to_dynamical_spectrum == 0)
    {
        single_dynamic_spectrum.addGraph();
        lcs_dynamic_spectrum.addGraph();
        graphs_next_to_dynamical_spectrum = 1;
    }

    // -- twotzymy widmo, ktore wyswietli sie po kliknieciu w widmo dynamiczne --
    // - warunki ze wzgledu na przyciski polaryzacji -
    QVector < double > velocity(rozmiar_w_y), flux(rozmiar_w_y);

    if (I_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = Ilst[xind][min_range_vel_index+i];
    }
    }

    else if (v_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = Vlst[xind][min_range_vel_index+i];
    }
    }
    else if (lhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = LHClst[xind][min_range_vel_index+i];
    }
    }
    else if (rhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = RHClst[xind][min_range_vel_index+i];
    }
    }

    single_dynamic_spectrum.replot();
    single_dynamic_spectrum.graph(0)->setData(velocity,flux);
    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double veldiff = *max_element(velocity.begin(), velocity.end()) - *min_element(velocity.begin(), velocity.end());
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));
    // -- pokazujemy ticki na gornej osi --
    single_dynamic_spectrum.xAxis2->setVisible(true);
    single_dynamic_spectrum.yAxis2->setVisible(true);
    single_dynamic_spectrum.xAxis2->setTickLabels(false);
    single_dynamic_spectrum.yAxis2->setTickLabels(false);
    single_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    if (vel_line_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        vel_line_added = 1;
    }
    QVector < double > x_vline(2), y_vline(2);
    x_vline[0] = VELlst[0][yind];
    x_vline[1] = VELlst[0][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end()));
    y_vline[1] = *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end()));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);
    single_dynamic_spectrum.replot();
    // -- tworzymy krzywa blasku, ktora wyswietli sie w krzywej blasku --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    if(I_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = Ilst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(v_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = Vlst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(lhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = LHClst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(rhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = RHClst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }
    //cout << epoch[0] << endl;

    errorBars->setAntialiased(false);
    errorBars->setDataPlottable(lcs_dynamic_spectrum.graph(0));
    errorBars->setPen(QPen(QColor(180,180,180)));

    lcs_dynamic_spectrum.graph(0)->setData(epoch,lcs_flux);
    errorBars->setData(error_lcs);

    lcs_dynamic_spectrum.graph(0)->setPen(QPen(Qt::blue));
    lcs_dynamic_spectrum.graph(0)->setLineStyle(QCPGraph::lsNone);
    lcs_dynamic_spectrum.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    lcs_dynamic_spectrum.xAxis->setLabel("MJD");
    lcs_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double diffrence = *max_element(epoch.begin(), epoch.end()) - *min_element(epoch.begin(), epoch.end());
    lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
    lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    lcs_dynamic_spectrum.replot();


    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }
    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = mjdlst[xind];
    lcsx_vline[1] = mjdlst[xind];
    lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);
    lcs_dynamic_spectrum.replot();

    // -- setujemy tekst do displayowania informacji --
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(to_string(int(mjdlst[xind])));


    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(to_string(CHANlst[xind][yind]));




    /*
    text_mjdlabel.append(string("      Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    */
    text_mjdlabel.append(string("\nVel: "));

    // Create an output string stream
    std::ostringstream streamObjvel;

    // Set Fixed -Point Notation
    streamObjvel << std::fixed;

    streamObjvel << std::setprecision(3);

    streamObjvel << VELlst[xind][yind];
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);

    /*
    text_mjdlabel.append(string("     Number: "));
    text_mjdlabel.append(to_string(xind+1));

    */
    mjd_label.setText(QString::fromStdString(text_mjdlabel));
    QFont f( "Arial", 11, QFont::Bold);
    mjd_label.setFont(f);
    string cocochanel_txt = "";


    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(to_string(int(ylst[xind])));
    cocochanel_txt.append(string(" "));


    if (int(mlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(mlst[xind])));
    else
        cocochanel_txt.append(to_string(int(mlst[xind])));

    cocochanel_txt.append(string(" "));

    if (int(dlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(dlst[xind])));
    else
        cocochanel_txt.append(to_string(int(dlst[xind])));

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(to_string(xind+1));

    cocochanel.setFont(f);
    cocochanel.setText(QString::fromStdString(cocochanel_txt));
    set_down_IVLHCRHCbuttons();
}

// -- obsluguje granice w osi predkosci na widmie dynamicznym (max) --
void body::set_max_range_on_dynamic_specrum_y_up()
{
    // ustalamy jaki jest max
    max_range_vel_index = yind;

    // ustawiamy ten max na widmie dynamicznym
    rozmiar_w_y = max_range_vel_index - min_range_vel_index;
    if (rozmiar_w_y <= 0)
        rozmiar_w_y = 1;

    //vector < double > tmpvel;

    /*
    for(int i = min_range_vel_index; i < VELlst[xind][max_range_vel_index]; i++)
    {
        rozmiar_w_y = rozmiar_w_y + 1;
    }
    */
    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    if(I_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(v_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Vlst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(lhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(rhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();
    double veldif = VELlst[xind][max_range_vel_index] - VELlst[xind][min_range_vel_index];
    single_dynamic_spectrum.xAxis->setRange(VELlst[xind][min_range_vel_index] - 0.05 * veldif, VELlst[xind][max_range_vel_index] + 0.05 * veldif);
    single_dynamic_spectrum.replot();
    window.show();
    set_down_IVLHCRHCbuttons();
}

// -- obsluguje granice w osi predkosci na widmie dynamicznym (min) --
void body::set_max_range_on_dynamic_specrum_y_down()
{
    // ustalamy jaki jest max
    min_range_vel_index = yind;
    //cout << min_range_vel_index << endl;
    // ustawiamy ten max na widmie dynamicznym
    rozmiar_w_y = max_range_vel_index - min_range_vel_index;
    if (rozmiar_w_y <= 0)
        rozmiar_w_y = 1;

    //vector < double > tmpvel;

    /*
    for(int i = min_range_vel_index; i < VELlst[xind][max_range_vel_index]; i++)
    {
        rozmiar_w_y = rozmiar_w_y + 1;
    }
    */
    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    if(I_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(v_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Vlst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(lhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(rhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();
    double veldif = VELlst[xind][max_range_vel_index] - VELlst[xind][min_range_vel_index];
    single_dynamic_spectrum.xAxis->setRange(VELlst[xind][min_range_vel_index] - 0.05 * veldif, VELlst[xind][max_range_vel_index] + 0.05 * veldif);
    single_dynamic_spectrum.replot();
    window.show();
    set_down_IVLHCRHCbuttons();
}

// -- obsluguje granice w osi czasu na widmie dynamicznym (max) --
void body::set_max_range_on_dynamic_specrum_x_right()
{
    // ustalamy jaki jest max
    max_obs_number = xind;

    // ustawiamy ten max na widmie dynamicznym
    rozmiar_w_x = max_obs_number - min_obs_number+1;
    if (rozmiar_w_x <= 0)
        rozmiar_w_x = 1;

    //vector < double > tmpvel;

    /*
    for(int i = min_range_vel_index; i < VELlst[xind][max_range_vel_index]; i++)
    {
        rozmiar_w_y = rozmiar_w_y + 1;
    }
    */
    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    if(I_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(v_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Vlst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(lhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(rhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();
    lcs_dynamic_spectrum.xAxis->setRange(mjdlst[min_obs_number], mjdlst[max_obs_number]);
    lcs_dynamic_spectrum.replot();
    window.show();
    set_down_IVLHCRHCbuttons();
    //cout << "zrobione" << endl;
}

// -- obsluguje granice w osi czasu na widmie dynamicznym (in) --
void body::set_max_range_on_dynamic_specrum_x_left()
{
    // ustalamy jaki jest max
    min_obs_number = xind;

    // ustawiamy ten max na widmie dynamicznym
    rozmiar_w_x = max_obs_number - min_obs_number+1;
    if (rozmiar_w_x <= 0)
        rozmiar_w_x = 1;

    //vector < double > tmpvel;

    /*
    for(int i = min_range_vel_index; i < VELlst[xind][max_range_vel_index]; i++)
    {
        rozmiar_w_y = rozmiar_w_y + 1;
    }
    */
    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    //cout << "min: " << min_obs_number << endl;
    //cout << "max: " << max_obs_number << endl;
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));

    if(I_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(v_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Vlst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(lhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(rhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    colorMap -> setTightBoundary(false);
    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();
    lcs_dynamic_spectrum.xAxis->setRange(mjdlst[min_obs_number], mjdlst[max_obs_number]);
    lcs_dynamic_spectrum.replot();
    window.show();
    set_down_IVLHCRHCbuttons();
    //cout << "zrobione" << endl;
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

// -- ustala parametr stokesa 'I' na widmie dynamicznym --
void body::set_I_on_dynamic_spectrum()
{

    //cout << rozmiar_w_x << endl;
    //cout << rozmiar_w_y << endl;
    //vector < double > tmpvel;

    /*
    for(int i = min_range_vel_index; i < VELlst[xind][max_range_vel_index]; i++)
    {
        rozmiar_w_y = rozmiar_w_y + 1;
    }
    */
    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    double x,y,z;
    for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
    {
        for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
        {
            if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                colorMap->data()->setCell(xIndex,yIndex, Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
            else
                colorMap->data()->setCell(xIndex,yIndex, 0.0);
        }
    }

    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();


    // --- lcs --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = Ilst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    lcs_dynamic_spectrum.graph(0)->setData(epoch, lcs_flux);
    errorBars->setData(error_lcs);
    double diffrence = *max_element(epoch.begin(), epoch.end()) - *min_element(epoch.begin(), epoch.end());
    lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
    lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    lcs_dynamic_spectrum.replot();


    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }
    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = mjdlst[xind];
    lcsx_vline[1] = mjdlst[xind];
    lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);
    lcs_dynamic_spectrum.replot();
    // --- single spectrum --
    QVector < double > velocity(rozmiar_w_y), flux(rozmiar_w_y);
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = Ilst[xind][min_range_vel_index+i];
    }

    single_dynamic_spectrum.replot();
    single_dynamic_spectrum.graph(0)->setData(velocity,flux);
    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double veldiff = *max_element(velocity.begin(), velocity.end()) - *min_element(velocity.begin(), velocity.end());
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));
    // -- pokazujemy ticki na gornej osi --
    single_dynamic_spectrum.xAxis2->setVisible(true);
    single_dynamic_spectrum.yAxis2->setVisible(true);
    single_dynamic_spectrum.xAxis2->setTickLabels(false);
    single_dynamic_spectrum.yAxis2->setTickLabels(false);
    single_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    if (vel_line_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        vel_line_added = 1;
    }
    QVector < double > x_vline(2), y_vline(2);
    x_vline[0] = VELlst[0][yind];
    x_vline[1] = VELlst[0][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end()));
    y_vline[1] = *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end()));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);
    single_dynamic_spectrum.replot();


    // -- buttony i boole --
    window.show();
    Ibut.setDown(true);
    LHCbut.setDown(false);
    RHCbut.setDown(false);
    Vbut.setDown(false);
    I_pressed = 1;
    lhc_pressed = 0;
    rhc_pressed = 0;
    v_pressed = 0;

    // -- setujemy tekst do displayowania informacji --
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(to_string(int(mjdlst[xind])));


    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(to_string(CHANlst[xind][yind]));




    /*
    text_mjdlabel.append(string("      Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    */
    text_mjdlabel.append(string("\nVel: "));

    // Create an output string stream
    std::ostringstream streamObjvel;

    // Set Fixed -Point Notation
    streamObjvel << std::fixed;

    streamObjvel << std::setprecision(3);

    streamObjvel << VELlst[xind][yind];
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);

    /*
    text_mjdlabel.append(string("     Number: "));
    text_mjdlabel.append(to_string(xind+1));

    */
    mjd_label.setText(QString::fromStdString(text_mjdlabel));
    QFont f( "Arial", 11, QFont::Bold);
    mjd_label.setFont(f);
    string cocochanel_txt = "";


    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(to_string(int(ylst[xind])));
    cocochanel_txt.append(string(" "));


    if (int(mlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(mlst[xind])));
    else
        cocochanel_txt.append(to_string(int(mlst[xind])));

    cocochanel_txt.append(string(" "));

    if (int(dlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(dlst[xind])));
    else
        cocochanel_txt.append(to_string(int(dlst[xind])));

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(to_string(xind+1));

    cocochanel.setFont(f);
    cocochanel.setText(QString::fromStdString(cocochanel_txt));
}

// -- ustala parametr stokesa 'V' na widmie dynamicznym --
void body::set_V_on_dynamic_spectrum()
{

    //cout << rozmiar_w_x << endl;
    //cout << rozmiar_w_y << endl;
    //vector < double > tmpvel;

    /*
    for(int i = min_range_vel_index; i < VELlst[xind][max_range_vel_index]; i++)
    {
        rozmiar_w_y = rozmiar_w_y + 1;
    }
    */
    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
    {
        for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
        {
            if (1 >= 0)
                colorMap->data()->setCell(xIndex,yIndex, Vlst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
            else
                colorMap->data()->setCell(xIndex,yIndex, 0.0);
        }
    }
    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();

    // --- lcs --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = Vlst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    lcs_dynamic_spectrum.graph(0)->setData(epoch, lcs_flux);
    errorBars->setData(error_lcs);
    double diffrence = *max_element(epoch.begin(), epoch.end()) - *min_element(epoch.begin(), epoch.end());
    lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
    lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    lcs_dynamic_spectrum.replot();


    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }
    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = mjdlst[xind];
    lcsx_vline[1] = mjdlst[xind];
    lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);
    lcs_dynamic_spectrum.replot();

    // --- single spectrum --
    QVector < double > velocity(rozmiar_w_y), flux(rozmiar_w_y);
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = Vlst[xind][min_range_vel_index+i];
    }

    single_dynamic_spectrum.replot();
    single_dynamic_spectrum.graph(0)->setData(velocity,flux);
    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double veldiff = *max_element(velocity.begin(), velocity.end()) - *min_element(velocity.begin(), velocity.end());
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));
    // -- pokazujemy ticki na gornej osi --
    single_dynamic_spectrum.xAxis2->setVisible(true);
    single_dynamic_spectrum.yAxis2->setVisible(true);
    single_dynamic_spectrum.xAxis2->setTickLabels(false);
    single_dynamic_spectrum.yAxis2->setTickLabels(false);
    single_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    if (vel_line_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        vel_line_added = 1;
    }
    QVector < double > x_vline(2), y_vline(2);
    x_vline[0] = VELlst[0][yind];
    x_vline[1] = VELlst[0][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end()));
    y_vline[1] = *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end()));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);
    single_dynamic_spectrum.replot();



    Ibut.setDown(false);
    LHCbut.setDown(false);
    RHCbut.setDown(false);
    Vbut.setDown(true);
    I_pressed = 0;
    lhc_pressed = 0;
    rhc_pressed = 0;
    v_pressed = 1;
    window.show();

    // -- setujemy tekst do displayowania informacji --
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(to_string(int(mjdlst[xind])));


    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(to_string(CHANlst[xind][yind]));




    /*
    text_mjdlabel.append(string("      Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    */
    text_mjdlabel.append(string("\nVel: "));

    // Create an output string stream
    std::ostringstream streamObjvel;

    // Set Fixed -Point Notation
    streamObjvel << std::fixed;

    streamObjvel << std::setprecision(3);

    streamObjvel << VELlst[xind][yind];
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);

    /*
    text_mjdlabel.append(string("     Number: "));
    text_mjdlabel.append(to_string(xind+1));

    */
    mjd_label.setText(QString::fromStdString(text_mjdlabel));
    QFont f( "Arial", 11, QFont::Bold);
    mjd_label.setFont(f);
    string cocochanel_txt = "";


    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(to_string(int(ylst[xind])));
    cocochanel_txt.append(string(" "));


    if (int(mlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(mlst[xind])));
    else
        cocochanel_txt.append(to_string(int(mlst[xind])));

    cocochanel_txt.append(string(" "));

    if (int(dlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(dlst[xind])));
    else
        cocochanel_txt.append(to_string(int(dlst[xind])));

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(to_string(xind+1));

    cocochanel.setFont(f);
    cocochanel.setText(QString::fromStdString(cocochanel_txt));

}

// -- ustala parametr stokesa 'LHC' na widmie dynamicznym --
void body::set_LHC_on_dynamic_spectrum()
{

    //cout << rozmiar_w_x << endl;
    //cout << rozmiar_w_y << endl;
    //vector < double > tmpvel;

    /*
    for(int i = min_range_vel_index; i < VELlst[xind][max_range_vel_index]; i++)
    {
        rozmiar_w_y = rozmiar_w_y + 1;
    }
    */
    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    double x,y,z;
    for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
    {
        for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
        {
            if (LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                colorMap->data()->setCell(xIndex,yIndex, LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
            else
                colorMap->data()->setCell(xIndex,yIndex, 0.0);
        }
    }
    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();
    single_dynamic_spectrum.xAxis->setRange(VELlst[xind][min_range_vel_index], VELlst[xind][max_range_vel_index]);
    single_dynamic_spectrum.replot();

    // --- lcs --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = LHClst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    lcs_dynamic_spectrum.graph(0)->setData(epoch, lcs_flux);
    errorBars->setData(error_lcs);
    double diffrence = *max_element(epoch.begin(), epoch.end()) - *min_element(epoch.begin(), epoch.end());
    lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
    lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    lcs_dynamic_spectrum.replot();


    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }
    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = mjdlst[xind];
    lcsx_vline[1] = mjdlst[xind];
    lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);
    lcs_dynamic_spectrum.replot();

    // --- single spectrum --
    QVector < double > velocity(rozmiar_w_y), flux(rozmiar_w_y);
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = LHClst[xind][min_range_vel_index+i];
    }

    single_dynamic_spectrum.replot();
    single_dynamic_spectrum.graph(0)->setData(velocity,flux);
    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double veldiff = *max_element(velocity.begin(), velocity.end()) - *min_element(velocity.begin(), velocity.end());
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));
    // -- pokazujemy ticki na gornej osi --
    single_dynamic_spectrum.xAxis2->setVisible(true);
    single_dynamic_spectrum.yAxis2->setVisible(true);
    single_dynamic_spectrum.xAxis2->setTickLabels(false);
    single_dynamic_spectrum.yAxis2->setTickLabels(false);
    single_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    if (vel_line_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        vel_line_added = 1;
    }
    QVector < double > x_vline(2), y_vline(2);
    x_vline[0] = VELlst[0][yind];
    x_vline[1] = VELlst[0][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end()));
    y_vline[1] = *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end()));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);
    single_dynamic_spectrum.replot();



    Ibut.setDown(false);
    LHCbut.setDown(true);
    RHCbut.setDown(false);
    Vbut.setDown(false);
    I_pressed = 0;
    lhc_pressed = 1;
    rhc_pressed = 0;
    v_pressed = 0;

    // -- setujemy tekst do displayowania informacji --
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(to_string(int(mjdlst[xind])));


    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(to_string(CHANlst[xind][yind]));




    /*
    text_mjdlabel.append(string("      Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    */
    text_mjdlabel.append(string("\nVel: "));

    // Create an output string stream
    std::ostringstream streamObjvel;

    // Set Fixed -Point Notation
    streamObjvel << std::fixed;

    streamObjvel << std::setprecision(3);

    streamObjvel << VELlst[xind][yind];
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);

    /*
    text_mjdlabel.append(string("     Number: "));
    text_mjdlabel.append(to_string(xind+1));

    */
    mjd_label.setText(QString::fromStdString(text_mjdlabel));
    QFont f( "Arial", 11, QFont::Bold);
    mjd_label.setFont(f);
    string cocochanel_txt = "";


    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(to_string(int(ylst[xind])));
    cocochanel_txt.append(string(" "));


    if (int(mlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(mlst[xind])));
    else
        cocochanel_txt.append(to_string(int(mlst[xind])));

    cocochanel_txt.append(string(" "));

    if (int(dlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(dlst[xind])));
    else
        cocochanel_txt.append(to_string(int(dlst[xind])));

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(to_string(xind+1));

    cocochanel.setFont(f);
    cocochanel.setText(QString::fromStdString(cocochanel_txt));

    window.show();
}

// -- ustala parametr stokesa 'RHC' na widmie dynamicznym --
void body::set_RHC_on_dynamic_spectrum()
{

    //cout << rozmiar_w_x << endl;
    //cout << rozmiar_w_y << endl;
    //vector < double > tmpvel;

    /*
    for(int i = min_range_vel_index; i < VELlst[xind][max_range_vel_index]; i++)
    {
        rozmiar_w_y = rozmiar_w_y + 1;
    }
    */
    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    double x,y,z;
    for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
    {
        for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
        {
            if (RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                colorMap->data()->setCell(xIndex,yIndex, RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
            else
                colorMap->data()->setCell(xIndex,yIndex, 0.0);
        }
    }
    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();

    // --- lcs --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = RHClst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    lcs_dynamic_spectrum.graph(0)->setData(epoch, lcs_flux);
    errorBars->setData(error_lcs);
    double diffrence = *max_element(epoch.begin(), epoch.end()) - *min_element(epoch.begin(), epoch.end());
    lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
    lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    lcs_dynamic_spectrum.replot();


    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }
    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = mjdlst[xind];
    lcsx_vline[1] = mjdlst[xind];
    lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);
    lcs_dynamic_spectrum.replot();

    // --- single spectrum --
    QVector < double > velocity(rozmiar_w_y), flux(rozmiar_w_y);
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = RHClst[xind][min_range_vel_index+i];
    }

    single_dynamic_spectrum.replot();
    single_dynamic_spectrum.graph(0)->setData(velocity,flux);
    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double veldiff = *max_element(velocity.begin(), velocity.end()) - *min_element(velocity.begin(), velocity.end());
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));
    // -- pokazujemy ticki na gornej osi --
    single_dynamic_spectrum.xAxis2->setVisible(true);
    single_dynamic_spectrum.yAxis2->setVisible(true);
    single_dynamic_spectrum.xAxis2->setTickLabels(false);
    single_dynamic_spectrum.yAxis2->setTickLabels(false);
    single_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    if (vel_line_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        vel_line_added = 1;
    }
    QVector < double > x_vline(2), y_vline(2);
    x_vline[0] = VELlst[0][yind];
    x_vline[1] = VELlst[0][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end()));
    y_vline[1] = *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end()));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);
    single_dynamic_spectrum.replot();


    Ibut.setDown(false);
    LHCbut.setDown(false);
    RHCbut.setDown(true);
    Vbut.setDown(false);
    I_pressed = 0;
    lhc_pressed = 0;
    rhc_pressed = 1;
    v_pressed = 0;

    // -- setujemy tekst do displayowania informacji --
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(to_string(int(mjdlst[xind])));


    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(to_string(CHANlst[xind][yind]));




    /*
    text_mjdlabel.append(string("      Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    */
    text_mjdlabel.append(string("\nVel: "));

    // Create an output string stream
    std::ostringstream streamObjvel;

    // Set Fixed -Point Notation
    streamObjvel << std::fixed;

    streamObjvel << std::setprecision(3);

    streamObjvel << VELlst[xind][yind];
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);

    /*
    text_mjdlabel.append(string("     Number: "));
    text_mjdlabel.append(to_string(xind+1));

    */
    mjd_label.setText(QString::fromStdString(text_mjdlabel));
    QFont f( "Arial", 11, QFont::Bold);
    mjd_label.setFont(f);
    string cocochanel_txt = "";


    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(to_string(int(ylst[xind])));
    cocochanel_txt.append(string(" "));


    if (int(mlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(mlst[xind])));
    else
        cocochanel_txt.append(to_string(int(mlst[xind])));

    cocochanel_txt.append(string(" "));

    if (int(dlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(dlst[xind])));
    else
        cocochanel_txt.append(to_string(int(dlst[xind])));

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(to_string(xind+1));

    cocochanel.setFont(f);
    cocochanel.setText(QString::fromStdString(cocochanel_txt));

    window.show();
}

// -- robi to samo, co 'press_map()', jednak bez wciśnięcia - czyta ostatnio zapisane wartości x i y --
void body::press_map_met()
{

    xind = 0;
    yind = 0;
    QPen pen;
    pen.setColor(QColor(255,255,255));
    x_axis_line->setPen(pen);
    y_axis_line->setPen(pen);
    dynamic_spectrum_pl.setCursor(QCursor(Qt::CrossCursor));
    x_axis_line->start->setCoords(xind, -QCPRange::maxRange);
    x_axis_line->end->setCoords(xind, QCPRange::maxRange);
    y_axis_line->start->setCoords(-QCPRange::maxRange,VELlst[0][yind]);
    y_axis_line->end->setCoords(QCPRange::maxRange,VELlst[0][yind]);
    rectangle->setPen(pen);
    rectangle->topLeft->setCoords(double(xind)-0.5, VELlst[0][yind]+0.5*(VELlst[0][2]-VELlst[0][1]));
    rectangle->bottomRight->setCoords(double(xind)+0.5, VELlst[0][yind]-0.5*(VELlst[0][2]-VELlst[0][1]));
    dynamic_spectrum_pl.replot();
    //cout << "Kliknieto w x: " << xind << " i w y: " << VELlst[0][yind] << endl;
   // single_dynamic_spectrum
    //lcs_dynamic_spectrum

    // -- sprawdzamy, czy byly grafiki juz wczesniej otwierane w oknie --
    if (graphs_next_to_dynamical_spectrum == 0)
    {
        single_dynamic_spectrum.addGraph();
        lcs_dynamic_spectrum.addGraph();
        graphs_next_to_dynamical_spectrum = 1;
    }

    // -- twotzymy widmo, ktore wyswietli sie po kliknieciu w widmo dynamiczne --
    // - warunki ze wzgledu na przyciski polaryzacji -
    QVector < double > velocity(rozmiar_w_y), flux(rozmiar_w_y);

    if (I_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = Ilst[xind][min_range_vel_index+i];
    }
    }

    else if (v_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = Vlst[xind][min_range_vel_index+i];
    }
    }
    else if (lhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = LHClst[xind][min_range_vel_index+i];
    }
    }
    else if (rhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = RHClst[xind][min_range_vel_index+i];
    }
    }

    single_dynamic_spectrum.replot();
    single_dynamic_spectrum.graph(0)->setData(velocity,flux);
    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()), *max_element(velocity.begin(), velocity.end()));
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()), *max_element(flux.begin(), flux.end()));
    // -- pokazujemy ticki na gornej osi --
    single_dynamic_spectrum.xAxis2->setVisible(true);
    single_dynamic_spectrum.yAxis2->setVisible(true);
    single_dynamic_spectrum.xAxis2->setTickLabels(false);
    single_dynamic_spectrum.yAxis2->setTickLabels(false);
    single_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    if (vel_line_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        vel_line_added = 1;
    }
    QVector < double > x_vline(2), y_vline(2);
    x_vline[0] = VELlst[0][yind];
    x_vline[1] = VELlst[0][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end());
    y_vline[1] = *max_element(flux.begin(), flux.end());
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);
    single_dynamic_spectrum.replot();
    // -- tworzymy krzywa blasku, ktora wyswietli sie w krzywej blasku --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    if(I_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = Ilst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(v_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = Vlst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(lhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = LHClst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(rhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = RHClst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }
    //cout << epoch[0] << endl;

    errorBars->setAntialiased(false);
    errorBars->setDataPlottable(lcs_dynamic_spectrum.graph(0));
    errorBars->setPen(QPen(QColor(180,180,180)));

    lcs_dynamic_spectrum.graph(0)->setData(epoch,lcs_flux);
    errorBars->setData(error_lcs);

    lcs_dynamic_spectrum.graph(0)->setPen(QPen(Qt::blue));
    lcs_dynamic_spectrum.graph(0)->setLineStyle(QCPGraph::lsNone);
    lcs_dynamic_spectrum.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    lcs_dynamic_spectrum.xAxis->setLabel("MJD");
    lcs_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()), *max_element(epoch.begin(), epoch.end()));
    lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()), *max_element(lcs_flux.begin(), lcs_flux.end()));
    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    lcs_dynamic_spectrum.replot();


    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }
    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = mjdlst[xind];
    lcsx_vline[1] = mjdlst[xind];
    lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end());
    lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end());
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);
    lcs_dynamic_spectrum.replot();
    // -- setujemy tekst do displayowania informacji --
    // -- setujemy tekst do displayowania informacji --
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(to_string(int(mjdlst[xind])));


    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(to_string(CHANlst[xind][yind]));




    /*
    text_mjdlabel.append(string("      Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        text_mjdlabel.append(strObj3);
    }
    */
    text_mjdlabel.append(string("\nVel: "));

    // Create an output string stream
    std::ostringstream streamObjvel;

    // Set Fixed -Point Notation
    streamObjvel << std::fixed;

    streamObjvel << std::setprecision(3);

    streamObjvel << VELlst[xind][yind];
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);

    /*
    text_mjdlabel.append(string("     Number: "));
    text_mjdlabel.append(to_string(xind+1));

    */
    mjd_label.setText(QString::fromStdString(text_mjdlabel));
    QFont f( "Arial", 11, QFont::Bold);
    mjd_label.setFont(f);
    string cocochanel_txt = "";


    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(to_string(int(ylst[xind])));
    cocochanel_txt.append(string(" "));


    if (int(mlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(mlst[xind])));
    else
        cocochanel_txt.append(to_string(int(mlst[xind])));

    cocochanel_txt.append(string(" "));

    if (int(dlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(dlst[xind])));
    else
        cocochanel_txt.append(to_string(int(dlst[xind])));

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(to_string(xind+1));

    cocochanel.setFont(f);
    cocochanel.setText(QString::fromStdString(cocochanel_txt));
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

// -- liczy srednia po predkosci - dla jednej epoki --
vector < double > body::average_over_velocity(int min_chan, int max_chan, vector < double > stokes_parameter, vector < double > error)
{
    double suma = 0.0;
    //int licznik = 0;
    int chan_count = max_chan - min_chan + 1;
    if(chan_count < 0)
        chan_count = 1;

    // petla liczaca srednia
    for (int i = 0; i < chan_count; i++)
    {
        suma = suma + stokes_parameter[min_chan + i];
    }
    suma = suma / chan_count;

    // petla liczaca sredni blad
    double sumaer = 0.0;
    for (int i = 0; i < chan_count; i++)
    {
        sumaer = sumaer + error[min_chan + i];
    }
    sumaer = sumaer / chan_count;

    double standard_deriv = 0.0;
    // petla liczaca odchylenie standardowe
    for (int i = 0; i < chan_count; i++)
    {
        standard_deriv = standard_deriv + pow(stokes_parameter[min_chan + i] - suma,2.0);
    }

    // dzielimy przez n-1
    if (chan_count == 1)
    {
        standard_deriv = 0.0;
    }
    else
    {
        standard_deriv = standard_deriv / ((chan_count * chan_count)-1.0);
        standard_deriv = sqrt(standard_deriv);
    }
    double final_error = sumaer;//sqrt(standard_deriv*standard_deriv + sumaer*sumaer / 3.0);

    vector < double > return_value (2);
    //cout << suma << endl;
    return_value[0] = suma;
    return_value[1] = final_error;
    return return_value;
}

// -- liczy srednia po predkosci - dla wszystkich epok --
void body::calculate_aver_over_velocity()
{
    if (loaded_data == 0)
    {
        //cout << endl;
        //cout << "----> Please load data first!" << endl;
        //cout << endl;
        // ee
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    int min, max;
    QString mins,maxs;
    mins = starting_channel.toPlainText();
    maxs = ending_channel.toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString())-1;
        max = stoi(maxs.toStdString())-1;
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return;
    }

    // -- kilka szczególnych przypadków złej obsługi metody --
    // początkowy channel większy od końcowego channel
    if (min > max)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel > max channel!"));
        return;
    }

    // początkowy channel mniejszy od 0
    if (min < 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel < 1!"));
        return;
    }

    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > Ilst[0].size()-1)
        max = Ilst[0].size()-1;

    chan4int_start = min;
    chan4int_end = max;

    // -- integrujemy --
    vector < double > wynik (2);
    for(unsigned int i = 0; i < Ilst.size(); i++)
    {
        // I
        wynik = average_over_velocity(chan4int_start, chan4int_end, Ilst[i], ERRlst[i]);
        averaged_over_velocity_I.push_back(wynik[0]);
        averaged_over_velocity_I_err.push_back(wynik[1]);

        // V
        wynik = average_over_velocity(chan4int_start, chan4int_end, Vlst[i], VERRlst[i]);
        averaged_over_velocity_V.push_back(wynik[0]);
        averaged_over_velocity_V_err.push_back(wynik[1]);

        // LHC
        wynik = average_over_velocity(chan4int_start, chan4int_end, LHClst[i], LHCERRlst[i]);
        averaged_over_velocity_LHC.push_back(wynik[0]);
        averaged_over_velocity_LHC_err.push_back(wynik[1]);

        // RHC
        wynik = average_over_velocity(chan4int_start, chan4int_end, RHClst[i], RHCERRlst[i]);
        averaged_over_velocity_RHC.push_back(wynik[0]);
        averaged_over_velocity_RHC_err.push_back(wynik[1]);
    }
    //cout << "----> Averaged over channels " << min << " -> " << max << endl;
    // -- zapisujemy do pliku --
    // liczymy srednia predkosc radialna
    double velaver = (VELlst[0][max] + VELlst[0][min]) / 2.0;
    ofstream integ;
    string filename = working_directory + "/" + srcname + "_averaged_over_velocity_chan_" + to_string(min+1) + "_to_" + to_string(max+1) + ".DAT";
    integ.open(filename.c_str());

    if(include_pytime->isChecked())
    {
        integ << "# time_in_isoformat MJD year I err V err LHC err RHC err" << endl;
        integ << "# VEL: " << velaver << endl;
        for(int i = 0; i < Ilst.size(); i++)
        {
            integ << fixed << setprecision(11) << pytime_format[i] << "   " <<  mjdlst[i] << "   " <<  yrlst[i] << "   " << averaged_over_velocity_I[i] << "   " <<  averaged_over_velocity_I_err[i] << "   " << averaged_over_velocity_V[i] << "   " << averaged_over_velocity_V_err[i] << "   " << averaged_over_velocity_LHC[i] << "   " << averaged_over_velocity_LHC_err[i] << "   " << averaged_over_velocity_RHC[i] << "   " << averaged_over_velocity_RHC_err[i] <<  endl;
        }
    }
    else
    {
        integ << "# MJD year I err V err LHC err RHC err" << endl;
        integ << "# VEL: " << velaver << endl;
        for(int i = 0; i < Ilst.size(); i++)
        {
            integ << fixed << setprecision(11) << mjdlst[i] << "   " <<  yrlst[i] << "   " << averaged_over_velocity_I[i] << "   " <<  averaged_over_velocity_I_err[i] << "   " << averaged_over_velocity_V[i] << "   " << averaged_over_velocity_V_err[i] << "   " << averaged_over_velocity_LHC[i] << "   " << averaged_over_velocity_LHC_err[i] << "   " << averaged_over_velocity_RHC[i] << "   " << averaged_over_velocity_RHC_err[i] <<  endl;
        }
    }

    integ.close();
    averaged_over_velocity_I.clear();
    averaged_over_velocity_V.clear();
    averaged_over_velocity_LHC.clear();
    averaged_over_velocity_RHC.clear();
    averaged_over_velocity_I_err.clear();
    averaged_over_velocity_V_err.clear();
    averaged_over_velocity_LHC_err.clear();
    averaged_over_velocity_RHC_err.clear();

    string message = "";
    message = "Averaged over channels " + to_string(min+1) + " -> " + to_string(max+1) + "\n" + "Saved to " + filename;
    close_window_for_aver_over_velocity();
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
    if (loaded_data == 0)
    {
        //cout << endl;
        //cout << "----> Please load data first!" << endl;
        //cout << endl;
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    QString mins,maxs;
    mins = starting_channel.toPlainText();
    maxs = ending_channel.toPlainText();
    int min, max;

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString())-1;
        max = stoi(maxs.toStdString())-1;
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return;
    }

    if (min > max)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min epoch > max epoch!"));
        return;
    }
    if (min < 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Bad min epoch!"));
    }

    if (max > mjdlst.size()-1)
        max = mjdlst.size()-1;

    for(int channel = 0; channel < CHANlst[0].size(); channel++)
    {
        // tworzymy bloki time series
        vector < double > I_timeseries, I_timeseries_err;
        vector < double > V_timeseries, V_timeseries_err;
        vector < double > LHC_timeseries, LHC_timeseries_err;
        vector < double > RHC_timeseries, RHC_timeseries_err;
        vector < double > wynik(2);
        // generujemy light_curves
        for (int i = 0; i < mjdlst.size(); i++)
        {
            // I
            I_timeseries.push_back(Ilst[i][channel]);
            I_timeseries_err.push_back(ERRlst[i][channel]);

            // V
            V_timeseries.push_back(Vlst[i][channel]);
            V_timeseries_err.push_back(VERRlst[i][channel]);

            // LHC
            LHC_timeseries.push_back(LHClst[i][channel]);
            LHC_timeseries_err.push_back(LHCERRlst[i][channel]);

            // RHC
            RHC_timeseries.push_back(RHClst[i][channel]);
            RHC_timeseries_err.push_back(RHCERRlst[i][channel]);
        }

        // liczymy average
        wynik = average_over_time(min, max, I_timeseries, I_timeseries_err);
        averaged_over_time_I.push_back(wynik[0]);
        averaged_over_time_I_err.push_back(wynik[1]);
        wynik = average_over_time(min, max, V_timeseries, V_timeseries_err);
        averaged_over_time_V.push_back(wynik[0]);
        averaged_over_time_V_err.push_back(wynik[1]);
        wynik = average_over_time(min, max, LHC_timeseries, LHC_timeseries_err);
        averaged_over_time_LHC.push_back(wynik[0]);
        averaged_over_time_LHC_err.push_back(wynik[1]);
        wynik = average_over_time(min, max, RHC_timeseries, RHC_timeseries_err);
        averaged_over_time_RHC.push_back(wynik[0]);
        averaged_over_time_RHC_err.push_back(wynik[1]);

    }

    // -- zapisujemy do pliku --

    ofstream integ;
    string filename = working_directory + "/" + srcname + "_averaged_over_time_epoch_" + to_string(min+1) + "_to_" + to_string(max+1) + ".DAT";
    integ.open(filename.c_str());
    integ << "# channel velocity I err V err LHC err RHC err" << endl;
    for(int i = 0; i < CHANlst[0].size(); i++)
    {
        integ << fixed << setprecision(11) << CHANlst[0][i] << "   " <<  VELlst[0][i] << "   " << averaged_over_time_I[i] << "   " <<  averaged_over_time_I_err[i] << "   " << averaged_over_time_V[i] << "   " << averaged_over_time_V_err[i] << "   " << averaged_over_time_LHC[i] << "   " << averaged_over_time_LHC_err[i] << "   " << averaged_over_time_RHC[i] << "   " << averaged_over_time_RHC_err[i] <<  endl;
    }
    integ.close();
    averaged_over_time_I.clear();
    averaged_over_time_V.clear();
    averaged_over_time_LHC.clear();
    averaged_over_time_RHC.clear();
    averaged_over_time_I_err.clear();
    averaged_over_time_V_err.clear();
    averaged_over_time_LHC_err.clear();
    averaged_over_time_RHC_err.clear();

    string message;
    message = "Averaged over epochs: " + to_string(min + 1) + " " + " -> " + to_string(max + 1) + "\n";
    message = message + "Saved to " + filename;
    close_window_for_aver_over_time();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));


}

// -- liczy VI, FI i chi2red dla jednego kanału --
vector < double >  body::spectral_index_from_lcs(int min_epoch, int max_epoch, vector < double > time_series, vector < double > error)
{
    double max_flux, err_of_max;
    int index_of_max;
    vector < double > params (3);
    params = max_w_index(min_epoch, max_epoch,time_series, error);
    max_flux = params[0];
    err_of_max = params[1];
    index_of_max = int(params[2]);
    double min_flux, err_of_min;
    int index_of_min;
    params = min_w_index(min_epoch, max_epoch,time_series, error);
    min_flux = params[0];
    err_of_min = params[1];
    index_of_min = int(params[2]);

    if (min_epoch < 0)
        min_epoch = 0;
    if (max_epoch < min_epoch)
        max_epoch = min_epoch;
    int time_span = max_epoch - min_epoch + 1;

    // srednia
    double mean = 0.0;
    for (int i = 0; i < time_span; i++)
    {
        mean = mean + time_series[min_epoch + i];
    }

    mean = mean / time_span;

    // -- liczymy VI
    double VI;
    if (min_flux < 0.0)
        min_flux = 0.0;

    if (max_flux > 3.0 * err_of_max && (max_flux - err_of_max) + (min_flux + err_of_min) > 0.1)
        VI = ((max_flux - err_of_max) - (min_flux + err_of_min)) / ((max_flux - err_of_max) + (min_flux + err_of_min));
    else
        VI = 0.0;

    // -- liczymy FI --
    // wagi
    vector < double > weight (error.size());
    for (int i = 0; i < error.size(); i++)
    {
        weight[i] = 1.0 / (error[i]*error[i]);
    }
    // trzy sumy
    double sum1 = 0.0;
    double sum2 = 0.0;
    double sum3 = 0.0;
    // liczymy sumy
    for(int i = 0; i < time_span; i++)
    {
        sum1 = sum1 + (time_series[min_epoch + i]*time_series[min_epoch + i] ) * weight[min_epoch + i];
        sum2 = sum2 + (time_series[min_epoch + i] * weight[min_epoch + i]);
        sum3 = sum3 + weight[min_epoch + i];
    }
    // liczymy FI
    sum2 = mean * sum2;
    double FI;
    if (time_span == 1 || sum1 == 0.0 || sum2 == 0.0 || mean < 0.1)
        FI = 0.0;
    else
        FI = sqrt(abs((((sum1 - sum2)/(time_span-1)) - 1.0) * time_span / sum3)) * 1.0 / mean;

    if (FI < 0.0)
        FI = 0.0;

    // liczymy chi2

    double sum_chi = 0.0;
    for(int i = 0; i < time_span; i++)
    {
        sum_chi = sum_chi + pow(((time_series[min_epoch + i] - mean) / (error[min_epoch + i] )),2);
    }
    double chi2;
    if (time_span <= 1)
        chi2 = 0.0;
    else
        chi2 = 1.0 / (time_span - 1) * sum_chi;

    vector < double > wynik (3);
    wynik[0] = VI;
    wynik[1] = FI;
    wynik[2] = chi2;
    return wynik;
}

// -- znajduje maksimum w zadanej w argumencie serii czasowej --
vector < double >  body::max_w_index(int min_epoch, int max_epoch, vector < double > time_series, vector < double > error)
{
    if (min_epoch < 0)
        min_epoch = 0;
    if (max_epoch < min_epoch)
        max_epoch = min_epoch;
    int time_span = max_epoch - min_epoch + 1;

    double max_value;
    double index_of_maximum = 0.0;
    max_value = 0.0;
    max_value = time_series[0];
    for (int i = 0; i < time_span; i++)
    {
        if (time_series[min_epoch + i] > max_value)
        {
            max_value = time_series[min_epoch + i];
            index_of_maximum = double(min_epoch + i);
        }
    }
    vector < double > wynik (3);
    wynik[0] = max_value;
    wynik[1] = error[int(index_of_maximum)];
    wynik[2] = index_of_maximum;
    return wynik;
}

// -- znajduje minimum w zadanej w argumencie serii czasowej --
vector < double >  body::min_w_index(int min_epoch, int max_epoch, vector < double > time_series, vector < double > error)
{
        if (min_epoch < 0)
            min_epoch = 0;
        if (max_epoch < min_epoch)
            max_epoch = min_epoch;
        int time_span = max_epoch - min_epoch + 1;

        double max_value;
        double index_of_maximum = 0.0;
        max_value = 0.0;
        for (int i = 0; i < time_span; i++)
        {
            if (time_series[min_epoch + i] < max_value && time_series[min_epoch + i] > 0.0+error[min_epoch+i])
            {
                max_value = time_series[min_epoch + i];
                index_of_maximum = double(min_epoch + i);
            }
        }
        vector < double > wynik (3);
        wynik[0] = max_value;
        wynik[1] = error[int(index_of_maximum)];
        wynik[2] = index_of_maximum;
        return wynik;
}

// -- liczy VI, FI i chi2red dla wszystkich kanałów --
void body::calculate_spectral_index()
{
    if (loaded_data == 0)
    {
        //cout << endl;
        //cout << "----> Please load data first!" << endl;
        //cout << endl;
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    QString mins,maxs;
    mins = starting_channel.toPlainText();
    maxs = ending_channel.toPlainText();
    int min, max;

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString())-1;
        max = stoi(maxs.toStdString())-1;
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return;
    }

    if (min > max)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min epoch > max epoch!"));
        return;
    }
    if (min < 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Bad min epoch!"));
    }

    if (max > mjdlst.size()-1)
        max = mjdlst.size()-1;


    for(int channel = 0; channel < CHANlst[0].size(); channel++)
    {
        // tworzymy bloki time series
        vector < double > I_timeseries, I_timeseries_err;
        vector < double > V_timeseries, V_timeseries_err;
        vector < double > LHC_timeseries, LHC_timeseries_err;
        vector < double > RHC_timeseries, RHC_timeseries_err;
        vector < double > wynik(3);
        // generujemy light_curves
        for (int i = 0; i < mjdlst.size(); i++)
        {
            // I
            I_timeseries.push_back(Ilst[i][channel]);
            I_timeseries_err.push_back(ERRlst[i][channel]);

            // V
            V_timeseries.push_back(Vlst[i][channel]);
            V_timeseries_err.push_back(VERRlst[i][channel]);

            // LHC
            LHC_timeseries.push_back(LHClst[i][channel]);
            LHC_timeseries_err.push_back(LHCERRlst[i][channel]);

            // RHC
            RHC_timeseries.push_back(RHClst[i][channel]);
            RHC_timeseries_err.push_back(RHCERRlst[i][channel]);
        }
        // liczymy average
        // I
        wynik = spectral_index_from_lcs(min, max, I_timeseries, I_timeseries_err);
        VI_I.push_back(wynik[0]);
        FI_I.push_back(wynik[1]);
        chi2_I.push_back(wynik[2]);
        // V
        wynik = spectral_index_from_lcs(min, max, V_timeseries, V_timeseries_err);
        VI_V.push_back(wynik[0]);
        FI_V.push_back(wynik[1]);
        chi2_V.push_back(wynik[2]);
        // LHC
        wynik = spectral_index_from_lcs(min, max, LHC_timeseries, LHC_timeseries_err);
        VI_LHC.push_back(wynik[0]);
        FI_LHC.push_back(wynik[1]);
        chi2_LHC.push_back(wynik[2]);
        // RHC
        wynik = spectral_index_from_lcs(min, max, RHC_timeseries, RHC_timeseries_err);
        VI_RHC.push_back(wynik[0]);
        FI_RHC.push_back(wynik[1]);
        chi2_RHC.push_back(wynik[2]);

    }

    // -- zapisujemy do pliku --

    ofstream integ;
    string filename = working_directory + "/" + srcname + "_VI_spind_epoch_" + to_string(min+1) + "_to_" + to_string(max+1) + ".DAT";
    integ.open(filename.c_str());
    integ << "# channel velocity I V LHC RHC " << endl;
    for(int i = 0; i < CHANlst[0].size(); i++)
    {
        integ << fixed << setprecision(11) << CHANlst[0][i] << "   " <<  VELlst[0][i] << "   " << VI_I[i] << "   " <<  VI_V[i] << "   " << VI_LHC[i] << "   " << VI_RHC[i] << endl;// << "   " << averaged_over_time_LHC[i] << "   " << averaged_over_time_LHC_err[i] << "   " << averaged_over_time_RHC[i] << "   " << averaged_over_time_RHC_err[i] <<  endl;
    }
    integ.close();

    string filenamefi = working_directory + "/" + srcname + "_FI_spind_epoch_" + to_string(min+1) + "_to_" + to_string(max+1) + ".DAT";
    integ.open(filenamefi.c_str());
    integ << "# channel velocity I V LHC RHC " << endl;
    for(int i = 0; i < CHANlst[0].size(); i++)
    {
        integ << fixed << setprecision(11) << CHANlst[0][i] << "   " <<  VELlst[0][i] << "   " << FI_I[i] << "   " <<  FI_V[i] << "   " << FI_LHC[i] << "   " << FI_RHC[i] << endl;// << "   " << averaged_over_time_LHC[i] << "   " << averaged_over_time_LHC_err[i] << "   " << averaged_over_time_RHC[i] << "   " << averaged_over_time_RHC_err[i] <<  endl;
    }
    integ.close();

    string filenamechi2 = working_directory + "/" + srcname + "_chi2_spind_epoch_" + to_string(min+1) + "_to_" + to_string(max+1) + ".DAT";
    integ.open(filenamechi2.c_str());
    integ << "# channel velocity I V LHC RHC " << endl;
    for(int i = 0; i < CHANlst[0].size(); i++)
    {
        integ << fixed << setprecision(11) << CHANlst[0][i] << "   " <<  VELlst[0][i] << "   " << chi2_I[i] << "   " <<  chi2_V[i] << "   " << chi2_LHC[i] << "   " << chi2_RHC[i] << endl;// << "   " << averaged_over_time_LHC[i] << "   " << averaged_over_time_LHC_err[i] << "   " << averaged_over_time_RHC[i] << "   " << averaged_over_time_RHC_err[i] <<  endl;
    }
    integ.close();

    averaged_over_time_I.clear();
    averaged_over_time_V.clear();
    averaged_over_time_LHC.clear();
    averaged_over_time_RHC.clear();
    averaged_over_time_I_err.clear();
    averaged_over_time_V_err.clear();
    averaged_over_time_LHC_err.clear();
    averaged_over_time_RHC_err.clear();

    // -- czyscimy tablice ch2 etc --
    chi2_I.clear();
    chi2_V.clear();
    chi2_LHC.clear();
    chi2_RHC.clear();
    VI_I.clear();
    VI_V.clear();
    VI_LHC.clear();
    VI_RHC.clear();
    FI_I.clear();
    FI_V.clear();
    FI_LHC.clear();
    FI_RHC.clear();


    /*
    cout << endl;
    cout << "----> Spectral-indexed over epochs: " << min + 1 << " -> " << max + 1 << endl;
    cout << "----> VI Saved to " << filename << endl;
    cout << "----> FI Saved to " << filenamefi << endl;
    cout << "----> chi2 Saved to " << filenamechi2 << endl;
    cout << endl;
    */
    string message;
    message = "Spectral-indexed over epochs: " + to_string(min + 1) + " " + " -> " + to_string(max + 1) + "\n";
    message = message + "VI Saved to " + filename + "\n";
    message = message + "FI Saved to " + filenamefi + "\n";
    message = message + "chi2 Saved to " + filenamechi2 + "\n";
    close_window_for_spind();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}

// -- dodaje do wykresu single spectrum wykresy --
void body::combo_box_display()
{
    string buf;
    QString bufor;
    int n_of_obs;
    bufor = list_of_observations->currentText();
    buf = bufor.toStdString();
    stringstream ss (buf);
    ss >> n_of_obs;
    n_of_obs = n_of_obs - 1;
    int marker = n_of_obs;
    last_marker = marker;
    // -- gromadzimy dane --
    QVector < double > x(n_chanslst[marker]), y(n_chanslst[marker]);
    // zapelniamy wektor
    for(unsigned int i = 0; i < Ilst[marker].size(); i++)
    {
        x[i] = VELlst[marker][i];
        y[i] = Ilst[marker][i];
    }
    // -- dodajemy do wykresu --
    spectrum.addGraph();
    n_graphs_on_single_spec = n_graphs_on_single_spec + 1;
    // -- dodajemy do grafiki dane --
    spectrum.graph(n_graphs_on_single_spec-1)->setData(x,y);
    // -- ustalamy kolor --
    QPen penis;
    penis.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    spectrum.graph(n_graphs_on_single_spec-1)->setPen(penis);
    // -- replotujemy --
    spectrum.replot();

    // -- dodajemy do tablicy z indeksami plotowanych obserwacji
    numbers_of_epochs_on_single_spec.push_back(marker);


}

// -- ustala zasięg na wykresie single spectrum --
void body::set_default_range()
{
    QVector < double > x(n_chanslst[last_marker]), y(n_chanslst[last_marker]);
    // zapelniamy wektor
    for(unsigned int i = 0; i < Ilst[last_marker].size(); i++)
    {
        x[i] = VELlst[last_marker][i];
        y[i] = Ilst[last_marker][i];
    }
    // ustalamy range
    double veldiff = *max_element(x.begin(), x.end()) - *min_element(x.begin(), x.end());
    spectrum.xAxis->setRange(*min_element(x.begin(), x.end()) - 0.05 * veldiff, *max_element(x.begin(), x.end())  + 0.05 * veldiff);
    spectrum.yAxis->setRange(*min_element(y.begin(), y.end()) - 0.05 * (*max_element(y.begin(), y.end())), *max_element(y.begin(), y.end())  + 0.05 * (*max_element(y.begin(), y.end())));
    spectrum.replot();

}

// -- usuwa wybrany plot z single spectrum --
void body::remove_selected_graph()
{
    /*
    if(spectrum.selectedGraphs().size() > 0)
    {
        spectrum.removeGraph(spectrum.selectedGraphs().first());
        spectrum.replot();
    }
    n_graphs_on_single_spec = n_graphs_on_single_spec - 1;
    */
    // -- popujemy z tablicy z indeksami plotowanych obserwacji --



    if (n_graphs_on_single_spec > 0)
    {
        last_marker = numbers_of_epochs_on_single_spec[numbers_of_epochs_on_single_spec.size()-1];
        numbers_of_epochs_on_single_spec.pop_back();
        spectrum.removeGraph(n_graphs_on_single_spec-1);
        n_graphs_on_single_spec = n_graphs_on_single_spec - 1;
    }
    //cout << n_graphs_on_single_spec << endl; //ww
    spectrum.replot();
}

// -- zapisuje wykresy z single spectrum do pliku, czytelnego dla gnuplota 00
void body::save_plots_from_single_spectrum()
{

    int count = numbers_of_epochs_on_single_spec.size(); // ilosc wybranych widm
    // -- petla, zapisujaca do plikow --
    for (int i = 0; i < count; i++)
    {
        int epoch = numbers_of_epochs_on_single_spec[i];
        string filename;
        filename = working_directory + "/" + srcname + "_" + to_string(int(mjdlst[epoch])) + "_" + to_string(epoch+1) + "_spectrum.dat";
        ofstream plik;
        plik.open(filename);
        plik << "# chan vel I er V er LHC er RHC er" << endl;
        for (int ee = 0; ee < CHANlst[epoch].size(); ee++)
        {
            plik << fixed << setprecision(11) << CHANlst[epoch][ee] << "   " <<  VELlst[epoch][ee] << "   " << Ilst[epoch][ee] << "   " << ERRlst[epoch][ee] << "   " << Vlst[epoch][ee] <<  "   " << VERRlst[epoch][ee] <<  "   " << LHClst[epoch][ee] <<  "   " << LHCERRlst[epoch][ee] <<  "   " << RHClst[epoch][ee] <<  "   " << RHCERRlst[epoch][ee] << endl;
        }
        plik.close();
        //cout << "----> Saved to " << filename << endl;
        string message;
        message = "Saved to " + filename;
        QMessageBox::information(&window, tr("Message to you!"), QString::fromStdString(message));
    }

}

// -- ustala, który z przycisków I V LHC RHC na widmie dynamicznym powinien być wciśnięty --
void body::set_down_IVLHCRHCbuttons()
{
    // -- buttony i boole --
    if(I_pressed == 1)
    {
        Ibut.setDown(true);
        LHCbut.setDown(false);
        RHCbut.setDown(false);
        Vbut.setDown(false);
    }
    else if (lhc_pressed == 1)
    {
        Ibut.setDown(false);
        LHCbut.setDown(true);
        RHCbut.setDown(false);
        Vbut.setDown(false);
    }
    else if(rhc_pressed == 1)
    {
        Ibut.setDown(false);
        LHCbut.setDown(false);
        RHCbut.setDown(true);
        Vbut.setDown(false);
    }
    else if(v_pressed == 1)
    {
        Ibut.setDown(false);
        LHCbut.setDown(false);
        RHCbut.setDown(false);
        Vbut.setDown(true);
    }

    window.show();
}

// -- wyświetla layout do integrate (przyciski i text edity z numerami kanałów)
void body::calculate_integrate_for_time_series_with_buttons()
{
    if (integrate_window_opened == 1)
        return;

    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (wd_section_opened == 1 || calibration_section_opened == 1 || spind_window_opened == 1 || aver_over_time_window_opened == 1 || aver_over_velocity_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }
    /*
    QWidget window_for_integrate;
    QPushButton make_int;
    QPushButton cancel;
    QTextEdit starting_channel;
    QTextEdit ending_channel;
    QHBoxLayout start;
    QHBoxLayout end;
    QHBoxLayout butterbean;
    QVBoxLayout integrate_layout;
    QLabel start_label;
    QLabel end_label;
    */
    //window_for_integrate.setVisible(true);
    //window_for_integrate.setAttribute(Qt::WA_DeleteOnClose);
    start_label.setVisible(true);
    end_label.setVisible(true);
    cancel.setVisible(true);
    make_int.setVisible(true);
    starting_channel.setVisible(true);
    ending_channel.setVisible(true);

    starting_channel.setMaximumSize(100,30);
    ending_channel.setMaximumSize(100,30);

    starting_channel.setMinimumSize(0,0);
    ending_channel.setMinimumSize(0,0);

    //cancel.setMaximumSize(30,30);
    //make_int.setMaximumSize(30,30);

    cancel.setMinimumSize(0,0);
    make_int.setMinimumSize(0,0);

    //start.setMaximumSize(100,30);
    //end.setMaximumSize(100,30);

    //start.setMinimumSize(0,0);
    //end.setMinimumSize(0,0);

    start_label.setText("Start Channel");
    end_label.setText("End Channel");
    make_int.setText("Integrate");
    cancel.setText("Cancel");
    //if (integrate_window_loaded == 0)
    //{
    start.addWidget(&start_label,Qt::AlignHCenter);
    start.addWidget(&starting_channel,Qt::AlignHCenter);
    end.addWidget(&end_label,Qt::AlignHCenter);
    end.addWidget(&ending_channel,Qt::AlignHCenter);
    butterbean.addWidget(&cancel,Qt::AlignHCenter);
    butterbean.addWidget(&make_int,Qt::AlignHCenter);
    integrate_layout.addLayout(&start,Qt::AlignHCenter);
    integrate_layout.addLayout(&end,Qt::AlignHCenter);
    integrate_layout.addLayout(&butterbean,Qt::AlignHCenter);

    //integrate_window_loaded = 1;
    //}

    if (intgridloaded == 0)
    {
        if (single_spectrum_opened == 1 || dynamic_spectrum_opened == 1)
        {
            vbox_main.addLayout(&integrate_layout,Qt::AlignLeft);
            intgridloaded = 1;

        }
        else
        {
            vbox_main.addLayout(&integrate_layout,Qt::AlignLeft);
            intgridloaded = 1;
        }
    }
    vbox_main.update();
    grid.update();
    //window_for_integrate.setGeometry(300,300,300,300);

    bool chan4int_loaded = read_chan4int();
    if(dynamic_spectrum_opened == 1)
    {
        starting_channel.setText(QString::fromStdString(to_string(min_range_vel_index+1)));
        ending_channel.setText((QString::fromStdString(to_string(max_range_vel_index+1))));
    }
    else if (chan4int_loaded == 1)
    {
        starting_channel.setText(QString::fromStdString(to_string(chan4int_start)));
        ending_channel.setText(QString::fromStdString(to_string(chan4int_end)));
    }

    QPushButton::connect(&cancel, SIGNAL(clicked()), this, SLOT(close_window_for_integrate()));
    QPushButton::connect(&make_int, SIGNAL(clicked()), this, SLOT(integrate_time_series()));


    window.show();
    integrate_window_opened = 1;

}

// -- zamyka poprzedni layout --
void body::close_window_for_integrate()
{
    start.removeWidget(&start_label);
    start.removeWidget(&starting_channel);
    end.removeWidget(&end_label);
    end.removeWidget(&ending_channel);
    butterbean.removeWidget(&cancel);
    butterbean.removeWidget(&make_int);
    integrate_layout.removeItem(&start);
    integrate_layout.removeItem(&end);
    integrate_layout.removeItem(&butterbean);
    //window_for_integrate.setVisible(false);
    start_label.setVisible(false);
    end_label.setVisible(false);
    cancel.setVisible(false);
    make_int.setVisible(false);
    starting_channel.setVisible(false);
    ending_channel.setVisible(false);
    vbox_main.removeItem(&integrate_layout);
    window.show();
    grid.update();
    vbox_main.update();
    intgridloaded = 0;
    QPushButton::disconnect(&make_int, SIGNAL(clicked()), this, SLOT(integrate_time_series()));
    QPushButton::disconnect(&cancel, SIGNAL(clicked()), this, SLOT(close_window_for_integrate()));
    integrate_window_opened = 0;
}

// -- layout do liczenia VI FI i chi2red --
void body::calculate_spectral_index_for_time_series_with_buttons()
{
    if (spind_window_opened == 1)
        return;

    if (loaded_data == 0)
    {
        /*
        cout << endl;
        cout << "----> Please load data first!" << endl;
        cout << endl;
        */
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (wd_section_opened == 1 || calibration_section_opened == 1 | integrate_window_opened == 1 || aver_over_time_window_opened == 1 || aver_over_velocity_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }
    /*
    QWidget window_for_integrate;
    QPushButton make_int;
    QPushButton cancel;
    QTextEdit starting_channel;
    QTextEdit ending_channel;
    QHBoxLayout start;
    QHBoxLayout end;
    QHBoxLayout butterbean;
    QVBoxLayout integrate_layout;
    QLabel start_label;
    QLabel end_label;
    */
    //window_for_integrate.setVisible(true);
    //window_for_integrate.setAttribute(Qt::WA_DeleteOnClose);
    start_label.setVisible(true);
    end_label.setVisible(true);
    cancel.setVisible(true);
    make_int.setVisible(true);
    starting_channel.setVisible(true);
    ending_channel.setVisible(true);

    starting_channel.setMaximumSize(100,30);
    ending_channel.setMaximumSize(100,30);

    starting_channel.setMinimumSize(0,0);
    ending_channel.setMinimumSize(0,0);

    //cancel.setMaximumSize(30,30);
    //make_int.setMaximumSize(30,30);

    cancel.setMinimumSize(0,0);
    make_int.setMinimumSize(0,0);

    //start.setMaximumSize(100,30);
    //end.setMaximumSize(100,30);

    //start.setMinimumSize(0,0);
    //end.setMinimumSize(0,0);

    start_label.setText("Start epoch");
    end_label.setText("End epoch");
    make_int.setText("Spindicate");
    cancel.setText("Cancel");
    //if (integrate_window_loaded == 0)
    //{
    start.addWidget(&start_label,Qt::AlignHCenter);
    start.addWidget(&starting_channel,Qt::AlignHCenter);
    end.addWidget(&end_label,Qt::AlignHCenter);
    end.addWidget(&ending_channel,Qt::AlignHCenter);
    butterbean.addWidget(&cancel,Qt::AlignHCenter);
    butterbean.addWidget(&make_int,Qt::AlignHCenter);
    integrate_layout.addLayout(&start,Qt::AlignHCenter);
    integrate_layout.addLayout(&end,Qt::AlignHCenter);
    integrate_layout.addLayout(&butterbean,Qt::AlignHCenter);

    //integrate_window_loaded = 1;
    //}

    if (intgridloaded == 0)
    {
        if (single_spectrum_opened == 1 || dynamic_spectrum_opened == 1)
        {
            vbox_main.addLayout(&integrate_layout,Qt::AlignLeft);
            intgridloaded = 1;

        }
        else
        {
            vbox_main.addLayout(&integrate_layout,Qt::AlignLeft);
            intgridloaded = 1;
        }
    }
    vbox_main.update();
    grid.update();
    //window_for_integrate.setGeometry(300,300,300,300);

    //bool chan4int_loaded = read_chan4int();

    starting_channel.setText(QString::fromStdString(to_string(1)));
    ending_channel.setText(QString::fromStdString(to_string(Ilst.size())));

    QPushButton::connect(&cancel, SIGNAL(clicked()), this, SLOT(close_window_for_spind()));
    QPushButton::connect(&make_int, SIGNAL(clicked()), this, SLOT(calculate_spectral_index()));

    window.show();
    spind_window_opened = 1;
}

// -- zamyka layout do liczenia VI FI i chi2red --
void body::close_window_for_spind()
{
    start.removeWidget(&start_label);
    start.removeWidget(&starting_channel);
    end.removeWidget(&end_label);
    end.removeWidget(&ending_channel);
    butterbean.removeWidget(&cancel);
    butterbean.removeWidget(&make_int);
    integrate_layout.removeItem(&start);
    integrate_layout.removeItem(&end);
    integrate_layout.removeItem(&butterbean);
    //window_for_integrate.setVisible(false);
    start_label.setVisible(false);
    end_label.setVisible(false);
    cancel.setVisible(false);
    make_int.setVisible(false);
    starting_channel.setVisible(false);
    ending_channel.setVisible(false);
    vbox_main.removeItem(&integrate_layout);
    window.show();
    grid.update();
    vbox_main.update();
    intgridloaded = 0;
    QPushButton::disconnect(&make_int, SIGNAL(clicked()), this, SLOT(calculate_spectral_index()));
    QPushButton::disconnect(&cancel, SIGNAL(clicked()), this, SLOT(close_window_for_spind()));
    spind_window_opened = 0;
}

// -- layout do liczenia średniej po prędkościach --
void body::calculate_aver_over_velocity_for_time_series_with_buttons()
{
    if (aver_over_velocity_window_opened == 1)
        return;

    if (loaded_data == 0)
    {
        /*
        cout << endl;
        cout << "----> Please load data first!" << endl;
        cout << endl;
        */
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (wd_section_opened == 1 || calibration_section_opened == 1 | integrate_window_opened == 1 || aver_over_time_window_opened == 1 || spind_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }
    /*
    QWidget window_for_integrate;
    QPushButton make_int;
    QPushButton cancel;
    QTextEdit starting_channel;
    QTextEdit ending_channel;
    QHBoxLayout start;
    QHBoxLayout end;
    QHBoxLayout butterbean;
    QVBoxLayout integrate_layout;
    QLabel start_label;
    QLabel end_label;
    */
    //window_for_integrate.setVisible(true);
    //window_for_integrate.setAttribute(Qt::WA_DeleteOnClose);
    start_label.setVisible(true);
    end_label.setVisible(true);
    cancel.setVisible(true);
    make_int.setVisible(true);
    starting_channel.setVisible(true);
    ending_channel.setVisible(true);

    starting_channel.setMaximumSize(100,30);
    ending_channel.setMaximumSize(100,30);

    starting_channel.setMinimumSize(0,0);
    ending_channel.setMinimumSize(0,0);

    //cancel.setMaximumSize(30,30);
    //make_int.setMaximumSize(30,30);

    cancel.setMinimumSize(0,0);
    make_int.setMinimumSize(0,0);

    //start.setMaximumSize(100,30);
    //end.setMaximumSize(100,30);

    //start.setMinimumSize(0,0);
    //end.setMinimumSize(0,0);

    start_label.setText("Start channel");
    end_label.setText("End channel");
    make_int.setText("Aver over vel.");
    cancel.setText("Cancel");
    //if (integrate_window_loaded == 0)
    //{
    start.addWidget(&start_label,Qt::AlignHCenter);
    start.addWidget(&starting_channel,Qt::AlignHCenter);
    end.addWidget(&end_label,Qt::AlignHCenter);
    end.addWidget(&ending_channel,Qt::AlignHCenter);
    butterbean.addWidget(&cancel,Qt::AlignHCenter);
    butterbean.addWidget(&make_int,Qt::AlignHCenter);
    integrate_layout.addLayout(&start,Qt::AlignHCenter);
    integrate_layout.addLayout(&end,Qt::AlignHCenter);
    integrate_layout.addLayout(&butterbean,Qt::AlignHCenter);

    //integrate_window_loaded = 1;
    //}

    if (intgridloaded == 0)
    {
        if (single_spectrum_opened == 1 || dynamic_spectrum_opened == 1)
        {
            vbox_main.addLayout(&integrate_layout,Qt::AlignLeft);
            intgridloaded = 1;

        }
        else
        {
            vbox_main.addLayout(&integrate_layout,Qt::AlignLeft);
            intgridloaded = 1;
        }
    }
    vbox_main.update();
    grid.update();
    //window_for_integrate.setGeometry(300,300,300,300);

    //bool chan4int_loaded = read_chan4int();

    bool chan4int_loaded = read_chan4int();
    /*
    if (chan4int_loaded == 1)
    {
        starting_channel.setText(QString::fromStdString(to_string(chan4int_start)));
        ending_channel.setText(QString::fromStdString(to_string(chan4int_end)));
    }
    */
    if(dynamic_spectrum_opened == 1)
    {
        starting_channel.setText(QString::fromStdString(to_string(min_range_vel_index+1)));
        ending_channel.setText((QString::fromStdString(to_string(max_range_vel_index+1))));
    }
    else if (chan4int_loaded == 1)
    {
        starting_channel.setText(QString::fromStdString(to_string(chan4int_start)));
        ending_channel.setText(QString::fromStdString(to_string(chan4int_end)));
    }
    QPushButton::connect(&cancel, SIGNAL(clicked()), this, SLOT(close_window_for_aver_over_velocity()));
    QPushButton::connect(&make_int, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity()));

    window.show();
    aver_over_velocity_window_opened = 1;
}

// -- zamyka layout do liczenia średniej po prędkościach --
void body::close_window_for_aver_over_velocity()
{
    start.removeWidget(&start_label);
    start.removeWidget(&starting_channel);
    end.removeWidget(&end_label);
    end.removeWidget(&ending_channel);
    butterbean.removeWidget(&cancel);
    butterbean.removeWidget(&make_int);
    integrate_layout.removeItem(&start);
    integrate_layout.removeItem(&end);
    integrate_layout.removeItem(&butterbean);
    //window_for_integrate.setVisible(false);
    start_label.setVisible(false);
    end_label.setVisible(false);
    cancel.setVisible(false);
    make_int.setVisible(false);
    starting_channel.setVisible(false);
    ending_channel.setVisible(false);
    vbox_main.removeItem(&integrate_layout);
    window.show();
    grid.update();
    vbox_main.update();
    intgridloaded = 0;
    QPushButton::disconnect(&cancel, SIGNAL(clicked()), this, SLOT(close_window_for_aver_over_velocity()));
    QPushButton::disconnect(&make_int, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity()));
    aver_over_velocity_window_opened = 0;
}

// -- layout do liczenia średniej po czasie --
void body::calculate_aver_over_time_for_time_series_with_buttons()
{
    if (aver_over_time_window_opened == 1)
        return;

    if (loaded_data == 0)
    {
        /*
        cout << endl;
        cout << "----> Please load data first!" << endl;
        cout << endl;
        */
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (wd_section_opened == 1 || calibration_section_opened == 1 | integrate_window_opened == 1 || spind_window_opened == 1 || aver_over_velocity_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }
    /*
    QWidget window_for_integrate;
    QPushButton make_int;
    QPushButton cancel;
    QTextEdit starting_channel;
    QTextEdit ending_channel;
    QHBoxLayout start;
    QHBoxLayout end;
    QHBoxLayout butterbean;
    QVBoxLayout integrate_layout;
    QLabel start_label;
    QLabel end_label;
    */
    //window_for_integrate.setVisible(true);
    //window_for_integrate.setAttribute(Qt::WA_DeleteOnClose);
    start_label.setVisible(true);
    end_label.setVisible(true);
    cancel.setVisible(true);
    make_int.setVisible(true);
    starting_channel.setVisible(true);
    ending_channel.setVisible(true);

    starting_channel.setMaximumSize(100,30);
    ending_channel.setMaximumSize(100,30);

    starting_channel.setMinimumSize(0,0);
    ending_channel.setMinimumSize(0,0);

    //cancel.setMaximumSize(30,30);
    //make_int.setMaximumSize(30,30);

    cancel.setMinimumSize(0,0);
    make_int.setMinimumSize(0,0);

    //start.setMaximumSize(100,30);
    //end.setMaximumSize(100,30);

    //start.setMinimumSize(0,0);
    //end.setMinimumSize(0,0);

    start_label.setText("Start epoch");
    end_label.setText("End epoch");
    make_int.setText("Aver over time");
    cancel.setText("Cancel");
    //if (integrate_window_loaded == 0)
    //{
    start.addWidget(&start_label,Qt::AlignHCenter);
    start.addWidget(&starting_channel,Qt::AlignHCenter);
    end.addWidget(&end_label,Qt::AlignHCenter);
    end.addWidget(&ending_channel,Qt::AlignHCenter);
    butterbean.addWidget(&cancel,Qt::AlignHCenter);
    butterbean.addWidget(&make_int,Qt::AlignHCenter);
    integrate_layout.addLayout(&start,Qt::AlignHCenter);
    integrate_layout.addLayout(&end,Qt::AlignHCenter);
    integrate_layout.addLayout(&butterbean,Qt::AlignHCenter);

    //integrate_window_loaded = 1;
    //}

    if (intgridloaded == 0)
    {
        if (single_spectrum_opened == 1 || dynamic_spectrum_opened == 1)
        {
            vbox_main.addLayout(&integrate_layout,Qt::AlignLeft);
            intgridloaded = 1;

        }
        else
        {
            vbox_main.addLayout(&integrate_layout,Qt::AlignLeft);
            intgridloaded = 1;
        }
    }
    vbox_main.update();
    grid.update();
    //window_for_integrate.setGeometry(300,300,300,300);

    //bool chan4int_loaded = read_chan4int();

    starting_channel.setText(QString::fromStdString(to_string(1)));
    ending_channel.setText(QString::fromStdString(to_string(Ilst.size())));

    QPushButton::connect(&cancel, SIGNAL(clicked()), this, SLOT(close_window_for_aver_over_time()));
    QPushButton::connect(&make_int, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time()));

    window.show();
    aver_over_time_window_opened = 1;
}

// -- zamyka layout do liczenia średniej po czasie --
void body::close_window_for_aver_over_time()
{
    start.removeWidget(&start_label);
    start.removeWidget(&starting_channel);
    end.removeWidget(&end_label);
    end.removeWidget(&ending_channel);
    butterbean.removeWidget(&cancel);
    butterbean.removeWidget(&make_int);
    integrate_layout.removeItem(&start);
    integrate_layout.removeItem(&end);
    integrate_layout.removeItem(&butterbean);
    //window_for_integrate.setVisible(false);
    start_label.setVisible(false);
    end_label.setVisible(false);
    cancel.setVisible(false);
    make_int.setVisible(false);
    starting_channel.setVisible(false);
    ending_channel.setVisible(false);
    vbox_main.removeItem(&integrate_layout);
    window.show();
    grid.update();
    vbox_main.update();
    intgridloaded = 0;
    QPushButton::disconnect(&cancel, SIGNAL(clicked()), this, SLOT(close_window_for_aver_over_time()));
    QPushButton::disconnect(&make_int, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time()));
    aver_over_time_window_opened = 0;
}

// -- przeładowuje obecnie załadowane dane --
void body::reload_slot()
{
    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    if (AVRNAMES_from_load.size() != 0)
    {
        read_time_series_for_list(AVRNAMES_from_load);
    }
    else if (list_filename != "")
    {
        lista.open(list_filename.c_str());
        read_time_series();
    }

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

// -- eksportuje krzywą blasku z zaznaczenia na widmie dynamicznym --
void body::make_lcs_slot()
{
    chan4int_start = yind;
    chan4int_end = yind;
    int min, max;
    min = chan4int_start;
    max = chan4int_end;
    // -- integrujemy --
    vector < double > wynik (2);
    for(unsigned int i = 0; i < Ilst.size(); i++)
    {
        // I
        wynik = average_over_velocity(chan4int_start, chan4int_end, Ilst[i], ERRlst[i]);
        averaged_over_velocity_I.push_back(wynik[0]);
        averaged_over_velocity_I_err.push_back(wynik[1]);

        // V
        wynik = average_over_velocity(chan4int_start, chan4int_end, Vlst[i], VERRlst[i]);
        averaged_over_velocity_V.push_back(wynik[0]);
        averaged_over_velocity_V_err.push_back(wynik[1]);

        // LHC
        wynik = average_over_velocity(chan4int_start, chan4int_end, LHClst[i], LHCERRlst[i]);
        averaged_over_velocity_LHC.push_back(wynik[0]);
        averaged_over_velocity_LHC_err.push_back(wynik[1]);

        // RHC
        wynik = average_over_velocity(chan4int_start, chan4int_end, RHClst[i], RHCERRlst[i]);
        averaged_over_velocity_RHC.push_back(wynik[0]);
        averaged_over_velocity_RHC_err.push_back(wynik[1]);
    }
    //cout << "----> Averaged over channels " << min << " -> " << max << endl;
    // -- zapisujemy do pliku --
    // liczymy srednia predkosc radialna
    double velaver = (VELlst[0][chan4int_start] + VELlst[0][chan4int_end]) / 2.0;
    ofstream integ;
    string filename = working_directory + "/" + srcname + "_lc_chan_" + to_string(min+1) + ".DAT";
    integ.open(filename.c_str());

    /*
    integ << "# MJD year I err V err LHC err RHC err" << endl;
    integ << "# VEL: " << velaver << endl;
    for(int i = 0; i < Ilst.size(); i++)
    {
        integ << fixed << setprecision(11) << mjdlst[i] << "   " <<  yrlst[i] << "   " << averaged_over_velocity_I[i] << "   " <<  averaged_over_velocity_I_err[i] << "   " << averaged_over_velocity_V[i] << "   " << averaged_over_velocity_V_err[i] << "   " << averaged_over_velocity_LHC[i] << "   " << averaged_over_velocity_LHC_err[i] << "   " << averaged_over_velocity_RHC[i] << "   " << averaged_over_velocity_RHC_err[i] <<  endl;
    }
    */
    if(include_pytime->isChecked())
    {
        integ << "# time_in_isoformat MJD year I err V err LHC err RHC err" << endl;
        integ << "# VEL: " << velaver << endl;
        for(int i = 0; i < Ilst.size(); i++)
        {
            integ << fixed << setprecision(11) << pytime_format[i] << "   " <<  mjdlst[i] << "   " <<  yrlst[i] << "   " << averaged_over_velocity_I[i] << "   " <<  averaged_over_velocity_I_err[i] << "   " << averaged_over_velocity_V[i] << "   " << averaged_over_velocity_V_err[i] << "   " << averaged_over_velocity_LHC[i] << "   " << averaged_over_velocity_LHC_err[i] << "   " << averaged_over_velocity_RHC[i] << "   " << averaged_over_velocity_RHC_err[i] <<  endl;
        }
    }
    else
    {
        integ << "# MJD year I err V err LHC err RHC err" << endl;
        integ << "# VEL: " << velaver << endl;
        for(int i = 0; i < Ilst.size(); i++)
        {
            integ << fixed << setprecision(11) << mjdlst[i] << "   " <<  yrlst[i] << "   " << averaged_over_velocity_I[i] << "   " <<  averaged_over_velocity_I_err[i] << "   " << averaged_over_velocity_V[i] << "   " << averaged_over_velocity_V_err[i] << "   " << averaged_over_velocity_LHC[i] << "   " << averaged_over_velocity_LHC_err[i] << "   " << averaged_over_velocity_RHC[i] << "   " << averaged_over_velocity_RHC_err[i] <<  endl;
        }
    }
    integ.close();
    averaged_over_velocity_I.clear();
    averaged_over_velocity_V.clear();
    averaged_over_velocity_LHC.clear();
    averaged_over_velocity_RHC.clear();
    averaged_over_velocity_I_err.clear();
    averaged_over_velocity_V_err.clear();
    averaged_over_velocity_LHC_err.clear();
    averaged_over_velocity_RHC_err.clear();

    string message = "";
    message = "Created lc over channel " + to_string(min+1) + "\n" + "Saved to " + filename;
    //close_window_for_aver_over_velocity();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));


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

// -- funkcja do flagowania zaznaczonej na widmie dynamicznym epoki --
void body::flag_slot()
{
    // zapisujemy nazwe oflagowanego pliku
    string flagged_filename = avrnames[xind];

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
    flagi[flags_number-1]->topLeft->setCoords(double(xind)-0.5, VELlst[xind][0]);
    //cout << VELlst[xind][0] << endl;
    //cout << VELlst[xind][VELlst[xind].size()-1] << endl;
    flagi[flags_number-1]->bottomRight->setCoords(double(xind)+0.5, VELlst[xind][VELlst[xind].size()-1]);

    flagi[flags_number-1]->setLayer("flags");
    dynamic_spectrum_pl.moveLayer(flagi[flags_number-1]->layer(), colorMap->layer(), QCustomPlot::limAbove );
    dynamic_spectrum_pl.replot();
    flagged_files_on_spectrum = 1;
    string message;
    message = "Flagged " + flagged_filename + "\nRELOAD the data to make changes";
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}

// -- rotuje widmo o zadaną ilość kanałów --
void body::rotate_slot_plus()
{
    // czytamy z pola tekstowego, ile kanałów mamy przerotować
    read_number_of_rotated_channels();
    // assignujemy to do zmiennej
    int ch = number_of_rotated_channels; // liczba kanalow
    int rotated_epoch = xind; // epoka rotowania

    string rotated_filename=avrnames[rotated_epoch]; // nazwa pliku, ktorego obserwacje rotujemy

    // -- rotowanie wlasciwe --
    vector < double > tmpi;
    vector < double > tmplhc;
    vector < double > tmprhc;
    vector < double > tmpv;

    for (int i = 0; i < Ilst[rotated_epoch].size(); i++)
    {
        if (ch+i < Ilst[rotated_epoch].size())
        {
            tmpi.push_back(Ilst[rotated_epoch][ch+i]);
            tmplhc.push_back(LHClst[rotated_epoch][ch+i]);
            tmprhc.push_back(RHClst[rotated_epoch][ch+i]);
            tmpv.push_back(Vlst[rotated_epoch][ch+i]);
        }
        else
        {
            tmpi.push_back(Ilst[rotated_epoch][(ch+i)-Ilst[rotated_epoch].size()]);
            tmplhc.push_back(LHClst[rotated_epoch][(ch+i)-RHClst[rotated_epoch].size()]);
            tmprhc.push_back(RHClst[rotated_epoch][(ch+i)-LHClst[rotated_epoch].size()]);
            tmpv.push_back(Vlst[rotated_epoch][(ch+i)-Vlst[rotated_epoch].size()]);
        }
        }

    for (int i=0; i < Ilst[rotated_epoch].size(); i++)
    {
        Ilst[rotated_epoch][i] = tmpi[i];
        LHClst[rotated_epoch][i] = tmplhc[i];
        Vlst[rotated_epoch][i] = tmpv[i];
        RHClst[rotated_epoch][i] = tmprhc[i];
    }

    if(I_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(v_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Vlst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(lhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(rhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    dynamic_spectrum_pl.replot();

    // -- dodajemy do listy rotowanych --
    append_to_rotated_lst(rotated_epoch);

    // -- ustawiamy wartosc "made rotation" na 1
    made_rotation = 1;


}

// -- rotuje widmo o zadaną ilość kanałów - ale w drugą stronę --
void body::rotate_slot_minus()
{
    // czytamy z pola tekstowego, ile kanałów mamy przerotować
    read_number_of_rotated_channels();

    int rotated_epoch = xind; // epoka rotowania
    int ch = Ilst[rotated_epoch].size() - number_of_rotated_channels;
    string rotated_filename=avrnames[rotated_epoch]; // nazwa pliku, ktorego obserwacje rotujemy

    // -- rotowanie wlasciwe --
    vector < double > tmpi;
    vector < double > tmplhc;
    vector < double > tmprhc;
    vector < double > tmpv;

    for (int i = 0; i < Ilst[rotated_epoch].size(); i++)
    {
        if (ch+i < Ilst[rotated_epoch].size())
        {
            tmpi.push_back(Ilst[rotated_epoch][ch+i]);
            tmplhc.push_back(LHClst[rotated_epoch][ch+i]);
            tmprhc.push_back(RHClst[rotated_epoch][ch+i]);
            tmpv.push_back(Vlst[rotated_epoch][ch+i]);
        }
        else
        {
            tmpi.push_back(Ilst[rotated_epoch][(ch+i)-Ilst[rotated_epoch].size()]);
            tmplhc.push_back(LHClst[rotated_epoch][(ch+i)-RHClst[rotated_epoch].size()]);
            tmprhc.push_back(RHClst[rotated_epoch][(ch+i)-LHClst[rotated_epoch].size()]);
            tmpv.push_back(Vlst[rotated_epoch][(ch+i)-Vlst[rotated_epoch].size()]);
        }
        }

    for (int i=0; i < Ilst[rotated_epoch].size(); i++)
    {
        Ilst[rotated_epoch][i] = tmpi[i];
        LHClst[rotated_epoch][i] = tmplhc[i];
        Vlst[rotated_epoch][i] = tmpv[i];
        RHClst[rotated_epoch][i] = tmprhc[i];
    }

    if(I_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(v_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Vlst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(lhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(rhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    dynamic_spectrum_pl.replot();
    // -- dodajemy do listy rotowanych --
    append_to_rotated_lst(rotated_epoch);
    // -- ustalamy "made rotation" na 1
    made_rotation = 1;

}

// -- dodaje nr. epoki do listy, przechowującej epoki przerotowanych widm --
void body::append_to_rotated_lst(int marker)
{
    // -- sprawdzamy, czy jest na liście rotated --
    if (check_if_is_on_rotated_lst(marker))
    {
        return; //  jesli zwraca true, wychodzimy i nic nie robimy
    }
    else
    {
        // -- jesli zwraca false, dodajemy numer obserwacji do listy --
        rotated_spectras.push_back(marker);
    }

    /*
    for (int i = 0; i < rotated_spectras.size(); i++)
    {
        cout << rotated_spectras[i];
    }
    cout << endl;
    */

}

// -- sprawdza, czy marker podany w argumencie jest na liście rotowanych widm (pomocnicze do append_to_rotated_lst() --
bool body::check_if_is_on_rotated_lst(int marker)
{
    // -- sprawdzamy, czy jest na liście rotated --

    for (int i = 0; i < rotated_spectras.size(); i++)
    {
        // -- returntujemy true, jeśli jest na liście
        if (rotated_spectras[i] == marker)
            return true;
    }

    // -- returnujemy false jeśli nie ma --
    return false;

}

// -- zapisuje przerotowane widma --
void body::save_rotated_spectras()
{
    if (made_rotation == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("There are no rotated spectras, so nothing will be saved"));
        return;
    }

    // -- okno do upewniania sie, ze na pewno chcesz --
    QMessageBox::StandardButton upewka;
    upewka = QMessageBox::question(&window, "Are you sure?", QString::fromStdString("Do you realy want to save rotated spectras (non - rotated versions will be stored at no_rotated*AVR.DAT)?"), QMessageBox::Yes| QMessageBox::No);
    if (upewka == QMessageBox::No)
    {
        //cout << "noioo" << endl;
        return;
    }

    // -- blok tymczasowych zmiennych --
    string filename;
    int epoch;
    string headere;
    vector < double > is,v,lhc,rhc;
    string output_filename;
    string cpy_message = "";
    //cpy_message = cpy_message + "Copied to\n"
    string message = "";
    message = message + "Saved rotated spectras to:\n";

    // -- kopiowanie plikow --
    ofstream cp_destination_rot;
    ifstream copied_file;
    // -- zaczynamy petle zapisu --
    for(int i = 0; i < rotated_spectras.size(); i++)
    {
        // -- ustalamy z czym mamy do czynienia --
        epoch = rotated_spectras[i];
        filename = avrnames[epoch];
        headere = headerlst[epoch];
        output_filename = "no_rotated_" + filename; // jest to nazwa pliku, do ktorego skopiowane zostana dane sprzed rotacji

        // -- kopiujemy do backupowego file --
        cp_destination_rot.open((working_directory + "/" + output_filename).c_str(), std::ios::binary);
        copied_file.open((working_directory + "/" + filename).c_str(), std::ios::binary);
        cp_destination_rot << copied_file.rdbuf();
        cp_destination_rot.close();
        copied_file.close();

        //system(("cp " + working_directory + "/" + filename + " " + working_directory + "/" + output_filename).c_str());
        //cout << "cp " + filename + " " + output_filename << endl;

        cpy_message = cpy_message + working_directory + "/" + filename + " copied to " + working_directory + "/" + output_filename + "\n";

        // -- zapelniamy tablice --
        for (int ee = 0; ee < Ilst[epoch].size(); ee++)
        {
            is.push_back(Ilst[epoch][ee]);
            v.push_back(Vlst[epoch][ee]);
            lhc.push_back(LHClst[epoch][ee]);
            rhc.push_back(RHClst[epoch][ee]);
        }

        // -- zapisujemy do pliku --
        save_avr_file(working_directory + "/" + filename, headere, is,v,lhc,rhc);
        //cout << headere << endl;
        // -- czyscimy kontenery --
        is.clear();
        v.clear();
        lhc.clear();
        rhc.clear();

        // -- dodajemy do wiadomosci --
        message = message + working_directory + "/" + filename + "\n";

    }
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(cpy_message));
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}

// -- zapisuje plik z dostępnych danych (używany do zapisywania rotowanych widm)
void body::save_avr_file(string target_filename, string header, vector < double > is, vector < double > v, vector < double > lhc, vector < double > rhc)
{
    // -- obiekt pliku do zapisywania --
    ofstream fle;
    // -- otwieramy --
    fle.open(target_filename.c_str());
    int licznik = 0;

    // -- petla zapisujaca --
    // header
    fle << header;

    // I
    for (int i = 0; i < is.size(); i++)
    {
        if (i%8 == 0)
        {
            if(i != 0)
                fle << endl;

            fle << setw(11) << setprecision(1) << fixed << is[i]*1000.0;
        }
        else
        {
            fle << setw(10) << setprecision(1) << fixed << is[i]*1000.0;
        }
    }
    // header
    fle << endl << header;

    // V
    for (int i = 0; i < v.size(); i++)
    {
        if (i%8 == 0)
        {
            if(i != 0)
                fle << endl;

            fle << setw(11) << setprecision(1) << fixed << v[i]*1000.0;
        }
        else
        {
            fle << setw(10) << setprecision(1) << fixed << v[i]*1000.0;
        }
    }

    // header
    fle << endl << header;

    // lhc
    for (int i = 0; i < lhc.size(); i++)
    {
        if (i%8 == 0)
        {
            if(i != 0)
                fle << endl;

            fle << setw(11) << setprecision(1) << fixed << lhc[i]*1000.0;
        }
        else
        {
            fle << setw(10) << setprecision(1) << fixed << lhc[i]*1000.0;
        }
    }
    // header
    fle << endl << header;

    // rhc
    for (int i = 0; i < lhc.size(); i++)
    {
        if (i%8 == 0)
        {
            if(i != 0)
                fle << endl;

            fle << setw(11) << setprecision(1) << fixed << rhc[i]*1000.0;
        }
        else
        {
            fle << setw(10) << setprecision(1) << fixed << rhc[i]*1000.0;
        }
    }

    fle.close();
}

// -- czyta, ile o ile kanałów ma być przerotowane widmo przy wywołaniu slotu 'rotate()' --
void body::read_number_of_rotated_channels()
{
    // Qstring, do którego zgrywamy tekst z text edit
    QString number_in_string;

    // Zgrywamy text do stringa
    number_in_string = number_of_rotated_channels_texted.toPlainText();

    // -- sprawdzamy, czy text edit jest wypełniony --
    if (number_in_string == "")
    {
        // jeśli nie, nic nie robimy
        return;
    }

    // -- konwertujemy wartość z texedit na int--
    try
    {
        number_of_rotated_channels = stoi(number_in_string.toStdString());
    }
    catch(...)
    {
        return;
    }
}

void body::open_cal_layout()
{
    if (calibration_section_opened == 1)
        return;

    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    if (wd_section_opened == 1 || spind_window_opened == 1 || aver_over_time_window_opened == 1 || aver_over_velocity_window_opened == 1 || integrate_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }

    cancel.setText("Cancel");

    load_caltab_l1.setVisible(true);
    load_caltab_r1.setVisible(true);
    start_calibration.setVisible(true);
    cancel.setVisible(true);
    caltab_r1_path.setVisible(true);
    caltab_l1_path.setVisible(true);
    toggle_calibration_button.setVisible(false);

    L1.addWidget(&load_caltab_l1,Qt::AlignHCenter);
    L1.addWidget(&caltab_l1_path,Qt::AlignHCenter);

    R1.addWidget(&load_caltab_r1,Qt::AlignHCenter);
    R1.addWidget(&caltab_r1_path,Qt::AlignHCenter);

    calbtns.addWidget(&start_calibration,Qt::AlignHCenter);
    //calbtns.addWidget(&toggle_calibration_button,Qt::AlignHCenter);
    calbtns.addWidget(&cancel,Qt::AlignHCenter);

    calibrate_layout.addLayout(&L1,Qt::AlignHCenter);
    calibrate_layout.addLayout(&R1,Qt::AlignHCenter);
    calibrate_layout.addLayout(&calbtns,Qt::AlignHCenter);

    // -- setujemy default na labele --
    if (caltabs_loaded == 0)
    {
        caltab_l1_path.setText(QString::fromStdString("Not loaded!"));
        caltab_r1_path.setText(QString::fromStdString("Not loaded!"));
    }
    else
    {
        caltab_l1_path.setText(QString::fromStdString("Loaded"));
        caltab_r1_path.setText(QString::fromStdString("Loaded"));
    }

    if (calgridloaded == 0)
    {
        vbox_main.addLayout(&calibrate_layout,Qt::AlignLeft);
        calgridloaded = 1;

    }

    if (cal_toggled == 0)
    {
        toggle_calibration_button.setDown(false);
        toggle_calibration_button.setText("Toggle cal");
    }
    else
    {
        toggle_calibration_button.setDown(true);
        toggle_calibration_button.setText("Untoggle cal");
    }

    if (calibration_done == 0)
    {
        start_calibration.setText("Calibrate");
    }
    else if (calibration_done == 1)
    {
        start_calibration.setText("Uncalibrate");
        start_calibration.setDown(true);
    }

    vbox_main.update();
    grid.update();
    window.show();

    calibration_section_opened = 1;

    QPushButton::connect(&cancel, SIGNAL(clicked()), this, SLOT(close_cal_layout()));
    QPushButton::connect(&start_calibration, SIGNAL(clicked()), this, SLOT(calibrate_button()));
    //QPushButton::connect(&toggle_calibration_button, SIGNAL(clicked()), this, SLOT(toggle_calibration()));
    QPushButton::connect(&load_caltab_l1, SIGNAL(clicked()), this, SLOT(load_l1_caltab_button()));
    QPushButton::connect(&load_caltab_r1, SIGNAL(clicked()), this, SLOT(load_r1_caltab_button()));
}

void body::close_cal_layout()
{

    L1.removeWidget(&load_caltab_l1);
    L1.removeWidget(&caltab_l1_path);

    R1.removeWidget(&load_caltab_r1);
    R1.removeWidget(&caltab_r1_path);

    calbtns.removeWidget(&start_calibration);
    calbtns.removeWidget(&cancel);
    //calbtns.removeWidget(&toggle_calibration_button);

    calibrate_layout.removeItem(&L1);
    calibrate_layout.removeItem(&R1);
    calibrate_layout.removeItem(&calbtns);

    load_caltab_l1.setVisible(false);
    load_caltab_r1.setVisible(false);
    start_calibration.setVisible(false);
    cancel.setVisible(false);
    caltab_r1_path.setVisible(false);
    caltab_l1_path.setVisible(false);
    toggle_calibration_button.setVisible(false);

    vbox_main.removeItem(&calibrate_layout);

    window.show();
    grid.update();
    vbox_main.update();
    calgridloaded = 0;

    calibration_section_opened = 0;

    QPushButton::disconnect(&cancel, SIGNAL(clicked()), this, SLOT(close_cal_layout()));
    QPushButton::disconnect(&start_calibration, SIGNAL(clicked()), this, SLOT(calibrate_button()));
    QPushButton::disconnect(&load_caltab_l1, SIGNAL(clicked()), this, SLOT(load_l1_caltab_button()));
    QPushButton::disconnect(&load_caltab_r1, SIGNAL(clicked()), this, SLOT(load_r1_caltab_button()));

}

// -- kalibruje podaną w argumencie epokę obserwacji --
vector < double > body::calibrate_single(int epoch_number)
{
    // -- sprawdzamy, czy załadowane zostały caltaby --
    if (caltabs_loaded == 0)
    {
        cout << "CALTABS not loaded" << endl;
        vector < double > tmoexd;
        tmoexd.push_back(1.0);
        tmoexd.push_back(1.0);
        return tmoexd;
    }

    // -- jeśli tak, przystępujemy do kalibracji --
    double cal_coef_lhc = 1.0; // wsp. kalibracyjny
    double cal_coef_rhc = 1.0; // wsp. kalibracyjny

    // LHC
    int index_of_cal_lhc = find_epoch_in_caltab(epoch_number, "LHC");

    if (index_of_cal_lhc < 0)
    {
        int prev = find_previous_epoch(epoch_number, "LHC");
        int nextep = find_next_epoch(epoch_number, "LHC");
        if (prev >= 0 && nextep >= 0)
        {
            double epoch1 = CALTAB_L1_epochs[prev];
            double coef1 = CALTAB_L1[prev];

            double epoch2 = CALTAB_L1_epochs[nextep];
            double coef2 = CALTAB_L1[nextep];

            double our_epoch = mjdlst[epoch_number] - 50000.0;

            // -- interpolacja --
            double slope = (coef2 - coef1) / (epoch2 - epoch1);
            double days_passed = our_epoch - epoch1;
            cal_coef_lhc = coef1+ slope * days_passed;

            //cout <<"[" << mjdlst[epoch_number] << "]: "<<"Found LHC coef: interpolating between " << epoch1 << ", " << coef1 << " and " << epoch2 << ", " << coef2 << ", coef value: " << cal_coef_lhc << endl;
        }
    }
    else if (index_of_cal_lhc >=0)
    {
        cal_coef_lhc = CALTAB_L1[index_of_cal_lhc];
        //cout <<"[" << mjdlst[epoch_number] << "]: " << "Found LHC coef:  " <<  CALTAB_L1[index_of_cal_lhc] << endl;
    }

    int index_of_cal_rhc = find_epoch_in_caltab(epoch_number, "RHC");

    if (index_of_cal_rhc < 0)
    {
        int prev = find_previous_epoch(epoch_number, "RHC");
        int nextep = find_next_epoch(epoch_number, "RHC");
        if (prev >= 0 && nextep >= 0)
        {
            double epoch1 = CALTAB_R1_epochs[prev];
            double coef1 = CALTAB_R1[prev];

            double epoch2 = CALTAB_R1_epochs[nextep];
            double coef2 = CALTAB_R1[nextep];

            double our_epoch = mjdlst[epoch_number] - 50000.0;

            // -- interpolacja --
            double slope = (coef2 - coef1) / (epoch2 - epoch1);
            double days_passed = our_epoch - epoch1;
            cal_coef_rhc = coef1 + slope * days_passed;

            //cout <<"[" << mjdlst[epoch_number] << "]: " << "Found RHC coef: interpolating between " << epoch1 << ", " << coef1 << " and " << epoch2 << ", " << coef2 << ", coef value: " << cal_coef_lhc << endl;
        }
    }
    else if (index_of_cal_rhc >=0)
    {
        cal_coef_rhc = CALTAB_R1[index_of_cal_rhc];
        //cout <<"[" << mjdlst[epoch_number] << "]: " << "Found RHC coef:  " <<  CALTAB_R1[index_of_cal_lhc] << endl;
    }

    vector < double > returning_values;
    returning_values.push_back(cal_coef_lhc);
    returning_values.push_back(cal_coef_rhc);
    return returning_values;
}

void body::toggle_calibration()
{
    if (calibration_done == 0)
    {
        QMessageBox::information(&window, tr("Error"), tr("Calibration is not done yet!"));
        return;
    }
    if (cal_toggled == 0)
    {
        //QMessageBox::information(&window, tr("TMP message"), tr("Cal toggled"));
        toggle_calibration_button.setDown(true);
        cal_toggled = 1;
        toggle_calibration_button.setText("Untoggle cal");
    }
    else if (cal_toggled == 1)
    {
        //QMessageBox::information(&window, tr("TMP message"), tr("Cal distoggled"));
        toggle_calibration_button.setDown(false);
        cal_toggled = 0;
        toggle_calibration_button.setText("Toggle cal");
    }
    return;
}

// -- laduje caltab l1 -- (LHC)
void body::load_l1_caltab(string filename)
{

    lhc_loaded = 0;
    ifstream tab; // plik z naszym caltabem

    // otwieramy plik o znalezionej nazwie
    tab.open(filename.c_str());

    // sprawdzamy, czy udało się otworzyć
    if (tab.good() != true)
    {
        //QMessageBox::information(&window, tr("Error"), tr("No such file or directory"));
        return;
    }

    // jeśli tak, clearujemy caltaby
    CALTAB_L1_epochs.clear();
    CALTAB_L1.clear();

    // tymczasowe zmienne do czytania
    int tmpepoch;
    double tmpcoef;
    string bufor;
    char check_if_hash;
    // główna pętla wczytująca caltab
    while(tab.good())
    {

        tab.get(check_if_hash);
        if (check_if_hash == '#')
        {
            getline(tab, bufor);
        }
        else
        {
            tab.seekg(-1,ios::cur);
            tab >> tmpepoch >> tmpcoef;
            CALTAB_L1_epochs.push_back(tmpepoch);
            CALTAB_L1.push_back(tmpcoef);
        }
    }

    tab.close();

    /*
    for(int i = 0; i < CALTAB_L1.size(); i++)
    {
        cout << CALTAB_L1_epochs[i] << "   " << CALTAB_L1[i] << endl;
    }
    */

    lhc_loaded = 1;
    caltab_l1_path.setText(QString::fromStdString("Loaded"));
    if (rhc_loaded == 1)
        caltabs_loaded = 1;
    else
        caltabs_loaded = 0;
    return;
}

// -- laduje caltab r1 -- (RHC)
void body::load_r1_caltab(string filename)
{

    rhc_loaded = 0;
    ifstream tab; // plik z naszym caltabem

    // otwieramy plik o znalezionej nazwie
    tab.open(filename.c_str());

    // sprawdzamy, czy udało się otworzyć
    if (tab.good() != true)
    {
        //QMessageBox::information(&window, tr("Error"), tr("No such file or directory"));
        return;
    }

    // jeśli tak, clearujemy caltaby
    CALTAB_R1_epochs.clear();
    CALTAB_R1.clear();

    // tymczasowe zmienne do czytania
    int tmpepoch;
    double tmpcoef;
    string bufor;
    char check_if_hash;
    // główna pętla wczytująca caltab
    while(tab.good())
    {

        tab.get(check_if_hash);
        if (check_if_hash == '#')
        {
            getline(tab, bufor);
        }
        else
        {
            tab.seekg(-1,ios::cur);
            tab >> tmpepoch >> tmpcoef;
            CALTAB_R1_epochs.push_back(tmpepoch);
            CALTAB_R1.push_back(tmpcoef);
        }
    }

    tab.close();

    /*
    for(int i = 0; i < CALTAB_R1.size(); i++)
    {
        cout << CALTAB_R1_epochs[i] << "   " << CALTAB_R1[i] << endl;
    }
    */
    rhc_loaded = 1;
    caltab_r1_path.setText(QString::fromStdString("Loaded"));
    if (lhc_loaded == 1)
        caltabs_loaded = 1;
    else
        caltabs_loaded = 0;
    return;
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
    load_l1_caltab(nazwa_pliku);
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
    load_r1_caltab(nazwa_pliku);
}

void body::calibrate_button()
{
    calibrate_method();
}

void body::calibrate_method()
{

    if (caltabs_loaded == 0)
    {
        QMessageBox::information(&window, tr("Error"), tr("Caltabs not loaded!"));
        return;
    }
    calcoefs_lhc.clear();
    calcoefs_rhc.clear();
    vector < double > tmp_calibrate;
    for(int i = 0; i < mjdlst.size(); i++)
    {
       tmp_calibrate = calibrate_single(i);
       calcoefs_lhc.push_back(tmp_calibrate[0]);
       calcoefs_rhc.push_back(tmp_calibrate[1]);
    }

    if (calibration_done == 0)
    {
        for(int i = 0; i < LHClst.size(); i++)
        {
            for (int k=0; k< LHClst[i].size(); k++)
            {
                LHClst[i][k] = calcoefs_lhc[i] * LHClst[i][k];
                LHCERRlst[i][k] = calcoefs_lhc[i] * LHCERRlst[i][k];
            }
        }

        for(int i = 0; i < RHClst.size(); i++)
        {
            for (int k=0; k< RHClst[i].size(); k++)
            {
                RHClst[i][k] = calcoefs_rhc[i] * RHClst[i][k];
                RHCERRlst[i][k] = calcoefs_rhc[i] * RHCERRlst[i][k];
            }
        }

        for(int i = 0; i < Ilst.size(); i++)
        {
            for (int k=0; k< Ilst[i].size(); k++)
            {
                Ilst[i][k] = (RHClst[i][k] + LHClst[i][k]) / 2.0;
                ERRlst[i][k] = (RHCERRlst[i][k] + LHCERRlst[i][k]) / 2.0;
            }
        }

        for(int i = 0; i < Vlst.size(); i++)
        {
            for (int k=0; k< Vlst[i].size(); k++)
            {
                Vlst[i][k] = (RHClst[i][k] - LHClst[i][k]) / 2.0;
                VERRlst[i][k] = (RHCERRlst[i][k] - LHCERRlst[i][k]) / 2.0;
            }
        }
        //QMessageBox::information(&window, tr("Message"), tr("Calibration done"));
        if (dynamic_spectrum_opened == 1)
        {
            update_dynamic_spectrum();
        }
        else if (rms_section_opened == 1)
        {
            set_plot_on_rms_vs_time();
            set_plot_on_int_vs_time();
            //set_plot_on_tsys_vs_time();
        }
        //calibrate_single(23);
        calibration_done = 1;
        start_calibration.setDown(true);
        start_calibration.setText("Uncalibrate");
    }
    else if (calibration_done == 1)
    {
        for(int i = 0; i < LHClst.size(); i++)
        {
            for (int k=0; k< LHClst[i].size(); k++)
            {
                LHClst[i][k] =  LHClst[i][k] / calcoefs_lhc[i];
                LHCERRlst[i][k] = LHCERRlst[i][k] / calcoefs_lhc[i];
            }
        }

        for(int i = 0; i < RHClst.size(); i++)
        {
            for (int k=0; k< RHClst[i].size(); k++)
            {
                RHClst[i][k] = RHClst[i][k] / calcoefs_rhc[i];
                RHCERRlst[i][k] = RHCERRlst[i][k] / calcoefs_rhc[i];
            }
        }

        for(int i = 0; i < RHClst.size(); i++)
        {
            for (int k=0; k< RHClst[i].size(); k++)
            {
                Ilst[i][k] = (RHClst[i][k] + LHClst[i][k]) / 2.0;
                ERRlst[i][k] = (RHCERRlst[i][k] + LHCERRlst[i][k]) / 2.0;
            }
        }

        for(int i = 0; i < Vlst.size(); i++)
        {
            for (int k=0; k< Vlst[i].size(); k++)
            {
                Vlst[i][k] = (RHClst[i][k] - LHClst[i][k]) / 2.0;
                VERRlst[i][k] = (RHCERRlst[i][k] - LHCERRlst[i][k]) / 2.0;
            }
        }

        //QMessageBox::information(&window, tr("Message"), tr("Calibration undone"));
        if (dynamic_spectrum_opened == 1)
        {
            update_dynamic_spectrum();
        }
        else if (rms_section_opened == 1)
        {
            set_plot_on_rms_vs_time();
            set_plot_on_int_vs_time();
            //set_plot_on_tsys_vs_time();
        }
        //calibrate_single(23);
        calibration_done = 0;
        start_calibration.setDown(false);
        start_calibration.setText("Calibrate");
    }
}

int body::find_epoch_in_caltab(int index_of_epoch, string type_of_caltab)
{
    // zwraca ujemne wartości jak nie znajdzie w tablicy
    if (type_of_caltab != "LHC" && type_of_caltab != "RHC")
    {
        return -1;
    }

    // zapisujemy jaką rozpatrujemy epoke
    int epoch = int(mjdlst[index_of_epoch] - 50000.0);

    bool found = 0;
    int index = -1;

    //petla szukajaca
    if (type_of_caltab == "LHC")
    {
        // -- dwa przypadki skrajne --
        if (epoch < CALTAB_L1_epochs[0])
        {
            return 0;
        }
        else if (epoch > CALTAB_L1_epochs[CALTAB_L1_epochs.size()-1])
        {
            return CALTAB_L1_epochs.size()-1;
        }

        for (int i = 0; i < CALTAB_L1_epochs.size(); i++)
        {
            if (CALTAB_L1_epochs[i] == epoch)
            {
                found = 1;
                index = i;
                break;
            }
        }
    }
    else if (type_of_caltab == "RHC")
    {
        // -- dwa przypadki skrajne --
        if (epoch < CALTAB_R1_epochs[0])
        {
            return 0;
        }
        else if (epoch > CALTAB_R1_epochs[CALTAB_R1_epochs.size()-1])
        {
            return CALTAB_R1_epochs.size()-1;
        }

        for (int i = 0; i < CALTAB_R1_epochs.size(); i++)
        {
            if (CALTAB_R1_epochs[i] == epoch)
            {
                found = 1;
                index = i;
                break;
            }
        }
    }

    // -- zwracamy odpowiednia wartosc --
    if (found == 1)
        return index;
    else
        return -1;
}

int body::find_previous_epoch(int index_of_epoch, string type_of_caltab)
{
    // zwraca ujemne wartości jak nie znajdzie w tablicy
    if (type_of_caltab == "LHC" && type_of_caltab == "RHC")
    {
        cout << "koncze bo zly typ xD" << endl;
        return -1;
    }

    // zapisujemy jaką rozpatrujemy epoke
    int epoch = int(mjdlst[index_of_epoch] - 50000.0);

    bool found = 0;
    int index = -1;

    //petla szukajaca
    if (type_of_caltab == "LHC")
    {
        // -- dwa przypadki skrajne --
        if (epoch < CALTAB_L1_epochs[0])
        {
            return 0;
        }
        else if (epoch > CALTAB_L1_epochs[CALTAB_L1_epochs.size()-1])
        {
            return CALTAB_L1_epochs.size()-1;
        }


        for (int i = 0; i < CALTAB_L1_epochs.size(); i++)
        {
            if (CALTAB_L1_epochs[i] > epoch)
            {
                found = 1;
                index = i-1;
                break;
            }
        }
    }
    else if (type_of_caltab == "RHC")
    {

        // -- dwa przypadki skrajne --
        if (epoch < CALTAB_R1_epochs[0])
        {
            return 0;
        }
        else if (epoch > CALTAB_R1_epochs[CALTAB_R1_epochs.size()-1])
        {
            return CALTAB_R1_epochs.size()-1;
        }

        for (int i = 0; i < CALTAB_R1_epochs.size(); i++)
        {
            if (CALTAB_R1_epochs[i] > epoch)
            {
                found = 1;
                index = i-1;
                break;
            }
        }
    }

    // -- zwracamy odpowiednia wartosc --
    if (found == 1)
        return index;
    else
        return -1;
}

int body::find_next_epoch(int index_of_epoch, string type_of_caltab)
{
    // zwraca ujemne wartości jak nie znajdzie w tablicy
    if (type_of_caltab != "LHC" && type_of_caltab != "RHC")
    {
        return -1;
    }

    // zapisujemy jaką rozpatrujemy epoke
    int epoch = int(mjdlst[index_of_epoch] - 50000.0);

    bool found = 0;
    int index = -1;

    //petla szukajaca
    if (type_of_caltab == "LHC")
    {
        // -- dwa przypadki skrajne --
        if (epoch < CALTAB_L1_epochs[0])
        {
            return 0;
        }
        else if (epoch > CALTAB_L1_epochs[CALTAB_L1_epochs.size()-1])
        {
            return CALTAB_L1_epochs.size()-1;
        }


        for (int i = 0; i < CALTAB_L1_epochs.size(); i++)
        {
            if (CALTAB_L1_epochs[i] > epoch)
            {
                found = 1;
                index = i;
                break;
            }
        }
    }
    else if (type_of_caltab == "RHC")
    {

        // -- dwa przypadki skrajne --
        if (epoch < CALTAB_R1_epochs[0])
        {
            return 0;
        }
        else if (epoch > CALTAB_R1_epochs[CALTAB_R1_epochs.size()-1])
        {
            return CALTAB_R1_epochs.size()-1;
        }

        for (int i = 0; i < CALTAB_R1_epochs.size(); i++)
        {
            if (CALTAB_R1_epochs[i] > epoch)
            {
                found = 1;
                index = i;
                break;
            }
        }
    }

    // -- zwracamy odpowiednia wartosc --
    if (found == 1)
        return index;
    else
        return -1;
}

void body::update_dynamic_spectrum()
{


    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(VELlst[0][min_range_vel_index], VELlst[0][max_range_vel_index]-(VELlst[0][2]-VELlst[0][1])));
    if(I_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(v_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, Vlst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(lhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, LHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }
    else if(rhc_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (Ilst[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, RHClst[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }

    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    colorMap -> rescaleDataRange(true);
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();
    /*
    double veldif = VELlst[xind][max_range_vel_index] - VELlst[xind][min_range_vel_index];
    single_dynamic_spectrum.xAxis->setRange(VELlst[xind][min_range_vel_index] - 0.05 * veldif, VELlst[xind][max_range_vel_index] + 0.05 * veldif);
    single_dynamic_spectrum.replot();

    lcs_dynamic_spectrum.xAxis->setRange(mjdlst[min_obs_number], mjdlst[max_obs_number]);
    lcs_dynamic_spectrum.replot();
    window.show();
    set_down_IVLHCRHCbuttons();
    */
    // -- twotzymy widmo, ktore wyswietli sie po kliknieciu w widmo dynamiczne --
    // - warunki ze wzgledu na przyciski polaryzacji -
    QVector < double > velocity(rozmiar_w_y), flux(rozmiar_w_y);

    if (I_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = Ilst[xind][min_range_vel_index+i];
    }
    }

    else if (v_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = Vlst[xind][min_range_vel_index+i];
    }
    }
    else if (lhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = LHClst[xind][min_range_vel_index+i];
    }
    }
    else if (rhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = VELlst[xind][min_range_vel_index+i];
        flux[i] = RHClst[xind][min_range_vel_index+i];
    }
    }

    single_dynamic_spectrum.replot();
    single_dynamic_spectrum.graph(0)->setData(velocity,flux);
    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double veldiff = *max_element(velocity.begin(), velocity.end()) - *min_element(velocity.begin(), velocity.end());
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));
    // -- pokazujemy ticki na gornej osi --
    single_dynamic_spectrum.xAxis2->setVisible(true);
    single_dynamic_spectrum.yAxis2->setVisible(true);
    single_dynamic_spectrum.xAxis2->setTickLabels(false);
    single_dynamic_spectrum.yAxis2->setTickLabels(false);
    single_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    if (vel_line_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        vel_line_added = 1;
    }
    QVector < double > x_vline(2), y_vline(2);
    x_vline[0] = VELlst[0][yind];
    x_vline[1] = VELlst[0][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end()));
    y_vline[1] = *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end()));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);
    single_dynamic_spectrum.replot();
    // -- tworzymy krzywa blasku, ktora wyswietli sie w krzywej blasku --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    if(I_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = Ilst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(v_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = Vlst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(lhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = LHClst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }

    else if(rhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = mjdlst[min_obs_number + i];
        lcs_flux[i] = RHClst[min_obs_number + i][yind];
        error_lcs[i] = ERRlst[min_obs_number + i][yind];
    }
    }
    //cout << epoch[0] << endl;

    errorBars->setAntialiased(false);
    errorBars->setDataPlottable(lcs_dynamic_spectrum.graph(0));
    errorBars->setPen(QPen(QColor(180,180,180)));

    lcs_dynamic_spectrum.graph(0)->setData(epoch,lcs_flux);
    errorBars->setData(error_lcs);

    lcs_dynamic_spectrum.graph(0)->setPen(QPen(Qt::blue));
    lcs_dynamic_spectrum.graph(0)->setLineStyle(QCPGraph::lsNone);
    lcs_dynamic_spectrum.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    lcs_dynamic_spectrum.xAxis->setLabel("MJD");
    lcs_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double diffrence = *max_element(epoch.begin(), epoch.end()) - *min_element(epoch.begin(), epoch.end());
    lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
    lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    lcs_dynamic_spectrum.replot();


    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }
    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = mjdlst[xind];
    lcsx_vline[1] = mjdlst[xind];
    lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);
    lcs_dynamic_spectrum.replot();


    // -- setujemy tekst do displayowania informacji --
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(to_string(int(mjdlst[xind])));


    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(to_string(CHANlst[xind][yind]));

    text_mjdlabel.append(string("\nVel: "));

    // Create an output string stream
    std::ostringstream streamObjvel;

    // Set Fixed -Point Notation
    streamObjvel << std::fixed;

    streamObjvel << std::setprecision(3);

    streamObjvel << VELlst[xind][yind];
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);

    mjd_label.setText(QString::fromStdString(text_mjdlabel));
    QFont f( "Arial", 11, QFont::Bold);
    mjd_label.setFont(f);
    string cocochanel_txt = "";


    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(to_string(int(ylst[xind])));
    cocochanel_txt.append(string(" "));


    if (int(mlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(mlst[xind])));
    else
        cocochanel_txt.append(to_string(int(mlst[xind])));

    cocochanel_txt.append(string(" "));

    if (int(dlst[xind]) < 10)
        cocochanel_txt.append("0" + to_string(int(dlst[xind])));
    else
        cocochanel_txt.append(to_string(int(dlst[xind])));

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << Ilst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << Vlst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << LHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << RHClst[xind][yind];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(to_string(xind+1));

    cocochanel.setFont(f);
    cocochanel.setText(QString::fromStdString(cocochanel_txt));
    set_down_IVLHCRHCbuttons();
}

bool body::read_calconfig()
{
    ifstream calfle;
    calfle.open((working_directory + "/" + "calconfig.sv").c_str());

    string bufor;
    char spr;

    if (calfle.good())
    {
            calfle.get(spr);
            if (spr != '#')
            {
                calfle.seekg(-1, ios::cur);
                calfle >> caltab_LHC_path;
                calfle >> caltab_RHC_path;
                calfle.close();
                return 1;
            }
            else
            {
                getline(calfle, bufor);
                //cout << bufor << endl;
                calfle >> caltab_LHC_path;
                calfle >> caltab_RHC_path;
                calfle.close();
                return 1;
            }
     }
    return 0;

}

void body::open_dynspectum_layout()
{
    if (wd_section_opened == 1)
        return;


    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    if (wd_section_opened == 1)
    {
        return;
    }

    if (spind_window_opened == 1 || aver_over_time_window_opened == 1 || aver_over_velocity_window_opened == 1 || integrate_window_opened == 1 || calibration_section_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }

    start_chanwd.setMaximumSize(100,30);
    end_chanwd.setMaximumSize(100,30);

    start_chanwd.setMinimumSize(0,0);
    end_chanwd.setMinimumSize(0,0);

    cancel.setText("Cancel");
    WD_start.setText("Export dyn. spec.");

    start_channelwd.setText("Start channel");
    end_channelwd.setText("End channel");

    WD_start.setVisible(true);
    start_chanwd.setVisible(true);
    end_chanwd.setVisible(true);
    cancel.setVisible(true);
    start_channelwd.setVisible(true);
    end_channelwd.setVisible(true);

    start_channelwd_label.addWidget(&start_chanwd,Qt::AlignHCenter);
    start_channelwd_label.addWidget(&start_channelwd,Qt::AlignHCenter);

    end_channelwd_label.addWidget(&end_chanwd,Qt::AlignHCenter);
    end_channelwd_label.addWidget(&end_channelwd,Qt::AlignHCenter);


    btns.addWidget(&WD_start,Qt::AlignHCenter);
    btns.addWidget(&cancel,Qt::AlignHCenter);

    wd_layout.addLayout(&start_channelwd_label);
    wd_layout.addLayout(&end_channelwd_label);
    wd_layout.addLayout(&btns,Qt::AlignHCenter);

    vbox_main.addLayout(&wd_layout);
    vbox_main.update();
    grid.update();
    window.show();

    wd_section_opened = 1;

    QPushButton::connect(&cancel, SIGNAL(clicked()), this, SLOT(close_dynspectrum_layout()));
    QPushButton::connect(&WD_start, SIGNAL(clicked()), this, SLOT(export_file_for_dynamic_spectrum()));

    if(dynamic_spectrum_opened== 1)
    {
        start_chanwd.setText(QString::fromStdString(to_string(min_range_vel_index+1)));
        end_chanwd.setText((QString::fromStdString(to_string(max_range_vel_index+1))));
    }
}

void body::close_dynspectrum_layout()
{
    WD_start.setVisible(false);
    start_chanwd.setVisible(false);
    end_chanwd.setVisible(false);
    cancel.setVisible(false);
    start_channelwd.setVisible(false);
    end_channelwd.setVisible(false);

    wd_layout.removeItem(&start_channelwd_label);
    wd_layout.removeItem(&end_channelwd_label);
    wd_layout.removeItem(&btns);

    btns.removeWidget(&WD_start);
    btns.removeWidget(&cancel);

    start_channelwd_label.removeWidget(&start_chanwd);
    start_channelwd_label.removeWidget(&start_channelwd);

    end_channelwd_label.removeWidget(&end_chanwd);
    end_channelwd_label.removeWidget(&end_channelwd);

    vbox_main.removeItem(&wd_layout);

    window.show();
    grid.update();
    vbox_main.update();

    //calgridloaded = 0;

    wd_section_opened = 0;

    QPushButton::disconnect(&cancel, SIGNAL(clicked()), this, SLOT(close_dynspectrum_layout()));
    QPushButton::disconnect(&WD_start, SIGNAL(clicked()), this, SLOT(export_file_for_dynamic_spectrum()));
}

void body::export_file_for_dynamic_spectrum()
{
    int min, max;
    QString mins,maxs;

    // -- czytamy wartości z pól tekstowych --
    mins = start_chanwd.toPlainText();
    maxs = end_chanwd.toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString())-1;
        max = stoi(maxs.toStdString())-1;
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return;
    }

    // -- kilka szczególnych przypadków złej obsługi metody --
    // początkowy channel większy od końcowego channel
    if (min > max)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel > max channel!"));
        return;
    }

    // początkowy channel mniejszy od 0
    if (min < 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel < 1!"));
        return;
    }

    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > Ilst[0].size()-1)
        max = Ilst[0].size()-1;

    // -- otwieramy plik do zapisu --
    // nazwa pliku
    string filename = working_directory + "/" + srcname + "_dynamic_spectrum_" + to_string(min+1) + "_to_" + to_string(max+1) + ".DAT";
    // obiekt pliku
    ofstream fle_for_wd;
    // otwieramy
    fle_for_wd.open(filename.c_str());

    if(include_pytime->isChecked())
    {
        // zapisujemy do pliku
        fle_for_wd << "# " << filename << endl;
        fle_for_wd << "# i time_in_isoformat MJD year channel velocity I e V e LHC e RHC e" << endl;

        // podwójna pętla zapisu
        for(int i = 0; i < Ilst.size(); i++) // po epokach
        {
            for (int e = min; e <= max;e++)
            {
                fle_for_wd << fixed << setprecision(11) << i+1 << " " << pytime_format[i] << " " << mjdlst[i] << " " << yrlst[i] << " " << CHANlst[i][e] << " " << VELlst[i][e] << " " << Ilst[i][e] << " " << ERRlst[i][e] << " " << Vlst[i][e] << " " << VERRlst[i][e] << " " << LHClst[i][e] << " " << LHCERRlst[i][e] << " " << RHClst[i][e] << " " << RHCERRlst[i][e] << "\n";
            }
            fle_for_wd << "\n";
        }
    }
    else
    {
        // zapisujemy do pliku
        fle_for_wd << "# " << filename << endl;
        fle_for_wd << "# i MJD year channel velocity I e V e LHC e RHC e" << endl;

        // podwójna pętla zapisu
        for(int i = 0; i < Ilst.size(); i++) // po epokach
        {
            for (int e = min; e <= max;e++)
            {
                fle_for_wd << fixed << setprecision(11) << i+1 << " " << mjdlst[i] << " " << yrlst[i] << " " << CHANlst[i][e] << " " << VELlst[i][e] << " " << Ilst[i][e] << " " << ERRlst[i][e] << " " << Vlst[i][e] << " " << VERRlst[i][e] << " " << LHClst[i][e] << " " << LHCERRlst[i][e] << " " << RHClst[i][e] << " " << RHCERRlst[i][e] << "\n";
            }
            fle_for_wd << "\n";
        }
    }

    // zamykamy plik
    fle_for_wd.close();
    // wiadomość końcowa
    string message = "";
    message = "Dynamic spectrum over channels " + to_string(min+1) + " -> " + to_string(max+1) + "\n" + "Saved to " + filename;
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

    // -- zamykamy sekcje dynspec --
    close_dynspectrum_layout();
}

void body::open_rms_section_slot()
{
    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    if (dynamic_spectrum_opened == 1)
    {
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        QMessageBox::information(&window, tr("Error!"), tr("Please, close the DYNAMIC SPECTRUM window"));
        return;
    }
    else if (single_spectrum_opened == 1)
    {
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        QMessageBox::information(&window, tr("Error!"), tr("Please, close the SINGLE SPECTRUM window"));
        return;
    }
    else if (rms_section_opened == 1)
    {
        set_plot_on_rms_vs_time();
        set_plot_on_int_vs_time();
        set_plot_on_tsys_vs_time();
        show_points_or_lines();
        return;
    }
    // dodajemy do grida
    grid.addWidget(&rms_vs_time, 0,1,5,2);
    grid.addWidget(&tsys_vs_time, 5,1,4,2);
    grid.addWidget(&int_vs_time, 0,3,5,2);
    grid.addLayout(&preferences_on_rms, 5,3,4,1);
    grid.addLayout(&exporting_on_rms, 5,4,4,1);

    // labele
    stokes_parameters.setText("Stokes parameters");
    integration_parameters_label.setText("Integration parameters");
    exporting_rms_section_label.setText("Exporting");
    export_rms_vs_tme.setText("Export rms vs time");
    export_tsys_vs_tme.setText("Export Tsys vs time");
    export_tint_vs_tme.setText("Export Integrated flux vs time");
    export_all_vs_tme.setText("Export all of the above");
    graph_params_label.setText("Plot properties");
    // fonty w labelach
    QFont f( "Arial", 10, QFont::Bold);
    stokes_parameters.setFont(f);
    integration_parameters_label.setFont(f);
    exporting_rms_section_label.setFont(f);
    graph_params_label.setFont(f);

    // checkboxy
    //I_on_rms->setVisible(true);
    //V_on_rms->setVisible(true);
    //LHC_on_rms->setVisible(true);
    //RHC_on_rms->setVisible(true);
    checkboxes_of_pol.addWidget(I_on_rms);
    checkboxes_of_pol.addWidget(V_on_rms);
    checkboxes_of_pol.addWidget(LHC_on_rms);
    checkboxes_of_pol.addWidget(RHC_on_rms);
    preferences_on_rms.addWidget(&stokes_parameters);
    preferences_on_rms.addLayout(&checkboxes_of_pol);

    // kanały
    //rms_int_start_label.setVisible(true);
    //rms_int_end_label.setVisible(true);
    //rms_int_start.setVisible(true);
    //rms_int_end.setVisible(true);
    //recalculate_integration.setVisible(true);
    rms_int_start_label.setText("Integration start channel");
    rms_int_end_label.setText("Integration end channel");
    rms_int_start.setText("500");
    rms_int_end.setText("1500");
    rms_int_start.setMaximumSize(100, 40);
    rms_int_end.setMaximumSize(100, 40);
    recalculate_integration.setText("Recalculate integration");
    start_chan.addWidget(&rms_int_start_label);
    start_chan.addWidget(&rms_int_start,Qt::AlignHCenter);
    end_chan.addWidget(&rms_int_end_label);
    end_chan.addWidget(&rms_int_end, Qt::AlignHCenter);
    preferences_on_rms.addWidget(&integration_parameters_label);
    preferences_on_rms.addLayout(&start_chan);
    preferences_on_rms.addLayout(&end_chan);
    preferences_on_rms.addWidget(&recalculate_integration);

    // przyciski do eksportowania
    export_rms_vs_tme.setMaximumSize(10000,10000);
    export_tsys_vs_tme.setMaximumSize(10000,10000);
    export_tint_vs_tme.setMaximumSize(10000,10000);
    export_all_vs_tme.setMaximumSize(10000,10000);
    exporting_on_rms.addWidget(&exporting_rms_section_label);
    exporting_on_rms.addWidget(&export_rms_vs_tme);
    exporting_on_rms.addWidget(&export_tsys_vs_tme);
    exporting_on_rms.addWidget(&export_tint_vs_tme);
    exporting_on_rms.addWidget(&export_all_vs_tme);
    // dodatkowo - manipulowanie grafiką
    exporting_on_rms.addWidget(&graph_params_label);
    exporting_on_rms.addWidget(show_pts);
    exporting_on_rms.addWidget(show_lns);

    // ustalamy szerokość kolumn
    grid.setColumnStretch(1,1);
    grid.setColumnStretch(2,1);
    grid.setColumnStretch(3,1);
    grid.setColumnStretch(4,1);

    // dodajemy amykający button do głównego panelu
    kill_rms_section.setText("Kill Tsys, Sint and RMS section --->");
    vbox_main.addWidget(&kill_rms_section);

    // pojawia się i znika
    // -- graphy -
    rms_vs_time.setVisible(true);
    tsys_vs_time.setVisible(true);
    int_vs_time.setVisible(true);
    // -- checkboxy --
    I_on_rms->setVisible(true);
    V_on_rms->setVisible(true);
    LHC_on_rms->setVisible(true);
    RHC_on_rms->setVisible(true);
    show_pts->setVisible(true);
    show_lns->setVisible(true);
    // -- labele --
    stokes_parameters.setVisible(true);
    integration_parameters_label.setVisible(true);
    exporting_rms_section_label.setVisible(true);
    rms_int_start_label.setVisible(true);
    rms_int_end_label.setVisible(true);
    graph_params_label.setVisible(true);
    // -- txt ctrle --
    rms_int_start.setVisible(true);
    rms_int_end.setVisible(true);
    // -- buttony --
    recalculate_integration.setVisible(true);
    export_rms_vs_tme.setVisible(true);
    export_tsys_vs_tme.setVisible(true);
    export_tint_vs_tme.setVisible(true);
    export_all_vs_tme.setVisible(true);
    kill_rms_section.setVisible(true);

    // - zaznaczamy checkbox I -
    I_on_rms->setChecked(true);
    show_pts->setChecked(true);
    // connectujemy
    QPushButton::connect(&kill_rms_section, SIGNAL(clicked()), this, SLOT(close_rms_section_slot()));

    QObject::connect(I_on_rms, SIGNAL(clicked()), this, SLOT(I_on_rms_checkbox_checked_slot()));
    QObject::connect(V_on_rms, SIGNAL(clicked()), this, SLOT(V_on_rms_checkbox_checked_slot()));
    QObject::connect(LHC_on_rms, SIGNAL(clicked()), this, SLOT(LHC_on_rms_checkbox_checked_slot()));
    QObject::connect(RHC_on_rms, SIGNAL(clicked()), this, SLOT(RHC_on_rms_checkbox_checked_slot()));
    QObject::connect(show_pts, SIGNAL(clicked()), this, SLOT(show_points_or_lines()));
    QObject::connect(show_lns, SIGNAL(clicked()), this, SLOT(show_points_or_lines()));
    QPushButton::connect(&export_rms_vs_tme, SIGNAL(clicked()), this, SLOT(exp_rms_vs_time()));
    QPushButton::connect(&export_tint_vs_tme, SIGNAL(clicked()), this, SLOT(exp_sint_vs_time()));
    QPushButton::connect(&recalculate_integration, SIGNAL(clicked()), this, SLOT(recalculate_integration_on_rms_slot()));
    QPushButton::connect(&export_all_vs_tme, SIGNAL(clicked()), this, SLOT(exp_all()));
    QPushButton::connect(&export_tsys_vs_tme, SIGNAL(clicked()), this, SLOT(exp_tsys_vs_time()));
    window.setGeometry(window.x(), window.y(),1360,720);
    window.show();
    grid.update();

    set_plot_on_rms_vs_time();
    set_plot_on_int_vs_time();
    set_plot_on_tsys_vs_time();
    show_points_or_lines();
    //preferences_on_rms.update();

    rms_section_opened = 1;
}

void body::close_rms_section_slot()
{
    // ustalamy visibilities
    // -- graphy -
    rms_vs_time.setVisible(false);
    tsys_vs_time.setVisible(false);
    int_vs_time.setVisible(false);
    // -- checkboxy --
    I_on_rms->setVisible(false);
    V_on_rms->setVisible(false);
    LHC_on_rms->setVisible(false);
    RHC_on_rms->setVisible(false);
    show_pts->setVisible(false);
    show_lns->setVisible(false);
    // -- labele --
    stokes_parameters.setVisible(false);
    integration_parameters_label.setVisible(false);
    exporting_rms_section_label.setVisible(false);
    rms_int_start_label.setVisible(false);
    rms_int_end_label.setVisible(false);
    graph_params_label.setVisible(false);
    // -- txt ctrle --
    rms_int_start.setVisible(false);
    rms_int_end.setVisible(false);
    // -- buttony --
    recalculate_integration.setVisible(false);
    export_rms_vs_tme.setVisible(false);
    export_tsys_vs_tme.setVisible(false);
    export_tint_vs_tme.setVisible(false);
    export_all_vs_tme.setVisible(false);
    kill_rms_section.setVisible(false);

    // odpinamy od grida
    // - gtaphy -
    grid.removeWidget(&rms_vs_time);
    grid.removeWidget(&tsys_vs_time);
    grid.removeWidget(&int_vs_time);
    // - layouty -
    grid.removeItem(&preferences_on_rms);
    grid.removeItem(&exporting_on_rms);

    // odpinamy od layoutow
    // -- preferences_on_rms --
    start_chan.removeWidget(&rms_int_start_label);
    start_chan.removeWidget(&rms_int_start);
    end_chan.removeWidget(&rms_int_end_label);
    end_chan.removeWidget(&rms_int_end);
    checkboxes_of_pol.removeWidget(I_on_rms);
    checkboxes_of_pol.removeWidget(V_on_rms);
    checkboxes_of_pol.removeWidget(LHC_on_rms);
    checkboxes_of_pol.removeWidget(RHC_on_rms);
    preferences_on_rms.removeWidget(&stokes_parameters);
    preferences_on_rms.removeItem(&checkboxes_of_pol);
    preferences_on_rms.removeWidget(&integration_parameters_label);
    preferences_on_rms.removeItem(&start_chan);
    preferences_on_rms.removeItem(&end_chan);
    preferences_on_rms.removeWidget(&recalculate_integration);
    // -- exporting_on_rms --
    exporting_on_rms.removeWidget(&exporting_rms_section_label);
    exporting_on_rms.removeWidget(&export_rms_vs_tme);
    exporting_on_rms.removeWidget(&export_tsys_vs_tme);
    exporting_on_rms.removeWidget(&export_tint_vs_tme);
    exporting_on_rms.removeWidget(&export_all_vs_tme);
    exporting_on_rms.removeWidget(&graph_params_label);
    exporting_on_rms.removeWidget(show_pts);
    exporting_on_rms.removeWidget(show_lns);

    // -- usuwamy przycisk z vbox_main --
    vbox_main.removeWidget(&kill_rms_section);
    // ustalamy wygląd okna
    window.setGeometry(window.x(), window.y(),300,720);
    grid.setColumnStretch(0,1);
    grid.setColumnStretch(1,0);
    grid.setColumnStretch(2,0);
    grid.setColumnStretch(3,0);
    grid.setColumnStretch(4,0);
    grid.setColumnStretch(5,0);
    // robimy replot okna
    grid.update();
    window.setLayout(&grid);
    window.show();
    window.setGeometry(window.x(), window.y(),300,720);
    // disconnectujemy metodę zamykania sekcji
    QPushButton::disconnect(&kill_rms_section, SIGNAL(clicked()), this, SLOT(close_rms_section_slot()));
    QObject::disconnect(I_on_rms, SIGNAL(clicked()), this, SLOT(I_on_rms_checkbox_checked_slot()));
    QObject::disconnect(V_on_rms, SIGNAL(clicked()), this, SLOT(I_on_rms_checkbox_checked_slot()));
    QObject::disconnect(LHC_on_rms, SIGNAL(clicked()), this, SLOT(I_on_rms_checkbox_checked_slot()));
    QObject::disconnect(RHC_on_rms, SIGNAL(clicked()), this, SLOT(I_on_rms_checkbox_checked_slot()));
    QObject::disconnect(show_pts, SIGNAL(clicked()), this, SLOT(show_points_or_lines()));
    QObject::disconnect(show_lns, SIGNAL(clicked()), this, SLOT(show_points_or_lines()));
    QPushButton::disconnect(&recalculate_integration, SIGNAL(clicked()), this, SLOT(recalculate_integration_on_rms_slot()));
    QPushButton::disconnect(&export_rms_vs_tme, SIGNAL(clicked()), this, SLOT(exp_rms_vs_time()));
    QPushButton::disconnect(&export_tint_vs_tme, SIGNAL(clicked()), this, SLOT(exp_sint_vs_time()));
    QPushButton::disconnect(&export_all_vs_tme, SIGNAL(clicked()), this, SLOT(exp_all()));
    QPushButton::disconnect(&export_tsys_vs_tme, SIGNAL(clicked()), this, SLOT(exp_tsys_vs_time()));
    rms_section_opened = 0;
}

void body::set_plot_on_rms_vs_time()
{
    rms_vs_time.clearGraphs();
    // wektor z danymi
    QVector < double > xI(Ilst.size()), yI(Ilst.size()), yV(Ilst.size()), yLHC(Ilst.size()), yRHC(Ilst.size());

    // zapelniamy wektory
    for(unsigned int i = 0; i < Ilst.size(); i++)
    {
        xI[i] = mjdlst[i];
        yI[i] = ERRlst[i][0];
        yV[i] = VERRlst[i][0];
        yLHC[i] = LHCERRlst[i][0];
        yRHC[i] = RHCERRlst[i][0];
    }
    // -- graphy --
    // -- dodajemy grafike (I) --
    rms_vs_time.addGraph();
    if(I_on_rms->isChecked())
    {
        rms_vs_time.graph(0)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(0)->setVisible(false);
    }
    rms_vs_time.graph(0)->setName("I");
    rms_vs_time.graph(0)->setPen(QPen(Qt::blue));
    rms_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // -- dodajemy grafike (V) --
    rms_vs_time.addGraph();
    if(V_on_rms->isChecked())
    {
        rms_vs_time.graph(1)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(1)->setVisible(false);
    }
    rms_vs_time.graph(1)->setName("V");
    rms_vs_time.graph(1)->setPen(QPen(Qt::black));
    rms_vs_time.graph(1)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // -- dodajemy grafike (V) --
    rms_vs_time.addGraph();
    if(LHC_on_rms->isChecked())
    {
        rms_vs_time.graph(2)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(2)->setVisible(false);
    }
    rms_vs_time.graph(2)->setName("LHC");
    rms_vs_time.graph(2)->setPen(QPen(Qt::red));
    rms_vs_time.graph(2)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // -- dodajemy grafike (V) --
    rms_vs_time.addGraph();
    if(RHC_on_rms->isChecked())
    {
        rms_vs_time.graph(3)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(3)->setVisible(false);
    }
    rms_vs_time.graph(3)->setName("RHC");
    rms_vs_time.graph(3)->setPen(QPen(Qt::green));
    rms_vs_time.graph(3)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));

    // -- legenda --
    rms_vs_time.legend->setVisible(true);
    QFont f( "Arial", 10, QFont::Bold);
    rms_vs_time.legend->setFont(f);

    // -- dodajemy do grafiki dane --
    rms_vs_time.graph(0)->setData(xI,yI);
    rms_vs_time.graph(1)->setData(xI,yV);
    rms_vs_time.graph(2)->setData(xI,yLHC);
    rms_vs_time.graph(3)->setData(xI,yRHC);

    // -- zarzadzamy labelami --
    rms_vs_time.xAxis->setLabel("MJD");
    rms_vs_time.yAxis->setLabel("RMS");
    // -- zarzadzamy rangeami --
    //spectrum.xAxis->setRange(*min_element(x.begin(), x.end()), *max_element(x.begin(), x.end()));
    //spectrum.yAxis->setRange(*min_element(y.begin(), y.end()), *max_element(y.begin(), y.end()));
    double veldiff = *max_element(xI.begin(), xI.end()) - *min_element(xI.begin(), xI.end());
    rms_vs_time.xAxis->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    rms_vs_time.yAxis->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    // -- pokazujemy ticki na gornej osi --
    rms_vs_time.xAxis2->setVisible(true);
    rms_vs_time.yAxis2->setVisible(true);
    rms_vs_time.xAxis2->setTickLabels(false);
    rms_vs_time.yAxis2->setTickLabels(false);
    // -- dodajemy interakcje --
    rms_vs_time.setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
    rms_vs_time.axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    rms_vs_time.axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    rms_vs_time.axisRect()->setRangeZoomAxes(rms_vs_time.xAxis, rms_vs_time.yAxis);
    rms_vs_time.setSelectionRectMode(QCP::srmZoom);
    rms_vs_time.replot();
}

void body::set_plot_on_tsys_vs_time()
{
    tsys_vs_time.clearGraphs();
    // wektor z danymi
    QVector < double > xI(Ilst.size()), yI(Ilst.size());

    // zapelniamy wektory
    for(unsigned int i = 0; i < Ilst.size(); i++)
    {
        xI[i] = mjdlst[i];
        yI[i] = tsyslst[i];
    }
    // -- graphy --
    // -- dodajemy grafike (I) --
    tsys_vs_time.addGraph();

    tsys_vs_time.graph(0)->setName("I");
    tsys_vs_time.graph(0)->setPen(QPen(Qt::blue));
    tsys_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
    tsys_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));

    // -- dodajemy do grafiki dane --
    tsys_vs_time.graph(0)->setData(xI,yI);

    // -- zarzadzamy labelami --
    tsys_vs_time.xAxis->setLabel("MJD");
    tsys_vs_time.yAxis->setLabel("Tsys (K)");

    // -- zarzadzamy rangeami --
    double veldiff = *max_element(xI.begin(), xI.end()) - *min_element(xI.begin(), xI.end());
    tsys_vs_time.xAxis->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    tsys_vs_time.yAxis->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    // -- pokazujemy ticki na gornej osi --
    tsys_vs_time.xAxis2->setVisible(true);
    tsys_vs_time.yAxis2->setVisible(true);
    tsys_vs_time.xAxis2->setTickLabels(false);
    tsys_vs_time.yAxis2->setTickLabels(false);
    // -- dodajemy interakcje --
    tsys_vs_time.setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
    tsys_vs_time.axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    tsys_vs_time.axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    tsys_vs_time.axisRect()->setRangeZoomAxes(tsys_vs_time.xAxis, tsys_vs_time.yAxis);
    tsys_vs_time.setSelectionRectMode(QCP::srmZoom);
    tsys_vs_time.replot();
}

void body::set_plot_on_int_vs_time()
{
    // czyscimy tablice z int
    integrated_fluxlst_I.clear();
    integrated_fluxlst_V.clear();
    integrated_fluxlst_LHC.clear();
    integrated_fluxlst_RHC.clear();
    integrated_fluxlst_I_er.clear();
    integrated_fluxlst_V_er.clear();
    integrated_fluxlst_LHC_er.clear();
    integrated_fluxlst_RHC_er.clear();

    // liczymy calke z widma
    unsigned int min, max;
    QString mins,maxs;
    mins = rms_int_start.toPlainText();
    maxs = rms_int_end.toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString())-1;
        max = stoi(maxs.toStdString())-1;
    }
    catch(...)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Error while converting values"));
        return;
    }

    // -- obsługujemy kilka przypadków błędnego wpisania paramatrów --
    // początkowy channel większy od końcowego
    if (min > max)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel > max channel!"));
        return;
    }
    // początkowy channel mniejszy od zera
    if (min < 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel < 1!"));
        return;
    }
    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > Ilst[0].size()-1)
        max = Ilst[0].size()-1;

    chan4int_start = min;
    chan4int_end = max;

    // -- integrujemy --
    for(unsigned int i = 0; i < Ilst.size(); i++)
    {
        integrate_single(min, max, i);
        integrated_fluxlst_I.push_back(integrated_flux_I);
        integrated_fluxlst_V.push_back(integrated_flux_V);
        integrated_fluxlst_LHC.push_back(integrated_flux_LHC);
        integrated_fluxlst_RHC.push_back(integrated_flux_RHC);
        integrated_fluxlst_I_er.push_back(integrated_flux_I_er);
        integrated_fluxlst_V_er.push_back(integrated_flux_V_er);
        integrated_fluxlst_LHC_er.push_back(integrated_flux_LHC_er);
        integrated_fluxlst_RHC_er.push_back(integrated_flux_RHC_er);
    }

    // -- clearujemy grafiki --
    int_vs_time.clearGraphs();
    // -- wektory Q do wykresow --
    int nobs = integrated_fluxlst_I.size();
    QVector < double > xI(nobs), yI(nobs),yV(nobs),yLHC(nobs),yRHC(nobs),yI_er(nobs), yV_er(nobs), yLHC_er(nobs), yRHC_er(nobs);
    for(int i = 0; i < integrated_fluxlst_I.size(); i++)
    {
        xI[i] = mjdlst[i];
        yI[i] = integrated_fluxlst_I[i];
        yV[i] = integrated_fluxlst_V[i];
        yLHC[i] = integrated_fluxlst_LHC[i];
        yRHC[i] = integrated_fluxlst_RHC[i];
        yI_er[i] = integrated_fluxlst_I_er[i];
        yV_er[i] = integrated_fluxlst_V_er[i];
        yLHC_er[i] = integrated_fluxlst_LHC_er[i];
        yRHC_er[i] = integrated_fluxlst_RHC_er[i];
    }

    // -- graphy --
    // -- dodajemy grafike (I) --
    int_vs_time.addGraph();
    if(I_on_rms->isChecked())
    {
        int_vs_time.graph(0)->setVisible(true);
    }
    else
    {
        int_vs_time.graph(0)->setVisible(false);
    }
    int_vs_time.graph(0)->setName("I");
    int_vs_time.graph(0)->setPen(QPen(Qt::blue));
    int_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // -- dodajemy grafike (V) --
    int_vs_time.addGraph();
    if(V_on_rms->isChecked())
    {
        int_vs_time.graph(1)->setVisible(true);
    }
    else
    {
        int_vs_time.graph(1)->setVisible(false);
    }
    int_vs_time.graph(1)->setName("V");
    int_vs_time.graph(1)->setPen(QPen(Qt::black));
    int_vs_time.graph(1)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // -- dodajemy grafike (V) --
    int_vs_time.addGraph();
    if(LHC_on_rms->isChecked())
    {
        int_vs_time.graph(2)->setVisible(true);
    }
    else
    {
        int_vs_time.graph(2)->setVisible(false);
    }
    int_vs_time.graph(2)->setName("LHC");
    int_vs_time.graph(2)->setPen(QPen(Qt::red));
    int_vs_time.graph(2)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // -- dodajemy grafike (V) --
    int_vs_time.addGraph();
    if(RHC_on_rms->isChecked())
    {
        int_vs_time.graph(3)->setVisible(true);
    }
    else
    {
        int_vs_time.graph(3)->setVisible(false);
    }
    int_vs_time.graph(3)->setName("RHC");
    int_vs_time.graph(3)->setPen(QPen(Qt::green));
    int_vs_time.graph(3)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));

    // -- legenda --
    int_vs_time.legend->setVisible(false);
    QFont f( "Arial", 10, QFont::Bold);
    int_vs_time.legend->setFont(f);

    // -- dodajemy do grafiki dane --
    int_vs_time.graph(0)->setData(xI,yI);
    int_vs_time.graph(1)->setData(xI,yV);
    int_vs_time.graph(2)->setData(xI,yLHC);
    int_vs_time.graph(3)->setData(xI,yRHC);
    /*
    // -- errorbary --
    // I
    QCPErrorBars * errorBars_tint_I = new QCPErrorBars(int_vs_time.xAxis, int_vs_time.yAxis);
    errorBars_tint_I->setAntialiased(false);
    errorBars_tint_I->setDataPlottable(int_vs_time.graph(0));
    errorBars_tint_I->setPen(QPen(QColor(180,180,180)));
    errorBars_tint_I->setData(yI_er);
    cout << yI_er[0] << endl;
    // V
    QCPErrorBars * errorBars_tint_V = new QCPErrorBars(int_vs_time.xAxis, int_vs_time.yAxis);
    errorBars_tint_V->setAntialiased(false);
    errorBars_tint_V->setDataPlottable(int_vs_time.graph(1));
    errorBars_tint_V->setPen(QPen(QColor(180,180,180)));
    errorBars_tint_V->setData(yV_er);
    // LHC
    QCPErrorBars * errorBars_tint_LHC = new QCPErrorBars(int_vs_time.xAxis, int_vs_time.yAxis);
    errorBars_tint_LHC->setAntialiased(false);
    errorBars_tint_LHC->setDataPlottable(int_vs_time.graph(2));
    errorBars_tint_LHC->setPen(QPen(QColor(180,180,180)));
    errorBars_tint_LHC->setData(yLHC_er);
    // RHC
    QCPErrorBars * errorBars_tint_RHC = new QCPErrorBars(int_vs_time.xAxis, int_vs_time.yAxis);
    errorBars_tint_RHC->setAntialiased(false);
    errorBars_tint_RHC->setDataPlottable(int_vs_time.graph(3));
    errorBars_tint_RHC->setPen(QPen(QColor(180,180,180)));
    errorBars_tint_RHC->setData(yRHC_er);
    */
    // -- zarzadzamy labelami --
    int_vs_time.xAxis->setLabel("MJD");
    int_vs_time.yAxis->setLabel("Integrated flux");
    // -- zarzadzamy rangeami --
    //spectrum.xAxis->setRange(*min_element(x.begin(), x.end()), *max_element(x.begin(), x.end()));
    //spectrum.yAxis->setRange(*min_element(y.begin(), y.end()), *max_element(y.begin(), y.end()));
    double veldiff = *max_element(xI.begin(), xI.end()) - *min_element(xI.begin(), xI.end());
    int_vs_time.xAxis->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    int_vs_time.yAxis->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    // -- pokazujemy ticki na gornej osi --
    int_vs_time.xAxis2->setVisible(true);
    int_vs_time.yAxis2->setVisible(true);
    int_vs_time.xAxis2->setTickLabels(false);
    int_vs_time.yAxis2->setTickLabels(false);
    // -- dodajemy interakcje --
    int_vs_time.setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
    int_vs_time.axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    int_vs_time.axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    int_vs_time.axisRect()->setRangeZoomAxes(int_vs_time.xAxis, int_vs_time.yAxis);
    int_vs_time.setSelectionRectMode(QCP::srmZoom);
    int_vs_time.replot();
}

void body::I_on_rms_checkbox_checked_slot()
{
    if(I_on_rms->isChecked())
    {
        rms_vs_time.graph(0)->setVisible(true);
        int_vs_time.graph(0)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(0)->setVisible(false);
        int_vs_time.graph(0)->setVisible(false);
    }
    rms_vs_time.replot();
    int_vs_time.replot();
}

void body::V_on_rms_checkbox_checked_slot()
{
    if(V_on_rms->isChecked())
    {
        rms_vs_time.graph(1)->setVisible(true);
        int_vs_time.graph(1)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(1)->setVisible(false);
        int_vs_time.graph(1)->setVisible(false);
    }
    rms_vs_time.replot();
    int_vs_time.replot();
}

void body::LHC_on_rms_checkbox_checked_slot()
{
    if(LHC_on_rms->isChecked())
    {
        rms_vs_time.graph(2)->setVisible(true);
        int_vs_time.graph(2)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(2)->setVisible(false);
        int_vs_time.graph(2)->setVisible(false);
    }
    rms_vs_time.replot();
    int_vs_time.replot();
}

void body::RHC_on_rms_checkbox_checked_slot()
{
    if(RHC_on_rms->isChecked())
    {
        rms_vs_time.graph(3)->setVisible(true);
        int_vs_time.graph(3)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(3)->setVisible(false);
        int_vs_time.graph(3)->setVisible(false);
    }
    rms_vs_time.replot();
    int_vs_time.replot();
}

void body::recalculate_integration_on_rms_slot()
{
    set_plot_on_int_vs_time();
    show_points_or_lines();
}

void body::show_points_or_lines()
{
    if(show_pts->isChecked())
    {
        // rms vs time
        rms_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        rms_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        rms_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        rms_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        // int vs time
        int_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        int_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        int_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        int_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
        // tsys vs time
        tsys_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    }
    else
    {
        // rms vs time
        rms_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
        rms_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
        rms_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
        rms_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
        // int vs time
        int_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
        int_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
        int_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
        int_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
        // tsys vs time
        tsys_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone, 4));
    }

    if(show_lns->isChecked())
    {
        // rms vs time
        rms_vs_time.graph(0)->setLineStyle(QCPGraph::lsLine);
        rms_vs_time.graph(1)->setLineStyle(QCPGraph::lsLine);
        rms_vs_time.graph(2)->setLineStyle(QCPGraph::lsLine);
        rms_vs_time.graph(3)->setLineStyle(QCPGraph::lsLine);
        // int vs time
        int_vs_time.graph(0)->setLineStyle(QCPGraph::lsLine);
        int_vs_time.graph(1)->setLineStyle(QCPGraph::lsLine);
        int_vs_time.graph(2)->setLineStyle(QCPGraph::lsLine);
        int_vs_time.graph(3)->setLineStyle(QCPGraph::lsLine);
        // tsys vs time
        tsys_vs_time.graph(0)->setLineStyle(QCPGraph::lsLine);
    }
    else
    {
        // rms vs time
        rms_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
        rms_vs_time.graph(1)->setLineStyle(QCPGraph::lsNone);
        rms_vs_time.graph(2)->setLineStyle(QCPGraph::lsNone);
        rms_vs_time.graph(3)->setLineStyle(QCPGraph::lsNone);
        // int vs time
        int_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
        int_vs_time.graph(1)->setLineStyle(QCPGraph::lsNone);
        int_vs_time.graph(2)->setLineStyle(QCPGraph::lsNone);
        int_vs_time.graph(3)->setLineStyle(QCPGraph::lsNone);
        // tsys vs time
        tsys_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
    }

    // replotujemy
    rms_vs_time.replot();
    int_vs_time.replot();
    tsys_vs_time.replot();
}

void body::exp_sint_vs_time()
{
    // -- zapisujemy do pliku --
    min_rms_int_channel = chan4int_start;
    max_rms_int_channel = chan4int_end;
    ofstream integ;
    string filename = working_directory + "/" + srcname + "_integrated_flux_density_" + to_string(min_rms_int_channel+1) + "_to_" + to_string(max_rms_int_channel+1) +  ".DAT";
    integ.open(filename.c_str());

    if(include_pytime->isChecked())
    {
        // wpisujemy naglowek do pliku
        integ << "# time_in_isoformat MJD year I err V err LHC err RHC err" << endl;
        // petla zapisujaca
        for(int i = 0; i < Ilst.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << pytime_format[i] << "   " << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "   " << integrated_fluxlst_I_er[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_V_er[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_LHC_er[i] << "   " << "   " << integrated_fluxlst_RHC[i] << "   " << integrated_fluxlst_RHC_er[i] << "   " << endl;
            //integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
        //cout << "Zaznaczono pytime" << endl;
    }
    else
    {
        // wpisujemy naglowek do pliku
        integ << "# MJD year I err V err LHC err RHC err" << endl;
        // petla zapisujaca
        for(int i = 0; i < Ilst.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "   " << integrated_fluxlst_I_er[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_V_er[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_LHC_er[i] << "   " << "   " << integrated_fluxlst_RHC[i] << "   " << integrated_fluxlst_RHC_er[i] << "   " << endl;
            //integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
    }

    integ.close();
    string message = "";
    message = "Integrated over channels " + to_string(min_rms_int_channel+1) + " -> " + to_string(max_rms_int_channel+1) + "\n" + "Saved to " + filename;
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));
}

void body::exp_rms_vs_time()
{
    ofstream integ;
    string filename = working_directory + "/" + srcname + "_rms_vs_time.DAT";
    integ.open(filename.c_str());

    if(include_pytime->isChecked())
    {
        // wpisujemy naglowek do pliku
        integ << "# time_in_isoformat MJD year RMS_I RMS_V RMS_LHC RMS_RHC" << endl;
        // petla zapisujaca
        for(int i = 0; i < Ilst.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << pytime_format[i] << "   " << mjdlst[i] << "   " << yrlst[i] << "   " << ERRlst[i][0] << "   " << VERRlst[i][0] << "  " << LHCERRlst[i][0] << "   " << RHCERRlst[i][0] << endl;
            //integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
        //cout << "Zaznaczono pytime" << endl;
    }
    else
    {
        // wpisujemy naglowek do pliku
        integ << "# MJD year RMS_I RMS_V RMS_LHC RMS_RHC" << endl;
        // petla zapisujaca
        for(int i = 0; i < Ilst.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << ERRlst[i][0] << "   " << VERRlst[i][0] << "  " << LHCERRlst[i][0] << "   " << RHCERRlst[i][0] << endl;
            //integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
    }
    integ.close();
    string message = "";
    message = "Saved RMS vs time to " + filename;
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}

void body::exp_all()
{
    exp_sint_vs_time();
    exp_rms_vs_time();
    exp_tsys_vs_time();
}

void body::exp_tsys_vs_time()
{
    ofstream integ;
    string filename = working_directory + "/" + srcname + "_tsys_vs_time.DAT";
    integ.open(filename.c_str());

    if(include_pytime->isChecked())
    {
        // wpisujemy naglowek do pliku
        integ << "# time_in_isoformat MJD year Tsys (K)" << endl;
        // petla zapisujaca
        for(int i = 0; i < Ilst.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << pytime_format[i] << "   " << mjdlst[i] << "   " << yrlst[i] << "   " << tsyslst[i] << endl;
            //integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
        //cout << "Zaznaczono pytime" << endl;
    }
    else
    {
        // wpisujemy naglowek do pliku
        integ << "# MJD year Tsys (K)" << endl;
        // petla zapisujaca
        for(int i = 0; i < Ilst.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << "   " << mjdlst[i] << "   " << yrlst[i] << "   " << tsyslst[i] << endl;
            //integ << fixed << setprecision(11) << mjdlst[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
    }
    integ.close();
    string message = "";
    message = "Saved Tsys vs time to " + filename;
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}
