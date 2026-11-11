#include "cli.h"

#include <iostream>
#include <limits>
#include <stdexcept>

int CliParser::parseInteger(const std::string& value) {
    std::size_t pos = 0;
    long long result = 0;
    try {
        result = std::stoll(value, &pos, 10);
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid integer: " + value);
    }
    if (pos != value.size() ||
        result < std::numeric_limits<int>::min() ||
        result > std::numeric_limits<int>::max()) {
        throw std::invalid_argument("Invalid integer: " + value);
    }
    return static_cast<int>(result);
}

CliOptions::Range CliParser::parseRange(const std::string& start,
                                        const std::string& end) {
    const int first = parseInteger(start);
    const int last = parseInteger(end);
    if (first < 1 || last < first) {
        throw std::invalid_argument("Invalid range: " + start + " " + end +
                                    " (expected 1 <= START <= END)");
    }
    return {first, last};
}

bool CliParser::isOption(const std::string& argument) {
    // A single '-' is not considered an option here (but is not a supported input file).
    return !argument.empty() && argument[0] == '-';
}

void CliParser::addInput(CliOptions& options, const std::string& path) {
    if (path.empty()) {
        throw std::invalid_argument("Input filename cannot be empty");
    }
    // Globs are expanded by the user's shell. Do not silently interpret quoted patterns.
    if (path.find_first_of("*?[]") != std::string::npos) {
        throw std::invalid_argument("Unexpanded wildcard pattern: " + path);
    }
    options.inputFiles.push_back(path);
}

CliOptions CliParser::parse(int argc, char* argv[]) const {
    CliOptions options;
    if (argc < 0 || (argc > 0 && argv == nullptr)) {
        throw std::invalid_argument("Invalid argc/argv");
    }

    // Help takes precedence over malformed unrelated arguments.
    for (int i = 1; i < argc; ++i) {
        if (argv[i] != nullptr &&
            (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h")) {
            options.showHelp = true;
            return options;
        }
    }

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == nullptr) {
            throw std::invalid_argument("Null command-line argument");
        }
        const std::string arg(argv[i]);

        if (arg == "--input") {
            // Consume a shell-expanded list until the next option.
            const int first = i + 1;
            while (i + 1 < argc && argv[i + 1] != nullptr &&
                   !isOption(argv[i + 1])) {
                addInput(options, argv[++i]);
            }
            if (i + 1 < argc && argv[i + 1] == nullptr) {
                throw std::invalid_argument("Null command-line argument");
            }
            if (i + 1 == first) {
                throw std::invalid_argument("--input requires at least one filename");
            }
        } else if (arg == "--flagged_files") {
            if (i + 1 >= argc || argv[i + 1] == nullptr ||
                isOption(argv[i + 1]) || std::string(argv[i + 1]).empty()) {
                throw std::invalid_argument("--flagged_files requires a filename");
            }
            options.flaggedFile = argv[++i];
            if (options.flaggedFile.find_first_of("*?[]") != std::string::npos) {
                throw std::invalid_argument(
                    "Unexpanded wildcard pattern in --flagged_files: " + options.flaggedFile);
            }
        } else if (arg == "--aov" || arg == "--aot") {
            if (i + 2 >= argc || argv[i + 1] == nullptr || argv[i + 2] == nullptr) {
                throw std::invalid_argument(arg + " requires START and END integers");
            }
            const auto range = parseRange(argv[i + 1], argv[i + 2]);
            (arg == "--aov" ? options.aovOperations : options.aotOperations)
                .push_back(range);
            i += 2;
        } else if (isOption(arg)) {
            throw std::invalid_argument("Unknown option: " + arg);
        } else {
            addInput(options, arg);
        }
    }
    validate(options);
    return options;
}

void CliParser::validate(const CliOptions& options) {
    if (options.hasOperations() && options.inputFiles.empty()) {
        throw std::invalid_argument("Input files are required for CLI operations");
    }
}

void CliParser::printHelp(const std::string& programName) {
    std::cout
        << "RT4SV++ - Radio Telescope Spectra Visualizer\n\n"
        << "Usage:\n  " << programName << " [FILES...] [options]\n\n"
        << "Input:\n"
        << "  Positional files or --input FILE [FILE ...].\n"
        << "  Accepted by the loading layer: FITS/AVR files or an observations list.\n"
        << "  Use unquoted shell globs (e.g., *.fits); quoted patterns are rejected.\n\n"
        << "Options:\n"
        << "  --input FILE [FILE ...]  Add one or more input paths\n"
        << "  --aov START END         Average over velocity (channels)\n"
        << "  --aot START END         Average over time (epochs)\n"
        << "  --flagged_files FILE    Flagged observations list (default: flagged_obs.dat)\n"
        << "  -h, --help              Show this help\n\n"
        << "Operations are independent and may be repeated.\n\n"
        << "Examples:\n"
        << "  " << programName << " observation.fits\n"
        << "  " << programName << " --input *.fits --aov 100 300\n"
        << "  " << programName << " obs1.fits obs2.fits --aov 100 300 --aot 1 20\n";
}
