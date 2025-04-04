#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	vector<int> q;
	q.push_back(1);
	q.push_back(2);
	for (int &v:q){
		printf("%d\n", ++v);
	}
	for (int v:q){
		printf("%d\n", v);
	}
	return 0;
}