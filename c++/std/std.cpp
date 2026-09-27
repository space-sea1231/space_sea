#include<bits/stdc++.h>
using namespace std;

// 快速读入
inline int read(){
    int x=0,f=1; char c=0;
    while(!isdigit(c)){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(isdigit(c)){
        x=(x<<3)+(x<<1)+(c-'0');
        c=getchar();
    }
    return x*f;
}

const int N=2e6+10, inf=0x3f3f3f3f;
int n,m,cmax=0;

/*
 tr 是主线段树，维护：
   mx[u]    : 区间最大值
   spmx[u]  : 区间“特殊最大值”，初始为 -1；当某个位置被激活后，spmx 会跟踪 mx 的变化
   tag[u]   : 区间加法懒标记

 主要操作：
   update : 区间加 1
   change : 单点激活/取消激活（设置 spmx）
*/
struct node{
    int mx[N<<2], spmx[N<<2], tag[N<<2];

    // 合并左右儿子信息
    inline void pushup(int u){
        mx[u]=max(mx[u<<1],mx[u<<1|1]);
        spmx[u]=max(spmx[u<<1],spmx[u<<1|1]);
    }

    // 对节点 u 整体加 k
    inline void upd(int u,int k){
        mx[u]+=k;
        tag[u]+=k;
        // 只有已经激活的位置（spmx >= 0）才需要同步加 k
        if(spmx[u]>=0) spmx[u]+=k;
    }

    // 下传懒标记
    inline void pushdown(int u){
        if(tag[u]){
            upd(u<<1,tag[u]);
            upd(u<<1|1,tag[u]);
            tag[u]=0;
        }
    }

    // 区间 [x,y] 加 1
    inline void update(int u,int l,int r,int x,int y){
        if(x<=l && r<=y){
            upd(u,1);
            return;
        }   
        pushdown(u);
        int mid=(l+r)>>1;
        if(x<=mid) update(u<<1,l,mid,x,y);
        if(y>mid) update(u<<1|1,mid+1,r,x,y);
        pushup(u);
    }

    // 单点激活/取消激活
    // k = true  : 激活，spmx 设为当前 mx
    // k = false : 取消激活，spmx 设为 -1
    inline void change(int u,int l,int r,int x,bool k){
        if(l==r){
            if(!k) spmx[u]=-1;
            else spmx[u]=mx[u];
            return;
        }
        pushdown(u);
        int mid=(l+r)>>1;
        if(x<=mid) change(u<<1,l,mid,x,k);
        else change(u<<1|1,mid+1,r,x,k);
        pushup(u);
    }
}tr;

/*
 tra 是辅助线段树，维护每个位置被“左端点”覆盖的次数最大值。
 主要用于判断区间 [a,b] 内是否有点被覆盖过（query > 0）。
*/
struct nodea{
    int mx[N<<2];

    inline void pushup(int u){ mx[u]=max(mx[u<<1],mx[u<<1|1]); }

    // 单点加 1
    inline void update(int u,int l,int r,int x){
        if(l==r){
            mx[u]++;
            return;
        }   
        int mid=(l+r)>>1;
        if(x<=mid) update(u<<1,l,mid,x);
        else update(u<<1|1,mid+1,r,x);
        pushup(u);
    }

    // 区间最大值查询
    inline int query(int u,int l,int r,int x,int y){
        if(x<=l && r<=y) return mx[u];
        int mid=(l+r)>>1;
        if(x<=mid && mid<y) return max(query(u<<1,l,mid,x,y),query(u<<1|1,mid+1,r,x,y));
        else if(x<=mid) return query(u<<1,l,mid,x,y);
        else return query(u<<1|1,mid+1,r,x,y); 
    }
}tra;

/*
 trb 是另一棵辅助线段树，维护每个位置的最小值 mn。
 主要作用：
   - change : 单点修改最小值
   - get    : 在区间 [x,y] 中找到第一个 mn < L 的位置
   - clear  : 反复调用 get，把所有 mn < L 的位置“清除”（置为 inf 并取消 tr 中的激活）
*/
struct nodeb{
    int mn[N<<2];

    inline void pushup(int u){ mn[u]=min(mn[u<<1],mn[u<<1|1]); }

    // 单点修改
    inline void change(int u,int l,int r,int x,int k){
        if(l==r){
            mn[u]=k;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) change(u<<1,l,mid,x,k);
        else change(u<<1|1,mid+1,r,x,k);
        pushup(u);
    }

    // 区间最小值查询
    inline int query(int u,int l,int r,int x,int y){
        if(x<=l && r<=y) return mn[u];
        int mid=(l+r)>>1;
        if(x<=mid && mid<y) return min(query(u<<1,l,mid,x,y),query(u<<1|1,mid+1,r,x,y));
        else if(x<=mid) return query(u<<1,l,mid,x,y);
        else return query(u<<1|1,mid+1,r,x,y); 
    }

    // 在区间 [x,y] 中找第一个 mn < L 的位置，找不到返回 -1
    inline int get(int u,int l,int r,int x,int y,int L){
        if(mn[u]>=L) return -1;
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(x<=l && r<=y){
            if(mn[u<<1]<L) return get(u<<1,l,mid,x,y,L);
            else return get(u<<1|1,mid+1,r,x,y,L);
        }
        int res=-1;
        if(x<=mid) res=get(u<<1,l,mid,x,y,L);
        if(res==-1 && y>mid) res=get(u<<1|1,mid+1,r,x,y,L);
        return res;
    }

    // 清除区间 [x,y] 中所有 mn < L 的位置
    inline void clear(int x,int y,int L){
        while(1){
            int p=get(1,1,m,x,y,L);
            if(p==-1) break;
            change(1,1,m,p,inf);       // 将该位置最小值置为 inf
            tr.change(1,1,m,p,0);      // 在 tr 中取消该位置的激活
        }
    }
}trb;

int main(){
    m=read(),n=read();
    m=n*2;  // 坐标范围扩大到 2n

    // 初始化：trb.mn 全为 inf，tr.spmx 全为 -1
    for(int i=0;i<(N<<2);i++) trb.mn[i]=inf,tr.spmx[i]=-1;

    for(int i=1;i<=n;i++){
        int a=read(),b=read();
        if(a<b){
            // 情况 1：a < b
            tr.update(1,1,m,a,b);       // 区间 [a,b] 加 1
            tra.update(1,1,m,a);        // 左端点 a 计数 +1
            tra.update(1,1,m,b);        // 右端点 b 计数 +1（这里写法与 tra 定义一致）
            trb.clear(a,b,a);           // 清除 [a,b] 中 mn < a 的位置
        }
        else{
            // 情况 2：a >= b，交换后处理
            swap(a,b);
            // 如果 [a,b] 内没有被左端点覆盖过
            if(tra.query(1,1,m,a,b)==0){
                trb.change(1,1,m,b,a);  // 在 b 处记录最小值 a
                tr.change(1,1,m,b,1);   // 激活 b 位置
            }
        }

        // 更新全局最大值
        cmax=max(cmax,tr.spmx[1]);

        // 输出答案：如果全局特殊最大值等于全局最大值，则答案 +1，否则不变
        if(cmax==tr.mx[1]) printf("%d\n",tr.mx[1]+1);
        else printf("%d\n",tr.mx[1]);
    }
    return 0;
}

/*
Mobile Task Force Unit 机动特遣部队
stretch 伸展 
*/