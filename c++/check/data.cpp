#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


int Random(int l, int r) {
    return (long long)rand() * rand() % (r - l + 1) + l;
}

int n = 20;
string s;
int main() {
    srand((unsigned)time(0));
    for (int i = 1; i <= n; i++) {
        int a = Random(0, 9);
        s += (a + '0');
    }
    int n = Random(1, 10000);
    printf("%s\n%d\n", s.c_str(), n);
    return 0;
}