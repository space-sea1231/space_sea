#include<bits/stdc++.h>
#define FAST true
#define FIO true
#define DEBUG false
using namespace std;
#if FIO
void fio(string s,int i=0){
    freopen(((s+(i?to_string(i):""))+".in").c_str(),"r",stdin);
    freopen(((s+(i?to_string(i):""))+".out").c_str(),"w",stdout);
}
#endif
#define int long long
//#define int unsigned int
//#define int __int128
#if DEBUG
bool Memory_start;
void debug();
#endif
#if FAST
inline int read(){
    char c=getchar();
    int ret=0,f=1;
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        ret=(ret<<3)+(ret<<1)+c-'0';
        c=getchar();
    }return ret*f;
}
inline void write(int x,int op=0){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10,0);
    putchar((char)(x%10+'0'));
    if(op){
        if(op>0)puts("");
        if(op<0)putchar(' ');
        if(op==0)puts("114514");
    }
}
#endif
const int N=1e6+10,mod=998244353ll;
int T;
int n,ans;
bool flag;
int a[N<<1];
bool f[N<<1];
vector<int>v;
int cnt1,cnt2;
signed main(){
    fio("wo");
    T=read();
    while(T--){
        v.clear();
        cnt1=0,cnt2=0;
        memset(f,0,sizeof f);
        n=read();
        ans=1,flag=1;
        for(int i=1;i<=(n<<1);i++){
            a[i]=read();
            f[a[i]]=1;
            if(i&1)continue;
            if(flag&&a[i]&&a[i-1]&&((a[i]<=n&&a[i-1]<=n)||(a[i]>n&&a[i-1]>n))){
                flag=0;
            }
        }
        for(int i=1;i<=(n<<1);i++){
            if(!f[i])v.push_back(i);
            else{
                if(i<=n)cnt1++;
                else cnt2++;
            }
        }
        if(flag){
            cnt1=cnt2=0;
            for(int i=1;i<=(n<<1);i++){
                if(!f[i]){
                    if(i<=n)cnt1++;
                    else cnt2++;
                }
            }
        } else{
            if(v.size()&1){
                if(cnt1>=cnt2)cnt1=0,cnt2=1;
                else cnt1=1,cnt2=0;
                cnt1=0,cnt2=1;
            } else cnt1=cnt2=0;
            cnt1+=v.size()>>1,cnt2+=v.size()>>1;
        }
        for(int i=1;i<=(n<<1);i+=2){
            if(a[i]&&a[i+1])continue;
            if(a[i]){
                if(a[i]<=n)ans=(ans*(cnt2?cnt2--:cnt1--))%mod;
                else ans=(ans*(cnt1?cnt1--:cnt2--))%mod;
            } else if(a[i+1]){
                if(a[i+1]<=n)ans=(ans*(cnt2?cnt2--:cnt1--))%mod;
                else ans=(ans*(cnt1?cnt1--:cnt2--))%mod;
            } else ans=ans*(cnt1&&cnt2?2ll:1ll)%mod*(cnt1?cnt1--:cnt2--)%mod*(cnt2?cnt2--:cnt1--)%mod;
        }write(ans%mod,1);
    }
#if DEBUG
    debug();
#endif
    return 0;
}
#if DEBUG
bool Memory_end;
void debug(){
    cerr<<"Time: "<<clock()<<" ms\n";
    cerr<<fixed<<setprecision(6)<<"Memory: "<<abs(&Memory_start-&Memory_end)/1024.0/1024.0<<" MB";
}
#endif