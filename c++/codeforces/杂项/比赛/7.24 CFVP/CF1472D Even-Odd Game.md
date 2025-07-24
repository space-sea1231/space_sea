# CF1472D Even-Odd Game

## 题目描述

During their New Year holidays, Alice and Bob play the following game using an array $ a $ of $ n $ integers:

- Players take turns, Alice moves first.
- Each turn a player chooses any element and removes it from the array.
- If Alice chooses even value, then she adds it to her score. If the chosen value is odd, Alice's score does not change.
- Similarly, if Bob chooses odd value, then he adds it to his score. If the chosen value is even, then Bob's score does not change.

If there are no numbers left in the array, then the game ends. The player with the highest score wins. If the scores of the players are equal, then a draw is declared.

For example, if $ n = 4 $ and $ a = [5, 2, 7, 3] $ , then the game could go as follows (there are other options):

- On the first move, Alice chooses $ 2 $ and get two points. Her score is now $ 2 $ . The array $ a $ is now $ [5, 7, 3] $ .
- On the second move, Bob chooses $ 5 $ and get five points. His score is now $ 5 $ . The array $ a $ is now $ [7, 3] $ .
- On the third move, Alice chooses $ 7 $ and get no points. Her score is now $ 2 $ . The array $ a $ is now $ [3] $ .
- On the last move, Bob chooses $ 3 $ and get three points. His score is now $ 8 $ . The array $ a $ is empty now.
- Since Bob has more points at the end of the game, he is the winner.

You want to find out who will win if both players play optimally. Note that there may be duplicate numbers in the array.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of elements in the array $ a $ .

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the array $ a $ used to play the game.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output on a separate line:

- "Alice" if Alice wins with the optimal play;
- "Bob" if Bob wins with the optimal play;
- "Tie", if a tie is declared during the optimal play.

## 输入输出样例 #1

### 输入 #1

```
4
4
5 2 7 3
3
3 2 1
4
2 2 2 2
2
7 8
```

### 输出 #1

```
Bob
Tie
Alice
Alice
```