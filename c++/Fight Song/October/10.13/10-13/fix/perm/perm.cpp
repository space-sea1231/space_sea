#include "perlib.h"
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

vector<int> q, invq, known;

vector<int> odpowiedz(int c, int n) {
    for (int i = 0; i < n; i++) {
        q.emplace_back(i);
        invq.emplace_back(i);
    }
    known.emplace_back(0);
    for (int i = 1; i < n; i++) {
        if (!zapytaj(q, 0, i)) {
            swap(invq[0], invq[i]);
            for (int j = 0; j < n; j++) q[invq[j]] = j;
            known.insert(known.end(), i);
            continue;
        }   
        vector<int> cur = q, invcur = invq;
        int l = 1, r = known.size() - 1, pos = 0;
        while (l <= r) {
            int mid = l + r >> 1;
            swap(invq[0], invq[known[mid]]);
            for (int j = 0; j < n; j++) q[invq[j]] = j;
            if (!zapytaj(q, 0, i)) pos = mid, l = mid + 1;
            else r = mid - 1;
            q = cur, invq = invcur;
        }
        known.insert(known.begin() + pos + 1, i);
    }
    vector<int> tmp(n);
    for (int i = 0; i < n; i++) tmp[known[(i + n - 1) % n]] = known[i];
    for (int i = 0 ;i < n; i++) q[i] = invq[tmp[i]];
    return q;
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