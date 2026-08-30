#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a), i##ABRACADABRA = (b); i <= i##ABRACADABRA; i++)
using namespace std;
using ll = long long;

struct node{
  ll k,b;
  friend node operator+(node u,node v){
    return {u.k*v.k,u.k*v.b+u.b};
  }
}A[1000010];
ll ans[1000010];
int fa[1000010];
bool known[1000010];
int n,m;

int ff(int x){
  if (fa[x]==x)return x;
  int f=ff(fa[x]);
  A[x]=A[x]+A[fa[x]];
  return fa[x]=f;
}
void mg(int x,int y,ll c){
  int fx=ff(x),fy=ff(y);
  c-=A[x].b,c-=A[y].b;
  if (known[fy])swap(fx,fy),swap(x,y);
  fa[fy]=fx;
  A[fy]={-A[x].k/A[y].k,c/A[y].k};
}
ll ask(int i){
  return A[i].k*ans[ff(i)]+A[i].b;
}

void solve(){
  cin>>n>>m;
  rep(i,0,n+1)fa[i]=i,known[i]=0,A[i]={1,0},ans[i]=0;
  int lst=0;
  while (m--){
    int i,j;
    ll c;
    cin>>i>>j>>c;
    i=(i+lst-1)%n+1;
    j=(j+lst-1)%n+1;
    c=(c+lst)%1000000000+1;
    c<<=1,ff(i),ff(j);
    if (known[ff(i)]&&known[ff(j)]){
      if (ask(i)+ask(j)==c)cout<<"Yes\n",++lst;
      else cout<<"No\n";
    }else if (ff(i)==ff(j)){
      if (A[i].k!=A[j].k){
        if (A[i].b+A[j].b==c){
          cout<<"Yes\n",++lst;
        }else cout<<"No\n";
      }else{
        known[ff(i)]=1;
        ans[ff(i)]=(c-A[i].b-A[j].b)/(A[i].k+A[j].k);
        cout<<"Yes\n",++lst;
      }
    }else{
      mg(i,j,c);
      cout<<"Yes\n",++lst;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin>>tt;
  while (tt--)solve();
  return 0;
}