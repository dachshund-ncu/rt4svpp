#ifndef RT4SVPP_CLI_RUNNER_H
#define RT4SVPP_CLI_RUNNER_H

#include "cli.h"

class CliRunner {
public:
    // Returns 0 on success, non-zero on failure.
    int run(const CliOptions& options) const;
};

#endif
