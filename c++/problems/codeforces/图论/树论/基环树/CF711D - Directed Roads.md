# CF711D Directed Roads

## 题目描述

ZS the Coder and Chris the Baboon has explored Udayland for quite some time. They realize that it consists of $ n $ towns numbered from $ 1 $ to $ n $ .

There are $ n $ directed roads in the Udayland. $ i $ -th of them goes from town $ i $ to some other town $ a_{i} $ ( $ a_{i}≠i $ ). ZS the Coder can flip the direction of any road in Udayland, i.e. if it goes from town $ A $ to town $ B $ before the flip, it will go from town $ B $ to town $ A $ after.

ZS the Coder considers the roads in the Udayland confusing, if there is a sequence of distinct towns $ A_{1},A_{2},...,A_{k} $ ( $ k&gt;1 $ ) such that for every $ 1<=i&lt;k $ there is a road from town $ A_{i} $ to town $ A_{i+1} $ and another road from town $ A_{k} $ to town $ A_{1} $ . In other words, the roads are confusing if some of them form a directed cycle of some towns.

Now ZS the Coder wonders how many sets of roads (there are $ 2^{n} $ variants) in initial configuration can he choose to flip such that after flipping each road in the set exactly once, the resulting network will not be confusing.

Note that it is allowed that after the flipping there are more than one directed road from some town and possibly some towns with no roads leading out of it, or multiple roads between any pair of cities.

## 输入格式

The first line of the input contains single integer $ n $ ( $ 2<=n<=2·10^{5} $ ) — the number of towns in Udayland.

The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=n,a_{i}≠i) $ , $ a_{i} $ denotes a road going from town $ i $ to town $ a_{i} $ .

## 输出格式

Print a single integer — the number of ways to flip some set of the roads so that the resulting whole set of all roads is not confusing. Since this number may be too large, print the answer modulo $ 10^{9}+7 $ .

## 输入输出样例 #1

### 输入 #1

```
3
2 3 1
```

### 输出 #1

```
6
```

## 输入输出样例 #2

### 输入 #2

```
4
2 1 1 1
```

### 输出 #2

```
8
```

## 输入输出样例 #3

### 输入 #3

```
5
2 4 2 5 3
```

### 输出 #3

```
28
```

## 说明/提示

Consider the first sample case. There are $ 3 $ towns and $ 3 $ roads. The towns are numbered from $ 1 $ to $ 3 $ and the roads are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/bbf0ca4cbc925b1d673ae3b61e28811a0ccacf51.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/43ec097315a08660c95bbf7f709c76c8ce606dd6.png) initially. Number the roads $ 1 $ to $ 3 $ in this order.

The sets of roads that ZS the Coder can flip (to make them not confusing) are $ {1},{2},{3},{1,2},{1,3},{2,3} $ . Note that the empty set is invalid because if no roads are flipped, then towns $ 1,2,3 $ is form a directed cycle, so it is confusing. Similarly, flipping all roads is confusing too. Thus, there are a total of $ 6 $ possible sets ZS the Coder can flip.

The sample image shows all possible ways of orienting the roads from the first sample such that the network is not confusing.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/329f4376794f6e7da8ed8bb533f70d300253c072.png)