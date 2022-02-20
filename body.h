#ifndef BODY_H
#define BODY_H

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
#include "libs/qcustomplot.h"
#include <deque>
#include <stdlib.h>
#include <CCfits/CCfits>
#include "data/spectral_container.h"
#include "UI/vbox_main.h"
#include "UI/integrate_widget.h"
#include "UI/export_dynamic_spectrum_widget.h"
#include "UI/calsection.h"
#include "UI/heat_map_widget.h"
#include "UI/single_spec_widget.h"
#include "UI/rms_sec_widget.h"
using namespace std;

class body : public QObject
{

    Q_OBJECT

public:
    body(const char * nazwa);

    // NEW STUFF
    // ------------------------------
    vbox_mainw * left_hand_list = new vbox_mainw(this);
    integrate_widget * intWidget = new integrate_widget(this, "Integrate (channels)");
    integrate_widget * averOverVelocityWidget = new integrate_widget(this, "A.O.V. (channels)");
    integrate_widget * averOverTimeWidget = new integrate_widget(this, "A.O.T. (epochs)");
    integrate_widget * SpectralIndexWidget = new integrate_widget(this, "S.I. (epochs)");
    export_dynamic_spectrum_widget * exDynspWidget = new export_dynamic_spectrum_widget(this, "Export DS");
    calsection * calibrateWidget = new calsection(this, "Calibrate");
    // -------------------------------
    // -- do przechowywania danych --
    spectral_container * dataTable = new spectral_container;
    // -- do widma dynamicznego --
    // dostaje dodatkowy wskaźnik na checkbox do isotime, żeby móc czytać jaki jest jego stan
    heat_map_widget * dynspecWidget = new heat_map_widget(dataTable, left_hand_list->IsotimeInclude);
    // -- do single spectrum --
    single_spec_widget * ssWidget = new single_spec_widget(dataTable);
    // -- do RMS section --
    Rms_sec_widget * rms_sec_w = new Rms_sec_widget(dataTable);
    // END OF NEW STUFF

    // -- deklarujemy obiekty w programie  --
    QWidget window; // okno
    QGridLayout * grid = new QGridLayout(&window); // siatka

    // ------  SEKCJA DO DOPASOWYWANIA GAUSSA ------
    // - WIDGET -
    QWidget * gauss_fitting_widget = new QWidget(&window);

    // - customploty -
    QCustomPlot * spectrum_w_gauss = new QCustomPlot(gauss_fitting_widget);
    // axis recty
    QCPAxisRect * gorne_widmo_gauss = new QCPAxisRect(spectrum_w_gauss, true);
    QCPAxisRect * dolne_widmo_gauss = new QCPAxisRect(spectrum_w_gauss, true);
    // linie do crosshair
    //QCPItemLine * gauss_h_crosshair = new QCPItemLine(spectrum_w_gauss);
    //QCPItemLine * gauss_v_crosshair = new QCPItemLine(spectrum_w_gauss);
    //QCPItemLine * gauss_res_crosshair = new QCPItemLine(spectrum_w_gauss);

    // - buttony -
    QPushButton * fit_gauss = new QPushButton(gauss_fitting_widget);
    QPushButton * kill_gauss = new QPushButton(&window);
    QPushButton * prev_epoch = new QPushButton(gauss_fitting_widget);
    QPushButton * next_epoch = new QPushButton(gauss_fitting_widget);
    QPushButton * set_clicker_gauss = new QPushButton(gauss_fitting_widget);
    QPushButton * change_bounds = new QPushButton(gauss_fitting_widget);
    QPushButton * set_range_to_fit_limits = new QPushButton(gauss_fitting_widget);
    QPushButton * set_range_to_data = new QPushButton(gauss_fitting_widget);


    // - groupboxy -
    QGroupBox * fitted_params_gb = new QGroupBox("Fitted parameters");
    QGroupBox * starting_fit_params_gb = new QGroupBox("Starting fit parameters");
    //QWidget * fitted_params_gb = new QWidget(gauss_fitting_widget);
    //QWidget * starting_fit_params_gb = new QWidget(gauss_fitting_widget);

    // - layouty -
    QGridLayout * grid_for_gauss = new QGridLayout(gauss_fitting_widget);
    QVBoxLayout * fitted_params = new QVBoxLayout();
    QVBoxLayout * starting_fit_params = new QVBoxLayout();
    QHBoxLayout * top_right_buttons_gauss = new QHBoxLayout();
    QVBoxLayout * top_right_buttons_gauss_V = new QVBoxLayout();
    QVBoxLayout * labels_over_plot_gauss = new QVBoxLayout();
    QHBoxLayout * top_left_buttons_gauss = new QHBoxLayout();

    //QHBoxLayout * first_gauss_amp_start = new QHBoxLayout();
    //QHBoxLayout * first_gauss_vel_start = new QHBoxLayout();
    //QHBoxLayout * first_gauss_fwhm_start = new QHBoxLayout();
    //QHBoxLayout * first_gauss_amp_fitted = new QHBoxLayout();
    //QHBoxLayout * first_gauss_vel_fitted = new QHBoxLayout();
    //QHBoxLayout * first_gauss_fwhm_fitted = new QHBoxLayout();
    QHBoxLayout * fit_range_managment = new QHBoxLayout();
    QVBoxLayout * checkboxes_on_left_top = new QVBoxLayout();
    QVBoxLayout * range_buttons = new QVBoxLayout();


    // -- labele --
    /*
    QLabel * amp_starting = new QLabel(gauss_fitting_widget);
    QLabel * vel_starting = new QLabel(gauss_fitting_widget);
    QLabel * fwhm_starting = new QLabel(gauss_fitting_widget);

    QLabel * amp_fitted = new QLabel(gauss_fitting_widget);
    QLabel * vel_fitted = new QLabel(gauss_fitting_widget);
    QLabel * fwhm_fitted = new QLabel(gauss_fitting_widget);
    */
    QLabel * actual_mjd_gauss = new QLabel(gauss_fitting_widget);
    QLabel * actual_epoch_nr_gauss = new QLabel(gauss_fitting_widget);

    QLabel * range_lbl = new QLabel(gauss_fitting_widget);
    QLabel * lt = new QLabel(gauss_fitting_widget);

    /*
    QLabel * pm = new QLabel(gauss_fitting_widget);
    QLabel * pm2 = new QLabel(gauss_fitting_widget);
    QLabel * pm3 = new QLabel(gauss_fitting_widget);
    QLabel * pm4 = new QLabel(gauss_fitting_widget);
    QLabel * pm5 = new QLabel(gauss_fitting_widget);
    QLabel * pm6 = new QLabel(gauss_fitting_widget);
    */
    // -- textedity --
    QTextEdit * min_fit_range = new QTextEdit(gauss_fitting_widget);
    QTextEdit * max_fit_range = new QTextEdit(gauss_fitting_widget);

    QTextEdit * fitted_params_texted = new QTextEdit(gauss_fitting_widget);
    QTextEdit * starting_params_texted = new QTextEdit(gauss_fitting_widget);
    /*
    QTextEdit * amp_starting_texed = new QTextEdit(gauss_fitting_widget);
    QTextEdit * vel_starting_texed = new QTextEdit(gauss_fitting_widget);
    QTextEdit * fwhm_starting_texed = new QTextEdit(gauss_fitting_widget);
    // errory
    QTextEdit * amp_starting_err_texed = new QTextEdit(gauss_fitting_widget);
    QTextEdit * vel_starting_err_texed = new QTextEdit(gauss_fitting_widget);
    QTextEdit * fwhm_starting_err_texed = new QTextEdit(gauss_fitting_widget);

    QTextEdit * amp_fitted_texed = new QTextEdit(gauss_fitting_widget);
    QTextEdit * vel_fitted_texed = new QTextEdit(gauss_fitting_widget);
    QTextEdit * fwhm_fitted_texed = new QTextEdit(gauss_fitting_widget);
    // errory
    QTextEdit * amp_fitted_err_texed = new QTextEdit(gauss_fitting_widget);
    QTextEdit * vel_fitted_err_texed = new QTextEdit(gauss_fitting_widget);
    QTextEdit * fwhm_fitted_err_texed = new QTextEdit(gauss_fitting_widget);
    */
    // -- checkboxy --
    QCheckBox * set_lines_gauss = new QCheckBox("Show lines", gauss_fitting_widget);
    QCheckBox * set_points_gauss = new QCheckBox("Show points", gauss_fitting_widget);
    QCheckBox * set_crosshair_gauss = new QCheckBox("Show crosshair", gauss_fitting_widget);


    // -- scroll areasy --
    //QScrollArea * scroll_fitted_params = new QScrollArea();
    //QScrollArea * scroll_starting_params = new QScrollArea();

    /*
    // -- kontenery --
    // labele
    vector < QLabel * > fitted_amp_labels;
    vector < QLabel * > fitted_vel_labels;
    vector < QLabel * > fitted_fwhm_labels;
    vector < QLabel * > fitted_amp_pm;
    vector < QLabel * > fitted_vel_pm;
    vector < QLabel * > fitted_fwhm_pm;
    // textedity
    vector < QTextEdit * > fitted_amp_texted;
    vector < QTextEdit * > fitted_vel_texted;
    vector < QTextEdit * > fitted_fwhm_texted;
    vector < QTextEdit * > fitted_amp_texted_err;
    vector < QTextEdit * > fitted_vel_texted_err;
    vector < QTextEdit * > fitted_fwhm_texted_err;
    // hboxy

    vector < QHBoxLayout > fitted_amp_hbox;
    vector < QHBoxLayout > fitted_vel_hbox;
    vector < QHBoxLayout > fitted_fwhm_hbox;
    vector < QVBoxLayout > fitted_one_record;

    // widgety
    vector < QWidget * > fitted_one_widget;
    */

    vector < bool > fit_done; // przechowuje informacje, czy dopasowanie jest zrobione dla danej obserwacji
    unsigned long int actual_obs_index_gauss = 0; // jaki obecnie mamy indeks obserwacji?

    vector < vector < double > > fitted_parameters_tab;
    vector < vector < double > > starting_fit_parameters_tab;

    // -- boole --
    bool range_to_data_set = 1;
    bool range_to_fit_set = 0;

    // -- inty --
    double min_fit_range_d;
    double max_fit_range_d;
    // ---------------------------------------------------------------------

    // -- group boxy --
    // -- glowne widgety --
    QPushButton * kill_dynspec = new QPushButton(dynspecWidget);

    deque < QCPItemRect * > flagi;
    int flags_number = 0;

    QPushButton * kill_singspec = new QPushButton(&window);

    QStringList AVRNAMES_from_load;

    // -- do robienia sekcji rms vs czas --
    // - buttony -
    QPushButton * kill_rms_section = new QPushButton(&window);
    // - kontnery -
    vector < double > I_sint, V_sint, LHC_sint, RHC_sint, I_sint_e, V_sint_e, LHC_sint_e, RHC_sint_e;

    // boole
    bool rms_section_opened = 0;

    // bole
    bool geometry_window_set = 0;
    // -- ploty --
    bool loaded_from_listfile = 0;


    // -- boole do sprawdzania statusow --
    bool wd_section_opened = false;
    bool calibration_section_opened = false;
    bool calibration_done = false;
    bool color_scale_indicator = 0;
    bool dynamic_spectrum_opened = 0;
    bool single_spectrum_opened = 0;
    bool graphs_next_to_dynamical_spectrum = 0;
    bool layers_single_dyn_exist = 0;
    bool vel_line_added = 0;
    bool dot_single_added = 0;
    bool dot_lcs_added = 0;
    bool lcs_line_added = 0;
    bool loaded_data = 1;
    bool chan4rms_loaded = 0;
    bool chan4int_loaded = 0;
    bool layout_buttons_loaded_dynspec = 0;
    bool lhc_pressed = 0;
    bool rhc_pressed = 0;
    bool I_pressed = 1;
    bool v_pressed = 0;
    bool combo_loaded = 0;
    bool layout_single_loaded = 0;
    bool single_spectrum_buttons_connected = 0;
    bool integrate_window_loaded = 0;
    bool integrate_buttons_connected = 0;
    bool intgridloaded = 0;

    bool dark_mode_enabled = 0;
    bool integrate_window_opened = 0;
    bool spind_window_opened = 0;
    bool aver_over_time_window_opened = 0;
    bool aver_over_velocity_window_opened = 0;
    bool flagged_files_loaded = 0;
    bool flagged_files_on_spectrum = 0;
    bool dyns_first_open = 1;
    bool made_rotation = 0;
    bool check_if_loading_not_interrupted = 0;

    bool gauss_section_opened = 0;

    bool caltabs_loaded = 0;
    unsigned long int xind = 0;
    unsigned long int yind = 0;
    unsigned long int max_range_vel_index;
    unsigned long int min_range_vel_index = 0;
    unsigned long int min_obs_number = 0;
    unsigned long int max_obs_number;
    unsigned long int rozmiar_w_x;// = mjdlst.size();
    unsigned long int rozmiar_w_y;// = CHANlst[0].size();
    int n_graphs_on_single_spec = 0;
    int last_marker;
    vector < int > numbers_of_epochs_on_single_spec;

    int number_of_rotated_channels = 1;
    //int max_range_mjd_index;

public slots:
    // -- METODY - do przyciskow --
    // -- ladowanie danych --
    void load_time_series();
    void reload_slot();
    // -- single widmo --
    void display_single_spectrum();
    void kill_single_spectrum();
    // -- widmo dynamiczne --
    void display_dynamic_spectrum();
    void kill_dynamic_spectrum();
    // -- rms_section --
    void open_rms_section_slot();
    void close_rms_section_slot();

    void save_all_to_gnuplot_slot();
    //void autorange_plot(QCustomPlot * plot);

    void set_dark_mode();

    void set_gauss_widget();
    void open_gauss_widget();
    void close_gauss_widget();

    // -- sloty do sekcji gaussa --
    void previous_gauss_spec();
    void next_gauss_spec();
    void actual_gauss_spec();

    void plot_initial_fit();
    void plot_fitted_fit();

    void autoscale_gauss_graph();
    bool read_gauss_range_from_txt();

    void scale_fit_plot_to_data();
    void scale_fit_plot_to_txt();

    void set_gauss_dark_mode_pens();
    void set_gauss_light_mode_pens();

    void show_lines_gauss();
    void show_points_gauss();
    void show_crosshair_gauss();

    void cross_hair_gauss(QMouseEvent * event);

    //void fitted_parameters_creator(unsigned long int amount);
    //void menu_request(QPoint pos);
    /*
    void average_over_velocity();
    void average_over_time();
    void calculate_spectral_index();
    */

public:
    // ZMIENNE do uzycia tymczasowego:
    ifstream avr; // obiekt czytanego pliku AVR
    ifstream lista; // plik z lista
    // -- do rms kanaly --
    int rms_start_channel1, rms_end_channel1;
    int rms_start_channel2, rms_end_channel2;
    // -- do calkowania kanaly --
    int chan4int_start, chan4int_end;
    int chan4aver_start, chan4ver_end;
    string list_filename = "";
    string list_path;
    double jd, mjd; // MJD
    double el, az; // Elewacja i azymut
    double dec, ra; // Deklinacja i Rektascensja
    double freq; // Czestotliwosc
    double vlsr; // Predkosc centralna
    double wst; // szerokosc wstegi
    double n_chans; // ilosc punktow
    double rms;
    double integrated_flux_I, integrated_flux_LHC, integrated_flux_RHC,integrated_flux_V; // strumien zintegrowany
    double integrated_flux_I_er, integrated_flux_LHC_er, integrated_flux_RHC_er,integrated_flux_V_er; // strumien zintegrowany
    double d,m,y;
    string srcname; // - nazwa zrodla -
    string working_directory = "."; // - katalog, w ktorym jest lista z plikami AVR

    // KONTENERY:
    vector < string > header; // naglowek
    vector < double > LHC;
    vector < double >  RHC;
    vector < double >  V;
    vector < double >  I;
    vector < double >  VEL;
    vector < int >  CHAN;
    vector < double > ERR, VERR, LHCERR, RHCERR;

    // --  stale narzedzia --
    vector < string > pytime_format;
    vector < double > jdlst;
    vector < double > mjdlst;
    vector < double > yrlst;
    vector < double > hrlst;
    vector < double > minutelst;
    vector < double > seclst;
    vector < double > ellst, azlst;
    vector < double > declst, ralst;
    vector < double > freqlst;
    vector < double > vlsrlst;
    vector < double > wstlst;
    vector < double > n_chanslst;
    vector < double > rmslst, lhcrmslst, rhcrmslst, vrmslst;
    vector < double > integrated_fluxlst_I, integrated_fluxlst_V, integrated_fluxlst_LHC, integrated_fluxlst_RHC;
    vector < double > integrated_fluxlst_I_er, integrated_fluxlst_V_er, integrated_fluxlst_LHC_er, integrated_fluxlst_RHC_er;
    vector < double > dlst, mlst, ylst;
    vector < double > averaged_over_velocity_I, averaged_over_velocity_V, averaged_over_velocity_LHC, averaged_over_velocity_RHC;
    vector < double > averaged_over_velocity_I_err, averaged_over_velocity_V_err, averaged_over_velocity_LHC_err, averaged_over_velocity_RHC_err;
    vector < double > averaged_over_time_I, averaged_over_time_V, averaged_over_time_LHC, averaged_over_time_RHC;
    vector < double > averaged_over_time_I_err, averaged_over_time_V_err, averaged_over_time_LHC_err, averaged_over_time_RHC_err;
    // -- stale kontenery -- (podwojne)
    vector < string > headerlst; // lista z headerami
    vector < string > avrnames; // lista z plikami avr
    vector < string > flagged_avr_files; // lista z oflagowanymi plikami avr

    vector < double > VI_I, VI_LHC, VI_RHC, VI_V;
    vector < double > FI_I, FI_LHC, FI_RHC, FI_V;
    vector < double > chi2_I, chi2_LHC, chi2_RHC, chi2_V;
    vector < int > rotated_spectras;
    vector < int > filetype; // przechowuje typ pliku, jaki jest załadowany (0 - avr, 1 - fits);

    // -- tworzymy nowe stałe --
    double mean_rms_I = 0.0;
    double mean_rms_V = 0.0;
    double mean_rms_LHC = 0.0;
    double mean_rms_RHC = 0.0;

    void read_chan4rms();

    bool read_flagged_files();
    bool read_chan4int();
    bool check_if_flagged(string avr_filename);
    void set_label_on_popup_window();
    bool read_calconfig();

    // -- pozostale konterery --
    vector < double > average_over_velocity(int min_chan, int max_chan, vector < double > stokes_parameter, vector < double > error);
    double decimalyear(double year, double month = 0, double day = 0);
    vector < double > average_over_time(int min_epoch, int max_epoch, vector < double > time_series, vector < double > error);
    vector < double > spectral_index_from_lcs (int min_epoch, int max_epoch, vector < double > time_series, vector < double > error );
    vector < double > max_w_index(int min_epoch, int max_epoch,vector < double > time_series, vector < double > error);
    vector < double > min_w_index(int min_epoch, int max_epoch,vector < double > time_series, vector < double > error);
    vector < int > added_obsers_to_single_spectrum;

    void set_plot_on_rms_vs_time();
    void set_plot_on_tsys_vs_time();
    void set_plot_on_int_vs_time();
    void calculate_sint_for_rms_window();
    void select_on_rms_section(double x);

    // czyta plik fits
    void read_fits_file(const char * nazwa_pliku23);

    // pomocnicze sloty do "save rotated spectras"
    vector < string > save_edited_avr(int epoch); // ten zapisuje AVR
    vector < string > save_edited_fitsfile(int epoch); // ten zapisuje fits

    void save_new_cols_in_fits_file(string fitsfilename, vector < double > lhc, vector < double > rhc);

    bool check_if_avr_or_fits(string filename_of_tested_file, bool name_with_absolute_path);
    //void connectToSlotsVboxMain();
    //void read_chan4int();
public slots:
    // --- POBOCZNE SEKCJE DO EKSPORTU ---
    // -- metody pomocnicze --
    std::vector < int > readMinMaxValuesFromChannels(QTextEdit & minChannelTE, QTextEdit & maxChannelTE);
    std::vector < int > readMinMaxValuesFromEpochs(QTextEdit & minEpochlTE, QTextEdit & maxEpochlTE);
    void closeOtherSections();
    void connectSectionsToSlots();
    // -- integrate --
    void integrate_time_series();
    void openIntegrateSection();
    void closeIntegrateSection();
    // -- aver over velocity --
    void calculate_aver_over_velocity();
    void openAOVSection();
    void closeAOVSection();
    // -- aver over time --
    void openAOTSection();
    void closeAOTSection();
    void calculate_aver_over_time();
    // -- spectral index --
    void openSPINDSection();
    void closeSPINDSection();
    void calculate_spectral_index();
    // -- dynamic spectrum exp --
    void openWDSection();
    void closeWDSection();
    void export_file_for_dynamic_spectrum();
    // -- sekcja do kalibracji --
    void openCALSection();
    void closeCALSection();
    void calibrate_button();
    void load_l1_caltab_button();
    void load_r1_caltab_button();
};

#endif // BODY_H
