#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
int n,a[1000010],x;
long long good,baad;
char s[1000010],t;
map<int,int>mp1,mp2;
int main(int argc,char* argv[]){
	registerTestlibCmd(argc, argv);
	n=inf.readInt();
	for(int i=1;i<=n;i++)a[i]=inf.readInt(),mp1[a[i]]++,mp2[a[i]]++;
	string S=inf.readToken();
	for(int i=1;i<=n;i++)s[i]=S[i-1];
	good=baad=0;
	for(int i=1;i<=n;i++){
		x=ouf.readInt(),t=ouf.readChar(),t=ouf.readChar(),mp1[x]--;
		if(t!='G'&&t!='B')quitf(_wa,"Some of your problem is not good problem or bad problem.");
		if(mp2[x]==0)quitf(_wa,"Some of your problem is not exist.");
		if(mp1[x]==-1)quitf(_wa,"Some of your problem is same as before.");
		if(t=='G')good+=x;
		else baad+=x;
		if(s[i]=='G'&&good<baad)quitf(_wa,"Except good but your solution is bad.");
		if(s[i]=='B'&&good>=baad)quitf(_wa,"Except bad but your solution is good.");
	}
	quitf(_ok,"Your solution is good.");
	return 0;
}
