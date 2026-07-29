#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e3+10;

int n;
int sizc;
string c, a;
bool flag;
namespace Pts1{
    bool Check(char c){
        return c>='A'&&c<='Z';
    }
    void Go(){
        int siza=a.size();
        if (siza<sizc){
            for (int i=0; i<siza; i++){
                printf("0");
            }
            printf("\n");
            return;
        }
        for (int i=0; i<sizc; i++){
            if ((a[i]==c[i]||Check(c[i])==false)&&i==sizc-1){
                printf("1");
            }
            else if (a[i]!=c[i]&&Check(c[i])==true){
                for (int j=i; j<siza; j++){
                    printf("0");
                }
                printf("\n");
                return;
            }
            else{
                printf("0");
            }
        }
        for (int i=sizc+1; i<=siza; i++){
            printf("0");
        }
        printf("\n");
    }
}
namespace Pts2{
    bool ans[N];
    char tmp[N], ttmp[N];
    bool Check(char c){
        return c>='A'&&c<='Z';
    }
    void Go(string c){
        int siza=a.size();
        int sizc=c.size();
        if (siza<sizc){
            for (int i=0; i<siza; i++){
                ans[i]=false|ans[i];
            }
            return;
        }
        for (int i=0; i<sizc; i++){
            if ((a[i]==c[i]||Check(c[i])==false)&&i==sizc-1){
                ans[i]=true|ans[i];
            }
            else if (a[i]!=c[i]&&Check(c[i])==true){
                for (int j=i; j<siza; j++){
                    ans[j]=false|ans[j];
                }
                return;
            }
            else{
                ans[i]=false|ans[i];
            }
        }
        for (int i=sizc; i<siza; i++){
            ans[i]=false|ans[i];
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> c >> n;
    sizc=c.size();
    for (int i=0; i<sizc; i++){
        if (c[i]=='['){
            flag=true;
        }
    }
    if (flag==true){
        using namespace Pts2;
        bool fflag=false;
        int ss=0;
        for (int i=0; i<sizc; i++){
            if (c[i]=='['){
                fflag=true;
            }
            if (fflag==false){
                tmp[ss++]=c[i];
            }
            if (c[i]==']'){
                fflag=false;
            }
        }
        ss=0;
        for (int i=0; i<sizc; i++){
            if (c[i]=='['||c[i]==']'){
                continue;
            }
            ttmp[ss++]=c[i];
        }
        for (int i=1; i<=n; i++){
            memset(ans, 0, sizeof(ans));
            cin >> a;
            Go(ttmp);
            Go(tmp);
            int siza=a.size();
            for (int j=0; j<siza; j++){
                printf("%d", ans[j]);
            }
            printf("\n");
        }
    }
    else{
        using namespace Pts1;
        for (int i=1; i<=n; i++){
            cin >> a;
            Go();
        }
    }
    return 0;
}