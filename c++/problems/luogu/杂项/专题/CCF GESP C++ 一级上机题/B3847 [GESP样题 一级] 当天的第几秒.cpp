#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, m, s;
    char c;
    cin >> h >> m >> s >> c;
    printf("%d\n", h*3600+m*60+s+(c=='P'?43200:0));
    
    return 0;
}