# P3542 [POI 2012] PEN-Salaries

## 题目描述

**译自 POI 2012 Stage 3. Day 1「[Salaries](https://szkopul.edu.pl/problemset/problem/_qn633f6DVAHRkv0OX3LQaph/site/?key=statement)」**

有一个 $n$ 个点的有根树，每个点的权值分别为 $1 \ldots n$，且大于其儿子的权值。其中一部分点的权值是公开的，且每个权值已知的点的父亲权值也一定已知。求能够根据已知信息推算出来的权值未知的点的权值。

## 输入格式

第一行一个整数 $n$，表示点的个数。

接下来 $n$ 行每行两个整数 $p_i, z_i (1 \le p_i \le n,0 \le z_i \le n)$，其中 $p_i$ 表示结点 $i$ 的父亲，$z_i$ 表示结点 $i$ 的权值。如果 $z_i = 0$，则该点权值未知，否则该点权值为 $z_i$。

## 输出格式

输出 $n$ 行，每行一个整数，表示 $i$ 点的权值。如果该点权值已知或可以推算出来，输出该点权值，否则输出 $0$。

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/bjf4memv.png)

## 输入输出样例 #1

### 输入 #1

```
10
2 2
2 10
1 0
2 9
2 5
4 0
6 0
6 0
5 0
5 0
```

### 输出 #1

```
2
10
1
9
5
8
0
0
0
0
```

## 说明/提示

对于 $54\%$ 的数据有 $n \le 10^4$.

对于所有数据有 $1 \le n \le 10^6$。

翻译来自于 [LibreOJ](https://loj.ac/p/2700)。