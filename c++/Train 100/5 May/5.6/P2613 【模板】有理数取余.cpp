#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e4 + 10;
const int Mod = 19260817;

char sa[N], sb[N];
int suma[N], sumb[N];

int Mol(int *sum, int len) {
    ll rev = 0;
    for (int i = 1; i <= len; i++) rev = (rev * 10 + sum[i]) % Mod;
    return rev;
}

int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = ((ll)sum * a) % Mod;
        a = ((ll)a * a) % Mod;
        b >>= 1;
    }
    return sum;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> sa >> sb;
    int lena = strlen(sa), lenb = strlen(sb);
    for (int i = 0; i < lena; i++) suma[i + 1] = sa[i] - '0';
    for (int i = 0; i < lenb; i++) sumb[i + 1] = sb[i] - '0';
    int a = Mol(suma, lena);
    int b = Mol(sumb, lenb);
    if (b == 0) {
        printf("Angry!\n");
        return 0;
    }
    printf("%d\n", ((ll)a * Pow(b, Mod - 2) + Mod) % Mod);
    return 0;
}