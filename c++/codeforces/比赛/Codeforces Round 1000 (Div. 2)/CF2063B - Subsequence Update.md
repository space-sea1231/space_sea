B. Subsequence Update

time limit per test: 1.5 seconds

memory limit per test: 256 megabytes

input: standard input

output: standard output

After Little John borrowed expansion screws from auntie a few hundred times, eventually she decided to come and take back the unused ones.

But as they are a crucial part of home design, Little John decides to hide some in the most unreachable places — under the eco-friendly wood veneers.

You are given an integer sequence $a_1, a_2, \ldots, a_n$, and a segment $[l,r]$ ($1 \le l \le r \le n$).

You must perform the following operation on the sequence **exactly once**.

-   Choose any **subsequence**$^{\text{∗}}$ of the sequence $a$, and reverse it. Note that the subsequence does not have to be contiguous.

Formally, choose any number of indices $i_1,i_2,\ldots,i_k$ such that $1 \le i_1 < i_2 < \ldots < i_k \le n$. Then, change the $i_x$\-th element to the original value of the $i_{k-x+1}$\-th element simultaneously for all $1 \le x \le k$.

Find the **minimum value** of $a_l+a_{l+1}+\ldots+a_{r-1}+a_r$ after performing the operation.

$^{\text{∗}}$A sequence $b$ is a subsequence of a sequence $a$ if $b$ can be obtained from $a$ by the deletion of several (possibly, zero or all) element from arbitrary positions.

**Input**

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.

The first line of each test case contains three integers $n$, $l$, $r$ ($1 \le l \le r \le n \le 10^5$) — the length of $a$, and the segment $[l,r]$.

The second line of each test case contains $n$ integers $a_1,a_2,\ldots,a_n$ ($1 \le a_{i} \le 10^9$).

It is guaranteed that the sum of $n$ over all test cases does not exceed $10^5$.

**Output**

For each test case, output the minimum value of $a_l+a_{l+1}+\ldots+a_{r-1}+a_r$ on a separate line.

**Note**

On the second test case, the array is $a=[1,2,3]$ and the segment is $[2,3]$.

After choosing the subsequence $a_1,a_3$ and reversing it, the sequence becomes $[3,2,1]$. Then, the sum $a_2+a_3$ becomes $3$. It can be shown that the minimum possible value of the sum is $3$.