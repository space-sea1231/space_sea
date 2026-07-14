#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
typedef long long ll;

int t = 5;
int n;

int Random(int l, int r) {
    return (long long)rand() * rand() % (r - l + 1) + l;
}

int main() {
    srand((unsigned)time(0));
    printf("%d\n", t);
    while (t--) {
       int a = Random(1, 100);
       int b = Random(1, 100);
       int c = Random(1, 100);
        printf("%d %d %d\n", a, b, c);
    }
    return 0;
}