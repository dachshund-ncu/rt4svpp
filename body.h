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
#include "qcustomplot.h"
#include <deque>
#include <stdlib.h>
using namespace std;
class body : public QObject
{
    Q_OBJECT
public:
    body(const char * nazwa = "");
    // -- deklarujemy obiekty w programie  --
    QWidget window; // okno
    QGridLayout grid; // siatka
    // -- group boxy --
    //QVBoxLayout loaders_layout;
    //QGroupBox loaders;
    QPushButton load_data; // przyciski
    QPushButton reload;
    QPushButton dynamic_spectrum;
    QPushButton kill_dynspec;
    QPushButton integrate_button;
    QPushButton quit;
    QPushButton aver_over_velocity;
    QPushButton aver_over_time;
    QPushButton spectral_index;
    QPushButton single_spectrum;
    QPushButton kill_singspec;
    QPushButton y_down_border;
    QPushButton y_up_border;
    QPushButton x_left_border;
    QPushButton x_right_border;
    QPushButton reset;
    QPushButton Ibut,Vbut,LHCbut, RHCbut;
    QPushButton save_plots_on_single_spectrum;
    QPushButton display_plot_on_single_spectrum;
    QPushButton set_default_range_button;
    QPushButton erase_last_graph;
    QPushButton flag; // do flagowania
    QPushButton make_lcs_button; // robi krzywe blasku z zaznaczonego kwadratu
    QStringList AVRNAMES_from_load;

    // -- do sprawdzania, czy user chce eksportować czas również w formacie pytime --
    QCheckBox *include_pytime = new QCheckBox ("Include time in isoformat", &window);

    // -- Do rotacji widm --
    QPushButton rotate;
    QPushButton rotate_minus;
    QTextEdit number_of_rotated_channels_texted;
    // --------------------------------------
    QPushButton save_rotation;
    QFrame ramka; // rama
    QSizePolicy sizepolicy;
    QCPColorGradient gradient;

    // -- do kalibracji nieskalibrowanych obserwacji --
    // buttony
    QPushButton calibrate; // w menu glownym
    QPushButton load_caltab_l1; // bedzie ladowac tablice do rhc
    QPushButton load_caltab_r1; // bedzie ladowac tablice do lhc
    QPushButton start_calibration; // bedzie startowac kalibracje
    QPushButton toggle_calibration_button; // bedzie robić on/off kalibracji
    // texty
    QLabel caltab_l1_path; // tekst pokazujacy czy zaladowano caltab
    QLabel caltab_r1_path; // tekst pokazujacy czy zaladowano caltab
    // stringi
    string caltab_LHC_path;
    string caltab_RHC_path;
    // boole
    bool calibration_section_opened = 0;
    bool calgridloaded = 0;
    bool lhc_loaded = 0;
    bool rhc_loaded = 0;
    bool cal_toggled = 0;
    bool calibration_done = 0;
    // kontenery
    vector < double > CALTAB_L1_epochs;
    vector < double > CALTAB_L1;
    vector < double > CALTAB_R1_epochs;
    vector < double > CALTAB_R1;
    vector < double > calcoefs_lhc;
    vector < double > calcoefs_rhc;
    // layouty
    QHBoxLayout L1;
    QHBoxLayout R1;
    QHBoxLayout calbtns;
    QVBoxLayout calibrate_layout;
    // funkcje
    double find_cal_coefficent(double epoch);
    
    // -- do robienia pliku z widmem dynamicznym --
    QPushButton WD;
    QPushButton WD_start;

    bool wd_section_opened = 0;
    QTextEdit start_chanwd, end_chanwd;

    QVBoxLayout wd_layout;
    QHBoxLayout btns;
    QHBoxLayout start_channelwd_label;
    QHBoxLayout end_channelwd_label;

    QLabel start_channelwd;
    QLabel end_channelwd;

    // -- do robienia sekcji rms vs czas --
    // - buttony -
    QPushButton open_rms_section;
    QPushButton kill_rms_section;
    QPushButton recalculate_integration;
    QPushButton export_rms_vs_tme;
    QPushButton export_tint_vs_tme;
    QPushButton export_tsys_vs_tme;
    QPushButton export_all_vs_tme;
    QPushButton show_selected_spectrum;


    // - wykresy -
    QCustomPlot rms_vs_time;
    QCustomPlot tsys_vs_time;
    QCustomPlot int_vs_time;
    // -- do crosshair --
    QCPItemLine * rms_x_axis_line = new QCPItemLine(&rms_vs_time);
    QCPItemLine * rms_y_axis_line = new QCPItemLine(&rms_vs_time);
    QCPItemLine * tint_x_axis_line = new QCPItemLine(&int_vs_time);
    QCPItemLine * tint_y_axis_line = new QCPItemLine(&int_vs_time);
    QCPItemLine * tsys_x_axis_line = new QCPItemLine(&tsys_vs_time);
    QCPItemLine * tsys_y_axis_line = new QCPItemLine(&tsys_vs_time);
    // labele
    QCPItemText * rms_csh_label = new QCPItemText(&rms_vs_time);
    QCPItemText * tint_csh_label = new QCPItemText(&int_vs_time);
    QCPItemText * tsys_csh_label = new QCPItemText(&tsys_vs_time);
    // - checkboxy -
    //QCheckBox *include_pytime = new QCheckBox ("Include time in isoformat", &window);
    QCheckBox * I_on_rms = new QCheckBox ("I", &window);
    QCheckBox * V_on_rms = new QCheckBox ("V", &window);
    QCheckBox * LHC_on_rms = new QCheckBox ("LHC", &window);
    QCheckBox * RHC_on_rms = new QCheckBox ("RHC", &window);
    QCheckBox * show_pts = new QCheckBox ("Show points", &window);
    QCheckBox * show_lns = new QCheckBox ("Show lines", &window);
    QCheckBox * rect_zoom = new QCheckBox ("Rectangle zoom", &window);
    QCheckBox * selection_of_point = new QCheckBox ("Select", &window);
    //QCheckBox  I_on_rms;
    //QCheckBox  V_on_rms;
    //QCheckBox  LHC_on_rms;
    //QCheckBox  RHC_on_rms;


    // - text edity -
    QTextEdit rms_int_start;
    QTextEdit rms_int_end;
    QLabel rms_int_start_label;
    QLabel rms_int_end_label;
    QLabel rms_vs_time_label;
    QLabel tsys_vs_time_label;
    QLabel int_vs_time_label;
    QLabel stokes_parameters;
    QLabel integration_parameters_label;
    QLabel exporting_rms_section_label;
    QLabel graph_params_label;

    // -inty - do przechowywania channelow -
    int min_rms_int_channel = 500;
    int max_rms_int_channel = 1500;
    // - layouty -
    QVBoxLayout preferences_on_rms;
    QHBoxLayout checkboxes_of_pol;
    QHBoxLayout start_chan;
    QHBoxLayout end_chan;
    QHBoxLayout show_ptslns;
    QHBoxLayout selection_modes;
    QVBoxLayout exporting_on_rms;

    // - kontnery -
    vector < double > I_sint, V_sint, LHC_sint, RHC_sint, I_sint_e, V_sint_e, LHC_sint_e, RHC_sint_e;

    // boole
    bool rms_section_opened = 0;

    // do dodatkowego okna z widmem
    QWidget popup_window; // okno
    QGridLayout grid_of_popup_window; // siatka
    QCustomPlot spectrum_on_popup_window;
    QPushButton flag_on_popup_window;
    QPushButton close_popup_window;
    QLabel label_on_popup_window;
    bool popup_window_opened = 0;



    // -- ISTOTNE - widgety do umieszczania wykresow --
    QCustomPlot spectrum;
    QCustomPlot dynamic_spectrum_pl;
    //QCustomPlot  * color_scale_plot = new QCustomPlot(&dynamic_spectrum_pl);
    QCustomPlot single_dynamic_spectrum;
    QCustomPlot lcs_dynamic_spectrum;
    QCPItemLine * x_axis_line = new QCPItemLine(&dynamic_spectrum_pl);
    QCPItemLine * y_axis_line = new QCPItemLine(&dynamic_spectrum_pl);


    QCPItemLine * vel_line = new QCPItemLine(&single_dynamic_spectrum);
    QCPItemLine * epoch_line = new QCPItemLine(&lcs_dynamic_spectrum);
    QCPColorMap * colorMap = new QCPColorMap(dynamic_spectrum_pl.xAxis, dynamic_spectrum_pl.yAxis);
    QCPColorScale * colorScale = new QCPColorScale(&dynamic_spectrum_pl);
    QCPMarginGroup * marginGroup = new QCPMarginGroup(&dynamic_spectrum_pl);

    QCPErrorBars *errorBars = new QCPErrorBars(lcs_dynamic_spectrum.xAxis, lcs_dynamic_spectrum.yAxis);
    QShortcut * y_down_border_shrt = new QShortcut(&window);
    QShortcut * y_up_border_shrt = new QShortcut(&window);
    QShortcut * x_down_border_shrt = new QShortcut(&window);
    QShortcut * x_up_border_shrt = new QShortcut(&window);
    QShortcut * reset_dynamic_spectrum = new QShortcut(&window);
    QGroupBox * obsparams = new QGroupBox();
    QCPItemRect * rectangle = new QCPItemRect(&dynamic_spectrum_pl);
    QLabel mjd_label;
    QLabel date;
    QLabel cocochanel;
    QLabel radial_velocity;
    QLabel obsnumber;
    QLabel value;
    //QWidget for_vboxmain;
    //QVBoxLayout * vbox_main = new QVBoxLayout(&for_vboxmain);
    QVBoxLayout vbox_main;
    QVBoxLayout on_dyn_spec_buttons;



    //QWidget * for_hbox = new QWidget();
    QGroupBox * butters = new QGroupBox();
    QHBoxLayout * hbox = new QHBoxLayout();
    QHBoxLayout * operations = new QHBoxLayout();
    QVBoxLayout * vbox_single = new QVBoxLayout();
    QComboBox * list_of_observations = new QComboBox();

    // -- layout do integrate --
    //QWidget window_for_integrate;
    QPushButton make_int;
    QPushButton make_spind;
    QPushButton make_aver;
    QPushButton make_aver_time;
    QPushButton cancel;
    QTextEdit starting_channel;
    QTextEdit ending_channel;
    QHBoxLayout start;
    QHBoxLayout end;
    QHBoxLayout butterbean;
    QVBoxLayout integrate_layout;
    QLabel start_label;
    QLabel end_label;
    deque < QCPItemRect * > flagi;
    int flags_number = 0;

    // -- labele do listy przyciskow --
    QLabel load_data_section_label;
    QLabel wiev_data_section_label;
    QLabel export_data_section_label;
    QLabel others_section_label;

    // -- boole do sprawdzania statusow --
    bool layers_exist = 0;
    bool color_scale_indicator = 0;
    bool single_dynamic_spectrum_graph_added = 0;
    bool lcs_dynamic_spectrum_graph_added = 0;
    bool dynamic_spectrum_opened = 0;
    bool single_spectrum_opened = 0;
    bool graphs_next_to_dynamical_spectrum = 0;
    bool layers_single_dyn_exist = 0;
    bool vel_line_added = 0;
    bool lcs_line_added = 0;
    bool loaded_data = 0;
    bool chan4rms_loaded = 0;
    bool chan4int_loaded = 0;
    bool layout_buttons_loaded_dynspec = 0;
    bool lhc_pressed = 0;
    bool rhc_pressed = 0;
    bool I_pressed = 1;
    bool v_pressed = 0;
    bool buttons_on_dynamic_spectrum_connected = 0;
    bool combo_loaded = 0;
    bool layout_single_loaded = 0;
    bool single_spectrum_buttons_connected = 0;
    bool integrate_window_loaded = 0;
    bool integrate_buttons_connected = 0;
    bool intgridloaded = 0;

    bool integrate_window_opened = 0;
    bool spind_window_opened = 0;
    bool aver_over_time_window_opened = 0;
    bool aver_over_velocity_window_opened = 0;
    bool flagged_files_loaded = 0;
    bool flagged_files_on_spectrum = 0;
    bool dyns_first_open = 1;
    bool made_rotation = 0;
    bool check_if_loading_not_interrupted = 0;

    bool caltabs_loaded = 0;
    int xind = 0;
    int yind = 0;
    int max_range_vel_index;
    int min_range_vel_index = 0;
    int min_obs_number = 0;
    int max_obs_number;
    int rozmiar_w_x;// = mjdlst.size();
    int rozmiar_w_y;// = CHANlst[0].size();
    int n_graphs_on_single_spec = 0;
    int last_marker;
    vector < int > numbers_of_epochs_on_single_spec;

    int number_of_rotated_channels = 1;
    //int max_range_mjd_index;

public slots:
    // -- METODY - do przyciskow --
    void display_single_spectrum();
    void load_time_series();
    void integrate_time_series();
    void kill_single_spectrum();
    void display_dynamic_spectrum();
    void kill_dynamic_spectrum();
    void press_map(QMouseEvent * event);
    void set_max_range_on_dynamic_specrum_y_up();
    void set_max_range_on_dynamic_specrum_y_down();
    void set_max_range_on_dynamic_specrum_x_right();
    void set_max_range_on_dynamic_specrum_x_left();
    void set_I_on_dynamic_spectrum();
    void set_V_on_dynamic_spectrum();
    void set_RHC_on_dynamic_spectrum();
    void set_LHC_on_dynamic_spectrum();
    void calculate_aver_over_velocity();
    void calculate_aver_over_time();
    void calculate_spectral_index();
    void combo_box_display();
    void set_default_range();
    void remove_selected_graph();
    void save_plots_from_single_spectrum();
    void calculate_integrate_for_time_series_with_buttons();
    void close_window_for_integrate();
    void calculate_spectral_index_for_time_series_with_buttons();
    void close_window_for_spind();
    void calculate_aver_over_velocity_for_time_series_with_buttons();
    void close_window_for_aver_over_velocity();
    void calculate_aver_over_time_for_time_series_with_buttons();
    void close_window_for_aver_over_time();
    void reload_slot();
    void make_lcs_slot();
    void flag_slot();
    void rotate_slot_plus();
    void rotate_slot_minus();
    void save_rotated_spectras();

    void open_cal_layout();
    void close_cal_layout();
    void toggle_calibration();
    void load_l1_caltab_button();
    void load_r1_caltab_button();
    void calibrate_button();

    void open_dynspectum_layout();
    void close_dynspectrum_layout();
    void export_file_for_dynamic_spectrum();

    void open_rms_section_slot();
    void close_rms_section_slot();
    void I_on_rms_checkbox_checked_slot();
    void V_on_rms_checkbox_checked_slot();
    void LHC_on_rms_checkbox_checked_slot();
    void RHC_on_rms_checkbox_checked_slot();
    void recalculate_integration_on_rms_slot();
    void show_points_or_lines();
    void exp_sint_vs_time();
    void exp_rms_vs_time();
    void exp_tsys_vs_time();
    void exp_all();
    void cross_hair_rms_vs_time(QMouseEvent * event);
    void cross_hair_tsys_vs_time(QMouseEvent * event);
    void cross_hair_tint_vs_time(QMouseEvent * event);
    void set_unset_rect_zoom();
    void show_spectrum_on_select_rms(QMouseEvent * event);
    void show_spectrum_on_select_tint(QMouseEvent * event);
    void show_spectrum_on_select_tsys(QMouseEvent * event);
    void selection_point_on_rms_slot_for_graph_visibility();
    void open_popup_window();
    void close_popup_window_slot();
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
    vector < double > tsyslst;
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

    vector < vector < double > >  LHClst;
    vector < vector < double > >  RHClst;
    vector < vector < double > >  Vlst;
    vector < vector < double > >  Ilst;
    vector < vector < double > >  VELlst;
    vector < vector < int > >  CHANlst;
    vector < vector < double > >  ERRlst, VERRlst, LHCERRlst, RHCERRlst;
    /*
    vector < vector < double > >  tmpLHClst;
    vector < vector < double > >  tmpRHClst;
    vector < vector < double > >  tmpVlst;
    vector < vector < double > >  tmpIlst;
    vector < vector < double > >  tmpERRlst, tmpVERRlst, tmpLHCERRlst, tmpRHCERRlst;
*/
    vector < double > VI_I, VI_LHC, VI_RHC, VI_V;
    vector < double > FI_I, FI_LHC, FI_RHC, FI_V;
    vector < double > chi2_I, chi2_LHC, chi2_RHC, chi2_V;
    vector < int > rotated_spectras;

    // METODY - nie do przyciskow
    void czytaj(const char *nazwa_pliku); // zapełnia zmienne i kontenery danymi
    void wypisz(); // wypisuje dane w wybranym w zadaniu szyku
    double JD(double year, double day, double month); // zwraca dzien julianski z podanego roku, dnia i miesiaca
    void read_time_series ();
    void read_time_series_for_list(QStringList lista_plikow);
    void integrate_single(int min, int max, unsigned int marker);
    void read_chan4rms();
    void press_map_met();
    void set_down_IVLHCRHCbuttons();
    bool read_flagged_files();
    bool read_chan4int();
    bool check_if_flagged(string avr_filename);
    void append_to_rotated_lst(int marker);
    bool check_if_is_on_rotated_lst(int marker);
    void save_avr_file(string target_filename, string header, vector < double > i, vector < double > v, vector < double > lhc, vector < double > rhc);

    void read_number_of_rotated_channels();

    void load_l1_caltab(string filename);
    void load_r1_caltab(string filename);
    void calibrate_method();
    void update_dynamic_spectrum();

    void set_label_on_popup_window();
    bool read_calconfig();

    int find_epoch_in_caltab(int index_of_epoch, string type_of_caltab);
    int find_previous_epoch(int index_of_epoch, string type_of_caltab);
    int find_next_epoch(int index_of_epoch, string type_of_caltab);
    vector < double > calibrate_single(int epoch_number);


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
    //void read_chan4int();

};

#endif // BODY_H
