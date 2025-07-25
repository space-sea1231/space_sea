#include <bits/stdc++.h>
using namespace std;
const int N=60;
int sum[N], top;
string s;
int go(int x, int y, char z){
	if (z=='+'){
		return x+y;
	}
	if (z=='-'){
		return x-y;
	}
	if (z=='*'){
		return x*y;
	}
	if (z=='/'){
		return x/y;
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
    cin >> s;
	int tmp=0;
    for(int k=0; k<s.size()-1; k++){
		if(s[k]=='.'){
    		sum[++top]=tmp;
    		tmp=0;
		}else if(s[k]<='9'&&s[k]>='0'){
    		tmp=(tmp<<1)+(tmp<<3)+(s[k]^48);
		}else{
			int x=sum[top--];
			int y=sum[top--];
			sum[++top]=go(y, x, s[k]);
		}
	}
	printf("%d", sum[top]);

	return 0;
}