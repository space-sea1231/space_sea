> 按数位从高位到底位转移的DP

**使用场景：**

求一个区间$[L,R]$中满足条件的数的个数

**算法实现：**

1.  预处理,维护i位数中满足条件的数的个数。
2.  统计答案，求 $[1,R]$中满足条件的个数 $[1,L-1]$中满足条件的个数

1.  设求 $[1,x]$中满足条件的元素个数
2.  直接累加前$cnt-1$位数的答案，因为这些数小$x$
3.  统计数位恰好是$cnt$位数的答案，依次枚举$x$的前缀

## 例题

### 不要62

[传送门](https://vjudge.csgrandeur.cn/problem/HDU-2089#author=0)

#### 预处理

```cpp
void init(){
    dp[0][0]=1;
    for(int i=1;i<=7;i++){
        for(int j=0;j<10;j++){
            for(int k=0;k<10;k++){
                if(j!=4&&!(j==6&&k==2)){
                    dp[i][j]+=dp[i-1][k];
                }
            }
        }
    }
}
```

#### 求答案

```cpp
int helper(int x){
    int cnt=0;
    while(x>0){
        digit[++cnt]=x%10;
        x/=10;
    }
    digit[++cnt]=0;
    int ans=0;
    for(int i=cnt-1;i>=1;i--){
        for(int j=0;j<digit[i];j++){
            if(j!=4&&!(j==2&&digit[i+1]==6)){
                ans+=dp[i][j];
            }
        }
        if(digit[i]==4||(digit[i]==2&&digit[i+1]==6))break;
    }
    return ans;
}
```

### beautiful number

[传送门](https://vjudge.csgrandeur.cn/problem/HDU-5179#author=GPT_zh)

#### 状态

$dp_{i,j}$表示 $i$位数且高位为 $j$的合法数字个数。

#### 预处理

```cpp
void init(){
    dp[0][0]=1;
    for(int i=1;i<=9;i++)dp[1][i]=1;
    for(int i=2;i<=9;i++){
        for(int j=1;j<10;j++){
            for(int k=1;k<10;k++){
                if(j>=k&&j%k==0){
                    dp[i][j]+=dp[i-1][k];
                }
            }
        }
    }
}
```

#### 求答案

```cpp
int helper(int n){
	int cnt = 0;
	while(n != 0){
		a[++cnt] = n % 10;
		n /= 10;
	}
	int ans = 0;
	for(int i = 1 ; i <= cnt - 1 ; i++){
		for(int j = 1 ; j <= 9 ; j++){
			ans += dp[i][j];
		}
	}
	for(int i = 1 ; i < a[cnt] ; i++){
		ans += dp[cnt][i];
	}
	for(int i = cnt - 1 ; i >= 1 ; i--){
		for(int j = 1 ; j < a[i] ; j++){
			if(a[i + 1] >= j && a[i + 1] % j == 0){
				ans += dp[i][j];
			}
		}
		if(a[i] == 0 || a[i] > a[i + 1] || (a[i + 1] % a[i] != 0)){
			break;
		}
	}
	return ans;
}
```

### P2657 [SCOI2009] windy 数

#### 预处理

```cpp
void init(){
    for(int i=0;i<=9;i++)dp[1][i]=1;
    for(int i=2;i<=10;i++){
        for(int j=0;j<10;j++){
            for(int k=0;k<10;k++){
                if(abs(j-k)>=2){
                    dp[i][j]+=dp[i-1][k];
                }
            }
        }
    }
}
```

#### 求答案

```cpp
int helper(int x){
    int cnt=0;
    while(x>0){
        digit[++cnt]=x%10;
        x/=10;
    }
    int ans=0;
    for(int i=1;i<=cnt-1;i++){
        for(int j=1;j<=9;j++){
            ans+=dp[i][j];
        }
    }
    digit[++cnt]=13;
    for(int i=cnt-1;i>=1;i--){
        int j;
        if(i==cnt-1)j=1;
        else j=0;
        for(;j<digit[i];j++){
            if(abs(digit[i+1]-j)>=2){
                ans+=dp[i][j];
            }
        }
        if(abs(digit[i]-digit[i+1])<2)break;
    }
    return ans;
}
```

### P2602 [ZJOI2012]数字计数

对于 $1 \sim 10$，分别跑一遍`helper(R+1,i)-helper(L,i)`即可。

#### 预处理

```cpp
void init()
{
	for(int k=0;k<=9;k++)
		dp[1][k][k]=1;
	for(int i=2;i<=13;i++)
		for(int j=0;j<=9;j++)
		{
			for(int p=0;p<=9;p++)
				for(int k=0;k<=9;k++)
					dp[i][j][k]+=dp[i-1][p][k];
			dp[i][j][j]+=pow(10,(signed)(i-1));
		}
	return ;
}
```

#### 求答案

```cpp
int helper(int x,int id)
{
	int cnt=0;
	while(x!=0)
	{
		digit[++cnt]=x%10;
		x/=10;
	}
	int ans=0;
	for(int i=1;i<=cnt-1;i++)
		for(int j=1;j<=9;j++)
			ans+=dp[i][j][id];
	for(int i=1;i<digit[cnt];i++)
		ans+=dp[cnt][i][id];
	for(int i=cnt-1;i>=1;i--)
	{
		for(int j=0;j<digit[i];j++)
			ans+=dp[i][j][id];
		for(int p=cnt;p>=i+1;p--)
			if(digit[p]==id)
				ans+=1ll*digit[i]*pow(10,(signed)(i-1));
	}
	return ans;
}
```