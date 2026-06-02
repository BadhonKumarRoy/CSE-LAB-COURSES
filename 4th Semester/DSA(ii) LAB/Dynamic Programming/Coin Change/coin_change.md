# Coin Change Problem (Number of Ways) using Dynamic Programming

## Overview

The **Coin Change Problem** is a classic **Dynamic Programming (DP)** problem.

Given a set of coin denominations and a target amount, the goal is to determine the **number of different ways** to make the target amount using the available coins.

Important points:

* Each coin can be used **unlimited times**.
* The order of coins does **not** matter.
* We need to count the total number of possible combinations.

---

## Problem Statement

Given:

| Coin Types |
| ---------- |
| 2          |
| 3          |
| 5          |

Target Amount:

```text
100
```

Find the total number of ways to make the amount 100 using the given coin denominations.

---

# Dynamic Programming Approach

The solution uses a **Bottom-Up Dynamic Programming** method.

A one-dimensional DP array is used where:

```text
dp[i]
```

represents the number of ways to make amount **i**.

---

## DP Formula

For each coin:

```text
dp[j] = dp[j] + dp[j - coin]
```

Where:

* `dp[j]` = existing ways to make amount `j`
* `dp[j - coin]` = ways to make the remaining amount after using the current coin

---

## Initialization

Initially:

```text
dp[0] = 1
```

Reason:

There is exactly one way to make amount 0:

```text
Choose no coins
```

All other entries are initialized to 0.

---

## DP Array Construction

### Initial State

| Amount | 0 | 1 | 2 | 3 | 4 | 5 |
| ------ | - | - | - | - | - | - |
| Ways   | 1 | 0 | 0 | 0 | 0 | 0 |

---

## After Considering Coin = 2

For every amount from 2 to 100:

```text
dp[j] = dp[j] + dp[j-2]
```

First few values become:

| Amount | 0 | 1 | 2 | 3 | 4 | 5 |
| ------ | - | - | - | - | - | - |
| Ways   | 1 | 0 | 1 | 0 | 1 | 0 |

Explanation:

```text
2  -> {2}
4  -> {2+2}
```

---

## After Considering Coin = 3

For every amount from 3 to 100:

```text
dp[j] = dp[j] + dp[j-3]
```

First few values become:

| Amount | 0 | 1 | 2 | 3 | 4 | 5 |
| ------ | - | - | - | - | - | - |
| Ways   | 1 | 0 | 1 | 1 | 1 | 1 |

Examples:

```text
3 -> {3}

5 -> {2+3}
```

---

## After Considering Coin = 5

For every amount from 5 to 100:

```text
dp[j] = dp[j] + dp[j-5]
```

First few values become:

| Amount | 0 | 1 | 2 | 3 | 4 | 5 |
| ------ | - | - | - | - | - | - |
| Ways   | 1 | 0 | 1 | 1 | 1 | 2 |

Examples:

```text
5 -> {5}
     {2+3}
```

Therefore:

```text
dp[5] = 2
```

---

## Why Coin Loop Comes First

The algorithm processes coins one by one:

```cpp
for(int i = 0; i < n; i++)
{
    for(int j = coin; j <= amount; j++)
    {
        dp[j] += dp[j - coin];
    }
}
```

This guarantees that:

```text
2 + 3
```

and

```text
3 + 2
```

are counted as the same combination.

Thus, only unique combinations are counted.

---

## Example for Amount = 10

Possible combinations:

```text
2 + 2 + 2 + 2 + 2

2 + 2 + 3 + 3

2 + 3 + 5

5 + 5
```

Total ways:

```text
4
```

---

## Complete Algorithm

### Step 1

Create a DP array:

```text
dp[0...100]
```

Initialize:

```text
dp[0] = 1
```

### Step 2

Process each coin:

```text
Coin = 2
Coin = 3
Coin = 5
```

### Step 3

Update DP values:

```text
dp[j] += dp[j-coin]
```

### Step 4

Final answer:

```text
dp[100]
```

---

## Final Answer

The program outputs:

```text
184
```

Therefore, the number of different ways to make amount 100 using coins:

```text
{2, 3, 5}
```

is:

```text
184
```

---

# Time Complexity

| Operation      | Complexity    |
| -------------- | ------------- |
| DP Computation | O(n × Amount) |

Where:

* n = Number of coin types
* Amount = Target amount

For this problem:

```text
n = 3
Amount = 100
```

Therefore:

```text
O(3 × 100)
=
O(300)
```

---

# Space Complexity

The DP array contains:

```text
Amount + 1
```

elements.

Therefore:

```text
Space Complexity = O(Amount)
```

For this program:

```text
O(101)
```

---

# Key Takeaways

* Coin Change is a classic Dynamic Programming problem.
* A one-dimensional DP array is sufficient.
* Each coin can be used unlimited times.
* Processing coins first avoids counting duplicate permutations.
* The recurrence relation is:

```text
dp[j] = dp[j] + dp[j - coin]
```

* Time Complexity:

```text
O(n × Amount)
```

* Space Complexity:

```text
O(Amount)
```

* For coins `{2, 3, 5}` and target amount `100`, the total number of combinations is:

```text
184
```
