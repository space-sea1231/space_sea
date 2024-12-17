#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int INF=1<<30;
int n, m;
int a[N];
template <typename T, int N> struct Heap{
    T heap[N];
    int tot=0;
    void push(int x){
        heap[++tot]=x;
        int now=tot;
        while (now){
            int fa=(now>>1);
            if (fa&&heap[fa]<heap[now]){
                swap(heap[fa], heap[now]);
                now=fa;
            }else{
                return ;
            }
        }
    }
    void pop(){
        if (tot==0){
            return ;
        }
        int now=1;
        heap[now]=heap[tot];
        tot--;
        while (1){
            int l=(now<<1);
            int r=(now<<1)|1;
            int maxn=now;
            if (l<=tot&&heap[l]>heap[maxn]){
                maxn=l;
            }
            if (r<=tot&&heap[r]>heap[maxn]){
                maxn=r;
            }
            if (maxn==now){
                return ;
            }
            swap(heap[maxn], heap[now]);
            now=maxn;
        }
    }
    T top(){
        return heap[1];
    }
    int size(){
        return tot;
    }
};
Heap <int, N> q, p;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    int last=1;
    for (int i=1; i<=m; i++){
        int x;
        cin >> x;
        for (int j=last; j<=x; j++){
            q.push(a[j]);
            if (q.size()==i){
                p.push(-q.top());
                q.pop();
            }
        }
        printf("%d\n", -p.top());
        q.push(-p.top());
        p.pop();
        last=x+1;
    }

    return 0;
}