#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
typedef long long ll;

int t = 1;
int n = 6;
bool vis[7];
int Random(int l, int r) {
    return (long long)rand() * rand() % (r - l + 1) + l;
}
int main() {
    srand((unsigned)time(0));
    printf("%d\n", t);
    return 0;
}