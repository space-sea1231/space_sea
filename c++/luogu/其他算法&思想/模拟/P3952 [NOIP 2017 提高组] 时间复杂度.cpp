#include <bits/stdc++.h>
using namespace std;
int T;
bool vis[26], vis_1[26];
int n, r, l, w, maxn, cnt, cf, start;//cf(次方)
bool flag_1=0, flag_2=0, flag_3=0;//错误 
char now=' ';
string s, b, c;
int get(string a){
	int sum=0, len=a.size();
	for (int i=0; i<len; i++){
		sum*=10;
		sum+=a[i]-'0';
	}
	return sum;
}
void Init(){
	l=0, maxn=0, cnt=0, cf=0;
	r=s.find(' ', l)
	n=get(s.substr(l, r-l));
	memset(vis, 0, sizeof(vis));
	memset(vis_1, 0, sizeof(vis_1));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
	cin >> T;
	while (T--){
		getline(cin, s);
		Init();
		if (s[r+3]=='1') w=0;
        else{
			l=r+5;
			r=s.find(')', l);
			w=get(s.substr(l, r-l));
		}
		stack<char> q;//存储循环节 
		while (n--){
			flag_3=0;
			getline(cin, s);
			if (flag_1) continue;//该程序已经出现错误 
			if (s[0]=='F'){//循环节代码 
				int a=s[2]-'a';//当前的循环变量 
				if (vis[a]){//重复 
					flag_1=1;//程序错误 
					continue;
				}
				vis[a]=1;//标记一下（已经用过）
				q.push(s[2]);//储存一下（回溯用） 
				cnt++;//循环数量 
				if (flag_2) continue;//当前循环的外循环不会被执行 
				if (s[4]=='n') flag_3=1;//循环起始位是n 
				if (!flag_3){//循环起始位不是n 
					l=4, r=s.find(' ', l); 
					b=s.substr(l, r-l);
					start=get(b);
				}else l=r=5;//循环起始位是n  
				if (s[r+1]=='n'){//循环终结位是n 
					if (!flag_3){//不是常数项循环 
						cf++;
						vis_1[a]=1;
					}
				}else{
					if (flag_3){
						now=a+'a';
						flag_2=1;
						continue;
					} 
					l=r+1;
					c=s.substr(l);
					int end=get(c);
					if (start>end){//也不用执行了 
						flag_2=1;
						now=a+'a';
					}
				}
			}else{//退出循环代码 
				maxn=max(maxn, cf);
				cnt--;
				if (cnt<0) flag_1=1;
				if (flag_1) continue;
				if (q.top()==now){
					flag_2=0;
					now=' ';
				}
				if (vis_1[q.top()-'a']){
					vis_1[q.top()-'a']=0;
					cf--;
				}
				vis[q.top()-'a']=0;
				q.pop();
			}
		}
		if (cnt!=0) cout << "ERR" << endl;
		else if (flag_1) cout << "ERR" << endl;
		else if (w==maxn) cout << "Yes" << endl;
		else cout << "No" << endl;
	}

	return 0;
}