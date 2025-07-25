# UVA1194 Machine Schedule

## 题面翻译

有两台机器 $A,B$ 分别有 $n,m$ 种模式。

现在有 $k$ 个任务。对于每个任务 $i$ ，给定两个整数 $a_i$ 和 $b_i$ ，表示如果该任务在 $A$ 上执行，需要设置模式为 $a_i$ ；如果该任务在 $B$ 上执行，需要设置模式为 $b_i$ 。

每台机器第一次开机默认处在0模式，且第一次开机不需要消耗时间。任务可以以任意顺序被执行，但每台机器转换一次模式就要重启一次。求怎样分配任务并合理安排顺序，能使机器重启次数最少。

$1 \leq n,m \leq 100$，$1 \leq k \leq 1000$，$0 \leq a_i \lt n$，$0 \leq b_i \lt m$。

可能有多组数据。

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3635

[PDF](https://uva.onlinejudge.org/external/11/p1194.pdf)

## 输入格式

## 输出格式

## 样例 #1

### 样例输入 #1

```
5 5 10
0 1 1
1 1 2
2 1 3
3 1 4
4 2 1
5 2 2
6 2 3
7 2 4
8 3 3
9 4 3
0
```

### 样例输出 #1

```
3
```