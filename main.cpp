
#include <QApplication>
#include <QIcon>

#include <CCfits/CCfits>

#include <exception>
#include <iostream>
#include <string>

#include "body.h"
#include "interface/cli.h"
#include "interface/cli_runner.h"

#define RT4SV_VERSION "1.46"

int main(int argc, char* argv[])
{
    const std::string programName =
        (argc > 0 && argv[0]) ? argv[0] : "rt4sv++";

    // Handle version before parsing.
    // Version support can later be moved into CliParser.
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == nullptr)
            continue;

        const std::string arg(argv[i]);

        if (arg == "-v" || arg == "--version") {
            std::cout << "RT4SV++ version: "
                      << RT4SV_VERSION << '\n';
            return 0;
        }
    }

    CliOptions options;

    try {
        CliParser parser;
        options = parser.parse(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    if (options.showHelp) {
        CliParser::printHelp(programName);
        return 0;
    }

    // Headless CLI mode
    if (options.hasOperations()) {
        CliRunner runner;
        return runner.run(options);
    }

    // Interactive GUI mode
    Q_INIT_RESOURCE(resources);
    CCfits::FITS::setVerboseMode(false);

    QApplication app(argc, argv);

    app.setWindowIcon(
        QIcon(":/images/deathstaradder.svg")
    );

    body window(nullptr, options);

    return app.exec();
}
