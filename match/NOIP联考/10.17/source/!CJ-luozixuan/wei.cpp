/*
	君指尖跃动の光は、私の一生不変の信仰に、唯私の超電磁砲永世生き！
*/

#include<bits/stdc++.h>

#define int long long
#define DEBUG false
#define XLTX true
#define FILE_ true
#define mod (1LL<<32)

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

int t;

int n;
int a[400086];
class node{
	public:
		int l;
		int r;
		int kkk;
//		friend bool operator<(node a,node b){
////			return a.r-a.l<b.r-b.l;
//			return a.r>b.r;
//		}
};
int ans;
//std::priority_queue<node>q;
node q[400086];
int point;
int b[400086];
signed main(){
	file_("wei",FILE_);
	t=read();
//	t=1;
	while(t--){
		//code here
		n=read();
		ans=0;
		for(int i=1;i<=n;i++)
			a[i]=read();
		int qwq=1;
		for(int i=1;i<=n+1;i++)
			if(a[i]<a[i-1]){
				ans+=((i-qwq+1)*(i-qwq)>>1);
				q[++point]=(node){qwq,i-1,(i-qwq+1)*(i-qwq)>>1};
				b[qwq]=i-1;
				qwq=i;
			}
		int lll=ans;
		for(int i=1;i<=point;i++){
//			node awa=q[i];
//			int lr=q[i].r;
//			int rl=q[i+1].l;
			if(q[i+1].l==q[i+1].r and q[i].l==q[i].r)
				ans=std::max(ans,lll+1);
			else if(q[i+1].l==q[i+1].r)
				if(a[q[i].r-1]<a[q[i].r+1])
					ans=std::max(ans,lll+(((q[i+1].r-q[i].l+1)*(q[i+1].r-q[i].l+2))>>1)-q[i].ans-q[i+1].ans);
				else;
			else if(q[i].l==q[i].r)
				if(a[q[i].r]<a[q[i+1].l+1])
					ans=std::max(ans,((q[i+1].r-q[i].l+1)*(q[i+1].r-q[i].l+2)>>1)-q[i].ans-q[i+1].ans);
			else{
				if(a[q[i].r]<a[q[i+1].l+1])
					if(a[q[i+1].l]>a[q[i].r-1])//perfect!
						ans=std::max(ans,lll+((q[i+1].r-q[i].l+1)*(q[i+1].r-q[i].l+2)>>1)-q[i].ans-q[i+1].ans);
					else;
				else
					if(a[q[i].r])
			}
			} 
		}
//		for(int i=1;i<=n;i++)
//			std::cout<<b[i]<<" ";
//		node awa=q.top();
//		q.pop();
//		while(not q.empty()){
//			
//		}
//		while(not q.empty()){
//			std::cout<<q.top().l<<" "<<q.top().r<<"\n";
//			q.pop();
//		}
		std::cout<<ans<<"\n";
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

