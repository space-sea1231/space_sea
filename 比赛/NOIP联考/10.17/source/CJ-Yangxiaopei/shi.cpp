#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n;
string s;
vector<int> v;
signed main(){
	freopen("shi.in", "r", stdin);
	freopen("shi.out", "w", stdout);
	cin >> t;
	while(t--){
		cin >> s;
		n = s.size(), s = ' ' + s;
		if(n == 1){
			cout << s[1] - '0' << " " << 0;
			continue;
		}
		if(n == 2){
			cout << s[1] + s[2] - '0' - '0' << " " << 0;
			continue;
		}
		v.clear();
		for(int i = n; i >= 3; i--){
			if(s[i] == '1'){
				s[i] = '0';
				if(s[i - 1] == '0' && s[i - 2] == '0'){
					s[i - 2] = '1';
				}
				else{
					s[i - 2] = '0';
				}
				v.push_back(i - 1);
			}
		}
		if(s[2] == '0'){
			for(int i = 3 - (s[1] == '0'); i < n; i += 3){
				s[i - 1] = s[i + 1] = '1';
				v.push_back(i);
			}
		}
		else{
			for(int i = 4; i < n; i += 3){
				s[i - 1] = s[i + 1] = '1';
				v.push_back(i);
			}
		}
		int sum = 0;
		for(int i = 1; i <= n; i++){
			sum += (s[i] - '0');
		}
		cout << sum << " " << v.size();
		if(v.size()){
			cout << "\n";
		}
		for(auto i : v){
			cout << i << " ";
		}
		cout << "\n";
	}
	return 0;
}
