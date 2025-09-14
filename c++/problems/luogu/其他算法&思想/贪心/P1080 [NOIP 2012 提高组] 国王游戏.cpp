#include <iostream>
#include <stdio.h>
#include <algorithm>
// #define __Debug

using namespace std;
typedef long long ll;

const int N = 1e3 + 10;
const int M = 1e6 + 10;
const int INF = 0x3f3f3f3f;

int n;
int a[N], b[N];

struct Person {
    int a, b;

    bool operator<(const Person &src) {
        return a * b < src.a * src.b;
    }
};

struct HighPrecision {
    int len = 1;
    int sum[M] = {0, 1};
};

Person person[N];
HighPrecision sum, ans, tmp;

void Mul(HighPrecision &a, int b) {
    int sum = 0;
    for (int i = 1; i <= a.len; i++) {
        a.sum[i] *= b;
        a.sum[i] += sum % 10;
        sum /= 10;
        sum += a.sum[i] / 10;
        a.sum[i] %= 10;
    }
    while (sum) {
        a.len++;
        a.sum[a.len] = sum % 10;
        sum /= 10;
    }
    return;
}

void Div(HighPrecision &a, int b) {
    tmp.len = a.len;
    reverse(a.sum + 1, a.sum + a.len + 1);
    int sum = 0;
    for (int i = 1; i <= a.len; i++){
        tmp.sum[i] = (sum * 10 + a.sum[i]) / b;
        sum = (sum * 10 + a.sum[i]) % b;
    }
    reverse(a.sum + 1, a.sum + a.len + 1);
    int start = 1;
    while (!tmp.sum[start] && start < a.len) start++;
    for (int i = 1; i <= a.len - start + 1; i++) tmp.sum[i] = tmp.sum[i + start - 1]; 
    tmp.len = a.len - start + 1;
    return;
}

void Compare(HighPrecision &a, HighPrecision &b) {
    if (b.len < a.len) return;
    if (b.len > a.len) {
        a = b;
        return;
    }
    for (int i = 1; i <= a.len; i++) {
        if (a.sum[i] > b.sum[i]) return;
        if (a.sum[i] < b.sum[i]) {
            a = b;
            return;
        }
    }
    return;
}
#ifdef __Debug
void Print(HighPrecision &a) {
    printf("len=%d ", a.len);
    for (int i = a.len; i >= 1; i--) printf("%d", a.sum[i]);
    printf("\n");
    return;
}
#endif
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    ans.sum[1] = 0;
    cin >> n;
    for (int i = 0; i <= n; i++) cin >> person[i].a >> person[i].b;
    sort(person + 1, person + n + 1);
    #ifdef __Debug
    for (int i = 1; i <= n; i++) printf("person[%d]: a=%d b=%d\n", i, person[i].a, person[i].b);
    printf("\n");
    #endif
    Mul(sum, person[0].a);
    for (int i = 1; i <= n; i++) {
        Div(sum, person[i].b);
        Compare(ans, tmp);
        Mul(sum, person[i].a);
        #ifdef __Debug
        Print(ans);
        printf("------------------\n");
        Print(tmp);
        printf("\n");
        #endif
    }
    for (int i = 1; i <= ans.len; i++) printf("%d", ans.sum[i]);
    printf("\n");
    return 0;
}