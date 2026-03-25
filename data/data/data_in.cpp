#include <bits/stdc++.h>
using namespace std;
const int TEST=50;
const string id="U526216";;
const string problem="理智的采药";
const string file="/home/space_sea/space_sea/data/data/"+id+"/";
int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}

#define int long long
const int TT=1e3;
const int MM=1e3;
const int SIZE=1e5+10;
void date_in(){
    int t=Random(1, TT);
    int m=Random(1, SIZE/t);
    printf("%lld %lld\n", t, m);
    for (int i=1; i<=m; i++){
        int a=Random(1, TT);
        int b=Random(1, TT);
        int c=Random(1, TT);
        printf("%lld %lld %lld\n", a, b, c);
    }
}
signed main(){
    srand(time(NULL));//随机种子
    for (int task=1; task<=TEST; task++){
        string file_in="";
        file_in+=file+problem+"_";
        file_in+=to_string(task)+".in";
        freopen(file_in.c_str(), "w", stdout);
        date_in();
    }
    fclose(stdout);
    system("rm data_in");
    
    return 0;
}