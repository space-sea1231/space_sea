# Boring Day

## 题面翻译

给定一个长度为 $n$ 的序列 $a$，你可以把这个序列划分成任意个不相交的子段，请问每个子段的和在 $l$ 到 $r$ 之间的子段数量的最大值是多少。

### 输入格式。
每个测试由多个测试用例组成。第一行包含一个整数 $t$ ( $1 \le t \le 10^{4}$ ) - 测试用例的数量。随后是测试用例的描述。

每个测试用例的第一行包含三个整数 $n$ 、 $l$ 和 $r$ ( $1 \le n \le 10^{5}$ , $1 \le l \le r \le 10^9$ )。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$ ( $1 \le a_i \le 10^9$ ) --序列中的数字。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^{5}$ 。

## 题目描述

On another boring day, Egor got bored and decided to do something. But since he has no friends, he came up with a game to play.

Egor has a deck of $ n $ cards, the $ i $ -th card from the top has a number $ a_i $ written on it. Egor wants to play a certain number of rounds until the cards run out. In each round, he takes a non-zero number of cards from the top of the deck and finishes the round. If the sum of the numbers on the cards collected during the round is between $ l $ and $ r $ , inclusive, the round is won; otherwise, it is lost.

Egor knows by heart the order of the cards. Help Egor determine the maximum number of rounds he can win in such a game. Note that Egor is not required to win rounds consecutively.

## 输入格式

Each test consists of several test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. This is followed by a description of the test cases.

The first line of each test case contains three integers $ n $ , $ l $ , and $ r $ ( $ 1 \le n \le 10^{5} $ , $ 1 \le l \le r \le 10^9 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the numbers on the cards from top to bottom.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^{5} $ .

## 输出格式

For each test case, output a single number — the maximum number of rounds Egor can win.

## 样例 #1

### 样例输入 #1

```
8
5 3 10
2 1 11 3 7
10 1 5
17 8 12 11 7 11 21 13 10 8
3 4 5
3 4 2
8 12 25
10 7 5 13 8 9 12 7
2 3 3
5 2
9 7 9
2 10 5 1 3 7 6 2 3
1 8 10
9
5 5 6
1 4 2 6 4
```

### 样例输出 #1

```
3
0
1
4
0
3
1
2
```

## 提示

In the first test case, Egor can win $ 3 $ rounds:

- In the first round, take the top $ 2 $ cards with values $ 2 $ and $ 1 $ and win, as their sum is $ 3 $ . After this, the deck will look like this: $ [11, 3, 7] $ .
- In the second round, take the top card and lose, as its value $ 11 $ is greater than $ r = 10 $ . After this, the deck will look like this: $ [3, 7] $ .
- In the third round, take the top card with value $ 3 $ and win. After this, the deck will look like this: $ [7] $ .
- After this, in the fourth round, Egor only has to take the last card in the deck with value $ 7 $ and win again.

In the second test case, Egor cannot win any rounds, no matter how hard he tries.

In the third test case, you can take one card in each round, then the first and third rounds will be losing, and the second round will be winning.

In the fourth test case, you can take two cards in each round and always win.