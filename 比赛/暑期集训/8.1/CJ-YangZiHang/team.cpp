#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <unordered_map>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n;

struct Person {
    // #ifdef __Debug
    // int a, b;
    // #else
    int a, b, c;
    bool flag;
    // #endif
};

Person person[N];

bool Cmp1(Person a, Person b) {
    if (a.a != b.a) return a.a < b.a;
    if (a.b != b.b) return a.b < b.b;
    return a.c < b.c;
}
bool Cmp2(Person a, Person b) {
    if (a.b != b.b) return a.b < b.b;
    if (a.a != b.a) return a.a < b.a;
    return a.c < b.c;
}
bool Cmp3(Person a, Person b) {
    if (a.c != b.c) return a.c < b.c;
    if (a.b != b.b) return a.b < b.b;
    return a.a < b.a;
}
// #ifdef __Debug
// bool Cmp1(Person srca, Person srcb) {
//     if (srca.a != srcb.a) return srca.a < srcb.a;
//     return srca.b < srcb.b;
// }
// bool Cmp2(Person srca, Person srcb) {
//     return srca.b < srcb.b;
// }
// #else
// bool Cmp1(Person srca, Person srcb) {
//     if (srca.a != srcb.a) return srca.a < srcb.a;
//     if (srca.b != srcb.b) return srca.b < srcb.b;
//     return srca.c < srcb.c;
// }
// bool Cmp2(Person srca, Person srcb) {
//     if (srca.b != srcb.b) return srca.b < srcb.b;
//     return srca.c < srcb.c;
// }
// // #endif

// unordered_map<int, int> ump;

// struct BinaryTree {
//     int sum[N];

//     int Lowbit(int x) { return x & -x; }

//     void Add(int pos, int val) {
//         for (int i = pos; i <= n; i += Lowbit(i)) sum[i] = max(sum[i], val);
//         return; 
//     }

//     int Query(int pos) {
//         int ans = 0;
//         for (int i = pos; i > 0; i -= Lowbit(i)) ans = max(ans, sum[i]);
//         return ans;
//     }
// };

// BinaryTree bin;
// int ans;
// int cnt[N];

// void Cdq(int l, int r) {
//     if (l == r) return;
//     int mid = (l + r) >> 1;
//     Cdq(l, mid);
//     Cdq(mid + 1, r);
//     sort(person + l, person + mid + 1, Cmp2);
//     sort(person + mid + 1, person + r + 1, Cmp2);
//     for (int i = l; i <= r; i++) {
//         bin.Add(person[i].b, person[i].c);
//         cnt[ump[person[i].c]]++;
//     }
//     int i = l, j = mid + 1, maxn = 0;// 1 4
//     #ifdef __Debug
//         if (l == 1 && r == 5) {
//             printf("\n");
//             for (int i = 1; i <= n; i++) {
//                 printf("i=%d a=%d b=%d c=%d\n", i, person[i].a, person[i].b, person[i].c);
//             }
//         }
//     #endif
//     while (j <= r) {
//         while (i <= mid && person[i].b <= person[j].b) i++;
//         while (i <= mid && person[i].b > person[j].b) {
//             if (maxn > 0) ans = max(ans, maxn + person[i].b + person[j].a);
//             maxn = max(maxn, person[i].c);
//             i++;
//         }
//         if (maxn > 0) ans = max(ans, maxn + person[i].b + person[j].a);
//         maxn = max(maxn, person[j].c);
//         j++;
//     }
//     return;
// }

// int tmp[N];

signed main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        // #ifdef __Debug
        // cin >> person[i].a >> person[i].b;
        // #else
        cin >> person[i].a >> person[i].b >> person[i].c;
        // #endif
        // tmp[i] = person[i].c;
    }
    // sort(tmp + 1, tmp + n + 1);
    // for (int i = 1; i <= n; i++) ump[tmp[i]] = i;
    // sort(person + 1, person + n + 1, Cmp1);
    // #ifdef __Debug
    //     for (int i = 1; i <= n; i++) {
    //         printf("i=%d a=%d b=%d c=%d\n", i, person[i].a, person[i].b, person[i].c);
    //     }
    // #endif
    // Cdq(1, n);
    // if (!ans) printf("-1\n");
    // else printf("%d\n", ans);
    int ans = 0;
    sort(person + 1, person + n + 1, Cmp1);
    for (int i = 1; i <= n; i++) {
        if (!person[i].flag) {
            person[i].flag = true;
            ans += person[i].a;
            break;
        }
    }
    sort(person + 1, person + n + 1, Cmp2);
    for (int i = 1; i <= n; i++) {
        if (!person[i].flag) {
            person[i].flag = true;
            ans += person[i].c;
            break;
        }
    }
    sort(person + 1, person + n + 1, Cmp3);
    for (int i = 1; i <= n; i++) {
        if (!person[i].flag) {
            person[i].flag = true;
            ans += person[i].c;
            break;
        }
    }
    printf("%d\n", ans);

    return 0;
}