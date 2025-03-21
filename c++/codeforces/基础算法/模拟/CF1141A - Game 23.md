# Game 23

## 题面翻译

给出两个数 $n,m (1 \le n \le m \le 5 \cdot 10^{8})$

询问能否通过将 $n$ 乘 $2$ 和将 $n$ 乘 $3$ 两种操作使 $n$ 变为 $m$ ，如果可行，输出最小操作次数，如果不可行，输出 $-1$

## 题目描述

Polycarp plays "Game 23". Initially he has a number $ n $ and his goal is to transform it to $ m $ . In one move, he can multiply $ n $ by $ 2 $ or multiply $ n $ by $ 3 $ . He can perform any number of moves.

Print the number of moves needed to transform $ n $ to $ m $ . Print -1 if it is impossible to do so.

It is easy to prove that any way to transform $ n $ to $ m $ contains the same number of moves (i.e. number of moves doesn't depend on the way of transformation).

## 输入格式

The only line of the input contains two integers $ n $ and $ m $ ( $ 1 \le n \le m \le 5\cdot10^8 $ ).

## 输出格式

Print the number of moves to transform $ n $ to $ m $ , or -1 if there is no solution.

## 样例 #1

### 样例输入 #1

```
120 51840
```

### 样例输出 #1

```
7
```

## 样例 #2

### 样例输入 #2

```
42 42
```

### 样例输出 #2

```
0
```

## 样例 #3

### 样例输入 #3

```
48 72
```

### 样例输出 #3

```
-1
```

## 提示

In the first example, the possible sequence of moves is: $ 120 \rightarrow 240 \rightarrow 720 \rightarrow 1440 \rightarrow 4320 \rightarrow 12960 \rightarrow 25920 \rightarrow 51840. $ The are $ 7 $ steps in total.

In the second example, no moves are needed. Thus, the answer is $ 0 $ .

In the third example, it is impossible to transform $ 48 $ to $ 72 $ .