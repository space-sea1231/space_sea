#include <bits/stdc++.h>
using namespace std;
const int N=100000;//对拍次数
const int T=1000;//时间限制
void check(){
    if (system("g++ -o std std.cpp -std=c++14 -O2")){
        system("del *.exe");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
    if (system("g++ -o baoli baoli.cpp -std=c++14 -O2")){
        printf("###CE on baoli.cpp\n");
        system("del *.exe");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
    if (system("g++ -o date date.cpp -std=c++14 -O2")){
        printf("###CE on date.cpp\n");
        system("del *.exe");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
}
int main(){
    check();//CE检测
    for (int i=1; i<=N; i++){
        double st=clock();
        system("run.bat");
        double ed=clock();
        if (system("fc std.out baoli.out")){//WA检测
            printf("WA on #%d\n", i);
            system("del *.exe");//删除临时文件
            printf("删除临时文件\n");
            return 0;
        }
        printf("AC on #%d\n", i);
        printf("time:%lf\n", ed-st);
    }
    system("del *.exe");//删除临时文件
    printf("删除临时文件\n");
    
    return 0;
}