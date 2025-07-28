#ifndef TREE_H
#define TREE_H
#include<vector>
#include<random>
#include<climits>
#include<stack>
#include<chrono>
#include<tuple>
using namespace std;
namespace Tree{
	template<typename V> class Segment_tree{
		public:
			class Node{
				public:
					V val,tag;
					int l,r;
					Node *lc,*rc;
					Node(V v=V()){
						val=v;
						lc=rc=nullptr;
						l=r=tag=0;
					}
					void Build_tree(int L,int R,vector<V>& a){
						l=L;
						r=R;
						if(L==R){
							val=a[L];
							return;
						}
						int mid=L+R>>1;
						lc=new Node;
						rc=new Node;
						lc->Build_tree(L,mid,a);
						rc->Build_tree(mid+1,R,a);
						push_up();
					}
					void Edit(int L,int R,V x){
						if(l>=L&&r<=R){
							val+=(r-l+1)*x;
							tag+=x;
							return ;
						}
						int mid=l+r>>1;
						push_down();
						if(L<=mid){
							lc->Edit(L,R,x);
						}
						if(R>mid){
							rc->Edit(L,R,x);
						}
						push_up();
					}
					V Query(int L,int R){
						if(l>=L&&r<=R){
							return val;
						}
						int mid=l+r>>1;
						push_down();
						V tmp=0;
						if(L<=mid){
							tmp+=lc->Query(L,R);
						}
						if(R>mid){
							tmp+=rc->Query(L,R);
						}
						return tmp;
					}
					void push_up(){
						val=lc->val+rc->val;
					}
					void push_down(){
						lc->val+=(lc->r-lc->l+1)*tag;
						lc->tag+=tag;
						rc->val+=(rc->r-rc->l+1)*tag;
						rc->tag+=tag;
						tag=V();
					}
			};
			Node *root=new Node(0);
	};
    template<typename V>class Dymanic_segment_tree{
        private:
            class Node{
                public:
                    Node *lc,*rc;
                    V val,tag;
            };
        public:
            
    };
	class Chairman_tree{
		public:
			class Node{
				public:
					int val;
					int l,r,tag;
					Node *lc,*rc;
					Node(int v=0){
						val=v;
						lc=rc=nullptr;
						l=r=tag=0;
					}
					void Build_tree(int L,int R){
						l=L;
						r=R;
						if(L==R){
							val=0;
							return;
						}
						int mid=L+R>>1;
						lc=new Node;
						rc=new Node;
						lc->Build_tree(L,mid);
						rc->Build_tree(mid+1,R);
						push_up();
					}
					int Query(int L,int R){
						if(l>=L&&r<=R){
							return val;
						}
						int mid=l+r>>1;
						push_down();
						int tmp=0;
						if(L<=mid){
							tmp+=lc->Query(L,R);
						}
						if(R>mid){
							tmp+=rc->Query(L,R);
						}
						return tmp;
					}
					Node *Edit(int pos,int x){
						Node *tmp=clone();
						if(l==r&&r==pos){
							tmp->val=x;
							return tmp;
						}
						int mid=l+r>>1;
						if(pos<=mid){
							tmp->lc=lc->Edit(pos,x);
						}
						if(pos>mid){
							tmp->rc=rc->Edit(pos,x);
						}
						return tmp;
					}
					void push_up(){
						val=lc->val+rc->val;
					}
					void push_down(){
						lc->val+=(lc->r-lc->l+1)*tag;
						lc->tag+=tag;
						rc->val+=(rc->r-rc->l+1)*tag;
						rc->tag+=tag;
						tag=0;
					}
					Node *clone(){
						Node *tmp=new Node;
						*tmp=*this;
						return tmp;
					}
			};
			Node *root=new Node(0);
	};
	class Leftest_tree{
		public:
			class Node{
				public:
					int val,dis, id;
					int lc,rc,fa;
					bool del;
					Node(int v=0){
						val=v;
						dis=0;
						lc=rc=0;
						del=0;
					}
			}node[100001];
			int Find(int x){
				if(node[x].fa==x) return x;
				return node[x].fa=Find(node[x].fa);
			}
			int Merge(int x,int y){
				if(x==0||y==0){
					return x+y;
				}
				if(node[x].val>node[y].val||(node[x].val == node[y].val && node[x].id > node[y].id)) swap(x,y);
				node[x].rc=Merge(node[x].rc,y);
				if(node[node[x].lc].dis<node[node[x].rc].dis) swap(node[x].lc,node[x].rc);
				node[x].dis=node[node[x].rc].dis+1;
				return x;
			}
			void Erase(int x){
				if(node[x].del) return ;
				node[x].del=1;
				int tmp=Merge(node[x].lc,node[x].rc);
				node[node[x].lc].fa=node[node[x].rc].fa=node[x].fa=tmp;
				return ;
			}
	};
    template<typename K,typename V,K one>class FHQ_treap{
        protected:
            class Node{
                public:
                    K key;
                    V val;
                    Node *lc,*rc;
                    int pri,siz;
                    Node(K _key=K(),int _siz=1):key(_key){
                        val=V();
                        pri=rd();
                        siz=_siz;
                        lc=rc=null;
                    }
                    ~Node(){
                        if(lc!=null) delete lc;
                        if(rc!=null) delete rc;
                    }
                    void upd_siz(){
                        siz=1;
                        siz+=lc->siz;
                        siz+=rc->siz;
                    }
                    void print(){
                        if(this==null) return ;
                        printf("%d %d %d\n",key,val,siz);
                        printf("%d %d\n",key,lc->key);
                        lc->print();
                        printf("%d %d\n",key,rc->key);
                        rc->print();
                    }
            };
        public:
            static mt19937 rd;
            static Node *null;
            Node *root=null;
            pair<Node*,Node*> Split(K key,Node *now=nullptr){
                if(now==nullptr) now=root;
                if(now==null) return {null,null};
                if(now->key<=key){
                    auto tmp=Split(key,now->rc);
                    now->rc=tmp.first;
                    now->upd_siz();
                    return {now,tmp.second};
                }
                else{
                    auto tmp=Split(key,now->lc);
                    now->lc=tmp.second;
                    now->upd_siz();
                    return {tmp.first,now};
                }
            }
            Node *Merge(Node *l,Node *r){
                if(l==null) return r;
                if(r==null) return l;
                if(l->pri>r->pri){
                    l->rc=Merge(l->rc,r);
                    l->upd_siz();
                    return l;
                }
                else{
                    r->lc=Merge(l,r->lc);
                    r->upd_siz();
                    return r;                    
                }
            }
            Node *Insert(K key){
                auto tmp=Split(key-one);
                auto node=new Node(key);
                root=Merge(Merge(tmp.first,node),tmp.second);
                return node;
            }
            void Erase(K key){
                auto tmp1=Split(key);
                auto tmp2=Split(key-one,tmp1.first);
                if(tmp2.second!=null){
                    auto tmp=tmp2.second;
                    tmp2.second=Merge(tmp2.second->lc,tmp2.second->rc);
                    tmp->lc=tmp->rc=null;
                    delete tmp;
                }
                root=Merge(Merge(tmp2.first,tmp2.second),tmp1.second);
            }
            int Rank(K key){
                auto tmp=Split(key-one);
                int rank=tmp.first->siz+1;
                root=Merge(tmp.first,tmp.second);
                return rank;
            }
            K Key(int rank){
                Node *now=root;
                while(now!=null){
                    if(now->lc->siz+1==rank){
                        return now->key;
                    }
                    else if(now->lc->siz<rank){
                        rank-=now->lc->siz+1;
                        now=now->rc;
                    }
                    else{
                        now=now->lc;
                    }
                }
                return K();
            }
            Node *Find(K key){
                auto tmp1=Split(key);
                auto tmp2=Split(key-one,tmp1.first);
                root=Merge(Merge(tmp2.first,tmp2.second),tmp1.second);
                return tmp2.second;
            }
            V &operator[](K &key){
                auto tmp=Find(key);
                if(tmp==null){
                    return Insert(key)->val;
                }
                else{
                    return tmp->val;
                }
            }
            K Prev(K key){
                auto tmp=Split(key-one);
                Node *now=tmp.first;
                while(now->rc!=null){
                    now=now->rc;
                }
                root=Merge(tmp.first,tmp.second);
                return now->key;
            }
            K Next(K key){
                auto tmp=Split(key);
                Node *now=tmp.second;
                while(now->lc!=null){
                    now=now->lc;
                }
                root=Merge(tmp.first,tmp.second);
                return now->key;
            }
    };
    class Trie{
        public:
        	static const int Sigma=128;
            Trie(){
                root=new Node;
            }
            class Node{
                public:
                    Node *ch[Sigma];
                    int val;
            };
            Node *root;
            void Insert(string x){
                Node *now=root;
				for(int i=0;i<x.length();i++){
					if(now->ch[x[i]]==NULL){
						now->ch[x[i]]=new Node;
					}
					now=now->ch[x[i]];
				}
				now->val++;
            }
			int Find(string x){
				Node *now=root;
				for(int i=0;i<x.length();i++){
					if(now->ch[x[i]]==NULL){
						return 0;
					}
					now=now->ch[x[i]];
				}
				return now->val;
			}
			Node *Merge(Node *x,Node *y){
				if(x==NULL||y==NULL){
					return max(x,y);
				}
				x->val+=y->val;
				for(int i=0;i<Sigma;i++){
					x->ch[i]=Merge(x->ch[i],y->ch[i]);
				}
				return x;
			}
    };
	class Cartesian_tree{
		public:
			class Node{
				public:
					int key,val;
					int w;
					Node *lc,*rc;
					Node(int _k=0,int _w=0):key(_k),w(_w){

					}
			};
			void Build_tree(vector<pair<int,int>> x){
				stack<Node*>st;
				for(pair<int,int> i:x){
					Node *tmp=nullptr;
					Node *cur=new Node(i.first,i.second);
					while(!st.empty()&&st.top()->w>i.second){
						tmp=st.top();
						st.pop();
					}
					if(!st.empty()){
						st.top()->rc=cur;
					}
					if(tmp!=nullptr){
						cur->lc=tmp;
					}
					st.push(cur);
				}
			}
	};
}
#endif