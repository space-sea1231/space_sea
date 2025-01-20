#include <bits/stdc++.h>
using namespace std;
int read(){
    char c=getchar();
    int sum=0, flag=1;
    while (c<'0'||c>'9'){
        if (c=='-'){
            flag=-1;
        }
        c=getchar();
    }
    while (c>='0'&&c<='9'){
        sum=(sum<<1)+(sum<<3)+(c^48);
        c=getchar();
    }
    return sum*flag;
}
const int N=2e5+1;
int fa[N];
int find(int x){
    if (fa[x]==x){
        return x;
    }
    return fa[x]=find(fa[x]);
}
int main(){
    int n=read(), m=read(), cnt=0;
    for (int i=1; i<=n*3 ;i++){
        fa[i]=i;
    }
    for (int i=1; i<=m; i++){
        int z=read(), x=read(), y=read(); 
        if (x>n||y>n){
            cnt++;
            continue;
        }
        if (z==1){
            if (find(x)==find(y+n)||find(x+n)==find(y)){
                cnt++;
                continue;
            }
            fa[find(x)]=fa[find(y)];
            fa[find(x+n)]=fa[find(y+n)];
            fa[find(x+n*2)]=fa[find(y+n*2)];
        }else{
            if (find(x)==find(y)||find(x)==find(y+n)){
                cnt++;
                continue;
            }
            fa[find(x)]=fa[find(y+n*2)];
            fa[find(x+n)]=fa[find(y)];
            fa[find(x+n*2)]=fa[find(y+n)];
        }
    }
    cout << cnt;

    return 0;
}
/*
*/