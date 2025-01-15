#include <bits/stdc++.h>
using namespace std;
const int TEST=30;
const string problem="P2540";
const string file="/home/space-sea/桌面/数据/date/"+problem+"/";
int random_date(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}

const int N=30;
int vis[N], cnt;
void init(){
    for (int i=0; i<N; i++){
        vis[i]=0;
    }
    cnt=0;
}
void date_in(){
    int t=random_date(1, 10);
    int n=random_date(1, 23);
    printf("%d %d\n", t, n);
    while (t--){
        init();
        while (cnt<n){
            int x=random_date(0, 13);
            int y=random_date(1, 4);
            if (x==0){
                if (vis[0]<2){
                    vis[0]++;
                    printf("%d %d\n", x, y);
                    cnt++;
                }
            }else{
                if (vis[x]<4){
                    vis[x]++;
                    printf("%d %d\n", x, y);
                    cnt++;
                }
            }
        }
    }
}
int main(){
    srand(time(NULL));//随机种子
    for (int task=1; task<=TEST; task++){
        string file_in="";
        file_in+=file+problem+"_";
        file_in+=to_string(task)+".in";
        freopen(file_in.c_str(), "w", stdout);
        date_in();
    }
    fclose(stdout);
    system("rm date_in");
    
    return 0;
}