#include <bits/stdc++.h>
using namespace std;
const int N=52;
int n, tot[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    char x, y;
    for (int i=1; i<=n; i++){
        cin >> x >> y;
        if (x=='D'){
            if (y=='A') tot[0]++;
            if (y=='2') tot[1]++;
            if (y=='3') tot[2]++;
            if (y=='4') tot[3]++;
            if (y=='5') tot[4]++;
            if (y=='6') tot[5]++;
            if (y=='7') tot[6]++;
            if (y=='8') tot[7]++;
            if (y=='9') tot[8]++;
            if (y=='T') tot[9]++;
            if (y=='J') tot[10]++;
            if (y=='Q') tot[11]++;
            if (y=='K') tot[12]++;
        }
        if (x=='C'){
            if (y=='A') tot[13]++;
            if (y=='2') tot[14]++;
            if (y=='3') tot[15]++;
            if (y=='4') tot[16]++;
            if (y=='5') tot[17]++;
            if (y=='6') tot[18]++;
            if (y=='7') tot[19]++;
            if (y=='8') tot[20]++;
            if (y=='9') tot[21]++;
            if (y=='T') tot[22]++;
            if (y=='J') tot[23]++;
            if (y=='Q') tot[24]++;
            if (y=='K') tot[25]++;
        }
        if (x=='H'){
            if (y=='A') tot[26]++;
            if (y=='2') tot[27]++;
            if (y=='3') tot[28]++;
            if (y=='4') tot[29]++;
            if (y=='5') tot[30]++;
            if (y=='6') tot[31]++;
            if (y=='7') tot[32]++;
            if (y=='8') tot[33]++;
            if (y=='9') tot[34]++;
            if (y=='T') tot[35]++;
            if (y=='J') tot[36]++;
            if (y=='Q') tot[37]++;
            if (y=='K') tot[38]++;
        }
        if (x=='S'){
            if (y=='A') tot[39]++;
            if (y=='2') tot[40]++;
            if (y=='3') tot[41]++;
            if (y=='4') tot[42]++;
            if (y=='5') tot[43]++;
            if (y=='6') tot[44]++;
            if (y=='7') tot[45]++;
            if (y=='8') tot[46]++;
            if (y=='9') tot[47]++;
            if (y=='T') tot[48]++;
            if (y=='J') tot[49]++;
            if (y=='Q') tot[50]++;
            if (y=='K') tot[51]++;
        }
    }
    int cnt=0;
    for (int i=0; i<52; i++)
        if (tot[i]==0) cnt++;
    printf("%d", cnt);
    
    return 0;
}