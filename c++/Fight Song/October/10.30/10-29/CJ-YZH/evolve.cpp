#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e3 + 10;

int n;
string U;
string a[N];
int s1, s2;
vector<int> pos[N];
vector<int> ans1, ans2;
deque<int> line;

bool Check(int x, int y) {
    int sizx = a[x].size();
    int sizy = a[y].size();
    int cnt = 0;
    if (sizy == 0) return true;
    for (int i = 0; i < sizx; i++) {
        if (a[x][i] == a[y][cnt]) cnt++;
        if (cnt == sizy) return true;
    }
    return false;
}
void D(int x, int y) {cerr<<"Debug "<<y<<": "<<x<<"\n";}
signed main() {
    freopen("evolve.in", "r", stdin);
    freopen("evolve.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> a[n + 1];
    for (int i = 1; i <= n; i++) {    
        cin >> a[i];
        pos[a[i].size()].emplace_back(i);
    }
    int flag = 0;
    for (int i = 1; i < N; i++) {
        if (pos[i].empty()) continue;
        if (pos[i].size() > 2) { printf("impossible\n"); return 0; }
        if (pos[i].size() == 1) {
            bool c1 = Check(pos[i][0], s1);
            bool c2 = Check(pos[i][0], s2);
            if (flag) {
                // 能接上
                if (Check(pos[i][0], line.back())) line.push_back(pos[i][0]);
                else { // 开始接头
                    if (c1) {
                        ans1.emplace_back(pos[i][0]);
                        s1 = pos[i][0];
                        s2 = line.back();
                        while (!line.empty()) {
                            ans2.emplace_back(line.front());
                            line.pop_front();
                        }
                    } else if (c2) {
                        ans2.emplace_back(pos[i][0]);
                        s2 = pos[i][0];
                        s1 = line.back();
                        while (!line.empty()) {
                            ans1.emplace_back(line.front());
                            line.pop_front();
                        }
                    } else { printf("impossible\n"); return 0; }
                    flag = 0;
                }
                continue;
            }
            if (c1 && c2) { flag = i; line.push_back(pos[flag][0]); }
            else if (c1) {
                ans1.emplace_back(pos[i][0]);
                s1 = pos[i][0];
            } else if (c2) {
                ans2.emplace_back(pos[i][0]);
                s2 = pos[i][0];
            } else { printf("impossible\n"); return 0; }
        } else {
            #ifdef __Debug
            bool fff = false;
            if (pos[i][0] == 300 || pos[i][1] == 300) fff = true;
            #endif
            bool A_1 = Check(pos[i][0], s1);
            bool A_2 = Check(pos[i][0], s2);
            bool B_1 = Check(pos[i][1], s1);
            bool B_2 = Check(pos[i][1], s2);
            // cerr << A_1 << " " << A_2 << " " << B_1 <<" " << B_2 << "\n";
            if (flag) {
                bool C_1 = Check(pos[i][0], line.back());
                bool C_2 = Check(pos[i][1], line.back());
                // cerr<<C_1 << " " << C_2 << "\n";
                // cerr<<a[pos[i][0]] << " " << a[pos[i][1]] <<" " << line.back()<< "\n";
                if (C_1 && (B_1 || B_2)) {
                    if (B_1) {
                        ans1.emplace_back(pos[i][1]);
                        line.push_back(pos[i][0]);
                        s1 = pos[i][1];
                        s2 = line.back();
                        while (!line.empty()) {
                            ans2.emplace_back(line.front());
                            line.pop_front();
                        }
                    } else if (B_2) {
                        ans2.emplace_back(pos[i][1]);
                        line.push_back(pos[i][0]);
                        s2 = pos[i][1];
                        s1 = line.back();
                        while (!line.empty()) {
                            ans1.emplace_back(line.front());
                            line.pop_front();
                        }
                    }
                } else if (C_2 && (A_1 || A_2)) {
                    if (A_1) {
                        ans1.emplace_back(pos[i][0]);
                        line.push_back(pos[i][1]);
                        s1 = pos[i][0];
                        s2 = line.back();
                        while (!line.empty()) {
                            ans2.emplace_back(line.front());
                            line.pop_front();
                        }
                    } else if (A_2) {
                        ans2.emplace_back(pos[i][0]);
                        line.push_back(pos[i][1]);
                        s2 = pos[i][0];
                        s1 = line.back();
                        while (!line.empty()) {
                            ans1.emplace_back(line.front());
                            line.pop_front();
                        }
                    }
                } else { printf("impossible\n"); return 0; }
                flag = 0;
                continue;
            }
            if (A_1 && A_2) {
                if (B_1) {
                    ans1.emplace_back(pos[i][1]);
                    ans2.emplace_back(pos[i][0]);
                    s1 = pos[i][1], s2 = pos[i][0];
                } else if (B_2) {
                    ans2.emplace_back(pos[i][1]);
                    ans1.emplace_back(pos[i][0]);
                    s1 = pos[i][0], s2 = pos[i][1];
                } else { printf("impossible\n"); return 0; }
            } else if (B_1 && B_2) {
                if (A_1) {
                    ans1.emplace_back(pos[i][0]);
                    ans2.emplace_back(pos[i][1]);
                    s1 = pos[i][0], s2 = pos[i][1];
                } else if (A_2) {
                    ans2.emplace_back(pos[i][0]);
                    ans1.emplace_back(pos[i][1]);
                    s1 = pos[i][1], s2 = pos[i][0];
                } else { printf("impossible\n"); return 0; }
            } else {
                if (A_1 && B_2) {
                    ans1.emplace_back(pos[i][0]);
                    ans2.emplace_back(pos[i][1]);
                    s1 = pos[i][0], s2 = pos[i][1];
                } else if (A_2 && B_1) {
                    ans1.emplace_back(pos[i][1]);
                    ans2.emplace_back(pos[i][0]);
                    s1 = pos[i][1], s2 = pos[i][0];
                } else { printf("impossible\n"); return 0; }
            }
        }
    }
    if (flag) {
        while (!line.empty()) {
            ans1.emplace_back(line.front());
            line.pop_front();
        }
    }
    if ((!ans1.empty() && !Check(n + 1, ans1.back())) || (!ans2.empty() && !Check(n + 1, ans2.back()))) {
        printf("impossible\n");
        return 0;
    }
    printf("%d %d\n", (int)ans1.size(), (int)ans2.size());
    for (int p : ans1) printf("%s\n", a[p].c_str());
    for (int p : ans2) printf("%s\n", a[p].c_str());
    return 0;
}
/*
a
b
ab
aaa
*/