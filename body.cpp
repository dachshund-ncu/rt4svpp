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

    srand(QDateTime::currentDateTime().toTime_t());
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
    set_log_scale->setVisible(false);

    // -- sizepolicy --
    load_data->setMaximumSize(10000,10000);
    dynamic_spectrum->setMaximumSize(10000,10000);
    kill_dynspec->setMaximumSize(10000,10000);
    kill_singspec->setMaximumSize(10000,10000);
    integrate_button->setMaximumSize(10000,10000);
    quit->setMaximumSize(10000,10000);
    aver_over_velocity->setMaximumSize(10000,10000);
    aver_over_time->setMaximumSize(10000,10000);
    spectral_index->setMaximumSize(10000,10000);
    y_down_border->setMaximumSize(10000,30);
    y_up_border->setMaximumSize(10000,30);
    x_left_border->setMaximumSize(10000,30);
    x_right_border->setMaximumSize(10000,30);
    Ibut->setMaximumSize(10000,30);
    Vbut->setMaximumSize(10000,30);
    LHCbut->setMaximumSize(10000,30);
    RHCbut->setMaximumSize(10000,30);
    single_spectrum->setMaximumSize(10000,10000);
    spectral_index->setMaximumSize(10000,10000);
    list_of_observations->setMaximumSize(10000,10000);
    save_plots_on_single_spectrum->setMaximumSize(10000,10000);
    display_plot_on_single_spectrum->setMaximumSize(10000,10000);
    set_default_range_button->setMaximumSize(10000,10000);
    erase_last_graph->setMaximumSize(10000,10000);
    flag->setMaximumSize(10000,10000);
    rotate->setMaximumSize(10000,10000);
    make_lcs_button->setMaximumSize(10000,10000);
    reload->setMaximumSize(10000,10000);
    rotate_minus->setMaximumSize(10000,10000);
    save_rotation->setMaximumSize(10000,10000);
    number_of_rotated_channels_texted->setMaximumSize(60,30);
    calibrate->setMaximumSize(10000,10000);
    load_caltab_l1->setMaximumSize(10000,10000);
    load_caltab_r1->setMaximumSize(10000,10000);
    start_calibration->setMaximumSize(10000,10000);
    caltab_l1_path->setMaximumSize(10000,10000);
    caltab_r1_path->setMaximumSize(10000,10000);
    WD->setMaximumSize(10000,10000);
    open_rms_section->setMaximumSize(10000,10000);
    kill_rms_section->setMaximumSize(10000,10000);
    recalculate_integration->setMaximumSize(10000,10000);
    save_all_spectra_to_gnuplot->setMaximumSize(10000,10000);
    open_gauss->setMaximumSize(10000,10000);
    kill_gauss->setMaximumSize(10000,10000);
    recreate_I_button->setMaximumSize(10000,10000);


    load_data->setMinimumSize(0,0);
    dynamic_spectrum->setMinimumSize(0,0);
    kill_dynspec->setMinimumSize(0,0);
    integrate_button->setMinimumSize(0,0);
    quit->setMinimumSize(0,0);
    aver_over_velocity->setMinimumSize(0,0);
    aver_over_time->setMinimumSize(0,0);
    spectral_index->setMinimumSize(0,0);
    y_down_border->setMinimumSize(0,0);
    y_up_border->setMinimumSize(0,0);
    x_left_border->setMinimumSize(0,0);
    x_right_border->setMinimumSize(0,0);
    Ibut->setMinimumSize(0,0);
    Vbut->setMinimumSize(0,0);
    LHCbut->setMinimumSize(0,0);
    RHCbut->setMinimumSize(0,0);
    single_spectrum->setMinimumSize(0,0);
    spectral_index->setMinimumSize(0,0);
    kill_singspec->setMinimumSize(0,0);
    save_plots_on_single_spectrum->setMinimumSize(0,0);
    display_plot_on_single_spectrum->setMinimumSize(0,0);
    set_default_range_button->setMinimumSize(0,0);
    erase_last_graph->setMinimumSize(0,0);
    flag->setMinimumSize(0,0);
    rotate->setMinimumSize(0,0);
    make_lcs_button->setMinimumSize(0,0);
    reload->setMinimumSize(0,0);
    rotate_minus->setMinimumSize(0,0);
    save_rotation->setMinimumSize(0,0);
    number_of_rotated_channels_texted->setMinimumSize(0,0);
    calibrate->setMinimumSize(0,0);
    load_caltab_l1->setMinimumSize(0,0);
    load_caltab_r1->setMinimumSize(0,0);
    start_calibration->setMinimumSize(0,0);
    WD->setMinimumSize(0,0);
    open_rms_section->setMinimumSize(0,0);
    kill_rms_section->setMinimumSize(0,0);
    recalculate_integration->setMinimumSize(0,0);
    save_all_spectra_to_gnuplot->setMinimumSize(0,0);
    open_gauss->setMinimumSize(0,0);
    kill_gauss->setMinimumSize(0,0);
    recreate_I_button->setMinimumSize(0,0);

    // - font (do labelow) -
    QFont f( "Arial", 10, QFont::Bold);

    // -- ustalamy teksty naszych labelow --
    load_data_section_label->setText("Loading");
    load_data_section_label->setFont(f);
    wiev_data_section_label->setText("Visualisation");
    wiev_data_section_label->setFont(f);
    export_data_section_label->setText("Export & analysis");
    export_data_section_label->setFont(f);
    others_section_label->setText("Others");
    others_section_label->setFont(f);

    //loaders.setTitle("loaders");
    //loaders.setVisible(true);
    //loaders_layout.addWidget(&reload);
    //loaders_layout.addWidget(&load_data);
    //loaders_layout.addStretch(1);
    //loaders.setLayout(&loaders_layout);
    // -- dodajemy do głównego paska przycisków --
    //vbox_main.addWidget(butters);

    vbox_main.addWidget(load_data_section_label);
    //vbox_main.addWidget(&loaders);
    vbox_main.addWidget(reload);
    vbox_main.addWidget(load_data);

    vbox_main.addWidget(wiev_data_section_label);
    vbox_main.addWidget(dark_mode_switch);
    vbox_main.addWidget(dynamic_spectrum);
    vbox_main.addWidget(single_spectrum);
    vbox_main.addWidget(open_rms_section);
    vbox_main.addWidget(open_gauss);

    vbox_main.addWidget(export_data_section_label);
    vbox_main.addWidget(include_pytime);
    vbox_main.addWidget(integrate_button);
    vbox_main.addWidget(aver_over_velocity);
    vbox_main.addWidget(aver_over_time);
    vbox_main.addWidget(spectral_index);
    vbox_main.addWidget(WD);

    vbox_main.addWidget(others_section_label);
    vbox_main.addWidget(calibrate);
    vbox_main.addWidget(quit);

    grid->addLayout(&vbox_main, 0,0,9,1);
    grid->setColumnStretch(0,1);


    // -- dodajemy napis do przycisku --
    dynamic_spectrum->setText("Dynamic spectrum");
    single_spectrum->setText("Single spectrum");
    load_data->setText("Load AVR files");
    integrate_button->setText("Integrate");
    quit->setText("Quit");
    aver_over_time->setText("Aver over time");
    aver_over_velocity->setText("Aver over velocity");
    spectral_index->setText("Spectral index");
    make_lcs_button->setText("Make lc");
    rotate->setText("Rotate +");
    rotate_minus->setText("Rotate -");
    save_rotation->setText("Save");
    flag->setText("Flag");
    reload->setText("Reload");
    calibrate->setText("Calibrate");
    load_caltab_l1->setText("Load LHC caltab");
    load_caltab_r1->setText("Load RHC caltab");
    start_calibration->setText("START");
    WD->setText("Export file for dynamic spectrum");
    open_rms_section->setText("RMS, Tsys, Sint vs time");
    open_gauss->setText("Gaus fitting");

    // -- ustalamy ikony --
    //quit.setIcon(QIcon(":/images/exit.png"));
    // -- dodajemy layout do okna --


    // -- connectujemy przycisk do slotu --
    //QObject::connect(&quit, SIGNAL(clicked()), qApp, SLOT(quit()), Qt::QueuedConnection); // wylaczanie &QApplication::closeAllWindows
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()), Qt::QueuedConnection);
    QObject::connect(load_data, SIGNAL(clicked()), this, SLOT(load_time_series()));
    //QObject::connect(&integrate_button, SIGNAL(clicked()), this, SLOT(integrate_time_series()));
    QObject::connect(integrate_button, SIGNAL(clicked()), this, SLOT(calculate_integrate_for_time_series_with_buttons()));
    QObject::connect(single_spectrum, SIGNAL(clicked()), this, SLOT(display_single_spectrum()));
    QObject::connect(dynamic_spectrum, SIGNAL(clicked()), this, SLOT(display_dynamic_spectrum()));
    //QObject::connect(&aver_over_velocity, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity()));
    QObject::connect(aver_over_velocity, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity_for_time_series_with_buttons()));
    QObject::connect(aver_over_time, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time_for_time_series_with_buttons()));
    //QObject::connect(&aver_over_time, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time()));
    //QObject::connect(&spectral_index, SIGNAL(clicked()), this, SLOT(calculate_spectral_index()));
    QObject::connect(spectral_index, SIGNAL(clicked()), this, SLOT(calculate_spectral_index_for_time_series_with_buttons()));
    QObject::connect(reload, SIGNAL(clicked()), this, SLOT(reload_slot()));
    QObject::connect(calibrate, SIGNAL(clicked()), this, SLOT(open_cal_layout()));
    QObject::connect(WD, SIGNAL(clicked()), this, SLOT(open_dynspectum_layout()));
    QObject::connect(open_rms_section, SIGNAL(clicked()), this, SLOT(open_rms_section_slot()));
    QObject::connect(dark_mode_switch, SIGNAL(clicked()), this, SLOT(set_dark_mode()));
    QObject::connect(open_gauss, SIGNAL(clicked()), this, SLOT(open_gauss_widget()));
    QObject::connect(kill_gauss, SIGNAL(clicked()), this, SLOT(close_gauss_widget()));

    // -- setujemy widgety roznych sekcji --
    set_single_spectrum_widget();
    set_dynamic_spectrum_widget();
    set_rms_section_widget();
    set_gauss_widget();
    set_integrate_widget();
    set_aver_over_vel_widget();
    set_aver_over_time_widget();
    set_spectral_index_widget();
    set_wd_widget();
    set_calibrate_widget();

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
    dark_mode_switch->setChecked(1);
    set_dark_mode();

    // -- pokazujemy okno --
    window.show();

}

// -------------------------------------------------------------------------------
// -- funkcje, ustawiajace widgety (wywolywane na poczatku programu i tylko wtedy)
void body::set_dynamic_spectrum_widget()
{
    //dynamic_spectrum_widget.setParent(&window);
    dynamic_spectrum_widget->setVisible(false);
    kill_dynspec->setVisible(false);

    // layery
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

    // polaryzacje
    lhc_pressed = 0;
    rhc_pressed = 0;
    I_pressed = 1;
    v_pressed = 0;


    // -- ustawiamy nudne rzeczy w plotach --
    //dynamic_spectrum_pl.setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    dynamic_spectrum_pl.axisRect()->setupFullAxesBox(false);
    dynamic_spectrum_pl.xAxis->setLabel("Observation number");
    dynamic_spectrum_pl.yAxis->setLabel("Vel");
    colorMap->setInterpolate(false);
    colorMap->setTightBoundary(true);

    // -- connectujemy rozmaite sloty --
    y_down_border_shrt->setKey(QKeySequence("d"));
    y_up_border_shrt->setKey(QKeySequence("g"));
    x_down_border_shrt->setKey(QKeySequence("l"));
    x_up_border_shrt->setKey(QKeySequence("p"));
    reset_dynamic_spectrum->setKey(QKeySequence("b"));
    kill_dynspec->setText("Kill dynamic spectrum --->");
    QObject::connect(kill_dynspec, SIGNAL(clicked()), this, SLOT(kill_dynamic_spectrum()));
    QObject::connect(&dynamic_spectrum_pl, SIGNAL(mousePress(QMouseEvent *)), this, SLOT(press_map(QMouseEvent *)));
    QObject::connect(y_up_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_y_up()));
    QObject::connect(y_down_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_y_down()));
    QObject::connect(y_up_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_y_up()));
    QObject::connect(y_down_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_y_down()));
    QObject::connect(x_up_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_x_right()));
    QObject::connect(x_down_border_shrt, SIGNAL(activated()), this, SLOT(set_max_range_on_dynamic_specrum_x_left()));
    QObject::connect(x_right_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_x_right()));
    QObject::connect(x_left_border, SIGNAL(clicked()), this, SLOT(set_max_range_on_dynamic_specrum_x_left()));
    QObject::connect(Ibut, SIGNAL(clicked()), this, SLOT(set_I_on_dynamic_spectrum()));
    QObject::connect(LHCbut, SIGNAL(clicked()), this, SLOT(set_LHC_on_dynamic_spectrum()));
    QObject::connect(RHCbut, SIGNAL(clicked()), this, SLOT(set_RHC_on_dynamic_spectrum()));
    QObject::connect(Vbut, SIGNAL(clicked()), this, SLOT(set_V_on_dynamic_spectrum()));
    QObject::connect(make_lcs_button, SIGNAL(clicked()), this, SLOT(make_lcs_slot()));
    QObject::connect(flag, SIGNAL(clicked()), this, SLOT(flag_slot()));
    QObject::connect(rotate, SIGNAL(clicked()), this, SLOT(rotate_slot_plus()));
    QObject::connect(rotate_minus, SIGNAL(clicked()), this, SLOT(rotate_slot_minus()));
    QObject::connect(save_rotation, SIGNAL(clicked()), this, SLOT(save_rotated_spectras()));
    QObject::connect(reset_dynamic_spectrum, SIGNAL(activated()), this, SLOT(display_dynamic_spectrum()));
    QObject::connect(set_log_scale, SIGNAL(clicked()), this, SLOT(calculate_log()));
    QObject::connect(recreate_I_button, SIGNAL(clicked()), this, SLOT(make_new_I_and_V_for_epoch_on_dynspec()));
    // -- umieszczamy je wszystkie w widgecie --
    grid_dynamic_spectrum_widget->addWidget(&dynamic_spectrum_pl, 1,0,7,6);
    grid_dynamic_spectrum_widget->addWidget(&single_dynamic_spectrum, 0,6,4,4);
    grid_dynamic_spectrum_widget->addWidget(&lcs_dynamic_spectrum, 4,6,4,4);

    hbox->addWidget(Ibut);
    hbox->addWidget(Vbut);
    hbox->addWidget(LHCbut);
    hbox->addWidget(RHCbut);
    hbox->addWidget(y_down_border);
    hbox->addWidget(y_up_border);
    hbox->addWidget(x_left_border);
    hbox->addWidget(x_right_border);
    operations->addWidget(number_of_rotated_channels_texted);
    operations->addWidget(recreate_I_button);
    operations->addWidget(flag);
    operations->addWidget(rotate);
    operations->addWidget(save_rotation);
    operations->addWidget(rotate_minus);
    operations->addWidget(make_lcs_button);
    //operations->addWidget(set_log_scale);
    //operations->addWidget(rotate_all_pols);
    checkboxes_dynspec->addWidget(set_log_scale);
    checkboxes_dynspec->addWidget(rotate_all_pols);
    operations->addItem(checkboxes_dynspec);
    hbox->setSpacing(1);
    operations->setSpacing(1);
    on_dyn_spec_buttons->addLayout(operations);
    on_dyn_spec_buttons->addLayout(hbox);



    grid_dynamic_spectrum_widget->addLayout(on_dyn_spec_buttons,8,0,1,6);
    grid_dynamic_spectrum_widget->addWidget(&mjd_label, 8,6);
    grid_dynamic_spectrum_widget->addWidget(&cocochanel, 8,8);
    // -- teksty na przyciskach --
    y_down_border->setText("Down");
    y_up_border->setText("Up");
    x_left_border->setText("|->");
    x_right_border->setText("<-|");
    Ibut->setText("I");
    Vbut->setText("V");
    LHCbut->setText("LHC");
    RHCbut->setText("RHC");
    kill_dynspec->setText("Kill dynamic spectrum --->");
    recreate_I_button->setText("Recal");

    grid_dynamic_spectrum_widget->setColumnStretch(0,1);
    grid_dynamic_spectrum_widget->setColumnStretch(1,1);
    grid_dynamic_spectrum_widget->setColumnStretch(2,1);
    grid_dynamic_spectrum_widget->setColumnStretch(3,1);
    grid_dynamic_spectrum_widget->setColumnStretch(4,1);
    grid_dynamic_spectrum_widget->setColumnStretch(5,1);
    grid_dynamic_spectrum_widget->setColumnStretch(6,1);
    grid_dynamic_spectrum_widget->setColumnStretch(7,1);
    grid_dynamic_spectrum_widget->setColumnStretch(8,1);
    grid_dynamic_spectrum_widget->setColumnStretch(9,1);

    // -- connectujemy range wykresów --
    connect(single_dynamic_spectrum.xAxis, SIGNAL(rangeChanged(QCPRange)), single_dynamic_spectrum.xAxis2, SLOT(setRange(QCPRange)));
    connect(single_dynamic_spectrum.yAxis, SIGNAL(rangeChanged(QCPRange)), single_dynamic_spectrum.yAxis2, SLOT(setRange(QCPRange)));
    connect(lcs_dynamic_spectrum.xAxis, SIGNAL(rangeChanged(QCPRange)), lcs_dynamic_spectrum.xAxis2, SLOT(setRange(QCPRange)));
    connect(lcs_dynamic_spectrum.yAxis, SIGNAL(rangeChanged(QCPRange)), lcs_dynamic_spectrum.yAxis2, SLOT(setRange(QCPRange)));

    //dynamic_spectrum_widget.setLayout(grid_dynamic_spectrum_widget);


    // -- colorbar --
    // -- widget do colorbaru --

    colorbar_widget->clearPlottables();
    //colorbar_widget->removeItem(1);
    colorbar_widget->plotLayout()->clear();
    colorbar_widget->plotLayout()->addElement(0,0,colorbar);
    colorbar->setType(QCPAxis::atTop);
    grid_dynamic_spectrum_widget->addWidget(colorbar_widget, 0, 0, 1, 6);
    //dynamic_spectrum_pl.plotLayout()->addElement(0, 1, colorbar);
    //colorbar->setType(QCPAxis::atRight);
    colorMap->setColorScale(colorbar);
    colorbar->setDataRange(colorMap->dataRange());
    //colorbar->axis()->setLabel("Magnetic Field Strength");
    // - wyrównujemy dynspec i colorbar -
    QCPMarginGroup * grupa_marginesowa = new QCPMarginGroup(&dynamic_spectrum_pl);
    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, grupa_marginesowa);
    colorbar->setMarginGroup(QCP::msLeft|QCP::msRight, grupa_marginesowa);
    colorbar_widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    //colorbar->setMinimumSize(0.0,0.0);
    //colorbar->setMaximumSize(999999,999999);

    /*
    QMargins margines;
    margines.setLeft(0);
    margines.setTop(0);
    margines.setBottom(0);
    margines.setRight(0);
    colorbar_widget->setMargins(margines);
    */
    // -- setujemy max size dla colorbaru --
    colorbar_widget->setMaximumSize(9999999,70);
    colorbar->setMinimumMargins(QMargins(6, 0, 6, 0));

    colorbar_widget->resize(1,1);

    //connect(colorMap, SIGNAL(datarangeChanged(QCPRange)), colorbar, SLOT(setDataRange(QCPRange)));
    //connect(colorMap, SIGNAL(datarangeChanged(QCPRange)), colorbar, SLOT(replot()));
    connect(colorbar, SIGNAL(dataRangeChanged(QCPRange)), colorMap, SLOT(setDataRange(QCPRange)));
    connect(colorbar, SIGNAL(dataRangeChanged(QCPRange)), &dynamic_spectrum_pl, SLOT(replot()));
    connect(colorbar, SIGNAL(dataRangeChanged(QCPRange)), this, SLOT(set_down_IVLHCRHCbuttons()));
    //connect(this, SIGNAL(size_changed(const QSize)), colorbar_widget, SLOT(resize(1,1)));
    //connect(colorMap, SIGNAL(dataRangeChanged(QCPRange)), colorbar, SLOT(setDataRange(QCPRange)));
    //connect(colorbar->axis(), SIGNAL(rangeChanged(QCPRange)), &dynamic_spectrum_pl, SLOT(replot()));
    //connect(colorbar->axis(), SIGNAL(datarangeChanged(QCPRange)), this, SLOT(range_data_zmienion_na_cb()));

    rotate_all_pols->setChecked(true);

}

void body::set_single_spectrum_widget()
{
    //single_spectrum_widget.setParent(&window);
    single_spectrum_widget->setVisible(false);
    kill_singspec->setVisible(false);
    // -- tworzymy przycisk - do ubijania ramki --
    kill_singspec->setText("Kill single spectrum --->");
    save_plots_on_single_spectrum->setText("Save plots from single spectrum");
    display_plot_on_single_spectrum->setText("Display plot on single spectrum");
    set_default_range_button->setText("Set default range");
    erase_last_graph->setText("Erase last graph");
    save_all_spectra_to_gnuplot->setText("Save all spectra for gnuplot");

    // -- connectujemy z metodami
    //QObject::connect(list_of_observations, SIGNAL(activated()), this, SLOT(combo_box_display()));
    QObject::connect(kill_singspec, SIGNAL(clicked()), this, SLOT(kill_single_spectrum()));
    QObject::connect(display_plot_on_single_spectrum, SIGNAL(clicked()), this, SLOT(combo_box_display()));
    QObject::connect(set_default_range_button, SIGNAL(clicked()), this, SLOT(set_default_range()));
    QObject::connect(erase_last_graph, SIGNAL(clicked()), this, SLOT(remove_selected_graph()));
    QObject::connect(save_plots_on_single_spectrum, SIGNAL(clicked()), this, SLOT(save_plots_from_single_spectrum()));
    QObject::connect(save_all_spectra_to_gnuplot, SIGNAL(clicked()), this, SLOT(save_all_to_gnuplot_slot()));

    // -- dodajemy do grida --
    grid_single_spectrum_widget->addWidget(&spectrum, 0,0,9,4);
    grid_single_spectrum_widget->addWidget(list_of_observations, 0,4,1,1);
    grid_single_spectrum_widget->addWidget(save_plots_on_single_spectrum, 1,4,1,1);
    grid_single_spectrum_widget->addWidget(display_plot_on_single_spectrum, 2,4,1,1);
    grid_single_spectrum_widget->addWidget(set_default_range_button, 3,4,1,1);
    grid_single_spectrum_widget->addWidget(erase_last_graph, 4,4,1,1);
    grid_single_spectrum_widget->addWidget(save_all_spectra_to_gnuplot, 5,4,1,1);

    grid_single_spectrum_widget->setColumnStretch(0,2);
    grid_single_spectrum_widget->setColumnStretch(1,2);
    grid_single_spectrum_widget->setColumnStretch(2,2);
    grid_single_spectrum_widget->setColumnStretch(3,2);


    connect(spectrum.xAxis, SIGNAL(rangeChanged(QCPRange)), spectrum.xAxis2, SLOT(setRange(QCPRange)));
    connect(spectrum.yAxis, SIGNAL(rangeChanged(QCPRange)), spectrum.yAxis2, SLOT(setRange(QCPRange)));
    // -- setujemy layout --
    //single_spectrum_widget.setLayout(grid_single_spectrum_widget);

}

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

void body::set_integrate_widget()
{
    // - size policy -
    integrate_widget->setMaximumSize(100000,150);

    // - przy starcie nie chcemy go widziec -
    integrate_widget->setVisible(false);
    // - rozmiaty text editow -
    starting_channel_int->setMaximumSize(100,30);
    ending_channel_int->setMaximumSize(100,30);

    starting_channel_int->setMinimumSize(0,0);
    ending_channel_int->setMinimumSize(0,0);

    // - rozmiaty przyciskow -
    cancel_int->setMinimumSize(0,0);
    make_int2->setMinimumSize(0,0);

    // - teksty na przyciskach i labelach -
    start_label_int->setText("Start Channel");
    end_label_int->setText("End Channel");
    make_int2->setText("Integrate");
    cancel_int->setText("Cancel");

    // - dodajemy do layoutow -
    // start
    start_integration_channels->addWidget(start_label_int,Qt::AlignHCenter);
    start_integration_channels->addWidget(starting_channel_int,Qt::AlignHCenter);
    // end
    end_integration_channels->addWidget(end_label_int,Qt::AlignHCenter);
    end_integration_channels->addWidget(ending_channel_int,Qt::AlignHCenter);
    // przyciski
    integration_buttons->addWidget(cancel_int,Qt::AlignHCenter);
    integration_buttons->addWidget(make_int2,Qt::AlignHCenter);
    // do integrate
    integration_layout->addLayout(start_integration_channels,Qt::AlignHCenter);
    integration_layout->addLayout(end_integration_channels,Qt::AlignHCenter);
    integration_layout->addLayout(integration_buttons,Qt::AlignHCenter);
    // - connectujemy buttony -
    QPushButton::connect(cancel_int, SIGNAL(clicked()), this, SLOT(close_window_for_integrate()));
    QPushButton::connect(make_int2, SIGNAL(clicked()), this, SLOT(integrate_time_series()));
}

void body::set_aver_over_vel_widget()
{
    // - size policy -
    aver_over_vel_widget->setMaximumSize(100000,150);

    // - przy starcie nie chcemy go widziec -
    aver_over_vel_widget->setVisible(false);

    // - rozmiaty text editow -
    starting_channel_aov->setMaximumSize(100,30);
    ending_channel_aov->setMaximumSize(100,30);

    starting_channel_aov->setMinimumSize(0,0);
    ending_channel_aov->setMinimumSize(0,0);

    // - rozmiaty przyciskow -
    cancel_aver_over_vel->setMinimumSize(0,0);
    make_aver_over_vel->setMinimumSize(0,0);

    // - teksty na przyciskach i labelach -
    start_label_aov->setText("Start Channel");
    end_label_aov->setText("End Channel");
    make_aver_over_vel->setText("Aver over vel.");
    cancel_aver_over_vel->setText("Cancel");

    // - dodajemy do layoutow -
    // start
    start_aver_over_vel_channels->addWidget(start_label_aov,Qt::AlignHCenter);
    start_aver_over_vel_channels->addWidget(starting_channel_aov,Qt::AlignHCenter);
    // end
    end_aver_over_vel_channels->addWidget(end_label_aov,Qt::AlignHCenter);
    end_aver_over_vel_channels->addWidget(ending_channel_aov,Qt::AlignHCenter);
    // przyciski
    aver_over_vel_buttons->addWidget(cancel_aver_over_vel,Qt::AlignHCenter);
    aver_over_vel_buttons->addWidget(make_aver_over_vel,Qt::AlignHCenter);
    // do integrate
    aver_over_vel_layout->addLayout(start_aver_over_vel_channels,Qt::AlignHCenter);
    aver_over_vel_layout->addLayout(end_aver_over_vel_channels,Qt::AlignHCenter);
    aver_over_vel_layout->addLayout(aver_over_vel_buttons,Qt::AlignHCenter);

    // - connectujemy buttony -
    QPushButton::connect(cancel_aver_over_vel, SIGNAL(clicked()), this, SLOT(close_window_for_aver_over_velocity()));
    QPushButton::connect(make_aver_over_vel, SIGNAL(clicked()), this, SLOT(calculate_aver_over_velocity()));
}

void body::set_aver_over_time_widget()
{
    // - size policy -
    aver_over_time_widget->setMaximumSize(100000,150);

    // - przy starcie nie chcemy go widziec -
    aver_over_time_widget->setVisible(false);

    // - rozmiaty text editow -
    starting_channel_time->setMaximumSize(100,30);
    ending_channel_time->setMaximumSize(100,30);

    starting_channel_time->setMinimumSize(0,0);
    ending_channel_time->setMinimumSize(0,0);

    // - rozmiaty przyciskow -
    cancel_aver_over_time->setMinimumSize(0,0);
    make_aver_over_time->setMinimumSize(0,0);

    // - teksty na przyciskach i labelach -
    start_label_time->setText("Start epoch");
    end_label_time->setText("End epoch");
    make_aver_over_time->setText("Aver over time");
    cancel_aver_over_time->setText("Cancel");

    // - dodajemy do layoutow -
    // start
    start_aver_over_time_channels->addWidget(start_label_time,Qt::AlignHCenter);
    start_aver_over_time_channels->addWidget(starting_channel_time,Qt::AlignHCenter);
    // end
    end_aver_over_time_channels->addWidget(end_label_time,Qt::AlignHCenter);
    end_aver_over_time_channels->addWidget(ending_channel_time,Qt::AlignHCenter);
    // przyciski
    aver_over_time_buttons->addWidget(cancel_aver_over_time,Qt::AlignHCenter);
    aver_over_time_buttons->addWidget(make_aver_over_time,Qt::AlignHCenter);
    // do integrate
    aver_over_time_layout->addLayout(start_aver_over_time_channels,Qt::AlignHCenter);
    aver_over_time_layout->addLayout(end_aver_over_time_channels,Qt::AlignHCenter);
    aver_over_time_layout->addLayout(aver_over_time_buttons,Qt::AlignHCenter);

    // - connectujemy buttony -
    QPushButton::connect(cancel_aver_over_time, SIGNAL(clicked()), this, SLOT(close_window_for_aver_over_time()));
    QPushButton::connect(make_aver_over_time, SIGNAL(clicked()), this, SLOT(calculate_aver_over_time()));
}

void body::set_spectral_index_widget()
{
    // - size policy -
    aver_over_spi_widget->setMaximumSize(100000,150);

    // - przy starcie nie chcemy go widziec -
    aver_over_spi_widget->setVisible(false);

    // - rozmiaty text editow -
    starting_channel_spi->setMaximumSize(100,30);
    ending_channel_spi->setMaximumSize(100,30);

    starting_channel_spi->setMinimumSize(0,0);
    ending_channel_spi->setMinimumSize(0,0);

    // - rozmiaty przyciskow -
    make_aver_over_spi->setMinimumSize(0,0);
    cancel_aver_over_spi->setMinimumSize(0,0);

    // - teksty na przyciskach i labelach -
    start_label_spi->setText("Start epoch");
    end_label_spi->setText("End epoch");
    make_aver_over_spi->setText("Spindicate");
    cancel_aver_over_spi->setText("Cancel");

    // - dodajemy do layoutow -
    // start
    start_aver_over_spi_channels->addWidget(start_label_spi,Qt::AlignHCenter);
    start_aver_over_spi_channels->addWidget(starting_channel_spi,Qt::AlignHCenter);
    // end
    end_aver_over_spi_channels->addWidget(end_label_spi,Qt::AlignHCenter);
    end_aver_over_spi_channels->addWidget(ending_channel_spi,Qt::AlignHCenter);
    // przyciski
    aver_over_spi_buttons->addWidget(cancel_aver_over_spi,Qt::AlignHCenter);
    aver_over_spi_buttons->addWidget(make_aver_over_spi,Qt::AlignHCenter);
    // do integrate
    aver_over_spi_layout->addLayout(start_aver_over_spi_channels,Qt::AlignHCenter);
    aver_over_spi_layout->addLayout(end_aver_over_spi_channels,Qt::AlignHCenter);
    aver_over_spi_layout->addLayout(aver_over_spi_buttons,Qt::AlignHCenter);

    // - connectujemy buttony -
    QPushButton::connect(cancel_aver_over_spi, SIGNAL(clicked()), this, SLOT(close_window_for_spind()));
    QPushButton::connect(make_aver_over_spi, SIGNAL(clicked()), this, SLOT(calculate_spectral_index()));

}

void body::set_wd_widget()
{
    // - size policy -
    ex_dynsp_widget->setMaximumSize(100000,150);

    // - przy starcie nie chcemy go widziec -
    ex_dynsp_widget->setVisible(false);

    // - rozmiaty text editow -
    starting_channel_ex_dynsp->setMaximumSize(100,30);
    ending_channel_ex_dynsp->setMaximumSize(100,30);
    starting_epoch_ex_dynsp->setMaximumSize(100,30);
    ending_epoch_ex_dynsp->setMaximumSize(100,30);

    starting_channel_ex_dynsp->setMinimumSize(0,0);
    ending_channel_ex_dynsp->setMinimumSize(0,0);
    starting_epoch_ex_dynsp->setMinimumSize(0,0);
    ending_epoch_ex_dynsp->setMinimumSize(0,0);

    // - rozmiaty przyciskow -
    cancel_ex_dynsp->setMinimumSize(0,0);
    make_ex_dynsp->setMinimumSize(0,0);

    // - teksty na przyciskach i labelach -
    start_label_ex_dynsp->setText("Start Channel");
    end_label_ex_dynsp->setText("End Channel");
    make_ex_dynsp->setText("Export dynspec.");
    cancel_ex_dynsp->setText("Cancel");
    start_epoch_label_ex_dynsp->setText("Start epoch");
    end_epoch_label_ex_dynsp->setText("End epoch");

    // - dodajemy do layoutow -
    // start chan
    start_ex_dynsp_channels->addWidget(start_label_ex_dynsp,Qt::AlignHCenter);
    start_ex_dynsp_channels->addWidget(starting_channel_ex_dynsp,Qt::AlignHCenter);
    // end chan
    end_ex_dynsp_channels->addWidget(end_label_ex_dynsp,Qt::AlignHCenter);
    end_ex_dynsp_channels->addWidget(ending_channel_ex_dynsp,Qt::AlignHCenter);
    // start epoch
    start_ex_dynsp_epoch->addWidget(start_epoch_label_ex_dynsp, Qt::AlignHCenter);
    start_ex_dynsp_epoch->addWidget(starting_epoch_ex_dynsp, Qt::AlignHCenter);
    // end epoch
    end_ex_dynsp_epoch->addWidget(end_epoch_label_ex_dynsp, Qt::AlignHCenter);
    end_ex_dynsp_epoch->addWidget(ending_epoch_ex_dynsp, Qt::AlignHCenter);
    // przyciski
    ex_dynsp_buttons->addWidget(cancel_ex_dynsp,Qt::AlignHCenter);
    ex_dynsp_buttons->addWidget(make_ex_dynsp,Qt::AlignHCenter);
    // do integrate
    ex_dynsp_layout->addLayout(start_ex_dynsp_channels,Qt::AlignHCenter);
    ex_dynsp_layout->addLayout(end_ex_dynsp_channels,Qt::AlignHCenter);
    ex_dynsp_layout->addLayout(start_ex_dynsp_epoch,Qt::AlignHCenter);
    ex_dynsp_layout->addLayout(end_ex_dynsp_epoch,Qt::AlignHCenter);
    ex_dynsp_layout->addLayout(ex_dynsp_buttons,Qt::AlignHCenter);

    // connectujemy buttony
    QPushButton::connect(cancel_ex_dynsp, SIGNAL(clicked()), this, SLOT(close_dynspectrum_layout()));
    QPushButton::connect(make_ex_dynsp, SIGNAL(clicked()), this, SLOT(export_file_for_dynamic_spectrum()));
}

void body::set_calibrate_widget()
{
    // - size policy -
    calibrate_widget->setMaximumSize(100000,150);

    // - visibility -
    calibrate_widget->setVisible(false);

    // - setujemy tekst -
    cancel_calib->setText("Cancel");

    // - rozmiarówka -
    load_caltab_l1 -> setMinimumSize(0,0);
    load_caltab_r1 -> setMinimumSize(0,0);
    start_calibration -> setMinimumSize(0,0);

    // - konstrukcja widgetu -
    L1->addWidget(load_caltab_l1,Qt::AlignHCenter);
    L1->addWidget(caltab_l1_path,Qt::AlignHCenter);
    R1->addWidget(load_caltab_r1,Qt::AlignHCenter);
    R1->addWidget(caltab_r1_path,Qt::AlignHCenter);
    calbtns->addWidget(start_calibration,Qt::AlignHCenter);
    calbtns->addWidget(cancel_calib,Qt::AlignHCenter);
    calibrate_layout->addLayout(L1,Qt::AlignHCenter);
    calibrate_layout->addLayout(R1,Qt::AlignHCenter);
    calibrate_layout->addLayout(calbtns,Qt::AlignHCenter);

    // - connectujemy buttony -
    QPushButton::connect(cancel_calib, SIGNAL(clicked()), this, SLOT(close_cal_layout()));
    QPushButton::connect(start_calibration, SIGNAL(clicked()), this, SLOT(calibrate_button()));
    QPushButton::connect(load_caltab_l1, SIGNAL(clicked()), this, SLOT(load_l1_caltab_button()));
    QPushButton::connect(load_caltab_r1, SIGNAL(clicked()), this, SLOT(load_r1_caltab_button()));
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
    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (dynamic_spectrum_opened == 1)
    {
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        //QMessageBox::information(&window, tr("Error!"), tr("Please, close the DYNAMIC SPECTRUM window"));
        kill_dynamic_spectrum();
        //return;
    }


    else if (gauss_section_opened == 1)
    {
        close_gauss_widget();
    }

    else if (rms_section_opened == 1)
    {
        //cout << "Plese close the DYNAMIC SPECTRUM window" << endl;
        //QMessageBox::information(&window, tr("Error!"), tr("Please, close the RMS, Sint & Tsys window"));
        close_rms_section_slot();
        //return;
    }


    // -- dodajemy widget do głównego gridu --
    grid->addWidget(single_spectrum_widget, 0,1,9,5);

    // -- dodajemy kill singspec do vboxa --
    vbox_main.addWidget(kill_singspec);

    // -- ustalamy szerokości kolumny --
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);

    // -- ustalamy geometrię okna --


    // -- updatujemy nasze kochane rzeczy --
    grid->update();
    window.show();

    // -- zapelniamy wstepnie single spectrum --
    plot_single_spectrum();

    // -- ustawiamy visibility naszego widgetu --
    single_spectrum_widget->setVisible(true);
    kill_singspec->setVisible(true);

    // -- ustawiamy boola, informujacego co jest akurat otwarte --
    single_spectrum_opened=1;
}

// - zapełnia wstępnie wykres w powyższej sekcji -
void body::plot_single_spectrum()
{
    if (single_spectrum_opened == 1)
        return;

    // setujemy plot
    spectrum.clearGraphs();
    n_graphs_on_single_spec = 0;
    numbers_of_epochs_on_single_spec.clear();

    // przygotowujemy dane
    unsigned int marker = 0;
    // wektor z danymi
    //QVector < double > x(n_chanslst[marker]), y(n_chanslst[marker]);
    QVector < double > x (dataTable->channelTable[marker].size()), y(dataTable->channelTable[marker].size());
    // zapelniamy wektor
    for(unsigned int i = 0; i < dataTable->spectraTableI[marker].size(); i++)
    {
        x[i] = dataTable->velocityTable[marker][i];
        y[i] = dataTable->spectraTableI[marker][i];
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
    spectrum.xAxis2->setRange(*min_element(x.begin(), x.end()) - 0.05 * veldiff, *max_element(x.begin(), x.end())  + 0.05 * veldiff);
    spectrum.yAxis2->setRange(*min_element(y.begin(), y.end()) - 0.05 * (*max_element(y.begin(), y.end())), *max_element(y.begin(), y.end())  + 0.05 * (*max_element(y.begin(), y.end())));
    // -- pokazujemy ticki na gornej osi --
    spectrum.xAxis2->setVisible(true);
    spectrum.yAxis2->setVisible(true);
    spectrum.xAxis2->setTickLabels(false);
    spectrum.yAxis2->setTickLabels(false);

    // -- dodajemy interakcje --
    spectrum.setInteractions(QCP::iRangeZoom | QCP::iSelectPlottables);

    spectrum.axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    spectrum.axisRect()->setRangeZoom(Qt::Horizontal| Qt::Vertical);
    spectrum.axisRect()->setRangeZoomAxes(spectrum.xAxis, spectrum.yAxis);
    spectrum.setSelectionRectMode(QCP::srmZoom);

    // -- ladujemy combo boxa --

    for(int i = 0; i < dataTable->mjdTable.size(); i++)
    {
        list_of_observations->addItem(QString::fromStdString(to_string(i+1) + "   " + to_string(dataTable->mjdTable[i])));
    }

    // -- replotujemy single spectrum --
    spectrum.replot();

    // -- dwie rzeczy --
    n_graphs_on_single_spec = 1;
    numbers_of_epochs_on_single_spec.push_back(marker);
}

// - zamyka sekcję "single spectrum"
void body::kill_single_spectrum()
{
    // - odpinamy od grida -
    grid->removeWidget(single_spectrum_widget);
    // - odpinamy od vboxa -
    vbox_main.removeWidget(kill_singspec);
    // - znikamy -
    single_spectrum_widget->setVisible(false);
    kill_singspec->setVisible(false);
    // - ustawiamy widoczność -
    single_spectrum_opened=0;
    // - clearujemy list_of_obs -
    list_of_observations->clear();
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

    // -- wczytujemy: jeśli nasza lista plików to AVR, wczyta się w try, jeśli to plik z listą - w catch --
    dataTable->loadDataFromList(fileName1);
    loaded_data = 1;

    if (single_spectrum_opened == 1)
    {
        kill_single_spectrum();
        display_single_spectrum();
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

    unsigned int min, max;
    QString mins,maxs;
    mins = starting_channel_int->toPlainText();
    maxs = ending_channel_int->toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
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
    if (min < 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel < 1!"));
        return;
    }
    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > dataTable->spectraTableI[0].size())
        max = dataTable->spectraTableI[0].size();

    // --- całka właściwa ---
    dataTable->integrate4Pols(min, max, include_pytime->isChecked());

    // --- wiadomość końcowa ---
    string message = "";
    message = "Integrated over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getIntegrationFileName(min, max);
    close_window_for_integrate();
    QMessageBox::information(&window, tr("Message to you"), QString::fromStdString(message));
}

void body::plot_dynamic_spectrum()
{
    // na wszelki wypadek - czyścimy itemy
    single_dynamic_spectrum.clearItems();
    lcs_dynamic_spectrum.clearItems();

    // -- kilka rzeczy ustawiamy --
    min_range_vel_index = 0;
    min_obs_number = 0;
    max_range_vel_index = dataTable->velocityTable[0].size()-1;
    max_obs_number = dataTable->mjdTable.size()-1;
    rozmiar_w_x = dataTable->mjdTable.size();
    rozmiar_w_y = dataTable->velocityTable[0].size();

    double min_velocity = dataTable->velocityTable[0][min_range_vel_index];
    double max_velocity = dataTable->velocityTable[0][max_range_vel_index] - (dataTable->velocityTable[0][2] - dataTable->velocityTable[0][1]);

    // -- updatujemy widmo dynamiczne --
    //update_dynamic_spectrum();

    // color mapa
    unsigned long int nx = dataTable->mjdTable.size();
    unsigned long int ny = dataTable->velocityTable[0].size();

    colorMap->data()->setSize(nx,ny);
    //colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(dataTable->velocityTable[0][min_range_vel_index], dataTable->velocityTable[0][max_range_vel_index]-(dataTable->velocityTable[0][2]-dataTable->velocityTable[0][1])));
    if (rozmiar_w_x != 1)
        colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(min_velocity, max_velocity ) );
    else
        colorMap->data()->setRange(QCPRange(-0.5, 0.5), QCPRange(min_velocity, max_velocity ));
    //double x,y,z;

    for (unsigned long int xIndex = 0; xIndex < nx; xIndex++)
    {
        for (unsigned long int yIndex = 0; yIndex < ny; yIndex++)
        {
            //colorMap->data()->cellToCoord(xIndex,yIndex, &x, &y);
            if (dataTable->spectraTableI[xIndex][yIndex] > 0.0)
                colorMap->data()->setCell(xIndex, yIndex, dataTable->spectraTableI[xIndex][yIndex]);
            else
                colorMap->data()->setCell(xIndex, yIndex, 0.0);
        }
    }

    // -- color gradient --
    gradient.loadPreset(QCPColorGradient::gpJet);
    colorMap -> setGradient(gradient);
    colorMap->setDataScaleType(QCPAxis::stLinear);
    colorMap -> rescaleDataRange();
    colorMap -> rescaleKeyAxis();
    colorMap -> rescaleValueAxis();
    colorMap -> setTightBoundary(false);

    // -- na koniec --
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();

}
// -- wyswietla widmo dynamiczne --
void body::display_dynamic_spectrum()
{
    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    if (single_spectrum_opened == 1)
    {
        kill_single_spectrum();
    }
    else if (rms_section_opened == 1)
    {
        close_rms_section_slot();
    }


    else if (gauss_section_opened == 1)
    {
        close_gauss_widget();
    }

    else if (dynamic_spectrum_opened == 1)
    {
        min_range_vel_index = 0;
        min_obs_number = 0;
        max_range_vel_index = dataTable->velocityTable[0].size()-1;
        max_obs_number = dataTable->mjdTable.size()-1;
        rozmiar_w_x = dataTable->mjdTable.size();
        rozmiar_w_y = dataTable->velocityTable[0].size();
        press_map_met(xind,yind);
        update_dynamic_spectrum();
        return;
    }
    // -- dodajemy widget do grida --
    grid->addWidget(dynamic_spectrum_widget, 0,1,9,5);

    // -- dodajemy do vbox maina przycisk killujacy dynspec --
    vbox_main.addWidget(kill_dynspec);

    // -- ustalamy szerokości kolumny --
    grid->setColumnStretch(1,1);
    grid->setColumnStretch(2,2);
    grid->setColumnStretch(3,2);
    grid->setColumnStretch(4,2);
    grid->setColumnStretch(5,2);

    // -- plotujemy dynamic spectrum --
    if (first_time_dynamic_spectrum_opened == 1)
    {
        plot_dynamic_spectrum();
        first_time_dynamic_spectrum_opened = 0;
    }
    else
    {
        update_dynamic_spectrum();
    }

    // -- ustawiamy, ktory z przyciskow do pol. jest wcisniety --
    Ibut->setDown(true);
    LHCbut->setDown(false);
    RHCbut->setDown(false);
    Vbut->setDown(false);
    lhc_pressed = 0;
    rhc_pressed = 0;
    I_pressed = 1;
    v_pressed = 0;

    // bool mowiacy, czy widmo dynamcizne jest otwarte
    dynamic_spectrum_opened = 1;

    // ustalamy ilość rotowanych kanałów
    QString rot;
    rot = QString::fromStdString(to_string(number_of_rotated_channels));
    number_of_rotated_channels_texted->setText(rot);

    // wywolujemy metode, symulujaca klikniecie w 0,0
    press_map_met(xind, yind);

    // -- pokazujemy widget z dynamic spectrum --
    kill_dynspec->setVisible(true);
    dynamic_spectrum_widget->setVisible(true);

    // -- pokazujemy nasze kochane checkboxy --
    set_log_scale->setVisible(true);
    // -- reskalujemy osie --
    dynamic_spectrum_pl.rescaleAxes();
}

// -- zamyka widmo dynamiczne --
void body::kill_dynamic_spectrum()
{
    // -- chowamy checkbox --
    set_log_scale->setVisible(false);
    // -- chowamy dynamic spectrum --
    dynamic_spectrum_widget->setVisible(false);

    // -- odpinamy od grida --
    grid->removeWidget(dynamic_spectrum_widget);

    // -- odpinamy przycisk od vboxa --
    vbox_main.removeWidget(kill_dynspec);
    kill_dynspec->setVisible(false);

    // -- ustalamy boola --
    dynamic_spectrum_opened = 0;
}

// -- obsluguje wcisniecia na widmie dynamicznym --
void body::press_map(QMouseEvent * event)
{
    QPen graph_dark;
    graph_dark.setColor(QColor(135,206,250));
    graph_dark.setWidth(2);

    QPen graph_light;
    graph_light.setColor(QColor(0,0,255));
    graph_light.setWidth(2);

    // przechwytujemy pozycję kliknięcia
    double x,y;
    x = dynamic_spectrum_pl.xAxis->pixelToCoord(event -> pos().x());
    y = dynamic_spectrum_pl.yAxis->pixelToCoord(event -> pos().y());

    // zadajemy wartości parametrów na wypadki, gdy kliknięcie jest poza granicami plotu:
    if(x < 0)
    {
        x = 0.0;
    }
    else if (x > dataTable->mjdTable.size()-1)
    {
        x = dataTable->mjdTable.size()-1;
    }

    if(y < dataTable->velocityTable[0][0])
    {
        y = dataTable->velocityTable[0][0];
    }
    else if (y > dataTable->velocityTable[0][dataTable->velocityTable[0].size()-1])
    {
        y = dataTable->velocityTable[0][dataTable->velocityTable[0].size()-1];
    }


    // stwierdzenie, która epoka została kliknięta jest bardzo proste - wystarczy zaokrąglić pozycję kliknięcia:
    xind = int(round(x));

    // następnie musimy przeszukać tablicę Vel, by znaleźć indeks, odpowiadający klikniętemu Y:
    for(int i=0; i < dataTable->velocityTable[0].size(); i++)
    {

        if (dataTable->velocityTable[0][i] > y+0.5*(dataTable->velocityTable[0][2]-dataTable->velocityTable[0][1]))
        {
            yind = i-1;
            break;
        }
    }

    // dodatkowe zabezpieczenia
    if (yind > max_range_vel_index)
        yind = max_range_vel_index-1;

    if (yind < min_range_vel_index)
        yind = min_range_vel_index;

    if (xind < min_obs_number)
        xind = min_obs_number;

    if (xind > max_obs_number)
        xind = max_obs_number;

    // zabezpieczeine, jeśli kliknięta została brzegowa komórka:
    if (yind < 0)
    {
        yind = 0;
    }

    if (xind < 0)
    {
        xind = 0;
    }

    press_map_met(xind, yind);

}

void body::set_dynamic_spectrum_labels_for_clicked(int x_index_cl, int y_index_cl)
{
    // -- setujemy tekst do displayowania informacji --
    // --------------
    // Lewy
    string text_mjdlabel = "";
    text_mjdlabel.append(string("MJD = "));
    text_mjdlabel.append(to_string(int(dataTable->mjdTable[x_index_cl])));


    text_mjdlabel.append(string("\nChannel: "));
    text_mjdlabel.append(to_string((int) dataTable->channelTable[x_index_cl][y_index_cl]));

    text_mjdlabel.append(string("\nVel: "));

    // Create an output string stream
    std::ostringstream streamObjvel;

    // Set Fixed -Point Notation
    streamObjvel << std::fixed;

    streamObjvel << std::setprecision(3);

    streamObjvel << dataTable->velocityTable[x_index_cl][y_index_cl];
    std::string strObjvel = streamObjvel.str();
    text_mjdlabel.append(strObjvel);


    mjd_label.setText(QString::fromStdString(text_mjdlabel));
    QFont f( "Arial", 11, QFont::Bold);
    mjd_label.setFont(f);
    // --------------

    // ---------------
    // Prawy
    string cocochanel_txt = "";

    cocochanel_txt.append(string("Date: "));
    cocochanel_txt.append(to_string(int(dataTable->datetimeTable[x_index_cl][0])));
    cocochanel_txt.append(string(" "));


    if (int(dataTable->datetimeTable[x_index_cl][1]) < 10)
        cocochanel_txt.append("0" + to_string(int(dataTable->datetimeTable[x_index_cl][1])));
    else
        cocochanel_txt.append(to_string(int(dataTable->datetimeTable[x_index_cl][1])));

    cocochanel_txt.append(string(" "));

    if (int(dataTable->datetimeTable[x_index_cl][2]) < 10)
        cocochanel_txt.append("0" + to_string(int(dataTable->datetimeTable[x_index_cl][2])));
    else
        cocochanel_txt.append(to_string(int(dataTable->datetimeTable[x_index_cl][2])));

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Value: "));

    // Create an output string stream
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    streamObj3 << std::setprecision(3);

    if (I_pressed==1)
    {
        streamObj3 << dataTable->spectraTableI[x_index_cl][y_index_cl];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (v_pressed==1)
    {
        streamObj3 << dataTable->spectraTableV[x_index_cl][y_index_cl];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (lhc_pressed==1)
    {
        streamObj3 << dataTable->spectraTableLHC[x_index_cl][y_index_cl];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }
    else if (rhc_pressed==1)
    {
        streamObj3 << dataTable->spectraTableRHC[x_index_cl][y_index_cl];
        std::string strObj3 = streamObj3.str();
        cocochanel_txt.append(strObj3);
    }

    cocochanel_txt.append(string("\n"));
    cocochanel_txt.append(string("Number: "));
    cocochanel_txt.append(to_string(x_index_cl+1));

    cocochanel.setFont(f);
    cocochanel.setText(QString::fromStdString(cocochanel_txt));
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

    // aktualizujemy widmo dynamiczne
    update_dynamic_spectrum();
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

    // aktualizujemy widmo dynamiczne
    update_dynamic_spectrum();
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

    // aktualizujemy widmo dynamiczne
    update_dynamic_spectrum();
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

    // aktualizujemy widmo dynamiczne
    update_dynamic_spectrum();
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
    // -- ustalamy zmienne --
    Ibut->setDown(true);
    LHCbut->setDown(false);
    RHCbut->setDown(false);
    Vbut->setDown(false);
    I_pressed = 1;
    lhc_pressed = 0;
    rhc_pressed = 0;
    v_pressed = 0;

    // -- aktualizujemy dynspec --
    update_dynamic_spectrum();
}

// -- ustala parametr stokesa 'V' na widmie dynamicznym --
void body::set_V_on_dynamic_spectrum()
{
    // -- ustalamy zmienne --
    Ibut->setDown(false);
    LHCbut->setDown(false);
    RHCbut->setDown(false);
    Vbut->setDown(true);
    I_pressed = 0;
    lhc_pressed = 0;
    rhc_pressed = 0;
    v_pressed = 1;

    // -- aktualizujemy dynspec --
    update_dynamic_spectrum();
}

// -- ustala parametr stokesa 'LHC' na widmie dynamicznym --
void body::set_LHC_on_dynamic_spectrum()
{

    // -- ustalamy zmienne --
    Ibut->setDown(false);
    LHCbut->setDown(true);
    RHCbut->setDown(false);
    Vbut->setDown(false);
    I_pressed = 0;
    lhc_pressed = 1;
    rhc_pressed = 0;
    v_pressed = 0;

    // -- aktualizujemy dynspec --
    update_dynamic_spectrum();
}

// -- ustala parametr stokesa 'RHC' na widmie dynamicznym --
void body::set_RHC_on_dynamic_spectrum()
{

    // -- ustalamy zmienne --
    Ibut->setDown(false);
    LHCbut->setDown(false);
    RHCbut->setDown(true);
    Vbut->setDown(false);
    I_pressed = 0;
    lhc_pressed = 0;
    rhc_pressed = 1;
    v_pressed = 0;

    // -- aktualizujemy dynspec --
    update_dynamic_spectrum();
}

// -- robi to samo, co 'press_map()', jednak bez wciśnięcia - czyta ostatnio zapisane wartości x i y --
void body::press_map_met(unsigned long int x, unsigned long int y)
{
    QPen graph_dark;
    graph_dark.setColor(QColor(135,206,250));
    graph_dark.setWidth(2);

    QPen graph_light;
    graph_light.setColor(QColor(0,0,255));
    graph_light.setWidth(2);

    xind = x;
    yind = y;

    // teraz linie pionowe na widmie dynamicznym
    QPen pen;
    pen.setColor(QColor(255,255,255)); // dajemy im biały kolor
    x_axis_line->setPen(pen);
    y_axis_line->setPen(pen);

    // ustalamy kursor na dynspec na krzyżyk
    dynamic_spectrum_pl.setCursor(QCursor(Qt::CrossCursor));

    // ustalamy jak mają rozciągać się linie:
    x_axis_line->start->setCoords(xind, -QCPRange::maxRange);
    x_axis_line->end->setCoords(xind, QCPRange::maxRange);
    y_axis_line->start->setCoords(-QCPRange::maxRange,dataTable->velocityTable[0][yind]);
    y_axis_line->end->setCoords(QCPRange::maxRange,dataTable->velocityTable[0][yind]);

    // biały kwadrat, zaznaczający kliknięty piksel:
    rectangle->setPen(pen);
    rectangle->topLeft->setCoords(double(xind)-0.5, dataTable->velocityTable[0][yind]+0.5*(dataTable->velocityTable[0][2]-dataTable->velocityTable[0][1]));
    rectangle->bottomRight->setCoords(double(xind)+0.5, dataTable->velocityTable[0][yind]-0.5*(dataTable->velocityTable[0][2]-dataTable->velocityTable[0][1]));

    // i replot
    dynamic_spectrum_pl.replot();

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
        velocity[i] = dataTable->velocityTable[xind][min_range_vel_index+i];
        flux[i] = dataTable->spectraTableI[xind][min_range_vel_index+i];
    }
    }

    else if (v_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = dataTable->velocityTable[xind][min_range_vel_index+i];
        flux[i] = dataTable->spectraTableV[xind][min_range_vel_index+i];
    }
    }
    else if (lhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = dataTable->velocityTable[xind][min_range_vel_index+i];
        flux[i] = dataTable->spectraTableLHC[xind][min_range_vel_index+i];
    }
    }
    else if (rhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = dataTable->velocityTable[xind][min_range_vel_index+i];
        flux[i] = dataTable->spectraTableRHC[xind][min_range_vel_index+i];
    }
    }


    single_dynamic_spectrum.graph(0)->setData(velocity,flux);
    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double veldiff = *max_element(velocity.begin(), velocity.end()) - *min_element(velocity.begin(), velocity.end());
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));
    single_dynamic_spectrum.xAxis2->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis2->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));

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


    // -- ustawiamy pionową linię --
    // -- stylistyka --
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    QVector < double > x_vline(2), y_vline(2);
    x_vline[0] = dataTable->velocityTable[xind][yind];
    x_vline[1] = dataTable->velocityTable[xind][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end()));
    y_vline[1] = *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end()));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);


    //first_item_position
    //inf_vel_line->anchor()

    // -- tworzymy krzywa blasku, ktora wyswietli sie w krzywej blasku --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    if(I_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = dataTable->mjdTable[min_obs_number + i];
        lcs_flux[i] = dataTable->spectraTableI[min_obs_number + i][yind];
        error_lcs[i] = dataTable->spectraTableIERR[min_obs_number + i];
    }
    }

    else if(v_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = dataTable->mjdTable[min_obs_number + i];
        lcs_flux[i] = dataTable->spectraTableV[min_obs_number + i][yind];
        error_lcs[i] = dataTable->spectraTableVERR[min_obs_number + i];
    }
    }

    else if(lhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = dataTable->mjdTable[min_obs_number + i];
        lcs_flux[i] = dataTable->spectraTableLHC[min_obs_number + i][yind];
        error_lcs[i] = dataTable->spectraTableLHCERR[min_obs_number + i];
    }
    }

    else if(rhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = dataTable->mjdTable[min_obs_number + i];
        lcs_flux[i] = dataTable->spectraTableRHC[min_obs_number + i][yind];
        error_lcs[i] = dataTable->spectraTableRHCERR[min_obs_number + i];
    }
    }

    errorBars->setAntialiased(false);
    errorBars->setDataPlottable(lcs_dynamic_spectrum.graph(0));
    if(!dark_mode_switch->isChecked())
        errorBars->setPen(QPen(QColor(180,180,180)));
    else
        errorBars->setPen(QPen(QColor(105,105,105)));

    lcs_dynamic_spectrum.graph(0)->setData(epoch,lcs_flux);
    errorBars->setData(error_lcs);

    //lcs_dynamic_spectrum.graph(0)->setPen(QPen(Qt::blue));
    lcs_dynamic_spectrum.graph(0)->setLineStyle(QCPGraph::lsNone);
    lcs_dynamic_spectrum.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    lcs_dynamic_spectrum.xAxis->setLabel("MJD");
    lcs_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");

    if (rozmiar_w_x == 1)
    {
        lcs_dynamic_spectrum.rescaleAxes();
    }
    else
    {
        double diffrence = *max_element(epoch.begin(), epoch.end()) - *min_element(epoch.begin(), epoch.end());
        lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
        lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
        lcs_dynamic_spectrum.xAxis2->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
        lcs_dynamic_spectrum.yAxis2->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
    }

    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);


    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }


    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = dataTable->mjdTable[xind];
    lcsx_vline[1] = dataTable->mjdTable[xind];
    if (rozmiar_w_x == 1)
    {
        lcsy_vline[0] = lcs_dynamic_spectrum.yAxis->range().lower;
        lcsy_vline[1] = lcs_dynamic_spectrum.yAxis->range().upper;
    }
    else
    {
        lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
        lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    }
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);


    set_down_IVLHCRHCbuttons();
    set_dynamic_spectrum_labels_for_clicked(xind, yind);


    // ----- dodatkowa rzecz ! ---------------
    // -- dodajemy odpowiednią kropkę na krzywej blasku --
    if (dot_single_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        dot_single_added = 1;
    }

    // -- ustawiamy sobie kropkę na single spectrum --
    QVector < double > x_dot_spec(1), y_dot_spec(1);
    // predkosc radialna
    x_dot_spec[0] = dataTable->velocityTable[xind][yind]; // kliknięta prędkość radialna
    // gestosć strumienia
    if (I_pressed == 1)
        y_dot_spec[0] = dataTable->spectraTableI[xind][yind]; // kliknięta gęstość strumienia
    else if (lhc_pressed == 1)
        y_dot_spec[0] = dataTable->spectraTableLHC[xind][yind]; // kliknięta gęstość strumienia
    else if (rhc_pressed == 1)
        y_dot_spec[0] = dataTable->spectraTableRHC[xind][yind]; // kliknięta gęstość strumienia
    else if (v_pressed == 1)
        y_dot_spec[0] = dataTable->spectraTableV[xind][yind]; // kliknięta gęstość strumienia


    single_dynamic_spectrum.graph(2)->setData(x_dot_spec, y_dot_spec);
    if(dark_mode_switch->isChecked())
        single_dynamic_spectrum.graph(2)->setPen(QPen(Qt::magenta));
    else
        single_dynamic_spectrum.graph(2)->setPen(pen2);
    single_dynamic_spectrum.graph(2)->setLineStyle(QCPGraph::lsNone);
    single_dynamic_spectrum.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));


    // -- dodajemy kropkę na krzywej blasku --
    if (dot_lcs_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        dot_lcs_added = 1;
    }

    // -- ustawiamy sobie kropkę na single spectrum --
    QVector < double > x_dot_lcs(1), y_dot_lcs(1);
    // predkosc radialna
    x_dot_lcs[0] = dataTable->mjdTable[xind]; // kliknięta epoka
    // gestosć strumienia
    if (I_pressed == 1)
        y_dot_lcs[0] = dataTable->spectraTableI[xind][yind]; // kliknięta gęstość strumienia
    else if (lhc_pressed == 1)
        y_dot_lcs[0] = dataTable->spectraTableLHC[xind][yind]; // kliknięta gęstość strumienia
    else if (rhc_pressed == 1)
        y_dot_lcs[0] = dataTable->spectraTableRHC[xind][yind]; // kliknięta gęstość strumienia
    else if (v_pressed == 1)
        y_dot_lcs[0] = dataTable->spectraTableV[xind][yind]; // kliknięta gęstość strumienia
    // -- stylistyka --
    lcs_dynamic_spectrum.graph(2)->setData(x_dot_lcs, y_dot_lcs);
    if(dark_mode_switch->isChecked())
        lcs_dynamic_spectrum.graph(2)->setPen(QPen(Qt::magenta));
    else
        lcs_dynamic_spectrum.graph(2)->setPen(pen2);
    lcs_dynamic_spectrum.graph(2)->setLineStyle(QCPGraph::lsNone);
    lcs_dynamic_spectrum.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));

    // -- dark i light mode --
    if (dark_mode_switch->isChecked())
    {
        single_dynamic_spectrum.graph(0)->setPen(graph_dark);
        lcs_dynamic_spectrum.graph(0)->setPen(graph_dark);
    }
    else
    {
        single_dynamic_spectrum.graph(0)->setPen(graph_light);
        lcs_dynamic_spectrum.graph(0)->setPen(graph_light);
    }

    single_dynamic_spectrum.replot();
    lcs_dynamic_spectrum.replot();
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
    mins = starting_channel_aov->toPlainText();
    maxs = ending_channel_aov->toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
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
    if (min < 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Min channel < 1!"));
        return;
    }

    // koncowy channel większy od maksymalnej ilości kanałów
    if (max > dataTable->spectraTableI[0].size())
        max = dataTable->spectraTableI[0].size();

    // liczymy aver over velocity
    dataTable->averageOverVelocity4Pols(min, max, include_pytime->isChecked());

    string message = "";
    message = "Averaged over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getAverOverVelFileName(min, max);
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
    if (dataTable->loadedData == false)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    QString mins,maxs;
    mins = starting_channel_time->toPlainText();
    maxs = ending_channel_time->toPlainText();
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
        min = stoi(mins.toStdString());
        max = stoi(maxs.toStdString());
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

    if (max > dataTable->mjdTable.size())
        max = dataTable->mjdTable.size();

    // wykonujemy właściwej transformacji
    dataTable->averOverTime4Pols(min, max);

    // wiadomość dla usera
    string message;
    message = "Averaged over epochs: " + to_string(min) + " " + " -> " + to_string(max) + "\n";
    message = message + "Saved to " + dataTable->getAverOverTimeFileName(min, max);
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
    mins = starting_channel_spi->toPlainText();
    maxs = ending_channel_spi->toPlainText();
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

    if (max > dataTable->mjdTable.size()-1)
        max = dataTable->mjdTable.size()-1;


    for(int channel = 0; channel < dataTable->channelTable[0].size(); channel++)
    {
        // tworzymy bloki time series
        vector < double > I_timeseries, I_timeseries_err;
        vector < double > V_timeseries, V_timeseries_err;
        vector < double > LHC_timeseries, LHC_timeseries_err;
        vector < double > RHC_timeseries, RHC_timeseries_err;
        vector < double > wynik(3);
        // generujemy light_curves
        for (int i = 0; i < dataTable->mjdTable.size(); i++)
        {
            // I
            I_timeseries.push_back(dataTable->spectraTableI[i][channel]);
            I_timeseries_err.push_back(dataTable->spectraTableIERR[i]);

            // V
            V_timeseries.push_back(dataTable->spectraTableV[i][channel]);
            V_timeseries_err.push_back(dataTable->spectraTableVERR[i]);

            // LHC
            LHC_timeseries.push_back(dataTable->spectraTableLHC[i][channel]);
            LHC_timeseries_err.push_back(dataTable->spectraTableLHCERR[i]);

            // RHC
            RHC_timeseries.push_back(dataTable->spectraTableRHC[i][channel]);
            RHC_timeseries_err.push_back(dataTable->spectraTableRHCERR[i]);
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
    for(int i = 0; i < dataTable->channelTable[0].size(); i++)
    {
        integ << fixed << setprecision(11) << dataTable->channelTable[0][i] << "   " <<  dataTable->velocityTable[0][i] << "   " << VI_I[i] << "   " <<  VI_V[i] << "   " << VI_LHC[i] << "   " << VI_RHC[i] << endl;// << "   " << averaged_over_time_LHC[i] << "   " << averaged_over_time_LHC_err[i] << "   " << averaged_over_time_RHC[i] << "   " << averaged_over_time_RHC_err[i] <<  endl;
    }
    integ.close();

    string filenamefi = working_directory + "/" + srcname + "_FI_spind_epoch_" + to_string(min+1) + "_to_" + to_string(max+1) + ".DAT";
    integ.open(filenamefi.c_str());
    integ << "# channel velocity I V LHC RHC " << endl;
    for(int i = 0; i < dataTable->channelTable[0].size(); i++)
    {
        integ << fixed << setprecision(11) << dataTable->channelTable[0][i] << "   " <<  dataTable->velocityTable[0][i] << "   " << FI_I[i] << "   " <<  FI_V[i] << "   " << FI_LHC[i] << "   " << FI_RHC[i] << endl;// << "   " << averaged_over_time_LHC[i] << "   " << averaged_over_time_LHC_err[i] << "   " << averaged_over_time_RHC[i] << "   " << averaged_over_time_RHC_err[i] <<  endl;
    }
    integ.close();

    string filenamechi2 = working_directory + "/" + srcname + "_chi2_spind_epoch_" + to_string(min+1) + "_to_" + to_string(max+1) + ".DAT";
    integ.open(filenamechi2.c_str());
    integ << "# channel velocity I V LHC RHC " << endl;
    for(int i = 0; i < dataTable->channelTable[0].size(); i++)
    {
        integ << fixed << setprecision(11) << dataTable->channelTable[0][i] << "   " <<  dataTable->velocityTable[0][i] << "   " << chi2_I[i] << "   " <<  chi2_V[i] << "   " << chi2_LHC[i] << "   " << chi2_RHC[i] << endl;// << "   " << averaged_over_time_LHC[i] << "   " << averaged_over_time_LHC_err[i] << "   " << averaged_over_time_RHC[i] << "   " << averaged_over_time_RHC_err[i] <<  endl;
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
    QVector < double > x(dataTable->channelTable[marker].size()), y(dataTable->channelTable[marker].size());
    // zapelniamy wektor
    for(unsigned int i = 0; i < dataTable->spectraTableI[marker].size(); i++)
    {
        x[i] = dataTable->velocityTable[marker][i];
        y[i] = dataTable->spectraTableI[marker][i];
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
    QVector < double > x(dataTable->channelTable[last_marker].size()), y(dataTable->channelTable[last_marker].size());
    // zapelniamy wektor
    for(unsigned int i = 0; i < dataTable->spectraTableI[last_marker].size(); i++)
    {
        x[i] = dataTable->velocityTable[last_marker][i];
        y[i] = dataTable->spectraTableI[last_marker][i];
    }
    // ustalamy range
    double veldiff = *max_element(x.begin(), x.end()) - *min_element(x.begin(), x.end());
    spectrum.xAxis->setRange(*min_element(x.begin(), x.end()) - 0.05 * veldiff, *max_element(x.begin(), x.end())  + 0.05 * veldiff);
    spectrum.yAxis->setRange(*min_element(y.begin(), y.end()) - 0.05 * (*max_element(y.begin(), y.end())), *max_element(y.begin(), y.end())  + 0.05 * (*max_element(y.begin(), y.end())));
    spectrum.xAxis2->setRange(*min_element(x.begin(), x.end()) - 0.05 * veldiff, *max_element(x.begin(), x.end())  + 0.05 * veldiff);
    spectrum.yAxis2->setRange(*min_element(y.begin(), y.end()) - 0.05 * (*max_element(y.begin(), y.end())), *max_element(y.begin(), y.end())  + 0.05 * (*max_element(y.begin(), y.end())));
    spectrum.replot();

}

// -- usuwa wybrany plot z single spectrum --
void body::remove_selected_graph()
{

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
    string message;
    message = "Saved to ";
    // -- petla, zapisujaca do plikow --
    for (int i = 0; i < count; i++)
    {
        int epoch = numbers_of_epochs_on_single_spec[i];
        string filename;
        string avrname = dataTable->fileNamesTab[epoch];
        avrname.erase(avrname.end()-7, avrname.end());

        filename = avrname + to_string(int(dataTable->mjdTable[epoch])) + "_" + to_string(epoch+1) + "_spectrum.dat";

        ofstream plik;
        plik.open(filename);
        plik << "# chan vel I er V er LHC er RHC er" << endl;
        plik << fixed << setprecision(11) << "# freq: " << dataTable->restFreqsTable[epoch] << "   epoch: " << dataTable->mjdTable[epoch] << endl;
        for (int ee = 0; ee < dataTable->channelTable[epoch].size(); ee++)
        {
            plik << fixed << setprecision(11) << dataTable->channelTable[epoch][ee] << "   " <<  dataTable->velocityTable[epoch][ee] << "   " << dataTable->spectraTableI[epoch][ee] << "   " << dataTable->spectraTableIERR[epoch] << "   " << dataTable->spectraTableV[epoch][ee] <<  "   " << dataTable->spectraTableVERR[epoch] <<  "   " << dataTable->spectraTableLHC[epoch][ee] <<  "   " << dataTable->spectraTableLHCERR[epoch] <<  "   " << dataTable->spectraTableRHC[epoch][ee] <<  "   " << dataTable->spectraTableRHCERR[epoch] << endl;
        }
        plik.close();
        //cout << "----> Saved to " << filename << endl;
        message = message + filename + "\n";
    }
    QMessageBox::information(&window, tr("Message to you!"), QString::fromStdString(message));
}

void body::save_all_to_gnuplot_slot()
{
    // -- ilość źródeł --
    unsigned long int count_for_gnuplot = dataTable->spectraTableI.size();

    // -- pasek postepu --
    QProgressDialog postep;//(&window);
    postep.setLabelText("Saving files... please wait");
    postep.setMinimum(0);
    postep.setMaximum(count_for_gnuplot);
    postep.setVisible(true);

    // -- zapisujemy --
    for (unsigned long int i = 0; i < count_for_gnuplot; i++)
    {
        // -- epoka ekstrahowana do innej zmiennej --
        unsigned long int epoch = i;
        // -- tworzymy zmienną do przechowywania pliku --
        string filename;
        string avrname = dataTable->fileNamesTab[epoch];
        avrname.erase(avrname.end()-7, avrname.end());
        if (loaded_from_listfile == 1)
            filename = working_directory + "/" + avrname + to_string(int(dataTable->mjdTable[epoch])) + "_" + to_string(epoch+1) + "_spectrum.dat";
        else
            filename = avrname + to_string(int(dataTable->mjdTable[epoch])) + "_" + to_string(epoch+1) + "_spectrum.dat";
        ofstream plik;
        plik.open(filename);
        plik << "# chan vel I er V er LHC er RHC er" << endl;
        plik << fixed << setprecision(11) << "# freq: " << freqlst[epoch] << "   epoch: " << dataTable->mjdTable[epoch] << endl;
        for (unsigned long int ee = 0; ee < dataTable->channelTable[epoch].size(); ee++)
        {
            plik << fixed << setprecision(11) << dataTable->channelTable[epoch][ee] << "   " <<  dataTable->velocityTable[epoch][ee] << "   " << dataTable->spectraTableI[epoch][ee] << "   " << dataTable->spectraTableIERR[epoch] << "   " << dataTable->spectraTableV[epoch][ee] <<  "   " << dataTable->spectraTableVERR[epoch] <<  "   " << dataTable->spectraTableLHC[epoch][ee] <<  "   " << dataTable->spectraTableLHCERR[epoch] <<  "   " << dataTable->spectraTableRHC[epoch][ee] <<  "   " << dataTable->spectraTableRHCERR[epoch] << endl;
        }
        plik.close();

        // -- zwiększamy postęp paska postępu --
        postep.setValue(postep.value()+1);
        // -- coś tam robi, ale z tym też na wndowsie działa także... --
        QCoreApplication::processEvents();


    }

    // -- piszemy odpowiednie powiadomienie --
    string message;
    // - do zamiany intów na takie majtki -
    stringstream ss;
    ss << count_for_gnuplot;
    // - zapisujemy wiadomość -
    message = "Saved all " +  ss.str() + " spectra to " + working_directory;
    // - wyświetlamy -
    QMessageBox::information(&window, tr("Message to you!"), QString::fromStdString(message));
}


// -- ustala, który z przycisków I V LHC RHC na widmie dynamicznym powinien być wciśnięty --
void body::set_down_IVLHCRHCbuttons()
{
    // -- buttony i boole --
    if(I_pressed == 1)
    {
        Ibut->setDown(true);
        LHCbut->setDown(false);
        RHCbut->setDown(false);
        Vbut->setDown(false);
    }
    else if (lhc_pressed == 1)
    {
        Ibut->setDown(false);
        LHCbut->setDown(true);
        RHCbut->setDown(false);
        Vbut->setDown(false);
    }
    else if(rhc_pressed == 1)
    {
        Ibut->setDown(false);
        LHCbut->setDown(false);
        RHCbut->setDown(true);
        Vbut->setDown(false);
    }
    else if(v_pressed == 1)
    {
        Ibut->setDown(false);
        LHCbut->setDown(false);
        RHCbut->setDown(false);
        Vbut->setDown(true);
    }

    window.show();
}

// -- wyświetla layout do integrate (przyciski i text edity z numerami kanałów)
void body::calculate_integrate_for_time_series_with_buttons()
{
    // ----------------------------------------------
    // - poczatkowe moduly, obslugujace standardowe sytuacje -
    // - gdy sekcja jest juz otwarta -
    if (integrate_window_opened == 1)
        return;

    // - gdy dane nie sa zaladowane -
    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    // - gdy otwarta jest inna sekcja -
    if (wd_section_opened == 1 || calibration_section_opened == 1 || spind_window_opened == 1 || aver_over_time_window_opened == 1 || aver_over_velocity_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }
    // ---------------------------------------------

    // ---------------------------------------------
    // -- setup sekcji, potrzebny przy kazdym wywolaniu --
    // - gdy otwarte jest widmo dynamiczne, zapełniamy text edity od razu zasiegiem tegoż -
    if(dynamic_spectrum_opened == 1)
    {
        starting_channel_int->setText(QString::fromStdString(to_string(min_range_vel_index+1)));
        ending_channel_int->setText((QString::fromStdString(to_string(max_range_vel_index+1))));
    }

    // - ustawiamy boola na True -
    integrate_window_opened = 1;

    // - dodajemy widget do glownego vboxa -
    vbox_main.addWidget(integrate_widget);

    // - pokazujemy widget -
    integrate_widget->setVisible(true);
    // -----------------------------------------------
}

// -- zamyka poprzedni layout --
void body::close_window_for_integrate()
{
    // -- znikamy widget --
    integrate_widget->setVisible(false);
    // -- odpinamy od vboxa --
    vbox_main.removeWidget(integrate_widget);
    // -- ustawiamy boola na 0 --
    integrate_window_opened = 0;
}

// -- layout do liczenia VI FI i chi2red --
void body::calculate_spectral_index_for_time_series_with_buttons()
{
    if (spind_window_opened == 1)
        return;

    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (wd_section_opened == 1 || calibration_section_opened == 1 || integrate_window_opened == 1 || aver_over_time_window_opened == 1 || aver_over_velocity_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }

    // setujemy epoki
    starting_channel_spi->setText(QString::fromStdString(to_string(1)));
    ending_channel_spi->setText(QString::fromStdString(to_string(dataTable->spectraTableI.size())));

    // - przypinamy do vboxa -
    vbox_main.addWidget(aver_over_spi_widget);

    // - pokazujemy -
    aver_over_spi_widget->setVisible(true);

    // - ustawiamy boola -
    spind_window_opened = 1;
}

// -- zamyka layout do liczenia VI FI i chi2red --
void body::close_window_for_spind()
{
    // - znikamy widget -
    aver_over_spi_widget->setVisible(false);

    // - odpinamy od vboxa -
    vbox_main.removeWidget(aver_over_spi_widget);

    // - usrtawiamy boola -
    spind_window_opened = 0;
}

// -- layout do liczenia średniej po prędkościach --
void body::calculate_aver_over_velocity_for_time_series_with_buttons()
{
    // ---------------------------------------------
    // - standardwoe procedury dla znanych zdarzeń -
    // jeśli okno jest już otwarte
    if (aver_over_velocity_window_opened == 1)
        return;

    // jeśli dane nie są załadowane
    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }

    // jeśli jest otwarta inna sekcja
    if (wd_section_opened == 1 || calibration_section_opened == 1 || integrate_window_opened == 1 || aver_over_time_window_opened == 1 || spind_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }
    // -----------------------------------------------

    // -----------------------------------------------
    // - używane przy każdym otwarciu sekcji -
    // jeśli otwarte jest widmo dynamiczne, ustal text edity na granice tegoż
    if(dynamic_spectrum_opened == 1)
    {
        starting_channel_aov->setText(QString::fromStdString(to_string(min_range_vel_index+1)));
        ending_channel_aov->setText((QString::fromStdString(to_string(max_range_vel_index+1))));
    }

    // - ustawiamy boola, informującego o otwarciu sekcji -
    aver_over_velocity_window_opened = 1;

    // - przypinamy do vboxa -
    vbox_main.addWidget(aver_over_vel_widget);

    // - pokazujemy -
    aver_over_vel_widget->setVisible(true);
}

// -- zamyka layout do liczenia średniej po prędkościach --
void body::close_window_for_aver_over_velocity()
{
    // - znikamy widget -
    aver_over_vel_widget->setVisible(false);
    // - odpinamy od vboxa -
    vbox_main.removeWidget(aver_over_vel_widget);
    // - ustalamy boola -
    aver_over_velocity_window_opened = 0;
}

// -- layout do liczenia średniej po czasie --
void body::calculate_aver_over_time_for_time_series_with_buttons()
{
    if (aver_over_time_window_opened == 1)
        return;

    if (loaded_data == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, load data first!"));
        return;
    }
    if (wd_section_opened == 1 || calibration_section_opened == 1 || integrate_window_opened == 1 || spind_window_opened == 1 || aver_over_velocity_window_opened == 1)
    {
        QMessageBox::information(&window, tr("Error!"), tr("Please, close previous window"));
        return;
    }

    // ustalamy epoki na pierwszą i ostatnią
    starting_channel_time->setText(QString::fromStdString(to_string(1)));
    ending_channel_time->setText(QString::fromStdString(to_string(dataTable->spectraTableI.size())));

    // ustalamy boola
    aver_over_time_window_opened = 1;

    // - przypinamy do vboxa -
    vbox_main.addWidget(aver_over_time_widget);

    // - pokazujemy -
    aver_over_time_widget->setVisible(true);
}

// -- zamyka layout do liczenia średniej po czasie --
void body::close_window_for_aver_over_time()
{
    // - znikamy -
    aver_over_time_widget->setVisible(false);

    // - odpinamy od vboxa -
    vbox_main.removeWidget(aver_over_time_widget);

    // - zmieniamy boola -
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

// -- eksportuje krzywą blasku z zaznaczenia na widmie dynamicznym --
void body::make_lcs_slot()
{
    int min, max;
    min = yind + 1;
    max = yind + 1;

    dataTable->averageOverVelocity4Pols(min, max, include_pytime->isChecked());

    string message = "";
    message = "Created lc over channel " + to_string(min) + "\n" + "Saved to " + dataTable->getAverOverVelFileName(min, max);
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

// -- rotuje widmo o zadaną ilość kanałów --
void body::rotate_slot_plus()
{
    // czytamy z pola tekstowego, ile kanałów mamy przerotować
    read_number_of_rotated_channels();
    // assignujemy to do zmiennej
    int ch = number_of_rotated_channels; // liczba kanalow
    int rotated_epoch = xind; // epoka rotowania

    string rotated_filename=dataTable->fileNamesTab[rotated_epoch]; // nazwa pliku, ktorego obserwacje rotujemy

    // -- rotowanie wlasciwe --
    vector < double > tmpi;
    vector < double > tmplhc;
    vector < double > tmprhc;
    vector < double > tmpv;

    // -- dajemy warunek, czy checkbox jest zaznaczony --
    if (rotate_all_pols->isChecked())
    {
        for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
        {
            if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
            {
                tmpi.push_back(dataTable->spectraTableI[rotated_epoch][ch+i]);
                tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][ch+i]);
                tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][ch+i]);
                tmpv.push_back(dataTable->spectraTableV[rotated_epoch][ch+i]);
            }
            else
            {
                tmpi.push_back(dataTable->spectraTableI[rotated_epoch][(ch+i)-dataTable->spectraTableI[rotated_epoch].size()]);
                tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][(ch+i)-dataTable->spectraTableRHC[rotated_epoch].size()]);
                tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][(ch+i)-dataTable->spectraTableLHC[rotated_epoch].size()]);
                tmpv.push_back(dataTable->spectraTableV[rotated_epoch][(ch+i)-dataTable->spectraTableV[rotated_epoch].size()]);
            }
         }

        for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
        {
            dataTable->spectraTableI[rotated_epoch][i] = tmpi[i];
            dataTable->spectraTableLHC[rotated_epoch][i] = tmplhc[i];
            dataTable->spectraTableV[rotated_epoch][i] = tmpv[i];
            dataTable->spectraTableRHC[rotated_epoch][i] = tmprhc[i];
        }
    }
    else
    {
        if (I_pressed==1)
        {
            for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
                {
                    tmpi.push_back(dataTable->spectraTableI[rotated_epoch][ch+i]);
                }
                else
                {
                    tmpi.push_back(dataTable->spectraTableI[rotated_epoch][(ch+i)-dataTable->spectraTableI[rotated_epoch].size()]);
                }
             }

            for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                dataTable->spectraTableI[rotated_epoch][i] = tmpi[i];
            }
        }
        else if (v_pressed == 1)
        {
            for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
                {
                    tmpv.push_back(dataTable->spectraTableV[rotated_epoch][ch+i]);
                }
                else
                {
                    tmpv.push_back(dataTable->spectraTableV[rotated_epoch][(ch+i)-dataTable->spectraTableV[rotated_epoch].size()]);
                }
            }

            for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                dataTable->spectraTableV[rotated_epoch][i] = tmpv[i];
            }
        }
        else if (lhc_pressed == 1)
        {
            for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
                {
                    tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][ch+i]);
                }
                else
                {
                    tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][(ch+i)-dataTable->spectraTableRHC[rotated_epoch].size()]);
                }
            }

            for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                dataTable->spectraTableLHC[rotated_epoch][i] = tmplhc[i];
            }
        }
        else if (rhc_pressed == 1)
        {
            for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
                {
                    tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][ch+i]);
                }
                else
                {
                    tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][(ch+i)-dataTable->spectraTableLHC[rotated_epoch].size()]);
                }
            }

            for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                dataTable->spectraTableRHC[rotated_epoch][i] = tmprhc[i];
            }
        }
    }

    // aktualizujemy widmo dynamiczne
    update_dynamic_spectrum();
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
    int ch = dataTable->spectraTableI[rotated_epoch].size() - number_of_rotated_channels;
    string rotated_filename=dataTable->fileNamesTab[rotated_epoch]; // nazwa pliku, ktorego obserwacje rotujemy

    // -- rotowanie wlasciwe --
    vector < double > tmpi;
    vector < double > tmplhc;
    vector < double > tmprhc;
    vector < double > tmpv;

    /*
    for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
    {
        if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
        {
            tmpi.push_back(dataTable->spectraTableI[rotated_epoch][ch+i]);
            tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][ch+i]);
            tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][ch+i]);
            tmpv.push_back(dataTable->spectraTableV[rotated_epoch][ch+i]);
        }
        else
        {
            tmpi.push_back(dataTable->spectraTableI[rotated_epoch][(ch+i)-dataTable->spectraTableI[rotated_epoch].size()]);
            tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][(ch+i)-dataTable->spectraTableRHC[rotated_epoch].size()]);
            tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][(ch+i)-dataTable->spectraTableLHC[rotated_epoch].size()]);
            tmpv.push_back(dataTable->spectraTableV[rotated_epoch][(ch+i)-dataTable->spectraTableV[rotated_epoch].size()]);
        }
        }

    for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
    {
        dataTable->spectraTableI[rotated_epoch][i] = tmpi[i];
        dataTable->spectraTableLHC[rotated_epoch][i] = tmplhc[i];
        dataTable->spectraTableV[rotated_epoch][i] = tmpv[i];
        dataTable->spectraTableRHC[rotated_epoch][i] = tmprhc[i];
    }
    */

    // -- dajemy warunek, czy checkbox jest zaznaczony --
    if (rotate_all_pols->isChecked())
    {
        for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
        {
            if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
            {
                tmpi.push_back(dataTable->spectraTableI[rotated_epoch][ch+i]);
                tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][ch+i]);
                tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][ch+i]);
                tmpv.push_back(dataTable->spectraTableV[rotated_epoch][ch+i]);
            }
            else
            {
                tmpi.push_back(dataTable->spectraTableI[rotated_epoch][(ch+i)-dataTable->spectraTableI[rotated_epoch].size()]);
                tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][(ch+i)-dataTable->spectraTableRHC[rotated_epoch].size()]);
                tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][(ch+i)-dataTable->spectraTableLHC[rotated_epoch].size()]);
                tmpv.push_back(dataTable->spectraTableV[rotated_epoch][(ch+i)-dataTable->spectraTableV[rotated_epoch].size()]);
            }
         }

        for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
        {
            dataTable->spectraTableI[rotated_epoch][i] = tmpi[i];
            dataTable->spectraTableLHC[rotated_epoch][i] = tmplhc[i];
            dataTable->spectraTableV[rotated_epoch][i] = tmpv[i];
            dataTable->spectraTableRHC[rotated_epoch][i] = tmprhc[i];
        }
    }
    else
    {
        if (I_pressed==1)
        {
            for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
                {
                    tmpi.push_back(dataTable->spectraTableI[rotated_epoch][ch+i]);
                }
                else
                {
                    tmpi.push_back(dataTable->spectraTableI[rotated_epoch][(ch+i)-dataTable->spectraTableI[rotated_epoch].size()]);
                }
             }

            for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                dataTable->spectraTableI[rotated_epoch][i] = tmpi[i];
            }
        }
        else if (v_pressed == 1)
        {
            for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
                {
                    tmpv.push_back(dataTable->spectraTableV[rotated_epoch][ch+i]);
                }
                else
                {
                    tmpv.push_back(dataTable->spectraTableV[rotated_epoch][(ch+i)-dataTable->spectraTableV[rotated_epoch].size()]);
                }
            }

            for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                dataTable->spectraTableV[rotated_epoch][i] = tmpv[i];
            }
        }
        else if (lhc_pressed == 1)
        {
            for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
                {
                    tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][ch+i]);
                }
                else
                {
                    tmplhc.push_back(dataTable->spectraTableLHC[rotated_epoch][(ch+i)-dataTable->spectraTableRHC[rotated_epoch].size()]);
                }
            }

            for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                dataTable->spectraTableLHC[rotated_epoch][i] = tmplhc[i];
            }
        }
        else if (rhc_pressed == 1)
        {
            for (int i = 0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                if (ch+i < dataTable->spectraTableI[rotated_epoch].size())
                {
                    tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][ch+i]);
                }
                else
                {
                    tmprhc.push_back(dataTable->spectraTableRHC[rotated_epoch][(ch+i)-dataTable->spectraTableLHC[rotated_epoch].size()]);
                }
            }

            for (int i=0; i < dataTable->spectraTableI[rotated_epoch].size(); i++)
            {
                dataTable->spectraTableRHC[rotated_epoch][i] = tmprhc[i];
            }
        }
    }

    // aktualizujemy widmo dynamiczne
    update_dynamic_spectrum();
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

// -- pomocnicza metoda do "save rotated spectras" --
vector < string >  body::save_edited_avr(int epoch)
{
    // -- blok tymczasowych zmiennych --
    string filename; // tymczasowa zmienna, będzie przechowywać nazwę pliku edytowanego
    string headere; // tymczasowa zmienna, będzie przechowywać nagłówek AVR
    vector < double > is,v,lhc,rhc; // tymczasowe kontenery, będą przechowywać polaryzacje etc.
    string output_filename; // nazwa pliku, do którego zapisany będzie backup
    // -- kontener, za pomocą którego zwracamy nazwy plików --
    vector < string > returned_filenames(2);
    // -- kopiowanie plikow --
    ofstream cp_destination_rot; // obiekt pliku, do którego będziemy kopiować
    ifstream copied_file; // obiekt pliku, używany do robienia backapu

    // -- czytamy nazwę pliku, który będzie obrabiany --
    filename = dataTable->fileNamesTab[epoch];
    // czytamy jego header, który nie będzie konstruowany od nowa
    headere = headerlst[epoch];
    output_filename = filename; // jest to nazwa pliku, do ktorego skopiowane zostana dane sprzed edycji
    output_filename.erase(output_filename.end()-7, output_filename.end());
    output_filename = output_filename + "noedt.DAT";

    // -- zapelniamy tymczasowe tablice --
    for (unsigned long int ee = 0; ee < dataTable->spectraTableI[epoch].size(); ee++)
    {
        is.push_back(dataTable->spectraTableI[epoch][ee]);
        v.push_back(dataTable->spectraTableV[epoch][ee]);
        lhc.push_back(dataTable->spectraTableLHC[epoch][ee]);
        rhc.push_back(dataTable->spectraTableRHC[epoch][ee]);
    }

    // -- kopiujemy do backupowego file --
    // tutaj ify są potrzebne z prostego względu:
    // program wspiera wczytywanie zarówno z podanej listy plików, jak i czyta plku wybierane w selectorze ręcznie
    // w pierwszym przypadku, w kontenerze "dataTable->fileNamesTab" będą tylko nazwy plików
    // w drugim - całkowite absolutne ścieżki
    // dlatego chcemy być konsekwentni i w każdym wypadku podajemy absolutną ścieżkę do plików
    // w przypadku załadowania listy, ścieżka do niej jest przetrzymywana w zmiennej "working directory"
    if (loaded_from_listfile == 1)
    {
        // otwiera plik, do którego robimy backupa
        cp_destination_rot.open((working_directory + "/" + output_filename).c_str(), std::ios::binary);
        // otwiera plik, z którego robimy backupa
        copied_file.open((working_directory + "/" + filename).c_str(), std::ios::binary);
        // zapisujemy drugie do pierwszego za pomocą strumienia
        cp_destination_rot << copied_file.rdbuf();
        // zamykamy plik z backupem
        cp_destination_rot.close();
        // zamykamy plik, z którego robimy backupa
        copied_file.close();
        // przywołujemy metodę, która zapisze do pliku AVR
        save_avr_file(working_directory + "/" + filename, headere, is,v,lhc,rhc);
        // ustalamy, co zwróci nasza metoda
        returned_filenames[0] = working_directory + "/" + output_filename;
        returned_filenames[1] = working_directory + "/" + filename;

    }
    else
    {
        // otwiera plik, do którego robimy backupa
        cp_destination_rot.open((output_filename).c_str(), std::ios::binary);
        // otwiera plik, z którego robimy backupa
        copied_file.open(filename.c_str(), std::ios::binary);
        // zapisujemy drugie do pierwszego za pomocą strumienia
        cp_destination_rot << copied_file.rdbuf();
        // zamykamy plik z backupem
        cp_destination_rot.close();
        // zamykamy plik, z którego robimy backupa
        copied_file.close();
        // przywołujemy metodę, która zapisze do pliku AVR
        save_avr_file(filename, headere, is,v,lhc,rhc);
        // ustalamy, co zwróci nasza metoda
        returned_filenames[0] = output_filename;
        returned_filenames[1] = filename;
    }

    // -- zwracamy --
    return returned_filenames;
}

// -- pomocnicza metoda do "save rotated spectras" --
// -- zapisuje pliki fits --
vector < string > body::save_edited_fitsfile(int epoch)
{
    // -- blok tymczasowych zmiennych --
    string filename; // tymczasowa zmienna, będzie przechowywać nazwę pliku edytowanego
    vector < double > lhc ( (int) n_chanslst[epoch]), rhc( (int) n_chanslst[epoch]); // tymczasowe kontenery, będą przechowywać polaryzacje etc.
    string output_filename; // nazwa pliku, do którego zapisany będzie backup
    // -- kontener, za pomocą którego zwracamy nazwy plików --
    vector < string > returned_filenames(2);
    // -- kopiowanie plikow --
    ofstream cp_destination_rot; // obiekt pliku, do którego będziemy kopiować
    ifstream copied_file; // obiekt pliku, używany do robienia backapu

    // -- czytamy nazwę pliku, który będzie obrabiany --
    filename = dataTable->fileNamesTab[epoch];
    output_filename = filename; // jest to nazwa pliku, do ktorego skopiowane zostana dane sprzed edycji
    output_filename.erase(output_filename.end()-8, output_filename.end());
    output_filename = output_filename + "noedt.fits";

    // -- zapelniamy tymczasowe tablice --
    // w fitsach przechowujemy tylko LHC i RHC, także tutaj tylko te dwie
    // zapisujemy od tyłu, bo taki jest pomysł RS
    for (unsigned long int ee = 0; ee < dataTable->spectraTableI[epoch].size(); ee++)
    {
        lhc[lhc.size() - 1 - ee] = dataTable->spectraTableLHC[epoch][ee];
        rhc[lhc.size() - 1 - ee] = dataTable->spectraTableRHC[epoch][ee];
        //lhc.push_back(dataTable->spectraTableLHC[epoch][ee]);
        //rhc.push_back(dataTable->spectraTableRHC[epoch][ee]);
    }

    // -- kopiujemy do backupowego file --
    // tutaj ify są potrzebne z prostego względu:
    // program wspiera wczytywanie zarówno z podanej listy plików, jak i czyta plku wybierane w selectorze ręcznie
    // w pierwszym przypadku, w kontenerze "dataTable->fileNamesTab" będą tylko nazwy plików
    // w drugim - całkowite absolutne ścieżki
    // dlatego chcemy być konsekwentni i w każdym wypadku podajemy absolutną ścieżkę do plików
    // w przypadku załadowania listy, ścieżka do niej jest przetrzymywana w zmiennej "working directory"
    if (loaded_from_listfile == 1)
    {
        // otwiera plik, do którego robimy backupa
        cp_destination_rot.open((working_directory + "/" + output_filename).c_str(), std::ios::binary);
        // otwiera plik, z którego robimy backupa
        copied_file.open((working_directory + "/" + filename).c_str(), std::ios::binary);
        // zapisujemy drugie do pierwszego za pomocą strumienia
        cp_destination_rot << copied_file.rdbuf();
        // zamykamy plik z backupem
        cp_destination_rot.close();
        // zamykamy plik, z którego robimy backupa
        copied_file.close();
        // przywołujemy metodę, która zapisze do pliku AVR
        save_new_cols_in_fits_file(working_directory + "/" + filename, lhc, rhc);
        // ustalamy, co zwróci nasza metoda
        returned_filenames[0] = working_directory + "/" + output_filename;
        returned_filenames[1] = working_directory + "/" + filename;

    }
    else
    {
        // otwiera plik, do którego robimy backupa
        cp_destination_rot.open((output_filename).c_str(), std::ios::binary);
        // otwiera plik, z którego robimy backupa
        copied_file.open(filename.c_str(), std::ios::binary);
        // zapisujemy drugie do pierwszego za pomocą strumienia
        cp_destination_rot << copied_file.rdbuf();
        // zamykamy plik z backupem
        cp_destination_rot.close();
        // zamykamy plik, z którego robimy backupa
        copied_file.close();
        // przywołujemy metodę, która zapisze do pliku AVR
        save_new_cols_in_fits_file(working_directory + "/" + filename, lhc, rhc);
        // ustalamy, co zwróci nasza metoda
        returned_filenames[0] = output_filename;
        returned_filenames[1] = filename;
    }

    // -- zwracamy --
    return returned_filenames;
}

// -- zapisuje wszystkie edytowane widma --
void body::save_rotated_spectras()
{
    // -- warunek podstawowy - sprawdza, czy została wykonana jakaś edycja na widmie dynamicznym (w domyśle rotacja albo przeliczenie I/V ) --
    if (made_rotation == 0)
    {
        QMessageBox::information(&window, tr("Error!"), tr("There are no edited spectras, so nothing will be saved"));
        return;
    }

    // -- okno do upewniania sie, ze na pewno chcesz --
    QMessageBox::StandardButton upewka;
    upewka = QMessageBox::question(&window, "Are you sure?", QString::fromStdString("Do you realy want to save edited spectras (non - rotated versions will be stored at *noedt.DAT)?"), QMessageBox::Yes| QMessageBox::No);
    if (upewka == QMessageBox::No)
    {
        // -- jeśli klikniesz nie, nie pójdzie dalej --
        return;
    }

    // -- zmienne --
    int epoch; // epoka, będzie przechowywała w pętli informację, którą obserwację będziemy zapisywać. Jest to czysto pomocnicza zmienna
    string cpy_message = ""; // przechowuje informację, jaki tekst będzie na naszej wiadomości o wykonaniu backupa
    string message = ""; // przechowuje informację, jaki tekst będzie na informacji o tym, jakie pliki zostały edytowane
    message = message + "Saved edited spectra to:\n"; // wiadomix, dajemy pierwszą linię wiadomości (wcześniej było "spectras", mega krindżówa xD)

    // -- tymczasowy kontener ze stringami --
    // funkcje "save edited avr" i "save edited fits" zwracają kontener z dwoma stringami
    // poniższy kontener ma za zadanie je przejmować
    vector < string > tmp_filenames(2);

    // -- zaczynamy petle zapisu --
    for(int i = 0; i < rotated_spectras.size(); i++)
    {
        // -- ustalamy z czym mamy do czynienia --
        epoch = rotated_spectras[i];

        // -- sprawdzamy, czy ten plik to AVR czy fits --
        if (filetype[epoch] == 0)
        {
            // -- jeśli AVR, przywołujemy pomocniczą metodę do zapisu pliku AVR --
            // wykona ona też stosowny backup
            // nazwa pliku po edycji oraz pliku z backupem zostają zwrócone
            // za pomocą konrenera std::vector < string > (2)
            tmp_filenames = save_edited_avr(epoch);
        }
        else
        {
            // -- jeśli fits, to przywołujemy inną metodę --
            // -- ona też powinna wykonać stosowny backup --
            // na chwilę obecną jednak nic nie robi
            // nazwa pliku po edycji oraz pliku z backupem zostają zwrócone
            // za pomocą konrenera std::vector < string > (2)
            tmp_filenames = save_edited_fitsfile(epoch);
        }

        // -- uzupełniamy wiadomość o skopiowanych danych --
        cpy_message = cpy_message + tmp_filenames[1] + " copied to " + tmp_filenames[0] + "\n";
        message = message + tmp_filenames[1] + "\n";

    }

    // -- czyścimy tablicę z rotowanymi widmami --
    rotated_spectras.clear();

    // -- wyświetlamy odpowiednie komunikaty --
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

void body::save_new_cols_in_fits_file(string fitsfilename, vector<double> lhc, vector<double> rhc)
{
    QFile::remove((working_directory + "/" + "tmp_for_fitsedt").c_str());

    // -- otwieramy plik fits --
    FITS fle(fitsfilename.c_str(), Read);
    // -- otwieramy tymczasowy plik fits --
    FITS fle_new(working_directory + "/" + "tmp_for_fitsedt", fle);

    // kopiujemy
    //fle_new.copy(fle.pHDU());
    fle_new.copy(fle.extension(1));

    // podmieniwamy tablice
    fle_new.extension(1).column("Pol 1").write(lhc, 0);
    fle_new.extension(1).column("Pol 2").write(rhc, 0);

    // niszczymy niepotrzebne obiekty
    fle.destroy();
    fle_new.destroy();

    remove(fitsfilename.c_str());
    // kopiujemy tmp do podmienianego pliku
    QFile::copy((working_directory + "/" + "tmp_for_fitsedt").c_str(), fitsfilename.c_str());
    QFile::remove((working_directory + "/" + "tmp_for_fitsedt").c_str());

    // niszczymy tmp
    //fle_new_cpy.remove();


    /*
    // -- czytamy z niego headery
    PHDU & podstawa = fle->pHDU();
    ExtHDU & dane = fle->extension(1);

    // -- podmieniamy tablice na nowe -
    dane.column("Pol 1").write(lhc, 0);
    dane.column("Pol 2").write(rhc, 0);
    */
    // zamykamy plik

    // -- usuwamy ten plik i tworzymy nowy --

    //
    // -- otwieramy plik fits --


    // -- zapisujemy podstawowy header --
    //pHDU().write();
    //Table * newTable = fle->extension(1).column("Pol 1");
}

// -- czyta, ile o ile kanałów ma być przerotowane widmo przy wywołaniu slotu 'rotate()' --
void body::read_number_of_rotated_channels()
{
    // Qstring, do którego zgrywamy tekst z text edit
    QString number_in_string;

    // Zgrywamy text do stringa
    number_in_string = number_of_rotated_channels_texted->toPlainText();

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
    // - standardowa sekcja -
    // -----------------------------------------------------------
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
    // ------------------------------------------------------------


    // ------------------------------------------------------------
    // -- setujemy default na labele --
    if (caltabs_loaded == 0)
    {
        caltab_l1_path->setText(QString::fromStdString("Not loaded!"));
        caltab_r1_path->setText(QString::fromStdString("Not loaded!"));
    }
    else
    {
        caltab_l1_path->setText(QString::fromStdString("Loaded"));
        caltab_r1_path->setText(QString::fromStdString("Loaded"));
    }

    // -- ustawiamy napis na przycisku, w zależności od tego czy kalibrowaliśmy czy nie --
    if (calibration_done == 0)
    {
        start_calibration->setText("Calibrate");
        start_calibration->setDown(false);
    }
    else if (calibration_done == 1)
    {
        start_calibration->setText("Uncalibrate");
        start_calibration->setDown(true);
    }

    // -- dodajemy do vboxa --
    vbox_main.addWidget(calibrate_widget);

    // -- ustawiamy visibility --
    calibrate_widget->setVisible(true);

    // -- ustawiamy boola --
    calibration_section_opened = 1;


}

void body::close_cal_layout()
{
    // -- znikamy --
    calibrate_widget->setVisible(false);

    // -- odpinamy od vboxa --
    vbox_main.removeWidget(calibrate_widget);

    // -- ustawiamy boola --
    calibration_section_opened = 0;
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

            double our_epoch = dataTable->mjdTable[epoch_number] - 50000.0;

            // -- interpolacja --
            double slope = (coef2 - coef1) / (epoch2 - epoch1);
            double days_passed = our_epoch - epoch1;
            cal_coef_lhc = coef1+ slope * days_passed;

            //cout <<"[" << dataTable->mjdTable[epoch_number] << "]: "<<"Found LHC coef: interpolating between " << epoch1 << ", " << coef1 << " and " << epoch2 << ", " << coef2 << ", coef value: " << cal_coef_lhc << endl;
        }
    }
    else if (index_of_cal_lhc >=0)
    {
        cal_coef_lhc = CALTAB_L1[index_of_cal_lhc];
        //cout <<"[" << dataTable->mjdTable[epoch_number] << "]: " << "Found LHC coef:  " <<  CALTAB_L1[index_of_cal_lhc] << endl;
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

            double our_epoch = dataTable->mjdTable[epoch_number] - 50000.0;

            // -- interpolacja --
            double slope = (coef2 - coef1) / (epoch2 - epoch1);
            double days_passed = our_epoch - epoch1;
            cal_coef_rhc = coef1 + slope * days_passed;

            //cout <<"[" << dataTable->mjdTable[epoch_number] << "]: " << "Found RHC coef: interpolating between " << epoch1 << ", " << coef1 << " and " << epoch2 << ", " << coef2 << ", coef value: " << cal_coef_lhc << endl;
        }
    }
    else if (index_of_cal_rhc >=0)
    {
        cal_coef_rhc = CALTAB_R1[index_of_cal_rhc];
        //cout <<"[" << dataTable->mjdTable[epoch_number] << "]: " << "Found RHC coef:  " <<  CALTAB_R1[index_of_cal_lhc] << endl;
    }

    vector < double > returning_values;
    returning_values.push_back(cal_coef_lhc);
    returning_values.push_back(cal_coef_rhc);
    return returning_values;
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

    lhc_loaded = 1;
    caltab_l1_path->setText(QString::fromStdString("Loaded"));
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

    rhc_loaded = 1;
    caltab_r1_path->setText(QString::fromStdString("Loaded"));
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
    for(int i = 0; i < dataTable->mjdTable.size(); i++)
    {
       tmp_calibrate = calibrate_single(i);
       calcoefs_lhc.push_back(tmp_calibrate[0]);
       calcoefs_rhc.push_back(tmp_calibrate[1]);
    }

    if (calibration_done == 0)
    {
        for(int i = 0; i < dataTable->spectraTableLHC.size(); i++)
        {
            for (int k=0; k< dataTable->spectraTableLHC[i].size(); k++)
            {
                dataTable->spectraTableLHC[i][k] = calcoefs_lhc[i] * dataTable->spectraTableLHC[i][k];
                dataTable->spectraTableLHCERR[i] = calcoefs_lhc[i] * dataTable->spectraTableLHCERR[i];
            }
        }

        for(int i = 0; i < dataTable->spectraTableRHC.size(); i++)
        {
            for (int k=0; k< dataTable->spectraTableRHC[i].size(); k++)
            {
                dataTable->spectraTableRHC[i][k] = calcoefs_rhc[i] * dataTable->spectraTableRHC[i][k];
                dataTable->spectraTableRHCERR[i] = calcoefs_rhc[i] * dataTable->spectraTableRHCERR[i];
            }
        }

        for(int i = 0; i < dataTable->spectraTableI.size(); i++)
        {
            for (int k=0; k< dataTable->spectraTableI[i].size(); k++)
            {
                dataTable->spectraTableI[i][k] = (dataTable->spectraTableRHC[i][k] + dataTable->spectraTableLHC[i][k]) / 2.0;
                dataTable->spectraTableIERR[i] = (dataTable->spectraTableRHCERR[i] + dataTable->spectraTableLHCERR[i]) / 2.0;
            }
        }

        for(int i = 0; i < dataTable->spectraTableV.size(); i++)
        {
            for (int k=0; k< dataTable->spectraTableV[i].size(); k++)
            {
                dataTable->spectraTableV[i][k] = (dataTable->spectraTableRHC[i][k] - dataTable->spectraTableLHC[i][k]) / 2.0;
                dataTable->spectraTableVERR[i] = (dataTable->spectraTableRHCERR[i] - dataTable->spectraTableLHCERR[i]) / 2.0;
            }
        }
        // - liczymy sredni rms -
        calculate_mean_rms();
        //QMessageBox::information(&window, tr("Message"), tr("Calibration done"));
        if (dynamic_spectrum_opened == 1)
        {
            update_dynamic_spectrum();
        }
        else if (rms_section_opened == 1)
        {
            set_plot_on_rms_vs_time();
            set_plot_on_int_vs_time();
            show_points_or_lines();
            selection_point_on_rms_slot_for_graph_visibility();
            select_on_rms_section(dataTable->mjdTable[xind]);
            //set_plot_on_tsys_vs_time();
        }
        //calibrate_single(23);
        calibration_done = 1;
        start_calibration->setDown(true);
        start_calibration->setText("Uncalibrate");
    }
    else if (calibration_done == 1)
    {
        for(int i = 0; i < dataTable->spectraTableLHC.size(); i++)
        {
            for (int k=0; k< dataTable->spectraTableLHC[i].size(); k++)
            {
                dataTable->spectraTableLHC[i][k] =  dataTable->spectraTableLHC[i][k] / calcoefs_lhc[i];
                dataTable->spectraTableLHCERR[i] = dataTable->spectraTableLHCERR[i] / calcoefs_lhc[i];
            }
        }

        for(int i = 0; i < dataTable->spectraTableRHC.size(); i++)
        {
            for (int k=0; k< dataTable->spectraTableRHC[i].size(); k++)
            {
                dataTable->spectraTableRHC[i][k] = dataTable->spectraTableRHC[i][k] / calcoefs_rhc[i];
                dataTable->spectraTableRHCERR[i] = dataTable->spectraTableRHCERR[i] / calcoefs_rhc[i];
            }
        }

        for(int i = 0; i < dataTable->spectraTableRHC.size(); i++)
        {
            for (int k=0; k< dataTable->spectraTableRHC[i].size(); k++)
            {
                dataTable->spectraTableI[i][k] = (dataTable->spectraTableRHC[i][k] + dataTable->spectraTableLHC[i][k]) / 2.0;
                dataTable->spectraTableIERR[i] = (dataTable->spectraTableRHCERR[i] + dataTable->spectraTableLHCERR[i]) / 2.0;
            }
        }

        for(int i = 0; i < dataTable->spectraTableV.size(); i++)
        {
            for (int k=0; k< dataTable->spectraTableV[i].size(); k++)
            {
                dataTable->spectraTableV[i][k] = (dataTable->spectraTableRHC[i][k] - dataTable->spectraTableLHC[i][k]) / 2.0;
                dataTable->spectraTableVERR[i] = (dataTable->spectraTableRHCERR[i] - dataTable->spectraTableLHCERR[i]) / 2.0;
            }
        }

        // - liczymy sredni rms -
        calculate_mean_rms();
        //QMessageBox::information(&window, tr("Message"), tr("Calibration undone"));
        if (dynamic_spectrum_opened == 1)
        {
            update_dynamic_spectrum();
        }
        else if (rms_section_opened == 1)
        {
            set_plot_on_rms_vs_time();
            set_plot_on_int_vs_time();
            show_points_or_lines();
            selection_point_on_rms_slot_for_graph_visibility();
            select_on_rms_section(dataTable->mjdTable[xind]);
            //set_plot_on_tsys_vs_time();
        }
        //calibrate_single(23);
        calibration_done = 0;
        start_calibration->setDown(false);
        start_calibration->setText("Calibrate");
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
    int epoch = int(dataTable->mjdTable[index_of_epoch] - 50000.0);

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
    int epoch = int(dataTable->mjdTable[index_of_epoch] - 50000.0);

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
    int epoch = int(dataTable->mjdTable[index_of_epoch] - 50000.0);

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
    QPen graph_dark;
    graph_dark.setColor(QColor(135,206,250));
    graph_dark.setWidth(2);

    QPen graph_light;
    graph_light.setColor(QColor(0,0,255));
    graph_light.setWidth(2);

    // - ustawiamy informacje na color mapie -
    colorMap->data()->clear();
    dynamic_spectrum_pl.layer("pixmap");
    colorMap->data()->setSize(rozmiar_w_x, rozmiar_w_y);
    if (rozmiar_w_x == 1)
        colorMap->data()->setRange(QCPRange(min_obs_number-0.5, max_obs_number+0.5), QCPRange(dataTable->velocityTable[0][min_range_vel_index], dataTable->velocityTable[0][max_range_vel_index]-(dataTable->velocityTable[0][2]-dataTable->velocityTable[0][1])));
    else
        colorMap->data()->setRange(QCPRange(min_obs_number, max_obs_number), QCPRange(dataTable->velocityTable[0][min_range_vel_index], dataTable->velocityTable[0][max_range_vel_index]-(dataTable->velocityTable[0][2]-dataTable->velocityTable[0][1])));

    if(I_pressed == 1)
    {
        for (int xIndex = 0; xIndex < rozmiar_w_x; xIndex++)
        {
            for (int yIndex = 0; yIndex < rozmiar_w_y; yIndex++)
            {
                if (dataTable->spectraTableI[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, dataTable->spectraTableI[min_obs_number+xIndex][min_range_vel_index+yIndex]);
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
                if (dataTable->spectraTableV[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, dataTable->spectraTableV[min_obs_number+xIndex][min_range_vel_index+yIndex]);
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
                if (dataTable->spectraTableLHC[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, dataTable->spectraTableLHC[min_obs_number+xIndex][min_range_vel_index+yIndex]);
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
                if (dataTable->spectraTableRHC[min_obs_number+xIndex][min_range_vel_index+yIndex] >= 0.0)
                    colorMap->data()->setCell(xIndex,yIndex, dataTable->spectraTableRHC[min_obs_number+xIndex][min_range_vel_index+yIndex]);
                else
                    colorMap->data()->setCell(xIndex,yIndex, 0.0);
            }
        }
    }

    dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap -> setGradient(gradient);
    //colorMap -> rescaleDataRange(true);
    colorMap->data()->recalculateDataBounds();
    colorMap -> rescaleKeyAxis(true);
    colorMap -> rescaleValueAxis(true);
    //dynamic_spectrum_pl.axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);

    if (set_log_scale->isChecked())
    {
        double dno = 0.0;
        if(I_pressed == 1)
        {
            dno = mean_rms_I;
        }
        else if (v_pressed == 1)
        {
            dno = mean_rms_V;
        }
        else if (lhc_pressed == 1)
        {
            dno = mean_rms_LHC;
        }
        else
        {
            dno = mean_rms_RHC;
        }

        if (dno <= 0.0)
        {
            dno = 0.0001; // zabezpieczamy się przed dolną skalą < 0
        }
        QCPRange zasieg(dno, colorMap->data()->dataBounds().upper);
        colorbar->setDataRange(zasieg);
    }
    else
    {
        colorMap->rescaleDataRange();
    }
    //colorbar->setDataRange(colorMap->dataRange());
    colorbar_widget->replot();
    dynamic_spectrum_pl.rescaleAxes();
    dynamic_spectrum_pl.replot();


    // -- twotzymy widmo, ktore wyswietli sie po kliknieciu w widmo dynamiczne --
    // - warunki ze wzgledu na przyciski polaryzacji -
    QVector < double > velocity(rozmiar_w_y), flux(rozmiar_w_y);

    if (I_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = dataTable->velocityTable[xind][min_range_vel_index+i];
        flux[i] = dataTable->spectraTableI[xind][min_range_vel_index+i];
    }
    }

    else if (v_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = dataTable->velocityTable[xind][min_range_vel_index+i];
        flux[i] = dataTable->spectraTableV[xind][min_range_vel_index+i];
    }
    }
    else if (lhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = dataTable->velocityTable[xind][min_range_vel_index+i];
        flux[i] = dataTable->spectraTableLHC[xind][min_range_vel_index+i];
    }
    }
    else if (rhc_pressed == 1)
    {
    for (int i = 0; i < rozmiar_w_y; i++)
    {
        //cout << "i: " << i << "max: " << max_range_vel_index << endl;
        velocity[i] = dataTable->velocityTable[xind][min_range_vel_index+i];
        flux[i] = dataTable->spectraTableRHC[xind][min_range_vel_index+i];
    }
    }

    single_dynamic_spectrum.graph(0)->setData(velocity,flux);

    single_dynamic_spectrum.xAxis->setLabel("Vel");
    single_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    double veldiff = *max_element(velocity.begin(), velocity.end()) - *min_element(velocity.begin(), velocity.end());
    single_dynamic_spectrum.xAxis->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));
    single_dynamic_spectrum.xAxis2->setRange(*min_element(velocity.begin(), velocity.end()) - 0.05 * veldiff, *max_element(velocity.begin(), velocity.end())  + 0.05 * veldiff);
    single_dynamic_spectrum.yAxis2->setRange(*min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end())), *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end())));

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
    x_vline[0] = dataTable->velocityTable[xind][yind];
    x_vline[1] = dataTable->velocityTable[xind][yind];
    y_vline[0] = *min_element(flux.begin(), flux.end()) - 0.05 * (*max_element(flux.begin(), flux.end()));
    y_vline[1] = *max_element(flux.begin(), flux.end())  + 0.05 * (*max_element(flux.begin(), flux.end()));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    QPen pen2;
    pen2.setColor(QColor(182,26,26));
    single_dynamic_spectrum.graph(1)->setData(x_vline, y_vline);
    single_dynamic_spectrum.graph(1)->setPen(pen2);

    // -- tworzymy krzywa blasku, ktora wyswietli sie w krzywej blasku --
    QVector < double > epoch(rozmiar_w_x), lcs_flux(rozmiar_w_x), error_lcs(rozmiar_w_x);
    if(I_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = dataTable->mjdTable[min_obs_number + i];
        lcs_flux[i] = dataTable->spectraTableI[min_obs_number + i][yind];
        error_lcs[i] = dataTable->spectraTableIERR[min_obs_number + i];
    }
    }

    else if(v_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = dataTable->mjdTable[min_obs_number + i];
        lcs_flux[i] = dataTable->spectraTableV[min_obs_number + i][yind];
        error_lcs[i] = dataTable->spectraTableVERR[min_obs_number + i];
    }
    }

    else if(lhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = dataTable->mjdTable[min_obs_number + i];
        lcs_flux[i] = dataTable->spectraTableLHC[min_obs_number + i][yind];
        error_lcs[i] = dataTable->spectraTableLHCERR[min_obs_number + i];
    }
    }

    else if(rhc_pressed==1)
    {
    for (int i = 0; i < rozmiar_w_x; i++)
    {
        epoch[i] = dataTable->mjdTable[min_obs_number + i];
        lcs_flux[i] = dataTable->spectraTableRHC[min_obs_number + i][yind];
        error_lcs[i] = dataTable->spectraTableRHCERR[min_obs_number + i];
    }
    }
    //cout << epoch[0] << endl;

    errorBars->setAntialiased(false);
    errorBars->setDataPlottable(lcs_dynamic_spectrum.graph(0));
    if(!dark_mode_switch->isChecked())
        errorBars->setPen(QPen(QColor(180,180,180)));
    else
        errorBars->setPen(QPen(QColor(105,105,105)));

    lcs_dynamic_spectrum.graph(0)->setData(epoch,lcs_flux);
    errorBars->setData(error_lcs);

    //lcs_dynamic_spectrum.graph(0)->setPen(QPen(Qt::blue));
    lcs_dynamic_spectrum.graph(0)->setLineStyle(QCPGraph::lsNone);
    lcs_dynamic_spectrum.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 4));
    lcs_dynamic_spectrum.xAxis->setLabel("MJD");
    lcs_dynamic_spectrum.yAxis->setLabel("Flux density (Jy)");
    if(rozmiar_w_x == 1)
    {
        lcs_dynamic_spectrum.rescaleAxes();
    }
    else
    {
        double diffrence = *max_element(epoch.begin(), epoch.end()) - *min_element(epoch.begin(), epoch.end());
        lcs_dynamic_spectrum.xAxis->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
        lcs_dynamic_spectrum.yAxis->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
        lcs_dynamic_spectrum.xAxis2->setRange(*min_element(epoch.begin(), epoch.end()) - 0.05 * diffrence, *max_element(epoch.begin(), epoch.end())  + 0.05 * diffrence);
        lcs_dynamic_spectrum.yAxis2->setRange(*min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())), *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end())));
    }
    // -- pokazujemy ticki na gornej osi --
    lcs_dynamic_spectrum.xAxis2->setVisible(true);
    lcs_dynamic_spectrum.yAxis2->setVisible(true);
    lcs_dynamic_spectrum.xAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.yAxis2->setTickLabels(false);
    lcs_dynamic_spectrum.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    if (lcs_line_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        lcs_line_added = 1;
    }
    QVector < double > lcsx_vline(2), lcsy_vline(2);
    lcsx_vline[0] = dataTable->mjdTable[xind];
    lcsx_vline[1] = dataTable->mjdTable[xind];
    if(rozmiar_w_x == 1)
    {
        lcsy_vline[0] = lcs_dynamic_spectrum.yAxis->range().lower;
        lcsy_vline[1] = lcs_dynamic_spectrum.yAxis->range().upper;
    }
    else
    {
        lcsy_vline[0] = *min_element(lcs_flux.begin(), lcs_flux.end()) - 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
        lcsy_vline[1] = *max_element(lcs_flux.begin(), lcs_flux.end())  + 0.05 * (*max_element(lcs_flux.begin(), lcs_flux.end()));
    }
    lcs_dynamic_spectrum.graph(1)->setData(lcsx_vline, lcsy_vline);
    QPen pen3;
    pen3.setColor(QColor(182,26,26));
    lcs_dynamic_spectrum.graph(1)->setPen(pen3);

    set_dynamic_spectrum_labels_for_clicked(xind, yind);
    set_down_IVLHCRHCbuttons();

    // reskalujemy kolor bar
    //colorMap->data()->recalculateDataBounds();
    //colorbar_widget->resize(1,1);

    // ----- dodatkowa rzecz ! ---------------
    // -- dodajemy odpowiednią kropkę na krzywej blasku --
    if (dot_single_added == 0)
    {
        single_dynamic_spectrum.addGraph();
        dot_single_added = 1;
    }

    // -- ustawiamy sobie kropkę na single spectrum --
    QVector < double > x_dot_spec(1), y_dot_spec(1);
    // predkosc radialna
    x_dot_spec[0] = dataTable->velocityTable[xind][yind]; // kliknięta prędkość radialna
    // gestosć strumienia
    if (I_pressed == 1)
        y_dot_spec[0] = dataTable->spectraTableI[xind][yind]; // kliknięta gęstość strumienia
    else if (lhc_pressed == 1)
        y_dot_spec[0] = dataTable->spectraTableLHC[xind][yind]; // kliknięta gęstość strumienia
    else if (rhc_pressed == 1)
        y_dot_spec[0] = dataTable->spectraTableRHC[xind][yind]; // kliknięta gęstość strumienia
    else if (v_pressed == 1)
        y_dot_spec[0] = dataTable->spectraTableV[xind][yind]; // kliknięta gęstość strumienia


    single_dynamic_spectrum.graph(2)->setData(x_dot_spec, y_dot_spec);
    if(dark_mode_switch->isChecked())
        single_dynamic_spectrum.graph(2)->setPen(QPen(Qt::magenta));
    else
        single_dynamic_spectrum.graph(2)->setPen(pen2);

    single_dynamic_spectrum.graph(2)->setLineStyle(QCPGraph::lsNone);
    single_dynamic_spectrum.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));


    // -- dodajemy kropkę na krzywej blasku --
    if (dot_lcs_added == 0)
    {
        lcs_dynamic_spectrum.addGraph();
        dot_lcs_added = 1;
    }

    // -- ustawiamy sobie kropkę na single spectrum --
    QVector < double > x_dot_lcs(1), y_dot_lcs(1);
    // predkosc radialna
    x_dot_lcs[0] = dataTable->mjdTable[xind]; // kliknięta prędkość radialna
    // gestosć strumienia
    if (I_pressed == 1)
        y_dot_lcs[0] = dataTable->spectraTableI[xind][yind]; // kliknięta gęstość strumienia
    else if (lhc_pressed == 1)
        y_dot_lcs[0] = dataTable->spectraTableLHC[xind][yind]; // kliknięta gęstość strumienia
    else if (rhc_pressed == 1)
        y_dot_lcs[0] = dataTable->spectraTableRHC[xind][yind]; // kliknięta gęstość strumienia
    else if (v_pressed == 1)
        y_dot_lcs[0] = dataTable->spectraTableV[xind][yind]; // kliknięta gęstość strumienia
    // -- stylistyka --
    lcs_dynamic_spectrum.graph(2)->setData(x_dot_lcs, y_dot_lcs);

    if(dark_mode_switch->isChecked())
        lcs_dynamic_spectrum.graph(2)->setPen(QPen(Qt::magenta));
    else
        lcs_dynamic_spectrum.graph(2)->setPen(pen2);

    lcs_dynamic_spectrum.graph(2)->setLineStyle(QCPGraph::lsNone);
    lcs_dynamic_spectrum.graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));

    // -- dark i light mode --
    if (dark_mode_switch->isChecked())
    {
        single_dynamic_spectrum.graph(0)->setPen(graph_dark);
        lcs_dynamic_spectrum.graph(0)->setPen(graph_dark);
    }
    else
    {
        single_dynamic_spectrum.graph(0)->setPen(graph_light);
        lcs_dynamic_spectrum.graph(0)->setPen(graph_light);
    }
    single_dynamic_spectrum.replot();
    lcs_dynamic_spectrum.replot();
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
    // -------------- standardowa sekcja ----------------------
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
    // ---------------------------------------------------------

    // dla otwarteg owidma dynczmicznego - zapełniamy text edity
    if(dynamic_spectrum_opened== 1)
    {
        starting_channel_ex_dynsp->setText(QString::fromStdString(to_string(min_range_vel_index+1)));
        ending_channel_ex_dynsp->setText((QString::fromStdString(to_string(max_range_vel_index+1))));
        starting_epoch_ex_dynsp ->setText(QString::fromStdString(to_string(min_obs_number+1)));
        ending_epoch_ex_dynsp->setText((QString::fromStdString(to_string(max_obs_number+1))));
    }

    // przypinamy do vboxa
    vbox_main.addWidget(ex_dynsp_widget);

    // ustalamy visibility
    ex_dynsp_widget->setVisible(true);

    // ustalamy boola
    wd_section_opened = 1;
}

void body::close_dynspectrum_layout()
{
    // -- znikamy --
    ex_dynsp_widget->setVisible(false);
    // -- odpinamy od vboxa --
    vbox_main.removeWidget(ex_dynsp_widget);
    // -- ustalamy boola --
    wd_section_opened = 0;
}

void body::export_file_for_dynamic_spectrum()
{
    // -- inty z przechowywanymi granicami --
    int min, max, min_epoch, max_epoch;

    // -- stringi, do zczytywania wartości z text editów --
    QString mins,maxs, min_epoch_str, max_epoch_str;

    // -- czytamy wartości z pól tekstowych --
    // -- kanaly --
    mins = starting_channel_ex_dynsp->toPlainText();
    maxs = ending_channel_ex_dynsp->toPlainText();
    // -- epoki --
    min_epoch_str = starting_epoch_ex_dynsp->toPlainText();
    max_epoch_str = ending_epoch_ex_dynsp ->toPlainText();

    // -- sprawdzamy, czy text edity sa wypelnione --
    if (mins.toStdString() == "" || maxs.toStdString() == "" || min_epoch_str == "" || max_epoch_str == "")
    {
        QMessageBox::information(&window, tr("Error!"), tr("Fill text editors with text!"));
        return;
    }

    // -- konwertujemy tera wartosci z text edit na inty--
    try
    {
        min = stoi(mins.toStdString());
        max = stoi(maxs.toStdString());
        min_epoch = stoi(min_epoch_str.toStdString());
        max_epoch = stoi(max_epoch_str.toStdString());
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
    if (max > dataTable->spectraTableI[0].size())
        max = dataTable->spectraTableI[0].size();

    // początkowa epoka mniejsza, niż 0:
    if (min_epoch < 1)
        min_epoch = 1;

    // końcowa, większa niż całość:
    if (max_epoch > dataTable->mjdTable.size())
        max_epoch = dataTable->mjdTable.size();

    dataTable->saveDynamicSpectrumToFile(min_epoch, max_epoch, min, max, include_pytime->isChecked());

    // wiadomość końcowa
    string message = "";
    message = "Dynamic spectrum over channels " + to_string(min) + " -> " + to_string(max) + "\n" + "Saved to " + dataTable->getDynSpecFileName(min_epoch, max_epoch);
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
    vbox_main.addWidget(kill_rms_section);

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
    vbox_main.removeWidget(kill_rms_section);
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
    if (dark_mode_switch->isChecked())
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
    if (dark_mode_switch->isChecked())
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
        yI[i] = tsyslst[i];
    }
    // -- graphy --
    // -- dodajemy grafike (I) --
    tsys_vs_time.addGraph();

    tsys_vs_time.graph(0)->setName("I");
    if (dark_mode_switch->isChecked())
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
    if (dark_mode_switch->isChecked())
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
    if (dark_mode_switch->isChecked())
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

    if(include_pytime->isChecked())
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

    if(include_pytime->isChecked())
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

    if(include_pytime->isChecked())
    {
        // wpisujemy naglowek do pliku
        integ << "# time_in_isoformat MJD year Tsys (K)" << endl;
        // petla zapisujaca
        for(int i = 0; i < dataTable->spectraTableI.size(); i++)
        {
            // wrzucamy wszystko do pliku
            integ << fixed << setprecision(11) << pytime_format[i] << "   " << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << tsyslst[i] << endl;
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
            integ << fixed << setprecision(11) << "   " << dataTable->mjdTable[i] << "   " << yrlst[i] << "   " << tsyslst[i] << endl;
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
    if (dark_mode_switch->isChecked())
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
    if (dark_mode_switch->isChecked())
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
    if (dark_mode_switch->isChecked())
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
    if (dark_mode_switch->isChecked())
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
    if (dark_mode_switch->isChecked())
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

    if (dark_mode_switch->isChecked())
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
    Ytsys[0] = tsyslst[xind];
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
 for (int i = 0; i < dataTable->spectraTableI[xind].size(); i++)
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

 if(dark_mode_switch->isChecked())
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
 if (dark_mode_switch->isChecked())
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

    label_to_popup_window += "Tsys: " + to_string(tsyslst[xind]) +"\n\n";
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

void body::calculate_log()
{


    // -- skalujemy data range --
    if (set_log_scale->isChecked())
    {
        // reskalujemy data range
        double dno = 0.0;
        if(I_pressed == 1)
        {
            dno = mean_rms_I;
        }
        else if (v_pressed == 1)
        {
            dno = mean_rms_V;
        }
        else if (lhc_pressed == 1)
        {
            dno = mean_rms_LHC;
        }
        else
        {
            dno = mean_rms_RHC;
        }
        colorMap->data()->recalculateDataBounds();
        QCPRange zasieg(dno, colorMap->data()->dataBounds().upper);
        colorbar->setDataRange(zasieg);

        // -- zmieniamy scale type --
        colorMap->setDataScaleType(QCPAxis::stLogarithmic);
        colorbar->setDataScaleType(QCPAxis::stLogarithmic);
        colorbar->axis()->setTicker(QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog));
        colorbar_widget->replot();
        dynamic_spectrum_pl.replot();
        //colorMap->setDataRange(zasieg);
        // -- aktualizujemy wykres --
        //dynamic_spectrum_pl.replot();
        set_down_IVLHCRHCbuttons();

        //colorbar->axis()->rescale();


    }
    else
    {
        // -- zmieniamy na skale liniowa --
        colorMap->setDataScaleType(QCPAxis::stLinear);
        colorbar->setDataScaleType(QCPAxis::stLinear);
        // -- skalujemy od 0 do max --
        colorMap->rescaleDataRange();
        // -- replotujemy --
        dynamic_spectrum_pl.replot();
        set_down_IVLHCRHCbuttons();
        colorbar->setDataRange(colorMap->dataRange());
        //colorbar->axis()->rescale();
        colorbar->axis()->setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker));
        colorbar_widget->replot();
    }
}

void body::calculate_mean_rms()
{
    // - I -
    double ilosc = 0.0;
    double suma = 0.0;
    for(int i = 0; i < dataTable->spectraTableIERR.size(); i++)
    {
        suma = suma + dataTable->spectraTableIERR[i];
        ilosc = ilosc + 1.0;
    }
    suma = suma / ilosc;
    mean_rms_I = suma;

    // - V -
    suma = 0.0;
    ilosc = 0.0;
    for(int i = 0; i < dataTable->spectraTableVERR.size(); i++)
    {
        suma = suma + dataTable->spectraTableVERR[i];
        ilosc = ilosc + 1.0;
    }
    suma = suma / ilosc;
    mean_rms_V = suma;

    // - LHC -
    suma = 0.0;
    ilosc = 0.0;
    for(int i = 0; i < dataTable->spectraTableLHCERR.size(); i++)
    {
        suma = suma + dataTable->spectraTableLHCERR[i];
        ilosc = ilosc + 1.0;
    }
    suma = suma / ilosc;
    mean_rms_LHC = suma;

    // - RHC -
    suma = 0.0;
    ilosc = 0.0;
    for(int i = 0; i < dataTable->spectraTableRHCERR.size(); i++)
    {
        suma = suma + dataTable->spectraTableRHCERR[i];
        ilosc = ilosc + 1.0;
    }
    suma = suma / ilosc;
    mean_rms_RHC = suma;

}

void body::range_zmienion_na_cb()
{
    cout << "range zmienionty" << endl;
}


void body::range_data_zmienion_na_cb()
{
    cout << "data range zmienionty" << endl;
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
        single_dynamic_spectrum.setBackground(Qt::black);
        single_dynamic_spectrum.axisRect()->setBackground(Qt::black);
        // - kwadracik -
        single_dynamic_spectrum.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        single_dynamic_spectrum.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        single_dynamic_spectrum.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        single_dynamic_spectrum.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        single_dynamic_spectrum.xAxis->setTickLabelColor(Qt::white);
        single_dynamic_spectrum.xAxis2->setTickLabelColor(Qt::white);
        single_dynamic_spectrum.yAxis->setTickLabelColor(Qt::white);
        single_dynamic_spectrum.yAxis2->setTickLabelColor(Qt::white);
        // subtick
        single_dynamic_spectrum.xAxis->setSubTickPen(duda);
        single_dynamic_spectrum.xAxis2->setSubTickPen(duda);
        single_dynamic_spectrum.yAxis->setSubTickPen(duda);
        single_dynamic_spectrum.yAxis2->setSubTickPen(duda);
        // tick
        single_dynamic_spectrum.xAxis->setTickPen(duda);
        single_dynamic_spectrum.xAxis2->setTickPen(duda);
        single_dynamic_spectrum.yAxis->setTickPen(duda);
        single_dynamic_spectrum.yAxis2->setTickPen(duda);
        // label
        single_dynamic_spectrum.xAxis->setLabelColor(Qt::white);
        single_dynamic_spectrum.xAxis2->setLabelColor(Qt::white);
        single_dynamic_spectrum.yAxis->setLabelColor(Qt::white);
        single_dynamic_spectrum.yAxis2->setLabelColor(Qt::white);

        // -- lcs dynamic spectrum --
        // - tło -
        lcs_dynamic_spectrum.setBackground(Qt::black);
        lcs_dynamic_spectrum.axisRect()->setBackground(Qt::black);
        // - kwadracik -
        lcs_dynamic_spectrum.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        lcs_dynamic_spectrum.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        lcs_dynamic_spectrum.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        lcs_dynamic_spectrum.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        lcs_dynamic_spectrum.xAxis->setTickLabelColor(Qt::white);
        lcs_dynamic_spectrum.xAxis2->setTickLabelColor(Qt::white);
        lcs_dynamic_spectrum.yAxis->setTickLabelColor(Qt::white);
        lcs_dynamic_spectrum.yAxis2->setTickLabelColor(Qt::white);
        // subtick
        lcs_dynamic_spectrum.xAxis->setSubTickPen(duda);
        lcs_dynamic_spectrum.xAxis2->setSubTickPen(duda);
        lcs_dynamic_spectrum.yAxis->setSubTickPen(duda);
        lcs_dynamic_spectrum.yAxis2->setSubTickPen(duda);
        // tick
        lcs_dynamic_spectrum.xAxis->setTickPen(duda);
        lcs_dynamic_spectrum.xAxis2->setTickPen(duda);
        lcs_dynamic_spectrum.yAxis->setTickPen(duda);
        lcs_dynamic_spectrum.yAxis2->setTickPen(duda);
        // label
        lcs_dynamic_spectrum.xAxis->setLabelColor(Qt::white);
        lcs_dynamic_spectrum.xAxis2->setLabelColor(Qt::white);
        lcs_dynamic_spectrum.yAxis->setLabelColor(Qt::white);
        lcs_dynamic_spectrum.yAxis2->setLabelColor(Qt::white);

        // -- dynamic spectrum --
        // - tło -
        dynamic_spectrum_pl.setBackground(Qt::black);
        dynamic_spectrum_pl.axisRect()->setBackground(Qt::black);
        // - zmiana kolorów czcionki -
        // ticklabele
        dynamic_spectrum_pl.xAxis->setTickLabelColor(Qt::white);
        dynamic_spectrum_pl.xAxis2->setTickLabelColor(Qt::white);
        dynamic_spectrum_pl.yAxis->setTickLabelColor(Qt::white);
        dynamic_spectrum_pl.yAxis2->setTickLabelColor(Qt::white);
        // label
        dynamic_spectrum_pl.xAxis->setLabelColor(Qt::white);
        dynamic_spectrum_pl.xAxis2->setLabelColor(Qt::white);
        dynamic_spectrum_pl.yAxis->setLabelColor(Qt::white);
        dynamic_spectrum_pl.yAxis2->setLabelColor(Qt::white);

        // colorbar
        // - tło -
        colorbar_widget->setBackground(Qt::black);
        // ticklabele
        colorbar->axis()->setTickPen(duda);
        colorbar->axis()->setSubTickPen(duda);
        colorbar->axis()->setTickLabelColor(Qt::white);

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

        // -- spectrum --
        // - tło -
        spectrum.setBackground(Qt::black);
        spectrum.axisRect()->setBackground(Qt::black);
        // - kwadracik -
        spectrum.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        spectrum.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        spectrum.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        spectrum.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        spectrum.xAxis->setTickLabelColor(Qt::white);
        spectrum.xAxis2->setTickLabelColor(Qt::white);
        spectrum.yAxis->setTickLabelColor(Qt::white);
        spectrum.yAxis2->setTickLabelColor(Qt::white);
        // subtick
        spectrum.xAxis->setSubTickPen(duda);
        spectrum.xAxis2->setSubTickPen(duda);
        spectrum.yAxis->setSubTickPen(duda);
        spectrum.yAxis2->setSubTickPen(duda);
        // tick
        spectrum.xAxis->setTickPen(duda);
        spectrum.xAxis2->setTickPen(duda);
        spectrum.yAxis->setTickPen(duda);
        spectrum.yAxis2->setTickPen(duda);
        // label
        spectrum.xAxis->setLabelColor(Qt::white);
        spectrum.xAxis2->setLabelColor(Qt::white);
        spectrum.yAxis->setLabelColor(Qt::white);
        spectrum.yAxis2->setLabelColor(Qt::white);


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

        // -- jeśli otwarte jest widmo dynamiczne --
        if (dynamic_spectrum_opened == 1)
        {
            lcs_dynamic_spectrum.graph(0)->setPen(graph_dark);
            single_dynamic_spectrum.graph(0)->setPen(graph_dark);

            lcs_dynamic_spectrum.graph(2)->setPen(QPen(Qt::magenta));
            single_dynamic_spectrum.graph(2)->setPen(QPen(Qt::magenta));

            errorBars->setPen(QPen(QColor(105,105,105)));
        }


        // -- replotujemy --
        spectrum.replot();
        dynamic_spectrum_pl.replot();
        single_dynamic_spectrum.replot();
        lcs_dynamic_spectrum.replot();
        colorbar_widget->replot();
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

        // -- single dynamic spectrum --
        // - tło -
        single_dynamic_spectrum.setBackground(Qt::white);
        single_dynamic_spectrum.axisRect()->setBackground(Qt::white);
        // - kwadracik -
        single_dynamic_spectrum.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        single_dynamic_spectrum.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        single_dynamic_spectrum.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        single_dynamic_spectrum.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        single_dynamic_spectrum.xAxis->setTickLabelColor(Qt::black);
        single_dynamic_spectrum.xAxis2->setTickLabelColor(Qt::black);
        single_dynamic_spectrum.yAxis->setTickLabelColor(Qt::black);
        single_dynamic_spectrum.yAxis2->setTickLabelColor(Qt::black);
        // subtick
        single_dynamic_spectrum.xAxis->setSubTickPen(duda);
        single_dynamic_spectrum.xAxis2->setSubTickPen(duda);
        single_dynamic_spectrum.yAxis->setSubTickPen(duda);
        single_dynamic_spectrum.yAxis2->setSubTickPen(duda);
        // tick
        single_dynamic_spectrum.xAxis->setTickPen(duda);
        single_dynamic_spectrum.xAxis2->setTickPen(duda);
        single_dynamic_spectrum.yAxis->setTickPen(duda);
        single_dynamic_spectrum.yAxis2->setTickPen(duda);
        // label
        single_dynamic_spectrum.xAxis->setLabelColor(Qt::black);
        single_dynamic_spectrum.xAxis2->setLabelColor(Qt::black);
        single_dynamic_spectrum.yAxis->setLabelColor(Qt::black);
        single_dynamic_spectrum.yAxis2->setLabelColor(Qt::black);

        // -- lcs dynamic spectrum --
        // - tło -
        lcs_dynamic_spectrum.setBackground(Qt::white);
        lcs_dynamic_spectrum.axisRect()->setBackground(Qt::white);
        // - kwadracik -
        lcs_dynamic_spectrum.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        lcs_dynamic_spectrum.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        lcs_dynamic_spectrum.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        lcs_dynamic_spectrum.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        lcs_dynamic_spectrum.xAxis->setTickLabelColor(Qt::black);
        lcs_dynamic_spectrum.xAxis2->setTickLabelColor(Qt::black);
        lcs_dynamic_spectrum.yAxis->setTickLabelColor(Qt::black);
        lcs_dynamic_spectrum.yAxis2->setTickLabelColor(Qt::black);
        // subtick
        lcs_dynamic_spectrum.xAxis->setSubTickPen(duda);
        lcs_dynamic_spectrum.xAxis2->setSubTickPen(duda);
        lcs_dynamic_spectrum.yAxis->setSubTickPen(duda);
        lcs_dynamic_spectrum.yAxis2->setSubTickPen(duda);
        // tick
        lcs_dynamic_spectrum.xAxis->setTickPen(duda);
        lcs_dynamic_spectrum.xAxis2->setTickPen(duda);
        lcs_dynamic_spectrum.yAxis->setTickPen(duda);
        lcs_dynamic_spectrum.yAxis2->setTickPen(duda);
        // label
        lcs_dynamic_spectrum.xAxis->setLabelColor(Qt::black);
        lcs_dynamic_spectrum.xAxis2->setLabelColor(Qt::black);
        lcs_dynamic_spectrum.yAxis->setLabelColor(Qt::black);
        lcs_dynamic_spectrum.yAxis2->setLabelColor(Qt::black);

        // -- dynamic spectrum --
        // - tło -
        dynamic_spectrum_pl.setBackground(Qt::white);
        dynamic_spectrum_pl.axisRect()->setBackground(Qt::white);
        // - zmiana kolorów czcionki -
        // ticklabele
        dynamic_spectrum_pl.xAxis->setTickLabelColor(Qt::black);
        dynamic_spectrum_pl.xAxis2->setTickLabelColor(Qt::black);
        dynamic_spectrum_pl.yAxis->setTickLabelColor(Qt::black);
        dynamic_spectrum_pl.yAxis2->setTickLabelColor(Qt::black);
        // label
        dynamic_spectrum_pl.xAxis->setLabelColor(Qt::black);
        dynamic_spectrum_pl.xAxis2->setLabelColor(Qt::black);
        dynamic_spectrum_pl.yAxis->setLabelColor(Qt::black);
        dynamic_spectrum_pl.yAxis2->setLabelColor(Qt::black);

        // colorbar
        // - tło -
        colorbar_widget->setBackground(Qt::white);
        // ticklabele
        colorbar->axis()->setTickPen(duda);
        colorbar->axis()->setSubTickPen(duda);
        colorbar->axis()->setTickLabelColor(Qt::black);

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

        // -- spectrum --
        // - tło -
        spectrum.setBackground(Qt::white);
        spectrum.axisRect()->setBackground(Qt::white);
        // - kwadracik -
        spectrum.axisRect()->axis(QCPAxis::atTop)->setBasePen(duda);
        spectrum.axisRect()->axis(QCPAxis::atLeft)->setBasePen(duda);
        spectrum.axisRect()->axis(QCPAxis::atBottom)->setBasePen(duda);
        spectrum.axisRect()->axis(QCPAxis::atRight)->setBasePen(duda);
        // - zmiana kolorów czcionki -
        // ticklabele
        spectrum.xAxis->setTickLabelColor(Qt::black);
        spectrum.xAxis2->setTickLabelColor(Qt::black);
        spectrum.yAxis->setTickLabelColor(Qt::black);
        spectrum.yAxis2->setTickLabelColor(Qt::black);
        // subtick
        spectrum.xAxis->setSubTickPen(duda);
        spectrum.xAxis2->setSubTickPen(duda);
        spectrum.yAxis->setSubTickPen(duda);
        spectrum.yAxis2->setSubTickPen(duda);
        // tick
        spectrum.xAxis->setTickPen(duda);
        spectrum.xAxis2->setTickPen(duda);
        spectrum.yAxis->setTickPen(duda);
        spectrum.yAxis2->setTickPen(duda);
        // label
        spectrum.xAxis->setLabelColor(Qt::black);
        spectrum.xAxis2->setLabelColor(Qt::black);
        spectrum.yAxis->setLabelColor(Qt::black);
        spectrum.yAxis2->setLabelColor(Qt::black);


        // -- sekcja gauss --
        //spectrum_w_gauss->xaxis->

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
        if (dynamic_spectrum_opened == 1)
        {
            lcs_dynamic_spectrum.graph(0)->setPen(graph_light);
            single_dynamic_spectrum.graph(0)->setPen(graph_light);

            lcs_dynamic_spectrum.graph(2)->setPen(pen2);
            single_dynamic_spectrum.graph(2)->setPen(pen2);

            errorBars->setPen(QPen(QColor(180,180,180)));

        }

        // -- replotujemy --
        spectrum.replot();
        dynamic_spectrum_pl.replot();
        single_dynamic_spectrum.replot();
        lcs_dynamic_spectrum.replot();
        colorbar_widget->replot();
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
    vbox_main.addWidget(kill_gauss);

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
    vbox_main.removeWidget(kill_gauss);
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

// -- slot sprawia, że tworzone jest nowe I w wybranyej na widmie dynamicznym epoce --
void body::make_new_I_and_V_for_epoch_on_dynspec()
{
    // -- czytamy numer epoki --
    int epoch_number = xind;

    // -- tworzymy tymczasowe kontenery --
    vector < double > tmprec_LHCERR(dataTable->spectraTableLHC[epoch_number].size()); // deklarujemy dokładny rozmiar, by szybciej działało
    vector < double > tmprec_RHCERR(dataTable->spectraTableRHC[epoch_number].size());
    vector < double > tmprec_LHC(dataTable->spectraTableLHC[epoch_number].size());
    vector < double > tmprec_RHC(dataTable->spectraTableRHC[epoch_number].size());

    // -- pętla nr. 1 - zgrywanie informacji dot. LHC i RHC --
    for (unsigned long int i = 0; i < dataTable->spectraTableLHC[epoch_number].size(); i++)
    {
        tmprec_LHC[i] = dataTable->spectraTableLHC[epoch_number][i];
        tmprec_RHC[i] = dataTable->spectraTableRHC[epoch_number][i];
        tmprec_LHCERR[i] = dataTable->spectraTableLHCERR[epoch_number];
        tmprec_RHCERR[i] = dataTable->spectraTableRHCERR[epoch_number];
    }

    // -- pętla nr. 2 - zapisywanie infromacji na nowych tablicach --
    for (unsigned long int i = 0; i < dataTable->spectraTableLHC[epoch_number].size(); i++)
    {
        dataTable->spectraTableI[epoch_number][i] = (tmprec_LHC[i] + tmprec_RHC[i]) / 2.0;
        dataTable->spectraTableIERR[epoch_number] = (tmprec_LHCERR[i] + tmprec_RHCERR[i]) / 2.0;

        dataTable->spectraTableV[epoch_number][i] = (tmprec_RHC[i] - tmprec_LHC[i]) / 2.0;
        dataTable->spectraTableVERR[epoch_number] = (tmprec_LHCERR[i] + tmprec_RHCERR[i]) / 2.0;

    }

    // -- dodajemy do listy edutowanych --
    append_to_rotated_lst(epoch_number);
    // -- ustalamy "made rotation" na 1
    made_rotation = 1;
    // -- aktualizujemy widmo dynamiczne --
    update_dynamic_spectrum();
    /*
    for(int i = 0; i < dataTable->spectraTableRHC.size(); i++)
    {
        for (int k=0; k< dataTable->spectraTableRHC[i].size(); k++)
        {
            dataTable->spectraTableI[i][k] = (dataTable->spectraTableRHC[i][k] + dataTable->spectraTableLHC[i][k]) / 2.0;
            dataTable->spectraTableIERR[i][k] = (RHCdataTable->spectraTableIERR[i][k] + LHCdataTable->spectraTableIERR[i][k]) / 2.0;
        }
    }

    for(int i = 0; i < dataTable->spectraTableV.size(); i++)
    {
        for (int k=0; k< dataTable->spectraTableV[i].size(); k++)
        {
            dataTable->spectraTableV[i][k] = (dataTable->spectraTableRHC[i][k] - dataTable->spectraTableLHC[i][k]) / 2.0;
            VdataTable->spectraTableIERR[i][k] = (RHCdataTable->spectraTableIERR[i][k] - LHCdataTable->spectraTableIERR[i][k]) / 2.0;
        }
    }
    */

}
