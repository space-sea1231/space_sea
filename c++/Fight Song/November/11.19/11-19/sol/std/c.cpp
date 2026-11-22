#include<bits/stdc++.h>
using namespace std;using ll=long long;using P=pair<int,int>;
const int MOD=998244353;int n,dp[2][(1<<12)+2],blo[2][(1<<12)+2];
struct Node{int t,a;};vector<Node> v[1002];
int main(){
	freopen("c.in","r",stdin),freopen("c.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n;
	for(int i=1,x,t,a;i<=n;i++)cin>>x>>t>>a,v[x].emplace_back(Node{t,a}),assert(t==-1||(12%t==0&&a<t));
	dp[1][(1<<12)-1]=1;
	for(int i=1;i<=min(n,10);i++){
		swap(dp[0],dp[1]),memset(dp[1],0,sizeof(dp[1]));
		for(int j=0;j<(1<<12);j++)dp[1][(j>>1)^((j&1)<<11)]=dp[0][j];
		memset(blo,0,sizeof(blo)),blo[1][0]=1;
		for(Node t:v[i]){
			swap(blo[0],blo[1]),memset(blo[1],0,sizeof(blo[1]));
			for(int i=(t.t==-1?1:t.t);i<=(t.t==-1?12:t.t);i++)if(12%i==0){
				for(int j=(t.t==-1?0:t.a);j<=(t.t==-1?i-1:t.a);j++){
					for(int p=0;p<(1<<12);p++){
						int q=p;
						for(int k=0;k<12;k++)if(k%i==j&&!((q>>k)&1))q^=(1<<k);
						(blo[1][q]+=blo[0][p])%=MOD;
					}
				}
			}
		}
		swap(dp[0],dp[1]),memset(dp[1],0,sizeof(dp[1]));
		for(int j=0;j<(1<<12);j++)if(dp[0][j])for(int k=0;k<(1<<12);k++)if(blo[1][k]){
			bool p[24], q[24];
			p[0] = p[12] = (((j >> 0) & 1) && !((k >> 0) & 1)); q[0] = q[12] = (k >> 0) & 1;
			p[1] = p[13] = (((j >> 1) & 1) && !((k >> 1) & 1)); q[1] = q[13] = (k >> 1) & 1;
			p[2] = p[14] = (((j >> 2) & 1) && !((k >> 2) & 1)); q[2] = q[14] = (k >> 2) & 1;
			p[3] = p[15] = (((j >> 3) & 1) && !((k >> 3) & 1)); q[3] = q[15] = (k >> 3) & 1;
			p[4] = p[16] = (((j >> 4) & 1) && !((k >> 4) & 1)); q[4] = q[16] = (k >> 4) & 1;
			p[5] = p[17] = (((j >> 5) & 1) && !((k >> 5) & 1)); q[5] = q[17] = (k >> 5) & 1;
			p[6] = p[18] = (((j >> 6) & 1) && !((k >> 6) & 1)); q[6] = q[18] = (k >> 6) & 1;
			p[7] = p[19] = (((j >> 7) & 1) && !((k >> 7) & 1)); q[7] = q[19] = (k >> 7) & 1;
			p[8] = p[20] = (((j >> 8) & 1) && !((k >> 8) & 1)); q[8] = q[20] = (k >> 8) & 1;
			p[9] = p[21] = (((j >> 9) & 1) && !((k >> 9) & 1)); q[9] = q[21] = (k >> 9) & 1;
			p[10] = p[22] = (((j >> 10) & 1) && !((k >> 10) & 1)); q[10] = q[22] = (k >> 10) & 1;
			p[11] = p[23] = (((j >> 11) & 1) && !((k >> 11) & 1)); q[11] = q[23] = (k >> 11) & 1;
			
			if (!q[22]) p[22] |= p[23];
			if (!q[21]) p[21] |= p[22];
			if (!q[20]) p[20] |= p[21];
			if (!q[19]) p[19] |= p[20];
			if (!q[18]) p[18] |= p[19];
			if (!q[17]) p[17] |= p[18];
			if (!q[16]) p[16] |= p[17];
			if (!q[15]) p[15] |= p[16];
			if (!q[14]) p[14] |= p[15];
			if (!q[13]) p[13] |= p[14];
			if (!q[12]) p[12] |= p[13];
			if (!q[11]) p[11] |= p[12];
			if (!q[10]) p[10] |= p[11];
			if (!q[9]) p[9] |= p[10];
			if (!q[8]) p[8] |= p[9];
			if (!q[7]) p[7] |= p[8];
			if (!q[6]) p[6] |= p[7];
			if (!q[5]) p[5] |= p[6];
			if (!q[4]) p[4] |= p[5];
			if (!q[3]) p[3] |= p[4];
			if (!q[2]) p[2] |= p[3];
			if (!q[1]) p[1] |= p[2];
			if (!q[0]) p[0] |= p[1];
			
			int res = 0;
			if (p[0]) res ^= 1 << 0;
			if (p[1]) res ^= 1 << 1;
			if (p[2]) res ^= 1 << 2;
			if (p[3]) res ^= 1 << 3;
			if (p[4]) res ^= 1 << 4;
			if (p[5]) res ^= 1 << 5;
			if (p[6]) res ^= 1 << 6;
			if (p[7]) res ^= 1 << 7;
			if (p[8]) res ^= 1 << 8;
			if (p[9]) res ^= 1 << 9;
			if (p[10]) res ^= 1 << 10;
			if (p[11]) res ^= 1 << 11;
			
			(dp[1][res] += 1LL * dp[0][j] * blo[1][k] % MOD) %= MOD;
		}
	}
	int ans=0;
	for(int i=1;i<(1<<12);i++)(ans+=dp[1][i])%=MOD;
	return cout<<ans<<"\n",0;
}
