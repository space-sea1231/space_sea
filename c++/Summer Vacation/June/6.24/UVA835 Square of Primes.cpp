    #include <iostream>
    #include <stdio.h>
    #include <algorithm>
    #include <cstring>
    #include <vector>
    #define __Debug

    using namespace std;
    typedef long long ll;

    const int N = 1e5 + 10;
    const int M = 11;

    int t, n;
    int cnt;
    int prime[N];
    int ans[M][M];
    bool vis[N];
    bool flag[M][M][M][M][M][60];
    pair<int, int> pos[26] = {{0, 0}, 
        {3, 3}, {2, 2}, {2, 4}, {4, 2}, {4, 4}, {2, 3}, {3, 2}, {3, 4}, {4, 3},
        {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5},
        {2, 1}, {3, 1}, {4, 1}, {5, 1}, {5, 2}, {5, 3}, {5, 4}
    };

    int Get(int x, int y) {
        if (y == 0) {
            int sum = 0;
            while (x) {
                sum += x % 10;
                x /= 10;
            }
            return sum;
        }
        for (int i = 1; i < y; i++) x /= 10;
        return x % 10;
    }
    vector<int> tmp;
    void Dfs1(int cur, int i) {
        if (cur == 0) {
            flag[tmp[0]][tmp[1]][tmp[2]][tmp[3]][tmp[4]][n] = true;
            return ;
        }
        tmp.push_back(10);
        Dfs1(cur - 1, i);
        tmp.pop_back();
        tmp.push_back(Get(i, cur));
        Dfs1(cur - 1, i);
        tmp.pop_back();
    }
    void Init() {
        vis[1] = 1; 
        for (int i = 2; i < N - 10; i++) {
            if (!vis[i]) prime[++cnt] = i;
            for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
                vis[i * prime[j]] = true;
                if (i % prime[j] == 0) break;
            }
        }
    }
    string s[10000];
    int tot;
    void Dfs(int cur) {
        if (cur == 25) {
            // cerr << 1;
            tot++;
            for (int i = 1; i <= 5; i++) {
                for (int j = 1; j <= 5; j++) {
                    s[tot] += (ans[i][j] + '0');
                }
            }
            return;
        }
        int i = pos[cur].first, j = pos[cur].second;
        for (int k = 0; k <= 9; k++) {
            ans[i][j] = k;
            if (!flag[ans[i][1]][ans[i][2]][ans[i][3]][ans[i][4]][ans[i][5]][n]) continue;
            if (!flag[ans[1][j]][ans[2][j]][ans[3][j]][ans[4][j]][ans[5][j]][n]) continue;
            if (i == j && !flag[ans[1][1]][ans[2][2]][ans[3][3]][ans[4][4]][ans[5][5]][n]) continue;    
            if (i + j == 6 && !flag[ans[1][5]][ans[2][4]][ans[3][3]][ans[4][2]][ans[5][1]][n]) continue;
            Dfs(cur + 1);
        }
        ans[i][j] = 10;
        // printf("%d\n", cur);         
    }
    void Init1() {
        for (int i = 1; i <= cnt; i++) {
            if (prime[i] > 10000 && Get(prime[i], 0) == n) Dfs1(5, prime[i]);
        }
    }
    signed main() {
        cin.tie(nullptr) -> ios::sync_with_stdio(false);
        Init();
        cin >> t;
        while (t--) {
            for (int i = 1; i <= 5; i++) {
                for (int j = 1; j <= 5; j++) {
                    ans[i][j] = 10;
                }
            }
            cin >> n >> ans[1][1];
            Init1();
            Dfs(1);
        }
        sort(s + 1, s + tot + 1);
        for (int i = 1; i <= tot; i++) {
            for (int j = 1; j <= 5; j++) {
                for (int k = 1; k <= 5; k++) {
                    printf("%c", s[i][(j - 1) * 5 + k - 1]);
                }
                printf("\n");
            }
            printf("\n");
        }
        return 0;
    }