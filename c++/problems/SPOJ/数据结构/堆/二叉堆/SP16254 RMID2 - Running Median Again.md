# RMID2 - Running Median Again

## 题面翻译

### 题目描述

题目将以任意次序给出整数 **（与[SP15376](https://www.luogu.org/problemnew/show/SP15376)不一样，不一定按照不递减次序给出）**，当输入的整数是 $-1$ 时，输出当前序列的中位数**并且删去这个数**（注意不要插入 $-1$！），对于数列里有偶数项数时，输出较小的那个中位数。

### 输入格式

输入的第一行包含一个正整数 $t$ ，表示数据组数。

每一组数据会有若干行，每一行都有一个整数 $n$ 。如果 $n$ 是正数，把它加入数列；如果 $n=-1$ ，那么输出当前数列中的中位数并且删去；如果 $n=0$，表示这组数据结束。

**在每一个数据中，最多会有 $10^5$ 个整数加进数列，最多会有 $10^5$ 次询问。**

### 输出格式

对于每次询问，输出当前数列中的中位数。

## 说明/提示

对于 $100 \%$ 的数据，$n \le 10^9$。

## 题目描述

Danish has just solved the problem "Running Median".

The first line of the problem says "You will be given some integers in non-decreasing order". The problem asks you to report and remove the median of the list every time it is queried.

Having solved this problem, Danish now begins to wonder how to solve the problem if the input is in any order (not necessarily non-decreasing order as mentioned above).

Can you help him?

Your task is to take as input a list of positive integers. Whenever $-1$ is given as input, you must output the median of the list, and remove it from the list. Take the smaller element as the median in case of even number of elements.

## 输入格式

The input contains several test caes.

The first line contains an integer t, the number of test cases.

Each test case has several lines, each containing an integer $n$. If n is positive, add it to the list. $n=-1$ indicates a median query (there will be no median query if the list is empty). The test case is terminated by $n=0$.

In each test case, there will be upto $10^5$ integers to be added to the list, and upto $10^5$ median queries.

## 输出格式

For each median query as described above, print the median on a new line.

## 样例 #1

### 样例输入 #1

```
1
9
10
2
5
1
18
-1
-1
4
3
-1
8
7
-1
0
```

### 样例输出 #1

```
5
9
3
7
```