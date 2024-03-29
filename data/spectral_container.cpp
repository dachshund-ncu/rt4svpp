#include "spectral_container.h"
//#include <CCfits/CCfits>
// - metoda inicjująca klasę -
spectral_container::spectral_container()
{
    rmsChannelsTab.resize(4);
}


// - metoda czytająca listę plików -
void spectral_container::loadDataFromList(std::string listWithFilenames)
{
    // -- na początek - czyścimy kontenery --
    clearAllTables();

    // -- czytamy plik z listą --
    std::ifstream filesList;
    filesList.open(listWithFilenames.c_str());

    if (!filesList.good())
    {
        return;
    }

    // -- pasek postępu (albo nierządu) --
    QProgressDialog postep;
    postep.setLabelText("Loading files, please wait");
    postep.setMinimum(0);
    postep.setMaximum(lengthOfTheListFile(filesList));
    postep.setVisible(true);
    int licznik = 0;
    // -----------------------------------

    // -- zdobywamy info o ścieżce całkowitej --
    QFileInfo infotmp (QString::fromStdString(listWithFilenames));
    saveDirectory = infotmp.absolutePath().toStdString();
    // -----------------------------------------

    // -- wczytujemy pliki z flagami --
    std::vector < std::string > flaggedFiles = readFlaggedFiles();
    // --------------------------------

    // bufor
    std::string bufor;

    // pętla
    filesList.seekg(0);
    while (filesList.good())
    {
        // czytamy jedną linię z listy plików
        std::getline(filesList, bufor);


        // -- dodatkowe zabezpieczenie --
        if (bufor != "")
        {

            if ( checkIfFlagged(bufor, flaggedFiles) )
            {
                std::cout << "----> File: " << getFileNameFromFullPath(bufor) << " is flagged and I will not read it." << std::endl;
            }
            else
            {
                loadSingleSpectrumFromFile(saveDirectory + "/" + bufor); // ładujemy plik z listy, w argumencie podajemy ABSOLUTNĄ ścieżkę
            }
        }
        // do paska nierządu
        licznik += 1;
        postep.setValue(licznik);
        QCoreApplication::processEvents();
    }
    filesList.close();

    // ustawiamy flagę loaded
    loadedData = true;

    // -- bubblesorting --
    bubbleSortEpochs();
    // -- filling normalization coeffs --
    fillNormalizationCoeffsWith1();
}

// - metoda czytająca listę plików -
void spectral_container::loadDataFromList(QStringList qtListaPlikow)
{
    // -- na początek - czyścimy kontenery --
    clearAllTables();

    // -- pasek postępu (albo nierządu) --
    QProgressDialog postep;
    postep.setLabelText("Loading files, please wait");
    postep.setMinimum(0);
    postep.setMaximum(qtListaPlikow.size());
    postep.setVisible(true);
    // -----------------------------------

    // --------------------------------
    // w liście zawsze będą absolutne ścieżki do plików
    // dlatego ekstrahujemy z jej pierwszego elementu
    QFileInfo info(qtListaPlikow[0]);
    saveDirectory = info.absolutePath().toStdString();
    // --------------------------------

    // -- wczytujemy pliki z flagami --
    std::vector < std::string > flaggedFiles = readFlaggedFiles();
    // --------------------------------

    // -- komunikat w terminalu --
    std::cout << "---> Loading files from QT list:" << std::endl;
    // -- i czytamy pliki zgodnie z listą --
    for(int i = 0; i < qtListaPlikow.size(); i++)
    {
        if ( checkIfFlagged(qtListaPlikow[i].toStdString(), flaggedFiles) )
            std::cout << "----> File: " << getFileNameFromFullPath( qtListaPlikow[i].toStdString()) << " is flagged and I will not read it." << std::endl;
        else
            loadSingleSpectrumFromFile(qtListaPlikow[i].toStdString());
        postep.setValue(i);
        QCoreApplication::processEvents();
    }
    // ustawiamy flagę loaded
    loadedData = true;

    // -- bubblesortnig --
    bubbleSortEpochs();
    // -- filling normalization coeffs --
    fillNormalizationCoeffsWith1();
}


// - metoda czytająca pojedynczy plik z listy -
void spectral_container::loadSingleSpectrumFromFile(std::string spectrumFileName)
{
    // failsafe na pustą linię
    if (spectrumFileName == "")
        return;

    // tutaj rozpoczyna się czytanie pojedynczego pliku
    // pies to plik AVR, brak psa - FITS
    int index = fileNamesTab.size() + 1;
    if (isPies(spectrumFileName))
    {
        std::ifstream pies;
        pies.open(spectrumFileName.c_str());
        loadSingleSpectrum(pies, index);
        pies.close();
    }
    else
    {
        CCfits::FITS niePies(spectrumFileName, CCfits::Read);
        loadSingleSpectrum(niePies, index);
    }

    // dodatkowo dodajemy do listy plików nazwę
    fileNamesTab.push_back(spectrumFileName);

}

void spectral_container::loadSingleSpectrum(std::ifstream &file, int index_of_file)
{
    // tworzymy tablicę stringów
    // każdy jej element będzie przechowywał jedną linię w pliku
    std::vector < string > linesInFile;

    // dodatkowo bufor do funkcji getline
    std::string bufor;

    // wczytujemy plik do kontenera
    while(file.good())
    {
        std::getline(file, bufor);
        linesInFile.push_back(bufor);
    }

    // -- elewacja i azymut --
    bufor = linesInFile[3];
    std::vector < double > elaz;
    double bufor_double;
    std::stringstream eeeel(bufor);
    while(eeeel >> bufor_double)
    {
        elaz.push_back(bufor_double);
    }
    double az = elaz[0] + elaz[1] / 60.0;
    double el = elaz[2] + elaz[3] / 60.0;
    double z = 90.0 - el;
    // -----------------------

    // ------ RA i DEC -------
    eeeel.clear();
    eeeel.str(linesInFile[1]);
    std::vector < double > raDec;
    while(eeeel >> bufor_double)
    {
        raDec.push_back(bufor_double);
    }
    std::string raStr = constructRASTR(raDec[0], raDec[1], raDec[2]);
    std::string decStr = constructDECSTR(raDec[3], raDec[4], raDec[5]);
    // -----------------------

    // -- restfreq, vlsr i nazwa źródła --
    bufor = linesInFile[10];
    std::stringstream restf_ss(bufor);
    std::vector < double > dane;
    while(restf_ss >> bufor_double)
    {
        dane.push_back(bufor_double);
    }
    // -- zapisujemy dane --
    double vlsr = dane[3];
    double freq = dane[4];
    double wst  = dane[1];
    double n_chans = dane[0];
    // -- wczytujemy nazwę źródła, pomijając białe znaki --
    std::string srcname = linesInFile[11];
    srcname.erase(remove(srcname.begin(), srcname.end(), ' '), srcname.end());
    // ------------------------------------

    // -- data --
    bufor = linesInFile[4];
    double day, month, year, hour, min, sec;
    day = std::stod(bufor.substr(4,2));
    month = std::stod(bufor.substr(6,2));
    year = std::stod("20" + bufor.substr(8,2));
    std::vector < double > hms;
    bufor = linesInFile[13];
    std::stringstream hms_ss(bufor);
    while(hms_ss >> bufor_double)
    {
        hms.push_back(bufor_double);
    }
    hour = hms[0];
    min = hms[1];
    sec = hms[2];
    // dodatkowo
    double hour2;
    double day2;
    hour2 = hour + min / 60.0 + sec / 3600.0;
    day2 = day + hour2 / 24.0;
    double jd = JD(year, month, day2);
    double mjd = jd - 2400000.5;
    double decyr = decimalyear(year, month, day2);
    std::vector < double > datetime_tmp(6);
    datetime_tmp[0] = year;
    datetime_tmp[1] = month;
    datetime_tmp[2] = day;
    datetime_tmp[3] = hour;
    datetime_tmp[4] = min;
    datetime_tmp[5] = sec;
    // ----------

    // -- tsys --
    bufor = linesInFile[6];
    double tsystmp;
    std::stringstream tsys_ss(bufor);
    tsys_ss >> tsystmp;
    // ----------

    // -- header --
    std::string headertmp = "";
    for (unsigned long int i = 0; i < 14; i++)
    {
        headertmp = headertmp + linesInFile[i] + "\n";
    }
    // ------------

    // ---- CZYTANIE DANYCH ----
    std::vector < double > I, V, LHC, RHC;
    I = loadPOLfromAVR(linesInFile, 17);
    V = loadPOLfromAVR(linesInFile, 287);
    LHC = loadPOLfromAVR(linesInFile, 557);
    RHC = loadPOLfromAVR(linesInFile, 827);
    // -------------------------

    // ---- DOPPLER TRACKING ---
    std::vector < std::vector < double > > freqsAndVels;
    freqsAndVels = doppler_track(vlsr, freq, wst, 2048.0);
    std::vector < double > chans = freqsAndVels[2];
    std::vector < double > vels = freqsAndVels[1];
    std::vector < double > freqs = freqsAndVels[0];
    // -------------------------

    // ---- RMS ----
    if(!rmsSet)
    {
        rmsChannelsTab[0] = 100;
        rmsChannelsTab[1] = 400;
        rmsChannelsTab[2] = (unsigned long int) 2048 - 400;
        rmsChannelsTab[3] = (unsigned long int) 2048 - 100;
        rmsSet = true;
    }
    double rmsI = calculate_RMS(I, rmsChannelsTab);
    double rmsV = calculate_RMS(V, rmsChannelsTab);
    double rmsLHC = calculate_RMS(LHC, rmsChannelsTab);
    double rmsRHC = calculate_RMS(RHC, rmsChannelsTab);
    // -------------

    // ---- isotime ----
    std::string isotime = construct_isotime(year, month, day, hour, min, sec);
    // -----------------

    // ---- dodajemy do kontnerów ----
    // 2-D
    spectraTableI.push_back(I);
    spectraTableV.push_back(V);
    spectraTableLHC.push_back(LHC);
    spectraTableRHC.push_back(RHC);
    velocityTable.push_back(vels);
    channelTable.push_back(chans);
    // 1-D
    spectraTableIERR.push_back(rmsI);
    spectraTableVERR.push_back(rmsV);
    spectraTableLHCERR.push_back(rmsLHC);
    spectraTableRHCERR.push_back(rmsRHC);
    mjdTable.push_back(mjd);
    jdTable.push_back(jd);
    decyrTable.push_back(decyr);
    datetimeTable.push_back(datetime_tmp);
    azTable.push_back(az);
    elTable.push_back(el);
    zTable.push_back(z);
    restFreqsTable.push_back(freq);
    bandWidthTable.push_back(wst);
    vlsrTable.push_back(vlsr);
    isotimeTable.push_back(isotime);
    tsysTable.push_back(tsystmp);
    fileTypesTab.push_back(false);
    AVRHeaders.push_back(getHeaderFromAVRFile(linesInFile));
    obsProtperties.push_back(getAllHeaderInformation(vlsr, freq - wst / 2.0, freq + wst / 2.0, wst, 2000, n_chans, freq, az, z, tsystmp, 0.0, 0.0, 0.0, srcname, isotime, raStr, decStr, "--------"));
    // srcname
    nameOfSource = srcname;

    // --- komunikat że loaded ---
    print_loaded_comm(index_of_file, isotime, rmsI);

}

void spectral_container::loadSingleSpectrum(CCfits::FITS & file, int index_of_file)
{
    // deklarujemy tymczasowe zmienne w stacku
    // zostaną zniszczone po wykonaniu funkcji, więc nie musimy się o nie martwić
    double vlsr, freq_beg, freq_mid, freq_end, freq_rang, equinox, nchans, restfreq, el, az, z, tsys1, tsys2, dopp_vsu, dopp_vob, dopp_vto;
    //double year, month, day, hour, min,sec;
    std::string zstr, tsysstr, vlsr_str, freq_beg_str, freq_mid_str, freq_end_str, freq_rang_str, equinox_str, nchans_str, restfreq_str, el_str, az_str, z_str, tsys1_str, tsys2_str, dopp_vsu_str, dopp_vob_str, dopp_vto_str;
    std::string sourcename, isotime, ra, dec, molecule;

    // Czytamy plik fits
    CCfits::ExtHDU & table = file.extension(1);

    // i z niego
    try
    {
        table.readKey("VSYS", vlsr);
    }
    catch(...)
    {
        table.readKey("VSYS", vlsr_str);
        vlsr = stod(vlsr_str);
    }

    // FRQ_BEG
    try
    {
        table.readKey("FRQ_BEG", freq_beg);
    }
    catch(...)
    {
        table.readKey("FRQ_BEG", freq_beg_str);
        freq_beg = stod(freq_beg_str);
    }

    // FRQ_END
    try
    {
        table.readKey("FRQ_END", freq_end);
    }
    catch(...)
    {
        table.readKey("FRQ_END", freq_end_str);
        freq_end = stod(freq_end_str);
    }

    // FRQ_RANG
    try
    {
        table.readKey("FRQ_RANG", freq_rang);
    }
    catch(...)
    {
        table.readKey("FRQ_RANG", freq_rang_str);
        freq_rang = stod(freq_rang_str);
    }

    // EQUINOX
    try
    {
        table.readKey("EQUINOX", equinox);
    }
    catch(...)
    {
        table.readKey("EQUINOX", equinox_str);
        equinox = stod(equinox_str);
    }

    // NAXIS2
    try
    {
        table.readKey("NAXIS2", nchans);
    }
    catch(...)
    {
        table.readKey("NAXIS2", nchans_str);
        nchans = stod(nchans_str);
    }

    // FREQ
    try
    {
        table.readKey("FREQ", restfreq);
    }
    catch(...)
    {
        table.readKey("FREQ", restfreq_str);
        restfreq = stod(restfreq_str);
    }

    // AZ
    try
    {
        table.readKey("AZ", az);
    }
    catch(...)
    {
        try
        {
            table.readKey("AZ", az_str);
            az = stod(az_str);
        }
        catch(...)
        {
            az = 0.0;
        }
    }

    // Z
    try
    {
        table.readKey("Z", z);
    }
    catch(...)
    {
        try
        {
            table.readKey("Z", zstr);
            z = stod(zstr);
        }
        catch(...)
        {
            z = 0.0;
        }
    }


    // TSYS1 TSYS2
    try
    {
        table.readKey("TSYS1", tsys1);
        table.readKey("TSYS2", tsys2);
    }
    catch(...)
    {
        try
        {
            table.readKey("TSYS", tsys1);
            table.readKey("TSYS", tsys2);
        }
        catch(...)
        {
            tsys1 = 0.0;
            tsys2 = 0.0;
        }

    }

    // -- czytamy rzeczy, specyficzne dla RS --
    // -- dla autokorelatora wartości z tych pól będą równe 0 --
    try
    {
        table.readKey("DOPP_VSU", dopp_vsu);
    }
    catch(...)
    {
        table.readKey("DOPP_VSU", dopp_vsu_str);
        dopp_vsu = stod(dopp_vsu_str);
    }

    try
    {
        table.readKey("DOPP_VOB", dopp_vob);
    }
    catch(...)
    {
        table.readKey("DOPP_VOB", dopp_vob_str);
        dopp_vob = stod(dopp_vob_str);
    }

    try
    {
        table.readKey("DOPP_VTO", dopp_vto);
    }
    catch(...)
    {
        table.readKey("DOPP_VTO", dopp_vto_str);
        dopp_vto = stod(dopp_vto_str);
    }

    // stringi
    table.readKey("OBJECT", sourcename);
    table.readKey("DATE-OBS", isotime);
    table.readKey("SRC_RA", ra);
    table.readKey("SRC_DEC", dec);
    table.readKey("MOLECULE", molecule);

    // -- obliczamy kilka rzeczy --
    // elewacja
    el = 90.0 - z;

    // zamieniamy restfreq na MHZ
    restfreq = restfreq / 1000000.0;

    // daty
    std::vector < double > timeVector = makeTimeFromIsotime(isotime);
    double jd = timeVector[0];
    double mjd = timeVector[1];
    double decyr = timeVector[2];
    std::vector < double > time_temporal = extractDoublesFromIsotime(isotime);

    // -- czytamy dane --
    std::vector < double > lhc((int) nchans), rhc ((int) nchans);
    table.column("Pol 1").read(lhc, 0, nchans);
    table.column("Pol 2").read(rhc, 0, nchans);

    // -- obcinamy krawędzie wstęgi --
    for(int i = 0; i < 24; i++)
    {
        // - na początku wstęgi -
        lhc[i] = 0.0;
        rhc[i] = 0.0;

        // - i na końcu -
        lhc[(int) nchans - 1 - i] = 0.0;
        rhc[(int) nchans - 1 - i] = 0.0;
    }

    double overall_velocity = vlsr + dopp_vto;
    std::vector < std::vector < double > > freqsAndVels;
    freqsAndVels = doppler_track(overall_velocity, restfreq, freq_rang, nchans);
    std::vector < double > vels = freqsAndVels[1];
    std::vector < double > freqs = freqsAndVels[0];
    std::vector < double > chans = freqsAndVels[2];

    // -- odwracamy tablice, by VEL było od najmniejszej --
    std::vector < double > lhc_rev((int) nchans), rhc_rev((int) nchans);
    for (int i = 0; i < nchans; i++)
    {
        lhc_rev[i] = lhc[lhc.size() - 1 - i];
        rhc_rev[i] = rhc[rhc.size() - 1 - i];
    }
    // zapisujemy do oryginalnych
    lhc = lhc_rev;
    rhc = rhc_rev;

    // -- tworzymy tablice I oraz V --
    // na podstawie wczytanych LHC i RHC
    std::vector < std::vector < double > > IV(2);
    std::vector < double > i_tmp_lst((int) nchans), v_tmp_lst((int) nchans);
    IV = recreate_from_rlhc(lhc, rhc);
    i_tmp_lst = IV[0];
    v_tmp_lst = IV[1];

    // -- generujemy tablice z kanałami --
    std::vector < int > nanamichan((int) nchans);
    for(int i = 0; i < nchans; i++)
    {
        nanamichan[i] = i+1;
    }

    // -- liczymy RMS --
    if(!rmsSet)
    {
        rmsChannelsTab[0] = 100;
        rmsChannelsTab[1] = 400;
        rmsChannelsTab[2] = (unsigned long int) 2048 - 400;
        rmsChannelsTab[3] = (unsigned long int) 2048 - 100;
        rmsSet = true;
    }
    double rmsI = calculate_RMS(i_tmp_lst, rmsChannelsTab);
    double rmsV = calculate_RMS(v_tmp_lst, rmsChannelsTab);
    double rmsLHC = calculate_RMS(lhc, rmsChannelsTab);
    double rmsRHC = calculate_RMS(rhc, rmsChannelsTab);
    // formatujemy nazwę źródła
    sourcename.erase(remove(sourcename.begin(), sourcename.end(), ' '), sourcename.end());

    double tsys = (tsys1 + tsys2) / 2.0;

    // zapisujemy do kontenerów, będących atrybutami klasy
    // 2-D
    spectraTableI.push_back(i_tmp_lst);
    spectraTableV.push_back(v_tmp_lst);
    spectraTableLHC.push_back(lhc);
    spectraTableRHC.push_back(rhc);
    velocityTable.push_back(vels);
    channelTable.push_back(chans);
    // 1-D
    spectraTableIERR.push_back(rmsI);
    spectraTableVERR.push_back(rmsV);
    spectraTableLHCERR.push_back(rmsLHC);
    spectraTableRHCERR.push_back(rmsRHC);
    mjdTable.push_back(mjd);
    jdTable.push_back(jd);
    decyrTable.push_back(decyr);
    datetimeTable.push_back(time_temporal);
    azTable.push_back(az);
    elTable.push_back(el);
    zTable.push_back(z);
    restFreqsTable.push_back(restfreq);
    bandWidthTable.push_back(freq_rang);
    vlsrTable.push_back(vlsr);
    isotimeTable.push_back(isotime);
    tsysTable.push_back(tsys);
    fileTypesTab.push_back(true);
    AVRHeaders.push_back("");
    obsProtperties.push_back(getAllHeaderInformation(vlsr, freq_beg, freq_end, freq_rang, equinox, nchans, restfreq, az, z, tsys, dopp_vsu, dopp_vob, dopp_vto, sourcename, isotime, ra, dec, molecule));
    // nazwa źródła
    nameOfSource = sourcename;

    // --- komunikat że loaded ---
    print_loaded_comm(index_of_file, isotime, rmsI);
}

// - sortowanie bąbelkowe po epokach -
void spectral_container::bubbleSortEpochs()
{
    /*
     * This method bubble-sorts epochs, loaded previously
     * it's sad, that this method needs update every time new container is added
     * Maybe next time it will be better
     * -> if loadedData is false, do nothing
     * -> else bubblesort all
     */
    if(!loadedData || spectraTableI.size() < 2)
        return;
    std::cout << "-----------------------" << std::endl;
    std::cout << "----> Bubble-sorting epochs..." << std::endl;
    // -- bubblesort begins --
    for(unsigned long int i = 0; i < spectraTableI.size()-1; i++)
    {
        for(unsigned long int j = i+1; j < spectraTableI.size(); j++)
        {
            if (mjdTable[j] < mjdTable[i])
            {
                // -- 1-D containers --
                // DOUBLE
                swapD(mjdTable, i, j); // <--- CRITICAL: DATE
                swapD(spectraTableIERR, i, j);
                swapD(spectraTableVERR, i, j);
                swapD(spectraTableLHCERR, i, j);
                swapD(spectraTableRHCERR, i, j);
                swapD(jdTable, i, j);
                swapD(decyrTable, i, j);
                swapD(tsysTable, i, j);
                swapD(azTable, i, j);
                swapD(elTable, i, j);
                swapD(zTable, i, j);
                swapD(restFreqsTable, i, j);
                swapD(bandWidthTable, i, j);
                swapD(vlsrTable, i, j);
                swapD(fileTypesTab, i, j);
                swapD(AVRHeaders, i, j);
                swapD(isotimeTable, i, j);
                swapD(fileNamesTab, i, j);
                swapD(obsProtperties, i, j);

                // -- 2-D containers --
                swapD(spectraTableI, i, j);
                swapD(spectraTableV, i, j);
                swapD(spectraTableLHC, i, j);
                swapD(spectraTableRHC, i, j);
                swapD(velocityTable, i, j);
                swapD(channelTable, i, j);
                swapD(datetimeTable, i, j);
            }
        }
    }
    std::cout << "----> Done!" << std::endl;
    std::cout << "-----------------------" << std::endl;
}

// - czyści tablice bez zwalniania pamięci -
void spectral_container::clearAllTables()
{
    /*
     * Clears containers, needed to reload etc...
     * It should be specified, if containers are 2D or 1D
     */
    // -- 2D --
    spectraTableI.clear();
    spectraTableV.clear();
    spectraTableLHC.clear();
    spectraTableRHC.clear();
    velocityTable.clear();
    channelTable.clear();
    datetimeTable.clear();

    // -- 1D --
    spectraTableIERR.clear();
    spectraTableVERR.clear();
    spectraTableLHCERR.clear();
    spectraTableRHCERR.clear();
    mjdTable.clear();
    jdTable.clear();
    decyrTable.clear();
    tsysTable.clear();
    azTable.clear();
    elTable.clear();
    zTable.clear();
    restFreqsTable.clear();
    bandWidthTable.clear();
    vlsrTable.clear();
    fileTypesTab.clear();
    fileNamesTab.clear();
    AVRHeaders.clear();
    isotimeTable.clear();
    normalizationCoeffsI.clear();
    normalizationCoeffsV.clear();
    normalizationCoeffsLHC.clear();
    normalizationCoeffsRHC.clear();
}

// - sprawdza, czy wybrano psa -
// - fileName to nazwa sprawdzanego psa -
bool spectral_container::isPies(std::string fileName)
{
    std::ifstream tmpPies; // deklarujemy pusty obiekt sprawdzanego psa
    std::string bufoPies; // deklarujemy bufor do psa
    tmpPies.open( fileName.c_str() );

    // -- robimy fikołka --
    try
    {
        // -- sposób sprawdzania, czy wybrano psa jest bardzo prosty --
        // po prostu sprawdzamy, czy ma na początku trzy znaki zapytania (XD)
        // głupie, ale działa
        tmpPies >> bufoPies;
        tmpPies.close();
        if (bufoPies == "???")
        {
            // jeśli mamy te trzy znaki zapytania, zwracamy true
            return true;
        }
        else
        {
            // jeśli nie mamy tych trzech znaków zapytania, zwracamy false
            return false;
        }
    }
    catch (...)
    {
        // jeśli z jakiegoś powodu wypier*****o przy czytaniu to cóż
        // zwracamy jakby to był fits
        // bo w takim trybie prędzej fitsa nie przeczyta
        return false;
    }

}

double spectral_container::JD(double year, double month, double day)
{
  // metoda opisana na: https://gist.github.com/jiffyclub/1294443 (dostep: 25.09.2019, 1:00 UTC)
  // maly tweaking
  double yearp, monthp, A,B,C,D;
  if(month == 1 || month == 2)
  {
    yearp = year - 1.0;
    monthp = month + 12.0;
  }
  else
  {
    yearp = year;
    monthp = month;
  }

  // sprawdzamy jak sie ma nasza data w stosunku do 15 pazdziernika 1582, czyli poczatku kalendarza
  // gregorianskiego

  if (year < 1582.0 || (year == 1582.0 && month < 10.0) || (year == 1582.0 && month < 10.0 && day < 15.0) )
  {
    // przed startem gregorianskiego
    B = 0.0;
  }
  else
  {
    // po starcie gregorianskiego
    A = trunc(yearp / 100.0);
    B = 2.0  - A + trunc(A / 4.0);
  }

  if (yearp < 0.0)
  {
    C = trunc((365.25 * yearp) - 0.75);
  }
  else
  {
    C = trunc((365.25 * yearp));
  }

  D = trunc(30.6001 * (monthp + 1.0));

  double jd = B+C+D+day + 1720994.5;
  return jd;


}

double spectral_container::decimalyear(double year, double month, double day)
{
    double days_in_year = 365.25;
    std::vector < int > days_in_month(12);
    days_in_month[0] = 31;
    days_in_month[1] = 28;
    days_in_month[2] = 31;
    days_in_month[3] = 30;
    days_in_month[4] = 31;
    days_in_month[5] = 30;
    days_in_month[6] = 31;
    days_in_month[7] = 31;
    days_in_month[8] = 30;
    days_in_month[9] = 31;
    days_in_month[10] = 30;
    days_in_month[11] = 31;

    // sprawdzamy, czy rok jest przestepny
    if (int(year) % 4 == 0)
    {
        if(int(year) % 100 != 0 || int(year) % 400)
        {
            days_in_month[1] = 29;
            days_in_year = 366.25;
        }

    }

    // liczyny days w tym roku
    double days_into_year = 0.0;
    for(int i = 0; i < int(month)-1; i++)
    {
        days_into_year = days_into_year + double(days_in_month[i]);
    }
    days_into_year = days_into_year + day;

    double decim = year + days_into_year / days_in_year;
    return decim;

}

std::vector < std::vector < double > > spectral_container::recreate_from_rlhc (std::vector < double > lhc, std::vector < double > rhc)
{
    // --- deklarujemy potrzebne tablice ---
    std::vector < std::vector < double > > IV;
    std::vector < double > I;
    std::vector < double > V;

    // -- blok zapełniający te tablice za pomocą wczytanych LHC i RHC --
    for(unsigned long int i = 0; i < lhc.size(); i++)
    {
        // -- dodajemy I --
        I.push_back( (lhc[i] + rhc[i]) / 2.0 );
        // -- dodajemy V --
        V.push_back( (rhc[i] - lhc[i]) / 2.0);
    }
    // -- dodajemy do zwracanej tablicy --
    IV.push_back(I);
    IV.push_back(V);
    // -- zwracamy --
    return IV;
}

double spectral_container::calculate_RMS(std::vector < double > polarization, std::vector < unsigned long int > limits)
{
    // - definiujemy dwie zmienne -
    int n = 0;
    double suma = 0.0;

    // - pętla -
    for(unsigned long int i = limits[0]-1; i < limits[1]; i++)
    {
        suma = suma + polarization[i] * polarization[i];
        n = n + 1;
    }
    for(unsigned long int i = limits[2]-1; i < limits[3]; i++)
    {
        suma = suma + polarization[i] * polarization[i];
        n = n + 1;
    }

    return sqrt(suma / (n-1));

}

std::vector < double > spectral_container::makeTimeFromIsotime(std::string isotime)
{
    std::vector < double > time_temporal = extractDoublesFromIsotime(isotime);
    // zapisujemy z tablicy do naszych zmiennych
    double year = time_temporal[0];
    double month = time_temporal[1];
    double day = time_temporal[2];
    double hour = time_temporal[3];
    double min = time_temporal[4];
    double sec = time_temporal[5];
    // dodatkowa zmienna day2, integrująca godziny
    double day2 = day + hour / 24.0 + min / 24.0 / 60.0 + sec / 24.0 / 3600.0;
    // bierzemy sobie coś, co nazywa się JD:
    double jd = JD(year, month, day2);
    double mjd = jd - 2400000.5;
    double decyr = decimalyear(year, month, day2); // zmiennoprzecinkowy rok

    std::vector < double > time_vector = {jd, mjd, decyr};
    return time_vector;
}

std::vector < double > spectral_container::extractDoublesFromIsotime(std::string isotime)
{
    // zapisujemy do innej zmiennej, oryginał jeszcze się przyda
    std::string isotime2 = isotime;
    // formatujemy, by między numerami były białe znaki
    isotime2.replace(isotime2.find_first_of("-"), 1, " ");
    isotime2.replace(isotime2.find_first_of("-"), 1, " ");
    isotime2.replace(isotime2.find_first_of("T"), 1, " ");
    isotime2.replace(isotime2.find_first_of(":"), 1, " ");
    isotime2.replace(isotime2.find_first_of(":"), 1, " ");
    // zapisujemy do zmiennych double
    std::stringstream wppl(isotime2);
    // tymczasowa tablica i bufor double
    std::vector < double > time_temporal;
    double bufor_double_time;
    // pętla parsująca string na double
    while(wppl >> bufor_double_time)
    {
        time_temporal.push_back(bufor_double_time);
    }
    return time_temporal;
}

std::vector < double > spectral_container::loadPOLfromAVR(std::vector < std::string > linesInFile, int line_begin)
{
     /*
     linie w pliku:
     17  - początek I
     287 - początek V
     557 - początek LHC
     827 - początek RHC
     */

    // kilka zmiennych na początek
    std::string bufor;
    double bufor_double;

    // tymczasowy kontener na początek
    std::vector < double > tmp_container(2048);

    // -- I --
    // zapełniamy pierwsze  i ostatnie 23 kanały zerami
    for(int i = 0; i < 24; i++)
    {
        tmp_container[i] = 0.0;
        tmp_container[2047 - i] = 0.0;
    }

    // zapełniamy resztę
    int index_in_table = 24;
    for (unsigned long int k = 0; k < 250; k++)
    {
        bufor = linesInFile[line_begin+k];
        std::stringstream ss(bufor);
        while(ss >> bufor_double)
        {
            tmp_container[index_in_table] = (bufor_double / 1000.0); // dodajemy do kontenera
            index_in_table++; // inkrementujemy index w kontenerze
        }

    }

    // zwracamy kontener
    return tmp_container;

}

std::vector < std::vector < double > > spectral_container::doppler_track(double overall_velocity, double restfreq, double freq_rang, double nchans)
{
    /*
     celem tej metody jest zwrócenie tablicy z prędkościami radialnymi i częstotliwościami
     */

    // prędkość światła
    double c = 299792.458; // km/s

    // DOPPLER TRACKING
    // beta
    double beta = overall_velocity / c;
    // gamma
    double gamma = 1.0 / sqrt(1.0 - beta * beta);
    // fcentr
    double fcentr = restfreq * (gamma * (1.0 - beta));
    // fbeg
    double freq_beg = fcentr - (freq_rang / 2.0);
    double freq_step = freq_rang / nchans;
    // ----------------

    // tablice z częstotliwościami i prędkościami
    std::vector < double > freqs((int) nchans), vels((int) nchans), channels((int) nchans);

    // -- generujemy tablice prędkości --
    for (int i = 0; i < nchans; i++)
    {
        freqs[i] = (freq_beg + i*freq_step);
        vels[i] = - c * ( (freqs[i] / restfreq) - 1.0);
        channels[i] = i + 1;
    }

    // -- odwracamy tablice, by VEL było od najmniejszej --
    std::vector < double > vel_rev((int) nchans), freqs_rev((int) nchans);
    for (int i = 0; i < nchans; i++)
    {
        vel_rev[i] = vels[vels.size() - 1 - i];
        freqs_rev[i] = freqs[freqs.size() - 1 - i];
    }

    std::vector < std::vector < double > > for_return(3);
    for_return[0] = freqs_rev;
    for_return[1] = vel_rev;
    for_return[2] = channels;

    return for_return;
}

std::string spectral_container::construct_isotime(double year, double month, double day, double hour, double min, double sec)
{
    // deklarujemy stringi, potrzebne do konstrukcji isoformatu
    // -- konstruujemy pytime format --
    string time_in_isoformat, yearstr, monthstr, daystr, hourstr, minutestr, secondstr;

    // zapisujemy czas w isoformacie (YYYY-MM-DD)
    //year
    yearstr = std::to_string((int)year);
    // month
    if (std::to_string((int)month).length() == 1)
        monthstr = string("0")+std::to_string((int)month);
    else
        monthstr = std::to_string((int)month);
    // day
    if (std::to_string((int)day).length() == 1)
        daystr = string("0") + std::to_string((int)day);
    else
        daystr = std::to_string((int)day);
    // hour
    if (std::to_string((int)hour).length() == 1)
        hourstr = string("0") + std::to_string((int)hour);
    else
        hourstr = std::to_string((int)hour);
    // minute
    if (std::to_string((int)min).length() == 1)
        minutestr = string("0") + std::to_string((int)min);
    else
        minutestr = std::to_string((int)min);
    // second
    if (std::to_string((int)sec).length() == 1)
        secondstr = string("0") + std::to_string((int)sec);
    else
        secondstr = std::to_string((int)sec);

    // zapisujemy do time...
    time_in_isoformat = yearstr + string("-") + monthstr + string("-") + daystr + string("T") + hourstr + string(":") + minutestr + string(":") + secondstr;

    return time_in_isoformat;
}

void spectral_container::print_loaded_comm(int obsnum, std::string isotime, double obs_error)
{
    // printuje komunikat o załadowanym pliku
    std::cout << "----> [" << obsnum << "]   " << isotime << "   rms: " << obs_error << std::endl;
}

std::string spectral_container::getHeaderFromAVRFile(std::vector<std::string> linesInFile)
{
    std::string tmpHeader = "";
    for(int i = 0; i < 14; i++)
    {
        tmpHeader = tmpHeader + linesInFile[i] + "\n";
    }
    return tmpHeader;
}

int spectral_container::lengthOfTheListFile(std::ifstream &lstfile)
{
    std::string bufor;
    int licznik = 0;
    while(lstfile.good())
    {
        std::getline(lstfile, bufor);
        licznik += 1;
    }
    //lstfile.seekg(0);
    lstfile.clear(lstfile.goodbit);
    return licznik;
}

void spectral_container::flag(int epoch)
{
    // -- nazwa oflagowanego pliku --
    std::string flaggedFilename = getFileNameFromFullPath(fileNamesTab[epoch-1]);
    appendToFlaggedList( flaggedFilename);
    std::cout << "----> Flagged " << flaggedFilename << std::endl;
    // -- okno do upewniania sie, ze na pewno chcesz --

//    QMessageBox::StandardButton upewka;
//    upewka = QMessageBox::question(nullptr, "Are you sure?", QString::fromStdString("Do you realy want to flag " + flaggedFilename + "?"), QMessageBox::Yes| QMessageBox::No);
//    if (upewka == QMessageBox::No)
//    {
//        return;
//    }

}

void spectral_container::appendToFlaggedList(std::string flaggedFilename)
{
    std::ofstream flagfile;
    flagfile.open((saveDirectory + "/" + "flagged_obs.dat").c_str(), std::ios_base::app );
    if (flagfile.good())
    {
        flagfile << flaggedFilename << std::endl;
        flagfile.close();
    }
}

std::vector < std::string > spectral_container::readFlaggedFiles()
{
    std::vector < std::string > returnedFlagFilesTable;
    // -- otwieramy plik z flagami --
    std::ifstream flagfile;
    flagfile.open((saveDirectory + "/" + "flagged_obs.dat").c_str());
    while(flagfile.good())
    {
        std::string bufor = "";
        std::getline(flagfile, bufor);
        returnedFlagFilesTable.push_back(bufor);
    }
    flagfile.close();
    return returnedFlagFilesTable;
}

bool spectral_container::checkIfFlagged(std::string fileName, const std::vector<std::string> &flagTable)
{
    std::string baseFileName = getFileNameFromFullPath(fileName);

    for(auto &i : flagTable)
    {
        if(baseFileName == i)
            return true;
        if((saveDirectory + "/" + baseFileName) == i)
            return true;
    }
    return false;
}

std::string spectral_container::getFileNameFromFullPath(std::string fileName)
{
    return fileName.substr(fileName.find_last_of("/\\")+1);
}

void spectral_container::setNewRMSChannels(std::vector<int> chns)
{
    for(int i = 0; i < (int) chns.size(); i++)
    {
        rmsChannelsTab[i] = (unsigned long int) chns[i];
    }
}

void spectral_container::recalculateRMS()
{
    spectraTableIERR.clear();
    spectraTableVERR.clear();
    spectraTableLHCERR.clear();
    spectraTableRHCERR.clear();
    for (int obsn = 0; obsn < (int) spectraTableI.size(); obsn++)
    {
        spectraTableIERR.push_back(calculate_RMS(spectraTableI[obsn], rmsChannelsTab));
        spectraTableVERR.push_back(calculate_RMS(spectraTableV[obsn], rmsChannelsTab));
        spectraTableLHCERR.push_back(calculate_RMS(spectraTableLHC[obsn], rmsChannelsTab));
        spectraTableRHCERR.push_back(calculate_RMS(spectraTableRHC[obsn], rmsChannelsTab));
    }

}

void spectral_container::fillNormalizationCoeffsWith1()
{
    normalizationCoeffsI.clear();
    normalizationCoeffsV.clear();
    normalizationCoeffsLHC.clear();
    normalizationCoeffsRHC.clear();
    for(unsigned long int i = 0; i < spectraTableI.size(); i++)
    {
        normalizationCoeffsI.push_back(1.0);
        normalizationCoeffsV.push_back(1.0);
        normalizationCoeffsLHC.push_back(1.0);
        normalizationCoeffsRHC.push_back(1.0);
    }
}

void spectral_container::setNormalizationCoeffs(int startingChan, int endingChan)
{
    normalizationCoeffsI.clear();
    normalizationCoeffsV.clear();
    normalizationCoeffsLHC.clear();
    normalizationCoeffsRHC.clear();
    normalizationCoeffsI = averagePolOverVelocity(startingChan, endingChan, spectraTableI);
    normalizationCoeffsV = averagePolOverVelocity(startingChan, endingChan, spectraTableV);
    normalizationCoeffsLHC = averagePolOverVelocity(startingChan, endingChan, spectraTableLHC);
    normalizationCoeffsRHC = averagePolOverVelocity(startingChan, endingChan, spectraTableRHC);
}

std::string spectral_container::getAllHeaderInformation(double vlsr, double freq_beg, double freq_end, double freq_rang, double equinox, double nchans, double restfreq, double az, double z, double tsys, double dopp_vsu, double dopp_vob, double dopp_vto, std::string sourcename, std::string isotime, std::string ra, std::string dec, std::string molecule)
{
    /*
     * Returns a string, that represents a header of the FITS file
     */
    std::string returnedStr = "";
    returnedStr += "OBJECT = " + sourcename + "\n";
    returnedStr += "EQUINOX = " + std::to_string(equinox) + "\n";
    returnedStr += "SRC_RA = " + ra + "\n";
    returnedStr += "SRC_DEC = " + dec + "\n";
    returnedStr += "DATE-OBS = " + isotime + "\n";
    returnedStr += "FREQ = " + std::to_string(restfreq) + "\n";
    returnedStr += "FRQ_BEG = " + std::to_string(freq_beg) + "\n";
    returnedStr += "FRQ_END = " + std::to_string(freq_end) + "\n";
    returnedStr += "FRQ_RANG = " + std::to_string(freq_rang) + "\n";
    returnedStr += "VSYS = " + std::to_string(vlsr) + "\n";
    returnedStr += "DOPP_VSU = " + std::to_string(dopp_vsu) + "\n";
    returnedStr += "DOPP_VOB = " + std::to_string(dopp_vob) + "\n";
    returnedStr += "DOPP_VTO = " + std::to_string(dopp_vto) + "\n";
    returnedStr += "MOLECULE = " + molecule + "\n";
    returnedStr += "AZ = " + std::to_string(az) + "\n";
    returnedStr += "Z = " + std::to_string(z) + "\n";
    returnedStr += "TSYS = " + std::to_string(tsys) + "\n";
    return returnedStr;
}

std::string spectral_container::makeProperFormatNumber(double number)
{
    std::string returnedStr = "";
    if( number < 10 )
    {
        returnedStr += "0";
        returnedStr += std::to_string((int)number);
    }
    else
    {
        returnedStr += std::to_string((int)number);
    }
    return returnedStr;
}

std::string spectral_container::constructRASTR(double rah, double ram, double ras)
{
    std::string returnedStr = "";
    returnedStr += makeProperFormatNumber(rah);
    returnedStr += "h";
    returnedStr += makeProperFormatNumber(ram);
    returnedStr += "m";
    returnedStr += makeProperFormatNumber(ras);
    returnedStr += "s";
    return returnedStr;
}

std::string spectral_container::constructDECSTR(double decd, double decm, double decs)
{
    std::string returnedStr = "";
    if(decd < 0)
    {
        decd *= -1;
        returnedStr += "-";
    }
    returnedStr += makeProperFormatNumber(decd);
    returnedStr += "d";
    returnedStr += makeProperFormatNumber(decm);
    returnedStr += "m";
    returnedStr += makeProperFormatNumber(decs);
    returnedStr += "s";
    return returnedStr;
}
