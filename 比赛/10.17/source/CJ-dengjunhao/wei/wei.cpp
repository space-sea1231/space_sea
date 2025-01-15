#include <bits/stdc++.h>
using namespace std;
#define int long long
long long mod=(1ll<<32);
int read(){
    int ch=getchar(),x=0,f=1;
    for(;!isdigit(ch);ch=getchar())f=(ch=='-'?-1:1);
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
struct node{
    long long l,r;
};
vector<node> vec;
int a[500005],n,ans;
unordered_map<unsigned long long ,int> ma;
int get_id(int x){
    int l=0,r=vec.size()-1,ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(vec[mid].l<=x){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return ans;
}
long long get(int x,int y){
    if(x>y){
        swap(x,y);
    }
    int idl=get_id(x),idr=get_id(y);
    int Lst_ans=ans;
    if(idl==idr){
        ans-=((vec[idl].r-y+1)*(y-vec[idl].l)+(y-x-1)*(vec[idl].r-vec[idl].l+1-(y-x-1))+(x-vec[idl].l+1)*(vec[idl].r-x))/2;
        int Anss=ans;
        ans=Lst_ans;
        return Anss;
    }
    if(x==y-1){
        if(a[y]<a[x]){
            ans+=(vec[idl].r-vec[idl].l+1)*(vec[idr].r-vec[idr].l+1);
            int Anss=ans;
            ans=Lst_ans;;
            return Anss;
        }
    }
    ans-=(vec[idl].r-x+1)*(x-vec[idl].l+1)-1;
    ans-=(vec[idr].r-y+1)*(y-vec[idr].l+1)-1;
    node aab;
    aab.l=x;
    aab.r=x;
    if(x!=vec[idl].l){
        if(a[y]>=a[x-1]){
            ans+=(x-vec[idl].l)*(aab.r-aab.l+1);
            aab.l=vec[idl].l;
        }
    }
    if(x!=vec[idl].r){
        if(a[y]<=a[x+1]){
            ans+=(vec[idl].r-x)*(aab.r-aab.l+1);
            aab.r=vec[idl].r;
        }
    }
    if(x==vec[idl].l && idl>0){
        if(a[y]>=a[x-1]){
            ans+=(vec[idl-1].r-vec[idl-1].l+1)*(aab.r-aab.l+1);
            aab.l=vec[idl-1].l;
        }
    }
    node aa;
    aa.l=y;
    aa.r=y;
    if(y!=vec[idr].l){
        if(a[x]>=a[y-1]){
            ans+=(y-vec[idr].l)*(aa.r-aa.l+1);
            aa.l=vec[idr].l;
        }
    }
    if(y!=vec[idr].r){
        if(a[x]<=a[y+1]){
            ans+=(vec[idr].r-y)*(aa.r-aa.l+1);
            aa.r=vec[idr].r;
        }
    }
    if(y==vec[idr].r && idr<vec.size()-1){
        if(a[x]<=a[y+1]){
            ans+=(vec[idr+1].r-vec[idr+1].l+1)*(aa.r-aa.l+1);
            aa.r=vec[idr+1].r;
        }
    }
    // cout<<x<<' '<<y<<' '<<ans<<' '<<aab.l<<' '<<aab.r<<' '<<aa.l<<' '<<aa.r<<'\n';
    if(idr>idl+2){
        if(y==vec[idr].l && idr>0){
            if(a[x]>=a[y-1]){
                ans+=(vec[idr-1].r-vec[idr-1].l+1)*(aa.r-aa.l+1);
                aa.l=vec[idr-1].l;
            }
        }
        if(x==vec[idl].r && idl<vec.size()-1){
            if(a[y]<=a[x+1]){
                ans+=(vec[idl+1].r-vec[idl+1].l+1)*(aab.r-aab.l+1);
                aab.r=vec[idl+1].r;
            }
        }
    }else{
        if(y==vec[idr].l && idr>0 && x==vec[idl].r && idl<vec.size()-1){
            // cout<<"SBLY"<<' '<<'\n';
            if(a[x]>=a[y-1] && a[y]<=a[x+1]){
                ans+=((aa.r-aa.l+1)*(aa.r-aab.l+1-(aa.r-aa.l+1))+(y-x-1)*(aa.r-aab.l+1-(y-x-1))+(aab.r-aab.l+1)*(aa.r-aab.l+1-(aab.r-aab.l+1)))/2;
            }
        }else{
            if(y==vec[idr].l && idr>0){
                if(a[x]>=a[y-1]){
                    ans+=(vec[idr-1].r-vec[idr-1].l+1)*(aa.r-aa.l+1);
                    aa.l=vec[idr-1].l;
                }
            }
            if(x==vec[idl].r && idl<vec.size()-1){
                if(a[y]<=a[x+1]){
                    ans+=(vec[idl+1].r-vec[idl+1].l+1)*(aab.r-aab.l+1);
                    aab.r=vec[idl+1].r;
                }
            }
        }
    }
    int Anss=ans;
    ans=Lst_ans;
    // cout<<x<<' '<<
    return Anss;
}
signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    mt19937 rnd(time(0));
    int T=read();
    while(T--){
        vec.clear();
        ma.clear();
        n=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        node aa;
        aa.l=1;
        aa.r=1;
        ans=0;
        for(int i=2;i<=n;i++){
            if(a[i]>a[i-1]){
                aa.r=i;
            }else{
                ans+=(aa.r-aa.l+1)*(aa.r-aa.l)/2+aa.r-aa.l+1;
                vec.push_back(aa);
                aa.l=i;
                aa.r=i;
            }
        }
        vec.push_back(aa);
        ans+=(aa.r-aa.l+1)*(aa.r-aa.l)/2+aa.r-aa.l+1;
        ma.clear();
        int Id=n*5;
        if(n<=100){
            long long Max=ans;
            for(int i=1;i<=n;i++){
                for(int j=i+1;j<=n;j++){
                    Max=max(Max,get(i,j));
                }
            }
            cout<<Max%mod<<'\n';
        }else{
            long long Max=ans;
            while(Id--){
                long long x=rnd()%n+1,y=rnd()%n+1;
                int tim=5;
                unsigned long long HAsh=x*1299709+y;
                while(tim && (x==y || ma.find(HAsh)!=ma.end())){
                    x=rnd()%n+1;
                    y=rnd()%n+1;
                    HAsh=x*1299709+y;
                    tim--;
                }
                ma[HAsh]=1;
                // cout<<x<<' '<<y<<' '<<get(x,y)<<'\n';
                Max=max(Max,get(x,y));
            }
            cout<<Max%mod<<'\n';
        }
    }
    return 0;
}