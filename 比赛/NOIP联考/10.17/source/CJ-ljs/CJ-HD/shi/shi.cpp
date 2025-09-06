#include<bits/stdc++.h>
using namespace std;
const int M=1e6+5;
int n,m,t,a[M],ans[M*13],cnt;
string s;
int read(){
	char ch=getchar();
	while(1){
		if(ch=='0')return 0;
		if(ch=='1')return 1;
		ch=getchar();
	}
}
void work1(int x){
	ans[++cnt]=x+1,ans[++cnt]=x+2;
	a[x]=a[x+1]=a[x+2]=a[x+3]=0;
}
void sol(){
	for(int i=1;i<=n-3;i++){
		if(a[i]){
//			cout<<i<<" ";
			int x=a[i+1]*100+a[i+2]*10+a[i+3];
			if(x==101){
				work1(i);
			}
			if(x==0){
				ans[++cnt]=i+2;
				work1(i);
			}
			if(x==1){
				ans[++cnt]=i+1,ans[++cnt]=i+2;
				a[i]=a[i+1]=a[i+3]=0,a[i+2]=1;
			}
			if(x==100){
				ans[++cnt]=i+2,ans[++cnt]=i+1,ans[++cnt]=i+2;
				a[i]=a[i+1]=a[i+3]=0,a[i+2]=1;
			}
			if(x==111){
				ans[++cnt]=i+2,ans[++cnt]=i+1;
				a[i]=a[i+1]=a[i+2]=a[i+3]=0;
			}
			if(x==10){
				ans[++cnt]=i+1;
				a[i]=a[i+1]=a[i+2]=a[i+3]=0;
			}
			if(x==11){
				ans[++cnt]=i+2,ans[++cnt]=i+1;
				a[i]=a[i+1]=a[i+2]=a[i+3]=0;
			}
			if(x==110){
				ans[++cnt]=i+1,ans[++cnt]=i+2;
				a[i]=a[i+1]=a[i+2]=0,a[i+3]=1;
			}
		}
	}
	if(a[n-2]){
		ans[++cnt]=n-4,ans[++cnt]=n-3,ans[++cnt]=n-4;
		a[n-2]=0;
	}
	if(a[n-1]){
		ans[++cnt]=n-3,ans[++cnt]=n-2,ans[++cnt]=n-3;
		a[n-1]=0;
	}
	if(a[n]){
		ans[++cnt]=n-2,ans[++cnt]=n-1,ans[++cnt]=n-2;
		a[n]=0;
	} 
	for(int i=1;i<=n-5;i++){
		ans[++cnt]=i+1,ans[++cnt]=i+3,ans[++cnt]=i+2,ans[++cnt]=i+3,ans[++cnt]=i+2;
		a[i]=1;
	}
	ans[++cnt]=n-3,ans[++cnt]=n-1,ans[++cnt]=n-2;
	cout<<0<<" "<<cnt<<"\n";
	for(int i=1;i<=cnt;i++){
		printf("%d ",ans[i]);
	}
	putchar('\n');
} 
int main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	cin>>t;
	while(t--){
		cnt=0;
		s="";
		cin>>s;n=s.size();
		for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
		if(n>=5){
			int flag=1;
			for(int i=1;i<=n;i++)if(!a[i])flag=0;
			if(flag==1){
				cout<<"0 0\n";
			}
			else sol();
		}
		else{
			cout<<"0 ";
			if(n==4){
				int x=a[1]*1000+a[2]*100+a[3]*10+a[4];
				if(x==0||x==1){
					cout<<1<<"\n";
					cout<<2<<"\n";
				}
				if(x==10){
					cout<<2<<"\n";
					cout<<2<<" "<<3<<"\n";
				}
				if(x==11){
					cout<<3<<"\n";
					cout<<3<<" "<<2<<" "<<3<<"\n";
				}
				if(x==100){
					cout<<2<<"\n";
					cout<<3<<" "<<2<<"\n";
				}
				if(x==101){
					cout<<"0\n";
				}
				if(x==110){
					cout<<"3\n3 2 3\n";
				}
				if(x==111){
					cout<<"0\n";
				}
				if(x==1000){
					cout<<"1\n3\n";
				}
				if(x==1001){
					cout<<"4\n3 2 3 2\n";
				}
				if(x==1010){
					cout<<"0\n";
				}
				if(x==1011){
					cout<<"0\n";
				}
				if(x==1100){
					cout<<"3\n2 3 2\n";
				}
				if(x==1101||x==1110||x==1111){
					cout<<"0\n";
				}
			}
			if(n==3){
				int x=a[1]*100+a[2]*10+a[3];
				if(x==0){
					cout<<"1\n2\n";
				}
				if(x==1||x==10||x==11||x==100||x==101||x==110||x==111){
					cout<<"0\n";
				}
			}
			if(n==2||n==1){
				cout<<"0\n";
			}
		}
	}
	return 0;
}
