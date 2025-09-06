#include<bits/stdc++.h>
using namespace std;
int T,n;
string S;
int main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    scanf("%d",&T);
    while(T--){
        cin>>S;
        n=S.size();
        S='?'+S;
        bool flg=false;
        int need=0;
        for(int i=1;i<=n;i++){
            if(S[i]=='0'){
                flg=true;
            }
            else need++;
        }
        if(!flg){
            printf("%d %d\n",n,0);
            continue;
        }
        if(n<=2){
            printf("%d %d\n",need,0);
            continue;
        }
        vector<int> ans;
        for(int i=2;i<n;i++){//现在i-1
            if(S[i-1]=='1'){
                continue;
            }
            if(S[i]=='1'){//操作i+1，如果
                if(i+1==n)break;
                ans.push_back(i+1);
                S[i]='0';
                S[i+2]=(S[i+1]=='0'&&S[i+2]=='0')+'0';
            }
            ans.push_back(i);
            S[i-1]='1';
            S[i+1]=(S[i]=='0'&&S[i+1]=='0')+'0';
        }
        if(n<=3){
            int need=0;
            for(int i=1;i<=n;i++)need+=(S[i]=='1');
            printf("%d %lu\n",need,ans.size());
            for(int i=0;i<ans.size();i++){
                printf("%d ",ans[i]);
            }
            puts("");
            continue;
        }
        // printf("n=%d\n",n);
        // cout<<S<<'\n';
        if((S[n]=='1'||S[n-1]=='1')&&S[n-2]=='1'){//找到答案了
            printf("%d %lu\n",n-1,ans.size());
            for(int i=0;i<ans.size();i++){
                printf("%d ",ans[i]);
            }
            puts("");
            continue;
        }
        else{
            if(S[n-2]=='1'){//末尾是100
                ans.push_back(n-2);
                ans.push_back(n-1);
                ans.push_back(n-2);
            }
            else{
                printf("%d %lu\n",n-2,ans.size());
                for(int i=0;i<ans.size();i++){
                    printf("%d ",ans[i]);
                }
                puts("");
                continue;
            }
                // if(S[n-1]=='1'){//末尾是010
                //     ans.push_back(n-2);
                //     ans.push_back(n-1);
                //     ans.push_back(n-2);
                //     ans.push_back(n-2);
                // }
                // else{//不可能有001
                //     assert(0);
                // }
        }
        printf("%d %lu\n",n-1,ans.size());
        for(int i=0;i<ans.size();i++){
            printf("%d ",ans[i]);
        }
        puts("");
    }
    return 0;
}
/*
1. 操作就意味着必然有0
2. 答案必然是n-1，3那个情况是特例。
3. 考虑构造：

如果a[1]是1了，把他丢掉，视a[2]为新的a[1]
如果a[1]是0，考虑a[2]，如果a[2]是1，那就操作a[3]，然后a[2]就是0了，直接操作，a[1]就变成1了

一直到最后如果出现了最后是100的搞笑情况，就可以用四个数把他调整回来


111100
110100
110001
111011

111010
110000
110101
110001
111011

0010

1000
1101
0101
0000
1010
*/