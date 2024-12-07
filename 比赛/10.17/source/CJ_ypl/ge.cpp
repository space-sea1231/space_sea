#include<bits/stdc++.h>
using namespace std;
const int N=20,inf=0x3f3f3f3f;
int t,n,m,p[N][N],s[N];
vector<int>st;
int main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		st.clear();
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				cin>>p[i][j];
			}
		}
		bool k=0;
		for(int i=1;i<=m;i++){
			cin>>s[i];
			if(s[i]){
				k=1;
				st.push_back(i); 
			}
		}
		if(!k){
			cout<<"NIE"<<endl;
			continue;
		}
		if(n==1){
			sort(st.begin(),st.end(),[](int a,int b){return p[a][0]<p[b][0];});
			int mmax=-inf,mmin=inf,ans=inf,cnt=1;
			for(int i=1;i<=m;i++){
				mmin=min(mmin,p[i][1]);
				mmax=max(mmax,p[i][1]);
			}
			ans=min(p[st.front()][1]-mmin+mmax-mmin,ans);
			ans=min(mmax-p[st.back()][1]+mmax-mmin,ans);
			if(p[st.front()][1]-mmin+mmax-mmin==mmax-p[st.back()][0]+mmax-mmin)cnt++;
			cout<<ans<<' '<<cnt<<endl;
			continue;
		}
		cout<<0<<' '<<0<<endl;
	}
	return 0;
}
