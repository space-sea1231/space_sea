#include<bits/stdc++.h>
using namespace std;
const int N=1e6+100;
int n;
int a[N],pre[N],nxt[N]; 
void solve()
{
    cin>>n;
    stack<int>st;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        while(!st.empty()&&a[st.top()]>a[i])st.pop();
        if(!st.empty())pre[i]=i-st.top();else pre[i]=0;
        st.push(i);
    }
    auto chk=[&](const int&x,const int&y)
    {
        return pre[x+1]==(pre[y]>x?0:pre[y]);    
    };
    nxt[1]=0;for(int i=2,j=0;i<=n;i++)
    {
        while(j&&!chk(j,i))j=nxt[j];
        if(chk(j,i))j++;
        nxt[i]=j;
    }
    for(int i=1;i<=n;i++)cout<<nxt[i]<<" ";cout<<endl;
}
signed main()
{
    // freopen("hdu.in","r",stdin);
    // freopen("hdu.out","w",stdout);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int _;cin>>_;while(_--)solve();
    return 0;
}