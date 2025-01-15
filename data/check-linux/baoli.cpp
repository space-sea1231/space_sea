#include <bits/stdc++.h>
using namespace std;
int n, a, b;
priority_queue<int, vector<int>, greater<int> > q;
int main(){
	cin >> n;
	for (int i=0; i<n; i++){
		cin >> a;
		if (a==1){
			cin >> b;
			q.push(b);
			
		}
		if (a==2){
			cout << q.top() << endl;
			
		}
		if (a==3){
			q.pop();
			
		}
	}
	
	return 0;
}