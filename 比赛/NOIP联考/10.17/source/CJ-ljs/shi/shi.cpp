#include<bits/stdc++.h>
using namespace std;
int T,n,cnt;
string s;
vector<int>ans;
void solve1(){
	if(s=="#000#")
		cout<<"2 1\n2\n";
	else if(n==3)
		cout<<cnt<<" 0\n\n";
	else if(s=="#0000#")
		cout<<"2 1\n2\n";
	else if(s=="#0001#")
		cout<<"3 1\n2\n";
	else if(s=="#0010#")
		cout<<"3 2\n2 3\n";
	else if(s=="#0011#")
		cout<<"3 3\n3 2 3\n";
	else if(s=="#0100#")
		cout<<"3 2\n3 2\n";
	else if(s=="#0101#")
		cout<<"2 0\n\n";
	else if(s=="#0110#")
		cout<<"3 3\n3 2 3\n";
	else if(s=="#1000#")
		cout<<"3 1\n3\n";
	else if(s=="#1001#")
		cout<<"3 4\n2 3 2 3\n";
	else if(s=="#1010#")
		cout<<"2 0\n\n";
	else if(s=="#1100#")
		cout<<"3 3\n2 3 2\n";
	else
		assert(0);
}
void work(int p){
	ans.emplace_back(p);
	if(s[p]=='0')
		s[p-1]^=1,s[p+1]^=1;
	else
		s[p-1]=s[p+1]='0';
}
void check(int&l,int&r){
	while(s[l-1]=='0')
		l--;
	while(s[r+1]=='0')
		r++;
}
void changel(int p,int len){
	if(len==1)
		work(p+1),work(p),work(p+1);
	else if(len==2)
		work(p-1),work(p),work(p-1),work(p),work(p-1);
	else
		work(p-1),work(p-2);
}
void changer(int p,int len){
	if(len==1)
		work(p-1),work(p),work(p-1);
	else if(len==2)
		work(p+1),work(p),work(p+1),work(p),work(p+1);
	else
		work(p+1),work(p+2);
}
void solve2(int p){
	int l=p,r=p;
	check(l,r);
	if(l==r)
		work(l),check(l,r);
	if(l+1==r){
		if(l==1)
			work(2),l=2,r=3;
		work(r),work(l),work(r),l--;
	}
	while(l!=1||r!=n){
		for(p=l-1;p>=1;p--)
			if(s[p]!='1')
				break;
		while(l-3>p)
			changel(l,3),l-=3;
		if(l==p+2)
			changel(l,1),l--;
		else if(l==p+3)
			changel(l,2),l-=2;
		check(l,r);
		for(p=r+1;p<=n;p++)
			if(s[p]!='1')
				break;
		while(r+3<p)
			changer(r,3),r+=3;
		if(r==p-2)
			changer(r,1),r++;
		else if(r==p-3)
			changer(r,2),r+=2;
		check(l,r);
	}
}
int main(){
	freopen("shi.in","r",stdin),freopen("shi.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cin>>T;
	while(T--){
		cin>>s,n=s.size(),s='#'+s+'#',ans.clear(),cnt=0;
		for(int i=1;i<=n;i++)
			cnt+=s[i]^48;
		if(cnt>=n-1||n<=2){
			cout<<cnt<<" 0\n\n";
			continue;
		}
		if(n<=4){
			solve1();
			continue;
		}
		if(cnt==n-2&&s[1]=='0'&&s[n]=='0')
			work(2),s[3]='0';
		for(int i=2;i<n;i++)
			if(s[i]=='0'){
				solve2(i);
				break;
			}
		work(2),work(4),work(3);
		for(int i=6;i<=n;i++)
			work(i-2),work(i-1),work(i-2);
		cout<<n-1<<' '<<ans.size()<<'\n';
		for(int x:ans)
			cout<<x<<' ';
		cout<<'\n';
	}
	return 0;
}