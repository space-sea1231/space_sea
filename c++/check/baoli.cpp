#include<bits/stdc++.h>//万能头 大家都在用吧 
using namespace std;
int n,tong[100007],m;//桶删数 
int head[100007],nxt[100007];//链式常规操作 
int main(){
    freopen("date.in", "r", stdin);
    freopen("baoli.out", "w", stdout);
    scanf("%d",&n);
    nxt[0]=1;//将0的下一个定为1 
    for(int i=2,p,k;i<=n;i++){
        scanf("%d%d",&k,&p);
        if(!p){ //放在左边 
            nxt[head[k]]=i;//断开链子并接上 
            head[i]=head[k];//将我们上一步完善 
            nxt[i]=k;// 连接下一个 
            head[k]=i;//将下一个的head连在i上 
        }else{//放在右边，而且具有对称性，比较容易来修改代码 
            head[nxt[k]]=i;
            nxt[i]=nxt[k];
            head[i]=k;
            nxt[k]=i;//由于同理，就不再解释了 
        }
    }
    scanf("%d",&m);
    for(int i=1,t;i<=m;i++){
        scanf("%d",&t);
        tong[t]=1;//tong删法 
    }
    for(int i=nxt[0];1;i=nxt[i]){
        if(!tong[i]) printf("%d ",i);
        if(!nxt[i]) break;/*为甚要放在后面而不是for循环上，
		大家可以试试，这样应该就能明白了 */
    }
}