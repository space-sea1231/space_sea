#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(time(0));
    int T=rand()%3+1;
    cout<<T<<"\n";
    while(T--){
        int n=rand()%10+2;
        int k=rand()%n+1;
        cout<<n<<" "<<k<<"\n";

        vector<vector<pair<int,int>>> ch(n+1);
        vector<int> ord;
        ord.push_back(k);
        for(int i=1;i<=n;i++) if(i!=k) ord.push_back(i);
        for(int i=1;i<(int)ord.size();i++){
            int j=i+rand()%((int)ord.size()-i);
            swap(ord[i],ord[j]);
        }
        for(int i=1;i<(int)ord.size();i++){
            int p=ord[rand()%i];
            int w=rand()%5+1;
            ch[p].push_back({ord[i],w});
        }

        for(int i=1;i<=n;i++){
            if(ch[i].empty()){
                cout<<"0 "<<rand()%10000+1<<"\n";
            }else{
                cout<<"1 "<<ch[i].size();
                for(auto [v,w]:ch[i]){
                    cout<<" "<<w<<" "<<v;
                }
                cout<<"\n";
            }
        }
    }
    return 0;
}