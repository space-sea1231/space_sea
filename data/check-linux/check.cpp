#include <iostream>
#include <stdlib.h>

using namespace std;

const int N=10000;//对拍次数
const int T=1000;//时间限制

void Check(){
    if (system("g++ -o std std.cpp -std=c++14 -O2 -fsanitize=address,undefined")){
        system("rm check std baoli data");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
    if (system("g++ -o baoli baoli.cpp -std=c++14 -O2 -fsanitize=address,undefined")){
        printf("###CE on baoli.cpp\n");
        system("rm check std baoli data");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
    if (system("g++ -o data data.cpp -std=c++14 -O2 -fsanitize=address,undefined")){
        printf("###CE on data.cpp\n");
        system("rm check std baoli data");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
}
void Run(){
    if (system("./data>data.in")){
        printf("###RE on data.cpp\n");
        system("rm check std baoli data");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
    if (system("./std<data.in>std.out")){
        printf("###RE on std.cpp\n");
        system("rm check std baoli data");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
    if (system("./baoli<data.in>baoli.out")){
        printf("###RE on baoli.cpp\n");
        system("rm check std baoli data");//删除临时文件
        printf("删除临时文件\n");
        exit(0);
    }
}
signed main(){
    Check();//CE检测
    for (int i=1; i<=N; i ++) {
        double st=clock();
        Run();
        double ed=clock();
        if (system("diff -Bb std.out baoli.out")){//WA检测
            printf("WA on #%d\n", i);
            system("rm check std baoli data");//删除临时文件
            printf("删除临时文件\n");
            return 0;
        }
        printf("AC on #%d\n", i);
        printf("time:%lf\n", ed-st);
    }
    system("rm check std baoli data");//删除临时文件
    printf("删除临时文件\n");
    
    return 0;
}