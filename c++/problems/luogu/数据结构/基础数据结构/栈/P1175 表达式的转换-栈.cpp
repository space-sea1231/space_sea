#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
const int INF=1<<30;
int top_ans, top_tmp, top_num;
char ans[N], tmp[N];
int num[N];
string s;
int level(char c){
	if (c=='('||c==')'){
		return 0;
	}
	if (c=='+'||c=='-'){
		return 1;
	}
	if(c=='*'||c=='/'){
		return 2;
	}
	if (c=='^'){
		return 3;
	}
	return -1;
}
int mi(int a, int b){
	int sum=1;
	while (b){
		if (b&1){
			sum=sum*a;
		}
		a=a*a;
		b>>=1;
	}
	return sum;
}
int go(int x, int y, char z){
	// printf("Debug2: %d %d %c\n",x, y, z);
	if (z=='+'){
		return x+y;
	}
	if (z=='-'){
		return x-y;
	}
	if (z=='*'){
		return x*y;
	}
	if (z=='/'){
		return x/y;
	}
	if (z=='^'){
		return mi(x, y);
	}
	return -INF;
}
void change(){
	for (int i=0; i<s.size(); i++){
		if (s[i]>='0'&&s[i]<='9'){//数字
			ans[++top_ans]=s[i];
		}else if (s[i]=='('){
			tmp[++top_tmp]=s[i];
		}else if (s[i]==')'){//处理括号
			while (tmp[top_tmp]!='('){
				ans[++top_ans]=tmp[top_tmp--];
			}
			top_tmp--;
		}else if (level(s[i])!=-1){
			while (top_tmp&&level(s[i])<=level(tmp[top_tmp])){//弹出操作
				if (s[i]=='^'&&tmp[top_tmp]=='^'){//乘方特殊运算法则
					break;
				}
				ans[++top_ans]=tmp[top_tmp--];//栈顶元素转移
			}
			tmp[++top_tmp]=s[i];//新元素入栈
		}	
	}
	while(top_ans){//再压回去...
		tmp[++top_tmp]=ans[top_ans--];
	}
	for (int i=top_tmp; i>=1; i--){
		printf("%c ", tmp[i]);
	}
	printf("\n");
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> s;
	change();
	while (top_tmp){
		if (tmp[top_tmp]>='0'&&tmp[top_tmp]<='9'){
			num[++top_num]=tmp[top_tmp--]-'0';
		}else{
			int x=num[top_num--];
			int y=num[top_num--];
			// printf("Debug: %d %d %c %d\n", x, y, tmp[top_tmp], go(y, x, tmp[top_tmp]));
			num[++top_num]=go(y, x, tmp[top_tmp--]);
			for (int i=1; i<=top_num; i++){
				printf("%d ", num[i]);
			}
			for (int i=top_tmp; i>=1; i--){
				printf("%c ", tmp[i]);
			}
			printf("\n");
		}
	}

	return 0;
}