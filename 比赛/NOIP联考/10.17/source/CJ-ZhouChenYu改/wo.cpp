#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NR = 1e6 + 5;
const int MOD = 998244353;
int t;
int n;
int a[2 * NR];
int fat[NR];
int cnt,cnt2;
int place,place2,tot;
int fpow(int a,int b){
    int res = 1;
    while(b){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    cin >> t;
    fat[0] = 1;
    for(int i = 1;i <= 1e6;i++) fat[i] = fat[i - 1] * i % MOD;
    while(t--){
        cin >> n;
        cnt = cnt2 = n,place = place2 = tot = 0;
        for(int i = 1;i <= 2 * n;i++){
            cin >> a[i];
            if(a[i] > n) cnt2--;
            else if(a[i] == 0);
            else cnt--;
        }
        // cerr << cnt << " " << cnt2 << "\n";
        for(int i = 1;i <= n;i++){
            if(a[2 * i] == 0 && a[2 * i - 1] == 0){
                if(place < cnt && place2 < cnt2) place++,place2++,tot++;
                else if(place2 < cnt2 - 1) place2++,place2++;
                else if(place < cnt - 1) place++,place++;
            }
            else if(a[2 * i] == 0){
                if(a[2 * i - 1] > n){
                    if(place < cnt) place++;
                    else if(place2 < cnt2) place2++;
                }
                else{
                    if(place2 < cnt2) place2++;
                    else if(place < cnt) place++;
                }
            }
            else if(a[2 * i - 1] == 0){
                if(a[2 * i] > n){
                    if(place < cnt) place++;
                    else if(place2 < cnt2) place2++;
                }
                else{
                    if(place2 < cnt2) place2++;
                    else if(place < cnt) place++;
                }
            }
            // cerr << place << " " << place2 << " " << tot << "\n";
        }
        // cerr << fat[place] << " " << fat[place2] << " " << fpow(2,tot) << "\n\n";
        cout << fat[place] % MOD * fat[place2] % MOD * fpow(2,tot) % MOD << "\n";
    }
    return 0;
}
