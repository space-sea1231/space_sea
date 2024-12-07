#ifndef GRAPH_H
#define GRAPH_H
#define TREE
#include<queue>
#include<vector>
#include<climits>
#include<stack>
#include<functional>
#include<random>
using namespace std;
int n,m;
enum split_tag{Heavy_chain,Long_chain,Left_chain,Right_chain,Random_chain};
class Graph{
	public:
		class Node;
		int mdfn,mgop;//augmenting path,tarjan or RST 
		class Edge{
			public:
				int v;
				Edge *next;
				int w;
				Edge *reverse;//add double
				bool operator <(Edge x)const{//boruvka
                    return w<x.w;
                }
				~Edge(){
					if(next) delete next;
				}
                Edge(){
                    v=w=0;
                    next=reverse=nullptr;
                }
		};
		class Node{
			public:
				int dis;
				Edge *head;
				int vis;
				Edge *last_edge;//dinic
				int dfn;//chain split,augmenting path,tarjan or RST
                int low,group;//augmenting path,tarjan or RST
				int index;//topo sort
				int oudex;//???
				int h;//johnson
                int tim;//SPFA
				int match;//augmenting path
                Node *f;//kruskal or boruvka
                #ifdef TREE
                int fa;
                int dep;
                int siz;
                int top,hc;//chain split
                int hi;//long chain split
                #endif
                Node *find(){//kruskal or boruvka
                    if(f==this){
                        return this;
                    }
                    return f=f->find();
                }
                bool merge(Node *y){//kruskal or boruvka
                    Node *fx=find(),*fy=y->find();
                    if(fx!=fy){
                        fx->f=fy;
                        return 1;
                    }
                    return 0;
                }
				void init(){
					dis=INT_MAX;
					head=last_edge=NULL;
					vis=dfn=low=group=index=oudex=h=tim=0;
					match=-1;
					Node *f=this;
                    #ifdef TREE
                    fa=dep=top=hc=0;
                    hi=0;
                    siz=1;
                    #endif
				}
				Node(){
					init();
				}
        }node[10005];
		int dis[1005][1005];//floyd or johnson
		void add(int u,int v,int w=1){
			Edge *tmp=new Edge;
			tmp->v=v;
			tmp->w=w;
			tmp->next=node[u].head;
			node[u].head=tmp;
			node[v].index++;//topo_sort
			node[u].oudex++;//???
		}
		void add_double(int u,int v,int w=1){
			Edge *tmp=new Edge;
			tmp->v=v;
			tmp->w=w;
			tmp->next=node[u].head;
			node[u].head=tmp;
			Edge *tmp2=new Edge;
			tmp2->v=u;
			tmp2->w=0;
			tmp2->next=node[v].head;
			node[v].head=tmp2;
			tmp->reverse=tmp2;
			tmp2->reverse=tmp;
		}
		stack<int>st;//tarjan or RST
		vector<vector<int> > ans;//PCC
		void tarjan_SCC(int now,int fa){
            mdfn++;
            st.push(now);
		    node[now].dfn=node[now].low=mdfn;
		    node[now].vis=1;
		    for(Edge *i=node[now].head;i;i=i->next){
		        if(i->v!=fa){
    		        if(!node[i->v].dfn){
    				    tarjan_SCC(i->v,now);
    				    node[now].low=min(node[now].low,node[i->v].low);
                    }
                    
                }
				if(node[i->v].vis){
                    node[now].low=min(node[now].low,node[i->v].dfn);
                }
			}
			if(node[now].dfn==node[now].low){
			    mgop++;
			    while(st.top()!=now){
			        node[st.top()].group=mgop;
			        node[st.top()].vis=0;
			        st.pop();
                }
                node[now].vis=0;
                node[now].group=mgop;
                st.pop();
            }
        }
        void tarjan_ECC(int now,Edge *fa){
            mdfn++;
            st.push(now);
		    node[now].dfn=node[now].low=mdfn;
		    for(Edge *i=node[now].head;i;i=i->next){
		        if(i!=fa){
    		        if(!node[i->v].dfn){
    				    tarjan_ECC(i->v,i->reverse);
    				    node[now].low=min(node[now].low,node[i->v].low);
                    }
                    else{
                        node[now].low=min(node[now].low,node[i->v].dfn);
                    }
                }
			}
			if(node[now].dfn==node[now].low){
			    mgop++;
			    while(st.top()!=now){
			        node[st.top()].group=mgop;
			        st.pop();
                }
                node[now].group=mgop;
                st.pop();
            }
        }
        void tarjan_PCC(int now,int fa){
            mdfn++;
            int cnt=0;
		    node[now].dfn=node[now].low=mdfn;
		    for(Edge *i=node[now].head;i!=NULL;i=i->next){
		        if(i->v!=fa){
    		        if(!node[i->v].dfn){
    		            st.push(i->v);
    				    tarjan_PCC(i->v,now);
    				    cnt++;
    				    node[now].low=min(node[now].low,node[i->v].low);
    				    if(node[i->v].low>=node[now].dfn){
                			mgop++;
                			ans.push_back(vector<int>(1,1));
            			    while(st.top()!=i->v){
            			        ans[mgop].push_back(st.top());
            			        ans[mgop][0]++;
            			        st.pop();
                            }
                            ans[mgop].push_back(st.top());
                            st.pop();
                            ans[mgop][0]++;
                            ans[mgop].push_back(now);
                        }
                    }
                    else{
                        node[now].low=min(node[now].low,node[i->v].dfn);
                    }
                }
			}
			if(fa==now&&cnt==0){
			    mgop++;
			    ans.push_back(vector<int>(1,1));
			    ans[mgop].push_back(now);
            }
        }
		bool SPFA(int st){
			queue<int>q;
			node[st].dis=0;
			q.push(st);
			while(!q.empty()){
				int now=q.front();
				q.pop();
				node[now].vis=0;
                node[now].tim++;
				if(node[now].tim>n) return 0;
				for(Edge *i=node[now].head;i;i=i->next){
					if(node[i->v].dis>node[now].dis+i->w){
						node[i->v].dis=node[now].dis+i->w;
						if(!node[i->v].vis){
							node[i->v].vis=1;
							q.push(i->v);
						}
					}
				}
			}
			return 1;
		}
		void dijkstra(int st){
			struct state{
				int id;
				int dis;
				bool operator <(state x)const{
					return dis>x.dis;
				}
			};
			priority_queue<state>p;
			p.push({st,0});
			while(!p.empty()){
				int now=p.top().id,d=p.top().dis;
				p.pop();
				if(node[now].vis) continue;
				node[now].vis=1;
				node[now].dis=d;
				for(Edge *i=node[now].head;i;i=i->next){
					if(node[i->v].dis>node[now].dis+i->w){
						node[i->v].dis=node[now].dis+i->w;
						if(!node[i->v].vis){
							p.push({i->v,node[now].dis+i->w});
						}
					}
				}
			}
		}
		void topo_sort(){
			queue<int>q;
			for(int i=1;i<=n;i++){
				if(node[i].index==0){
					q.push(i);
				}
			}
			while(!q.empty()){
				int now=q.front();
				q.pop();
				for(Edge *i=node[now].head;i;i=i->next){
					node[i->v].index--;
					if(!node[i->v].index){
						q.push(i->v);
					}
				}
			}
		}
		void floyd(){
		    for(int k=1;k<=n;k++){
		        for(int i=1;i<=n;i++){
		            if(i==k) continue;
		            for(int j=1;j<=n;j++){
		                if(i==j||j==k) continue;
		                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
                    }
                }
            }
        }
        bool johnson(){
            queue<int>q;
			for(int i=1;i<=n;i++){
			    q.push(i);
			    node[i].vis=1;
			    node[i].tim=0;
            }
			while(!q.empty()){
				int now=q.front();
				q.pop();
				node[now].vis=0;
				node[now].tim++;
				if(node[now].tim>n) return 0;
				for(Edge *i=node[now].head;i;i=i->next){
					if(node[i->v].h>node[now].h+i->w){
						node[i->v].h=node[now].h+i->w;
						if(!node[i->v].vis){
							node[i->v].vis=1;
							q.push(i->v);
						}
					}
				}
			}
			for(int i=1;i<=n;i++){
			    dijkstra(i);
			    for(int j=1;j<=n;j++){
			        dis[i][j]=node[j].dis;
                }
            }
            return 1;
        }
        int boruvka(){
            int num=n;
            int ans=0;
            Edge *target[5005]={};
            while(num>1){
                for(int i=1;i<=n;i++){
                    for(Edge *j=node[i].head;j;j=j->next){
                        if(node[i].find()!=node[j->v].find()){
                            if(target[node[i].find()-node]==NULL){
                                target[node[i].find()-node]=j;
                            }
                            else{
                                if(*j<*target[node[i].find()-node]){
                                    target[node[i].find()-node]=j;
                                }
                            }
                        }
                    }
                }
                bool flag=1;
                for(int i=1;i<=n;i++){
                    if(target[i]!=NULL){
                        bool f=node[i].merge(&node[target[i]->v]);
                        num-=f;
                        if(f){
                            ans+=target[i]->w;
                        }
                        target[i]=NULL;
                        flag=0;
                    }
                }
                if(flag) return -1;
            }
            return ans;
        }
		int dinic(int s,int t){
			std::function<int(int,int)> dinic_bfs=[&](int s,int t) -> bool
			{
				for(int i=1;i<=n;i++){
					node[i].dis=0;
				}
				queue<int>q;
				q.push(s);
				node[s].dis=1;
				node[s].last_edge=node[s].head;
				while(!q.empty()){
					int now=q.front();
					if(now==t) return true;
					q.pop();
					for(Edge *i=node[now].head;i;i=i->next){
						if(i->w>0&&node[i->v].dis==0){
							node[i->v].dis=node[now].dis+1;
							node[i->v].last_edge=node[i->v].head;
							q.push(i->v);
						}
					}
				}
				return false;
			};
			std::function<int(int,int,int)> dinic_dfs=[&](int now,int sum,int t) -> int
			{
				if(now==t) return sum;
				int res=0;
				for(Edge *i=node[now].last_edge;i&&sum;i=i->next){
					node[now].last_edge=i;
					if(i->w>0&&node[i->v].dis==node[now].dis+1){
						int tmp=dinic_dfs(i->v,min(sum,i->w),t);
						i->w-=tmp;
						i->reverse->w+=tmp;
						res+=tmp;
						sum-=tmp;
					}
				}
				return res;
			};
			int res=0;
			while(dinic_bfs(s,t)){
				res+=dinic_dfs(s,INT_MAX,t);
			}
			return res;
		}
		int augmenting_path(int l){
			std::function<int(int)> dfs=[&](int now) -> bool
			{
				node[now].dfn=mdfn;
				for(Edge *i=node[now].head;i;i=i->next){
					if(node[i->v].match==-1){
						node[i->v].match=now;
						node[now].match=i->v;
						return 1;
					}
				}
				for(Edge *i=node[now].head;i;i=i->next){
					if(node[node[i->v].match].dfn!=mdfn&&dfs(node[i->v].match)){
						node[i->v].match=now;
						node[now].match=i->v;
						return 1;
					}
				}
				return 0;
			};
			int res=0;
			while(1){
				int cnt=0;
				mdfn++;
				for(int i=1;i<=l;i++){
					if(node[i].match==-1&&dfs(i)){
						cnt++;
					}
				}
				if(cnt==0) break;
				res+=cnt;
			}
			return res;
		}
		void clear(){
			for(int i=1;i<=n;i++){
				if(node[i].head) delete node[i].head;
				node[i].init();
			}
		}
		void RST(int now,Graph &T);
        #ifdef TREE
        void tree_init(int now,int fa){
            node[now].fa=fa;
            node[now].dep=node[fa].dep+1;
            node[now].siz=1;
            for(Edge *i=node[now].head;i;i=i->next){
                if(i->v!=fa){
                    tree_init(i->v,now);
                    node[now].siz+=node[i->v].siz;
                    node[now].hi=max(node[now].hi,node[i->v].hi);
                }
            }
            node[now].hi++;
        }
        vector<int> chain_split(int root,split_tag tg){
            vector<int> occ(1);
            mt19937 rd(114514);
            function<void(int)> gethc=[&](int now)->void{
                for(Edge *i=node[now].head;i;i=i->next){
                    if(i->v!=node[now].fa){
                        gethc(i->v);
                        switch(tg){
                            case Heavy_chain:{
                                if(node[i->v].siz>node[node[now].hc].siz){
                                    node[now].hc=i->v;
                                }
                                break;
                            }
                            case Long_chain:{
                                if(node[i->v].hi>node[node[now].hc].hi){
                                    node[now].hc=i->v;
                                }
                                break;
                            }
                            case Left_chain:{
                                if(node[now].hc==0){
                                    node[now].hc=i->v;
                                }
                                break;
                            }
                            case Right_chain:{
                                if(i->next==nullptr){
                                    node[now].hc=i->v;
                                }
                                break;
                            }
                            case Random_chain:{
                                if(rd()%5==0||node[now].hc==0){
                                    node[now].hc=i->v;
                                }
                                break;
                            }
                        }
                    }
                }
            };
            function<void(int,int)> dfs=[&](int now,int top)->void{
                occ.push_back(now);
                node[now].dfn=occ.size()-1;
                node[now].top=top;
                if(node[now].hc) dfs(node[now].hc,top);
                for(Edge *i=node[now].head;i;i=i->next){
                    if(i->v!=node[now].fa&&i->v!=node[now].hc){
                        dfs(i->v,i->v);
                    }
                }
            };
            gethc(root);
            dfs(root,root);
            return occ;
        }
        int LCA(int x,int y){
            while(node[x].top!=node[y].top){
                if(node[node[x].top].dep<node[node[y].top].dep) swap(x,y);
                x=node[node[x].top].fa;
            }
            if(node[x].dep<node[y].dep) swap(x,y);
            return y;
        }
        #endif
};
void Graph::RST(int now,Graph &T){
    mdfn++;
    node[now].dfn=node[now].low=mdfn;
    st.push(now);
    for(Edge *i=node[now].head;i!=NULL;i=i->next){
        if(!node[i->v].dfn){
		    RST(i->v,T);
		    node[now].low=min(node[now].low,node[i->v].low);
		    if(node[i->v].low==node[now].dfn){
		    	T.mgop++;
		    	while(st.top()!=now){
		    		T.add(n+T.mgop,st.top(),0);
		    		T.add(st.top(),n+T.mgop,0);
		    		st.pop();
				}
				T.add(n+T.mgop,now,0);
		    	T.add(now,n+T.mgop,0);
			}
        }
        else{
            node[now].low=min(node[now].low,node[i->v].dfn);
        }
	}
}

#endif