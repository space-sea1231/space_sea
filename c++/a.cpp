//avl 数组版，合并相同关键字
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
struct avlnode{
    int val;
    int size;
    int cnt;
    int height;
    int ls;
    int rs;
}avl[maxn];
int root,tot;
int height(int rt)
{
    if (rt==0) return 0;
    return avl[rt].height;
}
void pushup(int rt)
{
    if (rt==0) return ;
    avl[rt].size=avl[avl[rt].ls].size+avl[avl[rt].rs].size+avl[rt].cnt;
}
void LeftRotation(int &rt)
{
    int k;
    k=avl[rt].rs;
    avl[rt].rs=avl[k].ls;
    avl[k].ls=rt;
    avl[rt].height=max(height(avl[rt].ls),height(avl[rt].rs))+1;
    pushup(rt);
    avl[k].height=max(height(avl[k].ls),height(avl[k].rs))+1;
    pushup(k);
    rt=k;
}
void RightRotation(int &rt)
{
    int k;
    k=avl[rt].ls;
    avl[rt].ls=avl[k].rs;
    avl[k].rs=rt;
    avl[rt].height=max(height(avl[rt].ls),height(avl[rt].rs))+1;
    pushup(rt);
    avl[k].height=max(height(avl[k].ls),height(avl[k].rs))+1;
    pushup(k);
    rt=k;
}
int Newavl(int v)
{
    tot++;
    avl[tot].val=v;
    avl[tot].ls=avl[tot].rs=0;
    avl[tot].cnt=avl[tot].size=1;
    avl[tot].height=0;
    return tot;
}
void preorder(int rt)
{
    if (rt!=0)
    {
        cout<<rt<<",ls"<<avl[rt].ls<<",rs"<<avl[rt].rs<<",cnt"<<avl[rt].cnt<<",size"<<avl[rt].size<<",height"<<avl[rt].height<<",val"<<avl[rt].val<<endl;
        preorder(avl[rt].ls);
        preorder(avl[rt].rs);     
    }
}
void inorder(int rt)
{
    if (rt!=0)
    {
        inorder(avl[rt].ls);
        for (int i=1;i<=avl[rt].cnt;++i) cout<<avl[rt].val<<" ";
        inorder(avl[rt].rs);
    }
}
void insert(int &rt,int v)
{
    if (rt==0)
    {
        rt=Newavl(v);
    }
    else
    {
        if (avl[rt].val>v)
        {
            insert(avl[rt].ls,v);
            if (avl[avl[rt].ls].height-avl[avl[rt].rs].height==2)
            {
                int& k=avl[rt].ls;
                if (avl[avl[k].ls].height>avl[avl[k].rs].height)
                {
                    RightRotation(rt);
                }
                else
                {
                    LeftRotation(k);
                    //LeftRotation(avl[rt].ls);//LeftRotation(k);???
                    RightRotation(rt);
                }
            }
        }
        else if (v>avl[rt].val)
        {
            insert(avl[rt].rs,v);
            if (avl[avl[rt].ls].height-avl[avl[rt].rs].height==-2)
            {
                int& k=avl[rt].rs;
                if (avl[avl[k].ls].height<avl[avl[k].rs].height)
                {
                    LeftRotation(rt); 
                }
                else
                {
                    RightRotation(k);
                    //RightRotation(avl[rt].rs);//RightRotation(k)  ??
                    LeftRotation(rt);
                }
            }
        }
        else
        {
            avl[rt].cnt++;
        }
    }
    pushup(rt);
    avl[rt].height=max(avl[avl[rt].ls].height,avl[avl[rt].rs].height)+1;
}
int Maximum(int rt)
{
    if (rt==0)
    {
        return rt;
    }
    while(avl[rt].rs!=0)
    {
        rt=avl[rt].rs;
    }
    return rt;
}
int Minimum(int rt)
{
    if (rt==0)
    {
        return rt;
    }
    while(avl[rt].ls!=0)
    {
        rt=avl[rt].ls;
    }
    return rt;
}
void dele(int &rt,int v)
{
    if (rt==0)
    {
        return ;
    }
    if (v<avl[rt].val)
    {
        dele(avl[rt].ls,v);
        avl[rt].height=max(height(avl[rt].ls),height(avl[rt].rs))+1;
        if (height(avl[rt].ls)-height(avl[rt].rs)==-2)
        {
            int &k=avl[rt].rs;
            if (height(avl[k].ls)>height(avl[k].rs))
            {
                RightRotation(k);
                LeftRotation(rt);
            }
            else
            {
                LeftRotation(rt);     
            }
        }
    }
    else if(v>avl[rt].val)
    {
        dele(avl[rt].rs,v);
        avl[rt].height=max(height(avl[rt].ls),height(avl[rt].rs))+1;
        if (height(avl[rt].ls)-height(avl[rt].rs)==2)
        {
            int &k=avl[rt].ls;
            if (height(avl[k].rs)>height(avl[k].ls))
            {
                LeftRotation(k);
                RightRotation(rt);
            }
            else
            {
                RightRotation(rt);
            }
        }
    }
    else
    {
        if (avl[rt].ls&&avl[rt].rs)
        {
            if (height(avl[rt].ls)>height(avl[rt].rs))
            {
                int k=Maximum(avl[rt].ls);
                avl[rt].val=avl[k].val;
                avl[rt].cnt=avl[k].cnt;
                dele(avl[rt].ls,avl[k].val);
            }
            else
            {
                int k=Minimum(avl[rt].rs);
                avl[rt].val=avl[k].val;
                avl[rt].cnt=avl[k].cnt;
                dele(avl[rt].rs,avl[k].val);
            }
        }
        else
        {
            rt=avl[rt].ls+avl[rt].rs;
        }
    }
    pushup(rt);
}
void del(int &rt,int v)
{
    if (rt==0)
    {
        return ;
    }
    else if(avl[rt].val==v)
    {
        avl[rt].size--;
        avl[rt].cnt--;
        if (avl[rt].cnt==0)
        {
            dele(rt,v);
        }
    }
    else if(v<avl[rt].val)
    {
        del(avl[rt].ls,v);
    }
    else
    {
        del(avl[rt].rs,v);
    }
    if (rt!=0)
    avl[rt].height=max(height(avl[rt].ls),height(avl[rt].rs))+1;
    pushup(rt);
}
int kth(int rt,int k)
{
    if (avl[avl[rt].ls].size>=k) return kth(avl[rt].ls,k);
    else if(avl[avl[rt].ls].size+avl[rt].cnt>=k) return avl[rt].val;
    else return kth(avl[rt].rs,k-avl[avl[rt].ls].size-avl[rt].cnt);
}
int Rank(int rt,int val)
{
    if (rt==0) return 1;
    if (avl[rt].val>=val) return Rank(avl[rt].ls,val);
    else return avl[avl[rt].ls].size+avl[rt].cnt+Rank(avl[rt].rs,val);
}
int Pre(int rt,int val)
{
    return kth(rt,Rank(rt,val)-1);
}
int suc(int rt,int val)
{
    return kth(rt,Rank(rt,val+1));
}
int main()
{
    int n;
     
    cin>>n;
    for (int i=1;i<=n;++i)
    {
        int opt,v;
        cin>>opt;
        if (opt==1)
        {
            cin>>v;
            insert(root,v);
        }
        else if(opt==2)
        {
            cin>>v;
            del(root,v);
        }
        else if(opt==3)
        {
            cin>>v;
            cout<<Rank(root,v)<<endl;
        }
        else if (opt==4)
        {
            cin>>v;
            cout<<kth(root,v)<<endl;
        }
        else if(opt==5)
        {
            cin>>v;
            cout<<Pre(root,v)<<endl;
        }
        else if(opt==6)
        {
            cin>>v;
            cout<<suc(root,v)<<endl;
        }
        else if(opt==7)
        {
            inorder(root);
            cout<<endl;
        }
        else if(opt==8)
        {
            preorder(root);
        }
          
    }
   
}