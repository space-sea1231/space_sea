#include<bits/stdc++.h>
using namespace std;
const int N=4e5+6;
int tree[N];
int n,k;
int t[N];
int ans[N];
int lowbit(int x){
    return x&(-x);
}
int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
void update(int x,int y){
    while(x<=300000){
        tree[x]+=y;
        x+=lowbit(x);
    }
    return ;
}
struct node{
    int a,b,c,id,res;
}a[N];
bool cmp1(node a,node b){
    if (a.a!=b.a) return a.a<b.a;
    if (a.b!=b.b) return a.b<b.b;
    return a.c<b.c;
}
bool cmp2(node a,node b){
    if (a.b!=b.b) return a.b<b.b;
    return a.c<b.c;
}
void cdq(int l,int r){
    if(l==r)return ;
    int mid=(l+r)>>1;
    cdq(l,mid),cdq(mid+1,r);
    sort(a+l,a+1+mid,cmp2);
    sort(a+1+mid,a+1+r,cmp2);
    int ptr=l;
    for(int i=mid+1;i<=r;i++){
        while(ptr<=mid&&a[ptr].b<=a[i].b){
            // cerr<<a[ptr].c<<"\n";
            update(a[ptr].c,1);
            ptr++;
        }
        a[i].res+=query(a[i].c);
        // cerr<<query(1)<<"\n";
    }
    for(int i=l;i<ptr;i++){
        update(a[i].c,-1);
    }
}
int main(){
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i].a >> a[i].b >> a[i].c;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp1);
    cdq(1,n);
    int l=0;
    for(int i=1;i<=n;i++){
        if(a[i].a!=a[i-1].a||a[i].b!=a[i-1].b||a[i].c!=a[i-1].c){
            for(int j=l;j<i;j++){
                // cerr<<1;
                ans[j]+=i-l-1;
            }
            l=i;
        }else{
            ans[i]-=i-l;
        }
    }
    for(int i=1;i<=n;i++){
        t[a[i].res]++;
    }
    for(int i=0;i<n;i++){
        cout << t[i] << "\n";
    }
    return 0;
}
// 1 2