#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+10;
int n, now, cnt, l, r, b;
string s, a;
struct node{
    string ip;
    int id;
}S[N];
int turn(string a){
    int len=a.size();
    int sum=0;
    for (int i=0; i<len; i++){
        sum=(sum<<1)+(sum<<3)+(a[i]^48);
    }
    return sum;
}
bool check(string a, string b){
    int len_a=a.size(), len_b=b.size();
    if (len_a>len_b){
        return 1;
    }
    if (len_a<len_b){
        return 0;
    }
    for (int i=0; i<len_a; i++){
        if (a[i]>b[i]){
            return 1;
        }
        if (a[i]<b[i]){
            return 0;
        }
    }
    return 0;
}
bool cnm(string a){
    int cntt=0;
    int len=a.size();
    int flag=-1;
    for (int i=0; i<len; i++){
        if (a[i]<'0'||a[i]>'9'){//是字母
            if (flag==0){//上一位是数字
                cntt++;
            }
            if (flag==-1){//第一位是字母
                return 1;
            }
            if (flag){//两个字母连在一起
                return 1;
            }
            flag=1;
        }else{
            flag=0;
        }
    }
    if (flag==0){//最后一位是数字
        cntt++;
    }
    if (flag==1){//最后一位是字母
        return 1;
    }
    if (cntt!=5){//数字数量不符
        return 1;
    }
    return 0;
}
signed main(){
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    getline(cin, s);
    while (now++<n){
        // printf("Debug1: %d\n", n);
        getline(cin, s);
        a=s.substr(0, 6);
        // cout << s << endl;
/*--------------------------服务机---------------------------*/
        if (a=="Server"){
            l=r=7;
            a=s.substr(7);
            if (cnm(a)){
                goto ERR;
            }
            for (int i=1; i<=cnt; i++){//判断是否有重复情况
                // cout << S[i] << "  " << a << endl;
                if (a==S[i].ip){//发现重复情况
                    // cout << "???";
                    goto FAIL;
                }
            }
            for (int i=1; i<=4; i++){//a, b, c, d判断合法
                if (i==4){//特判最后一位分割符
                    r=s.find(":", l);
                }else{
                    r=s.find(".", l);
                }
                a=s.substr(l, r-l);
                if (a.size()>1&&a[0]=='0'){//判断前导零
                    // cout << "ZERO " << a << " " << i << endl;
                    goto ERR;
                }
                if (check(a, "255")){//判断越界
                    goto ERR;
                }
                l=r+1;//更新左端点
            }
            a=s.substr(l);
            if (a[0]=='0'){
                goto ERR;
            }
            if (check(a, "65535")){//e判断合法
                goto ERR;
            }
            S[++cnt].ip=s.substr(7);
            S[cnt].id=now;
            // printf("YEPPY\n");
            goto OK;
        }
// /*--------------------------客户机---------------------------*/
        if (a=="Client"){
            l=r=7;
            a=s.substr(7);
            if (cnm(a)){
                goto ERR;
            }
            for (int i=1; i<=4; i++){//a, b, c, d判断合法
                if (i==4){//特判最后一位分割符
                    r=s.find(":", l);
                }else{
                    r=s.find(".", l);
                }
                a=s.substr(l, r-l);
                if (a.size()>1&&a[0]=='0'){//判断前导零
                    goto ERR;
                }
                if (check(a, "255")){//判断越界
                    goto ERR;
                }
                l=r+1;//更新左端点
            }
            a=s.substr(l);
            if (a[0]=='0'){
                goto ERR;
            }
            // printf("%d\n", b);
            if (check(a, "65535")){//e判断合法
                goto ERR;
            }
            bool flag=0;
            a=s.substr(7);
            for (int i=1; i<=cnt; i++){
                if (S[i].ip==a){
                    printf("%lld\n", S[i].id);
                    flag=1;
                }
            }
            if (!flag){
                goto FAIL;
            }
        }
        continue;
        OK:
            printf("OK\n");
            continue;
        FAIL:
            printf("FAIL\n");
            continue;
        ERR:
            printf("ERR\n");
            continue;
    }
    return 0;
}
/*
5
Server 192.168.1.1:8080
Server 192.168.1.1:8080
Client 192.168.1.1:8080
Client 192.168.1.1:80
Client 192.168.1.1:99999
*/