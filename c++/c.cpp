#include<iostream>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<cstring>
#include<set>
#include<map>
#include<climits>
#include<bits/extc++.h>
using namespace std;
int n,k;
struct Item{
    long long tim,need;
    bool flag;
    int index;
    vector<pair<int,int>> req;
}a[100005];
void DFS(int now){
    int cnt=0;
    long long maxt=0;
    for(auto v:a[now].req){
        if(a[now].need*v.first>1e9){
            a[v.second].flag=1;
        }
        else{
            a[v.second].need=a[now].need*v.first;
        }
        DFS(v.second);
        if(v.first*a[v.second].tim>1e9||a[v.second].flag){
            a[now].flag=1;
        }
        else{
            a[now].tim+=v.first*a[v.second].tim;
        }
        if(now==k){
            if(a[v.second].flag){
                cnt++;
            }
            else{
                maxt=max(maxt,v.first*a[v.second].tim);
            }
        }
    }
    if(now==k){
        if(cnt==0){
            a[now].tim-=maxt;
        }
        if(cnt==1){
            a[now].flag=0;
        }
        if(cnt>1){
            a[now].flag=1;
        }
    }
    if(a[now].need*a[now].tim>1e9){
        a[now].flag=1;
    }
    // printf("Debug%d:%lld %lld %d\n",now,a[now].tim,a[now].need,a[now].flag);
}
void Work(){
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        a[i].req.clear();
        a[i].flag=0;
        a[i].tim=0;
        int p;
        cin >> p;
        if(p==0){
            cin >> a[i].tim;
        }
        else{
            int k;
            cin >> k;
            while(k--){
                int cnt,id;
                cin >> cnt >> id;
                a[id].index++;
                a[i].req.push_back(make_pair(cnt,id));
            }
        }
    }
    a[k].need=1;
    DFS(k);
    if(a[k].flag){
        cout << "Impossible\n";
    }
    else{
        cout << a[k].tim << "\n";
    }
}
int main(){
    // atexit(FastIO::flush);
    int t=1;
    cin >> t;
    while(t--){
        Work();
    }
    return 0;
}