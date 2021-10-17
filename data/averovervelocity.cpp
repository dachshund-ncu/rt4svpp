#include "spectral_container.h"
/*
Ten plik źródłowy przechowuje kod z metodami do liczenia
średniej po prędkościach
*/

void spectral_container::averageOverVelocity4Pols(int min_channel, int max_channel, bool isotimeInclude)
{
    std::vector < std::vector < double > > averaging_results, errors_of_aver;
    // średnie liczymy
    averaging_results.push_back(averagePolOverVelocity(min_channel, max_channel, spectraTableI));
    averaging_results.push_back(averagePolOverVelocity(min_channel, max_channel, spectraTableV));
    averaging_results.push_back(averagePolOverVelocity(min_channel, max_channel, spectraTableLHC));
    averaging_results.push_back(averagePolOverVelocity(min_channel, max_channel, spectraTableRHC));

    errors_of_aver.push_back(spectraTableIERR);
    errors_of_aver.push_back(spectraTableVERR);
    errors_of_aver.push_back(spectraTableLHCERR);
    errors_of_aver.push_back(spectraTableRHCERR);
    // zapisujemy do pliku
    saveAveragingToFile(min_channel, max_channel, averaging_results, errors_of_aver, isotimeInclude);

}

std::vector < double > spectral_container::averagePolOverVelocity(int min_channel, int max_channel, std::vector<std::vector<double> > &fluxtab)
{
    // deklarujemy zwracaną tablicę z wynikami
    std::vector < double > resultOfAveraging(fluxtab.size());

    // pętla
    for(unsigned long int i = 0; i < fluxtab.size(); i++)
    {
        resultOfAveraging[i] = averageEpochOverVelocity(min_channel, max_channel, fluxtab[i]);
    }

    return resultOfAveraging;
}

double spectral_container::averageEpochOverVelocity(int min_channel, int max_channel, std::vector<double> fluxtab)
{
    // suma ze średnią
    double sum = 0.0;
    double chan_count = 0.0;

    // pętla, licząca średnią - w argumentach są kanały, my używamy indeksów rakże jest min_channel -1
    if( min_channel == max_channel)
    {
        sum = fluxtab[min_channel-1];
    }
    else
    {
        for(int i = min_channel - 1; i < max_channel; i++)
        {
            sum = sum + fluxtab[i];
            chan_count = chan_count + 1.0;
        }
        sum = sum / chan_count;
    }
    return sum;
}

void spectral_container::saveAveragingToFile(int min_channel, int max_channel, std::vector<std::vector<double> > & averagingResults, std::vector < std::vector < double > > & errors, bool isotimeInclude)
{
    // otwieramy plik do zapistwania
    std::ofstream averVel;
    averVel.open(getAverOverVelFileName(min_channel, max_channel).c_str());

    int columnw = 14;
    // piszemy nagłówek pliku
    averVel << "# ----------------------------------------------" << std::endl;
    averVel << "# averaged over velocity from channel " << min_channel << " to " << max_channel << std::endl;
    averVel << "# velocity range: " << velocityTable[0][min_channel-1] << " to " << velocityTable[0][max_channel-1] << " km/s" << std::endl;
    averVel << "# central velocity: " << getCentralVelocityOfAveraging(min_channel, max_channel) << " km/s" << std::endl;
    averVel << "# columns:" << std::endl;
    averVel << "# " << std::left;
    if(isotimeInclude)
        averVel << std::setw(columnw+14) << "time_in_isoformat ";

    averVel << std::setw(columnw) << "MJD  " << std::setw(columnw+3) << "year ";
    averVel << std::setw(columnw) << "I " << std::setw(columnw) << "+/- ";
    averVel << std::setw(columnw) << "V " << std::setw(columnw) << "+/- ";
    averVel << std::setw(columnw) << "LHC " << std::setw(columnw) << "+/- ";
    averVel << std::setw(columnw) << "RHC " << std::setw(columnw) << "+/- " << std::endl;
    averVel << "# ----------------------------------------------" << std::endl;

    // pętla, zapisująca dane
    for (int i = 0; i < (int) averagingResults[0].size(); i++)
    {
        // czas
        if (isotimeInclude)
        {
            averVel << std::right << std::fixed << std::setprecision(7) << isotimeTable[i] << " ";
        }
        averVel << std::right << std::fixed << std::setprecision(7) << std::setw(columnw+1) << mjdTable[i] << " " << std::setw(columnw-1) << decyrTable[i] << " ";
        // dane (pętla po I,V,RHC,LHC)
        for (int polind = 0; polind < 4; polind++)
            averVel << std::setw(columnw-1) << averagingResults[polind][i] << " " << std::setw(columnw-1) << errors[polind][i] << " ";
        averVel << std::endl;
    }

    // zamykamy plik
    averVel.close();
}

std::string spectral_container::getAverOverVelFileName(int min_channel, int max_channel)
{
    std::string averFileName;
    if (min_channel != max_channel)
        averFileName = saveDirectory + "/" + nameOfSource + "_averaged_over_velocity_from_" + std::to_string(min_channel) + "_to_" + std::to_string(max_channel) + ".dat";
    else
        averFileName = saveDirectory + "/" + nameOfSource + "_lc_over_channel_" + std::to_string(min_channel) + ".dat";

    return averFileName;
}

double spectral_container::getCentralVelocityOfAveraging(int min_channel, int max_channel)
{
    // liczymy średnią z prędkości
    double sum = 0.0;
    double count = 0.0;

    for(int i = min_channel - 1; i < max_channel; i++)
    {
        sum = sum + velocityTable[0][i];
        count = count + 1.0;
    }
    sum = sum / count;
    return sum;
}
