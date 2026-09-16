#include <bits/stdc++.h>
using namespace std;

using uint64 = unsigned long long;
using int64 = long long;

static constexpr int MOD = 998244353;

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

static uint64 makeKey(int u, int v) {
    if (u > v) {
        swap(u, v);
    }

    return
        (static_cast<uint64>(
            static_cast<unsigned int>(u)
        ) << 32) |
        static_cast<unsigned int>(v);
}

int main() {
    FastInput input;

    int T = input.readInt();

    string output;
    output.reserve(static_cast<size_t>(T) * 12);

    while (T--) {
        int n = input.readInt();
        int m = input.readInt();
        int k = input.readInt();

        vector<uint64> edges;

        if (k == 2) {
            edges.reserve(m);
        }

        for (int i = 0; i < m; ++i) {
            int u = input.readInt();
            int v = input.readInt();

            if (k == 2) {
                edges.push_back(makeKey(u, v));
            }
        }

        int answer = 0;

        if (k == 2) {
            sort(edges.begin(), edges.end());

            for (int left = 0; left < m;) {
                int right = left + 1;

                while (right < m &&
                       edges[right] == edges[left]) {
                    ++right;
                }

                int64 count = right - left;
                int64 contribution =
                    count * (count - 1) / 2;

                answer = static_cast<int>(
                    (answer + contribution) % MOD
                );

                left = right;
            }
        }

        output += to_string(answer);
        output.push_back('\n');
    }

    fwrite(output.data(), 1, output.size(), stdout);
    return 0;
}