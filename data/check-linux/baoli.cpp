#include <bits/stdc++.h>
using namespace std;
long long gcd(long long x, long long y){
	if(y==0)
		return x;
	return gcd(y, x%y);
}
long long lcm(long long x, long long y){
	return x*y/gcd(x, y);
}
int main(){
    int n;
	cin >> n;
	while(n--){
		long long sum=0, a, b, c, d;
		cin >> a >> b >> c >> d;
		for(long long i=1; i*i<=d; i++){
			if(!(d%i)){
				if(gcd(i, a)==b&&lcm(i, c)==d){
                    sum++;
                }
				if(d/i!=i){
                    if(gcd(d/i, a)==b&&lcm(d/i, c)==d){
                        sum++;
                    }
                }
			}
		}
		cout << sum << endl;
	}

	return 0;
}