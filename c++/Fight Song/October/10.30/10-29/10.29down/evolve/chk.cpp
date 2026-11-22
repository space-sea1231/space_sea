#include "testlib.h"

#include <string>
#include <unordered_map>
#include <vector>

struct InputData {
    int n;
    std::string universe;
    std::vector<std::string> strings;
    std::unordered_map<std::string, int> id;
};

struct OutputData {
    bool impossible = false;
    int count[2] = {0, 0};
    std::vector<std::string> chain[2];
};

static int parseCount(const std::string& token, int n, InStream& stream, bool jurySide) {
    if (token.empty()) stream.quitf(jurySide ? _fail : _wa, "empty chain size");
    long long value = 0;
    for (char ch : token) {
        if (ch < '0' || ch > '9') {
            stream.quitf(jurySide ? _fail : _wa, "invalid chain size '%s'", compress(token).c_str());
        }
        value = value * 10 + (ch - '0');
        if (value > n) stream.quitf(jurySide ? _fail : _wa, "chain size exceeds n");
    }
    return static_cast<int>(value);
}

static std::string parseChainString(InStream& stream, bool jurySide,
                                    int side, int position) {
    const std::string token = stream.readToken();
    const TResult verdict = jurySide ? _fail : _wa;
    if (token.empty() || token.size() > 5000) {
        stream.quitf(verdict, "chain[%d][%d] has invalid length", side, position);
    }
    for (char ch : token) {
        if (ch != 'A' && ch != 'C' && ch != 'M') {
            stream.quitf(verdict, "chain[%d][%d] contains an invalid character",
                         side, position);
        }
    }
    return token;
}

static InputData readInput() {
    InputData input;
    input.n = inf.readInt();
    input.universe = inf.readToken();
    input.strings.resize(input.n);
    input.id.reserve(static_cast<size_t>(input.n) * 2 + 3);
    for (int i = 0; i < input.n; ++i) {
        input.strings[i] = inf.readToken();
        input.id.emplace(input.strings[i], i);
    }
    return input;
}

static OutputData readOutput(InStream& stream, const InputData& input, bool jurySide) {
    OutputData output;
    const std::string first = stream.readToken();
    if (first == "impossible") {
        output.impossible = true;
        if (!stream.seekEof()) stream.quitf(jurySide ? _fail : _pe, "extra tokens after impossible");
        return output;
    }

    output.count[0] = parseCount(first, input.n, stream, jurySide);
    output.count[1] = parseCount(stream.readToken(), input.n, stream, jurySide);
    for (int side = 0; side < 2; ++side) {
        output.chain[side].reserve(output.count[side]);
        for (int i = 0; i < output.count[side]; ++i) {
            output.chain[side].push_back(parseChainString(stream, jurySide, side + 1, i + 1));
        }
    }
    if (!stream.seekEof()) stream.quitf(jurySide ? _fail : _pe, "extra tokens after the two chains");
    return output;
}

static bool isSubsequence(const std::string& small, const std::string& large) {
    size_t at = 0;
    for (char ch : large) if (at < small.size() && small[at] == ch) ++at;
    return at == small.size();
}

static void validateWitness(const InputData& input, const OutputData& output,
                            InStream& stream, bool jurySide) {
    const TResult verdict = jurySide ? _fail : _wa;
    if (output.count[0] + output.count[1] != input.n) {
        stream.quitf(verdict, "chain sizes sum to %d instead of n=%d",
                     output.count[0] + output.count[1], input.n);
    }

    std::vector<unsigned char> seen(input.n, 0);
    for (int side = 0; side < 2; ++side) {
        const auto& chain = output.chain[side];
        for (int i = 0; i < static_cast<int>(chain.size()); ++i) {
            auto found = input.id.find(chain[i]);
            if (found == input.id.end()) {
                stream.quitf(verdict, "chain %d contains a string absent from the input", side + 1);
            }
            if (seen[found->second]) {
                stream.quitf(verdict, "input string '%s' is printed more than once",
                             compress(chain[i]).c_str());
            }
            seen[found->second] = 1;
            if (i > 0 && !isSubsequence(chain[i - 1], chain[i])) {
                stream.quitf(verdict, "chain %d breaks the subsequence order at position %d",
                             side + 1, i + 1);
            }
        }
        if (!chain.empty() && !isSubsequence(chain.back(), input.universe)) {
            stream.quitf(verdict, "the last string of chain %d is not a subsequence of U", side + 1);
        }
    }
    for (int i = 0; i < input.n; ++i) {
        if (!seen[i]) stream.quitf(verdict, "input string %d is missing from both chains", i + 1);
    }
}

int main(int argc, char* argv[]) {
    setName("evolve witness checker (linear hash lookup)");
    registerTestlibCmd(argc, argv);

    const InputData input = readInput();
    const OutputData jury = readOutput(ans, input, true);
    if (!jury.impossible) validateWitness(input, jury, ans, true);

    const OutputData participant = readOutput(ouf, input, false);
    if (participant.impossible) {
        if (!jury.impossible) quitf(_wa, "a valid partition exists");
        quitf(_ok, "both outputs report impossible");
    }

    validateWitness(input, participant, ouf, false);
    if (jury.impossible) quitf(_fail, "participant found a valid partition but jury reports impossible");
    quitf(_ok, "valid partition into chains of sizes %d and %d",
          participant.count[0], participant.count[1]);
}
