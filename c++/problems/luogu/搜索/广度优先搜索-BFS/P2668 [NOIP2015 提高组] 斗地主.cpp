#include <bits/stdc++.h>
using namespace std;
const int N=30;
const int INF=1<<30;
int t, n, ans;
int card[N];
void init(){
    for (int i=0; i<N; i++){
        card[i]=0;
    }
    ans=INF;
}
void serch(int dep){
    if (dep>=ans){//当前出牌次数肯定比目前最优解大
        return ;
    }
/*--------------------顺子--------------------*/
    int sum=0;
/*---------------单顺子---------------*/
    sum=0;
    for (int i=3; i<=14; i++){
        if (card[i]<1){
            sum=0;
        }else{
            sum++;
            if (sum>=5){
                for (int j=i-sum+1; j<=i; j++){//出牌
                    card[j]--;
                }
                serch(dep+1);
                for (int j=i-sum+1; j<=i; j++){//回溯
                    card[j]++;
                }
            }
        }
    }
/*---------------双顺子---------------*/
    sum=0;
    for (int i=3; i<=14; i++){
        if (card[i]<2){
            sum=0;
        }else{
            sum++;
            if (sum>=3){
                for (int j=i-sum+1; j<=i; j++){//出牌
                    card[j]-=2;
                }
                serch(dep+1);
                for (int j=i-sum+1; j<=i; j++){//回溯
                    card[j]+=2;
                }
            }
        }
    }
/*---------------三顺子---------------*/
    sum=0;
    for (int i=3; i<=14; i++){
        if (card[i]<3){
            sum=0;
        }else{
            sum++;
            if (sum>=2){
                for (int j=i-sum+1; j<=i; j++){//出牌
                    card[j]-=3;
                }
                serch(dep+1);
                for (int j=i-sum+1; j<=i; j++){//回溯
                    card[j]+=3;
                }
            }
        }
    }
/*--------------------带牌--------------------*/

    for (int i=2; i<=14; i++){
        /*---------------三带---------------*/
        if (card[i]==3){
            card[i]-=3;
            for (int j=2; j<=15; j++){
                if (j==i){
                    continue;
                }
                /*---带单牌---*/
                if (card[j]>=1){
                    card[j]--;
                    serch(dep+1);
                    card[j]++;
                }
                /*---带双牌---*/
                if (card[j]>=2){
                    card[j]-=2;
                    serch(dep+1);
                    card[j]+=2;
                }
            }
            card[i]+=3;
        }
        /*---------------四带/三带---------------*/
        if (card[i]==4){
            /*----------三带----------*/
            card[i]-=3;
            /*-----带单牌-----*/
            for (int j=2; j<=15; j++){
                if (j==i||card[j]<1){
                    continue;
                }
                card[j]--;
                serch(dep+1);
                card[j]++;
            }
            /*-----带双牌-----*/
            for (int j=2; j<=14; j++){
                if (j==i||card[j]<2){
                    continue;
                }
                card[j]-=2;
                serch(dep+1);
                card[j]+=2;
            }
            card[i]+=3;
            /*----------四带----------*/
            card[i]-=4;
            /*-----带单牌-----*/
            for (int j=2; j<=15; j++){
                if (i==j||card[j]<1){
                    continue;
                }
                card[j]--;
                for (int k=2; k<=15; k++){
                    if (j==k||card[k]<1){
                        continue;
                    }
                    card[k]--;
                    serch(dep+1);
                    card[k]++;
                }
                card[j]++;
            }
            /*-----带双牌-----*/
            for (int j=2; j<=14; j++){
                if (i==j||card[j]<2){
                    continue;
                }
                card[j]-=2;
                for (int k=2; k<=14; k++){
                    if (j==k||card[k]<2){
                        continue;
                    }
                    card[k]-=2;
                    serch(dep+1);
                    card[k]+=2;
                }
                card[j]+=2;
            }
            card[i]+=4;
        }
    }
    for (int i=2; i<=15; i++){
        if (card[i]){
            dep++;
        }
    }
    ans=min(ans, dep);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t >> n;
    while (t--){
        init();
        for (int i=1; i<=n; i++){
            int x, y;
            cin >> x >> y;
            if (x==1){//A则比K大，所以放到后面。2属于王牌，所以不动
                card[14]++;
            }else if (x==0){//大鬼和小鬼
                card[15]++;
            }else{
                card[x]++;
            }
        }
        serch(0);
        printf("%d\n", ans);
    }

    return 0;
}