# -- importing libraties --
import requests
import os
import tarfile


print("---------------------------------")
print("-----> Welcome! This is simple tool to install needed fits handling libraries for RT4SV++!")
print("-----> Installing required depedencies...")
#os.system('apt install qt5-default')
# os.system('apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools')
# os.system('apt install g++')
# os.system('apt install gfortran')
# os.system('apt install zlib1g-dev')

print("-----> Downloading needed archives...")
urlCCFITS = 'https://heasarc.gsfc.nasa.gov/FTP/software/fitsio/ccfits/CCfits.tar.gz'
ulrCFITSIO = 'https://heasarc.gsfc.nasa.gov/FTP/software/fitsio/c/cfitsio-4.6.3.tar.gz'

print("----> getting data for CCFITS")
CCFr = requests.get(urlCCFITS, allow_redirects=True)
print("----> getting data for CFITSIO")
CFTSIOr = requests.get(ulrCFITSIO, allow_redirects=True)

open('CCFITS.tar.gz', 'wb').write(CCFr.content)
open('CFTSIO.tar.gz', 'wb').write(CFTSIOr.content)

CCFtar = tarfile.open(name='CCFITS.tar.gz', mode='r')
CFTSIOtar = tarfile.open(name='CFTSIO.tar.gz', mode='r')
dirCCF = CCFtar.getnames()[0]
dirCFTSIO = CFTSIOtar.getnames()[0]

print('-----> extracting archives')
# -- untar --
CFTSIOtar.extractall()
CCFtar.extractall()
# -----------

print('-----> installing CFITSIO')
# -- install CFITSIO --
os.chdir(dirCFTSIO)
os.system('./configure --prefix=/usr/local --enable-static')
os.system('make')
os.system('make install')

print('-----> installing CCFITS')
# -- install CCFITS--
os.chdir('../' + dirCCF)
os.system('./configure --enable-static')
os.system('make')
os.system('make install')
# --------------------

# -- making linker work correctly: --
os.chdir('/etc/ld.so.conf.d/')
fle = open('rt4svpp.conf', 'w+')
fle.write('/usr/local/lib')
fle.close()
os.system('ldconfig')
# -----------------------------------

print("-----> Done!")
print("---------------------------------")
