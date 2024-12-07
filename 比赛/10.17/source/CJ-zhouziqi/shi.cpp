#include <cstring>
#include <cstdio>
#include <vector>

constexpr int MAXN = 1000000 + 2;

char a[MAXN];

std::vector<int> ans;

void operate(int x) {
    a[x - 1] = !a[x - 1] && !a[x];
    a[x + 1] = !a[x + 1] && !a[x];
    ans.push_back(x);
}

template <typename ...Args> void operate(int x, Args ...args) {
    operate(x);
    operate(args...);
}

void printAns(int sum) {
    printf("%d %ld\n", sum, ans.size());
    for (int x : ans) {
        printf("%d ", x);
    }
    putchar('\n');
}

void solve() {
    scanf("%s", a + 1);
    int n = strlen(a + 1), sum = 0;

    for (int i = 1; i <= n; i ++) {
        sum += (a[i] -= '0');
    }

    ans.clear();

    if (sum >= n - 1 || n < 3) {
        return printAns(sum);
    }

    if (n == 3) {
        int a1 = !a[1] && !a[2];
        int a3 = !a[3] && !a[2];

        if (a1 + a[2] + a3 == 2) {
            operate(2);
            printAns(2);
        } else {
            printAns(sum);
        }

        return;
    }

    for (int i = 1; i < n - 2; i ++) {
        if (!a[i] && a[i + 1]) {
            operate(i + 2);
        }
        if (!a[i]) {
            operate(i + 1);
        }
    }

    if (a[n - 2] + a[n - 1] + a[n] == 2) {
        return printAns(n - 1);
    }

    if (a[n - 1] && n == 4) {
        return printAns(n - 2);
    }

    if (a[n - 2]) {
        operate(n - 2, n - 1, n - 2);
    } else if (a[n - 1]) {
        operate(n - 3, n - 2, n - 3, n - 1, n - 2);
    } else if (a[n]) {
        operate(n - 2, n - 1, n - 2, n - 1);
    } else {
        operate(n - 1);
    }

    printAns(n - 1);
}

int main() {
    freopen("shi.in", "r", stdin);
    freopen("shi.out", "w", stdout);

    int T;
    scanf("%d", &T);

    while (T --) {
        solve();
    }

    return 0;
}
