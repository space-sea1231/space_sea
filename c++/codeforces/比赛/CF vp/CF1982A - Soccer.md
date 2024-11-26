# Soccer

## 题面翻译

## 题目描述

迪玛喜欢看足球赛。足球赛中是通过记分牌来记录双方的分数，记分牌上的分数表示为$x:y$，其中$x$是第一队的进球数，$y$是第二队的进球数。

有一天，迪玛在观看一场足球比赛时，中途被一件非常重要的事情打扰，必须去做一下这个事，这个事情做完之后，他又继续回来观看比赛。

迪玛可以记得做这个重要事情之前比赛的分数以及做完事情回来后比赛的分数，他想知道在他做这个重要事情的过程中，两支球队的比分是否有可能从来都不是相等的。

可以保证的是，在这两个时间点的得分中没有出现得分相等的情况，不过有可能在他缺席期间分数并没有改变。

## 输入

* 每个测试由几个测试用例组成。
* 第一行包含一个整数$t(1≤t≤10^4)$--测试用例的数量。然后是测试用例的描述。
* 每个测试用例的第一行包含两个整数$x_1,y_1(0≤x_1,y_1≤10^9,x_1≠y_1)$-迪玛被重要事情打断之前的比赛分数。
* 每个测试用例的第二行包含两个整数$x_2，y_2(x_1≤x_2≤10^9,，y_1≤y_2≤10^9,，x_2≠y_2)$迪玛被重要事情打断之后的比赛分数。

## 输出

对于每个测试用例，如果在他缺席的过程中有可能不出现比分相等的情况，输出“YES”，否则输出“NO”

## 题目描述

Dima loves watching soccer. In such a game, the score on the scoreboard is represented as $ x $ : $ y $ , where $ x $ is the number of goals of the first team, and $ y $ is the number of goals of the second team. At any given time, only one team can score a goal, so the score $ x $ : $ y $ can change to either $ (x + 1) $ : $ y $ , or $ x $ : $ (y + 1) $ .

While watching a soccer game, Dima was distracted by very important matters, and after some time, he returned to watching the game. Dima remembers the score right before he was distracted, and the score right after he returned. Given these two scores, he wonders the following question. Is it possible that, while Dima was not watching the game, the teams never had an equal score?

It is guaranteed that at neither of the two time points Dima remembers the teams had equal scores. However, it is possible that the score did not change during his absence.

Help Dima and answer the question!

## 输入格式

Each test consists of several test cases. The first line contains an integer $ t $ ( $ 1 \le t \le 10^{4} $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains two integers $ x_{1}, y_{1} $ ( $ 0 \le x_{1}, y_{1} \le 10^{9} $ , $ x_{1} \neq y_{1} $ ) — the score before Dima was distracted.

The second line of each test case contains two integers $ x_{2}, y_{2} $ ( $ x_{1} \le x_{2} \le 10^{9} $ , $ y_{1} \le y_{2} \le 10^{9} $ , $ x_{2} \neq y_{2} $ ) — the score when Dima returned.

## 输出格式

For each test case, output "YES" without quotes if it is possible, that the teams never had a tie while Dima was away, otherwise output "NO" without quotes.

You can output each letter in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 样例 #1

### 样例输入 #1

```
6
1 0
5 0
1 2
3 2
1 2
4 5
1 2
4 3
1 2
1 2
998244353 0
1000000000 999999999
```

### 样例输出 #1

```
YES
NO
YES
NO
YES
YES
```

## 提示

In the first test case, the score before Dima left was $ 1 $ : $ 0 $ . When he leaves, the first team scores several goals in a row until the score becomes $ 5 $ : $ 0 $ , so the answer is YES.

In the second test case, the score could only change as follows:

- $ 1 $ : $ 2 $
- $ 2 $ : $ 2 $
- $ 3 $ : $ 2 $

In this scenario, there is a moment when the teams have an equal score, so the answer is NO.

In the third test case, one of the possible developments is:

- $ 1 $ : $ 2 $
- $ 1 $ : $ 3 $
- $ 2 $ : $ 3 $
- $ 2 $ : $ 4 $
- $ 2 $ : $ 5 $
- $ 3 $ : $ 5 $
- $ 4 $ : $ 5 $

In this scenario, there was no time when the score was equal, so the answer is YES.