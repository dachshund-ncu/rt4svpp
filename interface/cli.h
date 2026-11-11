#ifndef RT4SVPP_CLI_H
#define RT4SVPP_CLI_H

#include <string>
#include <utility>
#include <vector>

struct CliOptions {
    using Range = std::pair<int, int>;

    std::vector<std::string> inputFiles;
    std::string flaggedFile = "flagged_obs.dat";
    std::vector<Range> aovOperations;
    std::vector<Range> aotOperations;
    bool showHelp = false;

    bool hasOperations() const noexcept {
        return !aovOperations.empty() || !aotOperations.empty();
    }
};

class CliParser {
public:
    CliOptions parse(int argc, char* argv[]) const;
    static void printHelp(const std::string& programName);

private:
    static int parseInteger(const std::string& value);
    static CliOptions::Range parseRange(const std::string& start,
                                        const std::string& end);
    static bool isOption(const std::string& argument);
    static void addInput(CliOptions& options, const std::string& path);
    static void validate(const CliOptions& options);
};

#endif // RT4SVPP_CLI_H
