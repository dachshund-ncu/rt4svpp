
#include "cli_runner.h"
#include "data/spectral_container.h"

#include <CCfits/CCfits>

#include <cstddef>
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

bool isFitsFile(const std::string& filename)
{
    try {
        CCfits::FITS fits(filename, CCfits::Read);
        fits.extension(1);
        return true;
    }
    catch (...) {
        return false;
    }
}

void loadInput(
    spectral_container& data,
    const std::vector<std::string>& files)
{
    if (files.empty()) {
        throw std::runtime_error(
            "No input files provided"
        );
    }

    auto progress = [](
        std::size_t /*current*/,
        std::size_t /*total*/)
    {
        // Progress reporting disabled.
    };

    // Preserve legacy behavior for a single list file.
    if (files.size() == 1 && !isFitsFile(files.front())) {
        std::cout << "Loading observations list: "
                  << files.front() << '\n';

        data.loadDataFromList(files.front(), progress);
    }
    else {
        std::cout << "Loading "
                  << files.size()
                  << " input file(s)\n";

        data.loadDataFromList(files, progress);
    }

    if (!data.loadedData ||
        data.spectraTableI.empty() ||
        data.spectraTableI.front().empty()) {
        throw std::runtime_error(
            "Could not load spectral data"
        );
    }
}

// Convert ALL (-1, -1) into the actual data range.
CliOptions::Range resolveRange(
    const CliOptions::Range& range,
    std::size_t maximum)
{
    if (range.first == CliOptions::ALL &&
        range.second == CliOptions::ALL) {

        if (maximum == 0 ||
            maximum > static_cast<std::size_t>(
                std::numeric_limits<int>::max()
            )) {
            throw std::out_of_range(
                "Invalid number of elements"
            );
        }

        return {
            1,
            static_cast<int>(maximum)
        };
    }

    return range;
}

// Validate a resolved range.
void validateRange(
    const CliOptions::Range& range,
    std::size_t maximum,
    const std::string& operation)
{
    if (range.first < 1 ||
        range.second < range.first ||
        static_cast<std::size_t>(range.second) > maximum) {

        throw std::out_of_range(
            operation + ": range " +
            std::to_string(range.first) + "-" +
            std::to_string(range.second) +
            " exceeds available data (1-" +
            std::to_string(maximum) + ")"
        );
    }
}

// Resolve and validate all ranges before processing.
std::vector<CliOptions::Range> prepareRanges(
    const std::vector<CliOptions::Range>& requested,
    std::size_t maximum,
    const std::string& operation)
{
    std::vector<CliOptions::Range> resolved;
    resolved.reserve(requested.size());

    for (const auto& range : requested) {
        const auto actual = resolveRange(range, maximum);

        validateRange(actual, maximum, operation);

        resolved.push_back(actual);
    }

    return resolved;
}

} // namespace

int CliRunner::run(const CliOptions& options) const
{
    try {
        CCfits::FITS::setVerboseMode(false);

        // Custom flagged-file handling is not yet connected
        // to the spectral_container loading layer.
        if (options.flaggedFile != "flagged_obs.dat") {
            throw std::runtime_error(
                "Custom --flagged_files is not "
                "supported by the loading layer yet"
            );
        }

        spectral_container data;

        // 1. Load observations.
        loadInput(data, options.inputFiles);

        const std::size_t nEpochs =
            data.spectraTableI.size();

        const std::size_t nChannels =
            data.spectraTableI.front().size();

        std::cout << "Loaded "
                  << nEpochs << " epochs and "
                  << nChannels << " channels.\n";

        // 2. Resolve ALL and validate every requested range.
        // No output files are written before this succeeds.
        const auto aovRanges = prepareRanges(
            options.aovOperations,
            nChannels,
            "--aov"
        );

        const auto aotRanges = prepareRanges(
            options.aotOperations,
            nEpochs,
            "--aot"
        );

        // 3. Average over velocity (channels).
        for (const auto& [first, last] : aovRanges) {

            std::cout << "AOV: channels "
                      << first << " -> " << last << '\n';

            data.averageOverVelocity4Pols(
                first,
                last,
                false
            );

            std::cout << "Output: "
                      << data.getAverOverVelFileName(
                             first, last)
                      << '\n';
        }

        // 4. Average over time (epochs).
        for (const auto& [first, last] : aotRanges) {

            std::cout << "AOT: epochs "
                      << first << " -> " << last << '\n';

            data.averOverTime4Pols(first, last);

            std::cout << "Output: "
                      << data.getAverOverTimeFileName(
                             first, last)
                      << '\n';
        }

        std::cout << "CLI processing completed.\n";

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "RT4SV++ CLI error: "
                  << e.what() << '\n';

        return 1;
    }
}
