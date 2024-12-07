#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t, n, ans;
int top_a=1, top_b=1;
int a[N], b[N];
int vis_a[N], vis_b[N];
struct node{
	int l, r;
	int cnt[2];
}q[N], p[N];
void init(){
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(vis_a, 0, sizeof(vis_a));
	memset(vis_b, 0, sizeof(vis_b));
	memset(q, 0, sizeof(q));
	memset(p, 0, sizeof(p));
	top_a=1, top_b=1;
	ans=0;
}
void Debug_1(){
	printf("Debug1: ");
	for (int i=1; i<=n; i++){
		printf("%d", a[i]);
	}
	printf("\n");
	printf("Debug1: ");
	for (int i=1; i<=n; i++){
		printf("%d", b[i]);
	}
	return ;
	printf("\n");
	printf("Debug1: ");
	for (int i=1; i<=n; i++){
		printf("%d", vis_a[i]);
	}
	printf("\n");
	printf("Debug1: ");
	for (int i=1; i<=n; i++){
		printf("%d", vis_b[i]);
	}
	printf("\n");
	printf("----------Q----------\n");
	for (int i=1; i<=top_a; i++){
		printf("%d %d %d %d\n", q[i].l, q[i].r, q[i].cnt[0], q[i].cnt[1]);
	}
	printf("\n");
	printf("----------P----------\n");
	for (int i=1; i<=top_b; i++){
		printf("%d %d %d %d\n", p[i].l, p[i].r, p[i].cnt[0], p[i].cnt[1]);
	}
	printf("\n");
}
int main(){
    freopen("edit.in", "r", stdin);
    freopen("edit.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie();
	cin >> t;
	while (t--){
		init();
		/*----------输入----------*/
		cin >> n;
		for (int i=1; i<=n; i++){
			char c;
			cin >> c;
			a[i]=c-'0';
		}
		for (int i=1; i<=n; i++){
			char c;
			cin >> c;
			b[i]=c-'0';
		}
		for (int i=1; i<=n; i++){
			char c;
			cin >> c;
			vis_a[i]=c-'0';
		}
		for (int i=1; i<=n; i++){
			char c;
			cin >> c;
			vis_b[i]=c-'0';
		}
		/*----------特殊情况----------*/
		bool flag=0;
		for (int i=1; i<=n; i++){
			if (vis_a[i-1]==0&&vis_a[i+1]==0){
				vis_a[i]=0;
			}
			if (vis_a[i]){
				if (flag){
					q[top_a].r++;
				}else{
					q[top_a].l=i;
					q[top_a].r=i;
					flag=1;
				}
				q[top_a].cnt[a[i]]++;
			}else{
				if (flag){
					flag=0;
					top_a++;
				}
			}
		}
		if (flag==0){
			top_a--;
		}
		flag=0;
		for (int i=1; i<=n; i++){
			if (vis_b[i-1]==0&&vis_b[i+1]==0){
				vis_b[i]=0;
			}
			if (vis_b[i]){
				if (flag){
					p[top_b].r++;
				}else{
					p[top_b].l=i;
					p[top_b].r=i;
					flag=1;
				}
				p[top_b].cnt[b[i]]++;
			}else{
				if (flag){
					flag=0;
					top_b++;
				}
			}
		}
		if (flag==0){
			top_b--;
		}
		// Debug_1();
		/*----------solve----------*/
		int l=1, r=1;
		bool flag_a=0, flag_b=0;
		for (int i=1; i<=n; i++){
			if (q[l].r+1==i){
				l++;
				flag_a=0;
			}
			if (p[r].r+1==i){
				r++;
				flag_b=0;
			}
			if (q[l].l==i){
				flag_a=1;
			}
			if (p[r].l==i){
				flag_b=1;
			}


			if (flag_a==0&&flag_b==0){
				if (a[i]==b[i]){
					ans++;
				}
			}


			if (flag_a&&flag_b==0){
				if (q[l].cnt[b[i]]>0){
					q[l].cnt[b[i]]--;
					ans++;
				}
			}
			if (flag_a==0&&flag_b){
				if (p[r].cnt[a[i]]>0){
					p[r].cnt[a[i]]--;
					ans++;
				}
			}



			if (flag_a&&flag_b){
				if (q[l].cnt[a[i]]==0){
					if (a[i]==0){
						a[i]=1;
					}else{
						a[i]=0;
					}
				}
				if (p[r].cnt[b[i]]==0){
					if (b[i]==0){
						b[i]=1;
					}else{
						b[i]=0;
					}
				}



				if (a[i]==b[i]){
					if (q[l].cnt[a[i]]>0&&p[r].cnt[a[i]]>0){
						q[l].cnt[a[i]]--;
						p[r].cnt[a[i]]--;
						ans++;
					}
					continue;
				}
				if (p[r].cnt[a[i]]>0){
					p[r].cnt[a[i]]--;
					q[l].cnt[a[i]]--;
					b[i]=a[i];
					ans++;
				}else if (q[l].cnt[b[i]]>0){
					q[l].cnt[b[i]]--;
					p[r].cnt[b[i]]--;
					a[i]=b[i];
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}

    return 0;
}
/*
35 49 14 1
35 49 7 8
*/