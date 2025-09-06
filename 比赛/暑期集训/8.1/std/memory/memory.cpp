#include <bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 10;
int n, m;
struct node{
    int mx;
    priority_queue<int> q;
} t[N*8];
 
void psu(int p){
    t[p].mx = max({ t[p<<1].mx, t[p<<1|1].mx, t[p].q.top() });
}
void add(int p, int l, int r, int ql, int qr, int v){
    if(qr < l || r < ql){
        return;
    } else if(ql <= l && r <= qr){
        t[p].mx = max(t[p].mx, v);
        t[p].q.push(v);
    } else {
        int mid = l + r >> 1;
        add(p<<1, l, mid, ql, qr, v);
        add(p<<1|1, mid+1, r, ql, qr, v);
        psu(p);
    }
}
void psd(int p, int l, int r, int ql, int qr, int v){
    if(ql <= l && r <= qr){
        return;
    }
    int mid = l + r >> 1;
    if(ql > mid){
        t[p<<1].mx = max(t[p<<1].mx, v);
        t[p<<1].q.push(v);
        psd(p<<1|1, mid+1, r, ql, qr, v);
    } else if(qr <= mid){
        t[p<<1|1].mx = max(t[p<<1|1].mx, v);
        t[p<<1|1].q.push(v);
        psd(p<<1, l, mid, ql, qr, v);
    } else {
        psd(p<<1, l, mid, ql, qr, v);
        psd(p<<1|1, mid+1, r, ql, qr, v);
    }
    psu(p);
}
void del(int p, int l, int r, int ql, int qr, int v){
    if(qr < l || r < ql || t[p].mx < v){
        return;
    } else if(t[p].q.top() == v){
        t[p].q.pop();
        psd(p, l, r, ql, qr, v);
        psu(p);
    } else {
        int mid = l + r >> 1;
        del(p<<1, l, mid, ql, qr, v);
        del(p<<1|1, mid+1, r, ql, qr, v);
        psu(p);
    }
}
int qry(int p, int l, int r, int ql, int qr){
    if(qr < l || r < ql){
        return -1;
    } else if(ql <= l && r <= qr){
        return t[p].mx;
    } else {
        int mid = l + r >> 1;
        return max({ qry(p<<1, l, mid, ql, qr),
                     qry(p<<1|1, mid+1, r, ql, qr),
                     t[p].q.top() });
    }
}
 
int main(){
	freopen("memory.in", "r", stdin);
	freopen("memory.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < N*4; ++ i){
        t[i].q.push(-1);
        t[i].mx = -1;
    }
    for(int i = 1; i <= m; ++ i){
        int op, l, r, k;
        scanf("%d%d%d", &op, &l, &r);
        if(op == 1){
            scanf("%d", &k);
            add(1, 1, n, l, r, k);
        } else if(op == 2){
            int p = qry(1, 1, n, l, r);
            if(p != -1){
                del(1, 1, n, l, r, p);
            }
        } else {
            printf("%d\n", qry(1, 1, n, l, r));
        }
    }
    return 0;
}