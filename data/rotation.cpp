#include "spectral_container.h"
/*
Ten plik źródłowy przechowuje kod z metodami do rotacji widm
*/

// rotuje wskazane części widma
void spectral_container::rotate(int epoch, int nChans, bool direction, bool Irot, bool Vrot, bool LHCrot, bool RHCrot)
{
    // ustalamy kierunek
    if (!direction)
        nChans = ( (int) spectraTableI[epoch-1].size() ) - nChans;

    // rotujemy
    if(Irot)
        rotate1Pol(spectraTableI, epoch, nChans);
    if(Vrot)
        rotate1Pol(spectraTableV, epoch, nChans);
    if(LHCrot)
        rotate1Pol(spectraTableLHC, epoch, nChans);
    if(RHCrot)
        rotate1Pol(spectraTableRHC, epoch, nChans);

    addToListOfModified(epoch);
}

void spectral_container::rotate1Pol(std::vector<std::vector<double> > &poltab, int epoch, int nChans)
{
    unsigned long int noOfChannels = poltab[epoch-1].size();
    std::vector < double > tmptab(noOfChannels);

    for (unsigned long int i = 0; i < noOfChannels; i++)
    {
        if(nChans + i < noOfChannels)
            tmptab[i] = poltab[epoch-1][i + nChans];
        else
            tmptab[i] = poltab[epoch-1][(i+nChans) - noOfChannels];
    }
    poltab[epoch-1] = tmptab;
}

void spectral_container::addToListOfModified(int epoch)
{
    if(!checkIfOnTheList(epoch, listOfModified))
        listOfModified.push_back(epoch);
}

bool spectral_container::checkIfOnTheList(int epoch, std::vector<int> &list)
{
    for (unsigned long int i = 0; i < list.size(); i++)
    {
        if(epoch == list[i])
            return true;
    }
    return false;
}

void spectral_container::recalculateIfromPols(bool modified)
{
    if (modified == true)
    {
        for(unsigned long int i = 0; i < listOfModified.size(); i++)
        {
            int epoch = listOfModified[i];
            std::vector < std::vector < double > > tmpIV;
            tmpIV = recreate_from_rlhc(spectraTableLHC[epoch-1], spectraTableRHC[epoch-1]);
            spectraTableI[epoch-1] = tmpIV[0];
            spectraTableV[epoch-1] = tmpIV[1];
        }
    }
    else
    {
        for(unsigned long int i = 0; i < spectraTableI.size(); i++)
        {
            int epoch = i+1;
            std::vector < std::vector < double > > tmpIV;
            tmpIV = recreate_from_rlhc(spectraTableLHC[epoch-1], spectraTableRHC[epoch-1]);
            spectraTableI[epoch-1] = tmpIV[0];
            spectraTableV[epoch-1] = tmpIV[1];
        }
    }

    for(int i = 0; i < listOfModified.size(); i++)
    {
        std::cout << i << "  " << listOfModified[i] << " | ";
    }
    std::cout << std::endl;
}
