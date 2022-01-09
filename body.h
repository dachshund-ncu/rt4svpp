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
    heat_map_widget * dspw = new heat_map_widget(dataTable, left_hand_list->IsotimeInclude);
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

    QWidget * dynamic_spectrum_widget = new QWidget(&window);

    QPushButton * kill_dynspec = new QPushButton(dynamic_spectrum_widget);


    QWidget * single_spectrum_widget = new QWidget(&window);
    QWidget * rms_section_widget = new QWidget(&window);

    QCustomPlot * colorbar_widget = new QCustomPlot();
    QCPColorScale * colorbar = new QCPColorScale(colorbar_widget);

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

    // funkcje
    double find_cal_coefficent(double epoch);

    //QWidget window_for_integrate;
    //QPushButton * make_int = new QPushButton(&window);
    //QPushButton * make_aver = new QPushButton(&window);
    //QPushButton * make_aver_time = new QPushButton(&window);
    //QPushButton * cancel = new QPushButton(&window);
    deque < QCPItemRect * > flagi;
    int flags_number = 0;


    QPushButton * kill_singspec = new QPushButton(&window);

    // -----------
    QVBoxLayout * checkboxes_dynspec = new QVBoxLayout();
    QCheckBox * set_log_scale = new QCheckBox ("Log scale", &window);
    QCheckBox * rotate_all_pols = new QCheckBox ("Rotate IVLR", &window);
    // -------------
    QPushButton * y_down_border = new QPushButton(dynamic_spectrum_widget);
    QPushButton * y_up_border = new QPushButton(dynamic_spectrum_widget);
    QPushButton * x_left_border = new QPushButton(dynamic_spectrum_widget);
    QPushButton * x_right_border = new QPushButton(dynamic_spectrum_widget);
    QPushButton * Ibut = new QPushButton(dynamic_spectrum_widget);
    QPushButton * Vbut = new QPushButton(dynamic_spectrum_widget);
    QPushButton * LHCbut = new QPushButton(dynamic_spectrum_widget);
    QPushButton * RHCbut = new QPushButton(dynamic_spectrum_widget);
    QPushButton * flag = new QPushButton(dynamic_spectrum_widget); // do flagowania
    QPushButton * make_lcs_button = new QPushButton(dynamic_spectrum_widget); // robi krzywe blasku z zaznaczonego kwadratu
    QPushButton * recreate_I_button = new QPushButton(dynamic_spectrum_widget);
    // -- Do rotacji widm --
    QPushButton * rotate = new QPushButton(dynamic_spectrum_widget);
    QPushButton * rotate_minus = new QPushButton(dynamic_spectrum_widget);
    QTextEdit * number_of_rotated_channels_texted = new QTextEdit(dynamic_spectrum_widget);
    QPushButton * save_rotation = new QPushButton(dynamic_spectrum_widget);
    // --------------------------------------
    QSizePolicy sizepolicy;
    QCPColorGradient gradient;

    bool first_time_dynamic_spectrum_opened = 1;
    QPushButton * save_plots_on_single_spectrum = new QPushButton(single_spectrum_widget);
    QPushButton * display_plot_on_single_spectrum = new QPushButton(single_spectrum_widget);
    QPushButton * set_default_range_button = new QPushButton(single_spectrum_widget);
    QPushButton * erase_last_graph = new QPushButton(single_spectrum_widget);
    QPushButton * save_all_spectra_to_gnuplot = new QPushButton(single_spectrum_widget);

    QStringList AVRNAMES_from_load;

    
    // -- do robienia pliku z widmem dynamicznym --
    //QPushButton * WD_start = new QPushButton(&window);

    bool wd_section_opened = 0;

    // -- do robienia sekcji rms vs czas --
    // - buttony -
    QPushButton * kill_rms_section = new QPushButton(&window);
    QPushButton * recalculate_integration = new QPushButton(rms_section_widget);
    QPushButton * export_rms_vs_tme = new QPushButton(rms_section_widget);
    QPushButton * export_tint_vs_tme = new QPushButton(rms_section_widget);
    QPushButton * export_tsys_vs_tme = new QPushButton(rms_section_widget);
    QPushButton * export_all_vs_tme = new QPushButton(rms_section_widget);
    QPushButton * show_selected_spectrum = new QPushButton(rms_section_widget);


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
    QLabel * stokes_parameters = new QLabel(rms_section_widget);
    QLabel * integration_parameters_label = new QLabel(rms_section_widget);
    QLabel * exporting_rms_section_label = new QLabel(rms_section_widget);
    QLabel * graph_params_label = new QLabel(rms_section_widget);

    // -inty - do przechowywania channelow -
    int min_rms_int_channel = 500;
    int max_rms_int_channel = 1500;
    // - layouty -
    QVBoxLayout * preferences_on_rms = new QVBoxLayout();
    QHBoxLayout * checkboxes_of_pol = new QHBoxLayout();
    QHBoxLayout * start_chan = new QHBoxLayout();
    QHBoxLayout * end_chan = new QHBoxLayout();
    QHBoxLayout * show_ptslns = new QHBoxLayout();
    QHBoxLayout * selection_modes = new QHBoxLayout();
    QVBoxLayout * exporting_on_rms = new QVBoxLayout();

    // - kontnery -
    vector < double > I_sint, V_sint, LHC_sint, RHC_sint, I_sint_e, V_sint_e, LHC_sint_e, RHC_sint_e;

    // boole
    bool rms_section_opened = 0;

    // do dodatkowego okna z widmem
    QWidget * popup_window = new QWidget();// = new QWidget(&window); // okno
    QGridLayout  * grid_of_popup_window = new QGridLayout(popup_window); // siatka
    QCustomPlot spectrum_on_popup_window;
    QPushButton * flag_on_popup_window = new QPushButton(popup_window);
    QPushButton * close_popup_window = new QPushButton(popup_window);
    QLabel * label_on_popup_window = new QLabel(popup_window);
    bool popup_window_opened = 0;



    // -- ISTOTNE - widgety do umieszczania wykresow --
    // - gridy -
    QGridLayout * grid_dynamic_spectrum_widget  = new QGridLayout(dynamic_spectrum_widget);
    QGridLayout * grid_single_spectrum_widget = new QGridLayout(single_spectrum_widget);
    QGridLayout * grid_rms_section_widget = new QGridLayout(rms_section_widget);

    // bole
    bool geometry_window_set = 0;
    // -- ploty --
    QCustomPlot spectrum;
    QCustomPlot dynamic_spectrum_pl;
    //QCustomPlot  * color_scale_plot = new QCustomPlot(&dynamic_spectrum_pl);
    QCustomPlot single_dynamic_spectrum;
    QCustomPlot lcs_dynamic_spectrum;
    QCPItemLine * x_axis_line = new QCPItemLine(&dynamic_spectrum_pl);
    QCPItemLine * y_axis_line = new QCPItemLine(&dynamic_spectrum_pl);


    QCPItemLine * vel_line = new QCPItemLine(&single_dynamic_spectrum);
    QCPItemLine * epoch_line = new QCPItemLine(&lcs_dynamic_spectrum);

    // - wertykalne linie -
    QCPItemStraightLine * inf_vel_line = new QCPItemStraightLine(&single_dynamic_spectrum);
    QCPItemStraightLine * inf_epoch_line = new QCPItemStraightLine(&lcs_dynamic_spectrum);

    QCPColorMap * colorMap = new QCPColorMap(dynamic_spectrum_pl.xAxis, dynamic_spectrum_pl.yAxis);
    QCPColorScale * colorScale = new QCPColorScale(&dynamic_spectrum_pl);
    QCPMarginGroup * marginGroup = new QCPMarginGroup(&dynamic_spectrum_pl);

    QCPErrorBars * errorBars = new QCPErrorBars(lcs_dynamic_spectrum.xAxis, lcs_dynamic_spectrum.yAxis);
    QShortcut * y_down_border_shrt = new QShortcut(dynamic_spectrum_widget);
    QShortcut * y_up_border_shrt = new QShortcut(dynamic_spectrum_widget);
    QShortcut * x_down_border_shrt = new QShortcut(dynamic_spectrum_widget);
    QShortcut * x_up_border_shrt = new QShortcut(dynamic_spectrum_widget);
    QShortcut * reset_dynamic_spectrum = new QShortcut(dynamic_spectrum_widget);
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
    QVBoxLayout * on_dyn_spec_buttons = new QVBoxLayout();



    //QWidget * for_hbox = new QWidget();
    QGroupBox * butters = new QGroupBox();
    QHBoxLayout * hbox = new QHBoxLayout();
    QHBoxLayout * operations = new QHBoxLayout();
    QVBoxLayout * vbox_single = new QVBoxLayout();
    QComboBox * list_of_observations = new QComboBox();


    bool loaded_from_listfile = 0;


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
    bool buttons_on_dynamic_spectrum_connected = 0;
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
    void display_single_spectrum();
    void load_time_series();
    void kill_single_spectrum();

    void set_dynamic_spectrum_widget();
    void plot_dynamic_spectrum();
    void display_dynamic_spectrum();

    //void set_dynamic_spectrum_widget();
    void set_single_spectrum_widget();
    void plot_single_spectrum();

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

    void combo_box_display();
    void set_default_range();
    void remove_selected_graph();
    void save_plots_from_single_spectrum();

    void reload_slot();
    void make_lcs_slot();
    void flag_slot();
    void rotate_slot_plus();
    void rotate_slot_minus();
    void save_rotated_spectras();

    void set_rms_section_widget();
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
    void calculate_log();
    void calculate_mean_rms();

    void range_zmienion_na_cb();
    void range_data_zmienion_na_cb();
    void set_down_IVLHCRHCbuttons();

    void save_all_to_gnuplot_slot();
    void autorange_plot(QCustomPlot * plot);

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

    void make_new_I_and_V_for_epoch_on_dynspec();

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
    void press_map_met(unsigned long int x, unsigned long int y);

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
    void set_dynamic_spectrum_labels_for_clicked(int x_index_cl, int y_index_cl);
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
    void load_l1_caltab_button();
    void load_r1_caltab_button();
    void calibrate_button();
};

#endif // BODY_H
