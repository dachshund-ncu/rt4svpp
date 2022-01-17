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

    // -- kilka rzeczy żeby nie było ich widać --
    I_on_rms->setVisible(false);
    V_on_rms->setVisible(false);
    LHC_on_rms->setVisible(false);
    RHC_on_rms->setVisible(false);
    show_pts->setVisible(false);
    show_lns->setVisible(false);
    rect_zoom->setVisible(false);
    selection_of_point->setVisible(false);

    // -- sizepolicy --
    kill_singspec->setMaximumSize(10000,10000);


    kill_rms_section->setMaximumSize(10000,10000);
    recalculate_integration->setMaximumSize(10000,10000);
    kill_gauss->setMaximumSize(10000,10000);
    kill_dynspec->setMaximumSize(10000,10000);

    kill_singspec->setMinimumSize(0,0);

    kill_rms_section->setMinimumSize(0,0);
    recalculate_integration->setMinimumSize(0,0);
    kill_gauss->setMinimumSize(0,0);
    kill_dynspec->setMinimumSize(0,0);

    grid->addWidget(left_hand_list, 0,0,9,1);
    grid->setColumnStretch(0,1);

    kill_dynspec->setText("Kill dynamic spectrum");
    kill_singspec->setText("Kill single spectrum");
    kill_singspec->setVisible(false);
    kill_dynspec->setVisible(false);

    // -- ustalamy ikony --
    //quit.setIcon(QIcon(":/images/exit.png"));
    // -- dodajemy layout do okna --


    // -- connectujemy przycisk do slotu --
    //QObject::connect(&quit, SIGNAL(clicked()), qApp, SLOT(quit()), Qt::QueuedConnection); // wylaczanie &QApplication::closeAllWindows

    QObject::connect(kill_gauss, SIGNAL(clicked()), this, SLOT(close_gauss_widget()));
    QObject::connect(kill_dynspec, SIGNAL(clicked()), this, SLOT(kill_dynamic_spectrum()));
    QObject::connect(kill_singspec, SIGNAL(clicked()), this, SLOT(kill_single_spectrum()));
    // -- setujemy widgety roznych sekcji --
    set_rms_section_widget();
    set_gauss_widget();

    connectSectionsToSlots();

    //cout << "Widgets set" << endl;

    // -- probojemy czytac liste --
    /*
    if (strncmp(nazwa, "", 300) == 0)
    {
        //lista.open("lista");
        dataTable->loadDataFromList("lista");
        window.setGeometry(window.x(), window.y(),1360,720);
        display_dynamic_spectrum();
        geometry_window_set = 1;
        loaded_data = true;

     }
    else
    {
        dataTable->loadDataFromList(nazwa);
        list_filename = string(nazwa);
        window.setGeometry(window.x(), window.y(),1360,720);
        display_dynamic_spectrum();
        geometry_window_set = 1;
        loaded_data = true;
    }
    */
    // -- domyślnie ustawiamy dark mode --
    set_dark_mode();

    // -- pokazujemy okno --
    window.show();

}

// --- connectujemy ---
// łączymy buttony z innymi metodami


// -------------------------------------------------------------------------------
// -- funkcje, ustawiajace widgety (wywolywane na poczatku programu i tylko wtedy)

void body::set_rms_section_widget()
{
    //
    //rms_section_widget.setParent(&window);
    rms_section_widget->setVisible(false);
    kill_rms_section->setVisible(false);
    // labele
    stokes_parameters->setText("Stokes parameters");
    integration_parameters_label->setText("Integration parameters");
    exporting_rms_section_label->setText("Exporting");
    export_rms_vs_tme->setText("Export rms vs time");
    export_tsys_vs_tme->setText("Export Tsys vs time");
    export_tint_vs_tme->setText("Export Integrated flux vs time");
    export_all_vs_tme->setText("Export all of the above");
    graph_params_label->setText("Plot properties");
    kill_rms_section->setText("Kill --->");
    // fonty w labelach
    QFont f( "Arial", 10, QFont::Bold);
    stokes_parameters->setFont(f);
    integration_parameters_label->setFont(f);
    exporting_rms_section_label->setFont(f);
    graph_params_label->setFont(f);

    // dodajemy do grida
    grid_rms_section_widget->addWidget(&rms_vs_time, 0,0,5,2);
    grid_rms_section_widget->addWidget(&tsys_vs_time, 5,0,5,2);
    grid_rms_section_widget->addWidget(&int_vs_time, 0,2,5,2);
    grid_rms_section_widget->addLayout(preferences_on_rms, 5,2,5,1);
    grid_rms_section_widget->addLayout(exporting_on_rms, 5,3,5,1);

    checkboxes_of_pol->addWidget(I_on_rms);
    checkboxes_of_pol->addWidget(V_on_rms);
    checkboxes_of_pol->addWidget(LHC_on_rms);
    checkboxes_of_pol->addWidget(RHC_on_rms);
    preferences_on_rms->addWidget(stokes_parameters);
    preferences_on_rms->addLayout(checkboxes_of_pol);

    // kanały
    rms_int_start_label.setText("Integration start channel");
    rms_int_end_label.setText("Integration end channel");
    rms_int_start.setText("500");
    rms_int_end.setText("1500");
    rms_int_start.setMaximumSize(100, 40);
    rms_int_end.setMaximumSize(100, 40);
    recalculate_integration->setText("Recalculate integration");
    show_selected_spectrum->setText("Show selected spectrum");
    start_chan->addWidget(&rms_int_start_label);
    start_chan->addWidget(&rms_int_start,Qt::AlignHCenter);
    end_chan->addWidget(&rms_int_end_label);
    end_chan->addWidget(&rms_int_end, Qt::AlignHCenter);
    preferences_on_rms->addWidget(integration_parameters_label);
    preferences_on_rms->addLayout(start_chan);
    preferences_on_rms->addLayout(end_chan);
    preferences_on_rms->addWidget(recalculate_integration);

    // przyciski do eksportowania
    export_rms_vs_tme->setMaximumSize(10000,10000);
    export_tsys_vs_tme->setMaximumSize(10000,10000);
    export_tint_vs_tme->setMaximumSize(10000,10000);
    export_all_vs_tme->setMaximumSize(10000,10000);
    exporting_on_rms->addWidget(exporting_rms_section_label);
    exporting_on_rms->addWidget(export_rms_vs_tme);
    exporting_on_rms->addWidget(export_tsys_vs_tme);
    exporting_on_rms->addWidget(export_tint_vs_tme);
    exporting_on_rms->addWidget(export_all_vs_tme);
    // dodatkowo - manipulowanie grafiką
    exporting_on_rms->addWidget(graph_params_label);
    show_ptslns->addWidget(show_pts);
    show_ptslns->addWidget(show_lns);
    selection_modes->addWidget(rect_zoom);
    selection_modes->addWidget(selection_of_point);
    exporting_on_rms->addLayout(show_ptslns);
    exporting_on_rms->addLayout(selection_modes);
    exporting_on_rms->addWidget(show_selected_spectrum);

    // - zaznaczamy checkbox I -
    I_on_rms->setChecked(true);
    show_pts->setChecked(true);
    rect_zoom->setChecked(true);
    selection_of_point->setChecked(true);
    // connectujemy
    QPushButton::connect(kill_rms_section, SIGNAL(clicked()), this, SLOT(close_rms_section_slot()));
    QObject::connect(I_on_rms, SIGNAL(clicked()), this, SLOT(I_on_rms_checkbox_checked_slot()));
    QObject::connect(V_on_rms, SIGNAL(clicked()), this, SLOT(V_on_rms_checkbox_checked_slot()));
    QObject::connect(LHC_on_rms, SIGNAL(clicked()), this, SLOT(LHC_on_rms_checkbox_checked_slot()));
    QObject::connect(RHC_on_rms, SIGNAL(clicked()), this, SLOT(RHC_on_rms_checkbox_checked_slot()));
    QObject::connect(show_pts, SIGNAL(clicked()), this, SLOT(show_points_or_lines()));
    QObject::connect(show_lns, SIGNAL(clicked()), this, SLOT(show_points_or_lines()));
    QObject::connect(rect_zoom, SIGNAL(clicked()), this, SLOT(set_unset_rect_zoom()));
    QObject::connect(selection_of_point, SIGNAL(clicked()), this, SLOT(selection_point_on_rms_slot_for_graph_visibility()));
    QPushButton::connect(export_rms_vs_tme, SIGNAL(clicked()), this, SLOT(exp_rms_vs_time()));
    QPushButton::connect(export_tint_vs_tme, SIGNAL(clicked()), this, SLOT(exp_sint_vs_time()));
    QPushButton::connect(recalculate_integration, SIGNAL(clicked()), this, SLOT(recalculate_integration_on_rms_slot()));
    QPushButton::connect(export_all_vs_tme, SIGNAL(clicked()), this, SLOT(exp_all()));
    QPushButton::connect(export_tsys_vs_tme, SIGNAL(clicked()), this, SLOT(exp_tsys_vs_time()));
    QPushButton::connect(show_selected_spectrum, SIGNAL(clicked()), this, SLOT(open_popup_window()));


    // cross - hairy
    QObject::connect(&rms_vs_time, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(cross_hair_rms_vs_time(QMouseEvent *)));
    QObject::connect(&tsys_vs_time, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(cross_hair_tsys_vs_time(QMouseEvent *)));
    QObject::connect(&int_vs_time, SIGNAL(mouseMove(QMouseEvent *)), this, SLOT(cross_hair_tint_vs_time(QMouseEvent *)));
    // selekcja z wykresow
    QObject::connect(&rms_vs_time, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(show_spectrum_on_select_rms(QMouseEvent * )));
    QObject::connect(&tsys_vs_time, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(show_spectrum_on_select_tsys(QMouseEvent * )));
    QObject::connect(&int_vs_time, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(show_spectrum_on_select_tint(QMouseEvent * )));

    grid_rms_section_widget->setColumnStretch(0,2);
    grid_rms_section_widget->setColumnStretch(1,2);
    grid_rms_section_widget->setColumnStretch(2,2);
    grid_rms_section_widget->setColumnStretch(3,2);
    //rms_section_widget.setLayout(grid_rms_section_widget);

    // -- connectujemy rescale --
    connect(rms_vs_time.xAxis, SIGNAL(rangeChanged(QCPRange)), rms_vs_time.xAxis2, SLOT(setRange(QCPRange)));
    connect(rms_vs_time.yAxis, SIGNAL(rangeChanged(QCPRange)), rms_vs_time.yAxis2, SLOT(setRange(QCPRange)));
    connect(tsys_vs_time.xAxis, SIGNAL(rangeChanged(QCPRange)), tsys_vs_time.xAxis2, SLOT(setRange(QCPRange)));
    connect(tsys_vs_time.yAxis, SIGNAL(rangeChanged(QCPRange)), tsys_vs_time.yAxis2, SLOT(setRange(QCPRange)));
    connect(int_vs_time.xAxis, SIGNAL(rangeChanged(QCPRange)), int_vs_time.xAxis2, SLOT(setRange(QCPRange)));
    connect(int_vs_time.yAxis, SIGNAL(rangeChanged(QCPRange)), int_vs_time.yAxis2, SLOT(setRange(QCPRange)));
    connect(spectrum_on_popup_window.xAxis, SIGNAL(rangeChanged(QCPRange)), spectrum_on_popup_window.xAxis2, SLOT(setRange(QCPRange)));
    connect(spectrum_on_popup_window.yAxis, SIGNAL(rangeChanged(QCPRange)), spectrum_on_popup_window.yAxis2, SLOT(setRange(QCPRange)));

}

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
        set_plot_on_rms_vs_time();
        set_plot_on_int_vs_time();
        set_plot_on_tsys_vs_time();
        show_points_or_lines();
        selection_point_on_rms_slot_for_graph_visibility();
        select_on_rms_section(dataTable->mjdTable[0]);
        return;
    }

    else if (gauss_section_opened == 1)
    {
        close_gauss_widget();
    }
    if(popup_window_opened==1)
    {
        close_popup_window_slot();
        popup_window_opened = 0;
    }

    // -- visibilities checkboxów --
    I_on_rms->setVisible(true);
    V_on_rms->setVisible(true);
    LHC_on_rms->setVisible(true);
    RHC_on_rms->setVisible(true);
    show_pts->setVisible(true);
    show_lns->setVisible(true);
    rect_zoom->setVisible(true);
    selection_of_point->setVisible(true);
    // dodajemy do grida widget sekcji
    grid->addWidget(rms_section_widget, 0, 1, 9, 5);

    // dodajemy zamykający button do głównego panelu
    left_hand_list->appendWidget(kill_rms_section);

    // ustalamy szerokość kolumn
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);

    rms_section_opened = 1;
    set_plot_on_rms_vs_time();
    set_plot_on_int_vs_time();
    set_plot_on_tsys_vs_time();
    show_points_or_lines();
    selection_point_on_rms_slot_for_graph_visibility();

    // -- ustalamy visibilities --
    rms_section_widget->setVisible(true);
    kill_rms_section->setVisible(true);

    // -- selectujemy na początek --
    select_on_rms_section(dataTable->mjdTable[xind]);
}

void body::close_rms_section_slot()
{
    // -- visibilities checkboxów --
    I_on_rms->setVisible(false);
    V_on_rms->setVisible(false);
    LHC_on_rms->setVisible(false);
    RHC_on_rms->setVisible(false);
    show_pts->setVisible(false);
    show_lns->setVisible(false);
    rect_zoom->setVisible(false);
    selection_of_point->setVisible(false);

    // ustalamy visibilities
    rms_section_widget->setVisible(false);
    kill_rms_section->setVisible(false);

    // odpinamy od grida
    grid->removeWidget(rms_section_widget);
    left_hand_list->deleteWidgetFromList(kill_rms_section);
    /*
    // ustalamy szerokość kolumn
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,1);
    grid->setColumnStretch(3,1);
    grid->setColumnStretch(4,1);
    grid->setColumnStretch(5,1);
    */
    // ustalamy wartość boola
    rms_section_opened = 0;
}

void body::set_plot_on_rms_vs_time()
{
    QPen graph_dark;
    graph_dark.setColor(QColor(135,206,250));
    graph_dark.setWidth(2);

    QPen graph_light;
    graph_light.setColor(QColor(0,0,255));
    graph_light.setWidth(2);

    rms_vs_time.setMouseTracking(true);
    rms_vs_time.clearGraphs();
    // wektor z danymi
    QVector < double > xI(dataTable->spectraTableI.size()), yI(dataTable->spectraTableI.size()), yV(dataTable->spectraTableI.size()), yLHC(dataTable->spectraTableI.size()), yRHC(dataTable->spectraTableI.size());

    // zapelniamy wektory
    for(unsigned int i = 0; i < dataTable->spectraTableI.size(); i++)
    {
        xI[i] = dataTable->mjdTable[i];
        yI[i] = dataTable->spectraTableIERR[i];
        yV[i] = dataTable->spectraTableVERR[i];
        yLHC[i] = dataTable->spectraTableLHCERR[i];
        yRHC[i] = dataTable->spectraTableRHCERR[i];
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
    if (left_hand_list->DarthMode->isChecked())
        rms_vs_time.graph(0)->setPen(graph_dark);
    else
        rms_vs_time.graph(0)->setPen(graph_light);
    rms_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
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
    if (left_hand_list->DarthMode->isChecked())
        rms_vs_time.graph(1)->setPen(QPen(Qt::white));
    else
        rms_vs_time.graph(1)->setPen(QPen(Qt::black));

    rms_vs_time.graph(1)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
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
    rms_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
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
    rms_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));

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
    /*
    //spectrum.xAxis->setRange(*min_element(x.begin(), x.end()), *max_element(x.begin(), x.end()));
    //spectrum.yAxis->setRange(*min_element(y.begin(), y.end()), *max_element(y.begin(), y.end()));
    double veldiff = *max_element(xI.begin(), xI.end()) - *min_element(xI.begin(), xI.end());
    rms_vs_time.xAxis->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    rms_vs_time.yAxis->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    rms_vs_time.xAxis2->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    rms_vs_time.yAxis2->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    */
    autorange_plot(&rms_vs_time);
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
    rms_vs_time.setCursor(QCursor(Qt::CrossCursor));
    rms_vs_time.replot();
    set_unset_rect_zoom();
    // graph do zaznaczania
    // I
    rms_vs_time.addGraph();
    rms_vs_time.graph(4)->setName("Selected");
    rms_vs_time.graph(4)->setPen(QPen(Qt::red));
    rms_vs_time.graph(4)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    rms_vs_time.graph(4)->setVisible(false);
    rms_vs_time.graph(4)->removeFromLegend();
    // V
    rms_vs_time.addGraph();
    rms_vs_time.graph(5)->setName("Selected");
    rms_vs_time.graph(5)->setPen(QPen(Qt::red));
    rms_vs_time.graph(5)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    rms_vs_time.graph(5)->setVisible(false);
    rms_vs_time.graph(5)->removeFromLegend();
    // LHC
    rms_vs_time.addGraph();
    rms_vs_time.graph(6)->setName("Selected");
    rms_vs_time.graph(6)->setPen(QPen(Qt::blue));
    rms_vs_time.graph(6)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    rms_vs_time.graph(6)->setVisible(false);
    rms_vs_time.graph(6)->removeFromLegend();
    // RHC
    rms_vs_time.addGraph();
    rms_vs_time.graph(7)->setName("Selected");
    rms_vs_time.graph(7)->setPen(QPen(Qt::red));
    rms_vs_time.graph(7)->setLineStyle(QCPGraph::lsNone);
    rms_vs_time.graph(7)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    rms_vs_time.graph(7)->setVisible(false);
    rms_vs_time.graph(7)->removeFromLegend();
}

void body::set_plot_on_tsys_vs_time()
{
    QPen graph_dark;
    graph_dark.setColor(QColor(135,206,250));
    graph_dark.setWidth(2);

    QPen graph_light;
    graph_light.setColor(QColor(0,0,255));
    graph_light.setWidth(2);

    tsys_vs_time.clearGraphs();
    // wektor z danymi
    QVector < double > xI(dataTable->spectraTableI.size()), yI(dataTable->spectraTableI.size());

    // zapelniamy wektory
    for(unsigned int i = 0; i < dataTable->spectraTableI.size(); i++)
    {
        xI[i] = dataTable->mjdTable[i];
        yI[i] = dataTable->tsysTable[i];
    }
    // -- graphy --
    // -- dodajemy grafike (I) --
    tsys_vs_time.addGraph();

    tsys_vs_time.graph(0)->setName("I");
    if (left_hand_list->DarthMode->isChecked())
        tsys_vs_time.graph(0)->setPen(graph_dark);
    else
        tsys_vs_time.graph(0)->setPen(graph_light);

    tsys_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
    tsys_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));

    // -- dodajemy do grafiki dane --
    tsys_vs_time.graph(0)->setData(xI,yI);

    // -- zarzadzamy labelami --
    tsys_vs_time.xAxis->setLabel("MJD");
    tsys_vs_time.yAxis->setLabel("Tsys (K)");

    // -- zarzadzamy rangeami --
    /*
    double veldiff = *max_element(xI.begin(), xI.end()) - *min_element(xI.begin(), xI.end());
    tsys_vs_time.xAxis->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    tsys_vs_time.yAxis->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    tsys_vs_time.xAxis2->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    tsys_vs_time.yAxis2->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    */
    autorange_plot(&tsys_vs_time);
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
    tsys_vs_time.setCursor(QCursor(Qt::CrossCursor));
    tsys_vs_time.replot();
    set_unset_rect_zoom();
    // graph do zaznaczania
    // I
    tsys_vs_time.addGraph();
    tsys_vs_time.graph(1)->setPen(QPen(Qt::red));
    tsys_vs_time.graph(1)->setLineStyle(QCPGraph::lsNone);
    tsys_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    tsys_vs_time.graph(1)->setVisible(false);
}

void body::set_plot_on_int_vs_time()
{
    QPen graph_dark;
    graph_dark.setColor(QColor(135,206,250));
    graph_dark.setWidth(2);

    QPen graph_light;
    graph_light.setColor(QColor(0,0,255));
    graph_light.setWidth(2);

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
    if (max > dataTable->spectraTableI[0].size()-1)
        max = dataTable->spectraTableI[0].size()-1;

    chan4int_start = min;
    chan4int_end = max;

    // -- integrujemy --
    integrated_fluxlst_I = dataTable->integratePol(min+1, max+1, dataTable->velocityTable, dataTable->spectraTableI);
    integrated_fluxlst_V = dataTable->integratePol(min+1, max+1, dataTable->velocityTable, dataTable->spectraTableV);
    integrated_fluxlst_LHC = dataTable->integratePol(min+1, max+1, dataTable->velocityTable, dataTable->spectraTableLHC);
    integrated_fluxlst_RHC = dataTable->integratePol(min+1, max+1, dataTable->velocityTable, dataTable->spectraTableRHC);

    integrated_fluxlst_I_er = dataTable->integratePolErr(dataTable->velocityTable, dataTable->spectraTableIERR);
    integrated_fluxlst_V_er = dataTable->integratePolErr(dataTable->velocityTable, dataTable->spectraTableVERR);
    integrated_fluxlst_LHC_er = dataTable->integratePolErr(dataTable->velocityTable, dataTable->spectraTableLHCERR);
    integrated_fluxlst_RHC_er = dataTable->integratePolErr(dataTable->velocityTable, dataTable->spectraTableRHCERR);

    // -- clearujemy grafiki --
    int_vs_time.clearGraphs();
    // -- wektory Q do wykresow --
    int nobs = integrated_fluxlst_I.size();
    QVector < double > xI(nobs), yI(nobs),yV(nobs),yLHC(nobs),yRHC(nobs),yI_er(nobs), yV_er(nobs), yLHC_er(nobs), yRHC_er(nobs);
    for(int i = 0; i < integrated_fluxlst_I.size(); i++)
    {
        xI[i] = dataTable->mjdTable[i];
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
    if (left_hand_list->DarthMode->isChecked())
        int_vs_time.graph(0)->setPen(graph_dark);
    else
        int_vs_time.graph(0)->setPen(graph_light);

    int_vs_time.graph(0)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
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
    if (left_hand_list->DarthMode->isChecked())
        int_vs_time.graph(1)->setPen(QPen(Qt::white));
    else
        int_vs_time.graph(1)->setPen(QPen(Qt::black));

    int_vs_time.graph(1)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
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
    int_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
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
    int_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));

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
    /*
    double veldiff = *max_element(xI.begin(), xI.end()) - *min_element(xI.begin(), xI.end());
    int_vs_time.xAxis->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    int_vs_time.yAxis->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    int_vs_time.xAxis2->setRange(*min_element(xI.begin(), xI.end()) - 0.05 * veldiff, *max_element(xI.begin(), xI.end())  + 0.05 * veldiff);
    int_vs_time.yAxis2->setRange(*min_element(yI.begin(), yI.end()) - 0.05 * (*max_element(yI.begin(), yI.end())), *max_element(yI.begin(), yI.end())  + 0.05 * (*max_element(yI.begin(), yI.end())));
    */
    autorange_plot(&int_vs_time);
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
    int_vs_time.setCursor(QCursor(Qt::CrossCursor));
    int_vs_time.replot();
    set_unset_rect_zoom();
    // I
    int_vs_time.addGraph();
    int_vs_time.graph(4)->setPen(QPen(Qt::red));
    int_vs_time.graph(4)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    int_vs_time.graph(4)->setVisible(false);
    // V
    int_vs_time.addGraph();
    int_vs_time.graph(5)->setName("Selected");
    int_vs_time.graph(5)->setPen(QPen(Qt::red));
    int_vs_time.graph(5)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(5)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    int_vs_time.graph(5)->setVisible(false);
    // LHC
    int_vs_time.addGraph();
    int_vs_time.graph(6)->setName("Selected");
    int_vs_time.graph(6)->setPen(QPen(Qt::blue));
    int_vs_time.graph(6)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    int_vs_time.graph(6)->setVisible(false);
    // RHC
    int_vs_time.addGraph();
    int_vs_time.graph(7)->setName("Selected");
    int_vs_time.graph(7)->setPen(QPen(Qt::red));
    int_vs_time.graph(7)->setLineStyle(QCPGraph::lsNone);
    int_vs_time.graph(7)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle , 10));
    int_vs_time.graph(7)->setVisible(false);
}

void body::I_on_rms_checkbox_checked_slot()
{
    if(I_on_rms->isChecked())
    {
        rms_vs_time.graph(0)->setVisible(true);
        int_vs_time.graph(0)->setVisible(true);
        if (selection_of_point->isChecked())
        {
            rms_vs_time.graph(4)->setVisible(true);
            int_vs_time.graph(4)->setVisible(true);
        }
        if(popup_window_opened == 1)
            spectrum_on_popup_window.graph(0)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(0)->setVisible(false);
        int_vs_time.graph(0)->setVisible(false);
        rms_vs_time.graph(4)->setVisible(false);
        int_vs_time.graph(4)->setVisible(false);
        if(popup_window_opened == 1)
            spectrum_on_popup_window.graph(0)->setVisible(false);
    }
    rms_vs_time.replot();
    int_vs_time.replot();
    if(popup_window_opened == 1)
        spectrum_on_popup_window.replot();

}

void body::V_on_rms_checkbox_checked_slot()
{
    if(V_on_rms->isChecked())
    {
        rms_vs_time.graph(1)->setVisible(true);
        int_vs_time.graph(1)->setVisible(true);
        if (selection_of_point->isChecked())
        {
            rms_vs_time.graph(5)->setVisible(true);
            int_vs_time.graph(5)->setVisible(true);
        }
        if(popup_window_opened == 1)
            spectrum_on_popup_window.graph(1)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(1)->setVisible(false);
        int_vs_time.graph(1)->setVisible(false);
        rms_vs_time.graph(5)->setVisible(false);
        int_vs_time.graph(5)->setVisible(false);
        if(popup_window_opened == 1)
            spectrum_on_popup_window.graph(1)->setVisible(false);
    }
    rms_vs_time.replot();
    int_vs_time.replot();
    if(popup_window_opened == 1)
        spectrum_on_popup_window.replot();
}

void body::LHC_on_rms_checkbox_checked_slot()
{
    if(LHC_on_rms->isChecked())
    {
        rms_vs_time.graph(2)->setVisible(true);
        int_vs_time.graph(2)->setVisible(true);
        if (selection_of_point->isChecked())
        {
            rms_vs_time.graph(6)->setVisible(true);
            int_vs_time.graph(6)->setVisible(true);
        }
        if(popup_window_opened == 1)
            spectrum_on_popup_window.graph(2)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(2)->setVisible(false);
        int_vs_time.graph(2)->setVisible(false);
        rms_vs_time.graph(6)->setVisible(false);
        int_vs_time.graph(6)->setVisible(false);
        if(popup_window_opened == 1)
            spectrum_on_popup_window.graph(2)->setVisible(false);
    }
    rms_vs_time.replot();
    int_vs_time.replot();
    if(popup_window_opened == 1)
        spectrum_on_popup_window.replot();
}

void body::RHC_on_rms_checkbox_checked_slot()
{
    if(RHC_on_rms->isChecked())
    {
        rms_vs_time.graph(3)->setVisible(true);
        int_vs_time.graph(3)->setVisible(true);
        if (selection_of_point->isChecked())
        {
            rms_vs_time.graph(7)->setVisible(true);
            int_vs_time.graph(7)->setVisible(true);
        }
        if(popup_window_opened == 1)
            spectrum_on_popup_window.graph(3)->setVisible(true);
    }
    else
    {
        rms_vs_time.graph(3)->setVisible(false);
        int_vs_time.graph(3)->setVisible(false);
        rms_vs_time.graph(7)->setVisible(false);
        int_vs_time.graph(7)->setVisible(false);
        if(popup_window_opened == 1)
            spectrum_on_popup_window.graph(3)->setVisible(false);
    }
    rms_vs_time.replot();
    int_vs_time.replot();
    if(popup_window_opened == 1)
        spectrum_on_popup_window.replot();
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
        rms_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        rms_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        rms_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        rms_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        // int vs time
        int_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        int_vs_time.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        int_vs_time.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        int_vs_time.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
        // tsys vs time
        tsys_vs_time.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
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

    if(left_hand_list->IsotimeInclude->isChecked())
    {
        // wpisujemy naglowek do pliku
        integ << "# time_in_isoformat MJD year I err V err LHC err RHC err" << endl;
        // petla zapisujaca
        for(int i = 0; i < dataTable->spectraTableI.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << pytime_format[i] << "   " << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "   " << integrated_fluxlst_I_er[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_V_er[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_LHC_er[i] << "   " << "   " << integrated_fluxlst_RHC[i] << "   " << integrated_fluxlst_RHC_er[i] << "   " << endl;
            //integ << fixed << setprecision(11) << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
        //cout << "Zaznaczono pytime" << endl;
    }
    else
    {
        // wpisujemy naglowek do pliku
        integ << "# MJD year I err V err LHC err RHC err" << endl;
        // petla zapisujaca
        for(int i = 0; i < dataTable->spectraTableI.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "   " << integrated_fluxlst_I_er[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_V_er[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_LHC_er[i] << "   " << "   " << integrated_fluxlst_RHC[i] << "   " << integrated_fluxlst_RHC_er[i] << "   " << endl;
            //integ << fixed << setprecision(11) << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
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

    if(left_hand_list->IsotimeInclude->isChecked())
    {
        // wpisujemy naglowek do pliku
        integ << "# time_in_isoformat MJD year RMS_I RMS_V RMS_LHC RMS_RHC" << endl;
        // petla zapisujaca
        for(int i = 0; i < dataTable->spectraTableI.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << pytime_format[i] << "   " << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << dataTable->spectraTableIERR[i] << "   " << dataTable->spectraTableVERR[i] << "  " << dataTable->spectraTableLHCERR[i] << "   " << dataTable->spectraTableRHCERR[i] << endl;
            //integ << fixed << setprecision(11) << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
        //cout << "Zaznaczono pytime" << endl;
    }
    else
    {
        // wpisujemy naglowek do pliku
        integ << "# MJD year RMS_I RMS_V RMS_LHC RMS_RHC" << endl;
        // petla zapisujaca
        for(int i = 0; i < dataTable->spectraTableI.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << dataTable->spectraTableIERR[i] << "   " << dataTable->spectraTableVERR[i] << "  " << dataTable->spectraTableLHCERR[i] << "   " << dataTable->spectraTableRHCERR[i] << endl;
            //integ << fixed << setprecision(11) << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
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

    if(left_hand_list->IsotimeInclude->isChecked())
    {
        // wpisujemy naglowek do pliku
        integ << "# time_in_isoformat MJD year Tsys (K)" << endl;
        // petla zapisujaca
        for(int i = 0; i < dataTable->spectraTableI.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << pytime_format[i] << "   " << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << dataTable->tsysTable[i] << endl;
            //integ << fixed << setprecision(11) << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
        //cout << "Zaznaczono pytime" << endl;
    }
    else
    {
        // wpisujemy naglowek do pliku
        integ << "# MJD year Tsys (K)" << endl;
        // petla zapisujaca
        for(int i = 0; i < dataTable->spectraTableI.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << "   " << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << dataTable->tsysTable[i] << endl;
            //integ << fixed << setprecision(11) << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << integrated_fluxlst_I[i] << "  " <<  integrated_fluxlst_V[i] << "   " << integrated_fluxlst_LHC[i] << "   " << integrated_fluxlst_RHC[i] << endl;
        }
    }
    integ.close();
    string message = "";
    message = "Saved Tsys vs time to " + filename;
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));

}

void body::cross_hair_rms_vs_time(QMouseEvent * event)
{
    // visibilities
    tsys_x_axis_line->setVisible(false);
    tsys_y_axis_line->setVisible(false);
    tint_x_axis_line->setVisible(false);
    tint_y_axis_line->setVisible(false);
    rms_x_axis_line->setVisible(true);
    rms_y_axis_line->setVisible(true);
    rms_csh_label->setVisible(true);
    tint_csh_label->setVisible(false);
    tsys_csh_label->setVisible(false);
    double x,y;
    x = rms_vs_time.xAxis->pixelToCoord(event -> pos().x());
    y = rms_vs_time.yAxis->pixelToCoord(event -> pos().y());
    //cout << x << "   " << y << endl;
    QPen pen;
    if (left_hand_list->DarthMode->isChecked())
        pen.setColor(Qt::white);
    else
        pen.setColor(Qt::black);

    pen.setStyle(Qt::DashLine);
    //rms_x_axis_line->set
    rms_x_axis_line->setPen(pen);
    rms_y_axis_line->setPen(pen);
    rms_x_axis_line->start->setCoords(x, -QCPRange::maxRange);
    rms_x_axis_line->end->setCoords(x, QCPRange::maxRange);
    rms_y_axis_line->start->setCoords(-QCPRange::maxRange,y);
    rms_y_axis_line->end->setCoords(QCPRange::maxRange,y);

    // label
    rms_csh_label->position->setCoords(x,y);
    //rms_csh_label->position->setCoords(x,y);
    rms_csh_label->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    string tekst;
    tekst = "    X: " + to_string(x) + "\n" + "Y: " + to_string(y) + "\n\n";
    rms_csh_label->setText(tekst.c_str());
    if (left_hand_list->DarthMode->isChecked())
    {
        rms_csh_label->setColor(Qt::white);
    }
    else
    {
        rms_csh_label->setColor(Qt::black);
    }
    //cout << x << "   " << y << endl;
    int_vs_time.replot();
    rms_vs_time.replot();
    tsys_vs_time.replot();
}

void body::cross_hair_tsys_vs_time(QMouseEvent * event)
{
    // visibilities
    tsys_x_axis_line->setVisible(true);
    tsys_y_axis_line->setVisible(true);
    tint_x_axis_line->setVisible(false);
    tint_y_axis_line->setVisible(false);
    rms_x_axis_line->setVisible(false);
    rms_y_axis_line->setVisible(false);
    rms_csh_label->setVisible(false);
    tint_csh_label->setVisible(false);
    tsys_csh_label->setVisible(true);

    double x,y;
    x = tsys_vs_time.xAxis->pixelToCoord(event -> pos().x());
    y = tsys_vs_time.yAxis->pixelToCoord(event -> pos().y());
    //cout << x << "   " << y << endl;
    QPen pen;
    if (left_hand_list->DarthMode->isChecked())
        pen.setColor(Qt::white);
    else
        pen.setColor(Qt::black);

    pen.setStyle(Qt::DashLine);
    //rms_x_axis_line->set
    tsys_x_axis_line->setPen(pen);
    tsys_y_axis_line->setPen(pen);
    tsys_x_axis_line->start->setCoords(x, -QCPRange::maxRange);
    tsys_x_axis_line->end->setCoords(x, QCPRange::maxRange);
    tsys_y_axis_line->start->setCoords(-QCPRange::maxRange,y);
    tsys_y_axis_line->end->setCoords(QCPRange::maxRange,y);
    //cout << x << "   " << y << endl;

    // label
    tsys_csh_label->position->setCoords(x,y);
    //rms_csh_label->position->setCoords(x,y);
    tsys_csh_label->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    string tekst;
    tekst = "    X: " + to_string(x) + "\n" + "Y: " + to_string(y) + "\n\n";
    tsys_csh_label->setText(tekst.c_str());
    if (left_hand_list->DarthMode->isChecked())
    {
        tsys_csh_label->setColor(Qt::white);
    }
    else
    {
        tsys_csh_label->setColor(Qt::black);
    }
    int_vs_time.replot();
    rms_vs_time.replot();
    tsys_vs_time.replot();
}

void body::cross_hair_tint_vs_time(QMouseEvent * event)
{
    // visibilities
    tsys_x_axis_line->setVisible(false);
    tsys_y_axis_line->setVisible(false);
    tint_x_axis_line->setVisible(true);
    tint_y_axis_line->setVisible(true);
    rms_x_axis_line->setVisible(false);
    rms_y_axis_line->setVisible(false);
    rms_csh_label->setVisible(false);
    tint_csh_label->setVisible(true);
    tsys_csh_label->setVisible(false);

    double x,y;
    x = int_vs_time.xAxis->pixelToCoord(event -> pos().x());
    y = int_vs_time.yAxis->pixelToCoord(event -> pos().y());
    //cout << x << "   " << y << endl;
    QPen pen;
    if (left_hand_list->DarthMode->isChecked())
        pen.setColor(Qt::white);
    else
        pen.setColor(Qt::black);

    pen.setStyle(Qt::DashLine);
    //rms_x_axis_line->set
    tint_x_axis_line->setPen(pen);
    tint_y_axis_line->setPen(pen);
    tint_x_axis_line->start->setCoords(x, -QCPRange::maxRange);
    tint_x_axis_line->end->setCoords(x, QCPRange::maxRange);
    tint_y_axis_line->start->setCoords(-QCPRange::maxRange,y);
    tint_y_axis_line->end->setCoords(QCPRange::maxRange,y);
    //cout << x << "   " << y << endl;

    // label
    tint_csh_label->position->setCoords(x,y);
    //rms_csh_label->position->setCoords(x,y);
    tint_csh_label->setPositionAlignment(Qt::AlignTop|Qt::AlignLeft);
    string tekst;
    tekst = "    X: " + to_string(x) + "\n" + "Y: " + to_string(y) + "\n\n";
    tint_csh_label->setText(tekst.c_str());

    if (left_hand_list->DarthMode->isChecked())
    {
        tint_csh_label->setColor(Qt::white);
    }
    else
    {
        tint_csh_label->setColor(Qt::black);
    }

    int_vs_time.replot();
    rms_vs_time.replot();
    tsys_vs_time.replot();

}

void body::set_unset_rect_zoom()
{
    if(rect_zoom->isChecked())
    {
        rms_vs_time.setInteractions(QCP::iRangeZoom);
        int_vs_time.setInteractions(QCP::iRangeZoom);
        tsys_vs_time.setInteractions(QCP::iRangeZoom);
        rms_vs_time.setSelectionRectMode(QCP::srmZoom);
        int_vs_time.setSelectionRectMode(QCP::srmZoom);
        tsys_vs_time.setSelectionRectMode(QCP::srmZoom);
        rms_vs_time.setCursor(QCursor(Qt::CrossCursor));
        int_vs_time.setCursor(QCursor(Qt::CrossCursor));
        tsys_vs_time.setCursor(QCursor(Qt::CrossCursor));
    }
    else
    {
        rms_vs_time.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        int_vs_time.setInteractions(QCP::iRangeDrag |QCP::iRangeZoom);
        tsys_vs_time.setInteractions(QCP::iRangeDrag |QCP::iRangeZoom);
        rms_vs_time.setSelectionRectMode(QCP::srmNone);
        int_vs_time.setSelectionRectMode(QCP::srmNone);
        tsys_vs_time.setSelectionRectMode(QCP::srmNone);
        rms_vs_time.setCursor(QCursor(Qt::ArrowCursor));
        int_vs_time.setCursor(QCursor(Qt::ArrowCursor));
        tsys_vs_time.setCursor(QCursor(Qt::ArrowCursor));
    }
}

void body::show_spectrum_on_select_rms(QMouseEvent * event)
{
    if(!selection_of_point->isChecked())
    {
        return;
    }

    double x,y;
    x = rms_vs_time.xAxis->pixelToCoord(event -> pos().x());
    y = rms_vs_time.yAxis->pixelToCoord(event -> pos().y());
    //cout << "clicked " << x << "  " << y << " on rms" << endl;
    //int_vs_time.graph(0)->setData(xI,yI);
    //QVector < double > Xp(1), Yp(1);
    //Xp[0] = x;
    //Yp[0] = y;
    //rms_vs_time.graph(4)->setData(Xp,Yp);
    //rms_vs_time.graph(4)->setVisible(true);
    //rms_vs_time.replot();
    select_on_rms_section(x);
}

void body::show_spectrum_on_select_tint(QMouseEvent * event)
{
    if(!selection_of_point->isChecked())
    {
        return;
    }
    double x,y;
    x = int_vs_time.xAxis->pixelToCoord(event -> pos().x());
    y = int_vs_time.yAxis->pixelToCoord(event -> pos().y());
    //cout << "clicked " << x << "  " << y << " on tint" << endl;
    /*
    QVector < double > Xp(1), Yp(1);
    Xp[0] = x;
    Yp[0] = y;
    int_vs_time.graph(4)->setData(Xp,Yp);
    */
    select_on_rms_section(x);

}

void body::show_spectrum_on_select_tsys(QMouseEvent * event)
{
    if(!selection_of_point->isChecked())
    {
        return;
    }
    double x,y;
    x = tsys_vs_time.xAxis->pixelToCoord(event -> pos().x());
    y = tsys_vs_time.yAxis->pixelToCoord(event -> pos().y());
    //cout << "clicked " << x << "  " << y << " on tsys" << endl;
    //int_vs_time.graph(0)->setData(xI,yI);
    //QVector < double > Xp(1), Yp(1);
    //Xp[0] = x;
    //Yp[0] = y;
    //tsys_vs_time.graph(1)->setData(Xp,Yp);
    //tsys_vs_time.replot();
    select_on_rms_section(x);
}

void body::selection_point_on_rms_slot_for_graph_visibility()
{
    if(!selection_of_point->isChecked())
    {
        tsys_vs_time.graph(1)->setVisible(false);
        int_vs_time.graph(4)->setVisible(false);
        rms_vs_time.graph(4)->setVisible(false);
        int_vs_time.graph(5)->setVisible(false);
        rms_vs_time.graph(5)->setVisible(false);
        int_vs_time.graph(6)->setVisible(false);
        rms_vs_time.graph(6)->setVisible(false);
        int_vs_time.graph(7)->setVisible(false);
        rms_vs_time.graph(7)->setVisible(false);
    }
    else
    {
        tsys_vs_time.graph(1)->setVisible(true);
        if(I_on_rms->isChecked())
        {
            int_vs_time.graph(4)->setVisible(true);
            rms_vs_time.graph(4)->setVisible(true);
        }
        if(V_on_rms->isChecked())
        {
            int_vs_time.graph(5)->setVisible(true);
            rms_vs_time.graph(5)->setVisible(true);
        }
        if(LHC_on_rms->isChecked())
        {
            int_vs_time.graph(6)->setVisible(true);
            rms_vs_time.graph(6)->setVisible(true);
        }
        if(RHC_on_rms->isChecked())
        {
            int_vs_time.graph(7)->setVisible(true);
            rms_vs_time.graph(7)->setVisible(true);
        }
    }
    tsys_vs_time.replot();
    rms_vs_time.replot();
    int_vs_time.replot();
}

void body::select_on_rms_section(double x)
{
    for(int i=0; i < dataTable->mjdTable.size(); i++)
    {

        if (i > 0)
        {
            if (dataTable->mjdTable[i] >= x)
            {
                if (abs(dataTable->mjdTable[i] - x) > abs(dataTable->mjdTable[i-1] - x))
                    xind = i-1;
                else
                    xind = i;
                break;
            }
        }
    }
    if(x <= dataTable->mjdTable[0])
    {
        xind = 0;
    }
    else if (x > dataTable->mjdTable[dataTable->mjdTable.size()-1])
    {
        xind = dataTable->mjdTable.size()-1;
    }

    // dodajemy markery zaznaczenia:
    // int_vs_time
    QVector < double > Xp(1), Yp(1), YpV(1), YpLHC(1), YpRHC(1);
    Xp[0] = dataTable->mjdTable[xind];
    Yp[0] = integrated_fluxlst_I[xind];
    YpV[0] = integrated_fluxlst_V[xind];
    YpLHC[0] = integrated_fluxlst_LHC[xind];
    YpRHC[0] = integrated_fluxlst_RHC[xind];
    int_vs_time.graph(4)->setData(Xp,Yp);
    int_vs_time.graph(5)->setData(Xp,YpV);
    int_vs_time.graph(6)->setData(Xp,YpLHC);
    int_vs_time.graph(7)->setData(Xp,YpRHC);
    int_vs_time.replot();
    //tsys_vs_time
    QVector < double > Ytsys(1), Xtsys(1);
    Xtsys[0] = dataTable->mjdTable[xind];
    Ytsys[0] = dataTable->tsysTable[xind];
    tsys_vs_time.graph(1)->setData(Xtsys,Ytsys);
    tsys_vs_time.replot();
    //rms_vs_time
    QVector < double > Xrms_sl(1), Yrms_sl(1), Yrms_slV(1), Yrms_slLHC(1), Yrms_slRHC(1);
    Xrms_sl[0] = dataTable->mjdTable[xind];
    Yrms_sl[0] = dataTable->spectraTableIERR[xind];
    Yrms_slV[0] = dataTable->spectraTableVERR[xind];
    Yrms_slLHC[0] = dataTable->spectraTableLHCERR[xind];
    Yrms_slRHC[0] = dataTable->spectraTableRHCERR[xind];
    rms_vs_time.graph(4)->setData(Xrms_sl,Yrms_sl);
    rms_vs_time.graph(5)->setData(Xrms_sl,Yrms_slV);
    rms_vs_time.graph(6)->setData(Xrms_sl,Yrms_slLHC);
    rms_vs_time.graph(7)->setData(Xrms_sl,Yrms_slRHC);
    rms_vs_time.replot();
}

void body::open_popup_window()
{
    // pomocnicze prezydenty
    QPen graph_dark;
    graph_dark.setColor(QColor(135,206,250));
    graph_dark.setWidth(2);

    QPen graph_light;
    graph_light.setColor(QColor(0,0,255));
    graph_light.setWidth(2);
 // grid 6x6
 // wykres zajmuje 5 w y i 4 w x
 // w 6 w y znajdziemy przyciski
 // w 4 i 5 w x znajdziemy szczegółowe informacje
 if(popup_window_opened==0)
 {
     // -- rozmiary przyciskow --
     close_popup_window->setMaximumSize(10000,10000);
     flag_on_popup_window->setMaximumSize(10000,10000);
     grid_of_popup_window->addWidget(&spectrum_on_popup_window, 0,0,5,5);
     grid_of_popup_window->addWidget(close_popup_window, 5,0,1,2);
     grid_of_popup_window->addWidget(flag_on_popup_window, 5,2,1,3);
     grid_of_popup_window->addWidget(label_on_popup_window, 0,5,6,1);
     //popup_window->setLayout(&grid_of_popup_window);
     popup_window->setGeometry(window.x(), window.y(),900,500);


     // -- rozmiary grida --
     grid_of_popup_window->setColumnStretch(0,1);
     grid_of_popup_window->setColumnStretch(1,1);
     grid_of_popup_window->setColumnStretch(2,1);
     grid_of_popup_window->setColumnStretch(3,1);
     grid_of_popup_window->setColumnStretch(4,1);
     grid_of_popup_window->setColumnStretch(5,1);
     grid_of_popup_window->setRowStretch(0,3);
     grid_of_popup_window->setRowStretch(1,3);
     grid_of_popup_window->setRowStretch(2,3);
     grid_of_popup_window->setRowStretch(3,3);
     grid_of_popup_window->setRowStretch(4,3);
     grid_of_popup_window->setRowStretch(5,1);
 }


 // -- teksty na przyciskach --
 close_popup_window->setText("Close");
 flag_on_popup_window->setText("Flag");

 // -- wykres --
 spectrum_on_popup_window.clearGraphs();
 QVector < double > I_pop(dataTable->spectraTableI[xind].size()), V_pop(dataTable->spectraTableI[xind].size()), LHC_pop((dataTable->spectraTableI[xind].size())), RHC_pop(dataTable->spectraTableI[xind].size()), VEL_pop(dataTable->spectraTableI[xind].size());
 for (int i = 0; i < (int) dataTable->spectraTableI[xind].size(); i++)
 {
     I_pop[i] = dataTable->spectraTableI[xind][i];
     V_pop[i] = dataTable->spectraTableV[xind][i];
     LHC_pop[i] = dataTable->spectraTableLHC[xind][i];
     RHC_pop[i] = dataTable->spectraTableRHC[xind][i];
     VEL_pop[i] = dataTable->velocityTable[xind][i];
 }
 // -- dodajemy grafike (I) --
 spectrum_on_popup_window.addGraph();
 if(I_on_rms->isChecked())
 {
     spectrum_on_popup_window.graph(0)->setVisible(true);
 }
 else
 {
     spectrum_on_popup_window.graph(0)->setVisible(false);
 }
 spectrum_on_popup_window.graph(0)->setName("I");

 if(left_hand_list->DarthMode->isChecked())
     spectrum_on_popup_window.graph(0)->setPen(graph_dark);
 else
     spectrum_on_popup_window.graph(0)->setPen(graph_light);

 //spectrum_on_popup_window.graph(0)->setLineStyle(QCPGraph::lsNone);
 //spectrum_on_popup_window.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
 // -- dodajemy grafike (V) --
 spectrum_on_popup_window.addGraph();
 if(V_on_rms->isChecked())
 {
     spectrum_on_popup_window.graph(1)->setVisible(true);
 }
 else
 {
     spectrum_on_popup_window.graph(1)->setVisible(false);
 }
 spectrum_on_popup_window.graph(1)->setName("V");
 if (left_hand_list->DarthMode->isChecked())
     spectrum_on_popup_window.graph(1)->setPen(QPen(Qt::white));
 else
     spectrum_on_popup_window.graph(1)->setPen(QPen(Qt::black));
 //spectrum_on_popup_window.graph(1)->setLineStyle(QCPGraph::lsNone);
 //spectrum_on_popup_window.graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
 // -- dodajemy grafike (V) --
 spectrum_on_popup_window.addGraph();
 if(LHC_on_rms->isChecked())
 {
     spectrum_on_popup_window.graph(2)->setVisible(true);
 }
 else
 {
     spectrum_on_popup_window.graph(2)->setVisible(false);
 }
 spectrum_on_popup_window.graph(2)->setName("LHC");
 spectrum_on_popup_window.graph(2)->setPen(QPen(Qt::red));
 //spectrum_on_popup_window.graph(2)->setLineStyle(QCPGraph::lsNone);
 //spectrum_on_popup_window.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
 // -- dodajemy grafike (V) --
 spectrum_on_popup_window.addGraph();
 if(RHC_on_rms->isChecked())
 {
     spectrum_on_popup_window.graph(3)->setVisible(true);
 }
 else
 {
     spectrum_on_popup_window.graph(3)->setVisible(false);
 }
 spectrum_on_popup_window.graph(3)->setName("RHC");
 spectrum_on_popup_window.graph(3)->setPen(QPen(Qt::green));
 //spectrum_on_popup_window.graph(3)->setLineStyle(QCPGraph::lsNone);
 //spectrum_on_popup_window.graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));

 // -- legenda --
 spectrum_on_popup_window.legend->setVisible(true);
 QFont f( "Arial", 10, QFont::Bold);
 spectrum_on_popup_window.legend->setFont(f);

 // -- dodajemy do grafiki dane --
 spectrum_on_popup_window.graph(0)->setData(VEL_pop,I_pop);
 spectrum_on_popup_window.graph(1)->setData(VEL_pop,V_pop);
 spectrum_on_popup_window.graph(2)->setData(VEL_pop,LHC_pop);
 spectrum_on_popup_window.graph(3)->setData(VEL_pop,RHC_pop);

 // -- zarzadzamy labelami --
 spectrum_on_popup_window.xAxis->setLabel("Velocity");
 spectrum_on_popup_window.yAxis->setLabel("Flux density");
 // -- zarzadzamy rangeami --
 //spectrum.xAxis->setRange(*min_element(x.begin(), x.end()), *max_element(x.begin(), x.end()));
 //spectrum.yAxis->setRange(*min_element(y.begin(), y.end()), *max_element(y.begin(), y.end()));
 double veldiff = *max_element(VEL_pop.begin(), VEL_pop.end()) - *min_element(VEL_pop.begin(), VEL_pop.end());
 spectrum_on_popup_window.xAxis->setRange(*min_element(VEL_pop.begin(), VEL_pop.end()) - 0.05 * veldiff, *max_element(VEL_pop.begin(), VEL_pop.end())  + 0.05 * veldiff);
 spectrum_on_popup_window.yAxis->setRange(*min_element(I_pop.begin(), I_pop.end()) - 0.05 * (*max_element(I_pop.begin(), I_pop.end())), *max_element(I_pop.begin(), I_pop.end())  + 0.05 * (*max_element(I_pop.begin(), I_pop.end())));
 // -- pokazujemy ticki na gornej osi --
 spectrum_on_popup_window.xAxis2->setVisible(true);
 spectrum_on_popup_window.yAxis2->setVisible(true);
 spectrum_on_popup_window.xAxis2->setTickLabels(false);
 spectrum_on_popup_window.yAxis2->setTickLabels(false);
 // -- dodajemy interakcje --
 spectrum_on_popup_window.setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);
 spectrum_on_popup_window.axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
 spectrum_on_popup_window.axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
 spectrum_on_popup_window.axisRect()->setRangeZoomAxes(spectrum_on_popup_window.xAxis, spectrum_on_popup_window.yAxis);
 spectrum_on_popup_window.setSelectionRectMode(QCP::srmZoom);
 spectrum_on_popup_window.setCursor(QCursor(Qt::CrossCursor));
 spectrum_on_popup_window.replot();

 // connectujemy
 QPushButton::connect(close_popup_window, SIGNAL(clicked()), this, SLOT(close_popup_window_slot()));
 QPushButton::connect(flag_on_popup_window, SIGNAL(clicked()), this, SLOT(flag_slot()));

 set_label_on_popup_window();


 popup_window_opened = 1;
 popup_window->setVisible(true);
 spectrum_on_popup_window.setVisible(true);
 close_popup_window->setVisible(true);
 flag_on_popup_window->setVisible(true);
 label_on_popup_window->setVisible(true);
}

void body::close_popup_window_slot()
{
    //visibilities
    spectrum_on_popup_window.setVisible(false);
    close_popup_window->setVisible(false);
    flag_on_popup_window->setVisible(false);
    label_on_popup_window->setVisible(false);
    popup_window->setVisible(false);
    // odpinamy od grida
    grid_of_popup_window->removeWidget(&spectrum_on_popup_window);
    grid_of_popup_window->removeWidget(close_popup_window);
    grid_of_popup_window->removeWidget(flag_on_popup_window);
    grid_of_popup_window->removeWidget(label_on_popup_window);
    // disconnectujemy
    QPushButton::disconnect(close_popup_window, SIGNAL(clicked()), this, SLOT(close_popup_window_slot()));
    QPushButton::disconnect(flag_on_popup_window, SIGNAL(clicked()), this, SLOT(flag_slot()));
    // bool
    popup_window_opened = 0;
}

void body::set_label_on_popup_window()
{
    string label_to_popup_window;
    label_to_popup_window = "Filename: " + dataTable->fileNamesTab[xind] + "\n";
    label_to_popup_window += "MJD: " + to_string(dataTable->mjdTable[xind]) + "\n";

    string yearstr, monthstr, daystr;

    // zapisujemy czas w isoformacie (YYYY-MM-DD)
    //year
    yearstr = to_string((int)ylst[xind]);
    // month
    if (to_string((int)mlst[xind]).length() == 1)
        monthstr = string("0")+to_string((int)mlst[xind]);
    else
        monthstr = to_string((int)mlst[xind]);
    // day
    if (to_string((int)dlst[xind]).length() == 1)
        daystr = string("0") + to_string((int)dlst[xind]);
    else
        daystr = to_string((int)dlst[xind]);

    label_to_popup_window += "Date (YYYY MM DD): " + yearstr + " " + monthstr + " " + daystr + "\n\n";

    label_to_popup_window += "Tsys: " + to_string(dataTable->tsysTable[xind]) +"\n\n";
    label_to_popup_window += "RMS (I): " + to_string(dataTable->spectraTableIERR[xind]) +"\n";
    label_to_popup_window += "RMS (V): " + to_string(dataTable->spectraTableVERR[xind]) +"\n";
    label_to_popup_window += "RMS (LHC): " + to_string(dataTable->spectraTableLHCERR[xind]) +"\n";
    label_to_popup_window += "RMS (RHC): " + to_string(dataTable->spectraTableRHCERR[xind]) +"\n\n";

    label_to_popup_window += "Sint (I): " + to_string(integrated_fluxlst_I[xind]) +"\n";
    label_to_popup_window += "Sint (V): " + to_string(integrated_fluxlst_V[xind]) +"\n";
    label_to_popup_window += "Sint (LHC): " + to_string(integrated_fluxlst_LHC[xind]) +"\n";
    label_to_popup_window += "Sint (RHC): " + to_string(integrated_fluxlst_RHC[xind]) +"\n";

    label_on_popup_window->setText(QString::fromStdString(label_to_popup_window));
}

void body::autorange_plot(QCustomPlot * plot)
{
    plot->rescaleAxes();
    double max_x, min_x, max_y, min_y;
    max_x = plot->xAxis->range().upper;
    min_x = plot->xAxis->range().lower;
    max_y = plot->yAxis->range().upper;
    min_y = plot->yAxis->range().lower;
    double diffrence_x = max_x - min_x;
    double diffrence_y = max_y - min_y;
    plot->xAxis->setRange(min_x - (0.05 * diffrence_x), max_x + (0.05 * diffrence_x));
    plot->yAxis->setRange(min_y - (0.05 * diffrence_y), max_y + (0.05 * diffrence_y));
    plot->replot();
}

void body::set_dark_mode()
{
    dynspecWidget->darthMode(!dark_mode_enabled);
    ssWidget->darthMode(!dark_mode_enabled);
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

        // -- rms_vs_time --
        // - tło -
        rms_vs_time.setBackground(Qt::black);
        rms_vs_time.axisRect()->setBackground(Qt::black);
        // - kwadracik -
        rms_vs_time.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        rms_vs_time.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        rms_vs_time.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        rms_vs_time.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        rms_vs_time.xAxis->setTickLabelColor(Qt::white);
        rms_vs_time.xAxis2->setTickLabelColor(Qt::white);
        rms_vs_time.yAxis->setTickLabelColor(Qt::white);
        rms_vs_time.yAxis2->setTickLabelColor(Qt::white);
        // subtick
        rms_vs_time.xAxis->setSubTickPen(duda);
        rms_vs_time.xAxis2->setSubTickPen(duda);
        rms_vs_time.yAxis->setSubTickPen(duda);
        rms_vs_time.yAxis2->setSubTickPen(duda);
        // tick
        rms_vs_time.xAxis->setTickPen(duda);
        rms_vs_time.xAxis2->setTickPen(duda);
        rms_vs_time.yAxis->setTickPen(duda);
        rms_vs_time.yAxis2->setTickPen(duda);
        // label
        rms_vs_time.xAxis->setLabelColor(Qt::white);
        rms_vs_time.xAxis2->setLabelColor(Qt::white);
        rms_vs_time.yAxis->setLabelColor(Qt::white);
        rms_vs_time.yAxis2->setLabelColor(Qt::white);

        // -- tsys_vs_time --
        // - tło -
        tsys_vs_time.setBackground(Qt::black);
        tsys_vs_time.axisRect()->setBackground(Qt::black);
        // - kwadracik -
        tsys_vs_time.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        tsys_vs_time.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        tsys_vs_time.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        tsys_vs_time.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        tsys_vs_time.xAxis->setTickLabelColor(Qt::white);
        tsys_vs_time.xAxis2->setTickLabelColor(Qt::white);
        tsys_vs_time.yAxis->setTickLabelColor(Qt::white);
        tsys_vs_time.yAxis2->setTickLabelColor(Qt::white);
        // subtick
        tsys_vs_time.xAxis->setSubTickPen(duda);
        tsys_vs_time.xAxis2->setSubTickPen(duda);
        tsys_vs_time.yAxis->setSubTickPen(duda);
        tsys_vs_time.yAxis2->setSubTickPen(duda);
        // tick
        tsys_vs_time.xAxis->setTickPen(duda);
        tsys_vs_time.xAxis2->setTickPen(duda);
        tsys_vs_time.yAxis->setTickPen(duda);
        tsys_vs_time.yAxis2->setTickPen(duda);
        // label
        tsys_vs_time.xAxis->setLabelColor(Qt::white);
        tsys_vs_time.xAxis2->setLabelColor(Qt::white);
        tsys_vs_time.yAxis->setLabelColor(Qt::white);
        tsys_vs_time.yAxis2->setLabelColor(Qt::white);

        // -- int_vs_time --
        // - tło -
        int_vs_time.setBackground(Qt::black);
        int_vs_time.axisRect()->setBackground(Qt::black);
        // - kwadracik -
        int_vs_time.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        int_vs_time.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        int_vs_time.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        int_vs_time.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        int_vs_time.xAxis->setTickLabelColor(Qt::white);
        int_vs_time.xAxis2->setTickLabelColor(Qt::white);
        int_vs_time.yAxis->setTickLabelColor(Qt::white);
        int_vs_time.yAxis2->setTickLabelColor(Qt::white);
        // subtick
        int_vs_time.xAxis->setSubTickPen(duda);
        int_vs_time.xAxis2->setSubTickPen(duda);
        int_vs_time.yAxis->setSubTickPen(duda);
        int_vs_time.yAxis2->setSubTickPen(duda);
        // tick
        int_vs_time.xAxis->setTickPen(duda);
        int_vs_time.xAxis2->setTickPen(duda);
        int_vs_time.yAxis->setTickPen(duda);
        int_vs_time.yAxis2->setTickPen(duda);
        // label
        int_vs_time.xAxis->setLabelColor(Qt::white);
        int_vs_time.xAxis2->setLabelColor(Qt::white);
        int_vs_time.yAxis->setLabelColor(Qt::white);
        int_vs_time.yAxis2->setLabelColor(Qt::white);

        // -- int_vs_time --
        // - tło -
        spectrum_on_popup_window.setBackground(Qt::black);
        spectrum_on_popup_window.axisRect()->setBackground(Qt::black);
        // - kwadracik -
        spectrum_on_popup_window.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        spectrum_on_popup_window.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        spectrum_on_popup_window.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        spectrum_on_popup_window.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        spectrum_on_popup_window.xAxis->setTickLabelColor(Qt::white);
        spectrum_on_popup_window.xAxis2->setTickLabelColor(Qt::white);
        spectrum_on_popup_window.yAxis->setTickLabelColor(Qt::white);
        spectrum_on_popup_window.yAxis2->setTickLabelColor(Qt::white);
        // subtick
        spectrum_on_popup_window.xAxis->setSubTickPen(duda);
        spectrum_on_popup_window.xAxis2->setSubTickPen(duda);
        spectrum_on_popup_window.yAxis->setSubTickPen(duda);
        spectrum_on_popup_window.yAxis2->setSubTickPen(duda);
        // tick
        spectrum_on_popup_window.xAxis->setTickPen(duda);
        spectrum_on_popup_window.xAxis2->setTickPen(duda);
        spectrum_on_popup_window.yAxis->setTickPen(duda);
        spectrum_on_popup_window.yAxis2->setTickPen(duda);
        // label
        spectrum_on_popup_window.xAxis->setLabelColor(Qt::white);
        spectrum_on_popup_window.xAxis2->setLabelColor(Qt::white);
        spectrum_on_popup_window.yAxis->setLabelColor(Qt::white);
        spectrum_on_popup_window.yAxis2->setLabelColor(Qt::white);

        // -- sekcja gauss --
        //spectrum_w_gauss->xaxis->

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


        // -- jeśli otwarta jest sekcja rms --
        if (rms_section_opened == 1)
        {
            rms_vs_time.graph(0)->setPen(graph_dark);
            rms_vs_time.graph(1)->setPen(QPen(Qt::white));

            int_vs_time.graph(0)->setPen(graph_dark);
            int_vs_time.graph(1)->setPen(QPen(Qt::white));

            tsys_vs_time.graph(0)->setPen(graph_dark);
        }

        // -- jeśli otwarte jest popup window --
        if (popup_window_opened == 1)
        {
            spectrum_on_popup_window.graph(0)->setPen(graph_dark);
            spectrum_on_popup_window.graph(1)->setPen(QPen(Qt::white));
        }


        // -- replotujemy --
        rms_vs_time.replot();
        tsys_vs_time.replot();
        int_vs_time.replot();
        spectrum_on_popup_window.replot();
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

        // -- rms_vs_time --
        // - tło -
        rms_vs_time.setBackground(Qt::white);
        rms_vs_time.axisRect()->setBackground(Qt::white);
        // - kwadracik -
        rms_vs_time.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        rms_vs_time.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        rms_vs_time.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        rms_vs_time.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        rms_vs_time.xAxis->setTickLabelColor(Qt::black);
        rms_vs_time.xAxis2->setTickLabelColor(Qt::black);
        rms_vs_time.yAxis->setTickLabelColor(Qt::black);
        rms_vs_time.yAxis2->setTickLabelColor(Qt::black);
        // subtick
        rms_vs_time.xAxis->setSubTickPen(duda);
        rms_vs_time.xAxis2->setSubTickPen(duda);
        rms_vs_time.yAxis->setSubTickPen(duda);
        rms_vs_time.yAxis2->setSubTickPen(duda);
        // tick
        rms_vs_time.xAxis->setTickPen(duda);
        rms_vs_time.xAxis2->setTickPen(duda);
        rms_vs_time.yAxis->setTickPen(duda);
        rms_vs_time.yAxis2->setTickPen(duda);
        // label
        rms_vs_time.xAxis->setLabelColor(Qt::black);
        rms_vs_time.xAxis2->setLabelColor(Qt::black);
        rms_vs_time.yAxis->setLabelColor(Qt::black);
        rms_vs_time.yAxis2->setLabelColor(Qt::black);

        // -- tsys_vs_time --
        // - tło -
        tsys_vs_time.setBackground(Qt::white);
        tsys_vs_time.axisRect()->setBackground(Qt::white);
        // - kwadracik -
        tsys_vs_time.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        tsys_vs_time.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        tsys_vs_time.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        tsys_vs_time.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        tsys_vs_time.xAxis->setTickLabelColor(Qt::black);
        tsys_vs_time.xAxis2->setTickLabelColor(Qt::black);
        tsys_vs_time.yAxis->setTickLabelColor(Qt::black);
        tsys_vs_time.yAxis2->setTickLabelColor(Qt::black);
        // subtick
        tsys_vs_time.xAxis->setSubTickPen(duda);
        tsys_vs_time.xAxis2->setSubTickPen(duda);
        tsys_vs_time.yAxis->setSubTickPen(duda);
        tsys_vs_time.yAxis2->setSubTickPen(duda);
        // tick
        tsys_vs_time.xAxis->setTickPen(duda);
        tsys_vs_time.xAxis2->setTickPen(duda);
        tsys_vs_time.yAxis->setTickPen(duda);
        tsys_vs_time.yAxis2->setTickPen(duda);
        // label
        tsys_vs_time.xAxis->setLabelColor(Qt::black);
        tsys_vs_time.xAxis2->setLabelColor(Qt::black);
        tsys_vs_time.yAxis->setLabelColor(Qt::black);
        tsys_vs_time.yAxis2->setLabelColor(Qt::black);

        // -- int_vs_time --
        // - tło -
        int_vs_time.setBackground(Qt::white);
        int_vs_time.axisRect()->setBackground(Qt::white);
        // - kwadracik -
        int_vs_time.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        int_vs_time.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        int_vs_time.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        int_vs_time.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        int_vs_time.xAxis->setTickLabelColor(Qt::black);
        int_vs_time.xAxis2->setTickLabelColor(Qt::black);
        int_vs_time.yAxis->setTickLabelColor(Qt::black);
        int_vs_time.yAxis2->setTickLabelColor(Qt::black);
        // subtick
        int_vs_time.xAxis->setSubTickPen(duda);
        int_vs_time.xAxis2->setSubTickPen(duda);
        int_vs_time.yAxis->setSubTickPen(duda);
        int_vs_time.yAxis2->setSubTickPen(duda);
        // tick
        int_vs_time.xAxis->setTickPen(duda);
        int_vs_time.xAxis2->setTickPen(duda);
        int_vs_time.yAxis->setTickPen(duda);
        int_vs_time.yAxis2->setTickPen(duda);
        // label
        int_vs_time.xAxis->setLabelColor(Qt::black);
        int_vs_time.xAxis2->setLabelColor(Qt::black);
        int_vs_time.yAxis->setLabelColor(Qt::black);
        int_vs_time.yAxis2->setLabelColor(Qt::black);

        // -- int_vs_time --
        // - tło -
        spectrum_on_popup_window.setBackground(Qt::white);
        spectrum_on_popup_window.axisRect()->setBackground(Qt::white);
        // - kwadracik -
        spectrum_on_popup_window.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        spectrum_on_popup_window.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        spectrum_on_popup_window.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        spectrum_on_popup_window.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        spectrum_on_popup_window.xAxis->setTickLabelColor(Qt::black);
        spectrum_on_popup_window.xAxis2->setTickLabelColor(Qt::black);
        spectrum_on_popup_window.yAxis->setTickLabelColor(Qt::black);
        spectrum_on_popup_window.yAxis2->setTickLabelColor(Qt::black);
        // subtick
        spectrum_on_popup_window.xAxis->setSubTickPen(duda);
        spectrum_on_popup_window.xAxis2->setSubTickPen(duda);
        spectrum_on_popup_window.yAxis->setSubTickPen(duda);
        spectrum_on_popup_window.yAxis2->setSubTickPen(duda);
        // tick
        spectrum_on_popup_window.xAxis->setTickPen(duda);
        spectrum_on_popup_window.xAxis2->setTickPen(duda);
        spectrum_on_popup_window.yAxis->setTickPen(duda);
        spectrum_on_popup_window.yAxis2->setTickPen(duda);
        // label
        spectrum_on_popup_window.xAxis->setLabelColor(Qt::black);
        spectrum_on_popup_window.xAxis2->setLabelColor(Qt::black);
        spectrum_on_popup_window.yAxis->setLabelColor(Qt::black);
        spectrum_on_popup_window.yAxis2->setLabelColor(Qt::black);

        // -- sekcja gauss --

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


        if (rms_section_opened == 1)
        {
            rms_vs_time.graph(0)->setPen(graph_light);
            rms_vs_time.graph(1)->setPen(QPen(Qt::black));

            int_vs_time.graph(0)->setPen(graph_light);
            int_vs_time.graph(1)->setPen(QPen(Qt::black));

            tsys_vs_time.graph(0)->setPen(graph_light);
        }
        // -- jeśli otwarte jest popup window --
        if (popup_window_opened == 1)
        {
            spectrum_on_popup_window.graph(0)->setPen(graph_light);
            spectrum_on_popup_window.graph(1)->setPen(QPen(Qt::black));
        }


        // -- replotujemy --
        rms_vs_time.replot();
        tsys_vs_time.replot();
        int_vs_time.replot();
        spectrum_on_popup_window.replot();
        spectrum_w_gauss->replot();

        //qApp->setStyleSheet("theme: Light");
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
