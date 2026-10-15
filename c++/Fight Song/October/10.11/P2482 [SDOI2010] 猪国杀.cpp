#include <bits/stdc++.h>
using namespace std;
bool _Debug = false;
void file_init(){
#ifndef ONLINE_JUDGE
    freopen("in","r",stdin);
    freopen("out","w",stdout);
#endif
    return ;
}
struct node{
    int K, D, P, F, N, W, J, Z;//手牌 杀：K 闪：D 桃：P 决斗：F 南猪入侵：N 万箭齐发：W 无懈可击：J 猪哥连弩：Z 
    int id, st, hp;//身份（1主猪， 2忠猪， 3反猪），状态（1跳忠，2跳反），血量
    int lst,nxt;
    bool z;
    bool Dead, pig_pig;//目前状态（0死了，1活着）, 类反猪判定（0不是，1是）
    string card_self;//自己目前持有卡牌
}e[11];
char card[2010];
int start, card_now=1, tips_L, tips_R, n, m, dead_cnt;//游戏开始位置，卡牌目前位置，全局锦囊牌右端点， 全局锦囊牌右端点，人数，卡牌数，死的人数
bool kill_cnt;//杀的限制
void card_delate(int go, char s){//删牌
	try{
		e[go].card_self.erase(e[go].card_self.find(s), 1);
	}
	catch(std::out_of_range x){
		cerr<<"Debug:"<<x.what()<<'\n';
	}
    return ;
}
void id_check(int i, string s){//身份标记
    if (s=="MP"){
        e[i].id=1; e[1].st = 1;
        start=i;
    }
    if (s=="ZP"){
        e[i].id=2;
    }
    if (s=="FP"){
        e[i].id=3;
    }
}
void card_check(int i, char s){//卡牌加加
    e[i].card_self+=s;
    if (s=='K'){
        e[i].K++;
    }
    if (s=='D'){
        e[i].D++;   
    }
    if (s=='P'){
        e[i].P++;
    }
    if (s=='F'){
        e[i].F++;
    }
    if (s=='N'){
        e[i].N++;
    }
    if (s=='W'){
        e[i].W++;
    }
    if (s=='J'){
        e[i].J++;
    }
    if (s=='Z'){
        e[i].Z++;
    }
    return ;
}
void gameover_check(){//判断游戏是否结束
    bool flag_mp=1, flag_fp=0;//判断主猪是否胜存活（0死亡，1存活），判断反猪是否存活（0死亡，1存活）
    for (int i=1; i<=n; i++){
        if (e[i].id==1&&!e[i].Dead){//若主猪已经死亡
            flag_mp=0;//毁灭吧！！！！！
        }
        if (e[i].id==3&&e[i].Dead){//若反猪还有存活的
            flag_fp=1;//人在，阵地在！
        }
    }
    if (flag_mp&&flag_fp){
        return;
    }
    if (!flag_mp){
        cout << "FP\n";
    }
    if (!flag_fp){
        cout << "MP\n";
    }
    for (int i=1; i<=n; i++){
        if (!e[i].Dead){//若该角色已经死亡
            cout << "DEAD\n";//输出已死亡
        }else{
            for (int j=0; j<e[i].card_self.size(); j++){//否则输出他的所有手牌
                cout << e[i].card_self[j] << " ";
            }
            cout << endl;
        }
    }
	cout << "\n";
    exit(0);
}
void dead(int go, int now){//死亡判定
    if (e[now].hp > 0){
        return;
    }
    if(e[now].P){
        e[now].hp++;
        e[now].P--;
if (_Debug)	cerr << e[now].card_self << " -> " << 'P' << "\n";
        card_delate(now,'P');
if (_Debug)	cerr << e[now].card_self << " : ED\n";
        return ;
    }
    e[now].Dead=0;
    dead_cnt++;
    gameover_check();//检测游戏是否结束
    if (e[now].id==3){//杀反猪奖励
        for (int i=1; i<=3; i++){
            card_check(go, card[card_now]);
            if(card_now<m){
                card_now++;
            }
        }
    }
    if (e[go].id==1&&e[now].id==2){//主猪杀忠猪惩罚
        e[go].card_self.clear();
        e[go].K=0;
        e[go].D=0;
        e[go].P=0;
        e[go].F=0;
        e[go].N=0;
        e[go].W=0;
        e[go].J=0;
        e[go].Z=0;
        e[go].z=false;
    }
    e[e[now].lst].nxt=e[now].nxt;
    e[e[now].nxt].lst=e[now].lst;
    return ;
}
void kill_check(int go, int now){//杀结算
    if (e[now].D){//闪判定
        e[now].D--;
if (_Debug)	cerr << e[now].card_self << " -> " << 'D' << "\n";
        card_delate(now, 'D');
if (_Debug)	cerr << e[now].card_self << " : ED\n";
    }else{//无闪，减血
        e[now].hp--;
        dead(go, now);
    }
    return ;
}
bool Round(int go, int st) {//循环判定之——无懈可击！(1:成功反制！0：失败了qwq)
	bool flag = false;
	for(int now=go;now!=go || !flag;now=e[now].nxt){
		int now_st = (e[now].id == 3 ? 2 : 1); // 当前猪身份
		if (now_st == st && e[now].J) {
			// cerr << now << " " << e[now].W << "\n";
			e[now].J--; e[now].st = now_st;
if (_Debug)	cerr << e[now].card_self << " ->1 " << 'J' << "\n";
			card_delate(now, 'J');
if (_Debug)	cerr << e[now].card_self << " : ED\n";
			return Round(now, 3 - st) ^ 1;
		}
		if (now == go) flag = true;
	}
	return false; // 反制失败
}
void dule_check(int go, int now){//决斗结算
	if (Round(go, e[now].st)) return;
    if (e[go].id==1&&e[now].id==2){//忠猪对主猪
        e[now].hp--;
        dead(go, now);
        return;
    }
    if (e[go].K<e[now].K){//打不过...
        e[now].K--;
if (_Debug)	cerr << e[now].card_self << " -> " << 'K' << "\n";
        card_delate(now,'K');
if (_Debug)	cerr << e[now].card_self << " : ED\n";
        swap(go, now);//交换攻防...
    }
    e[go].K-=e[now].K;//打他猪的！
    int a=e[now].K;//临时储存
    e[now].K=0;
    for (int i=1; i<=a; i++){//删牌
if (_Debug)	cerr << e[go].card_self << " -> " << 'K' << "\n";
        card_delate(go, 'K');
if (_Debug)	cerr << e[go].card_self << " : ED\n";
if (_Debug)	cerr << e[now].card_self << " -> " << 'K' << "\n";
        card_delate(now, 'K');
if (_Debug)	cerr << e[now].card_self << " : ED\n";

    }
    e[now].hp--;
    dead(go, now);
}
bool card_put(int go, char put){//出牌
    if(put=='Z'){ // 猪哥连弩
        e[go].Z--;
if (_Debug)	cerr << e[go].card_self << " -> " << put << "\n";
        card_delate(go,put);
if (_Debug)	cerr << e[go].card_self << " : ED\n";
        kill_cnt=0;
        e[go].z=1;
        return 1;
    }
    if(put=='F'){ // 决斗！
        if(e[go].id==3){
			e[go].F--;
            e[go].st=2;//跳反
if (_Debug)	cerr << e[go].card_self << " -> " << put << "\n";
            card_delate(go,put);
if (_Debug)	cerr << e[go].card_self << " : ED\n";
            dule_check(go,start);
            return 1;
        }
        for(int now=e[go].nxt;now!=go;now=e[now].nxt){
            bool flag=0;
            if (e[go].id==1&&(e[now].st==2||e[now].pig_pig)){//主猪满足杀猪条件
                flag=1;
            }
            if (e[go].id==2&&e[now].st==2){//忠猪满足杀猪条件
                e[go].st=1, e[go].pig_pig=0;//跳忠
                flag=1;
            }
            if(flag){
				e[go].F--;
if (_Debug)	cerr << e[go].card_self << " -> " << put << "\n";
                card_delate(go,put);
if (_Debug)	cerr << e[go].card_self << " : ED\n";
                dule_check(go,now);
                return 1;
            }
        }
    }
    if (put=='K'&&!kill_cnt){//K:杀判定+F判定（杀和决斗的代码很像，放一起节省空间）
        bool flag=0;//是否杀到猪
        int now=e[go].nxt;
        if (e[go].id==1&&(e[now].st==2||e[now].pig_pig)){//主猪满足杀猪条件
            flag=1;
        }
        if (e[go].id==2&&e[now].st==2){//忠猪满足杀猪条件
            e[go].st=1, e[go].pig_pig=0;//跳忠
            flag=1;
        }
        if (e[go].id==3&&(e[now].id==1||e[now].st==1)){//反猪满足杀猪条件
            e[go].st=2;//跳反
            flag=1;
        }
        if (flag){
            e[go].K--;//牌的数量--
if (_Debug)	cerr << e[go].card_self << " -> " << put << "\n";
            card_delate(go,put);
if (_Debug)	cerr << e[go].card_self << " : ED\n";
            kill_check(go, now);//杀猪判定
            if (!e[go].z){//判断有没有猪哥连弩
                kill_cnt=1;//若没有，杀人限制开启
            }
            return 1;
        }
    }
    if (put=='P'&&e[go].hp<4){//D:桃判定
        e[go].P--;
if (_Debug)	cerr << e[go].card_self << " -> " << put << "\n";
        card_delate(go,put);
if (_Debug)	cerr << e[go].card_self << " : ED\n";
        e[go].hp++;
        return 1;
    }
    if (put=='N'||put=='W'){//南猪入侵和万箭齐发
		if (put == 'N') e[go].N--;
		if (put == 'W') e[go].W--;
if (_Debug)	cerr << e[go].card_self << " ->2 " << put << "\n";
        card_delate(go,put);
if (_Debug)	cerr << e[go].card_self << " : ED\n";
        for(int now=e[go].nxt;now!=go;now=e[now].nxt){
            if (e[now].st!=0 && Round(go, e[now].st)){//已经跳了
				continue;
            }
			//没跳身份/救援失败
			if (put=='N'){//南猪入侵
				if (e[now].K){
					e[now].K--;
if (_Debug)	cerr << e[now].card_self << " -> " << 'K' << "\n";
					card_delate(now, 'K');
if (_Debug)	cerr << e[now].card_self << " : ED\n";
				}else{
					if(now==1&&e[go].st==0){
						e[go].pig_pig=1;
					}
					e[now].hp--;
					dead(go, now);
				}
			}else{//万箭齐发
				if (e[now].D){
					e[now].D--;
if (_Debug)	cerr << e[now].card_self << " -> " << 'D' << "\n";
					card_delate(now, 'D');
if (_Debug)	cerr << e[now].card_self << " : ED\n";
				}else{
					if(now==1&&e[go].st==0){
						e[go].pig_pig=1;
					}
					e[now].hp--;
					dead(go, now);
				}
			}
        }
        return 1;
    }
    return 0;
}
int main(){
    // file_init();
    cin >> n >> m;//n=3 m=10                                                                 check
    for (int i=1; i<=n; i++){
        e[i].hp=4, e[i].Dead=1;
        string s;
        cin >> s;
        id_check(i, s);//                                                                    check
        char ch;
        for (int j=1; j<=4; j++){
            cin >> ch;
            card_check(i, ch);//                                                             check
        }
        e[i].nxt=i+1;
        e[i].lst=i-1;
    }
    e[1].lst=n;
    e[n].nxt=1;
    for (int i=1; i<=m; i++){
        cin >> card[i];//                                                                    check
    }
    int round=0,now=start;
if (_Debug)cout << start << "\n";
    while(1){
        gameover_check();//检测游戏是否结束                                                   check
        // cout << "Debug1\n";
        // cerr<<++round<<"\n";
        kill_cnt=0;//杀人限制重置
        for (int j=1; j<=2; j++){//摸牌阶段
            card_check(now, card[card_now]);
            if(card_now<m){
                card_now++;
            }
        }
if (_Debug){
		cout << "-----" << now << "-----\n";
		for (int k = 1; k <= n; k++) {
			cout << e[k].hp << " " << e[k].card_self << "\n";
		}
		cout << "^\n|\n";
}
        for (int j=0; j<e[now].card_self.size(); j++){
            if (card_put(now, e[now].card_self[j])){//检测是否使用该卡
                j=-1;
if (_Debug){     for (int k = 1; k <= n; k++) {
					cout << e[k].hp << " " << e[k].card_self << "\n";
				}
				cout << "^\n|\n";
}
				if(!e[now].Dead){
					break;
                }
            }
        }
if (_Debug)	cerr<<"\n";
        now=e[now].nxt;
    }

    return 0;
}
/*
5 1
2 1
terminate called after throwing an instance of 'std::out_of_range'
  what():  basic_string::erase: __pos (which is 18446744073709551615) > this->size() (which is 3)

*/