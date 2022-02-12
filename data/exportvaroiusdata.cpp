#include "spectral_container.h"

void spectral_container::exportRmsData()
{
    // -- otwieramy plik --
    std::ofstream rmsValues;
    rmsValues.open( (getFileNameForExportedRms()).c_str() );
    int columnw = 13;
    // -- piszemy nagłówek pliku --
    rmsValues << "# ----------------------------------------------" << std::endl;
    rmsValues << "Rms values from source " << nameOfSource << std::endl;
    rmsValues << "# columns:" << std::endl;
    rmsValues << "# " << std::left << std::setw(columnw) << "MJD " << std::setw(columnw) << "RMS I ";
    rmsValues << std::setw(columnw) << "RMS V ";
    rmsValues << std::setw(columnw) << "RMS LHC ";
    rmsValues << std::setw(columnw) << "RMS RHC " << std::endl;
    rmsValues << "# ----------------------------------------------" << std::endl;
    // -- pętla zapisująca dane --
    for(unsigned long int i = 0; i < mjdTable.size(); i++)
    {
        rmsValues << std::right << std::fixed << std::setprecision(7) << std::setw(columnw) << mjdTable[i] << " ";
        rmsValues << std::setw(columnw) << spectraTableIERR[i] << " ";
        rmsValues << std::setw(columnw) << spectraTableVERR[i] << " ";
        rmsValues << std::setw(columnw) << spectraTableLHCERR[i] << " ";
        rmsValues << std::setw(columnw) << spectraTableRHCERR[i] << " ";
        rmsValues << std::endl;
    }
    rmsValues.close();
}

void spectral_container::exportTsysData()
{
    // -- otwieramy plik --
    std::ofstream tsysValues;
    tsysValues.open( (getFileNameForExportedTsys()).c_str() );
    int columnw = 13;
    // -- piszemy nagłówek pliku --
    tsysValues << "# ----------------------------------------------" << std::endl;
    tsysValues << "Rms values from source " << nameOfSource << std::endl;
    tsysValues << "# columns:" << std::endl;
    tsysValues << "# " << std::left << std::setw(columnw) << "MJD " << std::setw(columnw) << "Tsys " << std::endl;
    tsysValues << "# ----------------------------------------------" << std::endl;
    // -- pętla zapisująca dane --
    for(unsigned long int i = 0; i < mjdTable.size(); i++)
    {
        tsysValues << std::right << std::fixed << std::setprecision(7) << std::setw(columnw) << mjdTable[i] << " ";
        tsysValues << std::setw(columnw) << tsysTable[i] << std::endl;
    }
    tsysValues.close();
}

std::string spectral_container::getFileNameForExportedRms()
{
    std::string fileName = saveDirectory + "/" + nameOfSource + "_rms_vs_time.dat";
    return fileName;
}

std::string spectral_container::getFileNameForExportedTsys()
{
    std::string fileName = saveDirectory + "/" + nameOfSource + "_tsys_vs_time.dat";
    return fileName;
}
