
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
const int mod=998244353;
int n,dp[N][N],dp1[N][N];
vector<int> a;
int is[N][N];
string s;
int qu[N],qq;
int ans=0;
stack<int> st;
void check(){
    while(!st.empty())st.pop();
    bool b=0;
    // if(s==" ({([()])})")
    //     cout << 1;
    for(int i=1;i<=n;i++){
        if(s[i]=='('){
            st.push(1);
        }else if(s[i]=='['){
            st.push(2);
        }else if(s[i]=='{'){
            st.push(3);
        }else if(s[i]==')'){
            if(st.empty())return ;
            if(st.top()!=1)return ;
            st.pop();
        }else if(s[i]==']'){
            if(st.empty())return ;
            if(st.top()!=2)return ;
            st.pop();
        }else{
            if(st.empty())return ;
            if(st.top()!=3)return ;
            st.pop();
        }
    }
    if(!st.empty())return ;
    ans++;
    return ;
}
void dfs(int cur){
    if(cur>qq){
        check();
        return ;
    }
    s[qu[cur]]='(';
    dfs(cur+1);
    s[qu[cur]]='[';
    dfs(cur+1);
    s[qu[cur]]='{';
    dfs(cur+1);
    s[qu[cur]]=')';
    dfs(cur+1);
    s[qu[cur]]='}';
    dfs(cur+1);
    s[qu[cur]]=']';
    dfs(cur+1);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> n;
    cin >> s;
    s=" "+s;
    for(int i=1;i<n;i++){
        if((s[i]=='['&&s[i+1]==']')||(s[i]=='{'&&s[i+1]=='}')||(s[i]=='('&&s[i+1]==')')){
            is[i][i+1]=1;
            dp[i][i+1]=dp1[i][i+1]=1;
        }else if(s[i]=='?'&&s[i+1]=='?'){
            dp[i][i+1]=dp1[i][i+1]=3;
            is[i][i+1]=1;
        }else if(s[i]=='?'&&(s[i+1]==']'||s[i+1]==')'||s[i+1]=='}')){
            dp[i][i+1]=dp1[i][i+1]=1;
            is[i][i+1]=1;
        }else if(s[i+1]=='?'&&(s[i]=='['||s[i]=='('||s[i]=='{')){
            dp1[i][i+1]=dp[i][i+1]=1;
            is[i][i+1]=1;
        }
    }
    for(int len=4;len<=n;len+=2){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            if((s[i]=='['&&s[j]==']')||(s[i]=='{'&&s[j]=='}')||(s[i]=='('&&s[j]==')')){
                is[i][j]=1;
                dp1[i][j]=dp[i][j]=dp1[i+1][j-1];
            }else if(s[i]=='?'&&s[j]=='?'){
                dp1[i][j]=dp[i][j]=3*dp1[i+1][j-1];
                is[i][j]=1;
            }else if(s[i]=='?'&&(s[j]==']'||s[j]==')'||s[j]=='}')){
                dp1[i][j]=dp[i][j]=dp1[i+1][j-1];
                is[i][j]=1;
            }else if(s[j]=='?'&&(s[i]=='['||s[i]=='('||s[i]=='{')){
                dp1[i][j]=dp[i][j]=dp1[i+1][j-1];
                is[i][j]=1;
            }
            for(int k=i;k<j;k++){
                dp1[i][j]+=(dp[i][k]*dp1[k+1][j])%mod;
            }
            dp[i][j]%=mod;
            dp1[i][j]%=mod;
            // cout <<i<<" "<<j<<" "<< dp1[i][j] << "\n";
        }
        // cout << "\n";
    }
    cout << dp1[1][n]%mod;
    return 0;
}