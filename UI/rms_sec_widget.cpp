#include "rms_sec_widget.h"

Rms_sec_widget::Rms_sec_widget(spectral_container * dataTable)
               : dataTable(dataTable)
{
    // -- dajemy nowe rzeczy do roboty --
    this->setGeometry(300, 300, 1280, 720);
    this->setVisible(true);
}
