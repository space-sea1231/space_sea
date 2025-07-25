#include <bits/stdc++.h>
using namespace std;
stack<unsigned long long> q;
int m,n;
unsigned long long a;
string s;
int main(){
	cin>>n;
	while(n--){
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>s;
			if(s=="push") {
				cin>>a;
				q.push(a);
			}
			if(s=="po") {
				if(q.empty()) cout<<"Empty"<<endl;
				else q.pop();
			}
			
			if(s=="query") {
				if(q.empty()) cout<<"Anguei!"<<endl;
				else cout<<q.top()<<endl;
			}
			
			if(s=="size") {
				cout<<q.size()<<endl;
			}
		}
	}
	return 0;
}
