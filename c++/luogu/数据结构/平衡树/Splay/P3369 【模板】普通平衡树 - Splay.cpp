#include <bits/stdc++.h>
#define lson son[0]
#define rson son[1]
using namespace std;
const int N=1e5+10;
int n;
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
        int ans=0, cur=root;
        while (1){
            if (x<e[cur].val){
                cur=e[cur].lson;
                continue;
            }
            ans+=e[e[cur].lson].size;
            if (!cur){
                return ans+1;
            }
            if (e[cur].val==x){
                splay(cur);
                return ans+1;
            }
            ans+=e[cur].cnt;
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
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int opt, x;
        cin >> opt >> x;
        if (opt==1){
            tree.Insert(x);
        }
        if (opt==2){
            tree.Delete(x);
        }
        if (opt==3){
            printf("%d\n", tree.Val_Rank(x));
        }
        if (opt==4){
            printf("%d\n", tree.Rank_Val(x));
        }
        if (opt==5){
            // tree.Val_Rank(x);
            tree.Insert(x);
            printf("%d\n", tree.e[tree.Pre()].val);
            tree.Delete(x);
        }
        if (opt==6){
            // tree.Val_Rank(x);
            tree.Insert(x);
            printf("%d\n", tree.e[tree.Nxt()].val);
            tree.Delete(x);
        }
    }

    return 0;
}