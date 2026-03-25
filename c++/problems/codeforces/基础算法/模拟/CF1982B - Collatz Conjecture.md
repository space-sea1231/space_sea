# Collatz Conjecture

## 题面翻译

## 题目翻译

最近，一年级学生 Maxim 了解到了 Collatz 猜想，但他在讲座中没有太认真听，因此他只记得该猜想中提到了以下过程：
有一个变量 $x$ 和一个常数 $y$。将以下操作执行 $k$ 次：

- 将 $x$ 增加 $1$，然后
  
- 当 $x$ 可以被 $y$ 整除时，将 $x$ 除以 $y$。
  

注意，这两个操作是在一次操作中按顺序执行的。例如，如果数字 $x=16,y=3$，并且 $k=2$，那么在第一次运算之后，$x$变为 $17$，在第二次运算后，$x$ 变成 $2$，因为在加 $1$ 之后，$x=18$ 可被 $3$ 整除两次。
给定 $x$、$y$ 和 $k$ 的初始值，Maxim 想知道 $x$ 的最终值是多少。

## 题目描述

Recently, the first-year student Maxim learned about the Collatz conjecture, but he didn't pay much attention during the lecture, so he believes that the following process is mentioned in the conjecture:

There is a variable $ x $ and a constant $ y $ . The following operation is performed $ k $ times:

- increase $ x $ by $ 1 $ , then
- while the number $ x $ is divisible by $ y $ , divide it by $ y $ .

 Note that both of these actions are performed sequentially within one operation.For example, if the number $ x = 16 $ , $ y = 3 $ , and $ k = 2 $ , then after one operation $ x $ becomes $ 17 $ , and after another operation $ x $ becomes $ 2 $ , because after adding one, $ x = 18 $ is divisible by $ 3 $ twice.

Given the initial values of $ x $ , $ y $ , and $ k $ , Maxim wants to know what is the final value of $ x $ .

## 输入格式

Each test consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. Then follows the description of the test cases.

The only line of each test case contains three integers $ x $ , $ y $ , and $ k $ ( $ 1 \le x, k \le 10^{9} $ , $ 2 \le y \le 10^{9} $ ) — the initial variable, constant and the number of operations.

## 输出格式

For each test case, output a single integer — the number obtained after applying $ k $ operations.

## 样例 #1

### 样例输入 #1

```
13
1 3 1
2 3 1
24 5 5
16 3 2
2 2 1
1337 18 1
1 2 144133
12345678 3 10
998244353 2 998244353
998244353 123456789 998244352
998244354 998241111 998244352
998244355 2 9982443
1000000000 1000000000 1000000000
```

### 样例输出 #1

```
2
1
1
2
3
1338
1
16936
1
21180097
6486
1
2
```

## 提示

In the first test case, there is only one operation applied to $ x = 1 $ , resulting in $ x $ becoming $ 2 $ .

In the second test case, for $ x = 2 $ , within one operation, one is added to $ x $ and it's divided by $ y = 3 $ , resulting in $ x $ becoming $ 1 $ .

In the third test case, $ x $ changes as follows:

- After the first operation, $ x = 1 $ , because $ 24 + 1 = 25 $ and $ 25 $ is divisible by $ y = 5 $ twice within one operation.
- After the second operation, $ x = 2 $ .
- After the third operation, $ x = 3 $ .
- After the fourth operation, $ x = 4 $ .
- After the fifth operation, $ x = 1 $ .