#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e3 + 10;

int n;

struct Person {
    int t;
    int id;

    bool operator < (const Person src)const {
        if (t == src.t) return id < src.id;
        return t < src.t;
    }
};

Person person[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> person[i].t;
        person[i].id = i;
    }
    sort(person + 1, person + n + 1);
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        person[i].t += person[i - 1].t;
        if (i != n) ans += person[i].t;
        printf("%d ", person[i].id);
    } 
    printf("\n");
    printf("%.2lf\n", ans / n);

    return 0;
}