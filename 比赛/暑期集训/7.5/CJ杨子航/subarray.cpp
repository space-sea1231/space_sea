#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

const int N=1e3+10;

int t, n;
int flag;
int a[N], b[N];
vector<pair<int, int> > ans;

void Init(){
    ans.clear();
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
        for (int i=1; i<=n; i++){
            cin >> b[i];
        }
        for (int i=1; i<=n; i++){
            if (a[i]!=b[i]){
                flag=0;
                for (int j=i; j<=n; j++){
                    if (a[j]<b[i]){
                        flag=-1;
                        break;
                    }
                    if (a[j]==b[i]){
                        for (int k=j-1; k>=i; k--){
                            swap(a[k], a[k+1]);
                            ans.push_back(make_pair(k, k+1));
                        }
                        break;
                    }
                }
                if (flag==-1){
                    break;
                }
            }
        }
        printf("%d\n", flag);
        if (flag==0){
            printf("%ld\n", ans.size());
            for (auto &idx:ans){
                printf("%d %d\n", idx.first, idx.second);
            }
        }
    }

    return 0;
}