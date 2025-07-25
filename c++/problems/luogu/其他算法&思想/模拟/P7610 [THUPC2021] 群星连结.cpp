#include <bits/stdc++.h>
using namespace std;
struct node{
	int HP, maxHP;//每个角色的血量及血量上限 
	int MP=0, maxMP;//每个角色的能量及能量上限 
	int atk, delta_atk=0;//每个角色的基础攻击力和攻击力增益 
	int def, delta_def=0;//每个角色的基础防御力和防御力增益 
	int talent, talent_x, talent_y;//天赋及附加参数 
	int skill, skill_x, skill_y, skill_z;//技能及附加参数 
	int target, id;//当前的攻击目标，自己的编号
	bool live, team;//是否活着，是哪个阵营的人
}player[11][2];//1:Alice, 0:Bob
int player_role[11][11][2];//用于记录每个角色的优先目标 1:Alice, 0:Bob
int delta_MP[23334][2], delta_def[23334][2], delta_atk[23334][2];//能量值, 防御力和攻击力增益
int n, player_live[2], game_round;//场上还活着的人数 1:Alice, 0:Bob
int ql, ql_flag;//技能：“全力超全开！轮回之终末！”的暴毙机制
const char *ATS[11]={"My_ability_suck","Mana_burn","ICBM","Big_sword","Start_the_show","Slash","Blue_lighting","Aurora","Shooting_Star","Sprite_bless","End_the_circle"};
int read(){//快读(check)
    char c=getchar();
    int sum=0, flag=1;
    while (c<'0'||c>'9'){
        if (c=='-'){
            flag=-1;
        }
        c=getchar();
    }
    while (c>='0'&&c<='9'){
        sum=(sum<<1)+(sum<<3)+(c^48);
        c=getchar();
    }
    return sum*flag;
}
void player_read(int now, bool flag){//player读入(check)
	node *a=&player[now][flag];//为方便创个指针修改
    a->maxHP=a->HP=read();
    a->maxMP=read();
    a->atk=read();
    a->def=read();
    for (int j=1; j<=n; j++){//读入优先攻击目标 
        player_role[now][j][flag]=read();
    }
    a->talent=read();
    a->talent_x=read();
    a->talent_y=read();
    a->skill=read();
    a->skill_x=read();
    a->skill_y=read();
    a->skill_z=read();
    a->live=1;
	a->id=now;
	a->team=flag;
    a->target=player_role[now][1][flag];
}
bool game_over(){//判断游戏结束（0结束，1没结束）(check)
    for (int flag=0; flag<=1; flag++){
		if (!player_live[flag]){//(1:Alice, 0:Bob)人全死光
			cout << game_round << endl;
			if (flag){
				cout << "Bob\n";
			}else{
				cout << "Alice\n";
			}
			for (int i=1; i<=n; i++){
				cout << player[i][!flag].HP << " ";
			}
			// cout << endl;
			// for (int i=1; i<=n; i++){
			// 	cout << player[i][flag].HP << " ";
			// }
			exit(0);
		}
	}
    return 1;
}
void MP_plus(node *a, int sum){//加能量（真的吗？）(check)
//	printf("%d mana %d\n",a->id,sum);
	a->MP+=sum;
	if (a->MP>=a->maxMP){
		a->MP=a->maxMP;
	}
}
void HP_plus(node *a, int sum){//加血(check)
//	printf("%d heal %d\n",a->id,sum);
	a->HP+=sum;
	if (a->HP>=a->maxHP){
		a->HP=a->maxHP;
	}
}
void dead(node *a){//判断人死没死（0死了，1没死）(check)
	if (a->HP<=0){//死了？
//		printf("%d died\n",a->id);
		a->live=a->HP=0;//死了。
		// cout << a->id << " " << a->HP << endl;
		player_live[a->team]--;
		for (int i=1; i<=n; i++){
			node *b=&player[i][!a->team];//为方便创个指针修改
			if (b->target==a->id){//优先目标死亡
				for (int j=1; j<=n; j++){
					int *c=&player_role[i][j][!a->team];//为方便创个指针修改
					if (player[*c][a->team].live){//《活着》
						b->target=*c;//更新优先目标
						j=n;
					}
				}
			}
		}
		game_over();
	}
}
int A(node *a){//攻击力计算(check)
	return max(1, a->atk+a->delta_atk+delta_atk[game_round][a->team]);
}
int D(node *a){//防御力计算(check)
	return max(0, a->def+a->delta_def+delta_def[game_round][a->team]);
}
void atack(node *a, int atk){//普通伤害(check)
	a->HP-=max(0, atk-D(a));//扣血
	dead(a);//判死亡
}
void real_atack(node *a, int atk){//真实伤害(a->talent==1?atk/2:atk)
	a->HP-=atk-(a->talent==1?atk/2:0);//扣血
	dead(a);//判死亡
}
void player_skill(node *a){//(1:Alice, 0:Bob)阵营的now角色发动了技能
//	printf("move:%s->%d use ability %s\n",a->team?"Alice":"Bob",a->id,ATS[a->skill]);
	a->MP=0;//清空能量条发动技能
	int skill=a->skill;//为方便创个变量储存
	int skill_x=a->skill_x;//为方便创个变量储存
	int skill_y=a->skill_y;//为方便创个变量储存
	int skill_z=a->skill_z;//为方便创个变量储存
	if (skill==0){//技能：心态崩了！
		//P用没有
	}
	if (skill==1){//技能：格林炸裂！
		for (int i=1; i<=n; i++){//扣血
			node *b=&player[i][!a->team];//为方便创个指针修改
			if (b->live){//《活着》
				atack(b, skill_x);
				MP_plus(b, 1);
				MP_plus(b, -int(b->MP/10));
			}
		}
	}
	if (skill==2){//技能: 日(zhou)昇(ji)之(dao)雨(dan)！
		for (int i=1; i<=n; i++){
			node *b=&player[i][!a->team];//为方便创个指针修改
			if (b->live){//《活着》
				real_atack(b, A(a));
				MP_plus(b, 1);
			}
		}
	}
	if (skill==3){//技能：天楼霸断剑！
		for (int i=1; i<=n; i++){
			node *b=&player[i][!a->team];//为方便创个指针修改
			if (b->live){//《活着》
			
				atack(b, min(b->maxHP/10, skill_x*A(a)));
				MP_plus(b, 1);
			}
		}
	}
	if (skill==4){//技能：演出开始！
		for (int i=game_round; i<=game_round+skill_x-1&&i<=23333; i++){
			delta_MP[i][a->team]+=skill_y;
		}
	}
	if (skill==5){//技能：天狼噬斩！
		node *b=&player[a->target][!a->team];
		b->delta_def-=a->skill_x;
		if (b->live){//《活着》
			real_atack(b, A(a));
			MP_plus(b, 1);
		}
		// real_atack(b, A(a));
	}
	if (skill==6){//技能：地(太)球(虚)蓝(苍)色(蓝)闪(闪)电！
		node *b=&player[a->target][!a->team];
		if (b->live){//《活着》
			real_atack(b, A(a));
			MP_plus(b, 1);
		}
		// real_atack(b, A(a));
		for (int i=game_round; i<=game_round+skill_x-1&&i<=23333; i++){
			delta_atk[i][!a->team]-=skill_y;
		}
	}
	if (skill==7){//技能：极光绽放！
		int id=0;//储存编号
		for (int i=1; i<=n; i++){
			node *b=&player[i][a->team];//为方便创个指针修改
			if (b->live){//《活着》
				if (b->HP<player[id][a->team].HP||!id){
					id=i;
				}
			}
		}
		node *b=&player[id][a->team];
		HP_plus(b, skill_z);
		for (int i=game_round; i<=game_round+skill_x-1&&i<=23333; i++){
			delta_atk[i][a->team]+=skill_y;
		}
	}
	if (skill==8){//技能：流星！
		for (int i=1; i<=n; i++){
			node *b=&player[i][!a->team];//为方便创个指针修改
			if (b->live){//《活着》
				atack(b, A(a));
				MP_plus(b, 1);
			}
		}
		for (int i=game_round; i<=game_round+skill_x-1&&i<=23333; i++){
			delta_def[i][!a->team]-=skill_y;
		}
	}
	if (skill==9){//技能：精灵庇护！
		for (int i=1; i<=n; i++){
			node *b=&player[i][a->team];//为方便创个指针修改
			if (b->live){//活着
				HP_plus(b, skill_z);
			}
		}
		for (int i=game_round; i<=game_round+skill_x-1&&i<=23333; i++){
			delta_def[i][a->team]+=skill_y;
		}
	}
	if (skill==10){//技能：全力超全开！轮回之终末！
		for (int i=1; i<=n; i++){
			node *b=&player[i][a->team];
			if (b->live){//《活着》
				b->atk*=2, b->def*=2;//BUFF++
				b->HP=max(b->maxHP/2, b->HP);//BUFF++
				b->MP=max(b->maxMP/2, b->MP);//BUFF++
			}
			for (int j=0; j<=1; j++){//遍历两方角色
				node *c=&player[i][j];//为方便创个指针修改
				if (c->skill==10){//把所有10号技能变为0号技能
					c->skill=0;
				}
			}
		}
		for (int i=game_round; i<=game_round+skill_x-1&&i<=23333; i++){
			delta_MP[i][a->team]++;//BUFF++
		}
		ql=game_round+skill_x-1;//储存剩余可以存活到的回合
		ql_flag=a->team;//标记是哪一方的
	}
	MP_plus(a, 1);
	if (a->talent==5){//天赋 — 科技至上
		MP_plus(a, a->talent_y);
	}
	
}
int atack_sum(node *a){//生命值扣除总值(check)
	node *b=&player[a->target][!a->team];
	if (a->talent==2){
		return max(A(a)-D(b), 0)+a->talent_x-(b->talent==1?a->talent_x/2:0);
	}
	if (a->talent==4){
		return A(a)-(b->talent==1?A(a)/2:0);
	}
	return max(A(a)-D(b), 0);
}
void player_atack(node *a){//team(1:Alice, 0:Bob)阵营的now角色发动了普通攻击(check)
	node *b=&player[a->target][!a->team];
//	printf("move:%s->%d attack %d\n",a->team?"Alice":"Bob",a->id,a->target);
	MP_plus(b, 1);
	b->HP-=atack_sum(a);
	if (b->live){//《活着》
		dead(b);
	}
	// dead(b)
	if (a->talent==5){//天赋 — 科技至上
		HP_plus(a, a->talent_x);
	}
	MP_plus(a, 1);
}	
int main(){
//	freopen("My.txt","w",stdout);
    player_live[0]=player_live[1]=n=read();
    for (int flag=1; flag>=0; flag--){
		for (int i=1; i<=n; i++){
			player_read(i, flag);
		}
    }
    while (game_over()){
		game_round++;
//		printf("round:%d\n",game_round);
		for (int flag=1; flag>=0; flag--){
			int now_skill=-1, now_atack=0;
			int now_id=0;
        	for (int i=1; i<=n; i++){
				node *a=&player[i][flag];//为方便创个指针修改
				node *c=&player[now_atack][flag];//为方便创个指针修改
				if (a->live){//《活着》
					if (a->MP==a->maxMP&&(a->skill>=now_skill)){//蓝条满了&&(技能编号更大||目前无符合条件的角色
            			now_skill=a->skill;
            			now_id=i;
            		}
					if (player[a->target][!flag].HP>=player[c->target][!flag].HP||!now_atack){
						if (player[a->target][!flag].HP==player[c->target][!flag].HP){
							if (atack_sum(a)>=atack_sum(c)){
								now_atack=i;
								c=a;
							}
						}
						else{
							now_atack=i;
							c=a;
						}
					}
				}
			}
            if (now_skill!=-1){//可以发动技能
				node *a=&player[now_id][flag];
				player_skill(a);//flag(1:Alice, 0:Bob)阵营的now角色发动了技能
			}
			else{//不可发动技能
				node *a=&player[now_atack][flag];
				player_atack(a);//flag(1:Alice, 0:Bob)阵营的now角色发动了普通攻击
			}
//			printf("%s's round end\n",flag?"Alice":"Bob");
			for (int i=1; i<=n; i++){//能量值增益
				node *a=&player[i][flag];
				if (a->live){//《活着》
					MP_plus(a, delta_MP[game_round][flag]+1);
					if (a->talent==3){//天赋 — 心胜于物
						HP_plus(a, a->talent_x);
						MP_plus(a, a->talent_y);
					}
				}
			}
        }
		if (ql==game_round){
			for (int i=1; i<=n; i++){
				node *a=&player[i][ql_flag];
				a->HP=0;
				if (a->live){//《活着》
					dead(a);
				}
			}
		}
    }
    return 0;
}
/*
0.【天赋 — 我自闭了】该角色的天赋毫无作用；
1.【天赋 — 血肉皮囊】该角色免疫一半真实伤害。
2.【天赋 — 星河力量投射】(x) 该角色每次普通攻击会附加的x 点真实伤害；
3.【天赋 — 心胜于物】(x,y) 该角色每次己方行动结束后回复 x 点生命值，并额外回复 y 点能量值；
4.【天赋 — 超凡入圣】该角色的普通攻击被视为真实伤害攻击，即该角色的普通攻击不造成伤害，但造成 A 点真实伤害。
5.【天赋 — 科技至上】(x,y) 该角色每次进行普通攻击后，回复 x 点生命值；该角色每次发动技能后，额外回复 y 点能量值。注意：如果普通攻击或发动技能造成对方全部角色【死亡】，则该角色不再回复生命值或能量值。
*/

/*
0. 【技能：心态崩了！】该角色的主动技能毫无作用。
1. 【技能：格林炸裂！】(x)对敌方所有角色造成 x 点伤害，然后使敌方所有角色能量值减少 mp_enemy/10，其中 mp_enemy 为敌方该角色能量值（即对于每个敌方角色，若其当前的能量值为 mp_enemy，那么受此技能影响，其能量值会变成 mp_{enemy}-\left\lfloor\frac{mp_{enemy}}{10}\right\rfloor）。注意，根据规则，敌方角色会先受到伤害而进入生命值扣除环节，在该环节中回复能量值，然后再被该技能扣除能量值。
2. 【技能：日 (zhou) 昇 (ji) 之 (dao) 雨 (dan)！】对敌方所有角色造成 A 点真实伤害。
3. 【技能：天楼霸断剑！】(x)对敌方所有目标造成 min(HP_enemy/10,x*A) 点伤害，其中 HP_enemy 为被攻击目标的最大生命值。
4. 【技能：演出开始！】(x,y)设当前为第 t 回合，则从发动技能开始，到第 t+x-1 回合结束期间，在己方行动结束时，己方全体角色额外回复 y 点能量值。
5. 【技能：天狼噬斩！】(x) 将优先目标的防御力增益减小 x，然后对优先目标造成 A 点真实伤害。
6. 【技能：地 (太) 球 (虚) 蓝 (苍) 色 (蓝) 闪 (闪) 电！】(x,y) 对优先目标造成 A 点真实伤害。另外，设当前为第 t 回合，则从发动技能开始，到第 t+x-1 回合结束期间，敌方所有角色攻击力增益减小 y。
7. 【技能：极光绽放！】(x,y,z) 使己方未【死亡】角色生命值最低（如有多个，则编号最小）的恰好一名角色回复 z 点生命值。另外，设当前为第 t 回合，则从发动技能开始到第 t+x-1 回合结束期间，己方所有角色攻击力增益增大 y。
8. 【技能：流星！】(x,y) 对敌方所有角色造成 A 点伤害。设当前为第 t 回合，则从该技能造成伤害后，到第 t+x-1 回合结束期间，使敌方所有角色防御力增益减小 y。注意，本技能先造成伤害，再产生减益。
9. 【技能：精灵庇护！】(x,y,z) 己方全体角色回复 z 点生命值。设当前为第 t 回合，则从发动技能开始，到第 t+x-1 回合结束期间，己方所有角色防御力增益增大 y。
10. 【技能：全力超全开！轮回之终末！】(x) 己方所有角色基础攻击力 atk、基础防御力 def 变为原先的两倍 2*atk, 2*def；未【死亡】角色生命值 hp 变为 max(HP/2,hp)，能量值 mp 变为 max(MP/2,mp)；设当前为第 t 回合，则从发动技能开始，到第 t+x-1 回合结束期间，己方行动结束时，己方所有角色额外回复 1 点能量值。在第 t+x-1 回合结束时，若敌方仍有角色未【死亡】，则己方全体角色强制生命值清零，并被判定为【死亡】。另外，在发动该技能时，场上所有拥有这个技能的角色（包括自己）的技能将被强制替换为 0 号【技能：心态崩了！】（因此该技能最多在游戏中被发动一次）。
*/

/*
1.不要鞭尸
2.不要把优先攻击队列开成优先队列
3.寻找普通攻击者时不要直接比扣除的血量，优先找血量最高的
4.找发动的技能编号时值初始为-1，不然0号技能会gg
5.不要复活死人
6.天赋的结算不要漏掉，穿插在游戏的各个角落
7.释放技能时一定要先耗能量，尤其是10号技能，不然会gg
8.增益可以为负
9.放完技能或平A要回蓝
10.能量不够也是不能平A/放技能的
11.死人不能平A/放技能
12.随时都要判游戏是否结束
13.TLE了不要怀疑处理不够优，考虑死循环等情况
14.结算技能持续效果不要看错值，增益效果应当在第t+x-1回合结束时除去
15.血量低于零时记得归零
16.开10技能时记得把所有人的10技能设为0
17.0技能也是可以放的，清空蓝条
18.别把技能/天赋的x/y写反，真的很难找
19.技能标记的持续回合可能会超过23333，记得特判一下
20.蓝条不能为负
21.平A者优先序号大的，而不是小的
22.修改技能效果时不要把阵营搞反了
23.伤害和增减益效果顺序不要搞反
24.别忘了10号技能的额外回蓝
25.别忘了取max(x?D,0)
26.别忘了更新D/A的值
27.变量尽量别在不同函数中重名，但为了避免这个问题别取无意义变量名，真的很恶心，建议在i/j等常用名字前加上前缀
28.不要把什么技能都塞到一个函数里，会趋势
29.多去看看题解/讨论区的警钟，不要轻易放弃
30.凑个整qwq,加油
*/