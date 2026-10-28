#include <cstdint>
#include <cstdio>
#include <vector>

namespace {
constexpr int MOD = 998244353;

class FastInput {
    static constexpr int SIZE = 1 << 16;
    char buffer[SIZE];
    int position = 0, length = 0;

    int get() {
        if (position == length) {
            length = static_cast<int>(std::fread(buffer, 1, SIZE, stdin));
            position = 0;
            if (length == 0) return EOF;
        }
        return static_cast<unsigned char>(buffer[position++]);
    }

public:
    bool read(int& value) {
        int c;
        do {
            c = get();
            if (c == EOF) return false;
        } while (c <= ' ');
        value = 0;
        do {
            value = value * 10 + c - '0';
            c = get();
        } while (c >= '0' && c <= '9');
        return true;
    }
};

class FastOutput {
    static constexpr int SIZE = 1 << 16;
    char buffer[SIZE];
    int position = 0;

public:
    ~FastOutput() { flush(); }

    void flush() {
        if (position != 0) std::fwrite(buffer, 1, position, stdout);
        position = 0;
    }

    void write(int value) {
        if (position + 16 >= SIZE) flush();
        char digits[12];
        int count = 0;
        do {
            digits[count++] = static_cast<char>('0' + value % 10);
            value /= 10;
        } while (value != 0);
        while (count != 0) buffer[position++] = digits[--count];
        buffer[position++] = '\n';
    }
};
}  // namespace

int main() {
	freopen("assign.in","r",stdin);
	freopen("assign.out","w",stdout);
    FastInput input;
    FastOutput output;
    int subtask, tests;
    if (!input.read(subtask) || !input.read(tests)) return 0;
    (void)subtask;

    std::vector<int> power2(1, 1);
    std::vector<int> head, to, next, queue;
    std::vector<std::int8_t> color;

    while (tests--) {
        int n, m;
        input.read(n);
        input.read(m);
        if (m == 0) {
            // Every vertex is isolated and must have value zero.
            output.write(1);
            continue;
        }
        while (static_cast<int>(power2.size()) <= n) {
            power2.push_back(static_cast<int>(2LL * power2.back() % MOD));
        }
        head.assign(n, -1);
        color.assign(n, -1);
        to.resize(2 * m);
        next.resize(2 * m);
        queue.resize(n);
        int edgeCount = 0;
        auto addEdge = [&](int u, int v) {
            to[edgeCount] = v;
            next[edgeCount] = head[u];
            head[u] = edgeCount++;
        };
        for (int i = 0; i < m; ++i) {
            int u, v;
            input.read(u);
            input.read(v);
            --u;
            --v;
            addEdge(u, v);
            addEdge(v, u);
        }

        int answer = 1;
        bool bipartite = true;
        for (int start = 0; start < n && bipartite; ++start) {
            if (color[start] != -1) continue;
            int counts[2] = {1, 0};
            int front = 0, back = 0;
            color[start] = 0;
            queue[back++] = start;
            while (front < back && bipartite) {
                int u = queue[front++];
                for (int e = head[u]; e != -1; e = next[e]) {
                    int v = to[e];
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        ++counts[color[v]];
                        queue[back++] = v;
                    } else if (color[v] == color[u]) {
                        bipartite = false;
                        break;
                    }
                }
            }
            // The zero vertices form a nonempty subset of exactly one side.
            int ways = power2[counts[0]] + power2[counts[1]] - 2;
            if (ways >= MOD) ways -= MOD;
            answer = static_cast<int>(1LL * answer * ways % MOD);
        }
        output.write(bipartite ? answer : 0);
    }
    return 0;
}
