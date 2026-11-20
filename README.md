# RT4SV++ — Radio Telescope Spectra Visualizer

RT4SV++ is a C++ application designed for visualization and analysis of radio astronomical spectral observations obtained with the **32-m radio telescope operated by the Institute of Astronomy, Nicolaus Copernicus University (NCU), Toruń, Poland**.

The application provides both a graphical user interface (GUI) and a command-line interface (CLI), allowing interactive exploration of spectra as well as automated processing of observational data.

RT4SV++ is built using **Qt6** and uses the [QCustomPlot](https://www.qcustomplot.com/) library for scientific plotting. FITS file handling is provided by [CCfits](https://heasarc.gsfc.nasa.gov/fitsio/CCfits/) and [CFITSIO](https://heasarc.gsfc.nasa.gov/docs/software/fitsio/fitsio.html).

## Features

### Graphical interface

- Interactive visualization of dynamic spectra
- Display and comparison of individual spectral observations
- Support for Stokes I, V, LHC and RHC polarization data
- RMS, system temperature and integrated flux density analysis
- Averaging over spectral channels and observation epochs
- Spectral integration and variability analysis
- Extraction and export of light curves
- Observation flagging and exclusion
- Export of processed spectral data
- Dark and light interface themes

### Command-line interface

The CLI enables automated data processing without launching the graphical interface.

Supported features include:

- Loading individual FITS files, multiple files or observation lists
- Shell-expanded wildcard input
- Averaging over selected channels (`--aov`)
- Averaging over selected epochs (`--aot`)
- Automatic selection of complete data ranges using `all`
- Custom observation flagging files
- Multiple processing operations in a single invocation

## Intended audience

RT4SV++ was developed primarily for researchers and students at the NCU Institute of Astronomy working with single-dish radio spectroscopy observations.

Although its data handling is tailored to the NCU radio telescope, parts of the application may be useful for other radio astronomy projects using compatible observational formats.

## Installation

### Prebuilt packages

Prebuilt releases, when available, can be downloaded from the [GitHub Releases](https://github.com/dachshund-ncu/rt4svpp/releases) page.

Available package formats and supported operating systems depend on the release.

### Legacy APT repository

An APT repository has historically been provided for Debian/Ubuntu-based systems.

Install the repository signing key:

```bash
curl -fsSL \
  https://dachshund-ncu.github.io/rt4svpp_ppa/dists/stable/KEY.gpg \
  | sudo gpg --dearmor \
  -o /etc/apt/trusted.gpg.d/rt4svpp-keyring.gpg
```

Add the repository:

```bash
sudo curl -fsSL \
  -o /etc/apt/sources.list.d/rt4svpp.list \
  https://dachshund-ncu.github.io/rt4svpp_ppa/rt4svpp.list
```

Install RT4SV++:

```bash
sudo apt update
sudo apt install rt4svpp
```

**Note:** The legacy repository may contain older builds. Compatibility with the current Qt6-based source code is not guaranteed.

## Usage

RT4SV++ can operate in two modes:

- **GUI mode:** launched without processing operations
- **CLI mode:** activated when data-processing operations are specified

### Graphical mode

Start the application:

```bash
rt4sv++
```

Open a single FITS file:

```bash
rt4sv++ observation.fits
```

Open multiple observations:

```bash
rt4sv++ --input observations/*.fits
```

The graphical interface can also load observation lists containing paths to spectral files.

### Command-line mode

General syntax:

```bash
rt4sv++ [INPUT FILES...] [OPTIONS]
```

Or:

```bash
rt4sv++ --input FILE [FILE ...] [OPTIONS]
```

### Available options

| Option | Description |
|---|---|
| `--input FILE [FILE ...]` | Load one or more observation files |
| `--aov START END` | Average over a specified range of spectral channels |
| `--aov all` | Average over all available channels |
| `--aot START END` | Average over a specified range of observation epochs |
| `--aot all` | Generate an average spectrum using all loaded epochs |
| `--flagged_files FILE` | Use a custom file containing flagged observations |
| `-h`, `--help` | Display command-line help |
| `-v`, `--version` | Display the application version |

Channel and epoch ranges use **1-based indexing**.

Both endpoints of a range are included.

### Examples

**Average all observations into a single spectrum:**

```bash
rt4sv++ --input observations/*.fits --aot all
```

**Average observations 1 through 100:**

```bash
rt4sv++ --input observations/*.fits --aot 1 100
```

**Average spectral channels 100 through 300:**

```bash
rt4sv++ --input observations/*.fits --aov 100 300
```

**Perform multiple operations:**

```bash
rt4sv++ --input observations/*.fits \
  --aov 100 300 \
  --aov 400 600 \
  --aot all
```

**Process observations using a custom flagging file:**

```bash
rt4sv++ --input observations/*.fits \
  --flagged_files /path/to/flags.dat \
  --aot all
```

Processing operations are independent. All AOV operations are performed before AOT operations.

### Observation lists

Instead of specifying individual files, RT4SV++ can read a text file containing observation filenames.

Example `observations.list`:

```text
observation_001.fits
observation_002.fits
observation_003.fits
```

Run:

```bash
rt4sv++ --input observations.list --aot all
```

Relative paths within observation lists are interpreted relative to the directory containing the list file.

### Flagging observations

RT4SV++ supports excluding individual observations from processing.

By default, the application looks for:

```text
flagged_obs.dat
```

in the directory containing the first input observation.

The file contains one observation filename per line:

```text
observation_002.fits
observation_015.fits
observation_107.fits
```

Flagged observations are skipped during data loading.

To use another file:

```bash
rt4sv++ --input observations/*.fits \
  --flagged_files custom_flags.dat \
  --aot all
```

Custom relative paths are interpreted relative to the current working directory. Absolute paths are also supported.

The default flagging file is optional. A missing custom flagging file is treated as an error.

### Output files

Processing results are written to the **current working directory**, independently of the location of the input observations.

For example:

```bash
cd /home/user/results

rt4sv++ --input /data/observations/*.fits --aot all
```

The resulting average spectrum is saved under `/home/user/results`.

Output filenames are generated automatically by the corresponding processing operations.

## Sample data

The `sample_data` directory contains FITS observations of the 6.7 GHz methanol maser emission associated with Cepheus A.

The observations were obtained between 2009 and 2022 and are associated with the following publications:

- [Szymczak et al. (2014), MNRAS, 439, 407](https://ui.adsabs.harvard.edu/abs/2014MNRAS.439..407S/abstract)
- [Durjasz et al. (2022)](https://ui.adsabs.harvard.edu/abs/2022arXiv220508759D/abstract)

To open all sample observations in the GUI:

```bash
rt4sv++ --input sample_data/*.fits
```

To generate an average spectrum:

```bash
rt4sv++ --input sample_data/*.fits --aot all
```

Alternatively, create an observation list:

```bash
cd sample_data
ls *.fits > list_of_files
rt4sv++ list_of_files
```

## Building from source

### Requirements

RT4SV++ requires:

- A C++17-compatible compiler (GCC or Clang)
- Qt6 (Widgets and GUI components)
- qmake6
- CCfits
- CFITSIO
- GNU Make
- QCustomPlot (included in the source tree)

The application currently uses **qmake** as its build system.

### Ubuntu / Debian

Install development dependencies:

```bash
sudo apt update
sudo apt install \
  build-essential \
  qt6-base-dev \
  qt6-base-dev-tools \
  qmake6 \
  libccfits-dev \
  libcfitsio-dev \
  gfortran
```

Package availability may vary depending on the distribution version and enabled repositories.

### Fedora

Install the required development tools and libraries:

```bash
sudo dnf install \
  gcc-c++ \
  make \
  qt6-qtbase-devel \
  CCfits-devel \
  cfitsio-devel \
  gcc-gfortran
```

### Compilation

Clone the repository:

```bash
git clone https://github.com/dachshund-ncu/rt4svpp.git
cd rt4svpp
```

Generate the Makefile using Qt6:

```bash
qmake6
```

Compile:

```bash
make -j$(nproc)
```

Run:

```bash
./rt4sv++
```

The generated executable is named `rt4sv++`.

### Clean rebuild

After changing the project configuration or build dependencies, a clean rebuild may be necessary.

```bash
make distclean
qmake6
make -j$(nproc)
```

This regenerates the build configuration and prevents stale object files from being reused.

## Testing

The project includes unit tests for command-line argument parsing.

Compile the CLI parser tests:

```bash
mkdir -p build

g++ -std=c++17 -Wall -Wextra \
  -Iinterface \
  tests/test_cli.cpp \
  interface/cli.cpp \
  -o build/test_cli
```

Run the tests:

```bash
./build/test_cli
```

The CLI parser can also be exercised manually:

```bash
./rt4sv++ --help
./rt4sv++ --version
```

For data-processing tests, the included sample observations can be used:

```bash
./rt4sv++ --input sample_data/*.fits --aot all
```

Automated integration tests and numerical validation of processing results are planned for future development.

## Project structure

```text
rt4svpp/
├── UI/                   # Qt graphical components
├── data/                 # Spectral data processing
│   ├── spectral_container.cpp
│   ├── spectral_container.h
│   ├── averovertime.cpp
│   └── averovervelocity.cpp
├── interface/            # CLI parser and runner
│   ├── cli.cpp
│   ├── cli.h
│   ├── cli_runner.cpp
│   └── cli_runner.h
├── libs/                 # Bundled plotting library
├── images/               # Icons and UI resources
├── sample_data/          # Example FITS observations
├── tests/                # Tests
├── body.cpp              # Main GUI implementation
├── body.h
├── main.cpp              # Application entry point
└── resources.qrc
```

The application separates its graphical interface from the spectral processing layer.

The `spectral_container` class provides common data-loading and processing functionality used by both GUI and CLI modes.

## Troubleshooting

### Shared libraries cannot be found

If compilation succeeds but the executable cannot locate CCfits or CFITSIO, inspect its shared-library dependencies:

```bash
ldd ./rt4sv++
```

Libraries installed manually under `/usr/local/lib` or `/usr/local/lib64` may require additional dynamic linker configuration.

After configuring the appropriate library paths, update the linker cache:

```bash
sudo ldconfig
```

Prefer distribution-managed packages whenever possible.

### Qt build configuration issues

If qmake selects an incorrect Qt version, invoke `qmake6` explicitly.

After switching Qt versions or modifying the project file, perform a clean rebuild.

### FITS loading errors

Verify that input files exist and are readable.

Relative paths passed directly through the CLI are resolved against the process working directory.

Paths inside observation lists are resolved relative to the list file directory.

### File permissions

Make sure RT4SV++ has permission to read the input observations and write results into the current working directory.

## Development and releases

The project is under active development.

Planned improvements include:

- Continuous integration using GitHub Actions
- Automated builds and GitHub Releases
- Linux distribution packages (`.deb` and `.rpm`)
- Additional cross-platform builds
- Expanded unit and integration tests
- Improved packaging and dependency handling

For existing published versions, see [GitHub Releases](https://github.com/dachshund-ncu/rt4svpp/releases).

## License

See [LICENSE.md](LICENSE.md) for licensing information.

## Acknowledgments

RT4SV++ was developed for analysis and visualization of radio astronomical observations obtained with the NCU 32-m radio telescope.

The application uses the following external libraries:

- [Qt](https://www.qt.io/)
- [QCustomPlot](https://www.qcustomplot.com/)
- [CCfits](https://heasarc.gsfc.nasa.gov/fitsio/CCfits/)
- [CFITSIO](https://heasarc.gsfc.nasa.gov/docs/software/fitsio/fitsio.html)

Earlier releases (before version 1.35) used [linuxdeployqt](https://github.com/probonopd/linuxdeployqt) for deployment.
