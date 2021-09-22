#include "spectral_container.h"
#include <CCfits/CCfits>
// - metoda inicjująca klasę -
spectral_container::spectral_container()
{
    //std::cout << "Utworzono kontener spektralny!" << std::endl;
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

    // -- zdobywamy info o ścieżce całkowitej --
    QFileInfo infotmp (QString::fromStdString(listWithFilenames));
    std::string working_directory = infotmp.absolutePath().toStdString();


    // bufor
    std::string bufor;
    // pętla
    while (filesList.good())
    {
        // czytamy jedną linię z listy plików
        std::getline(filesList, bufor);

        // ładujemy plik z listy
        // w argumencie podajemy ABSOLUTNĄ ścieżkę
        loadSingleSpectrumFromFile(working_directory + "/" + bufor);
    }
    filesList.close();

}

// - metoda czytająca listę plików -
void spectral_container::loadDataFromList(QStringList qtListaPlikow)
{
    // -- na początek - czyścimy kontenery --
    clearAllTables();

    // -- i czytamy pliki zgodnie z listą --
    for(int i = 0; i < qtListaPlikow.size(); i++)
    {
        loadSingleSpectrumFromFile(qtListaPlikow[i].toStdString());
    }
    // w liście zawsze będą absolutne ścieżki do plików

}


// - metoda czytająca pojedynczy plik z listy -
void spectral_container::loadSingleSpectrumFromFile(std::string spectrumFileName)
{
    // failsafe na pustą linię
    if (spectrumFileName == "")
        return;

    // tutaj rozpoczyna się czytanie pojedynczego pliku
    // pies to plik AVR, brak psa - FITS
    if (isPies(spectrumFileName))
    {
        std::ifstream pies;
        pies.open(spectrumFileName.c_str());
        loadSingleSpectrum(pies);
    }
    else
    {
        CCfits::FITS niePies(spectrumFileName, CCfits::Read);
        loadSingleSpectrum(niePies);
    }

    // dodatkowo dodajemy do listy plików nazwę
    fileNamesTab.push_back(spectrumFileName);

}

void spectral_container::loadSingleSpectrum(std::ifstream &file)
{

}

void spectral_container::loadSingleSpectrum(CCfits::FITS & file)
{
    // deklarujemy tymczasowe zmienne w stacku
    // zostaną zniszczone po wykonaniu funkcji, więc nie musimy się o nie martwić
    double vlsr, freq_beg, freq_mid, freq_end, freq_rang, equinox, nchans, restfreq, el, az, z, tsys1, tsys2, dopp_vsu, dopp_vob, dopp_vto;
    double year, month, day, hour, min,sec;
    std::string zstr, tsysstr, vlsr_str, freq_beg_str, freq_mid_str, freq_end_str, freq_rang_str, equinox_str, nchans_str, restfreq_str, el_str, az_str, z_str, tsys1_str, tsys2_str, dopp_vsu_str, dopp_vob_str, dopp_vto_str;
    std::string sourcename, isotime, ra, dec;

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
        table.readKey("AZ", az_str);
        az = stod(az_str);
    }

    // Z
    try
    {
        table.readKey("Z", z);
    }
        catch(...)
    {
        table.readKey("Z", zstr);
        z = stod(zstr);
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
            table.readKey("TSYS", tsysstr);
            tsys1 = stod(tsysstr);
            tsys2 = stod(tsysstr);
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

    // -- deklarujemy tablice z częstotliwościami i prędkościami --
    std::vector < double > freqs((int) nchans), vels((int) nchans);
    // -- krok częstotliwości --
    double freq_step = freq_rang / nchans;
    // prędkość światła
    double c = 299792.458;

    // DOPPLER TRACKING
    // całkowita prędkość w kierunku źródła
    double overall_velocity = vlsr + dopp_vto;
    double beta = overall_velocity / c;
    // gamma
    double gamma = 1.0 / sqrt(1.0 - beta * beta);
    // fcentr
    double fcentr = restfreq * (gamma * (1.0 - beta));
    // fbeg
    freq_beg = fcentr - (freq_rang / 2.0);
    // ----------------

    // -- generujemy tablice prędkości --
    for (int i = 0; i < nchans; i++)
    {
        freqs[i] = (freq_beg + i*freq_step);
        vels[i] = - c * ( (freqs[i] / restfreq) - 1.0);
    }

    // -- odwracamy tablice, by VEL było od najmniejszej --
    std::vector < double > vel_rev((int) nchans), lhc_rev((int) nchans), rhc_rev((int) nchans);
    for (int i = 0; i < nchans; i++)
    {
        vel_rev[i] = vels[vels.size() - 1 - i];
        lhc_rev[i] = lhc[lhc.size() - 1 - i];
        rhc_rev[i] = rhc[rhc.size() - 1 - i];
    }
    // zapisujemy do oryginalnych
    vels = vel_rev;
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
    std::vector < unsigned long int > rms_limits = {100, 400, (unsigned long int) nchans - 400, (unsigned long int) nchans - 100};
    double rmsI = calculate_RMS(i_tmp_lst, rms_limits);
    double rmsV = calculate_RMS(v_tmp_lst, rms_limits);
    double rmsLHC = calculate_RMS(lhc, rms_limits);
    double rmsRHC = calculate_RMS(rhc, rms_limits);

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
}

// - sortowanie bąbelkowe po epokach -
void spectral_container::bubbleSortEpochs()
{

}

// - czyści tablice bez zwalniania pamięci -
void spectral_container::clearAllTables()
{
    spectraTableI.clear();
    spectraTableV.clear();
    spectraTableLHC.clear();
    spectraTableRHC.clear();

    spectraTableIERR.clear();
    spectraTableVERR.clear();
    spectraTableLHCERR.clear();
    spectraTableRHCERR.clear();

    velocityTable.clear();
    datetimeTable.clear();
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

    fileTypeTab.clear();
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
    for(unsigned long int i = limits[0]; i < limits[1]; i++)
    {
        suma = suma + polarization[i] * polarization[i];
        n = n + 1;
    }
    for(unsigned long int i = limits[2]; i < limits[3]; i++)
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
