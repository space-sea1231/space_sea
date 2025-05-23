#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int N=2e2+10;
const int K=10;

int n;
int cnt=1;
int max_sum[K]={0, 1, 3, 5, 9, 16, 41};
string position[K]={"", "BangZhu", "FuBangZhu", "HuFa", "ZhangLao", "TangZhu", "JingYing", "BangZhong"};

struct Person{
	string name, position;
	int score, level, id;
}person[N], bangzhu, fubangzhu[K];

int Change(string a){
	for (int i=1; i<=7; i++){
		if (a==position[i]){
			return i;
		}
	}
	return 0; 
}

bool Cmp(Person a, Person b){
	if (a.score==b.score){
		return a.id<b.id;
	}
	return a.score>b.score;	
}

bool Cmp1(Person a, Person b){
	if (Change(a.position)==Change(b.position)){
		if (a.level==b.level){
			return a.id<b.id;
		}
		return a.level>b.level;
	}
	return Change(a.position)<Change(b.position);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> person[i].name >> person[i].position >> person[i].score >> person[i].level;
		person[i].id=i;
		/*Debug*/
		// printf("Debug: 1:%s 2:%s 3:%d\n", person[cnt].name.c_str(), person[cnt].position.c_str(), person[cnt].level);
	}
	sort(person+4, person+n+1, Cmp);
	for (int i=1; i<=n; i++){
		person[i].position=position[cnt];
		if (i>=max_sum[cnt]&&cnt!=7){
			cnt++;
		}
	}
	sort(person+1, person+n+1, Cmp1);
	for (int i=1; i<=n; i++){
		printf("%s %s %d\n", person[i].name.c_str(), person[i].position.c_str(), person[i].level);
	}
	
	return 0;
}