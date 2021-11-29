#include "spectral_container.h"
/*
 * Ten plik źródłowy przechowuje metody, związane z kalibracją danych
 */
void spectral_container::calibrateEpoch(int epochNr, bool direction)
{
    // prosta pętla
    double MJD = mjdTable[epochNr - 1];
    double calCoeffLHC = findCalCoeff(caltabLHCMjd, caltabLHC, MJD);
    double calCoeffRHC = findCalCoeff(caltabRHCMjd, caltabRHC, MJD);
    for(unsigned long int i = 0; i < spectraTableLHC[epochNr-1].size(); i++)
    {
        if(direction)
        {
            spectraTableLHC[epochNr-1][i] *= calCoeffLHC;
            spectraTableRHC[epochNr-1][i] *= calCoeffRHC;
        }
        else
        {
            spectraTableLHC[epochNr-1][i] /= calCoeffLHC;
            spectraTableRHC[epochNr-1][i] /= calCoeffRHC;
        }
    }
    if(direction)
    {
        spectraTableLHCERR[epochNr-1] *= calCoeffLHC;
        spectraTableRHCERR[epochNr-1] *= calCoeffRHC;
    }
    else
    {
        spectraTableLHCERR[epochNr-1] /= calCoeffLHC;
        spectraTableRHCERR[epochNr-1] /= calCoeffRHC;
    }
    std::vector < std::vector < double > > IV = recreate_from_rlhc(spectraTableLHC[epochNr-1], spectraTableRHC[epochNr-1]);
    spectraTableI[epochNr - 1] = IV[0];
    spectraTableV[epochNr - 1] = IV[1];
    spectraTableIERR[epochNr-1] = (spectraTableRHCERR[epochNr-1] + spectraTableLHCERR[epochNr-1]) / 2.0;
    spectraTableVERR[epochNr-1] = (spectraTableRHCERR[epochNr-1] + spectraTableLHCERR[epochNr-1]) / 2.0;
}

void spectral_container::calibrateAll(bool direction)
{
    // prosta pętla po wszystkich epokach
    for(unsigned long int i = 0; i < spectraTableI.size(); i++)
    {
        calibrateEpoch(i + 1, direction);
    }
}


//
std::vector < std::vector < double > > spectral_container::loadCaltab(string CaltabFileName)
{
    // deklarujemy zwracane wektory
    std::vector < double > Coefs;
    std::vector < double > MJDs;
    std::vector < std::vector < double > > returnedVector;
    std::ifstream tab;
    tab.open(CaltabFileName.c_str());
    if (!tab.good())
        return returnedVector;

    double tmpepoch, tmpcoeff;
    std::string bufor;
    char check_if_hash;
    while(tab.good())
    {
        tab.get(check_if_hash);
        if (check_if_hash == '#')
            getline(tab, bufor);
        else
        {
            tab.seekg(-1, std::ios::cur);
            tab >> tmpepoch >> tmpcoeff;
            MJDs.push_back(tmpepoch + 50000.0);
            Coefs.push_back(tmpcoeff);
        }
    }
    returnedVector.push_back(MJDs);
    returnedVector.push_back(Coefs);
    return returnedVector;
}

void spectral_container::loadLHCCaltab(string CaltabFileName)
{
    std::vector < std::vector < double > > tmp = loadCaltab(CaltabFileName);
    this->caltabLHCMjd = tmp[0];
    this->caltabLHC = tmp[1];
}
void spectral_container::loadRHCCaltab(string CaltabFileName)
{
    std::vector < std::vector < double > > tmp = loadCaltab(CaltabFileName);
    this->caltabRHCMjd = tmp[0];
    this->caltabRHC = tmp[1];
}

double spectral_container::findCalCoeff(std::vector<double> caltabEpochs, std::vector<double> caltabCoeffs, double MJD)
{
    // skrajne przypadki
    if (MJD <= caltabEpochs[0] ) // MJD mniejsze, niż początek tablicy
        return caltabCoeffs[0];
    else if (MJD >= caltabEpochs[caltabEpochs.size()-1]) // MJD większe, niż koniec tablicy
        return caltabCoeffs[caltabCoeffs.size()-1];

    // pętla po caltabie, szukamy epoki
    for (unsigned long int i = 0; i < caltabEpochs.size(); i++)
        if (int(caltabEpochs[i]) == int(MJD))
            return caltabCoeffs[i];

    // jeśli jej nie znajdziemy, musimy zabawić się w interpolację
    std::vector < std::vector < double > > epochs_coefs_for_1intrpl = findBeforeAndAfterEpochs(caltabEpochs, caltabCoeffs, MJD);
    double before_epoch = epochs_coefs_for_1intrpl[0][0];
    double after_epoch = epochs_coefs_for_1intrpl[0][1];
    double before_coeff = epochs_coefs_for_1intrpl[1][0];
    double after_coeff = epochs_coefs_for_1intrpl[1][1];
    return interpolateCAL(before_epoch, before_coeff, after_epoch, after_coeff, MJD);
}

std::vector < std::vector < double > > spectral_container::findBeforeAndAfterEpochs(std::vector<double> caltabEpochs, std::vector<double> caltabCoeffs, double MJD)
{
    // numery epok
    unsigned long int index_before = 0;
    unsigned long int index_after = 0;

    for(unsigned long int i = 0; i < caltabEpochs.size(); i++)
    {
        if ( i != 0 && MJD < caltabEpochs[i])
        {
            index_before = i - 1;
            index_after = i;
            break;
        }
    }
    std::vector < double > coefs(2), mjds(2);
    std::vector < std::vector < double > > returnedCont;
    mjds[0] = caltabEpochs[index_before];
    mjds[1] = caltabEpochs[index_after];
    coefs[0] = caltabCoeffs[index_before];
    coefs[1] = caltabCoeffs[index_after];
    returnedCont.push_back(mjds);
    returnedCont.push_back(coefs);
    return returnedCont;
}

double spectral_container::interpolateCAL(double beginEpoch, double beginCoeff, double endEpoch, double endCoeff, double MJD)
{
    double slope = (endCoeff - beginCoeff) / (endEpoch - beginEpoch);
    double daysPassed = MJD - beginCoeff;
    return beginCoeff + (slope * daysPassed);
}
