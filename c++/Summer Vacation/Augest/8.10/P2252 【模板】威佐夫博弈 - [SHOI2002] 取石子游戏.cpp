#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

ll a, b;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> a >> b;
    if (a > b) swap(a, b);
    long double phi = (sqrt(5.0L) + 1.0L) / 2.0L;
    long double c = (b - a) * phi;
    // printf("%.9llf\n", c);
    if (floor(c) == a) printf("0\n");
    else printf("1\n");
    return 0;
}
/*
Are you ready kids?

准备好了吗？孩子们？

Aye, aye, captain!

是的，船长

I can't hear you!

太小声罗

Aye, aye, captain!

是的，船长

Ooh

哦~

Who lives in a pineapple under the sea?

是谁住在深海的大菠萝里

SpongeBob SquarePants!

海绵宝宝

Absorbent and yellow and porous is he!

方方黄黄伸缩自如

SpongeBob SquarePants!

海绵宝宝

If nautical nonsense be something you wish!

如果四处探险是你的愿望

SpongeBob SquarePants!

海绵宝宝

Then drop on the deck and flop like a fish!

那就敲敲甲板让大鱼开路

SpongeBob SquarePants!

海绵宝宝

Ready?

准备好了吗？

SpongeBob SquarePants,

海绵宝宝

SpongeBob SquarePants!

海绵宝宝

SpongeBob SquarePants!

海绵宝宝

SpongeBob SquarePants!

海绵宝宝

Ha, ha, ha

哈哈

Ha, ha, ha, ha, ha

哈哈哈
*/