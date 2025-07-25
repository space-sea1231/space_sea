# P7981 [JRKSJ R3] system

## 题目描述

定义对序列 $a$ 的一次操作为令 $b_i\gets a_{a_i}$，再令 $a_i\gets b_i$，其中 $i\in[1,n]$。

给你一个长为 $n$ 的序列 $a$，询问对 $a$ 进行 $k$ 次操作后的序列。

## 输入格式

第一行两个整数 $n,k$。

第二行 $n$ 个整数表示序列 $a$。

## 输出格式

一行共 $n$ 个整数，表示 $k$ 次操作后的序列 $a$。

## 输入输出样例 #1

### 输入 #1

```
5 2
2 5 4 3 1
```

### 输出 #1

```
2 5 3 4 1
```

## 输入输出样例 #2

### 输入 #2

```
20 233
1 1 5 6 8 15 10 11 18 14 4 16 16 11 3 5 1 15 4 5
```

### 输出 #2

```
1 1 4 5 6 8 4 15 5 6 3 11 11 15 11 4 1 8 3 4
```

## 说明/提示

### 样例解释

对于第 $1$ 个样例，$a$ 的变化如下：

$$5,1,3,4,2$$
$$2,5,3,4,1$$

### 数据规模与约定

本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^4$ | $\text A$ | $5$ |
| $2$ | $10^2$ | 无 | $15$ |
| $3$ | $10^4$ | $\text B$ | $10$ |
| $4$ | $5\times 10^5$ | $\text B$ | $20$ |
| $5$ | $5\times 10^5$ | $\text C$ | $20$ |
| $6$ | $5\times 10^5$ | 无 | $30$ |

性质 $\text A$：$0\le k\le 10^3$。\
性质 $\text B$：$a_i=i\bmod n+1$。\
性质 $\text C$：$a$ 是一个 $[1,n]$ 的排列。

对于 $100\%$ 的数据，$1\le n\le 5\times 10^5$，$0\le k\le 10^9$，$1\le a_i\le n$。