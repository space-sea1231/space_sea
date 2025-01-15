#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int n, ans;
template <typename T, int N> struct Heap{
    T heap[N];
    int tot=0;
    void push(int x){
        heap[++tot]=x;
        int now=tot;
        while (now){
            int fa=(now>>1);
            if (fa&&heap[fa]>heap[now]){
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
            if (l<=tot&&heap[maxn]>heap[l]){
                maxn=l;
            }
            if (r<=tot&&heap[maxn]>heap[r]){
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
    bool empty(){
        if (tot==0){
            return 1;
        }else{
            return 0;
        }
    }
};
Heap<int, N> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        q.push(x);
    }
    while (q.size()>1){
        int a=q.top();
        q.pop();
        int b=q.top();
        q.pop();
        ans=ans+(a+b);
        q.push(a+b);
    }
    printf("%d\n", ans);

    return 0;
}