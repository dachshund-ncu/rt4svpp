# Source code for rt4sv++
This tool is designed to view data from NCU 32m radio telescope.

It comes with qt ui and makes use of qcustomplot library (https://www.qcustomplot.com/)

Releases before 1.35 were deployed with linuxdeployqt (https://github.com/probonopd/linuxdeployqt)



### Some major comments ###

This tool is designed for NCU Institute of Astronomy employees and students - if you are not one of them, it is likely useless for you.

## Obtaining ##
Best way to enjoy this app is to download it from repository:

### using CURL
```bash
curl -SsL https://dachshund-ncu.github.io/rt4svpp_ppa/dists/stable/KEY.gpg | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/rt4svpp-keyring.gpg
```
```bash
sudo curl -SsL -o /etc/apt/sources.list.d/rt4svpp.list https://dachshund-ncu.github.io/rt4svpp_ppa/rt4svpp.list
```

### using WGET
```bash
wget -q https://dachshund-ncu.github.io/rt4svpp_ppa/dists/stable/KEY.gpg -O- | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/rt4svpp-keyring.gpg
```
```bash
sudo wget https://dachshund-ncu.github.io/rt4svpp_ppa/rt4svpp.list -O /etc/apt/sources.list.d/rt4svpp.list
```

### Then type
```bash
sudo apt update
```
```bash
sudo apt install rt4svpp
```

Also you can just download suitable release and enjoy it. .Deb release is now static and does not require depedencies. Only make sure, you use at least something based on ubuntu 18.04


## Usage ##
```bash
rt4sv++ list_of_files
or 
rt4sv++ [OPTIONS] 
OPTIONS: 
-h, --help      | Display this message 
-v, --version   | Display version info 
```
where list_of_files contains list of filenames of the .fits files you wish to load. 

### sample_data ###
This directory contains a set of .fits files, that can be loaded into RT4SV++. These files are 6.7 GHz methanol maser observations, performed between 2009 and 2022 and are already published in [Szymczak et al. 2014](https://ui.adsabs.harvard.edu/abs/2014MNRAS.439..407S/abstract) and [Durjasz et al. 2022](https://ui.adsabs.harvard.edu/abs/2022arXiv220508759D/abstract). To load these files into rt4sv++:
```bash
cd sample_data
ls *.fits > list_of_files
rt4sv++ list_of_files
```


## Compilation on Linux systems ##

### Needed Packages ###
- g++
- gfortran
- QT5:
  - qt5-default (before Ubuntu 21.04)
  - qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools (Ubuntu 21.04 and after)
- [CCFits](https://heasarc.gsfc.nasa.gov/fitsio/CCfits/)
- [cfitsio](https://heasarc.gsfc.nasa.gov/docs/software/fitsio/fitsio.html)


### How to install required packages? ###
If you run something, based on Ubuntu LTS, you can use installation script: 
```bash
sudo python3 installReqs.py
```
Just remember to uncoment proper line for installing qt on yout distro (it can install **qt5-default** or **qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools**)

To install packages manually:
```bash
sudo apt install gfortran
sudo apt install g++
```
```bash
sudo apt install qt5-default
```
or
```bash
sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
```


**cfitsio**
* untar the files
* in the main untared directory run ./configure --prefix=/usr/local/
* run make
* run sudo make install


**CCfits**
* unter the files
* in the main untared directory run ./configure
* run make
* run make install

## Compilation ##
Just type
```bash
qmake
make
make clean
```
Output binary is called "rt4sv++".


## Known problems ##
### Compilation succesful, but app won't start ###
Sometimes it happens, that compilation is succesful, but the binary won't start - it is due linker being not able to find shared libraries. You can manually add search library to the linker by creating a new .conf file in directory:
```bash
/etc/ld.so.conf.d 
```
This file should have only one line: a catalogue of CCFITS and CFITSIO install. If you followed carefully the steps, described above, it should be:
```bash
/usr/local
```
After creating this file, execute the command:
```bash
sudo ldconfig
```
Now the app should start
