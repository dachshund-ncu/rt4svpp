#ifndef SPECTRAL_CONTAINER_H
#define SPECTRAL_CONTAINER_H

/*
Autor: Michał Durjasz
Data pierwszego utworzenia: 31.09.2021
Plik nagłówkowy klasy, króra opisuje strukturę danych
Struktura ta to kontener z obserwacjami widmowymi
Z uwagi na lepszy czas dostępu będą one zapisywane w kontenerze 2D std::vector
Prawidłowe odwołanie do danej epoki to:
widmo_nr_3 = spectraTable[2]
kabnał_nr_1024_w_widmie_nr_3 = spectraTable[2][1023]
 */

// -- biblioteki --
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <QtWidgets>
#include <CCfits/CCfits>

// -- definicja klasy --
class spectral_container
{

// -- publiczne metody i atrybuty --
public:
    // - kontenery z danymi -
    // widma (2-D)
    std::vector < std::vector < double > > spectraTableI; // 2d kontener z widmami (polaryzacja I)
    std::vector < std::vector < double > > spectraTableV; // 2d kontener z widmami (polaryzacja V)
    std::vector < std::vector < double > > spectraTableLHC; // 2d kontener z widmami (polaryzacja LHC)
    std::vector < std::vector < double > > spectraTableRHC; // 2d kontener z widmami (polaryzacja RHC)
    // niepewności RMS (1-D)
    std::vector < double > spectraTableIERR; // 1d kontener z widmami (polaryzacja I)
    std::vector < double > spectraTableVERR; // 1d kontener z widmami (polaryzacja V)
    std::vector < double > spectraTableLHCERR; // 1d kontener z widmami (polaryzacja LHC)
    std::vector < double > spectraTableRHCERR; // 1d kontener z widmami (polaryzacja RHC)
    // prędkości (dla każdej epoki generowana jest osobna tablica)
    std::vector < std::vector < double > > velocityTable; // 2d kontener z prędkościami radialnymi
    std::vector < std::vector < double > > channelTable; // 2d kontener z kanałami
    // - pozostałe kontenery z danymi -
    // czas
    std::vector < double >  mjdTable; // 1D kontener z epokami (mjd)
    std::vector < double >  jdTable; // 1D kontener z epokami (jd)
    std::vector < double >  decyrTable; // 1D kontener z epokami (decimal year)
    std::vector < std::vector < double > > datetimeTable; // 2d kontener z datą (yr, month, day, hr, min, sec)
    // tsys
    std::vector < double >  tsysTable; // 1D kontener z TSYS
    // pozycja
    std::vector < double >  azTable; // 1D kontener z azymutami
    std::vector < double >  elTable; // 1D kontener z elewacjami
    std::vector < double >  zTable; // 1D kontener z odległościami zenitalnymi
    // częstotliwości, prędkości centralne
    std::vector < double > restFreqsTable; // 1D kontener z częstotliwościami spoczynkowymi [MHz]
    std::vector < double > bandWidthTable; // 1D kontener z szerokościami wstęgi [MHz]
    std::vector < double > vlsrTable; // 1D kontener z prędkościami centralnymi [Km/s]
    std::vector < std::string > isotimeTable; // 1D kontener z czasem w formacie ISO
    // czy plik to fits czy AVR
    std::vector < std::string > fileTypeTab; // 1D kontener z nazwą typu pliku (FITS lub AVR)
    // nazwy plików
    std::vector < std::string > fileNamesTab; // nazwy plików [ścieżki absolutne]
    // lista epok zmodyfikowanych
    std::vector < int > listOfModified;
    // pojedyncze stałe
    std::string nameOfSource; // nazwa źródła
    std::string saveDirectory; // nazwa katalogu, w którym będą zapistwane pliki
    bool loadedData = false;

    // - metody -
    // metoda inicjująca
    spectral_container();
    // zapełnia kontenery, w argumencie jest lista plików, wielokrotnie wzywa loadSingleSpectrumFromFile()
    // domyślnie, ta metoda będzie wywoływana gdy wywoła się program z listą w argumencie
    void loadDataFromList(std::string listWithFilenames);
    // to samo, tylko w argumencie przyjmuję listę plików QT
    // domyślnie, ta metoda będzie wywoływana gdy wybierze się pliki za pomocną graficznego wybieraka
    void loadDataFromList(QStringList qtListaPlikow);
    // -- liczy całkę z wszystkich polaryzacji i zapisuje do pliku --
    void integrate4Pols(int min_channel, int max_channel, bool isotimeInclude);
    // pomocnicze metody publiczne
    std::vector < double > integratePol(int min_channel, int max_channel, std::vector < std::vector < double > > & veltab, std::vector < std::vector < double > > &poltab );
    std::vector < double > integratePolErr(std::vector < std::vector < double > > & veltab, std::vector < double > & errtab );
    std::string getIntegrationFileName(int min_channel, int max_channel);
    // -- średnia po prędkości --
    void averageOverVelocity4Pols(int min_channel, int max_channel, bool isotimeInclude);
    std::string getAverOverVelFileName(int min_channel, int max_channel);
    // -- średnia po czasie --
    void averOverTime4Pols(int begin_epoch, int end_epoch);
    std::string getAverOverTimeFileName(int begin_epoch, int end_epoch);
    // -- export widma dynamicznego --
    void saveDynamicSpectrumToFile(int min_epoch, int max_epoch, int min_channel, int max_channel, bool isotimeInclude);
    std::string getDynSpecFileName(int min_epoch, int max_epoch);
    // -- spectral index --
    void spectralIndex4Pol(int begin_epoch, int end_epoch, double relativeError = 0.0);
    std::string getVIFileName(int begin_epoch, int end_epoch);
    std::string getFIFileName(int begin_epoch, int end_epoch);
    std::string getChi2RedFileName(int begin_epoch, int end_epoch);
    // -- rotacja widm --
    void rotate(int epoch, int nChans=1, bool direction = true, bool Irot=true, bool Vrot=true, bool LHCrot=true, bool RHCrot=true);
    void recalculateIfromPols(bool modified = true);

private:
    void loadSingleSpectrumFromFile(std::string spectrumFileName);     // wielokrotnie wzywana metoda, w argumencie ma absolutną ścieżkę do pojedynczego pliku
    void loadSingleSpectrum(std::ifstream & file, int index_of_file);    // metoda wczytywania pliku AVR
    void loadSingleSpectrum(CCfits::FITS & file, int index_of_file);    // metoda wczytywania pliku FITS
    void bubbleSortEpochs();    // sortowanie bąbelkowe epokami
    void clearAllTables(); // czyści wszystkie kontenery (ale nie zwalnia pamięci)
    bool isPies(std::string fileName);    // sprawdza czy fits czy avr
    double JD (double year, double month, double day); // liczy JD
    double decimalyear(double year, double month, double day); // liczy zmiennoprzecinkowy rok
    double calculate_RMS(std::vector < double > polarization, std::vector < unsigned long int > limits);     // liczy RMS
    std::vector < double > makeTimeFromIsotime(std::string isotime); // liczy czas (jd, mjd, decyr) z isotime
    std::vector < double > extractDoublesFromIsotime(std::string isotime); // extrah*je double (yr, month, day, hr,min,day) z isotime
    std::vector < std::vector < double > > recreate_from_rlhc(std::vector < double > lhc, std::vector < double > rhc);     // przelicza LHC i RHC na I oraz V
    std::vector < double > loadPOLfromAVR(std::vector < std::string > linesInFile, int line_begin); // wczytuje I z pliku AVR, podanego w argumencie jako kontener stringów
    std::vector < std::vector < double > > doppler_track (double vlsr, double restfreq, double freq_rang, double nchans);
    std::string construct_isotime(double year, double month, double day, double hour, double min, double sec);
    void print_loaded_comm(int obsnum, std::string isotime, double obs_error);
    // -- całkowanie widma --
    double integrateSingleEpoch(int min_channel, int max_channel, std::vector < double > veltab, std::vector < double > poltab);
    double integrateSingleEpochErr(std::vector < double > veltab, double epochRms);
    void saveIntegrationToFile(int min_channel, int max_channel, std::vector < std::vector < double > > & integrationResults, std::vector < std::vector < double > > & integrationErrors, bool isotimeInclude);
    // ----------------------
    // -- aver over velocity --
    std::vector < double > averagePolOverVelocity(int min_channel, int max_channel, std::vector < std::vector < double > > & fluxtab);
    double averageEpochOverVelocity(int min_channel, int max_channel, std::vector < double > fluxtab);
    void saveAveragingToFile(int min_channel, int max_channel, std::vector < std::vector < double > > & averagingResults, std::vector < std::vector < double > > & errors, bool isotimeInclude);
    double getCentralVelocityOfAveraging(int min_channel, int max_channel);
    // ----------------------
    // -- aver over time --
    std::vector < double > averOverTime1Pol(int begin_epoch, int end_epoch, std::vector < std::vector < double > > & fluxes);
    double averagedOverChannel(int channelNumber, int begin_epoch, int end_epoch, std::vector < std::vector < double > > & fluxes);
    double averOverTime1PolErr(int begin_epoch, int end_epoch, std::vector < double > & errors);
    void saveAverOverTime(int begin_epoch, int end_epoch, std::vector < std::vector < double > > & results, std::vector < double > & errors);
    // ----------------------
    // -- spectral index --
    // vi
    std::vector < double > viSpectralIndex1Pol(int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError);
    double viSpectralIndex1channel(int channel, int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError);
    void saveVItoFile(int begin_epoch, int end_epoch, double relativeError, std::vector < std::vector < double > > &VIContainer);
    std::vector < double > calculateMinAndMax(int channel, int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError);
    // fi
    std::vector < double > fiSpectralIndex1Pol(int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError);
    double fiSpectralIndex1channel(int channel, int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError);
    void saveFItoFile(int begin_epoch, int end_epoch, double relativeError, std::vector < std::vector < double > > &FIContainer);
    // chi2
    std::vector < double > chi2SpectralIndex1Pol(int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError);
    double chi2redFromSingleChannel (int channel, int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab, std::vector < double > & errors, double relativeError);
    void saveChi2RedToFile(int begin_epoch, int end_epoch, double relativeError, std::vector < std::vector < double > > &Chi2RedContainer);
    // mean
    double meanOfChannel(int channel, int begin_epoch, int end_epoch, std::vector < std::vector < double > > & poltab);
    // ----------------------
    // -- rotate --
    void rotate1Pol(std::vector < std::vector  < double > > & poltab, int epoch, int nChans);
    void addToListOfModified(int epoch);
    bool checkIfOnTheList(int epoch, std::vector < int > & list);


};

#endif // SPECTRAL_CONTAINER_H
