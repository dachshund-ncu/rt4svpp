# Source code for rt4sv++
This tool is designed to view data from NCU 32m radio telescope.

It comes with qt ui and makes use of qcustomplot library (https://www.qcustomplot.com/)

Release is deployed with linuxdeployqt (https://github.com/probonopd/linuxdeployqt)



'''Some major comments'''

This tool is designed for NCU Institute of Astronomy employees and students - if you are not one of them, it is likely useless for you.

-- Usage --

Just download suitable release and enjoy. .Deb release is now static and does not require depedencies. Only make sure, you use at least something based on ubuntu 18.04

If you want to build it instead...


-- Compilation on Linux systems --

- Needed Packages -

g++

qt5-default

CCFits and cfitsio libraries (https://heasarc.gsfc.nasa.gov/fitsio/CCfits/)


- How to install? -

sudo apt install g++

sudo apt install qt5-default

CCFits and cfitsio should be installed, according to the instructions provided by authors. Make sure, that installation directory is "/usr/local"


When ready, just type in main file catalogue "qmake", then "make". Compilation will start. Output binary is called "rt4sv++".
It is good to type "make clean" after compilation is done.

Sometimes it happens, that compilation is succesful, but the binary won't start - it is due linker being not able to find shared libraries. You can manually add search library to the linker by creating a new .conf file in /etc/ld.so.conf.d directory with one line:

/usr/local

then execude command:

sudo ldconfig


it should help

-- Known problems --

1. "My program does not want to compile"

Check version of your g++ compiler (type "g++ --version" in command line). If it is not in at least version 8, try to install it (sudo apt install g++-8). Then, change three lines in "Makefile":


From:

CC            = gcc  

CXX           = g++

LINK          = g++



To:

CC            = gcc-8

CXX           = g++-8

LINK          = g++-8

Compilation should run without problems now.


2. "I use old ubuntu/debian and i can not install g++-8"

My advice: update your system. But, if you REALLY have to use it, try this solution:

Install g++-4.8 (sudo apt install g++-4.8)

Change five lines in Makefile:

From:

CC            = gcc  

CXX           = g++

LINK          = g++

CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)

CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)

To:

CC            = gcc-4.8

CXX           = g++-4.8

LINK          = g++-4.8

CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT -std=c++11 -fPIC $(DEFINES)

CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT -std=c++11 -fPIC $(DEFINES)

type "make"

It should now run on your old system

3. I use fedora/red hat/arch/manjaro

Just don't use them 

Just joking.

I do not use system-specific libraries and commands inside rt4sv++, so if you compile it for these systems - it should perform fine.

4. Will this run on Windows?

Working on Windows with this program seems a bit non-natural to me - but since running it does not require terminal window, it can be done - you just need to compile it correctly. Best way is to download qt tools from qt site and use them to compile. Also remember, that you'll probably need to copy some dll files to executable directory to open it outside qtCreator.
Also there is no point of building windows version, since it is also in the "Release" section now.
