#include<bits/stdc++.h>
using namespace std;
int main()
{
    system("g++ 1.cpp -o 1 -O2");
    system("g++ 2.cpp -o 2 -O2");
    system("g++ 3.cpp -o 3 -O2");
    for(int i=1;;i++)
    {
        system("./3;./1;./2;");
        cout<<"#"<<i<<' ';
        if(system("diff -w 1.out 2.out"))
        {
            cout<<"NO"<<endl;
            return 0;
        }
        cout<<"YES"<<endl;
    }
}