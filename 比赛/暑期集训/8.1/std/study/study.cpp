#include <iostream>
#include <vector>
using namespace std;
using ll=long long;

int main(){
	freopen("study.in","r",stdin);
	freopen("study.out","w",stdout);
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	ll N,M;
	cin>>N>>M;
	vector<ll> A(N),B(N);
	for(ll& a:A) cin>>a;
	for(ll& b:B) cin>>b;
	for(ll i=0; i<N; i++) A[i]=max(A[i],B[i]);

	ll ok=0,ng=1LL<<60;
	auto check=[&](ll x) -> bool {
		ll day=0;
		for(ll i=0; i<N; i++){
			if(x<=A[i]*M) day+=(x+A[i]-1)/A[i];
			else day+=M+(x-A[i]*M+B[i]-1)/B[i];
			if(day>N*M) return 0;
		}
		return 1;
		};
	while(ng-ok>1){
		const ll mid=(ng+ok)/2;
		if(check(mid)) ok=mid;
		else ng=mid;
	}
	cout<<ok<<endl;
}