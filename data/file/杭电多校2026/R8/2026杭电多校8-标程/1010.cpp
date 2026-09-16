#include <bits/stdc++.h>
using namespace std;

static constexpr int MOD = 998244353;
static constexpr int MAX_N = 200000;
static constexpr int INV_TWO = (MOD + 1) / 2;

class FastInput {
private:
    static constexpr int BUFFER_SIZE = 1 << 20;
    char buffer[BUFFER_SIZE];
    int position = 0;
    int length = 0;

    char getChar() {
        if (position == length) {
            length = static_cast<int>(
                fread(buffer, 1, BUFFER_SIZE, stdin)
            );
            position = 0;

            if (length == 0) {
                return 0;
            }
        }

        return buffer[position++];
    }

public:
    int readInt() {
        char c = getChar();

        while (c < '0' || c > '9') {
            c = getChar();
        }

        int value = 0;

        while (c >= '0' && c <= '9') {
            value = value * 10 + c - '0';
            c = getChar();
        }

        return value;
    }
};

int main() {
    static int powerOfThree[MAX_N + 1];

    powerOfThree[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        powerOfThree[i] = static_cast<int>(
            3LL * powerOfThree[i - 1] % MOD
        );
    }

    FastInput input;
    int T = input.readInt();

    string output;
    output.reserve(static_cast<size_t>(T) * 12);

    while (T--) {
        int n = input.readInt();

        int count[3] = {1, 0, 0};
        int nextCountAtLast[3] = {0, 0, 0};
        int prefixRemainder = 0;
        int answer = 0;

        for (int right = 1; right <= n; ++right) {
            int value = input.readInt();
            prefixRemainder =
                (prefixRemainder + value) % 3;

            int remainder = prefixRemainder;

            // Left endpoint remainder s with remainder - s = 1.
            int firstState = (remainder + 2) % 3;
            int firstCount = count[firstState];

            int firstGeometric = static_cast<int>(
                1LL *
                (powerOfThree[firstCount] - 1 + MOD) %
                MOD *
                INV_TWO %
                MOD
            );

            answer += firstGeometric;
            if (answer >= MOD) {
                answer -= MOD;
            }

            // Left endpoint remainder s with remainder - s = 2.
            int secondState = (remainder + 1) % 3;
            int middleState = (secondState + 1) % 3;
            int secondCount = count[secondState];

            int secondGeometric = static_cast<int>(
                1LL *
                (powerOfThree[secondCount] - 1 + MOD) %
                MOD *
                INV_TWO %
                MOD
            );

            int middleCount =
                count[middleState] -
                nextCountAtLast[secondState];

            int factor =
                powerOfThree[middleCount] + 1;

            if (factor >= MOD) {
                factor -= MOD;
            }

            answer = static_cast<int>(
                (
                    answer +
                    1LL * secondGeometric * factor
                ) % MOD
            );

            ++count[remainder];
            nextCountAtLast[remainder] =
                count[(remainder + 1) % 3];
        }

        output += to_string(answer);
        output.push_back('\n');
    }

    fwrite(output.data(), 1, output.size(), stdout);
    return 0;
}
