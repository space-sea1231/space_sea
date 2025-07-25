#include <bits/stdc++.h>
using namespace std;
const int N=15;
int n, tot, a[N];
bool vis_1[N], vis_2[N<<1], vis_3[N<<1];
void serch(int dep){
    if (dep==n+1){
        tot++;
        if (tot<=3){
            for (int i=1; i<=n; i++){
                printf("%d ", a[i]);
            }
            printf("\n");
        }
        return ;
    }
    for (int i=1; i<=n; i++){
        if (vis_1[i]||vis_2[dep-i+n]||vis_3[i+dep]){
            continue;
        }
        vis_1[i]=1;
        vis_2[dep-i+n]=1;
        vis_3[i+dep]=1;
        a[dep]=i;
        serch(dep+1);
        vis_1[i]=0;
        vis_2[dep-i+n]=0;
        vis_3[i+dep]=0;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    serch(1);
    printf("%d", tot);

    return 0;