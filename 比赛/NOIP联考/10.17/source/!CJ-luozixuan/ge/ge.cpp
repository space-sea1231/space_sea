/*
	君指尖跃动の光は、私の一生不変の信仰に、唯私の超電磁砲永世生き！
*/

#include<bits/stdc++.h>
#define DEBUG false
#define XLTX true
#define FILE_ false

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


int main(){
	file_("",FILE_);
	t=read();
	t=1;
	while(t--){
		//code here
		//为什么不给暴力分/qd 
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

