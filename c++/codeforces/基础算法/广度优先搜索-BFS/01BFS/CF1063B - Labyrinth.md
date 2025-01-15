# Labyrinth

## 题面翻译

## 题意描述
你正在玩一款电脑游戏。在其中一关，你位于一个 $n$ 行 $m$ 列的迷宫。每个格子要么是可以通过的空地，要么是障碍。迷宫的起点位于第 $r$ 行第 $c$ 列。你每一步可以向上、下、左、右中的一个方向移动一格，前提是那一格不是障碍。你无法越出迷宫的边界。

不幸的是，你的键盘快坏了，所以你只能向左移动不超过 $x$ 格，并且向右移动不超过 $y$ 格。因为上下键情况良好，所以对向上和向下的移动次数没有限制。

现在你想知道在满足上述条件的情况下，从起点出发，有多少格子可以到达（包括起点）？
## 输入输出格式
### 输入格式：
第一行包含两个数 $n, m$ $(1 <= n, m, <= 2000)$ ,表示迷宫的行数和列数。

第二行包含两个数 $r,c$ $(1 <= r <= n, 1 <= c <= m)$ ,表示起点位于第 $r$ 行第 $c$ 列。

第三行包含两个数 $x,y$ $(1 <= x,y <= 10^9)$ ,表示最多向左或向右移动的次数。

接下来 $n$ 行描述这个迷宫，每行为一个长为 $m$ 的由 '.' 和 '\*' 组成的字符串。
'.' 表示空地， '\*' 表示障碍。
输入保证起点不是障碍。
### 输出格式：
输出一个整数，表示从起点出发可以到达的格子数，包括起点本身。

## 题目描述

You are playing some computer game. One of its levels puts you in a maze consisting of $ n $ lines, each of which contains $ m $ cells. Each cell either is free or is occupied by an obstacle. The starting cell is in the row $ r $ and column $ c $ . In one step you can move one square up, left, down or right, if the target cell is not occupied by an obstacle. You can't move beyond the boundaries of the labyrinth.

Unfortunately, your keyboard is about to break, so you can move left no more than $ x $ times and move right no more than $ y $ times. There are no restrictions on the number of moves up and down since the keys used to move up and down are in perfect condition.

Now you would like to determine for each cell whether there exists a sequence of moves that will put you from the starting cell to this particular one. How many cells of the board have this property?

## 输入格式

The first line contains two integers $ n $ , $ m $ ( $ 1<=n,m<=2000 $ ) — the number of rows and the number columns in the labyrinth respectively.

The second line contains two integers $ r $ , $ c $ ( $ 1<=r<=n $ , $ 1<=c<=m $ ) — index of the row and index of the column that define the starting cell.

The third line contains two integers $ x $ , $ y $ ( $ 0<=x,y<=10^{9} $ ) — the maximum allowed number of movements to the left and to the right respectively.

The next $ n $ lines describe the labyrinth. Each of them has length of $ m $ and consists only of symbols '.' and '\*'. The $ j $ -th character of the $ i $ -th line corresponds to the cell of labyrinth at row $ i $ and column $ j $ . Symbol '.' denotes the free cell, while symbol '\*' denotes the cell with an obstacle.

It is guaranteed, that the starting cell contains no obstacles.

## 输出格式

Print exactly one integer — the number of cells in the labyrinth, which are reachable from starting cell, including the starting cell itself.

## 样例 #1

### 样例输入 #1

```
4 5
3 2
1 2
.....
.***.
...**
*....
```

### 样例输出 #1

```
10
```

## 样例 #2

### 样例输入 #2

```
4 4
2 2
0 1
....
..*.
....
....
```

### 样例输出 #2

```
7
```

## 提示

Cells, reachable in the corresponding example, are marked with '+'.

First example:

```
+++..
+***.
+++**
*+++.
```
 
 Second example:

```
.++.
.+*.
.++.
.++.
```