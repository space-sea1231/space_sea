#include <bits/stdc++.h>
#define MOD 998244353
int N,M,a[10][10],f1[20],cl[20],f[20][20],f2[20][20],ff[(1<<18)+5],aa[20],ff2[20],
dd[(1<<18)+5],aaa[(1<<18)+5],ll[(1<<18)+5],cid;
unsigned long long dp[(1<<18)+5];
char s[10][10],h[10][10];
int cl1(int x) {
    if(f1[x]==ff2[x]) return 1;
    return MOD-f1[x];
}
int cl2(int x) {
    if(f1[x]==ff2[x]) return f1[x]+1;
    return 0;
}
int cl3(int x) {
    return 1;
}
signed main(void) {
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    scanf("%d %d %d",&cid,&N,&M);
    for(int i=1;i<=N;i++) {
        scanf("%s",s[i]+1);
        for(int j=1;j<=M;j++) {
            a[i][j]=s[i][j]-'0';
        }
    }
    for(int i=1;i<=N;i++) f1[i+1]=M,ff2[i+1]=M,cl[i+1]=2;
    for(int i=1;i<=M;i++) f1[i+N+1]=N,ff2[i+N+1]=N,cl[i+N+1]=3;
    for(int i=1;i<=N;i++) {
        scanf("%s",h[i]+1);
        for(int j=1;j<=M;j++) {
            if(h[i][j]=='0') a[i][j]-=(a[i][j]&2),f1[i+1]--,f1[j+N+1]--;
            else a[i][j]-=(a[i][j]&1);
        }
    }
    cl[1]=1;cl[N+M+2]=4;
    for(int i=1;i<=N+M+2;i++) {
        for(int j=1;j<=N+M+2;j++) {
            if(i==j) continue;
            if(cl[i]==1&&cl[j]==4) {
                f[i][j]=0;
                f2[i][j]=0;
                continue;
            }
            if(cl[i]==4&&cl[j]==1) {
                f[i][j]=0;
                f2[i][j]=1;
                continue;
            }
            if(abs(cl[i]-cl[j])!=1) {
                f[i][j]=f2[i][j]=1;
                continue;
            }
            //suan f
            if(cl[i]<cl[j]) {
                if(cl[i]==1||cl[j]==4) {
                    if(cl[i]==1) f[i][j]=cl1(j);
                    else f[i][j]=cl1(i);
                } else {
                    if(a[i-1][j-N-1]&3) {
                        f[i][j]=1;
                    } else {
                        f[i][j]=0;
                    }
                }
            } else {
                f[i][j]=1;
            }
            //suan f2
            if(cl[i]<cl[j]) {
                if(cl[i]==1) {
                    f2[i][j]=cl2(j);
                } else if(cl[j]==4){
                    f2[i][j]=cl2(i);
                } else {
                    int ct=0;
                    if(a[i-1][j-N-1]&3) {
                        ct++;
                    } 
                    if((a[i-1][j-N-1]&4)&&h[i-1][j-N-1]=='1') {
                        ct++;
                    } 
                    f2[i][j]=ct;
                }
            } else {
                if(cl[i]==4) {
                    f2[i][j]=cl3(j);
                } else if(cl[j]==1){
                    f2[i][j]=cl3(i);
                } else {
                    int ct=0;
                    if(a[j-1][i-N-1]&3) {
                        ct++;
                    } 
                    if((a[j-1][i-N-1]&4)&&h[j-1][i-N-1]=='0') {
                        ct++;
                    } 
                    f2[i][j]=ct;
                }
            }
        }
    }
    ff[0]=MOD-1;
    for(int i=1;i<(1<<N+M+2);i++) {
        ll[i]=std::__lg(i&(-i))+1;
        for(int j=1;j<=N+M+2;j++) {
            if((i>>j-1)&1) {
                int az=ff[i-(1<<j-1)];
                for(int k=j+1;k<=N+M+2;k++) {
                    if((i>>k-1)&1) az=1ll*az*f[j][k]%MOD;
                }
                ff[i]=(MOD-az)%MOD;break;
            }
        }
    }
    dp[0]=1;
    for(int i=0;i+1<(1<<N+M+2);i++) {
        int st=(1<<N+M+2)-i-1;
        dp[i]%=MOD;
//        printf("%d %d\n",i,dp[i]);
        if(dp[i]==0) continue;
        for(int x=1;x<=N+M+2;x++) aa[x]=1;
        int qqq=0;
        for(int x=1;x<=N+M+2;x++) {
            if(((i>>x-1)&1)==0) {
                aaa[++qqq]=x;
            }
        }
        for(int x=1;x<=N+M+2;x++) {
            if(((i>>x-1)&1)) {
                for(int y=1;y<=qqq;y++) {
                    aa[aaa[y]]=1ll*aa[aaa[y]]*f2[x][aaa[y]]%MOD;
                }
            }
        }
        dd[0]=1;
        for(int j=st&(st-1);j!=-1;) {
            int uu=st-j;
            if(j) j=st&(j-1);else j=-1;
            if(ff[uu]==0) continue;
            int x=ll[uu];
            dd[uu]=1ll*aa[x]*dd[uu-(1<<x-1)]%MOD;
            dp[i+uu]=(dp[i+uu]+dp[i]*ff[uu]%MOD*dd[uu]);
            if(dp[i+uu]>=17000000000000000000llu) dp[i+uu]%=MOD;
        }
    }
    printf("%llu",dp[(1<<N+M+2)-1]%MOD);
}