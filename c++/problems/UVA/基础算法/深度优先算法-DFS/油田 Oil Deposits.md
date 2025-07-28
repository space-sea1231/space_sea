# UVA572 油田 Oil Deposits

## 题面翻译

输入多个 $m$ 行 $n$ 列的矩阵，用 `0 0` 表示输入结束。找出有多少块石油区域，用 `@` 代表石油，假如两个 `@` 在横，竖或对角线上相邻，就说它们位于同一区域，对于每个输入，输出一个数表示有几个石油区域。

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=513

[PDF](https://uva.onlinejudge.org/external/5/p572.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/ce90a5dd1ff852d09612a3d726a859f2f238d409.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/e054765bf4e9769be3a53a455e412d62189dbbff.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA572/99ea5e1b8c71aa83bbd6eed7a0e27de87f60a175.png)

## 样例 #1

### 样例输入 #1

```
1 1
*
3 5
*@*@*
**@**
*@*@*
1 8
@@****@*
5 5
****@
*@@*@
*@**@
@@@*@
@@**@
0 0
```

### 样例输出 #1

```
0
1
2
2
```