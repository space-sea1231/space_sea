#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e3+10;

int n, a, b;
bool graph[N][N];
bool flag=true;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b;
    if ((a>1&&b>1)||(a==1&&b==1&&(n==2||n==3))){
        printf("NO\n");
        return 0;
    }
    if (a==1&&b==1){
        for (int i=1; i<n; i++){
            graph[i][i+1]=1;
            graph[i+1][i]=1;
        }
        flag=false;
    }else{
        if (a==1){
            swap(a, b);
            flag=false;
        }
        for (int i=1; i<=a-1; i++){
            for (int j=1; j<=n; j++){
                graph[i][j]=true;
                graph[j][i]=true;
            }
        }
        for (int i=1; i<=n; i++){
            graph[i][i]=true;
        }
    }
    printf("YES\n");
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            if (flag==true){
                graph[i][j]=graph[i][j]^true;
            }
            if (i==j){
                graph[i][j]=false;
            }
            printf("%d", graph[i][j]);
        }
        printf("\n");
    }
    return 0;
}
/*
001
001
110

010
100
000
*/