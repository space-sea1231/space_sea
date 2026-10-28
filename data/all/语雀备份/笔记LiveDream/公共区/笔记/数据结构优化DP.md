## 线段树优化DP

### P4644 [USACO05DEC] Cleaning Shifts S

#### 题意

1.  n头牛，[m,e]的时段
2.  已知第i头牛的工作起始和结束时间，以及工资a[i].x，a[i].y，a[i].s
3.  每个时段至少有1头牛在工作，牛的工资全额发放

目标：求覆盖m到e每个时段最少花多少钱。

#### 基础做法

1.  状态dp[i]表示覆盖从m到i的时段的最小花费
2.  答案：dp[e]
3.  状态转移:

```cpp
if(a[i].x<=i&&a[j].y>=i)
    dp[i]=min(dp[i],dp[a[j].x-1]+a[j].s);
```

#### 优化做法

1.  将n头牛的结束时间从小到大排序
2.  dp[i]意义同上
3.  状态转移：

```cpp
for(int j=a[i].x-1;j<=a[i].y-1;j++)
    dp[a[i].y]=min(dp[a[i.y]],dp[j]+a[i].s)
```

4.  初始状态：

```cpp
memset(dp,0x3f,sizeof(dp));
dp[1~m-1]=0;
```

5.  线段树优化决策点的枚举

```cpp
dp[a[i].y]=query(1,m,e,a[i]x-1,a[i].y-1)+a[i].s;
update(1,m,e,a[i].y,dp[a[i].y]);
```

## 树状数组优化DP

### UVA12983 The Battle of Chibi

#### 基础做法

状态:dp[i][j]表示以i结尾长度为j的LIS的个数

答案：ans+=dp[i][m];

状态转移：

```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        for(int k=1;k<=i-1;k++)
            if(a[k]<a[i])
                dp[i][j]+=dp[k][j-1];
```

## 倍增优化DP

### **Fence Obstacle Course栅栏行动**

1.  状态:dp[i][0/1]表示从牛棚走到第i号栅栏左/右端点时，最少的横向移动端距离
2.  答案:min(dp[n][0]+|s-a[n].l|,dp[n][1]+|a[n].r-s|);
3.  状态转移

```cpp
for(int j=i-1;j>=1;j--){
    for(a[j].l<=a[i].l&&a[j].r>=a[i].l){
        dp[i][0]=min(dp[j][0]+abs(a[i].l-a[j].l),dp[j][1]+abs(a[i].l-a[j].r));
        break;
    }
}
```