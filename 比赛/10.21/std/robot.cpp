#include<bits/stdc++.h>
using namespace std;
string st;
int n,q,op,x,l,r;
int mtx[4][4][4]={
    {{1,0,1,0},{0,1,0,1},{0,0,1,0},{0,0,0,1}},
    {{1,0,0,0},{0,1,0,0},{0,0,0,-1},{0,0,1,0}},
    {{1,0,-1,0},{0,1,0,-1},{0,0,1,0},{0,0,0,1}},
    {{1,0,0,0},{0,1,0,0},{0,0,0,1},{0,0,-1,0}}
};
//initial_result:[0,0,1,0]
int a[205000],sgt[805000][4][4],res[4],prvres[4];
char ch;
void pushup(int p) {
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            sgt[p][i][j]=0;
            for (int k=0;k<4;k++) {
                sgt[p][i][j]+=sgt[p*2][k][j]*sgt[p*2+1][i][k];
            }
        }
    }
}
void build(int p,int s,int t) {
    if (s==t) {
        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                sgt[p][i][j]=mtx[a[s]][i][j];
            }
        }
        return;
    }
    int mid=(s+t)/2;
    build(p*2,s,mid);
    build(p*2+1,mid+1,t);
    pushup(p);
}
void update(int p,int s,int t,int x,int y) {
    if (s==t) {
        for (int i=0;i<4;i++) {
            for (int j=0;j<4;j++) {
                sgt[p][i][j]=mtx[y][i][j];
            }
        }
        return;
    }
    int mid=(s+t)/2;
    if (x<=mid) update(p*2,s,mid,x,y);
    else update(p*2+1,mid+1,t,x,y);
    pushup(p);
}
void updres(int p) {
    for (int i=0;i<4;i++) {
        prvres[i]=res[i];
        res[i]=0;
    }
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            res[i]+=sgt[p][i][j]*prvres[j];
        }
    }
}
void query(int p,int s,int t,int l,int r) {
    if ((l<=s)&&(t<=r)) {
        updres(p);
        return;
    }
    int mid=(s+t)/2;
    if (l<=mid) query(p*2,s,mid,l,r);
    if (r>mid) query(p*2+1,mid+1,t,l,r);
}
int main() {
    freopen("robot.in","r",stdin);
    freopen("robot.out","w",stdout);
    cin>>n>>st;
    for (int i=1;i<=n;i++) {
        if (st[i-1]=='W') a[i]=0;
        else if (st[i-1]=='A') a[i]=1;
        else if (st[i-1]=='S') a[i]=2;
        else a[i]=3;
    }
    build(1,1,n);
    cin>>q;
    for (int i=1;i<=q;i++) {
        cin>>op;
        if (op==1) {
            cin>>x>>ch;
            if (ch=='W') a[x]=0;
            else if (ch=='A') a[x]=1;
            else if (ch=='S') a[x]=2;
            else a[x]=3;
            update(1,1,n,x,a[x]);
        } else {
            cin>>l>>r;
            res[0]=0;res[1]=0;res[2]=1;res[3]=0;
            query(1,1,n,l,r);
            printf("%d %d\n",res[0],res[1]);
        }
    }
    return 0;
}
/*
[{x},{y},{dirx},{diry}]
[{0},{0},{1},{0}]
W:[{1,0,1,0},{0,1,0,1},{0,0,1,0},{0,0,0,1}]
A:[{1,0,0,0},{0,1,0,0},{0,0,0,-1},{0,0,1,0}]
S:[{1,0,-1,0},{0,1,0,-1},{0,0,1,0},{0,0,0,1}]
D:[{1,0,0,0},{0,1,0,0},{0,0,0,1},{0,0,-1,0}]
*/