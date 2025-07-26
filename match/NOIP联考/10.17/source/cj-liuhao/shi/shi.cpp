#include <bits/stdc++.h>
using namespace std;

namespace mci {
	int t,n,rs;
	char a[1919810];
	vector<int> ans;
	
	char nand (char a,char b) {
		return a=='0'&&b=='0'? '1': '0';
	}
	
	int main () {
		cin>> t;
		while (t--) {
			cin>> (a+1);
			n=strlen (a+1);
			ans.clear ();
			for (int i=2;i<n;i++)
				if (a[i]=='0') {
					if (a[i-1]=='0') {
						a[i-1]=nand (a[i-1],a[i]);
						a[i+1]=nand (a[i+1],a[i]);
						ans.push_back (i);
					} else if (a[i-1]=='1'&&a[i+1]=='1'){
						a[i-1]=nand (a[i-1],a[i]);
						a[i+1]=nand (a[i+1],a[i]);
						ans.push_back (i);
					}
				}
			rs=0;
			for (int i=1;i<=n;i++)
				rs+=a[i]=='1';
			cout<< rs<< " "<< ans.size ()<< "\n";
			for (int i: ans)
				cout<< i<< " ";
			cout<< "\n";
		}
		return 0;
	}
}

int main () {
	freopen ("shi.in","r",stdin);
	freopen ("shi.out","w",stdout);
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	return mci::main ();
}
