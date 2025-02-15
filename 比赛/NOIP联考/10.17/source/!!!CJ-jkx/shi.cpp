#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[2000005];
string s;
vector<int> ans;
void upd(int x){
	ans.push_back(x);
	a[x-1]=!(a[x]|a[x-1]);
	a[x+1]=!(a[x]|a[x+1]);
	return;
}
void help(){
	int lt=1,rt=n;
	while(rt-lt+1>5){
		if(a[lt]==1) lt++;
		else if(a[lt+1]==1) upd(lt+2),upd(lt+1),lt++;
		else upd(lt+1),lt++;
	}
	if(rt-lt+1==5){
		if(!a[lt]){
			if(a[lt+1]==1) upd(lt+2),upd(lt+1);
			else upd(lt+1);
		}
		if(a[lt+1]!=a[lt+3]||a[lt+2]!=a[lt+4]) lt++;
		else if(a[lt+1]==1&&a[lt+2]==1) lt++;
		else if(a[lt+1]==0&&a[lt+2]==1) upd(rt-1),upd(lt+2),upd(lt+1),upd(lt+2),upd(lt+1),lt++;
		else if(a[lt+1]==1&&a[lt+2]==0) upd(lt+1),upd(lt+2),upd(lt+1),lt++;
		else upd(lt+2),upd(lt+1),upd(lt+2),upd(lt+1),lt++;
	}
	if(rt-lt+1<=2) return;
	else if(rt-lt+1==3){
		int val1=a[lt],val2=a[lt+1],val3=a[rt];
		if(val1==0&&val2==0&&val3==0) ans.push_back(lt+1);
		return;
	}
	else if(rt-lt+1==4){
		int val1=a[lt],val2=a[lt+1],val3=a[lt+2],val4=a[lt+3];
		if(val1+val2+val3+val4>=3) return;
		if(val1==1&&val2==1) upd(lt+1),upd(rt-1),upd(lt+1);
		else if(val1==1&&val3==1) return;
		else if(val1==1&&val4==1) upd(rt-1),upd(lt+1),upd(rt-1),upd(lt+1);
		else if(val2==1&&val3==1) upd(lt+1),upd(rt-1),upd(lt+1);
		else if(val2==1&&val4==1) return;
		else if(val3==1&&val4==1) upd(rt-1),upd(lt+1),upd(rt-1);
		else if(val1==1) upd(rt-1);
		else if(val2==1) upd(rt-1),upd(lt+1);
		else if(val3==1) upd(lt+1),upd(rt-1);
		else if(val4==1) upd(lt+1);
		else upd(lt+1);
		return;
	}
}
void solve(){
	cin>>s;
	n=s.size();
	for(int i=1; i<=n; i++) a[i]=s[i-1]-'0';
	ans.clear();
	help();
	int val=0;
	for(int i=1; i<=n; i++) val+=a[i];
	cout<<val<<' '<<ans.size()<<'\n';
	for(int x:ans) cout<<x<<' ';
	cout<<'\n';
	return;
}
signed main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) solve();
	return 0;
}