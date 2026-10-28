#include<bits/stdc++.h>
using namespace std;
string vformat(const char* fmt,va_list ap) {
    va_list ap_len;va_copy(ap_len,ap);
    int n=vsnprintf(nullptr,0,fmt,ap_len);va_end(ap_len);
    if(n<0)throw runtime_error("vsnprintf: encoding error");
    string s(n,'\0');
    if(n>0){va_list ap_out;va_copy(ap_out,ap);vsnprintf(&s[0],n+1,fmt,ap_out);va_end(ap_out);}
    return s;
}
const int _ok=0,_wa=1,_fail=-1;
void quitf(int status,const char *s,...){
	va_list ap;va_start(ap,s);string str;
	try{str=vformat(s,ap);}
	catch(...){va_end(ap);fputs("quitf: failed to format message\n",stderr);exit(-1);}
	va_end(ap);cout<<str<<endl;exit(status==_fail?1:0);
}
#define N 200004
int n,m,a[N],vis[N],mx[N],mn[N],deg[N];
struct BIT{
	int n,t[N];
	void init(int _n){n=_n;for(int i=1;i<=n;++i)t[i]=0;}
	void upd(int p,int d){for(;p<=n;p+=p&-p)t[p]+=d;}
	int qr(int p){int r=0;for(;p;p-=p&-p)r+=t[p];return r;}
}bit;
int main(int argc,char **argv){
	if(argc!=4){cout<<"Usage: ./checker river.in river.out river.ans (Linux) | checker river.in river.out river.ans (Windows)"<<endl;return 4;}
	ifstream inf(argv[1]);
	if(!inf)quitf(_fail,"Failed to open input file %s",argv[1]);
	ifstream ouf(argv[2]);
	if(!ouf)quitf(_fail,"Failed to open output file %s",argv[2]);
	ifstream ans(argv[3]);
	if(!ans)quitf(_fail,"Failed to open answer file %s",argv[3]);
	if(!(inf>>n))quitf(_fail,"Input file empty");
	if(!(2<=n&&n<=200000))quitf(_fail,"Input does not satisfy 2<=n&&n<=200000");
	if(!(ans>>m))quitf(_fail,"Answer file empty");
	if(!(ouf>>a[1]))quitf(_wa,"Output file: unexpected EOF");
	if(a[1]==-1){
		if(m==-1)quitf(_ok,"Accepted.");
		quitf(_wa,"There exists a solution, but the contestant does not find it.");
	}
	for(int i=2;i<=n;++i)if(!(ouf>>a[i]))quitf(_wa,"Output file: unexpected EOF");
	for(int i=1;i<=n;++i)if(a[i]<1||a[i]>n)quitf(_wa,"a[%d] does not fall in the range [1,n] (n=%d).",i,n);
	for(int i=1;i<=n;++i){
		if(vis[a[i]])quitf(_wa,"Duplicate value detected: a[%d] = a[%d] = %d.",vis[a[i]],i,a[i]);
		vis[a[i]]=i;
	}
	mn[1]=a[1];
	for(int i=2;i<=n;++i)mn[i]=min(mn[i-1],a[i]);
	mx[n]=a[n];
	for(int i=n-1;i>=1;--i)mx[i]=max(mx[i+1],a[i]);
	bool connected=true;
	for(int i=1;i<n;++i)if(mn[i]>=mx[i+1])connected=false;
	if(!connected)quitf(_wa,"Graph Disconnected.");
	for(int i=1;i<=n;++i)deg[i]=0;
	bit.init(n);
	for(int i=1;i<=n;++i)deg[i]+=bit.qr(a[i]-1),bit.upd(a[i],1);
	bit.init(n);
	for(int i=n;i>=1;--i)deg[i]+=bit.qr(n)-bit.qr(a[i]),bit.upd(a[i],1);
	for(int i=1;i<=n;++i)if(deg[i]&1)quitf(_wa,"Degree of node %d is %d, an odd number.",i,deg[i]);
	quitf(_ok,"Accepted.");
	return 0;
}
