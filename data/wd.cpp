#include "spectral_container.h"
/*
W tym pliku są metody do zapisywania widma dynamicznego do pliku
 */

void spectral_container::saveDynamicSpectrumToFile(int min_epoch, int max_epoch, int min_channel, int max_channel, bool isotimeInclude)
{
    // otwieramy plik do zapistwania
    std::ofstream dynSpecFile;
    dynSpecFile.open(getDynSpecFileName(min_epoch, max_epoch).c_str());

    int columnw = 15;
    // nagłówek
    dynSpecFile << "# ----------------------------------------------" << std::endl;
    dynSpecFile << "# File with data for dynamic spectrum from rt4sv++" << std::endl;
    dynSpecFile << "# Source: " << nameOfSource << std::endl;
    dynSpecFile << "# Time range (MJD): " << mjdTable[min_epoch-1] << " -> " << mjdTable[max_epoch-1] << std::endl;
    dynSpecFile << "# Time range (ISO): " << isotimeTable[min_epoch-1] << " -> " << isotimeTable[max_epoch-1] << std::endl;
    dynSpecFile << "# Channel range: " << min_channel << " -> " << max_channel << std::endl;
    dynSpecFile << "# V_lsr range: " << velocityTable[min_epoch-1][min_channel-1] << " -> " << velocityTable[min_epoch-1][max_channel-1] << " km/s" << std::endl;
    dynSpecFile << "# columns:" << std::endl;
    dynSpecFile << "# " << std::left << std::setw(4) << "nr ";
    if(isotimeInclude)
        dynSpecFile << std::setw(columnw) << " time_in_isoformat        ";

    dynSpecFile << std::setw(columnw) << " MJD " << std::setw(columnw) << "year ";
    dynSpecFile << std::setw(columnw) << "channel " << std::setw(columnw) << "V_lsr ";
    dynSpecFile << std::setw(columnw) << "I " << std::setw(columnw) << "+/- ";
    dynSpecFile << std::setw(columnw) << "V " << std::setw(columnw) << "+/- ";
    dynSpecFile << std::setw(columnw) << "LHC " << std::setw(columnw) << "+/- ";
    dynSpecFile << std::setw(columnw) << "RHC " << std::setw(columnw) << "+/- " << std::endl;
    dynSpecFile << "# ----------------------------------------------" << std::endl;

    // zapisujemy ciało danych
    // i - po epokach
    // j - po kanałach
    int count = 1;
    for(unsigned long int i = min_epoch-1; i < max_epoch; i++)
    {

        for(unsigned long int j = min_channel-1; j < max_channel; j++)
        {
            dynSpecFile << std::right << std::setw(5) << std::fixed << count << " ";
            if(isotimeInclude)
                dynSpecFile << std::right << std::setw(columnw) << isotimeTable[i] << " ";
            dynSpecFile << std::right << std::setw(columnw-2) << std::fixed << std::setprecision(7) << mjdTable[i] << " ";
            dynSpecFile << std::setw(columnw-2) << decyrTable[i] << " ";
            dynSpecFile << std::setw(columnw-2) << channelTable[i][j] << " ";
            dynSpecFile << std::setw(columnw-2) << velocityTable[i][j] << " ";
            dynSpecFile << std::setw(columnw-2) << spectraTableI[i][j] << " " << std::setw(columnw-2) << spectraTableIERR[i] << " ";
            dynSpecFile << std::setw(columnw-2) << spectraTableV[i][j] << " " << std::setw(columnw-2) << spectraTableVERR[i] << " ";
            dynSpecFile << std::setw(columnw-2) << spectraTableLHC[i][j] << " " << std::setw(columnw-2) << spectraTableLHCERR[i] << " ";
            dynSpecFile << std::setw(columnw-2) << spectraTableRHC[i][j] << " " << std::setw(columnw-2) << spectraTableRHCERR[i] << " ";
            dynSpecFile << "\n";
        }

        dynSpecFile << "\n";
        count = count + 1;
    }

    dynSpecFile.close();

}

std::string spectral_container::getDynSpecFileName(int min_epoch, int max_epoch)
{
    std::string wdFileName;
    wdFileName = saveDirectory + "/" + nameOfSource + "_dynamic_spectrum_epochs_" + std::to_string(min_epoch) + "_to_" + std::to_string(max_epoch) + ".dat";
    return wdFileName;
}
