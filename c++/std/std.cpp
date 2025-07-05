#include <iostream>
#include <stdio.h>

using namespace std;

const int N=1e5+10;

int n;

struct ScanLine{
    int l, r, h;
    int val;

    bool operator<(const ScanLine &ref)const{
        return h<ref.h;
    }
}line;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<=n; i++){
        int sx, sy, fx, fy;
        cin >> sx >> sy >> fx >> fy;
        
    }
    return 0;
}