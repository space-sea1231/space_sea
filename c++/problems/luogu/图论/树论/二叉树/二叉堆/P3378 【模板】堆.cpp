#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n, top;
int heap[N];
void add(int x){
    heap[++top]=x;
    int now=top;
    while (now){
        int fa=(now>>1);
        if (heap[fa]>heap[now]){
            swap(heap[fa], heap[now]);
            now=fa;
        }else{
            return ;
        }
    }
    return ;
}
void remove(){
    if (top==0){
        return ;
    }
    int now=1;
    heap[now]=heap[top];
    top--;
    while (1){
        int l=(now<<1);
        int r=(now<<1)|1;
        int maxn=now;
        if (l<=top&&heap[l]<=heap[maxn]){
            maxn=l;
        }
        if (r<=top&&heap[r]<=heap[maxn]){
            maxn=r;
        }
        if (maxn==now){
            return ;
        }
        swap(heap[maxn], heap[now]);
        now=maxn;
    }
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int x;
            cin >> x;
            add(x);
        }
        if (opt==2){
            printf("%d\n", heap[1]);
        }
        if (opt==3){
            remove();
        }
    }

    return 0;
}