#include "spectral_container.h"

// - metoda inicjująca klasę -
spectral_container::spectral_container()
{
    //std::cout << "Utworzono kontener spektralny!" << std::endl;
}


// - metoda czytająca listę plików -
void spectral_container::loadDataFromList(std::string listWithFilenames)
{
    //std::cout << "Ładuję dane z listy plików: " << listWithFilenames << std::endl;

    // plik
    std::ifstream filesList;
    // otwieramy
    filesList.open(listWithFilenames.c_str());
    // bufor
    std::string bufor;
    // pętla
    while (filesList.good())
    {
        std::getline(filesList, bufor);
        loadSingleSpectrumFromFile(bufor);
    }
    filesList.close();

}

// - metoda czytająca pojedynczy plik z listy -
void spectral_container::loadSingleSpectrumFromFile(std::string spectrumFileName)
{
    // failsafe if the line is empty
    if (spectrumFileName == "")
        return;

    //std::cout << "===> opening: " <<  spectrumFileName << std::endl;
}

// - sortowanie bąbelkowe po epokach -
void spectral_container::bubbleSortEpochs()
{

}

// - czyści tablice bez zwalniania pamięci -
void spectral_container::clearAllTables()
{

}

// - czyści tablice ze zwalnianiem pamięci -
void spectral_container::clearAllMemory()
{

}
