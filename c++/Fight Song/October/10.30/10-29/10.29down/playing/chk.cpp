#include "testlib.h"

#include <deque>
#include <string>
#include <vector>

struct TestCase {
    int n;
    std::vector<int> blocks;
};

static std::vector<TestCase> readInput() {
    const int testCount = inf.readInt();
    std::vector<TestCase> tests(testCount);
    for (int tc = 0; tc < testCount; ++tc) {
        tests[tc].n = inf.readInt();
        tests[tc].blocks.resize(tests[tc].n);
        for (int& x : tests[tc].blocks) x = inf.readInt();
    }
    return tests;
}

static bool validWitness(const TestCase& test, const std::string& witness) {
    if (static_cast<int>(witness.size()) != test.n) return false;
    std::deque<int> current;
    for (int i = 0; i < test.n; ++i) {
        const char side = witness[i];
        if (side != 'l' && side != 'r') return false;
        if (side == 'l') {
            current.push_front(test.blocks[i]);
            while (current.size() >= 2 && current[0] == current[1]) {
                const int merged = current[0] * 2;
                current.pop_front();
                current.pop_front();
                current.push_front(merged);
            }
        } else {
            current.push_back(test.blocks[i]);
            while (current.size() >= 2 && current[current.size() - 1] == current[current.size() - 2]) {
                const int merged = current.back() * 2;
                current.pop_back();
                current.pop_back();
                current.push_back(merged);
            }
        }
    }
    return current.size() == 1;
}

int main(int argc, char* argv[]) {
    setName("playing semantic checker (linear end-merge simulation)");
    registerTestlibCmd(argc, argv);

    const std::vector<TestCase> tests = readInput();
    std::vector<std::string> jury(tests.size());
    for (size_t tc = 0; tc < tests.size(); ++tc) {
        jury[tc] = ans.readToken();
        if (jury[tc] != "no" && !validWitness(tests[tc], jury[tc])) {
            quitf(_fail, "jury output for case %d is not a legal witness", static_cast<int>(tc + 1));
        }
    }
    if (!ans.seekEof()) quitf(_fail, "extra tokens in jury output");

    for (size_t tc = 0; tc < tests.size(); ++tc) {
        const std::string participant = ouf.readToken();
        if (participant == "no") {
            if (jury[tc] != "no") {
                quitf(_wa, "case %d is feasible, but participant printed no", static_cast<int>(tc + 1));
            }
            continue;
        }
        if (!validWitness(tests[tc], participant)) {
            quitf(_wa, "case %d contains an invalid placement witness", static_cast<int>(tc + 1));
        }
        if (jury[tc] == "no") {
            quitf(_fail, "case %d has a valid participant witness but jury says no", static_cast<int>(tc + 1));
        }
    }
    if (!ouf.seekEof()) quitf(_wa, "extra tokens in participant output");
    quitf(_ok, "%d cases checked", static_cast<int>(tests.size()));
}
