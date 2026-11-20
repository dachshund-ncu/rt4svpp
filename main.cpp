
#include <QApplication>
#include <QIcon>

#include <CCfits/CCfits>

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include "body.h"
#include "interface/cli.h"

#define RT4SV_VERSION "1.46"

void onWelcome() {
    std::cout
        << "-----------------------------------------\n"
        << "-----> Welcome to RT4SV++ "
        << "(RT4 Spectra Visualizer ++)\n";
}

void onVersion() {
    std::cout << "RT4SV++ version: "
              << RT4SV_VERSION << '\n';
}

int main(int argc, char* argv[]) {
    const std::string programName =
        (argc > 0 && argv[0]) ? argv[0] : "rt4sv++";

    // Version handling (not yet implemented in CliParser)
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == nullptr)
            continue;

        const std::string arg(argv[i]);

        if (arg == "-v" || arg == "--version") {
            onVersion();
            return 0;
        }
    }

    // Parse command-line arguments
    CliOptions options;

    try {
        CliParser parser;
        options = parser.parse(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << "RT4SV++: " << e.what() << "\n\n";
        CliParser::printHelp(programName);
        return 1;
    }

    if (options.showHelp) {
        CliParser::printHelp(programName);
        return 0;
    }

    onWelcome();

    // CLI data processing is not connected yet
    if (options.hasOperations()) {
        std::cerr
            << "Error: CLI data operations are "
            << "not implemented yet.\n";
        return 1;
    }

    // Initialize GUI
    Q_INIT_RESOURCE(resources);
    CCfits::FITS::setVerboseMode(false);

    QApplication app(argc, argv);
    app.setWindowIcon(
        QIcon(":/images/deathstaradder.svg")
    );

    // Preserve legacy GUI input behavior
    const std::string inputPath =
        options.inputFiles.empty()
            ? ""
            : options.inputFiles.front();

    body window(nullptr, inputPath.c_str());

    return app.exec();
}
