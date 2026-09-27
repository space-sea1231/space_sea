#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
long long a[N];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> a[i];

    long long sum_d = 0;
    long long g = 0;


    for (int i = 1; i < n; i++) 
    {
        long long d = abs(a[i + 1] - a[i]);
        sum_d += d;
        g = __gcd(g, d); 
    }
    g *= 2;

    long long v1;
    if (g == 0) 
        v1 = a[1];
    else 
        v1 = ((a[1] - 1) % g + g) % g + 1;

    cout << v1 + sum_d << "\n";

    return 0;
}
