#include "../interface/cli.h"

#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
int testsRun = 0;

void check(bool condition, const char* expression, int line) {
    if (!condition) {
        throw std::runtime_error("Line " + std::to_string(line) +
                                 ": assertion failed: " + expression);
    }
}
#define CHECK(...) check((__VA_ARGS__), #__VA_ARGS__, __LINE__)

CliOptions parse(std::vector<std::string> args) {
    std::vector<char*> argv;
    argv.reserve(args.size());
    for (auto& arg : args) argv.push_back(arg.data());
    return CliParser{}.parse(static_cast<int>(argv.size()), argv.data());
}

void expectInvalid(std::vector<std::string> args) {
    bool thrown = false;
    try {
        (void)parse(std::move(args));
    } catch (const std::invalid_argument&) {
        thrown = true;
    }
    CHECK(thrown);
}

void test(const char* name, const std::function<void()>& fn) {
    fn();
    ++testsRun;
    std::cout << "[PASS] " << name << '\n';
}
} // namespace

int main() {
    try {
        test("no arguments => GUI mode", [] {
            const auto o = parse({"rt4sv++"});
            CHECK(o.inputFiles.empty());
            CHECK(!o.hasOperations());
            CHECK(!o.showHelp);
            CHECK(o.flaggedFile == "flagged_obs.dat");
        });
        test("single FITS => GUI with input", [] {
            const auto o = parse({"rt4sv++", "obs.fits"});
            CHECK(o.inputFiles == std::vector<std::string>{"obs.fits"});
            CHECK(!o.hasOperations());
        });
        test("list file as positional input", [] {
            const auto o = parse({"rt4sv++", "observations.lst", "--aot", "1", "10"});
            CHECK(o.inputFiles == std::vector<std::string>{"observations.lst"});
            CHECK(o.aotOperations == std::vector<CliOptions::Range>{{1, 10}});
        });
        test("many positional inputs (shell-expanded glob)", [] {
            const auto o = parse({"rt4sv++", "a.fits", "b.fits", "c.fits", "--aov", "400", "800"});
            CHECK(o.inputFiles == (std::vector<std::string>{"a.fits", "b.fits", "c.fits"}));
            CHECK(o.aovOperations == std::vector<CliOptions::Range>{{400, 800}});
        });
        test("--input accepts multiple paths until next option", [] {
            const auto o = parse({"rt4sv++", "--input", "a.fits", "b.fits", "--aov", "2", "8"});
            CHECK(o.inputFiles == (std::vector<std::string>{"a.fits", "b.fits"}));
            CHECK(o.aovOperations == std::vector<CliOptions::Range>{{2, 8}});
        });
        test("--input and positional inputs can be mixed", [] {
            const auto o = parse({"rt4sv++", "one.fits", "--input", "two.fits", "three.fits", "--aot", "1", "2", "four.fits"});
            CHECK(o.inputFiles == (std::vector<std::string>{"one.fits", "two.fits", "three.fits", "four.fits"}));
        });
        test("repeat --input and operations", [] {
            const auto o = parse({"rt4sv++", "--input", "a.fits", "--aov", "1", "10", "--input", "b.fits", "--aov", "20", "30", "--aot", "1", "2"});
            CHECK(o.inputFiles == (std::vector<std::string>{"a.fits", "b.fits"}));
            CHECK(o.aovOperations == (std::vector<CliOptions::Range>{{1, 10}, {20, 30}}));
            CHECK(o.aotOperations == std::vector<CliOptions::Range>{{1, 2}});
        });
        test("--flagged_files anywhere", [] {
            const auto o = parse({"rt4sv++", "--aov", "1", "3", "--flagged_files", "bad.dat", "--input", "a.fits"});
            CHECK(o.flaggedFile == "bad.dat");
            CHECK(o.inputFiles == std::vector<std::string>{"a.fits"});
        });
        test("help takes priority", [] {
            const auto o = parse({"rt4sv++", "--garbage", "--help"});
            CHECK(o.showHelp);
        });
        test("inclusive singleton range", [] {
            const auto o = parse({"rt4sv++", "a.fits", "--aot", "9", "9"});
            CHECK(o.aotOperations[0] == CliOptions::Range(9, 9));
        });
        test("error: no input for operation", [] {
            expectInvalid({"rt4sv++", "--aov", "1", "2"});
        });
        test("error: --input without path", [] {
            expectInvalid({"rt4sv++", "--input"});
            expectInvalid({"rt4sv++", "--input", "--aot", "1", "2"});
        });
        test("error: missing flag file", [] {
            expectInvalid({"rt4sv++", "a.fits", "--flagged_files"});
            expectInvalid({"rt4sv++", "a.fits", "--flagged_files", "--aov", "1", "2"});
        });
        test("error: unknown options", [] {
            expectInvalid({"rt4sv++", "a.fits", "--not-real"});
            expectInvalid({"rt4sv++", "a.fits", "-x"});
        });
        test("error: quoted globs", [] {
            expectInvalid({"rt4sv++", "*.fits"});
            expectInvalid({"rt4sv++", "--input", "obs?.fits"});
            expectInvalid({"rt4sv++", "--input", "x[12].fits"});
        });
        test("error: invalid integers", [] {
            expectInvalid({"rt4sv++", "a.fits", "--aov", "foo", "2"});
            expectInvalid({"rt4sv++", "a.fits", "--aov", "1.5", "2"});
            expectInvalid({"rt4sv++", "a.fits", "--aov", "1x", "2"});
            expectInvalid({"rt4sv++", "a.fits", "--aov", "999999999999999999999999", "2"});
        });
        test("error: missing range operands", [] {
            expectInvalid({"rt4sv++", "a.fits", "--aot"});
            expectInvalid({"rt4sv++", "a.fits", "--aot", "1"});
            expectInvalid({"rt4sv++", "a.fits", "--aot", "1", "--aov", "2", "3"});
        });
        test("error: invalid range order or zero", [] {
            expectInvalid({"rt4sv++", "a.fits", "--aov", "0", "10"});
            expectInvalid({"rt4sv++", "a.fits", "--aov", "10", "9"});
            expectInvalid({"rt4sv++", "a.fits", "--aot", "-1", "10"});
        });
        test("error: empty filename", [] {
            expectInvalid({"rt4sv++", ""});
            expectInvalid({"rt4sv++", "--input", ""});
        });
        std::cout << "\nAll " << testsRun << " parser tests passed.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[FAIL] " << e.what() << '\n';
        return 1;
    }
}
