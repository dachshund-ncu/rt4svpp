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
#include "UI/varcoefscalcwidget.h"
#include "UI/rms_selector.h"
using namespace std;

class body : public QObject
{

    Q_OBJECT

public:
    body(const char * nazwa);

    // NEW STUFF
    // ------------------------------
    vbox_mainw * left_hand_list = new vbox_mainw(this);
    integrate_widget * intWidget = new integrate_widget(this, "Integrate (channels)", "Integrate");
    integrate_widget * averOverVelocityWidget = new integrate_widget(this, "Aver Over Velocity (channels)", "Aver over velocity");
    integrate_widget * averOverTimeWidget = new integrate_widget(this, "Aver over Time (epochs)", "Aver over time");
    integrate_widget * normalizationSelector = new integrate_widget(this, "Normalization channels", "Normalization");
    varCoefsCalcWidget * SpectralIndexWidget = new varCoefsCalcWidget(this, "Variability coefficients (epochs)", "Var. coeffs");
    export_dynamic_spectrum_widget * exDynspWidget = new export_dynamic_spectrum_widget(this, "Export Dynamic Spectrum");
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
    // -- menu --
    rms_selector * selectorOfRMS = new rms_selector();
    // END OF NEW STUFF

    // -- deklarujemy obiekty w programie  --
    QWidget window; // okno
    QGridLayout * grid = new QGridLayout(&window); // siatka
    // --------------------------------------

    // -- group boxy --
    // -- glowne widgety --
    //QPushButton * kill_dynspec = new QPushButton(dynspecWidget);

    deque < QCPItemRect * > flagi;
    int flags_number = 0;

    //QPushButton * kill_singspec = new QPushButton(&window);

    QStringList AVRNAMES_from_load;

    // -- do robienia sekcji rms vs czas --
    // - buttony -
    //QPushButton * kill_rms_section = new QPushButton(&window);
    // - kontnery -
    vector < double > I_sint, V_sint, LHC_sint, RHC_sint, I_sint_e, V_sint_e, LHC_sint_e, RHC_sint_e;


    // -------------------------------------
    // -- QMenuBar --
    QMenuBar * superMegaMenuBar = new QMenuBar();
    // -- QMENU --
    QMenu * filesM = new QMenu(tr("&File"));
    QMenu * advancedM = new QMenu(tr("&Advanced"));
    QMenu * dynSpecM = new QMenu(tr("&Dynamic spectrum"));
    QMenu * singSpecM = new QMenu(tr("&Single spectrum"));
    QMenu * rmsSecM = new QMenu(tr("&RMS section"));
    // actions
    // FILE
    QAction * loadAVRFile = new QAction(filesM);
    QAction * loadFITSFile = new QAction(filesM);
    QAction * reload = new QAction(filesM);
    QAction * quit = new QAction(filesM);
    // ADVANCED
    QAction * openDynamicSpectrumA = new QAction(advancedM);
    QAction * openSingleSpectrumA = new QAction(advancedM);
    QAction * openRmsSectionA = new QAction(advancedM);
    QAction * openIntegrationA = new QAction(advancedM);
    QAction * openAverOverVelA = new QAction(advancedM);
    QAction * openAverOverTimeA = new QAction(advancedM);
    QAction * openSpindicateA = new QAction(advancedM);
    QAction * openExportDynSpectrumA = new QAction(advancedM);
    QAction * openCalibrateSectionA = new QAction(advancedM);
    QAction * darthModeA = new QAction(advancedM);
    QAction * isoTimeA = new QAction(advancedM);
    QAction * setRmsChannelsA = new QAction(advancedM);
    // DYNAMIC SPECTRUM
    QAction * showIonDS = new QAction(dynSpecM);
    QAction * showVonDS = new QAction(dynSpecM);
    QAction * showLHConDS = new QAction(dynSpecM);
    QAction * showRHConDS = new QAction(dynSpecM);
    QAction * recalIVA = new QAction(dynSpecM);
    QAction * flagA = new QAction(dynSpecM);
    QAction * rotatePlus = new QAction(dynSpecM);
    QAction * rotateMinus = new QAction(dynSpecM);
    QAction * save = new QAction(dynSpecM);
    QAction * makeLCS = new QAction(dynSpecM);
    QAction * logScale = new QAction(dynSpecM);
    QAction * rotate_IVLR = new QAction(dynSpecM);
    QAction * resetDS = new QAction(dynSpecM);
    QAction * normalize = new QAction(dynSpecM);
    QAction * cancelNormalize = new QAction(dynSpecM);
    // SINGLE SPECTRUM
    QAction * exportAllSpectraA = new QAction(singSpecM);
    QAction * displayOnSingleSpecA = new QAction(singSpecM);
    QAction * setDefaultRangeA = new QAction(singSpecM);
    QAction * eraseLastGraphA = new QAction(singSpecM);
    QAction * exportSpectraFromGraphA = new QAction(singSpecM);
    // RMS SECTION
    QAction * stokesIA = new QAction(rmsSecM);
    QAction * stokesVA = new QAction(rmsSecM);
    QAction * stokesLHCA = new QAction(rmsSecM);
    QAction * stokesRHCA = new QAction(rmsSecM);
    // -
    QAction * showPointsA = new QAction(rmsSecM);
    QAction * showLinesA = new QAction(rmsSecM);
    QAction * rectangleZoomA = new QAction(rmsSecM);
    QAction * showCrosshairA = new QAction(rmsSecM);
    // -
    QAction * showSelSpectrumA = new QAction(rmsSecM);
    QAction * rescaleA = new QAction(rmsSecM);
    // -
    QAction * exportRmsVsTimeA = new QAction(rmsSecM);
    QAction * exportSintVsTimeA = new QAction(rmsSecM);
    QAction * exportTsysVsTimeA = new QAction(rmsSecM);
    QAction * exportAllParameA = new QAction(rmsSecM);
    // -
    QAction * recalculateIntegrationA = new QAction(rmsSecM);
    // -------------------------------------

private:
    void createMenuEntries();
    void updateBar();
    void makeActions();
private slots:
    void connectActionsInSuperBar();
public:
    void addDynspec();
    void addSingspec();
    void addRmssec();
    void hideAll();
    // -------------------------------------


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

    bool dark_mode_enabled = true;
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

private:
    bool checkIfFits(const char * filename);
    void setCheckedProperButtons();
public slots:
    // -- METODY - do przyciskow --
    // -- ladowanie danych --
    void load_time_series_AVR();
    void load_time_series_FITS();
    void loadTimeSeriesWrapper(QFileDialog * fileDialog);
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
    void set_dark_mode(bool mode = true);
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

    double readNumberFromQTextEdit(QTextEdit * box);
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
    // -- choosing polarization on heat map (just to make it menu-compatible --
    void choosePolIButton();
    void choosePolVButton();
    void choosePolLHCButton();
    void choosePolRHCButton();
    void connectSomeButtons();
    void setProperActionsChecked();
    // -- for log scale working also from the menu --
    void setLogScaleSlot();
    void setLogScaleForAction();
    // -- for IVLR checkboxes to work together --
    void setIVLRCheckBox();
    void setIVLRAction();
    // -- dark mode --
    void darkModeAction();
    void darkModeSlot();
    // -- isotime --
    void isoTimeWrapper();
    void isoTimeWrapperAction();
    // -- RMS SECTION --
    //void setIonRMSAction();
    //void setVonRMSAction();
    //void setLHConRMSAction();
    //void setRHConRMSAction();
    void checkboxPolRmsWrapperAction();
    void checkboxPolRmsWrapperButton();
    void otherCheckboxesWrapperAction();
    void otherCheckboxesWrapperButton();
    // -- RMS SELECTOR --
    void connectButtonsOnRmsSelection();
    void setNewRMSChannels();
    void showRmsSelector();
    // -- NORMALIZATION --
    void showNormalizationWindow();
    void hideNormalizationWindow();
    void goWithNormalization();
    void cancelNormalization();
};

#endif // BODY_H
