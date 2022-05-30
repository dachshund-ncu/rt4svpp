#include "spectral_container.h"
/*
 * This set of methods aims to extract the light curve from a given range of channels
 * Approach used to achieve this will be:
 * 1. find 3 brightest channels
 * 2. average their brightness
 * 3. average their velocity
 * 4. do this for whole time range
 * 5. save to a file
 * See? Ez.
*/

void spectral_container::extractLCS4Pol(int min_channel, int max_channel, bool isotimeInclude = false)
{
    /*
     * This is the main method, only "public" one
     * Here, we use more specialized methods to calculate this 3-channel average
     * We store results in 2D containers: I,V,LHC,RHC
     * Also we store calculated velocities in other container
     * Vel table is passed as a reference to the extractLCSFromChannelRange method
     */
    std::vector < std::vector < double > > extractingResults, extractingErrors;
    std::vector < double > extractingVels;
    // --
    extractingResults = extractLCSFromChannelRange(min_channel, max_channel, extractingVels);
    extractingErrors.push_back(spectraTableIERR);
    extractingErrors.push_back(spectraTableVERR);
    extractingErrors.push_back(spectraTableLHCERR);
    extractingErrors.push_back(spectraTableRHCERR);
    // --
    saveExtractingToFile(min_channel, max_channel, extractingResults, extractingErrors, extractingVels, isotimeInclude);

}

std::vector < std::vector < double > > spectral_container::extractLCSFromChannelRange(int min_channel, int max_channel, std::vector<double> &extractingVels)
{
    /*
     * We take this few-channel chunk for every epoch, sort it and take three highest of value
     * tmp = {I, V, LHC, RHC, Vel}
     */
    std::vector < std::vector < double > > returnedTable;
    std::vector < double > Itmp, Vtmp, LHCtmp, RHCtmp;
    for(unsigned long int i = 0; i < mjdTable.size(); i++)
    {
        std::vector < double > tmp = extractLCSSingleEpoch(min_channel, max_channel, i);
        Itmp.push_back(tmp[0]);
        Vtmp.push_back(tmp[1]);
        LHCtmp.push_back(tmp[2]);
        RHCtmp.push_back(tmp[3]);
        extractingVels.push_back(tmp[4]);
    }
    returnedTable.push_back(Itmp);
    returnedTable.push_back(Vtmp);
    returnedTable.push_back(LHCtmp);
    returnedTable.push_back(RHCtmp);
    return returnedTable;
}

std::vector < double > spectral_container::extractLCSSingleEpoch(int min_channel, int max_channel, unsigned long epochIndex)
{
    /*
     * Simply extracts the single epoch for the extracted light curve
     */
    std::vector < double > returnedValues(5);
    // -- filling chunks of data --
    std::vector < double > chunkI = fillChunk(min_channel, max_channel, epochIndex, spectraTableI);
    std::vector < double > chunkV = fillChunk(min_channel, max_channel, epochIndex, spectraTableV);
    std::vector < double > chunkLHC = fillChunk(min_channel, max_channel, epochIndex, spectraTableLHC);
    std::vector < double > chunkRHC = fillChunk(min_channel, max_channel, epochIndex, spectraTableRHC);
    std::vector < double > chunkVel = fillChunk(min_channel, max_channel, epochIndex, velocityTable);
    // -- sorting chunks of data by I --
    sortChunks(chunkI, chunkV, chunkLHC, chunkRHC, chunkVel);
    // -- getting mean of three highest --
    return getMeanOf3Highest(chunkI, chunkV, chunkLHC, chunkRHC, chunkVel);
}

std::vector < double > spectral_container::fillChunk(int min_channel, int max_channel, unsigned long epochIndex, std::vector<std::vector<double> > &poltab)
{
    /*
     * Assumes max_channel >= min_channel!
     * min_channel and max_channel are INCLUDED
     * so true length of a chunk will be max_channel - min_channel + 1!
     * e.g. channel 1045 - 1051:
     * we will use channels: {1045, 1046, 1047, 1048, 1049, 1050, 1051}
     */
    std::vector < double > returnedChunk;
    returnedChunk.reserve(max_channel - min_channel + 1);
    for(int i = min_channel-1; i < max_channel; i++)
    {
        returnedChunk.push_back(poltab[epochIndex][i]); // i is an INDEX, while CHANNEL is i+1
    }
    return returnedChunk;
}

void spectral_container::sortChunks(std::vector<double> &Itab, std::vector<double> &Vtab, std::vector<double> &LHCtab, std::vector<double> &RHCtab, std::vector<double> &tabWVel)
{
    /*
     * This method induces basic bubble-sort alghorithm and some failsafes in case, there is less, than 3 channels
     */
    for(unsigned long int i = 0; i < Itab.size()-1; i++)
    {
        for(unsigned long int j = i+1; j < Itab.size(); j++)
        {
            if (Itab[j] < Itab[i])
            {
                swapD(Itab, i, j); // simply swaps the index i -> j
                swapD(Vtab, i, j);
                swapD(LHCtab, i, j);
                swapD(RHCtab, i, j);
                swapD(tabWVel, i, j);
            }
        }
    }
    // NO RETURN SINCE IT IS VOID AND OPERATES ON REFERENCES
}

std::vector < double > spectral_container::getMeanOf3Highest(std::vector<double> &Itab, std::vector<double> &Vtab, std::vector<double> &LHCtab, std::vector<double> &RHCtab, std::vector<double> &tabWVel)
{
    /*
     * Assumes, that tables taken by the reference are SORTED BY I
     */
    // -- returned vector --
    std::vector < double > returnedArray;
    returnedArray.reserve(5);
    // -- couple of failsafes --
    if (Itab.size() < 1)
    {
        returnedArray = {0.0, 0.0, 0.0, 0.0, 0.0};
    }
    if (Itab.size() == 1)
    {
        returnedArray = {Itab[0], Vtab[0], LHCtab[0], RHCtab[0], tabWVel[0]};
    }
    else if (Itab.size() == 2)
    {
        returnedArray.push_back((Itab[0] + Itab[1]) / 2.0 ) ;
        returnedArray.push_back((Vtab[0] + Vtab[1]) / 2.0 );
        returnedArray.push_back((LHCtab[0] + LHCtab[1]) / 2.0 );
        returnedArray.push_back((RHCtab[0] + RHCtab[1]) / 2.0 );
        returnedArray.push_back((tabWVel[0] + tabWVel[1]) / 2.0 );
    }
    else
    {
        returnedArray.push_back(average3Last(Itab));
        returnedArray.push_back(average3Last(Vtab));
        returnedArray.push_back(average3Last(LHCtab));
        returnedArray.push_back(average3Last(RHCtab));
        returnedArray.push_back(average3Last(tabWVel));
    }
    return returnedArray;
}

double spectral_container::average3Last(std::vector<double> & tab)
{
    /*
     * Simply takes the <tab> and averages three last items of it
     * assumes TAB already has at least THREE elements
     * should be invoked only in getMeanOf3Highest (look up ^ )
     * -- loop helper: --
     * for a 7 element array:
     * i = 6 (arr.size() - 1)
     * i = 5
     * i = 4
     * end (i > arr.size() - 1 - 3)
    */
    double sum = 0.0;
    for(unsigned long int i = tab.size() - 1; i > tab.size()-1 -3; i--)
    {
        sum += tab[i];
    }
    sum /= 3.0;
    return sum;
}

void spectral_container::saveExtractingToFile(int min_channel, int max_channel, std::vector<std::vector<double> > &extractingResults, std::vector<std::vector<double> > &extractingErrors, std::vector < double > & extractingVels, bool isotimeInclude)
{
    // otwieramy plik do zapistwania
    std::ofstream extractVel;
    extractVel.open(getExtractedFileName(min_channel, max_channel).c_str());

    int columnw = 14;
    // piszemy nagłówek pliku
    extractVel << "# ----------------------------------------------" << std::endl;
    extractVel << "# velocity-extracted light curve from channel " << min_channel << " to " << max_channel << std::endl;
    extractVel << "# velocity range of extraction: " << velocityTable[0][min_channel-1] << " to " << velocityTable[0][max_channel-1] << " km/s" << std::endl;
    extractVel << "# light curve created by averaging three brightest channels in requested channel range" << std::endl;
    extractVel << "# columns:" << std::endl;
    extractVel << "# " << std::left;
    if(isotimeInclude)
        extractVel << std::setw(columnw+14) << "time_in_isoformat ";
    extractVel << std::setw(columnw) << "MJD  " << std::setw(columnw+3) << "year ";
    extractVel << std::setw(columnw) << "V_central ";
    extractVel << std::setw(columnw) << "I " << std::setw(columnw) << "+/- ";
    extractVel << std::setw(columnw) << "V " << std::setw(columnw) << "+/- ";
    extractVel << std::setw(columnw) << "LHC " << std::setw(columnw) << "+/- ";
    extractVel << std::setw(columnw) << "RHC " << std::setw(columnw) << "+/- " << std::endl;
    extractVel << "# ----------------------------------------------" << std::endl;

    for (int i = 0; i < (int) extractingResults[0].size(); i++)
    {
        // czas
        if (isotimeInclude)
        {
            extractVel << std::right << std::fixed << std::setprecision(7) << isotimeTable[i] << " ";
        }
        extractVel << std::right << std::fixed << std::setprecision(7) << std::setw(columnw+1) << mjdTable[i] << " " << std::setw(columnw-1) << decyrTable[i] << " " << std::setw(columnw) << extractingVels[i] << " ";
        // dane (pętla po I,V,RHC,LHC)
        for (int polind = 0; polind < 4; polind++)
            extractVel << std::setw(columnw-1) << extractingResults[polind][i] << " " << std::setw(columnw-1) << extractingErrors[polind][i] << " ";
        extractVel << std::endl;
    }
    extractVel.close();
}

std::string spectral_container::getExtractedFileName(int min_channel, int max_channel)
{
    std::string extractFileName;
    extractFileName = saveDirectory + "/" + nameOfSource + "_extracted_over_velocity_from_" + std::to_string(min_channel) + "_to_" + std::to_string(max_channel) + ".dat";
    return extractFileName;
}
