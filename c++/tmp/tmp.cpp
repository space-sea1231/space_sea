#include <iostream>
#include <stdio.h>

using namespace std;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string sa="abc";
	char *sptr=&sa[0];
	int ia=1, *iptr=&ia;
	*(sptr)++;
	printf("Debug1: %p\n", sptr);
	*(sptr)++;

	printf("%s %p->%s\n", sa.c_str(), sptr, sptr);
	printf("%d %p->%d\n", ia, iptr, *iptr);

	return 0;
}