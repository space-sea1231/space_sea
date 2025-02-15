/*
	君指尖跃动の光は、私の一生不変の信仰に、唯私の超電磁砲永世生き！
*/

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define DEBUG false
#define XLTX true
#define FILE_ true

#if DEBUG
	bool Memory_Start;
    void Deb();

#endif

#if XLTX
	inline int read(){
		int s=0;
		int w=1;
		char ch=getchar();
		for(;ch<'0'||ch>'9';ch=getchar())
	    	if(ch=='-')
				w=-1;
		for(;ch>='0' and ch<='9';ch=getchar())
			s=s*10+ch-'0';
		return s*w;
	}
	void write(int x){
		if(x<0){
			putchar('-');
			x=-x;
		}
		if(x>9)
	    	write(x/10);
		putchar(x%10+'0');
		return;
	}
#else
	inline int read(){
		int reader;
		std::cin>>reader;
		return reader;
	}
	void write(int x){
		std::cout<<x;
		return;
	}
#endif

void file_(std::string s,bool flag){
	if(not flag)
		return;
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
	return;
}

int qpow(int b,int p){
	int ans=1;
	while(p){
		if(p bitand 1)
			ans=ans*b%mod;
		b=b*b%mod;
		p>>=1;
	}
	return ans;
}
int t;
int n;
int a[1000086];
int b[1000086];
bool vis[2000086];
int ans1,ans2;
int q[2000086];
int pt;
signed main(){
	file_("wo",FILE_);
	t=read();
//	t=1;
	while(t--){
		//code here
		memset(vis,false,sizeof vis);
		pt=0;
		n=read();
		int cnt=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			b[i]=read();
			vis[a[i]]=true;
			vis[b[i]]=true;
			if((not a[i]) and (not b[i]))
				cnt++;
		}
		for(int i=1;i<=(n<<1);i++)
			if(vis[i]);
			else
				q[++pt]=i;
		int point=pt>>1;
//		std::cout<<point<<"\n";
		for(int i=1;i<=n;i++)
			if(a[i] and b[i])
				if(a[i]>q[point] and b[i]>q[point])
					point--;
				else if(a[i]<q[point] and b[i]<q[point])
					point++;
				else;
			else;
		int l=point;
		int r=pt-point;
//		std::cout<<l<<" "<<r<<"\n";
		ans1=1;
		for(int i=1;i<=n;i++){
			if(a[i] and (not b[i]))
				if(a[i]<q[point]){
					ans1=ans1*r%mod;
					r--;
				}
				else{
					ans1=ans1*l%mod;
					l--;
				}
			else if(b[i] and (not a[i]))
				if(b[i]<q[point]){
					ans1=ans1*r%mod;
					r--;
				}
				else{
					ans1=ans1*l%mod;
					l--;
				}
			else if((not a[i]) and (not b[i])){
				ans1=ans1*r%mod*l%mod*2%mod;
				l--;
				r--;
			}
			else;
//			std::cout<<l<<" "<<r<<" "<<ans<<"\n";
		}
		point=(pt)>>1;
		point++;
//		std::cout<<point<<"\n";
		for(int i=1;i<=n;i++)
			if(a[i] and b[i])
				if(a[i]>q[point] and b[i]>q[point])
					point--;
				else if(a[i]<q[point] and b[i]<q[point])
					point++;
				else;
			else;
		l=point;
		r=pt-point;
//		std::cout<<l<<" "<<r<<"\n";
		ans2=1;
		for(int i=1;i<=n;i++){
			if(a[i] and (not b[i]))
				if(a[i]<q[point]){
					ans2=ans2*r%mod;
					r--;
				}
				else{
					ans2=ans2*l%mod;
					l--;
				}
			else if(b[i] and (not a[i]))
				if(b[i]<q[point]){
					ans2=ans2*r%mod;
					r--;
				}
				else{
					ans2=ans2*l%mod;
					l--;
				}
			else if((not a[i]) and (not b[i])){
				ans2=ans2*r%mod*l%mod*2%mod;
				l--;
				r--;
			}
			else;
//			std::cout<<l<<" "<<r<<" "<<ans<<"\n";
		}
		std::cout<<std::max(ans1,ans2)<<"\n";;
					
	}


#if DEBUG
    Deb();
#endif
    return 0;
}
#if DEBUG
bool Memory_End;
void Deb(){
	std::cout<<"\n\n=========================================\nTime: "<<clock()<<" ms\nMemory: "<<abs(&Memory_End-&Memory_Start)/1024.0/1024.0<<" Mb";
	return;
}
#endif

//Tachibana27 done it ...

