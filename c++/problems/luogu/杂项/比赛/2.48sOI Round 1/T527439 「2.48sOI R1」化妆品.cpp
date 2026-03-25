#include <iostream>
#include <stdio.h>
#include <deque>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;

int n;
int vala[N], valb[N];
ll sum1a, sum1b, sum2a, sum2b;
bool vis[N];
deque<pair<int, int> > a, b;


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<=(n<<1); i++){
        cin >> vala[i];
    }
    for (int i=1; i<=(n<<1); i++){
        cin >> valb[i];
        a.push_back(make_pair(vala[i], i));
        b.push_back(make_pair(valb[i], i));
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i=1; i<=n; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            while (vis[a.front().second]==true){
                a.pop_front();
            }
            sum1a+=vala[a.front().second];
            sum1b+=valb[a.front().second];
            vis[a.front().second]=true;
            while (vis[a.back().second]==true){
                a.pop_back();
            }
            sum2a+=vala[a.back().second];
            sum2b+=valb[a.back().second];
            vis[a.back().second]=true;
        }
        if (opt==2){
            while (vis[b.front().second]==true){
                b.pop_front();
            }
            sum1a+=vala[b.front().second];
            sum1b+=valb[b.front().second];
            vis[b.front().second]=true;
            while (vis[b.back().second]==true){
                b.pop_back();
            }
            sum2a+=vala[b.back().second];
            sum2b+=valb[b.back().second];
            vis[b.back().second]=true;
        }
    }
    printf("%lld %lld\n", sum2a, sum2b);
    printf("%lld %lld\n", sum1a, sum1b);

    return 0;
}