# SP1716 GSS3 - Can you answer these queries III

## 题目描述

You are given a sequence A of N (N <= 50000) integers between -10000 and 10000. On this sequence you have to apply M (M <= 50000) operations:   
 modify the i-th element in the sequence or for given x y print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 输入格式

The first line of input contains an integer N. The following line contains N integers, representing the sequence A1..AN.   
 The third line contains an integer M. The next M lines contain the operations in following form:  
 0 x y: modify Ax into y (|y|<=10000).  
 1 x y: print max{Ai + Ai+1 + .. + Aj | x<=i<=j<=y }.

## 输出格式

For each query, print an integer as the problem required.

## 输入输出样例 #1

### 输入 #1

```
4
1 2 3 4
4
1 1 3
0 3 -3
1 2 4
1 3 3
```

### 输出 #1

```
6
4
-3
```