# CF1000E We Need More Bosses

## 题目描述

**题目大意：**

给定一个 $n$ 个点 $m$ 条边的无向图，保证图连通。找到两个点$s,t$，使得$s$到$t$**必须**经过的边最多（一条边无论走哪条路线都经过ta，这条边就是必须经过的边），$2<=n<=3*10^5,1<=m<=3*10^5$

## 输入格式

第一行两个整数，$n,m$

以下m行，每行两个整数$x,y$，表示$xy$间有一条无向边相连

## 输出格式

一个整数，即最多的必须经过边数

感谢@守望 提供翻译

## 输入输出样例 #1

### 输入 #1

```
5 5
1 2
2 3
3 1
4 1
5 2
```

### 输出 #1

```
2
```

## 输入输出样例 #2

### 输入 #2

```
4 3
1 2
4 3
3 2
```

### 输出 #2

```
3
```