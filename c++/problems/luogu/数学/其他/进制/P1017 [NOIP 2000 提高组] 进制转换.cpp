#include <bits/stdc++.h>
using namespace std;
const int N=20;
int n, p;
char idx[N]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J'};
vector<int> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> p;
    printf("%d=", n);
    while (n){
        int tmp=n%p;
        n/=p;
        if (tmp<0){
            tmp-=p;
            n++;
        }
        q.push_back(tmp);
    }
    reverse(q.begin(), q.end());
    for (int i:q){
        printf("%c", idx[i]);
    }
    printf("(base%d)\n", p);

    return 0;
}