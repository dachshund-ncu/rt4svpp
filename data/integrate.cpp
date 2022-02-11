#include "spectral_container.h"
/*
Ten plik źródłowy przechowuje kod z metodami do liczenia
całki z widm
*/

void spectral_container::integrate4Pols(int min_channel, int max_channel, bool isotimeInclude)
{
    std::vector < std::vector < double > > integrationResults, integrationErrs;
    // wyniki integracji
    integrationResults.push_back(integratePol(min_channel, max_channel, velocityTable, spectraTableI));
    integrationResults.push_back(integratePol(min_channel, max_channel, velocityTable, spectraTableV));
    integrationResults.push_back(integratePol(min_channel, max_channel, velocityTable, spectraTableLHC));
    integrationResults.push_back(integratePol(min_channel, max_channel, velocityTable, spectraTableRHC));
    // niepewności
    integrationErrs.push_back(integratePolErr(velocityTable, spectraTableIERR));
    integrationErrs.push_back(integratePolErr(velocityTable, spectraTableVERR));
    integrationErrs.push_back(integratePolErr(velocityTable, spectraTableLHCERR));
    integrationErrs.push_back(integratePolErr(velocityTable, spectraTableRHCERR));
    // zapisujemy do pliku
    saveIntegrationToFile(min_channel, max_channel, integrationResults, integrationErrs, isotimeInclude);
}

std::vector < double > spectral_container::integratePol(int min_channel, int max_channel, std::vector<std::vector<double> > &veltab, std::vector<std::vector<double> > &poltab)
{
    // deklarujemy tablicę, do której będziemy zapisywać wartości
    std::vector < double > integration_res(poltab.size());
    // w pętli liczymy kolejne wartości całki
    for (unsigned long int i = 0; i < poltab.size(); i++)
    {
        integration_res[i] = integrateSingleEpoch(min_channel, max_channel, veltab[i], poltab[i]);
    }
    return integration_res;
}

std::vector < double > spectral_container::integratePolErr(std::vector<std::vector<double> > &veltab, std::vector<double> &errtab)
{
    std::vector < double > errors(errtab.size());

    for(unsigned long int i = 0.0; i < errtab.size(); i++)
    {
        errors[i] = integrateSingleEpochErr(veltab[i], errtab[i]);
    }
    return errors;
}

double spectral_container::integrateSingleEpoch(int min_channel, int max_channel, std::vector<double> veltab, std::vector<double> poltab)
{
    // zabezpieczenie
    if (min_channel < 1)
        min_channel = 1;
    if (max_channel > (int) poltab.size())
        max_channel = (int) poltab.size();

    // tutaj będzie się dziać cała całkowa magia
    double suma = 0.0; // suma całki
    double h = abs(veltab[1] - veltab[0]);
    // pętla, licząca całkę
    for(int i = min_channel-1; i < max_channel; i++)
    {
        if(i == min_channel - 1 || i == max_channel-1)
            suma = suma + poltab[i] / 2.0;
        else
            suma = suma + poltab[i];
    }
    suma = suma * h;
    return suma;
}

double spectral_container::integrateSingleEpochErr(std::vector<double> veltab, double epochRms)
{
    double h = abs(veltab[1] - veltab[0]);
    double error = epochRms * 5.0 * h;
    return error;
}

void spectral_container::saveIntegrationToFile(int min_channel, int max_channel, std::vector<std::vector<double> > &integrationResults, std::vector<std::vector<double> > &integrationErrors, bool isotimeInclude)
{
    // otwieramy plik do zapistwania
    std::ofstream integ;
    integ.open(getIntegrationFileName(min_channel, max_channel).c_str());

    int columnw = 14;
    // piszemy nagłówek pliku
    integ << "# ----------------------------------------------" << std::endl;
    integ << "# integrated from channel " << min_channel << " to " << max_channel << std::endl;
    integ << "# velocity range: " << velocityTable[0][min_channel-1] << " to " << velocityTable[0][max_channel-1] << " km/s" << std::endl;
    integ << "# columns:" << std::endl;
    integ << "# " << std::left;
    if(isotimeInclude)
        integ << std::setw(columnw+14) << "time_in_isoformat ";

    integ << std::setw(columnw) << "MJD  " << std::setw(columnw+3) << "year ";
    integ << std::setw(columnw) << "I " << std::setw(columnw) << "+/- ";
    integ << std::setw(columnw) << "V " << std::setw(columnw) << "+/- ";
    integ << std::setw(columnw) << "LHC " << std::setw(columnw) << "+/- ";
    integ << std::setw(columnw) << "RHC " << std::setw(columnw) << "+/- " << std::endl;
    integ << "# ----------------------------------------------" << std::endl;

    // pętla, zapisująca dane
    for (int i = 0; i < (int) integrationResults[0].size(); i++)
    {
        // czas
        if (isotimeInclude)
        {
            integ << std::right << std::fixed << std::setprecision(7) << isotimeTable[i] << " ";
        }
        integ << std::right << std::fixed << std::setprecision(7) << std::setw(columnw+1) << mjdTable[i] << " " << std::setw(columnw-1) << decyrTable[i] << " ";
        // dane (pętla po I,V,RHC,LHC)
        for (int polind = 0; polind < 4; polind++)
            integ << std::setw(columnw-1) << integrationResults[polind][i] << " " << std::setw(columnw-1) << integrationErrors[polind][i] << " "; // I
        integ << std::endl;
    }

    // zamykamy plik
    integ.close();
}

std::string spectral_container::getIntegrationFileName(int min_channel, int max_channel)
{
    std::string integration_file_name = saveDirectory + "/" + nameOfSource + "_integrated_from_" + std::to_string(min_channel) + "_to_" + std::to_string(max_channel) + ".dat";
    return integration_file_name;
}

std::vector < std::vector < double > > spectral_container::getIntegrate(int min_channel, int max_channel)
{
    std::vector < std::vector < double > > integrationResults;
    // wyniki integracji
    integrationResults.push_back(integratePol(min_channel, max_channel, velocityTable, spectraTableI));
    integrationResults.push_back(integratePol(min_channel, max_channel, velocityTable, spectraTableV));
    integrationResults.push_back(integratePol(min_channel, max_channel, velocityTable, spectraTableLHC));
    integrationResults.push_back(integratePol(min_channel, max_channel, velocityTable, spectraTableRHC));
    return integrationResults;
}
