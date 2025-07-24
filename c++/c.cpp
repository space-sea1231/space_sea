#include <iostream>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;
vector<int> v;
signed main(){
  v.reserve(1e6);
    v.push_back(1);
    for(int i:v){
      v.push_back(i);
    }
    return 0;
}