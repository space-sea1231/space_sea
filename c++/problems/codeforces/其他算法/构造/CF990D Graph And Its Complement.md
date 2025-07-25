# CF990D Graph And Its Complement

## 题目描述

Given three numbers $ n, a, b $ . You need to find an adjacency matrix of such an undirected graph that the number of components in it is equal to $ a $ , and the number of components in its complement is $ b $ . The matrix must be symmetric, and all digits on the main diagonal must be zeroes.

In an undirected graph loops (edges from a vertex to itself) are not allowed. It can be at most one edge between a pair of vertices.

The adjacency matrix of an undirected graph is a square matrix of size $ n $ consisting only of "0" and "1", where $ n $ is the number of vertices of the graph and the $ i $ -th row and the $ i $ -th column correspond to the $ i $ -th vertex of the graph. The cell $ (i,j) $ of the adjacency matrix contains $ 1 $ if and only if the $ i $ -th and $ j $ -th vertices in the graph are connected by an edge.

A connected component is a set of vertices $ X $ such that for every two vertices from this set there exists at least one path in the graph connecting this pair of vertices, but adding any other vertex to $ X $ violates this rule.

The complement or inverse of a graph $ G $ is a graph $ H $ on the same vertices such that two distinct vertices of $ H $ are adjacent if and only if they are not adjacent in $ G $ .

## 输入格式

In a single line, three numbers are given $ n, a, b \,(1 \le n \le 1000, 1 \le a, b \le n) $ : is the number of vertexes of the graph, the required number of connectivity components in it, and the required amount of the connectivity component in it's complement.

## 输出格式

If there is no graph that satisfies these constraints on a single line, print "NO" (without quotes).

Otherwise, on the first line, print "YES"(without quotes). In each of the next $ n $ lines, output $ n $ digits such that $ j $ -th digit of $ i $ -th line must be $ 1 $ if and only if there is an edge between vertices $ i $ and $ j $ in $ G $ (and $ 0 $ otherwise). Note that the matrix must be symmetric, and all digits on the main diagonal must be zeroes.

If there are several matrices that satisfy the conditions — output any of them.

## 输入输出样例 #1

### 输入 #1

```
3 1 2
```

### 输出 #1

```
YES
001
001
110
```

## 输入输出样例 #2

### 输入 #2

```
3 3 3
```

### 输出 #2

```
NO
```