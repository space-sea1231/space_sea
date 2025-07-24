#include<iostream>
#include<queue>
#include<cstring>
#include<functional>
#define DEBUG
using namespace std;
const int N=55;
struct Chess{
	int color;
	int power;
	bool operator ==(const Chess &p)const{
		return color==p.color;
	}
};
int mx,my,mc,q;
Chess board[N][N];
bool chk[N][N];
bool vis[N][N];
struct Vec2{
	int x,y;
	Vec2(int _x=0,int _y=0){
		x=_x;
		y=_y;
	}
	Vec2 operator +(const Vec2 &p)const{
		return Vec2(x+p.x,y+p.y);
	}
	bool Adjacent(const Vec2 &p)const{
		return abs(x-p.x)==1&&y==p.y||abs(y-p.y)==1&&x==p.x;
	}
	template<typename T,size_t p1,size_t p2> T& operator ()(T (&p)[p1][p2]){
		return p[x][y];
	}
	bool InBound(){
		return x>0&&x<=mx&&y>0&&y<=my;
	}
};
const Vec2 _2D4[4]={Vec2(0,1),Vec2(0,-1),Vec2(1,0),Vec2(-1,0)};
const Vec2 _2D3x3[9]={
	Vec2(-1,-1),Vec2(0,-1),Vec2(1,-1),
	Vec2(-1,0),Vec2(0,0),Vec2(1,0),
	Vec2(-1,1),Vec2(0,1),Vec2(1,1)
};
const Vec2 _2D5x5[25]={
	Vec2(-2,-2),Vec2(-1,-2),Vec2(0,-2),Vec2(1,-2),Vec2(2,-2),
	Vec2(-2,-1),Vec2(-1,-1),Vec2(0,-1),Vec2(1,-1),Vec2(2,-1),
	Vec2(-2,0),Vec2(-1,0),Vec2(0,0),Vec2(1,0),Vec2(2,0),
	Vec2(-2,1),Vec2(-1,1),Vec2(0,1),Vec2(1,1),Vec2(2,1),
	Vec2(-2,2),Vec2(-1,2),Vec2(0,2),Vec2(1,2),Vec2(2,2)
};
const Vec2 G=Vec2(0,1);
function<void(Vec2)> Effect[7]={
	[](Vec2 now)->void{
		return ;
	},
	[](Vec2 now)->void{
		for(int x=1;x<=mx;x++){
			if(!chk[x][now.y]){
				chk[x][now.y]=1;
				Effect[board[x][now.y].power](Vec2(x,now.y));
			}
		}
	},
	[](Vec2 now)->void{
		for(int y=1;y<=my;y++){
			if(!chk[now.x][y]){
				chk[now.x][y]=1;
				Effect[board[now.x][y].power](Vec2(now.x,y));
			}
		}
	},
	[](Vec2 now)->void{
		for(int y=1;y<=my;y++){
			if(!chk[now.x][y]){
				chk[now.x][y]=1;
				Effect[board[now.x][y].power](Vec2(now.x,y));
			}
		}
		for(int x=1;x<=mx;x++){
			if(!chk[x][now.y]){
				chk[x][now.y]=1;
				Effect[board[x][now.y].power](Vec2(x,now.y));
			}
		}
	},
	[](Vec2 now)->void{
		for(Vec2 delta:_2D3x3){
			Vec2 to=now+delta;
			if(to.InBound()&&!to(chk)){
				to(chk)=1;
				Effect[to(board).power](to);
			}
		}
	},
	[](Vec2 now)->void{
		for(Vec2 delta:_2D5x5){
			Vec2 to=now+delta;
			if(to.InBound()&&!to(chk)){
				to(chk)=1;
				Effect[to(board).power](to);
			}
		}
	},
	[](Vec2 now)->void{
		for(int y=1;y<=my;y++){
			for(int x=1;x<=mx;x++){
				if(board[x][y].color==now(board).color&&!chk[x][y]){
					chk[x][y]=1;
					Effect[board[x][y].power](Vec2(x,y));
				}
			}
		}
	},
};
bool CheckElim(){
	memset(chk,0,sizeof(chk));
	bool f=0;
	for(int y=1;y<=my;y++){
		int cnt=1;
		for(int x=1;x<=mx;x++){
			if(board[x][y]==board[x-1][y]&&board[x][y].color!=0){
				cnt++;
			}
			else{
				cnt=1;
			}
			if(cnt==3){
				for(int px=x;px>=x-2;px--){
					chk[px][y]=1;
				}
				f=1;
			}
			if(cnt>3){
				chk[x][y]=1;
			}
		}
	}
	for(int x=1;x<=mx;x++){
		int cnt=1;
		for(int y=1;y<=my;y++){
			if(board[x][y]==board[x][y-1]&&board[x][y].color!=0){
				cnt++;
			}
			else{
				cnt=1;
			}
			if(cnt==3){
				for(int py=y;py>=y-2;py--){
					chk[x][py]=1;
				}
				f=1;
			}
			if(cnt>3){
				chk[x][y]=1;
			}
		}
	}
	return f;
}
void Print(bool highelim=0){
	for(int y=1;y<=my;y++){
		for(int x=1;x<=mx;x++){
			if(highelim){
				if(chk[x][y]){
					printf("(%3d,%3d,%3d)",board[x][y].color,board[x][y].power,1);
				}
				else if(board[x][y].color==0){
					printf("             ");
				}
				else{
					printf("(X,X,X)");
				}
			}
			else{
				if(board[x][y].color==0){
					printf("             ");
				}
				else{
					printf("(%3d,%3d,%3d)",board[x][y].color,board[x][y].power,1);
				}
			}
		}
		printf("\n");
	}
}
void Fall(){
	bool flag=1;
	while(flag){
		flag=0;
		for(int y=my-1;y>=1;y--){
			for(int x=1;x<=mx;x++){
				if(board[x][y].color!=0&&board[x][y+1].color==0){
					swap(board[x][y+1],board[x][y]);
					flag=1;
				}
			}
		}
	}
}
long long score;
int qow(int base,int power){
	if(power==0) return 1;
	int tmp=qow(base,power>>1);
	if(power&1){
		return tmp*tmp*base;
	}
	else{
		return tmp*tmp;
	}
}
void BFS(Vec2 st){
	int col=st(board).color;
	queue<Vec2>q;
	q.push(st);
	int cnt=0;
	st(vis)=1;
	while(!q.empty()){
		Vec2 now=q.front();
		cnt++;
		q.pop();
		for(Vec2 delta:_2D4){
			Vec2 to=now+delta;
			if(to.InBound()&&to(board).color==col&&to(chk)&&!to(vis)){
				to(vis)=1;
				q.push(to);
			}
		}
	}
	#ifdef DEBUG
	printf("BFS(%d,%d)=%d\n",st.x,st.y,cnt);
	#endif
	score+=50ll*qow(cnt-3,2);
}
void Elim(){
	int chain=0;
	while(CheckElim()){
		chain++;
		#ifdef DEBUG
		printf("round%d:\n",chain);
		// Print(1);
		#endif
		memset(vis,0,sizeof(vis));
		for(int y=1;y<=my;y++){
			for(int x=1;x<=mx;x++){
				if(board[x][y].color!=0&&chk[x][y]&&!vis[x][y]){
					BFS(Vec2(x,y));
				}
			}
		}
		for(int y=1;y<=my;y++){
			for(int x=1;x<=mx;x++){
				if(chk[x][y]){
					Effect[board[x][y].power](Vec2(x,y));
				}
			}
		}
		#ifdef DEBUG
		printf("Trigger Effect:\n");
		// Print(1);
		#endif
		long long sum=0;
		for(int y=1;y<=my;y++){
			for(int x=1;x<=mx;x++){
				if(chk[x][y]){
					sum+=board[x][y].color;
					board[x][y].color=0;
					board[x][y].power=0;
				}
			}
		}
		score+=sum*chain;
		Fall();
	}
	score+=80ll*qow(chain-1,2);
}
vector<pair<int,int>> cards;
vector<int> buc;
int max_card_score;
void GetCardScore(){
	int maxv=0,maxc,smaxv=0,smaxc;
	#ifdef DEBUG
	printf("Can do:\n");
	for(int c=1;c<=mc;c++){
		for(int i=1;i<=buc[c];i++){
			printf("%d ",c);
		}
	}
	printf("\n");
	#endif
	for(int c=1;c<=mc;c++){
		if(buc[c]>=maxv){
			smaxv=maxv;
			smaxc=maxc;
			maxv=buc[c];
			maxc=c;
		}
		else if(buc[c]>=smaxv){
			smaxv=buc[c];
			smaxc=c;
		}
	}
	if(maxv==1){
		#ifdef DEBUG
		printf("High Card\n");
		#endif
		max_card_score=max(max_card_score,50+maxc);
	}
	if(maxv==2&&smaxv==1){
		#ifdef DEBUG
		printf("Pair\n");
		#endif
		max_card_score=max(max_card_score,100+maxc*2);
	}
	if(maxv==2&&smaxv==2){
		#ifdef DEBUG
		printf("2 Pair\n");
		#endif
		max_card_score=max(max_card_score,200+maxc*2+smaxc);
	}
	if(maxv==3&&smaxv==1){
		#ifdef DEBUG
		printf("Trio\n");
		#endif
		max_card_score=max(max_card_score,300+maxc*3);
	}
	if(maxv==3&&smaxv==2){
		#ifdef DEBUG
		printf("Full House\n");
		#endif
		max_card_score=max(max_card_score,500+maxc*3+smaxc);
	}
	if(maxv==4){
		#ifdef DEBUG
		printf("Quad\n");
		#endif
		max_card_score=max(max_card_score,750+maxc*5);
	}
	if(maxv==5){
		#ifdef DEBUG
		printf("Straight\n");
		#endif
		max_card_score=max(max_card_score,1000+maxc*10);
	}
}
void DFS(int now){
	if(now==5){
		GetCardScore();
		return ;
	}
	buc[cards[now].first]++;
	DFS(now+1);
	buc[cards[now].first]--;
	if(cards[now].first!=cards[now].second){
		buc[cards[now].second]++;
		DFS(now+1);
		buc[cards[now].second]--;
	}
}
void CheckCard(){
	#ifdef DEBUG
	printf("CheckCard()\n");
	#endif
	max_card_score=0;
	DFS(0);
	#ifdef DEBUG
	printf("max score=%d\n",max_card_score);
	#endif
	score+=max_card_score;
}
int main(){
  freopen("tmp.in","r",stdin);
  freopen("tmp.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>my>>mx>>mc>>q;
	buc.resize(mc+1);
	for(int y=1;y<=my;y++){
		for(int x=1;x<=mx;x++){
			cin>>board[x][y].color;
		}
	}
	for(int y=1;y<=my;y++){
		for(int x=1;x<=mx;x++){
			cin>>board[x][y].power;
		}
	}
	bool all_avil=1,full_clear=1;
	for(int i=1;i<=q;i++){
		Vec2 p1,p2;
		cin>>p1.y>>p1.x>>p2.y>>p2.x;
    cout<<score<<'\n';
		if(!p1.InBound()||!p2.InBound()||!p1.Adjacent(p2)){
			#ifdef DEBUG
			printf("failed\n");
			#endif
			all_avil=0;
			continue;
		}
		if(p1(board).color==0||p2(board).color==0){
			#ifdef DEBUG
			printf("failed\n");
			#endif
			all_avil=0;
			continue;
		}
		swap(p1(board),p2(board));
		if(!CheckElim()){
			#ifdef DEBUG
			printf("failed\n");
			#endif
			swap(p1(board),p2(board));
			all_avil=0;
		}
		else{
			#ifdef DEBUG
			printf("success main=%d %d\n",p1(chk)?p1(board).color:p2(board).color,p2(chk)?p2(board).color:p1(board).color);
			#endif
			cards.emplace_back(make_pair(p1(chk)?p1(board).color:p2(board).color,p2(chk)?p2(board).color:p1(board).color));
			Elim();
			if(cards.size()==5){
				CheckCard();
				cards.clear();
			}
		}
		#ifdef DEBUG
		printf("Done:%lld\n",score);
		Print();
		#endif
	}
	for(int y=1;y<=my;y++){
		for(int x=1;x<=mx;x++){
			if(board[x][y].color!=0){
				full_clear=0;
			}
		}
	}
	score+=all_avil*1000+full_clear*10000;
	printf("%lld",score);
	return 0;
}
/*
2 4 2 5
1 1 2 2
2 2 1 1
0 0 0 0
0 0 0 0
1 1 2 1
2 2 2 2
1 4 2 3
1 1 1 4
1 1 1 2




*/