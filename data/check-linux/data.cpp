#include <iostream>
#include <stack>

using namespace std;
typedef long long ll;

const int N=10;
const int M=20;

int sum;
char c[4]={' ', 'D', 'R', 'Q'};
bool vis[M];
stack<int> house;

inline int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
signed main(){
    srand(time(NULL));//随机种子
    
    int n=N, m=N;
    printf("%d %d\n", n, m);
    while (m--){
        int opt=Random(1, 3);
        int x=Random(1, n);
        while (opt==2&&sum==0){
            opt=Random(1, 3);
        }
        if (opt==1){
            while (vis[x]==true){
                x=Random(1, n);
            }
            vis[x]=true;
            sum++;
            house.push(x);
            printf("%c %d\n", c[opt], x);
        }
        if (opt==2){
            printf("%c\n", c[opt]);
            vis[house.top()]=false;
            sum--;
            house.pop();
        }
        if (opt==3){
            printf("%c %d\n", c[opt], x);
        }
    }

    return 0;
}