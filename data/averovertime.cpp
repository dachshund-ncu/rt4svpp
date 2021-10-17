#include "spectral_container.h"
/*
Ten plik źródłowy przechowuje kod z metodami do liczenia
średniej po czasie
*/

void spectral_container::averOverTime4Pols(int begin_epoch, int end_epoch)
{
    std::vector < std::vector < double > > results;
    std::vector < double > errors;
    results.push_back(averOverTime1Pol(begin_epoch, end_epoch, spectraTableI));
    results.push_back(averOverTime1Pol(begin_epoch, end_epoch, spectraTableV));
    results.push_back(averOverTime1Pol(begin_epoch, end_epoch, spectraTableLHC));
    results.push_back(averOverTime1Pol(begin_epoch, end_epoch, spectraTableRHC));

    errors.push_back(averOverTime1PolErr(begin_epoch, end_epoch, spectraTableIERR));
    errors.push_back(averOverTime1PolErr(begin_epoch, end_epoch, spectraTableVERR));
    errors.push_back(averOverTime1PolErr(begin_epoch, end_epoch, spectraTableLHCERR));
    errors.push_back(averOverTime1PolErr(begin_epoch, end_epoch, spectraTableRHCERR));

    saveAverOverTime(begin_epoch, end_epoch, results, errors);
}

std::vector < double > spectral_container::averOverTime1Pol(int begin_epoch, int end_epoch, std::vector < std::vector < double > > & fluxes)
{
    // zwracany kontener
    std::vector < double > resultingAverage((int) fluxes[0].size());

    // pętla - i leci tutaj po kanałach
    for(unsigned long int i = 0; i < fluxes[0].size(); i++)
    {
        resultingAverage[i] = averagedOverChannel(i, begin_epoch, end_epoch, fluxes);
    }

    return resultingAverage;
}

double spectral_container::averagedOverChannel(int channelNumber, int begin_epoch, int end_epoch, std::vector < std::vector < double > > & fluxes)
{
    double sum = 0.0; // suma średniej
    double count = 0.0; // licznik pętli, ale w double by dzielenie było łatwe

    // pętla - i leci tutaj po epokach, nr. kanału jest stały
    for (int i = begin_epoch - 1; i < end_epoch; i++)
    {
        sum = sum + fluxes[i][channelNumber];
        count = count + 1.0;
    }
    sum = sum / count;

    return sum;

}

double spectral_container::averOverTime1PolErr(int begin_epoch, int end_epoch, std::vector< double > & errors)
{
    double sum = 0.0; // suma średniej
    double count = 0.0; // licznik pętli, ale w double by dzielenie było łatwe

    for(int i = begin_epoch - 1; i < end_epoch; i++)
    {
        sum = sum + errors[i];
        count = count + 1.0;
    }
    sum = sum / count;

    return sum;
}

std::string spectral_container::getAverOverTimeFileName(int begin_epoch, int end_epoch)
{
    std::string averFileName;
    averFileName = saveDirectory + "/" + nameOfSource + "_averaged_over_time_from_" + std::to_string(begin_epoch) + "_to_" + std::to_string(end_epoch) + ".dat";
    return averFileName;
}

void spectral_container::saveAverOverTime(int begin_epoch, int end_epoch, std::vector<std::vector<double> > &results, std::vector<double> &errors)
{
    // otwieramy plik do zapistwania
    std::ofstream averTime;
    averTime.open(getAverOverTimeFileName(begin_epoch, end_epoch).c_str());

    int columnw = 13;
    // piszemy nagłówek pliku
    averTime << "# ----------------------------------------------" << std::endl;
    averTime << "# averaged over time from epoch " << begin_epoch << " to " << end_epoch << std::endl;
    averTime << "# time range (MJD): " << mjdTable[begin_epoch-1] << " to " << mjdTable[end_epoch-1] << std::endl;
    averTime << "# time range (ISO): " << isotimeTable[begin_epoch-1] << " to " << isotimeTable[end_epoch-1] << std::endl;
    averTime << "# columns:" << std::endl;
    averTime << "# " << std::left << std::setw(columnw) << "channel "<< std::setw(columnw) << "V_lsr (km/s)  ";
    averTime << std::setw(columnw) << "I "<< std::setw(columnw) << "+/- "<< std::setw(columnw) << "V ";
    averTime << std::setw(columnw) << "+/- " << std::setw(columnw) << "LHC " << std::setw(columnw) << "+/- ";
    averTime << std::setw(columnw) << "RHC " << std::setw(columnw) << "+/- " << std::endl;
    averTime << "# ----------------------------------------------" << std::endl;

    // pętla, zapisująca dane
    for (int i = 0; i < (int) results[0].size(); i++)
    {
        averTime << std::right << std::fixed << std::setprecision(7) << std::setw(12) << channelTable[begin_epoch-1][i] << " " << std::setw(12) << velocityTable[begin_epoch-1][i] << " ";
        // dane (pętla po I,V,RHC,LHC)
        for (int polind = 0; polind < 4; polind++)
            averTime << std::setw(12) << results[polind][i] << " " << std::setw(12) << errors[polind] << " ";
        averTime << std::endl;
    }

    // zamykamy plik
    averTime.close();
}
