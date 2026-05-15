// namespace FileIO{
//     void Test(string s){
//         freopen((s+".in").c_str(),"r",stdin);
//         freopen("test.out","w",stdout);
//     }
//     void File(string s){
//         freopen((s+".in").c_str(),"r",stdin);
//         freopen((s+".out").c_str(),"w",stdout);
//     }
// }
namespace FastIO{
    const int BUF_L=1<<20;
    char ibuf[BUF_L];
    char obuf[BUF_L];
    char *po=obuf;
    char *pl=ibuf,*pr=ibuf;
    inline char getchar(){
        if(pl==pr){
            pr=ibuf+fread(ibuf,1,BUF_L,stdin),pl=ibuf;
            if(pl==pr){
                return EOF;
            }
        }
        return *pl++;
    }
    void read(){

    }
    template<typename T>void read(T &res){
        bool neg=0;
        res=0;
        char ch=getchar();
        while(ch<'0'||ch>'9'){
            if(ch=='-') neg=1;
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            res=(res<<3)+(res<<1)+(ch^48);
            ch=getchar();
        }
        if(neg) res=-res;
    }
    template<typename... Arg>void read(Arg&... args){
        initializer_list<int>{(read(args),0)...,0};
    }
}