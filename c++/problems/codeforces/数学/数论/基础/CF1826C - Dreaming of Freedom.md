# Dreaming of Freedom

## 题面翻译

$n$ 个程序员要在 $m$ 个算法里选出最受欢迎的算法，每轮投票每个程序员都会在剩下的算法中选择一个。

在第一轮投票前，$m$ 种算法都可以选择；每轮投票后，只保留有最多票数的算法；只剩下一种算法时，选拔结束。请判断无论怎样投票选拔都会结束吗？

## 题目描述

Because to take away a man's freedom of choice, even his freedom to make the wrong choice, is to manipulate him as though he were a puppet and not a person.

— Madeleine L'Engle



There are $ n $ programmers choosing their favorite algorithm amongst $ m $ different choice options. Before the first round, all $ m $ options are available. In each round, every programmer makes a vote for one of the remaining algorithms. After the round, only the algorithms with the maximum number of votes remain. The voting process ends when there is only one option left. Determine whether the voting process can continue indefinitely or no matter how people vote, they will eventually choose a single option after some finite amount of rounds?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases.

Each test case consists of a single line containing two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 10^6 $ ) — the number of people and choice options respectively.

## 输出格式

For each test case output "YES" if the programmers will eventually choose a single option, and "NO" otherwise.

You may print each letter in any case (for example, YES, Yes, yes, yEs will all be recognized as a positive answer).

## 样例 #1

### 样例输入 #1

```
5
3 2
4 2
5 3
1000000 1000000
1 1000000
```

### 样例输出 #1

```
YES
NO
YES
NO
YES
```

## 提示

In the first example, there are $ 8 $ ways people could vote: $ \{1|1|1, 1|1|2, 1|2|1, 1|2|2, 2|1|1, 2|1|2, 2|2|1, 2|2|2\} $ .

In cases $ 1 $ , $ 2 $ , $ 3 $ , and $ 5 $ , the programmers are left with the first algorithm, and in the remaining cases people are left with the second one, so the voting ends in one round in any case.

In the second example, the programmers could always vote $ 1|1|2|2 $ . Both algorithms have the maximum number of votes and remain for the next round, so the voting never ends.