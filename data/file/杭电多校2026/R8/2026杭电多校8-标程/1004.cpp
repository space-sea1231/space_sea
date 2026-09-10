#include <bits/stdc++.h>
using namespace std;

class FastInput {
private:
    static constexpr int SIZE = 1 << 20;
    char buffer[SIZE];
    int position = 0;
    int length = 0;

    char getChar() {
        if (position == length) {
            length = fread(buffer, 1, SIZE, stdin);
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

static constexpr int HASH_MOD = 10000019;

static int hashHead[HASH_MOD];
static bitset<HASH_MOD> hashTouched;
static vector<int> touchedBuckets;

static uint64_t makeKey(int u, int v) {
    if (u > v) {
        swap(u, v);
    }

    return
        (static_cast<uint64_t>(static_cast<uint32_t>(u)) << 32) |
        static_cast<uint32_t>(v);
}

static uint64_t xorshift(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

static int getBucket(uint64_t key) {
    return static_cast<int>(xorshift(key) % HASH_MOD);
}

static void clearHashTable() {
    for (int bucket : touchedBuckets) {
        hashHead[bucket] = 0;
        hashTouched[bucket] = false;
    }
    touchedBuckets.clear();
}

class Solver {
private:
    struct Relation {
        int endpoint[2];
        int next[2];
        int previous[2];
        int hashNext;
        unsigned char mask;
        bool alive;
    };

    int n;
    int components;

    vector<int> head;
    vector<int> componentSize;
    vector<Relation> relations;

    vector<int> commonQueue;
    int queuePosition = 0;

    int endpointSlot(int id, int vertex) const {
        return relations[id].endpoint[0] == vertex ? 0 : 1;
    }

    int otherEndpoint(int id, int vertex) const {
        const Relation &edge = relations[id];

        if (edge.endpoint[0] == vertex) {
            return edge.endpoint[1];
        }
        return edge.endpoint[0];
    }

    void touchBucket(int bucket) {
        if (!hashTouched[bucket]) {
            hashTouched[bucket] = true;
            touchedBuckets.push_back(bucket);
        }
    }

    int findRelation(int u, int v) const {
        uint64_t key = makeKey(u, v);
        int bucket = getBucket(key);

        for (int current = hashHead[bucket];
             current != 0;
             current = relations[current - 1].hashNext) {
            int id = current - 1;
            const Relation &edge = relations[id];

            if (makeKey(
                    edge.endpoint[0],
                    edge.endpoint[1]
                ) == key) {
                return id;
            }
        }

        return -1;
    }

    void insertHash(int id) {
        Relation &edge = relations[id];

        int bucket = getBucket(
            makeKey(edge.endpoint[0], edge.endpoint[1])
        );

        touchBucket(bucket);

        edge.hashNext = hashHead[bucket];
        hashHead[bucket] = id + 1;
    }

    void eraseHash(int id) {
        Relation &edge = relations[id];

        int bucket = getBucket(
            makeKey(edge.endpoint[0], edge.endpoint[1])
        );

        int *current = &hashHead[bucket];

        while (*current != 0) {
            int currentId = *current - 1;

            if (currentId == id) {
                *current = relations[currentId].hashNext;
                edge.hashNext = 0;
                return;
            }

            current = &relations[currentId].hashNext;
        }
    }

    void linkEndpoint(int id, int slot) {
        Relation &edge = relations[id];
        int vertex = edge.endpoint[slot];

        edge.previous[slot] = -1;
        edge.next[slot] = head[vertex];

        if (head[vertex] != -1) {
            int first = head[vertex];
            int firstSlot = endpointSlot(first, vertex);
            relations[first].previous[firstSlot] = id;
        }

        head[vertex] = id;
    }

    void unlinkEndpoint(int id, int slot) {
        Relation &edge = relations[id];

        int vertex = edge.endpoint[slot];
        int previous = edge.previous[slot];
        int next = edge.next[slot];

        if (previous == -1) {
            head[vertex] = next;
        } else {
            int previousSlot = endpointSlot(previous, vertex);
            relations[previous].next[previousSlot] = next;
        }

        if (next != -1) {
            int nextSlot = endpointSlot(next, vertex);
            relations[next].previous[nextSlot] = previous;
        }

        edge.previous[slot] = -1;
        edge.next[slot] = -1;
    }

    int createRelation(
        int u,
        int v,
        unsigned char mask
    ) {
        int id = static_cast<int>(relations.size());

        Relation edge;
        edge.endpoint[0] = u;
        edge.endpoint[1] = v;
        edge.next[0] = edge.next[1] = -1;
        edge.previous[0] = edge.previous[1] = -1;
        edge.hashNext = 0;
        edge.mask = mask;
        edge.alive = true;

        relations.push_back(edge);

        linkEndpoint(id, 0);
        linkEndpoint(id, 1);
        insertHash(id);

        if (mask == 3) {
            commonQueue.push_back(id);
        }

        return id;
    }

    void addInitialEdge(
        int u,
        int v,
        unsigned char mask
    ) {
        int id = findRelation(u, v);

        if (id == -1) {
            createRelation(u, v, mask);
            return;
        }

        unsigned char oldMask = relations[id].mask;
        relations[id].mask |= mask;

        if (oldMask != 3 && relations[id].mask == 3) {
            commonQueue.push_back(id);
        }
    }

    void removeRelation(int id) {
        Relation &edge = relations[id];

        eraseHash(id);
        unlinkEndpoint(id, 0);
        unlinkEndpoint(id, 1);

        edge.alive = false;
    }

    void retargetRelation(
        int id,
        int oldVertex,
        int newVertex
    ) {
        Relation &edge = relations[id];

        eraseHash(id);

        int slot = endpointSlot(id, oldVertex);
        unlinkEndpoint(id, slot);

        edge.endpoint[slot] = newVertex;

        linkEndpoint(id, slot);
        insertHash(id);
    }

    void mergeRelations(
        int movingId,
        int existingId
    ) {
        Relation &moving = relations[movingId];
        Relation &existing = relations[existingId];

        unsigned char oldMask = existing.mask;
        existing.mask |= moving.mask;

        eraseHash(movingId);
        unlinkEndpoint(movingId, 0);
        unlinkEndpoint(movingId, 1);

        moving.alive = false;

        if (oldMask != 3 && existing.mask == 3) {
            commonQueue.push_back(existingId);
        }
    }

    int getCommonRelation() {
        while (queuePosition <
               static_cast<int>(commonQueue.size())) {
            int id = commonQueue[queuePosition++];

            if (relations[id].alive &&
                relations[id].mask == 3) {
                return id;
            }
        }

        return -1;
    }

    void contractRelation(int id) {
        int x = relations[id].endpoint[0];
        int y = relations[id].endpoint[1];

        if (componentSize[x] < componentSize[y]) {
            swap(x, y);
        }

        removeRelation(id);

        while (head[y] != -1) {
            int movingId = head[y];
            int neighbor = otherEndpoint(movingId, y);

            int existingId = findRelation(x, neighbor);

            if (existingId == -1) {
                retargetRelation(movingId, y, x);
            } else {
                mergeRelations(movingId, existingId);
            }
        }

        componentSize[x] += componentSize[y];
        componentSize[y] = 0;
        --components;
    }

public:
    explicit Solver(int vertexCount)
        : n(vertexCount),
          components(vertexCount),
          head(n + 1, -1),
          componentSize(n + 1, 1) {
        relations.reserve(max(0, 2 * n - 2));
        commonQueue.reserve(max(0, 2 * n - 2));
    }

    void readInput(FastInput &input) {
        for (int i = 1; i < n; ++i) {
            int u = input.readInt();
            int v = input.readInt();
            addInitialEdge(u, v, 1);
        }

        for (int i = 1; i < n; ++i) {
            int u = input.readInt();
            int v = input.readInt();
            addInitialEdge(u, v, 2);
        }
    }

    bool solve() {
        while (components > 1) {
            int id = getCommonRelation();

            if (id == -1) {
                return false;
            }

            contractRelation(id);
        }

        return true;
    }
};

int main() {
    FastInput input;

    int T = input.readInt();

    string output;
    output.reserve(static_cast<size_t>(T) * 4);

    touchedBuckets.reserve(1500000);

    while (T--) {
        int n = input.readInt();

        {
            Solver solver(n);
            solver.readInput(input);

            if (solver.solve()) {
                output += "YES\n";
            } else {
                output += "NO\n";
            }
        }

        clearHashTable();
    }

    fwrite(output.data(), 1, output.size(), stdout);
    return 0;
}

