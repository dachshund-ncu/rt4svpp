#include "spectral_container.h"

void spectral_container::saveSpectrum(int epoch)
{
    // otwieramy plik do zapisywania
    std::ofstream asciiSpec;
    asciiSpec.open( (getFileNameForAsciiSave(epoch)).c_str() );

    int columnw = 13;
    // piszemy nagłówek pliku
    asciiSpec << "# ----------------------------------------------" << std::endl;
    asciiSpec << "# ascii file, spectrum from epoch no. " << epoch << std::endl;
    asciiSpec << "# time (MJD): " << mjdTable[epoch-1] << std::endl;
    asciiSpec << "# time (ISO): " << isotimeTable[epoch-1] << std::endl;
    asciiSpec << "# columns:" << std::endl;
    asciiSpec << "# " << std::left << std::setw(columnw) << "channel "<< std::setw(columnw) << "V_lsr (km/s)  ";
    asciiSpec << std::setw(columnw) << "I "<< std::setw(columnw) << "+/- "<< std::setw(columnw) << "V ";
    asciiSpec << std::setw(columnw) << "+/- " << std::setw(columnw) << "LHC " << std::setw(columnw) << "+/- ";
    asciiSpec << std::setw(columnw) << "RHC " << std::setw(columnw) << "+/- " << std::endl;
    asciiSpec << "# ----------------------------------------------" << std::endl;

    // pętla zapisująca
    for (int i = 0; i < (int) spectraTableI[epoch-1].size(); i++)
    {
        asciiSpec << std::right << std::fixed << std::setprecision(7) << std::setw(12) << channelTable[epoch-1][i] << " " << std::setw(12) << velocityTable[epoch-1][i] << " ";
        // dane (I)
        asciiSpec << std::setw(12) << spectraTableI[epoch-1][i] << " " << std::setw(12) << spectraTableIERR[epoch-1] << " ";
        asciiSpec << std::setw(12) << spectraTableV[epoch-1][i] << " " << std::setw(12) << spectraTableVERR[epoch-1] << " ";
        asciiSpec << std::setw(12) << spectraTableLHC[epoch-1][i] << " " << std::setw(12) << spectraTableLHCERR[epoch-1] << " ";
        asciiSpec << std::setw(12) << spectraTableRHC[epoch-1][i] << " " << std::setw(12) << spectraTableRHCERR[epoch-1] << " ";
        asciiSpec << std::endl;
    }
    // zamykamy plik
    asciiSpec.close();

}

void spectral_container::saveAllSpectra()
{
    // pasek postępu
    QProgressDialog postep;
    postep.setLabelText("Saving files to ASCII, please wait");
    postep.setMinimum(0);
    postep.setMaximum((int) spectraTableI.size());
    postep.setVisible(true);

    // wykonujemy prostą pętlę po wszystkich epokach
    for(int i = 0; i < (int) spectraTableI.size(); i++)
    {
        saveSpectrum(i+1); // epoka jest +1 bo tam przyjmujemy w argumencie numer epoki, numerowaney od 1
        postep.setValue(i);
        QCoreApplication::processEvents();
    }
}

std::string spectral_container::getFileNameForAsciiSave(int epoch)
{
    std::string oldFileName = fileNamesTab[epoch-1];
    std::string asciiFileName = "";
    // dodajemy coś jeszcze
    if (!fileTypesTab[epoch-1])
    {
        oldFileName.erase(oldFileName.end()-4, oldFileName.end());
    }
    else
    {
        oldFileName.erase(oldFileName.end()-5, oldFileName.end());
    }
    asciiFileName += oldFileName + "_ascii.DAT";
    return asciiFileName;
}
