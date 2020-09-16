# Source code for rt4sv++
This tool is designed to view data from NCU 32m radio telescope.
It comes with qt ui.

-- Compilation on Linux systems --

You will need packages "qt4-default" or "qt5-default" and g++ compiler (works best with version 8)

When ready, just type in main file catalogue "qmake", then "make". Compilation will start. Output binary is called "mdrt4sv".
It is good to type "make clean" after compilation is done.

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
