#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=4005;
int n,z;
ll S[N],V[N];
int ic[N],c[N];
unordered_map<ll,int> mp;
// vector<pair<ll,ll>> ans;
int get(ll x){return mp.count(x)?mp[x]:-1;}
bool CHK(ll P,ll Q,ll R){
    for(int i=1;i<=z;i++)c[i]=ic[i];
    // ans.clear();
    if(P+Q==0){
        if(R==0){
            for(int i=1;i<=z;i++){
                if(c[i]%2)return 0;
                // for(int j=0;j<c[i]/2;j++)ans.push_back({V[i],V[i]});
                c[i]=0;
            }
        }
    }else if(R%(P+Q)==0){
        int id=get(R/(P+Q));
        if(id!=-1){
            if(c[id]&1)return 0;
            // for(int j=0;j<c[id]/2;j++)ans.push_back({V[id],V[id]});
            c[id]=0;
        }
    }

    auto get_neighbors=[&](int idx,int& n1,int& n2){
        n1=((R-P*V[idx])%Q==0)?get((R-P*V[idx])/Q):-1;
        n2=((R-Q*V[idx])%P==0)?get((R-Q*V[idx])/P):-1;
        if(n1==idx)n1=-1;if(n2==idx)n2=-1;
    };
    auto get_deg=[&](int idx) ->int {
        int n1,n2;get_neighbors(idx,n1,n2);
        if(n1!=-1&&n2!=-1&&n1!=n2)return 2;
        return (n1!=-1||n2!=-1)?1:0;
    };

    for(int i=1;i<=z;i++){
        if(c[i]<=0)continue;
        int d=get_deg(i);
        if(d==0)return 0;
        if(d==1){
            int curr=i,prev=-1;
            while(curr!=-1){
                int n1,n2;get_neighbors(curr,n1,n2);
                int nxt=-1;
                if(n1!=-1&&n1!=prev)nxt=n1;
                else if(n2!=-1&&n2!=prev)nxt=n2;
                if(nxt==-1){
                    if(c[curr]!=0)return 0;
                    curr=-1;
                }else{
                    if(c[nxt]<c[curr])return 0;
                    int amt=c[curr];c[nxt]-=amt;c[curr]=0;
                    // for(int j=0;j<amt;j++){
                        // if(V[curr]*P+V[nxt]*Q==R)ans.push_back({V[curr],V[nxt]});
                        // else ans.push_back({V[nxt],V[curr]});
                    // }
                    prev=curr;curr=nxt;
                }
            }
        }
    }
    for(int i=1;i<=z;i++)if(c[i]>0)return 0;
    return 1;
}
bool chk(ll a1,ll b1,ll a2,ll b2){
    ll Q=a1-a2,P=b2-b1;
    if(!Q||!P)return 0;
    if(P<0)P=-P,Q=-Q;
    ll g=gcd(P,Q);P/=g;Q/=g;
    return CHK(P,Q,a1*P+b1*Q);
}
void work(){
    cin>>n;
    for(int i=1;i<=2*n;i++)cin>>S[i];
    sort(S+1,S+2*n+1);
    for(int i=1;i<=n+1;i++)if(S[i]==S[i+n-1]){
        cout<<"YES\n";
        // for(int j=1;j<i;j++)cout<<S[j]<<" "<<S[i]<<"\n";
        // for(int j=i+n;j<=2*n;j++)cout<<S[j]<<" "<<S[i]<<"\n";
        return;
    }
    z=0;mp.clear();
    for(int i=1;i<=2*n;i++){
        if(i==1||S[i]!=S[i-1])z++,V[z]=S[i],mp[S[i]]=z,ic[z]=0;
        ic[z]++;
    }
    for(int j=1;j<=z;j++){
        if(chk(V[1],V[2],V[3],V[j]) || chk(V[1],V[2],V[j],V[3])){
            cout<<"YES\n";
            // for(auto p:ans)cout<<p.first<<" "<<p.second<<"\n";
            return;
        }
    }
    for(int j=1;j<=z;j++)for(int k=1;k<=z;k++){
        if(chk(V[1],V[j],V[2],V[k]) || chk(V[1],V[j],V[k],V[2])){
            cout<<"YES\n";
            // for(auto p:ans)cout<<p.first<<" "<<p.second<<"\n";
            return;
        }
    }
    cout<<"NO\n";
}
int main(){
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    // clock_t start=clock();
    ios::sync_with_stdio(0),cin.tie(0);
    int T;cin>>T;while(T--)work();
    // clock_t end=clock();
    // cerr<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s\n";
}