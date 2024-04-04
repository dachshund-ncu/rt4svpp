#############################################################################
# Makefile for building: rt4sv++
# Generated by qmake (3.1) (Qt 5.15.3)
# Project:  ui_class.pro
# Template: app
# Command: /usr/lib/qt5/bin/qmake -o Makefile ui_class.pro
#############################################################################

MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_PRINTSUPPORT_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -Wall -Wextra -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -Wextra -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++
QMAKE         = /usr/lib/qt5/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /usr/lib/qt5/bin/qmake -install qinstall
QINSTALL_PROGRAM = /usr/lib/qt5/bin/qmake -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = rt4sv++1.0.0
DISTDIR = /home/michu/projects/rt4svpp/.tmp/rt4sv++1.0.0
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS) -L /usr/local/lib/ -lCCfits -lcfitsio /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so /usr/lib/x86_64-linux-gnu/libQt5Widgets.so /usr/lib/x86_64-linux-gnu/libQt5Gui.so /usr/lib/x86_64-linux-gnu/libQt5Core.so -lGL -lpthread   
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = UI/custom_widget.cpp \
		UI/varcoefscalcwidget.cpp \
		body.cpp \
		data/calibration.cpp \
		data/exportvaroiusdata.cpp \
		data/spectral_container.cpp \
		libs/qcustomplot.cpp \
		main.cpp \
		data/averovervelocity.cpp \
		data/integrate.cpp \
		data/averovertime.cpp \
		data/wd.cpp \
		data/spectralindex.cpp \
		data/rotation.cpp \
		data/savespectrumtoascii.cpp \
		UI/vbox_main.cpp \
		UI/integrate_widget.cpp \
		UI/export_dynamic_spectrum_widget.cpp \
		UI/calsection.cpp \
		UI/heat_map_widget.cpp \
		UI/single_spec_widget.cpp \
		UI/rms_sec_widget.cpp \
		UI/rms_selector.cpp \
		data/extractlcs.cpp \
		UI/contentviewer.cpp qrc_resources.cpp \
		moc_custom_widget.cpp \
		moc_varcoefscalcwidget.cpp \
		moc_body.cpp \
		moc_qcustomplot.cpp \
		moc_heat_map_widget.cpp \
		moc_single_spec_widget.cpp \
		moc_rms_sec_widget.cpp \
		moc_rms_selector.cpp
OBJECTS       = custom_widget.o \
		varcoefscalcwidget.o \
		body.o \
		calibration.o \
		exportvaroiusdata.o \
		spectral_container.o \
		qcustomplot.o \
		main.o \
		averovervelocity.o \
		integrate.o \
		averovertime.o \
		wd.o \
		spectralindex.o \
		rotation.o \
		savespectrumtoascii.o \
		vbox_main.o \
		integrate_widget.o \
		export_dynamic_spectrum_widget.o \
		calsection.o \
		heat_map_widget.o \
		single_spec_widget.o \
		rms_sec_widget.o \
		rms_selector.o \
		extractlcs.o \
		contentviewer.o \
		qrc_resources.o \
		moc_custom_widget.o \
		moc_varcoefscalcwidget.o \
		moc_body.o \
		moc_qcustomplot.o \
		moc_heat_map_widget.o \
		moc_single_spec_widget.o \
		moc_rms_sec_widget.o \
		moc_rms_selector.o
DIST          = /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		ui_class.pro UI/custom_ui_elements.h \
		UI/custom_widget.h \
		UI/varcoefscalcwidget.h \
		body.h \
		data/spectral_container.h \
		libs/qcustomplot.h \
		UI/vbox_main.h \
		UI/integrate_widget.h \
		UI/export_dynamic_spectrum_widget.h \
		UI/calsection.h \
		UI/heat_map_widget.h \
		UI/single_spec_widget.h \
		UI/rms_sec_widget.h \
		UI/rms_selector.h \
		UI/contentviewer.h UI/custom_widget.cpp \
		UI/varcoefscalcwidget.cpp \
		body.cpp \
		data/calibration.cpp \
		data/exportvaroiusdata.cpp \
		data/spectral_container.cpp \
		libs/qcustomplot.cpp \
		main.cpp \
		data/averovervelocity.cpp \
		data/integrate.cpp \
		data/averovertime.cpp \
		data/wd.cpp \
		data/spectralindex.cpp \
		data/rotation.cpp \
		data/savespectrumtoascii.cpp \
		UI/vbox_main.cpp \
		UI/integrate_widget.cpp \
		UI/export_dynamic_spectrum_widget.cpp \
		UI/calsection.cpp \
		UI/heat_map_widget.cpp \
		UI/single_spec_widget.cpp \
		UI/rms_sec_widget.cpp \
		UI/rms_selector.cpp \
		data/extractlcs.cpp \
		UI/contentviewer.cpp
QMAKE_TARGET  = rt4sv++
DESTDIR       = 
TARGET        = rt4sv++


first: all
####### Build rules

rt4sv++:  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ui_class.pro /usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		ui_class.pro \
		resources.qrc
	$(QMAKE) -o Makefile ui_class.pro
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_edid_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_egl_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fb_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_glx_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_input_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_kms_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_service_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_theme_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_vulkan_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/toolchain.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qmake_use.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/file_copies.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf:
ui_class.pro:
resources.qrc:
qmake: FORCE
	@$(QMAKE) -o Makefile ui_class.pro

qmake_all: FORCE


all: Makefile rt4sv++

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents resources.qrc $(DISTDIR)/
	$(COPY_FILE) --parents /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents UI/custom_ui_elements.h UI/custom_widget.h UI/varcoefscalcwidget.h body.h data/spectral_container.h libs/qcustomplot.h UI/vbox_main.h UI/integrate_widget.h UI/export_dynamic_spectrum_widget.h UI/calsection.h UI/heat_map_widget.h UI/single_spec_widget.h UI/rms_sec_widget.h UI/rms_selector.h UI/contentviewer.h $(DISTDIR)/
	$(COPY_FILE) --parents UI/custom_widget.cpp UI/varcoefscalcwidget.cpp body.cpp data/calibration.cpp data/exportvaroiusdata.cpp data/spectral_container.cpp libs/qcustomplot.cpp main.cpp data/averovervelocity.cpp data/integrate.cpp data/averovertime.cpp data/wd.cpp data/spectralindex.cpp data/rotation.cpp data/savespectrumtoascii.cpp UI/vbox_main.cpp UI/integrate_widget.cpp UI/export_dynamic_spectrum_widget.cpp UI/calsection.cpp UI/heat_map_widget.cpp UI/single_spec_widget.cpp UI/rms_sec_widget.cpp UI/rms_selector.cpp data/extractlcs.cpp UI/contentviewer.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all: qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resources.cpp
qrc_resources.cpp: resources.qrc \
		/usr/lib/qt5/bin/rcc \
		images/chiRedIcon.svg \
		images/openRmsSection.svg \
		images/averOverVelIcon.svg \
		images/VDSicon.svg \
		images/Rotate_p_icon.svg \
		images/IDSicon2.svg \
		images/DOWNicon.svg \
		images/openSingleSpecIcon.svg \
		images/calibrateIcon.svg \
		images/reloadIcon.svg \
		images/LEFTicon.svg \
		images/loadFitsFilesIcon.svg \
		images/UPicon.svg \
		images/exitIcon.svg \
		images/deathstaradder.svg \
		images/openDynSpecIcon.svg \
		images/Rotate_m_icon.svg \
		images/FLAGicon.svg \
		images/exportDynspecIcon.svg \
		images/RHDSicon.svg \
		images/RIGHTicon.svg \
		images/averOverTimeIcon.svg \
		images/integrateIcon.svg \
		images/loadFitsAVRIcon.svg \
		images/LHCDSicon.svg
	/usr/lib/qt5/bin/rcc -name resources resources.qrc -o qrc_resources.cpp

compiler_moc_predefs_make_all: moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) moc_predefs.h
moc_predefs.h: /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -O2 -Wall -Wextra -dM -E -o moc_predefs.h /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all: moc_custom_widget.cpp moc_varcoefscalcwidget.cpp moc_body.cpp moc_qcustomplot.cpp moc_heat_map_widget.cpp moc_single_spec_widget.cpp moc_rms_sec_widget.cpp moc_rms_selector.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_custom_widget.cpp moc_varcoefscalcwidget.cpp moc_body.cpp moc_qcustomplot.cpp moc_heat_map_widget.cpp moc_single_spec_widget.cpp moc_rms_sec_widget.cpp moc_rms_selector.cpp
moc_custom_widget.cpp: UI/custom_widget.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/michu/projects/rt4svpp/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/michu/projects/rt4svpp -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include UI/custom_widget.h -o moc_custom_widget.cpp

moc_varcoefscalcwidget.cpp: UI/varcoefscalcwidget.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/michu/projects/rt4svpp/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/michu/projects/rt4svpp -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include UI/varcoefscalcwidget.h -o moc_varcoefscalcwidget.cpp

moc_body.cpp: body.h \
		libs/qcustomplot.h \
		data/spectral_container.h \
		UI/vbox_main.h \
		UI/integrate_widget.h \
		UI/export_dynamic_spectrum_widget.h \
		UI/calsection.h \
		UI/heat_map_widget.h \
		UI/contentviewer.h \
		UI/single_spec_widget.h \
		UI/rms_sec_widget.h \
		UI/varcoefscalcwidget.h \
		UI/rms_selector.h \
		UI/custom_ui_elements.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/michu/projects/rt4svpp/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/michu/projects/rt4svpp -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include body.h -o moc_body.cpp

moc_qcustomplot.cpp: libs/qcustomplot.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/michu/projects/rt4svpp/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/michu/projects/rt4svpp -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include libs/qcustomplot.h -o moc_qcustomplot.cpp

moc_heat_map_widget.cpp: UI/heat_map_widget.h \
		libs/qcustomplot.h \
		data/spectral_container.h \
		UI/contentviewer.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/michu/projects/rt4svpp/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/michu/projects/rt4svpp -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include UI/heat_map_widget.h -o moc_heat_map_widget.cpp

moc_single_spec_widget.cpp: UI/single_spec_widget.h \
		data/spectral_container.h \
		libs/qcustomplot.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/michu/projects/rt4svpp/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/michu/projects/rt4svpp -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include UI/single_spec_widget.h -o moc_single_spec_widget.cpp

moc_rms_sec_widget.cpp: UI/rms_sec_widget.h \
		libs/qcustomplot.h \
		data/spectral_container.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/michu/projects/rt4svpp/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/michu/projects/rt4svpp -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include UI/rms_sec_widget.h -o moc_rms_sec_widget.cpp

moc_rms_selector.cpp: UI/rms_selector.h \
		moc_predefs.h \
		/usr/lib/qt5/bin/moc
	/usr/lib/qt5/bin/moc $(DEFINES) --include /home/michu/projects/rt4svpp/moc_predefs.h -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -I/home/michu/projects/rt4svpp -I/usr/local/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -I/usr/include/c++/11/backward -I/usr/lib/gcc/x86_64-linux-gnu/11/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include UI/rms_selector.h -o moc_rms_selector.cpp

compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_rcc_clean compiler_moc_predefs_clean compiler_moc_header_clean 

####### Compile

custom_widget.o: UI/custom_widget.cpp UI/custom_widget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o custom_widget.o UI/custom_widget.cpp

varcoefscalcwidget.o: UI/varcoefscalcwidget.cpp UI/varcoefscalcwidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o varcoefscalcwidget.o UI/varcoefscalcwidget.cpp

body.o: body.cpp body.h \
		libs/qcustomplot.h \
		data/spectral_container.h \
		UI/vbox_main.h \
		UI/integrate_widget.h \
		UI/export_dynamic_spectrum_widget.h \
		UI/calsection.h \
		UI/heat_map_widget.h \
		UI/contentviewer.h \
		UI/single_spec_widget.h \
		UI/rms_sec_widget.h \
		UI/varcoefscalcwidget.h \
		UI/rms_selector.h \
		UI/custom_ui_elements.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o body.o body.cpp

calibration.o: data/calibration.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o calibration.o data/calibration.cpp

exportvaroiusdata.o: data/exportvaroiusdata.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o exportvaroiusdata.o data/exportvaroiusdata.cpp

spectral_container.o: data/spectral_container.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o spectral_container.o data/spectral_container.cpp

qcustomplot.o: libs/qcustomplot.cpp libs/qcustomplot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qcustomplot.o libs/qcustomplot.cpp

main.o: main.cpp body.h \
		libs/qcustomplot.h \
		data/spectral_container.h \
		UI/vbox_main.h \
		UI/integrate_widget.h \
		UI/export_dynamic_spectrum_widget.h \
		UI/calsection.h \
		UI/heat_map_widget.h \
		UI/contentviewer.h \
		UI/single_spec_widget.h \
		UI/rms_sec_widget.h \
		UI/varcoefscalcwidget.h \
		UI/rms_selector.h \
		UI/custom_ui_elements.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

averovervelocity.o: data/averovervelocity.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o averovervelocity.o data/averovervelocity.cpp

integrate.o: data/integrate.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o integrate.o data/integrate.cpp

averovertime.o: data/averovertime.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o averovertime.o data/averovertime.cpp

wd.o: data/wd.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o wd.o data/wd.cpp

spectralindex.o: data/spectralindex.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o spectralindex.o data/spectralindex.cpp

rotation.o: data/rotation.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rotation.o data/rotation.cpp

savespectrumtoascii.o: data/savespectrumtoascii.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o savespectrumtoascii.o data/savespectrumtoascii.cpp

vbox_main.o: UI/vbox_main.cpp UI/vbox_main.h \
		UI/integrate_widget.h \
		data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o vbox_main.o UI/vbox_main.cpp

integrate_widget.o: UI/integrate_widget.cpp UI/integrate_widget.h \
		data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o integrate_widget.o UI/integrate_widget.cpp

export_dynamic_spectrum_widget.o: UI/export_dynamic_spectrum_widget.cpp UI/export_dynamic_spectrum_widget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o export_dynamic_spectrum_widget.o UI/export_dynamic_spectrum_widget.cpp

calsection.o: UI/calsection.cpp UI/calsection.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o calsection.o UI/calsection.cpp

heat_map_widget.o: UI/heat_map_widget.cpp UI/heat_map_widget.h \
		libs/qcustomplot.h \
		data/spectral_container.h \
		UI/contentviewer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o heat_map_widget.o UI/heat_map_widget.cpp

single_spec_widget.o: UI/single_spec_widget.cpp UI/single_spec_widget.h \
		data/spectral_container.h \
		libs/qcustomplot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o single_spec_widget.o UI/single_spec_widget.cpp

rms_sec_widget.o: UI/rms_sec_widget.cpp UI/rms_sec_widget.h \
		libs/qcustomplot.h \
		data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rms_sec_widget.o UI/rms_sec_widget.cpp

rms_selector.o: UI/rms_selector.cpp UI/rms_selector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rms_selector.o UI/rms_selector.cpp

extractlcs.o: data/extractlcs.cpp data/spectral_container.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o extractlcs.o data/extractlcs.cpp

contentviewer.o: UI/contentviewer.cpp UI/contentviewer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o contentviewer.o UI/contentviewer.cpp

qrc_resources.o: qrc_resources.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resources.o qrc_resources.cpp

moc_custom_widget.o: moc_custom_widget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_custom_widget.o moc_custom_widget.cpp

moc_varcoefscalcwidget.o: moc_varcoefscalcwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_varcoefscalcwidget.o moc_varcoefscalcwidget.cpp

moc_body.o: moc_body.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_body.o moc_body.cpp

moc_qcustomplot.o: moc_qcustomplot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qcustomplot.o moc_qcustomplot.cpp

moc_heat_map_widget.o: moc_heat_map_widget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_heat_map_widget.o moc_heat_map_widget.cpp

moc_single_spec_widget.o: moc_single_spec_widget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_single_spec_widget.o moc_single_spec_widget.cpp

moc_rms_sec_widget.o: moc_rms_sec_widget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rms_sec_widget.o moc_rms_sec_widget.cpp

moc_rms_selector.o: moc_rms_selector.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rms_selector.o moc_rms_selector.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

