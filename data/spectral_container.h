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


// -- definicja klasy --
class spectral_container
{

// -- publiczne metody i atrybuty --
public:
    // - kontenery z danymi 2D-
    // widma
    std::vector < std::vector < double > > spectraTableI; // 2d kontener z widmami (polaryzacja I)
    std::vector < std::vector < double > > spectraTableV; // 2d kontener z widmami (polaryzacja V)
    std::vector < std::vector < double > > spectraTableLHC; // 2d kontener z widmami (polaryzacja LHC)
    std::vector < std::vector < double > > spectraTableRHC; // 2d kontener z widmami (polaryzacja RHC)
    // niepewności
    std::vector < std::vector < double > > spectraTableIERR; // 2d kontener z widmami (polaryzacja I)
    std::vector < std::vector < double > > spectraTableVERR; // 2d kontener z widmami (polaryzacja V)
    std::vector < std::vector < double > > spectraTableLHCERR; // 2d kontener z widmami (polaryzacja LHC)
    std::vector < std::vector < double > > spectraTableRHCERR; // 2d kontener z widmami (polaryzacja RHC)
    // prędkości
    std::vector < std::vector < double > > velocityTable; // 2d kontener z prędkościami radialnymi
    // rok, miesiąc, dzień, godzina, minuta, sekunda:
    std::vector < std::vector < double > > datetimeTable; // 2d kontener z dniem, etc.
    // - kontenery z danymi 1D -
    // czas
    std::vector < double >  mjdTable; // 1D kontener z epokami (mjd)
    std::vector < double >  jdTable; // 1D kontener z epokami (jd)
    std::vector < double >  decyrTable; // 1D kontener z epokami (decimal year)
    // tsys
    std::vector < double >  tsysTable; // 1D kontener z TSYS
    // pozycja
    std::vector < double >  azTable; // 1D kontener z azymutami
    std::vector < double >  elTable; // 1D kontener z elewacjami
    std::vector < double >  zTable; // 1D kontener z odległościami zenitalnymi
    // częstotliwości, prędkości centralne
    std::vector < double > restFreqsTable; // 1D kontener z częstotliwościami spoczynkowymi [MHz]
    std::vector < double > baseBandWidthTable; // 1D kontener z szerokościami wstęgi [MHz]
    std::vector < double > vlsrTable; // 1D kontener z prędkościami centralnymi [Km/s]

    // - metody -
    // metoda inicjująca
    spectral_container();
    // zapełnia kontenery, w argumencie jest lista plików, wielokrotnie wzywa loadSingleSpectrumFromFile()
    void loadDataFromList(std::string listWithFilenames);


private:
    // wielokrotnie wzywana metoda, w argumencie ma absolutną ścieżkę do pojedynczego pliku
    void loadSingleSpectrumFromFile(std::string spectrumFileName);
    // sortowanie bąbelkowe epokami
    void bubbleSortEpochs();
    // czyści wszystkie kontenery (ale nie zwalnia pamięci)
    void clearAllTables();
    // czyści wszystkie kontenery (i zwalnia pamięć)
    void clearAllMemory();
};

#endif // SPECTRAL_CONTAINER_H
