#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int N = 5e3 + 10;

int n;
int S[N], D[N], p[N];
bool vis[N];

extern "C" int tryCombination(int S[]);
extern "C" void answer(int S[], int D[]);

void Dfs(int l, int r, int k, int door) {
    if (l == r) { 
        D[l] = door;
        if (k == door) S[l] = p[l] = !p[l];
        else S[l] = p[l];
        vis[l] = true;
        return;
    }
    int mid = (l + r) >> 1;
    for (int i = l; i <= mid; i++) {
        if (!vis[i]) p[i] = !p[i];
    }
    int t = tryCombination(p);
    if ((k == door && t != door) || (k != door && t == door)) Dfs(l, mid, t, door);
    else Dfs(mid + 1, r, t, door);
}

extern "C" void exploreCave(int N) {
    n = N;
    for (int dr = 0; dr < n; dr++) {
        int k = tryCombination(p);
        Dfs(0, n - 1, k, dr);
    }
    answer(S, D);
}
/*
取一杯天上的水
照着明月人世间晃呀晃
爱恨不过是一瞬间
红尘里飘摇
取一杯天上的水
照了明月人世间望呀望
爱恨重复过千百遍
红尘里飘摇
就让这 大风吹 大风吹 一直吹
吹走我心里 那段痛 那段悲
让暴雨冲洗 风中唏嘘 当初的你
仿佛是天注定
就让这 大风吹 大风吹 一直吹
漆黑中洗去眼眸里那泪水
就让那往事 消失风里 当初的你
曾记得我的那个谁
取一杯天上的水
照了明月人世间望呀望
爱恨重复过千百遍
红尘里飘摇
就让这 大风吹 大风吹 一直吹
吹走我心里 那段痛 那段悲
让暴雨冲洗 风中唏嘘 当初的你
仿佛是天注定
就让这 大风吹 大风吹 一直吹
漆黑中洗去眼眸里那泪水
就让那往事 消失风里 当初的你
曾记得我的那个谁
*/