#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e6+5;
const int MOD=998244353;
int t,n,tot1,tot2;
long long ans=1,xx,yy;
int vis1[MAXN],vis2[MAXN];
int pre1[MAXN],pre2[MAXN],x[MAXN],y[MAXN];
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	} 
	return x*f;
}
void print(int x){
	if(x<0){
		putchar('-');
	}
	if(x>=0 && x<=9){
		putchar(x+'0');
		return ;
	}
	print(x/10);
	putchar(x%10+'0');
}
void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		x[i]=read(),y[i]=read();
		if(x[i] && y[i]){
			vis1[x[i]]=1,vis2[x[i]]=1;
			vis1[y[i]]=1,vis2[y[i]]=1;
		}
		else if(x[i] || y[i]){
			if(y[i]){
				swap(x[i],y[i]);
			}
			vis1[x[i]]=1;
			tot2+=2,tot1+=1;
		}
		else{
			tot1+=2,tot2+=2;
		}
	}
	int mid=0,cnt1=0,cnt2=0;
	for(int i=1;i<=2*n;i++){
		if(!vis2[i]){
			cnt2++;
			pre2[cnt2]=i;
			if(cnt2==tot2/2){
				mid=i;
			}
		}
	}
	for(int i=1;i<=2*n;i++){
		if(!vis1[i]){
//			cout<<i<<endl;
			cnt1++;
			pre1[cnt1]=i;
			if(i<=mid){
				xx++;
			}
			else{
				yy++;
			}
		}
	}
//	cout<<xx<<" "<<yy<<endl;
	for(int i=1;i<=n;i++){
		if(x[i] && y[i]){
			continue;
		}
		else if(x[i]){
			if(x[i]<=mid){
				ans=ans*yy%MOD;
				yy--;
			}
			else{
				ans=ans*xx%MOD;
				xx--;
			}
		}
		else{
			ans=ans*xx%MOD*yy%MOD*2%MOD;
			xx--,yy--;
		}
	}
//	cout<<xx<<" "<<yy<<endl;
	print(ans),puts("");
}
void clean(){
	tot1=0,tot2=0,ans=1,xx=0,yy=0;
	for(int i=1;i<=2*n;i++){
		vis1[i]=vis2[i]=pre1[i]=pre2[i]=x[i]=y[i]=0;
	}
}
int main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	t=read();
	while(t--){
		solve();
		clean();
	}
}
