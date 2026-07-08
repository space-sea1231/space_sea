#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
typedef long long ll;

int t = 1;
int n;

int Random(int l, int r) {
    return (long long)rand() * rand() % (r - l + 1) + l;
}

int main() {
    srand((unsigned)time(0));
    printf("%d\n", t);
    while (t--) {
        n = Random(1, 10);
        printf("%d\n", n);
        for (int i = 1; i <= n; i++) {
            printf("%d ", Random(1, 30));
        }
    }
    return 0;
}