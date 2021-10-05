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

    // - metody -
    // metoda inicjująca
    spectral_container();
    // zapełnia kontenery, w argumencie jest lista plików, wielokrotnie wzywa loadSingleSpectrumFromFile()
    // domyślnie, ta metoda będzie wywoływana gdy wywoła się program z listą w argumencie
    void loadDataFromList(std::string listWithFilenames);
    // to samo, tylko w argumencie przyjmuję listę plików QT
    // domyślnie, ta metoda będzie wywoływana gdy wybierze się pliki za pomocną graficznego wybieraka
    void loadDataFromList(QStringList qtListaPlikow);



private:
    void loadSingleSpectrumFromFile(std::string spectrumFileName);     // wielokrotnie wzywana metoda, w argumencie ma absolutną ścieżkę do pojedynczego pliku
    void loadSingleSpectrum(std::ifstream & file);    // metoda wczytywania pliku AVR
    void loadSingleSpectrum(CCfits::FITS & file);    // metoda wczytywania pliku FITS
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
};

#endif // SPECTRAL_CONTAINER_H
