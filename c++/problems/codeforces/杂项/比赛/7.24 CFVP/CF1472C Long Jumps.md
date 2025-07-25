# CF1472C Long Jumps

## 题目描述

Polycarp found under the Christmas tree an array $ a $ of $ n $ elements and instructions for playing with it:

- At first, choose index $ i $ ( $ 1 \leq i \leq n $ ) — starting position in the array. Put the chip at the index $ i $ (on the value $ a_i $ ).
- While $ i \leq n $ , add $ a_i $ to your score and move the chip $ a_i $ positions to the right (i.e. replace $ i $ with $ i + a_i $ ).
- If $ i > n $ , then Polycarp ends the game.

For example, if $ n = 5 $ and $ a = [7, 3, 1, 2, 3] $ , then the following game options are possible:

- Polycarp chooses $ i = 1 $ . Game process: $ i = 1 \overset{+7}{\longrightarrow} 8 $ . The score of the game is: $ a_1 = 7 $ .
- Polycarp chooses $ i = 2 $ . Game process: $ i = 2 \overset{+3}{\longrightarrow} 5 \overset{+3}{\longrightarrow} 8 $ . The score of the game is: $ a_2 + a_5 = 6 $ .
- Polycarp chooses $ i = 3 $ . Game process: $ i = 3 \overset{+1}{\longrightarrow} 4 \overset{+2}{\longrightarrow} 6 $ . The score of the game is: $ a_3 + a_4 = 3 $ .
- Polycarp chooses $ i = 4 $ . Game process: $ i = 4 \overset{+2}{\longrightarrow} 6 $ . The score of the game is: $ a_4 = 2 $ .
- Polycarp chooses $ i = 5 $ . Game process: $ i = 5 \overset{+3}{\longrightarrow} 8 $ . The score of the game is: $ a_5 = 3 $ .

Help Polycarp to find out the maximum score he can get if he chooses the starting index in an optimal way.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

The first line of each test case contains one integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the array $ a $ .

The next line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — elements of the array $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output on a separate line one number — the maximum score that Polycarp can get by playing the game on the corresponding array according to the instruction from the statement. Note that Polycarp chooses any starting position from $ 1 $ to $ n $ in such a way as to maximize his result.

## 输入输出样例 #1

### 输入 #1

```
4
5
7 3 1 2 3
3
2 1 4
6
2 1000 2 3 995 1
5
1 1 1 1 1
```

### 输出 #1

```
7
6
1000
5
```

## 说明/提示

The first test case is explained in the statement.

In the second test case, the maximum score can be achieved by choosing $ i = 1 $ .

In the third test case, the maximum score can be achieved by choosing $ i = 2 $ .

In the fourth test case, the maximum score can be achieved by choosing $ i = 1 $ .