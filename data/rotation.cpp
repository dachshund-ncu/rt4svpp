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

    madeRotation = true;
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
    madeRotation = true;
}

void spectral_container::saveModifiedEpochs()
{
    // prosta pętla po zmodyfikowanych epokach
    for(unsigned long int i = 0; i < listOfModified.size(); i++)
    {
        int epoch = listOfModified[i];


        if(!fileTypesTab[epoch-1])
        {
            makeBackupOfFile(epoch - 1, false);
            saveActualTablesToAVR(epoch - 1);
        }
        else
        {
            makeBackupOfFile(epoch - 1, true);
            saveActualTablesToFits(epoch - 1);
        }

    }

    // clearujemy tablicę z modyfikowanymi
    listOfModified.clear();
    // setujemy boola na false
    madeRotation = false;
}

void spectral_container::makeBackupOfFile(int epoch, bool fits=true)
{
    // nazwy plików
    std::string oldFilename = fileNamesTab[epoch];
    std::string newFilename = oldFilename;
    if (!fits)
    {
        newFilename.erase(newFilename.end()-7, newFilename.end());
        newFilename = newFilename + "noedt.DAT";
    }
    else
    {
        newFilename.erase(newFilename.end()-8, newFilename.end());
        newFilename = newFilename + "noedt.fits";
    }

    // obiekty plików
    std::ofstream backupDestination;
    std::ifstream fileToBackup;

    // zapisujemy
    backupDestination.open(newFilename.c_str(), std::ios::binary);
    fileToBackup.open(oldFilename.c_str(), std::ios::binary);
    // kopjujemy
    backupDestination << fileToBackup.rdbuf();
    // zamykamy pliki
    backupDestination.close();
    fileToBackup.close();
}

void spectral_container::saveActualTablesToAVR(int epoch)
{
    // zestaw tymczasowych zmiennych
    string filename = fileNamesTab[epoch];
    string header = AVRHeaders[epoch];
    if (header == "")
    {
        // nic nie robimy, jeśli header jest pustym stringiem
        std::cout << "Header is empty! Is it really AVR file?" << std::endl;
        return;
    }

    // obiekt pliku do zapisywania
    std::ofstream fileToSave;
    fileToSave.open(filename.c_str());

    // deklarujemy tymczasowe tablice z polaryzacjami
    std::vector < double > Is = spectraTableI[epoch];
    std::vector < double > Vs = spectraTableV[epoch];
    std::vector < double > LHCs = spectraTableLHC[epoch];
    std::vector < double > RHCs = spectraTableRHC[epoch];

    // zapisujemy wszystko do pliku
    // header
    fileToSave << header;

    // I
    for (unsigned long int i = 0; i < Is.size(); i++)
    {
        if (i%8 == 0)
        {
            if(i != 0)
                fileToSave << std::endl;

            fileToSave << std::setw(11) << std::setprecision(1) << std::fixed << Is[i]*1000.0;
        }
        else
        {
            fileToSave << std::setw(10) << std::setprecision(1) << std::fixed << Is[i]*1000.0;
        }
    }
    // header
    fileToSave << std::endl << header;
    // V
    for (unsigned long int i = 0; i < Vs.size(); i++)
    {
        if (i%8 == 0)
        {
            if(i != 0)
                fileToSave << std::endl;

            fileToSave << std::setw(11) << std::setprecision(1) << std::fixed << Vs[i]*1000.0;
        }
        else
        {
            fileToSave << std::setw(10) << std::setprecision(1) << std::fixed << Vs[i]*1000.0;
        }
    }
    // header
    fileToSave << std::endl << header;
    // LHC
    for (unsigned long int i = 0; i < LHCs.size(); i++)
    {
        if (i%8 == 0)
        {
            if(i != 0)
                fileToSave << std::endl;

            fileToSave << std::setw(11) << std::setprecision(1) << std::fixed << LHCs[i]*1000.0;
        }
        else
        {
            fileToSave << std::setw(10) << std::setprecision(1) << std::fixed << LHCs[i]*1000.0;
        }
    }
    // header
    fileToSave << std::endl << header;
    // RHC
    for (unsigned long int i = 0; i < RHCs.size(); i++)
    {
        if (i%8 == 0)
        {
            if(i != 0)
                fileToSave << std::endl;

            fileToSave << std::setw(11) << std::setprecision(1) << std::fixed << RHCs[i]*1000.0;
        }
        else
        {
            fileToSave << std::setw(10) << std::setprecision(1) << std::fixed << RHCs[i]*1000.0;
        }
    }
    fileToSave.close();
}

void spectral_container::saveActualTablesToFits(int epoch)
{
    CCfits::FITS::setVerboseMode(false);
    // -- poczatkowe stale --
    std::string filename = fileNamesTab[epoch];
    // zapisujemy tablice odwrotnie
    std::vector < double > lhc ((int) spectraTableLHC[epoch].size());
    std::vector < double > rhc ((int) spectraTableLHC[epoch].size());
    for (unsigned long int ee = 0; ee < lhc.size(); ee++)
    {
        lhc[lhc.size() - 1 - ee] = spectraTableLHC[epoch][ee];
        rhc[lhc.size() - 1 - ee] = spectraTableRHC[epoch][ee];
    }

    // -- otwieramy plik fits --
    CCfits::FITS fitsFile(filename.c_str(), CCfits::Write);
    /*
    // -- otwieramy tymczasowy plik fits --
    CCfits::FITS fitsFileNew("jamnikowyFitsTymczasowy.fits", fitsFile);

    // kopiujemy plik do tego tymczasowego
    fitsFileNew
    */
    fitsFile.extension(1).column("Pol 1").write(lhc,0);
    fitsFile.extension(1).column("Pol 2").write(rhc,0);

    fitsFile.destroy();
}
