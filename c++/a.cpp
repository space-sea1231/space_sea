#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010, INF = 1e9;

struct Operator
{
    //op 表示操作类型
    //op = 0 表示将第 x 个数赋值为 y
    //op = i 表示第 i 次查询 [x, y] 区间中第 k 小数的答案
    int op, x, y, k;
};
Operator q[N * 2], lq[N * 2], rq[N * 2]; //总操作序列、左子操作序列、右子操作序列
int qcnt;

int n, m;
int tr[N]; //树状数组，统计 [0, x] 区间中 <= mid 的数的个数
int res[N]; //记录所有查询的答案

int lowbit(int x)
{
    return x & -x;
}

void insert(int x, int c) //将树状数组第 x 个位置加上 c
{
    for(int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int query(int x) //查询 [0, x] 区间中 <= mid 的数的个数
{
    int res = 0;
    for(int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

void work(int minv, int maxv, int l, int r) //值域为 [minv, maxv]，操作序列为 [l, r]
{
    if(l > r) return; //操作序列为空
    if(minv == maxv) //值域到达边界
    {
        for(int i = l; i <= r; i++)
            if(q[i].op) res[q[i].op] = minv; //将操作序列中所有查询操作的答案直接赋值为边界
        return;
    }

    int mid = minv + maxv >> 1; //计算值域中间值
    int lcnt = 0, rcnt = 0;
    for(int i = l; i <= r; i++) //枚举区间中所有操作
    {
        if(!q[i].op) //赋值操作
        {
            if(q[i].y <= mid) //如果当前数的值 <= mid
            {
                insert(q[i].x, 1); //第 q[i].x 个位置上 <= mid 的数+1
                lq[++lcnt] = q[i]; //加入左序列
            }
            else rq[++rcnt] = q[i]; //加入右序列
        }
        else //询问操作
        {
            int cnt = query(q[i].y) - query(q[i].x - 1); //查询 [q[i].x, q[i].y] 区间中 <= mid 的数的个数
            if(cnt >= q[i].k) lq[++lcnt] = q[i]; //如果答案在左区间，将操作加入左序列
            else
            {
                q[i].k -= cnt; //在右区间中查询的数的排名应该减去左区间中数的个数，即 q[i].k - cnt
                rq[++rcnt] = q[i]; //否则说明答案在右区间，将操作加入右序列
            }
        }
    }

    for(int i = r; i >= l; i--) //还原树状数组
        if(!q[i].op && q[i].y <= mid) //将之前符合要求的赋值操作撤销
            insert(q[i].x, -1);

    for(int i = 1; i <= lcnt; i++) q[l + i - 1] = lq[i]; //将左子序列的操作拷贝回原序列
    for(int i = 1; i <= rcnt; i++) q[l + lcnt + i - 1] = rq[i]; //将右子序列的操作拷贝回原序列

    work(minv, mid, l, l + lcnt - 1); //递归左区间
    work(mid + 1, maxv, l + lcnt, r); //递归右区间
}

int main()
{
    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        q[++qcnt] = {0, i, x, 0}; //将初始序列看成赋值操作
    }

    for(int i = 1; i <= m; i++)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        q[++qcnt] = {i, l, r, k}; //查询操作
    }

    work(-INF, INF, 1, qcnt); //对所有操作进行整体分治

    for(int i = 1; i <= m; i++) printf("%d\n", res[i]);

    return 0;
}