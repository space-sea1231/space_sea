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
        if (position != 0) {
            fwrite(buffer, 1, position, stdout);
            position = 0;
        }
    }

    void putChar(char c) {
        if (position == BUFFER_SIZE) {
            flush();
        }

        buffer[position++] = c;
    }

    void writeInt(int value, char ending) {
        char digits[16];
        int length = 0;

        do {
            digits[length++] =
                static_cast<char>('0' + value % 10);
            value /= 10;
        } while (value != 0);

        while (length != 0) {
            putChar(digits[--length]);
        }

        putChar(ending);
    }
};

class Solver {
private:
    static constexpr int TYPE_COUNT = 20;
    static constexpr int INF = 1000000000;

    int n;
    int queryCount;

    vector<int> type;
    array<vector<int>, TYPE_COUNT + 1> positions;

    vector<int> previousSame;
    vector<int> nextSame;

    vector<int> queryLeft;
    vector<int> queryRight;
    vector<int> answer;

    vector<int> distanceValue;
    vector<unsigned char> visited;

    void runDijkstra(int source, int left, int right) {
        for (int i = left; i <= right; ++i) {
            distanceValue[i] = INF;
            visited[i] = 0;
        }

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > queue;

        distanceValue[source] = 0;
        queue.emplace(0, source);

        while (!queue.empty()) {
            auto [currentDistance, vertex] = queue.top();
            queue.pop();

            if (visited[vertex]) {
                continue;
            }

            visited[vertex] = 1;

            auto relax = [&](int nextVertex, int edgeWeight) {
                if (nextVertex < left || nextVertex > right) {
                    return;
                }

                int newDistance = currentDistance + edgeWeight;

                if (newDistance < distanceValue[nextVertex]) {
                    distanceValue[nextVertex] = newDistance;
                    queue.emplace(newDistance, nextVertex);
                }
            };

            if (vertex > left) {
                relax(vertex - 1, 2);
            }

            if (vertex < right) {
                relax(vertex + 1, 2);
            }

            if (previousSame[vertex] != 0) {
                relax(
                    previousSame[vertex],
                    vertex - previousSame[vertex]
                );
            }

            if (nextSame[vertex] != 0) {
                relax(
                    nextSame[vertex],
                    nextSame[vertex] - vertex
                );
            }
        }
    }

    void divideAndConquer(
        int left,
        int right,
        vector<int> &queries
    ) {
        if (queries.empty()) {
            return;
        }

        int middle = (left + right) >> 1;

        vector<int> leftQueries;
        vector<int> rightQueries;
        vector<int> middleQueries;

        leftQueries.reserve(queries.size() / 2);
        rightQueries.reserve(queries.size() / 2);
        middleQueries.reserve(queries.size());

        for (int id : queries) {
            if (queryLeft[id] > middle) {
                rightQueries.push_back(id);
            } else if (queryRight[id] < middle) {
                leftQueries.push_back(id);
            } else {
                middleQueries.push_back(id);
            }
        }

        if (!middleQueries.empty()) {
            int width = right - left + 1;
            int dijkstraLeft = max(1, left - width - 1);
            int dijkstraRight = min(n, right + width + 1);

            for (int value = 1; value <= TYPE_COUNT; ++value) {
                const vector<int> &list = positions[value];

                auto iterator =
                    lower_bound(list.begin(), list.end(), middle);

                if (iterator == list.end()) {
                    continue;
                }

                int source = *iterator;

                if (source < dijkstraLeft ||
                    source > dijkstraRight) {
                    continue;
                }

                runDijkstra(
                    source,
                    dijkstraLeft,
                    dijkstraRight
                );

                for (int id : middleQueries) {
                    int candidate =
                        distanceValue[queryLeft[id]] +
                        distanceValue[queryRight[id]];

                    answer[id] = min(answer[id], candidate);
                }
            }
        }

        if (!leftQueries.empty()) {
            divideAndConquer(
                left,
                middle - 1,
                leftQueries
            );
        }

        if (!rightQueries.empty()) {
            divideAndConquer(
                middle + 1,
                right,
                rightQueries
            );
        }
    }

public:
    Solver(int vertexCount, int numberOfQueries)
        : n(vertexCount),
          queryCount(numberOfQueries),
          type(n + 1),
          previousSame(n + 1),
          nextSame(n + 1),
          queryLeft(queryCount),
          queryRight(queryCount),
          answer(queryCount),
          distanceValue(n + 1),
          visited(n + 1) {}

    void read(FastInput &input) {
        for (int i = 1; i <= n; ++i) {
            type[i] = input.readInt();
            positions[type[i]].push_back(i);
        }

        for (int value = 1; value <= TYPE_COUNT; ++value) {
            const vector<int> &list = positions[value];

            for (int i = 1;
                 i < static_cast<int>(list.size());
                 ++i) {
                int x = list[i - 1];
                int y = list[i];

                nextSame[x] = y;
                previousSame[y] = x;
            }
        }

        for (int id = 0; id < queryCount; ++id) {
            int x = input.readInt();
            int y = input.readInt();

            if (x > y) {
                swap(x, y);
            }

            queryLeft[id] = x;
            queryRight[id] = y;
            answer[id] = 2 * (y - x);
        }
    }

    void solve() {
        vector<int> allQueries(queryCount);
        iota(allQueries.begin(), allQueries.end(), 0);

        divideAndConquer(1, n, allQueries);
    }

    void writeAnswers(FastOutput &output) const {
        for (int i = 0; i < queryCount; ++i) {
            output.writeInt(
                answer[i],
                i + 1 == queryCount ? '\n' : ' '
            );
        }
    }
};

int main() {
    FastInput input;
    FastOutput output;

    int T = input.readInt();

    while (T--) {
        int n = input.readInt();
        int q = input.readInt();

        Solver solver(n, q);
        solver.read(input);
        solver.solve();
        solver.writeAnswers(output);
    }

    return 0;
}
