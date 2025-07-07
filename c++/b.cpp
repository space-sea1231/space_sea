#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
// #define __Debug

using namespace std;

const int N=1e3+10;

int t, n;
int cnt;
int a[N], b[N];
vector<pair<int, int> > ans;

void Init(){
    for (int i=1; i<=n; i++){
        b[i]=0;
    }
    ans.clear();
    cnt=0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--){
        Init();
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
        }
        int last=1;
        for (int i=1; i<=n+1; i++){
            if (i!=n+1){
                cin >> b[i];
            }
            if (b[i]<b[i-1]){
                int l=i-1, r=i;//7-8
                while (b[r+1]<b[r]){
                    r++;
                }
                #ifdef __Debug
                    printf("l=%d r=%d\n", l, r);
                #endif
                for (int j=r; j>=l; j--){
                    if (a[j]!=b[j]){
                        for (int k=j-1; k>=last; k--){
                            if (a[k]==b[j]){
                                cnt++;
                                ans.push_back(make_pair(k, j));
                                sort(a+k, a+j+1);
                                k=last;
                            }
                        }
                    }
                }
                if (last>l){
                    continue;
                }
                cnt++;
                ans.push_back(make_pair(last, l));
                sort(a+last, a+l);
                last=r;
            }
        }
        bool flag=true;
        #ifdef __Debug
            for (int i=1; i<=n; i++){
                printf("%d ", a[i]);
            }
            printf("\n");
        #endif
        for (int i=1; i<=n; i++){
            if (a[i]!=b[i]){
                flag=false;
            }
        }
        if (flag){
            printf("0\n");
            printf("%d\n", cnt);
            for (auto idx:ans){
                printf("%d %d\n", idx.first, idx.second);
            }
        }else{
            printf("-1\n");
        }
    }
    return 0;
}