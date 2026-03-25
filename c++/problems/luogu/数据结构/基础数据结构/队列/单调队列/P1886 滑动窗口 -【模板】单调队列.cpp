#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n, m;
int a[N];
deque<int> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    for (int i=1; i<=n; i++){
        while (!q.empty()&&a[q.back()]>a[i]){
            q.pop_back();
        }
        while (!q.empty()&&i-q.front()>=m&&i>=m){
            q.pop_front();
        }
        q.push_back(i);
        if (i>=m){
            printf("%d ", a[q.front()]);
        }
    }
    printf("\n");
    while (!q.empty()){
        q.pop_front();
    }
    for (int i=1; i<=n; i++){
        while (!q.empty()&&a[q.back()]<a[i]){
            q.pop_back();
        }
        while (!q.empty()&&i-q.front()>=m&&i>=m){
            q.pop_front();
        }
        q.push_back(i);
        if (i>=m){
            printf("%d ", a[q.front()]);
        }
    }

    return 0;
}