#include <bits/stdc++.h>
using namespace std;

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

    string readString() {
        char c = getChar();

        while (c <= ' ') {
            c = getChar();
        }

        string result;

        while (c > ' ') {
            result.push_back(c);
            c = getChar();
        }

        return result;
    }
};

class FastOutput {
private:
    static constexpr int BUFFER_SIZE = 1 << 20;
    char buffer[BUFFER_SIZE];
    int position = 0;

public:
    ~FastOutput() {
        flush();
    }

    void flush() {
        if (position > 0) {
            fwrite(buffer, 1, position, stdout);
            position = 0;
        }
    }

    void writeAnswer(bool answer) {
        if (position + 2 > BUFFER_SIZE) {
            flush();
        }

        buffer[position++] = answer ? '1' : '0';
        buffer[position++] = '\n';
    }
};

static constexpr int MAX_SPECIAL = 205;

int main() {
    FastInput input;
    FastOutput output;

    int T = input.readInt();

    while (T--) {
        int n = input.readInt();
        int m = input.readInt();
        int k = input.readInt();
        int q = input.readInt();

        vector<string> grid(n);

        for (int i = 0; i < n; ++i) {
            grid[i] = input.readString();
        }
        // cerr<<n<<" "<<m<<endl;
        int totalCells = n * m;
        vector<int> component(totalCells, -1);
        vector<int> queue(totalCells);

        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};

        int componentCount = 0;

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                int start = x * m + y;

                if (grid[x][y] == '#' ||
                    component[start] != -1) {
                    continue;
                }

                int left = 0;
                int right = 0;

                queue[right++] = start;
                component[start] = componentCount;

                while (left < right) {
                    int cell = queue[left++];
                    int currentX = cell / m;
                    int currentY = cell % m;

                    for (int direction = 0;
                         direction < 4;
                         ++direction) {
                        int nextX = currentX + dx[direction];
                        int nextY = currentY + dy[direction];

                        if (nextX < 0 || nextX >= n ||
                            nextY < 0 || nextY >= m) {
                            continue;
                        }

                        if (grid[nextX][nextY] == '#') {
                            continue;
                        }

                        int nextCell = nextX * m + nextY;

                        if (component[nextCell] != -1) {
                            continue;
                        }

                        component[nextCell] = componentCount;
                        queue[right++] = nextCell;
                    }
                }

                ++componentCount;
            }
        }

        vector<pair<int, int>> portals(k);
        vector<int> specialIndex(componentCount, -1);
        int specialCount = 0;

        auto getComponent = [&](int x, int y) {
            return component[(x - 1) * m + (y - 1)];
        };

        for (int i = 0; i < k; ++i) {
            int x1 = input.readInt();
            int y1 = input.readInt();
            int x2 = input.readInt();
            int y2 = input.readInt();

            int from = getComponent(x1, y1);
            int to = getComponent(x2, y2);

            portals[i] = {from, to};

            if (specialIndex[from] == -1) {
                specialIndex[from] = specialCount++;
            }

            if (specialIndex[to] == -1) {
                specialIndex[to] = specialCount++;
            }
        }

        vector<bitset<MAX_SPECIAL>> reachable(specialCount);

        for (int i = 0; i < specialCount; ++i) {
            reachable[i].set(i);
        }

        for (auto [from, to] : portals) {
            reachable[specialIndex[from]].set(
                specialIndex[to]
            );
        }

        for (int middle = 0;
             middle < specialCount;
             ++middle) {
            for (int from = 0;
                 from < specialCount;
                 ++from) {
                if (reachable[from].test(middle)) {
                    reachable[from] |= reachable[middle];
                }
            }
        }

        while (q--) {
            int x1 = input.readInt();
            int y1 = input.readInt();
            int x2 = input.readInt();
            int y2 = input.readInt();

            int from = getComponent(x1, y1);
            int to = getComponent(x2, y2);

            bool answer;

            if (from == to) {
                answer = true;
            } else if (specialIndex[from] == -1 ||
                       specialIndex[to] == -1) {
                answer = false;
            } else {
                answer = reachable[specialIndex[from]].test(
                    specialIndex[to]
                );
            }

            output.writeAnswer(answer);
        }
    }

    return 0;
}