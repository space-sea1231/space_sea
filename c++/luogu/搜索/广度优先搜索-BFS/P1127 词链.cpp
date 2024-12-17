#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n, cnt;
int edge_st, edge_ed;
int fa[N], in[N], out[N];
bool vis[N];
string s[N], ans[N];
struct node{
    string word;
    int to, id;
};
vector<node> q[N];
bool cmp(string a, string b){
    return a<b;
}
int find(int x){
    if (fa[x]==x){
        return x;
    }
    return fa[x]=find(fa[x]);
}
void dfs(int dep, int u, int fa){
    if (dep==n+1){
        for (int i=1; i<=n; i++){
            cout << ans[i];
            if (i!=n){
                printf(".");
            }
        }
        printf("\n");
        exit(0);
    }
    for (int i=0; i<q[u].size(); i++){
        int to=q[u][i].to;
        int id=q[u][i].id;
        string word=q[u][i].word;
        if (!vis[id]){
            vis[id]=1;
            ans[dep]=word;
            dfs(dep+1, to, id);
        }
    }
    vis[fa]=0;
    return ;
}
int main(){
    // ios::sync_with_stdio(0);
    // cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> s[i];
    }
    sort(s+1, s+n+1, cmp);
    for (int i=1; i<=n; i++){
        int st=(int)(s[i][0]-'a'+1);
        int ed=(int)(s[i][s[i].size()-1]-'a'+1);
        out[st]++, in[ed]++;
        if (fa[st]==0){
            fa[st]=st;
            cnt++;
        }
        if (fa[ed]==0){
            fa[ed]=ed;
            cnt++;
        }
        if (st!=ed){
            int fa_st=find(st);
            int fa_ed=find(ed);
            if (fa_st!=fa_ed){
                cnt--;
                fa[fa_ed]=fa_st;
            }
        }
        q[st].push_back({s[i], ed, i});
    }
    if (cnt!=1){
        printf("***");
        return 0;
    }
    for (int i=1; i<=26; i++){
        if (fa[i]==0){
            continue;
        }
        if (in[i]+1==out[i]){
            if (edge_st!=0){
                printf("***");
                return 0;
            }
            edge_st=i;
        }else if (in[i]==out[i]+1){
            if (edge_ed!=0){
                printf("***");
                return 0;
            }
            edge_ed=i;
        }else if (in[i]!=out[i]){
            printf("***");
            return 0;
        }
    }
    if ((edge_st==0&&edge_ed!=0)||(edge_st!=0&&edge_ed==0)){
        printf("***");
        return 0;
    }
    if (edge_st==0){
        edge_st=s[1][0]-'a'+1;
    }
    dfs(1, edge_st, 0);

    return 0;
}