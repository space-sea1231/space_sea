#include <iostream>
#include <stdio.h>
#include <algorithm>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n;

struct Person {
    #ifdef __Debug
    int a, b;
    #else
    int a, b, c;
    #endif
};

Person person[N];

#ifdef __Debug
bool Cmp1(Person srca, Person srcb) {
    if (srca.a != srcb.a) return srca.a < srcb.a;
    return srca.b < srcb.b;
}
bool Cmp2(Person srca, Person srcb) {
    return srca.b < srcb.b;
}
#else
bool Cmp1(Person srca, Person srcb) {
    if (srca.a != srcb.a) return srca.a < srcb.a;
    if (srca.b != srcb.b) return srca.b < srcb.b;
    return srca.c < srcb.c;
}
bool Cmp2(Person srca, Person srcb) {
    if (srca.b != srcb.b) return srca.b < srcb.b;
    return srca.c < srcb.c;
}
#endif
int ans;

void Cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    Cdq(l, mid);
    Cdq(mid + 1, r);
    sort(person + l, person + mid + 1, Cmp2);
    sort(person + mid + 1, person + r + 1, Cmp2);
    int i = l, j = mid + 1;
    while (j <= r) {
        while (i <= mid && person[j].b < person[i].b) {
            ans = max(ans, person[j].a + person[i].b);
            i++;
        }
        j++;
    }
    return;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        #ifdef __Debug
        cin >> person[i].a >> person[i].b;
        #else
        cin >> person[i].a >> person[i].b >> person[i].c;
        #endif
    }
    sort(person + 1, person + n + 1, Cmp1);
    Cdq(1, n);
    if (!ans) printf("-1\n");
    else printf("%d\n", ans);
    return 0;
}