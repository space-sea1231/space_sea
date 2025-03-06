#include<bits/stdc++.h>
using namespace std;
int n,m,F[105],f[105][66][66],start[70],cnt=0,gs[200];//特殊记录，不爆空间
bool mp[105][30];

int main(){
	cin>>n>>m;
	char a;	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a; 
			if(a=='H')mp[i][j]=1;//另不能选的为1
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			F[i]=(F[i]<<1)+mp[i][j];
            //把每行“不可选”状态压缩起来方便实用
		}
		printf("%d\n", F[i]);
	}
	
	start[++cnt]=0;
    /*这个尤为重要，如果你要空间时间，就得像下面一样存
    如果直接存的话，就没了（毕竟那个一整排H的数据还是有的）
    不过如果从0开始循环也可以，但是放在这里起警示作用233*/
	
	for(int i=1;i<(1<<m);i++){
		if(i&(i<<1))continue;	//因为左二右二不能选
		if(i&(i<<2))continue;
		if(i&(i>>1))continue;
		if(i&(i>>2))continue;
		start[++cnt]=i;//直接存有用的就行
		int x=i;
		while(x){		//求取每个状态的贡献
			gs[cnt]++;
			x-=(x&(-x));
		}
	}
	
	for(int i=1;i<=cnt;i++){	//处理第一排
		if((start[i]&F[1])==0){	//不能与地形冲突
			f[1][i][0]=gs[i];
		}	
	}
	
	for(int i=1;i<=cnt;i++){	//第二排
		if((start[i]&F[2])==0)
		for(int j=1;j<=cnt;j++){
			if((start[i]&start[j])==0&&(start[j]&F[1])==0){
            		//判断是否冲突
				f[2][i][j]=gs[j]+gs[i];
                printf("%d\n", f[2][i][j]);
			} 
		}
	}
	//让for来的更猛烈些吧（枚举状态）
	for(int i=3;i<=n;i++){		
		for(int j=1;j<=cnt;j++){	//当前一排状态		
			if((start[j]&F[i])==0){	
				for(int k1=1;k1<=cnt;k1++){		//上面第一排			
					if((start[j]&start[k1])==0&&(start[k1]&F[i-1])==0){						
						for(int k2=1;k2<=cnt;k2++){	//上面第二排				
							if((start[j]&start[k2])==0&&(start[k1]&start[k2])==0&&(start[k2]&F[i-2])==0){	
                            				//判断所有冲突情况
								f[i][j][k1]=max(f[i][j][k1],f[i-1][k1][k2]+gs[j]);//从之前转移过来就行
							}
						}
					}
				}
			} 	
		}
	}
	
	int ans=0;
    //所有的值都在最后1排存，用这一排的所有情况的最大值当最大值
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++){
			ans=max(ans,f[n][i][j]);
		}
	}
	cout<<ans;
}
