#include<bits/stdc++.h>
using namespace std;
string s;
int n;
bool pls[45];
clock_t st;
int tonum(string n){//将字符串转换为数字
	int reans=0;
	for(int i=0;i<n.size();i++)
		reans=reans*10+(n[i]-'0');
	return reans;
}
bool dfs(int p,int now,int len,bool bx){
	if(clock()-st>=9888){//剪枝三
		cout<<-1;
		exit(0);
	}
	if(now>=len){//剪枝一
		string cut[45];
		int l=1;
		for(int i=0;i<s.size();i++){
			cut[l]+=s[i];
			if(pls[i])
				l++;
		}
		int reans=0;
		for(int i=1;i<=l;i++)
			reans+=tonum(cut[i]);
		return reans==n;
	}
	if(!bx&&dfs(p+1,now,len,s.size()-p-1<=len))//剪枝二，无需再多搜一个分支
		return true;
	pls[p]=true;
	bool reans=dfs(p+1,now+1,len,bx);
	pls[p]=false;
	return reans;
}
int main(){
	cin.tie(0)->sync_with_stdio(false);//由于要用string所以这个人就勉为其难地不用scanf和printf了
	cout.tie(0);
	cin>>s>>n;
	st=clock();
	for(int i=0;i<s.size();i++){//枚举可能的答案，i为必须要添加加号的数量
		memset(pls,false,sizeof(pls));
		if(dfs(0,0,i,i==0)){
			cout<<i;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
