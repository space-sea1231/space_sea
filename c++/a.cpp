    #include<cstdio>
    #include<algorithm>
    #include<queue>
    #include<cstring>
    using namespace std;
    int n=1;//注意，邻接表不支持0号节点，trie树的根编号为1
    struct nod
    {int num;int typ;};
    queue <nod> q;
    struct trie//trie树
    {
        int map[100010][30];int end[100010];//记录结束点
        int word;//单词计数器
        int fa[100010];int fail[100010];int dis[100010];//father，以及end数组的反向数组
        inline int insert(int p,char c)//trie树插入
        {
            if(map[p][c-'a'+1]!=0)return map[p][c-'a'+1];
            map[p][c-'a'+1]=++n;fa[n]=p;return n;
        }
        inline int back(int p){return fa[p];}//这个是为了实现打字机的'B'键
        inline void ed(int p){end[p]=++word;dis[word]=p;}
        inline void build()//构造fail
        {
            for(int i=1;i<=26;i++)
            if(map[1][i]!=0)//第一层节点的特判
            {nod p;p.num=map[1][i];p.typ=i;fail[p.num]=1;q.push(p);}
            while(!q.empty())//bfs
            {
                nod now=q.front();q.pop();
                if(fail[now.num]!=1)//跳fail
                {
                    int trail=fail[fa[now.num]];
                    while(1)
                    {
                        if(map[trail][now.typ]!=0){trail=map[trail][now.typ];break;}
                        if(trail==1)break;trail=fail[trail];
                    }fail[now.num]=trail;
                }
                for(int i=1;i<=26;i++)
                {if(map[now.num][i]!=0)
                {nod p;p.num=map[now.num][i];p.typ=i;q.push(p);}}
            }return;
        }
    }tr;
    struct data{int v;int nxt;}edge[200010];
    int cnt;int alist[100010];
    inline void add(int u,int v)//存fail树
    {
        edge[++cnt].v=v;edge[cnt].nxt=alist[u];
        alist[u]=cnt;return;
    }
    struct node{int v;int num;};
    struct data2{node v;int nxt;}edge1[100010];
    int cnt1;int alist1[100010];
    inline void add1(int u,int v,int num)//存询问
    {
        node p;p.v=v;p.num=num;
        edge1[++cnt1].v=p;edge1[cnt1].nxt=alist1[u];
        alist1[u]=cnt1;return;
    }
    struct treearray//4行树状数组
    {
        int ta[200010];
        inline void ub(int& x){x+=x&(-x);}
        inline void db(int& x){x-=x&(-x);}
        inline void c(int x,int t){for(;x<=n;ub(x))ta[x]+=t;}
        inline int sum(int x){int res=0;for(;x>0;db(x))res+=ta[x];return res;}
    }ta;
    int dfn[100010];int size[100010];int dfu;
    bool book[100010];int ans[100010];
    void dfsfail(int x)//对fail树的dfs
    {
        dfn[x]=++dfu;
        size[x]=1;book[x]=true;
        int nxt=alist[x];
        while(nxt)
        {
            int v=edge[nxt].v;
            if(book[v]==false)
            {dfsfail(v);size[x]+=size[v];}
            nxt=edge[nxt].nxt;
        }return;
    }
    void dfstrie(int x)//对trie的dfs
    {
        ta.c(dfn[x],1);
        if(tr.end[x]!=0)
        {
            int nxt=alist1[tr.end[x]];
            while(nxt)
            {
                node v=edge1[nxt].v;int x=tr.dis[v.v];
                ans[v.num]=ta.sum(dfn[x]+size[x]-1)-ta.sum(dfn[x]-1);
                nxt=edge1[nxt].nxt;
            }
        }
        for(int i=1;i<=26;i++)
        {if(tr.map[x][i]!=0){dfstrie(tr.map[x][i]);}}
        ta.c(dfn[x],-1);return;
    }
    char mde[100010];int len;int st;int m;
    int main()
    {
        scanf("%s",mde+1);
        len=strlen(mde+1);
        for(st=1;st<=len;st++){if(mde[st]!='B'&&mde[st]!='P')break;}
        int p=tr.insert(1,mde[st]);
        for(int i=st+1;i<=len;i++)//构造trie
        {
            if(mde[i]=='B'){p=tr.back(p);}
            else if(mde[i]=='P'){tr.ed(p);}
            else p=tr.insert(p,mde[i]);
        }
        scanf("%d",&m);
        for(int i=1;i<=m;i++)//离线
        {
            int u;int v;
            scanf("%d%d",&u,&v);
            add1(v,u,i);
        }tr.build();//建AC自动机
        for(int i=2;i<=n;i++)
        {add(tr.fail[i],i);add(i,tr.fail[i]);}//建fail树
        dfsfail(1);dfstrie(1);//两边dfs
        for(int i=1;i<=m;i++)
        {printf("%d\n",ans[i]);}
        return 0;//拜拜程序~
    }

