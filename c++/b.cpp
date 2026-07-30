#include <bits/stdc++.h>
using namespace std;
#define lson son[0]
#define rson son[1]
const int N = 3e5 + 10;
int T;
int n, top;
int cnt[N], b[N << 2];
bool vis[N];
bool Cmp(int x, int y) {
    int dx = min(x, n - x + 1);
    int dy = min(y, n - y + 1);
    if (dx != dy) return dx < dy;
    return x < y;
}
struct Splay{
    int root, num;
    struct Node{
        int fa, val;
        int size, cnt;
        int son[2];
    }e[N];
    void Update(int x){
        e[x].size=e[e[x].lson].size+e[e[x].rson].size+e[x].cnt;
    }
    bool Check(int x){
        return x==e[e[x].fa].rson;
    }
    void Clear(int x){
        e[x].fa=0, e[x].val=0;
        e[x].size=0, e[x].cnt=0;
        e[x].rson=0, e[x].lson=0;
    }
    void Init(){
        for (int i=1; i<=num; i++){
            Clear(i);
        }
        root=0, num=0;
    }
    void New(int x){
        e[++num].val=x;
        e[num].cnt++;
    }
    void Rotate(int x){
        int y=e[x].fa, z=e[y].fa, to=Check(x);
        e[y].son[to]=e[x].son[to^1];
        if (e[x].son[to^1]){
            e[e[x].son[to^1]].fa=y;
        }
        e[x].son[to^1]=y;
        e[y].fa=x, e[x].fa=z;
        if (z){
            e[z].son[e[z].rson==y]=x;
        }
        Update(y);
        Update(x);
    }
    void splay(int x){
        for (int i=e[x].fa; i=e[x].fa, i; Rotate(x)){
            if (e[i].fa){
                Rotate(Check(x)==Check(i)?i:x);
            }
        }
        root=x;
    }
    void Insert(int x){
        if (!root){
            New(x);
            Update(num);
            root=num;
            return ;
        }
        int cur=root, last=0;
        while (1){
            if (e[cur].val==x){
                e[cur].cnt++;
                Update(cur);
                Update(last);
                splay(cur);
                return ;
            }
            last=cur, cur=e[cur].son[x>e[cur].val];
            if (!cur){
                New(x);
                e[num].fa=last;
                e[last].son[x>e[last].val]=num;
                Update(num);
                Update(last);
                splay(num);
                return ;
            }
        }
    }
    int Pre(){
        int cur=e[root].lson;
        if (!cur){
            return cur;
        }
        while (e[cur].rson){
            cur=e[cur].rson;
        }
        splay(cur);
        return cur;
    }
    int Nxt(){
        int cur=e[root].rson;
        if (!cur){
            return cur;
        }
        while (e[cur].lson){
            cur=e[cur].lson;
        }
        splay(cur);
        return cur;
    }
    int Val_Rank(int x){
        int ans=0, cur=root, last=0;
        while (1){
            if (x<e[cur].val){
                last=cur;
                cur=e[cur].lson;
                continue;
            }
            ans+=e[e[cur].lson].size;
            if (!cur){
                if (last){
                    splay(last);
                }
                return ans+1;
            }
            if (e[cur].val==x){
                splay(cur);
                return ans+1;
            }
            ans+=e[cur].cnt;
            last=cur;
            cur=e[cur].rson;
        }
    }
    int Rank_Val(int x){
        int cur=root;
        while (1){
            if (e[cur].lson&&x<=e[e[cur].lson].size){
                cur=e[cur].lson;
                continue;
            }
            x-=e[e[cur].lson].size+e[cur].cnt;
            if (x<=0){
                splay(cur);
                return e[cur].val;
            }
            cur=e[cur].rson;
        }
    }
    void Delete(int x){
        Val_Rank(x);
        if (e[root].cnt>1){
            e[root].cnt--;
            Update(root);
            return ;
        }
        if (!e[root].lson&&!e[root].rson){
            Clear(root);
            root=0;
            return ;
        }
        if (!e[root].lson){
            int cur=root;
            root=e[root].rson;
            e[root].fa=0;
            Clear(cur);
            return ;
        }
        if (!e[root].rson){
            int cur=root;
            root=e[root].lson;
            e[root].fa=0;
            Clear(cur);
            return ;
        }
        int cur=root;
        int tmp=Pre();
        e[e[cur].rson].fa=tmp;
        e[tmp].rson=e[cur].rson;
        Clear(cur);
        Update(root);
    }
    int Size(){
        return e[root].size;
    }
    int Less(int x){
        return Val_Rank(x)-1;
    }
    int Min(){
        return Rank_Val(1);
    }
    int Max(){
        return Rank_Val(e[root].size);
    }
}tree;
vector<int> a;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n;
        int m = (n + 1) / 2;
        int total = n + m;
        a.clear();
        tree.Init();
        top = 0;
        bool ok = true;
        for (int i = 1; i <= n; i++) {
            cnt[i] = -1;
            vis[i] = false;
        }
        for (int i = 1; i <= total; i++) {
            int x;
            cin >> x;
            if (x >= 1 && x <= n) cnt[x]++;
            else ok = false;
        }
        for (int i = 1; i <= n; i++) {
            if (cnt[i] < 0) ok = false;
        }
        if (!ok) {
            printf("-1\n");
            continue;
        }
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= cnt[i]; k++) {
                b[top++] = i;
            }
        }
        sort(b, b + top, Cmp);
        for (int i = 0; i < top; i++) {
            if (min(b[i], n - b[i] + 1) < i + 1) ok = false;
        }
        if (!ok) {
            printf("-1\n");
            continue;
        }
        for (int i = 1; i <= n; i++) tree.Insert(i);
        a.push_back(b[0]);
        tree.Delete(b[0]);
        vis[b[0]] = true;
        for (int i = 1; i < m; i++) {
            int y = b[i];
            int low = (y - 1) - tree.Less(y);
            int need = i - low;
            vector<int> par;
            if (!vis[y]) {
                par.push_back(y);
                tree.Delete(y);
                vis[y] = true;
            }
            for (int j = 1; j <= need; j++) {
                int v = tree.Min();
                par.push_back(v);
                tree.Delete(v);
                vis[v] = true;
            }
            while ((int)par.size() < 2) {
                int v = tree.Max();
                par.push_back(v);
                tree.Delete(v);
                vis[v] = true;
            }
            a.push_back(par[0]);
            a.push_back(par[1]);
        }
        for (int i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }
    return 0;
}