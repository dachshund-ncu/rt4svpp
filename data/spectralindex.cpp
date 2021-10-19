#include "spectral_container.h"
/* Zawiera metody do obliczania VI, FI i chi2red */

void spectral_container::spectralIndex4Pol(int begin_epoch, int end_epoch, double relativeError)
{
    // wektory, przechowujące widma x 4:
    std::vector < std::vector < double > > VIContainer, FIContainer, CHI2REDContainer;
    // dodajemy do VI Container widma
    VIContainer.push_back(viSpectralIndex1Pol(begin_epoch, end_epoch, spectraTableI, spectraTableIERR, relativeError));
    VIContainer.push_back(viSpectralIndex1Pol(begin_epoch, end_epoch, spectraTableV, spectraTableVERR, relativeError));
    VIContainer.push_back(viSpectralIndex1Pol(begin_epoch, end_epoch, spectraTableLHC, spectraTableLHCERR, relativeError));
    VIContainer.push_back(viSpectralIndex1Pol(begin_epoch, end_epoch, spectraTableRHC, spectraTableRHCERR, relativeError));

    FIContainer.push_back(fiSpectralIndex1Pol(begin_epoch, end_epoch, spectraTableI, spectraTableIERR, relativeError));
    FIContainer.push_back(fiSpectralIndex1Pol(begin_epoch, end_epoch, spectraTableV, spectraTableIERR, relativeError));
    FIContainer.push_back(fiSpectralIndex1Pol(begin_epoch, end_epoch, spectraTableLHC, spectraTableIERR, relativeError));
    FIContainer.push_back(fiSpectralIndex1Pol(begin_epoch, end_epoch, spectraTableRHC, spectraTableIERR, relativeError));
    /*
    CHI2REDContainer.push_back(chi2SpectralIndex1Pol(begin_epoch, end_epoch, spectraTableI, spectraTableIERR, relativeError));
    CHI2REDContainer.push_back(chi2SpectralIndex1Pol(begin_epoch, end_epoch, spectraTableV, spectraTableIERR, relativeError));
    CHI2REDContainer.push_back(chi2SpectralIndex1Pol(begin_epoch, end_epoch, spectraTableLHC, spectraTableIERR, relativeError));
    CHI2REDContainer.push_back(chi2SpectralIndex1Pol(begin_epoch, end_epoch, spectraTableRHC, spectraTableIERR, relativeError));
    */

    saveVItoFile(begin_epoch, end_epoch, relativeError, VIContainer);
    saveFItoFile(begin_epoch, end_epoch, relativeError, VIContainer);


}

std::vector < double > spectral_container::fiSpectralIndex1Pol(int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError)
{
    std::vector < double > spectrumOfFI( (int) poltab[begin_epoch-1].size());
    for(unsigned long int i = 0; i < poltab[begin_epoch-1].size(); i++)
    {
        spectrumOfFI[i] = fiSpectralIndex1channel(i+1, begin_epoch, end_epoch, poltab, errors, relativeError);
    }
    return spectrumOfFI;
}

std::vector < double > spectral_container::viSpectralIndex1Pol(int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError)
{
    std::vector < double > spectrumOfVI( (int) poltab[begin_epoch-1].size());
    for(unsigned long int i = 0; i < poltab[begin_epoch-1].size(); i++)
    {
        spectrumOfVI[i] = viSpectralIndex1channel(i+1, begin_epoch, end_epoch, poltab, errors, relativeError);
    }
    return spectrumOfVI;

}

double spectral_container::fiSpectralIndex1channel(int channel, int begin_epoch, int end_epoch, std::vector<std::vector<double> > &poltab, std::vector<double> &errors, double relativeError)
{
    // TZW. STANDARDOWE UMIEJĘTNOŚCI MAGICZNE
    double sum1 = 0.0;
    double sum2 = 0.0;
    double sum3 = 0.0;
    double sum_to_mean = 0.0;
    double counter_to_mean = 0.0;

    // właściwa pętla licząca
    for(int i = begin_epoch-1; i < end_epoch; i++)
    {
        double flux = poltab[i][channel-1];
        double err = errors[i] + relativeError * flux;
        double weight = 1.0 / err;
        sum1 = sum1 + flux*flux * weight;
        sum2 = sum2 + flux * weight;
        sum3 = sum3 + weight;
        sum_to_mean = sum_to_mean + flux;
        counter_to_mean = counter_to_mean + 1.0;

    }
    sum_to_mean = sum_to_mean / counter_to_mean;
    // obliczamy FI
    double FI;
    if ( (begin_epoch - end_epoch) == 0.0 || counter_to_mean == 1.0 || sum1 == 0.0 || sum2 == 0.0)
        FI = 0.0;
    else
        FI = sqrt(abs((((sum1 - sum2)/(counter_to_mean-1.0)) - 1.0) * counter_to_mean / sum3)) * 1.0 / sum_to_mean;

    if(FI < 0.0)
        FI = 0.0;

    return FI;
}

double spectral_container::viSpectralIndex1channel(int channel, int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError)
{
    double minFlux, maxFlux, minFluxError, maxFluxError;
    std::vector < double > MinMaxErr = calculateMinAndMax(channel, begin_epoch, end_epoch, poltab, errors, relativeError);

    minFlux = MinMaxErr[0];
    minFluxError = MinMaxErr[1];
    maxFlux = MinMaxErr[2];
    maxFluxError = MinMaxErr[3];

    // liczymy
    double VI = 0.0;
    if( (maxFlux > 3.0 * maxFluxError) && ( ((maxFlux - maxFluxError) - (minFlux + minFluxError)) > 0.1 ) )
        VI = ((maxFlux - maxFluxError) - (minFlux + minFluxError)) / ((maxFlux - maxFluxError) + (minFlux + minFluxError));

    return VI;


}

std::vector < double > spectral_container::calculateMinAndMax(int channel, int begin_epoch, int end_epoch, std::vector<std::vector<double> > &poltab, std::vector<double> &errors, double relativeError)
{
    // double
    double minFlux = 0.0;
    double maxFlux = 0.0;
    double minFluxError = 0.0;
    double maxFluxError = 0.0;
    // zwracany kontener
    std::vector < double > returned_container(4);
    returned_container[0] = minFlux;
    returned_container[1] = minFluxError;
    returned_container[2] = maxFlux;
    returned_container[3] = maxFluxError;

    // ustalamy wstępny minFlux
    for(int i = begin_epoch-1; i < end_epoch; i++)
    {
        if (poltab[i][channel-1] >= 0.0)
        {
            // min
            minFlux = poltab[i][channel-1];
            minFluxError = errors[i] + minFlux * relativeError;
            // max też
            maxFlux = minFlux;
            maxFluxError = minFluxError;
            // wychodzimy z pętli
            break;
        }
    }

    // sprawdzamy, czy cokolwiek się zapisał
    if (minFlux == 0.0 && maxFlux == 0.0 && minFluxError == 0.0 && maxFluxError == 0.0)
    {
        return returned_container;
    }

    // właściwa pętla do liczenia minmax
    // min
    for(int i = begin_epoch-1; i < end_epoch; i++)
    {
        if (poltab[i][channel-1] < minFlux && poltab[i][channel-1] >= 0.0)
        {
            minFlux = poltab[i][channel-1];
            minFluxError = errors[i] + minFlux * relativeError;
        }

        if (poltab[i][channel-1] > maxFlux && poltab[i][channel-1] >= 0.0)
        {
            maxFlux = poltab[i][channel-1];
            maxFluxError = errors[i] + maxFlux * relativeError;
        }
    }
    // ustalamy wartości w kontenerze
    returned_container[0] = minFlux;
    returned_container[1] = minFluxError;
    returned_container[2] = maxFlux;
    returned_container[3] = maxFluxError;
    return returned_container;
}

std::string spectral_container::getFIFileName(int begin_epoch, int end_epoch)
{
    std::string viFileName;
    viFileName = saveDirectory + "/" + nameOfSource + "_FI_spectrum_from_epoch_" + std::to_string(begin_epoch) + "_to_" + std::to_string(end_epoch) + ".dat";
    return viFileName;
}

std::string spectral_container::getVIFileName(int begin_epoch, int end_epoch)
{
    std::string viFileName;
    viFileName = saveDirectory + "/" + nameOfSource + "_VI_spectrum_from_epoch_" + std::to_string(begin_epoch) + "_to_" + std::to_string(end_epoch) + ".dat";
    return viFileName;
}

void spectral_container::saveVItoFile(int begin_epoch, int end_epoch, double relativeError, std::vector<std::vector<double> > & VIContainer)
{
    // otwieramy plik do zapistwania
    std::ofstream viFle;
    viFle.open(getVIFileName(begin_epoch, end_epoch).c_str());
    int columnw = 13;
    // piszemy nagłówek pliku
    viFle << "# ----------------------------------------------" << std::endl;
    viFle << "# VI from epoch " << begin_epoch << " to " << end_epoch << std::endl;
    viFle << "# time range (MJD): " << mjdTable[begin_epoch-1] << " to " << mjdTable[end_epoch-1] << std::endl;
    viFle << "# time range (ISO): " << isotimeTable[begin_epoch-1] << " to " << isotimeTable[end_epoch-1] << std::endl;
    if (relativeError != 0.0)
        viFle << "# Applied relative calibration error of " << relativeError << std::endl;
    viFle << "# columns:" << std::endl;
    viFle << "# " << std::left << std::setw(columnw) << "channel "<< std::setw(columnw) << "V_lsr (km/s)  ";
    viFle << std::setw(columnw) << "I "<< std::setw(columnw) << "V ";
    viFle << std::setw(columnw) << "LHC ";
    viFle << std::setw(columnw) << "RHC " << std::endl;
    viFle << "# ----------------------------------------------" << std::endl;

    // pętla, zapisująca dane
    for (int i = 0; i < VIContainer[0].size(); i++)
    {
        viFle << std::right << std::fixed << std::setprecision(7) << std::setw(12) << channelTable[begin_epoch-1][i] << " " << std::setw(12) << velocityTable[begin_epoch-1][i] << " ";
        // dane (pętla po I,V,RHC,LHC)
        for (int polind = 0; polind < 4; polind++)
        {
            viFle << std::setw(12) << VIContainer[polind][i] << " ";
        }
        viFle << std::endl;
    }
    // zamykamy plik
    viFle.close();
}

void spectral_container::saveFItoFile(int begin_epoch, int end_epoch, double relativeError, std::vector<std::vector<double> > &FIContainer)
{
    // otwieramy plik do zapistwania
    std::ofstream fiFle;
    fiFle.open(getFIFileName(begin_epoch, end_epoch).c_str());
    int columnw = 13;
    // piszemy nagłówek pliku
    fiFle << "# ----------------------------------------------" << std::endl;
    fiFle << "# FI from epoch " << begin_epoch << " to " << end_epoch << std::endl;
    fiFle << "# time range (MJD): " << mjdTable[begin_epoch-1] << " to " << mjdTable[end_epoch-1] << std::endl;
    fiFle << "# time range (ISO): " << isotimeTable[begin_epoch-1] << " to " << isotimeTable[end_epoch-1] << std::endl;
    if (relativeError != 0.0)
        fiFle << "# Applied relative calibration error of " << relativeError << std::endl;
    fiFle << "# columns:" << std::endl;
    fiFle << "# " << std::left << std::setw(columnw) << "channel "<< std::setw(columnw) << "V_lsr (km/s)  ";
    fiFle << std::setw(columnw) << "I "<< std::setw(columnw) << "V ";
    fiFle << std::setw(columnw) << "LHC ";
    fiFle << std::setw(columnw) << "RHC " << std::endl;
    fiFle << "# ----------------------------------------------" << std::endl;

    // pętla, zapisująca dane
    for (int i = 0; i < FIContainer[0].size(); i++)
    {
        fiFle << std::right << std::fixed << std::setprecision(7) << std::setw(12) << channelTable[begin_epoch-1][i] << " " << std::setw(12) << velocityTable[begin_epoch-1][i] << " ";
        // dane (pętla po I,V,RHC,LHC)
        for (int polind = 0; polind < 4; polind++)
        {
            fiFle << std::setw(12) << FIContainer[polind][i] << " ";
        }
        fiFle << std::endl;
    }
    // zamykamy plik
    fiFle.close();
}
