# 0/1 Knapsack Problem using Dynamic Programming

## Overview

The **0/1 Knapsack Problem** is one of the most important problems in **Dynamic Programming (DP)**.

Given a set of items, each having:

* A **weight**
* A **profit/value**

and a knapsack with a fixed **capacity**, the goal is to maximize the total profit without exceeding the capacity.

In the **0/1 Knapsack**, each item can either be:

* Included (**1**)
* Excluded (**0**)

You cannot take fractional parts of an item.

---

## Problem Statement

Given:

| Item | Weight | Profit |
| ---- | ------ | ------ |
| 1    | 2      | 1      |
| 2    | 3      | 2      |
| 3    | 4      | 5      |
| 4    | 5      | 6      |

Knapsack Capacity = **8**

Find the maximum profit that can be obtained.

---

# Dynamic Programming Approaches

Abdul Bari explains two DP approaches:

1. Bottom-Up (Tabular Method)
2. Top-Down (Memoization Method)

Video Lecture:

🔗 https://youtu.be/nLmhmB6NzcM?si=D1KScrORxzH-K8XK

---

# 1. Bottom-Up (Tabular Method)

## DP Formula

For each item and capacity:

```text
V[i][w] = max(
    V[i-1][w],                    // Exclude item
    V[i-1][w-weight[i]] + profit[i] // Include item
)
```

### Cases

#### If item cannot fit:

```text
weight[i] > w
```

Then:

```text
V[i][w] = V[i-1][w]
```

#### If item can fit:

```text
V[i][w] =
max(
    V[i-1][w],
    V[i-1][w-weight[i]] + profit[i]
)
```

---

## DP Table Construction

### Initial Table

Row = Items

Column = Capacity (0 to 8)

| Item/Capacity | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| ------------- | - | - | - | - | - | - | - | - | - |
| 0 Items       | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

---

## After Considering Item 1

Weight = 2

Profit = 1

| Item/Capacity | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| ------------- | - | - | - | - | - | - | - | - | - |
| Item 1        | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |

---

## After Considering Item 2

Weight = 3

Profit = 2

| Item/Capacity | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| ------------- | - | - | - | - | - | - | - | - | - |
| Item 2        | 0 | 0 | 1 | 2 | 2 | 3 | 3 | 3 | 3 |

---

## After Considering Item 3

Weight = 4

Profit = 5

| Item/Capacity | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| ------------- | - | - | - | - | - | - | - | - | - |
| Item 3        | 0 | 0 | 1 | 2 | 5 | 5 | 6 | 7 | 7 |

---

## After Considering Item 4

Weight = 5

Profit = 6

| Item/Capacity | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| ------------- | - | - | - | - | - | - | - | - | - |
| Item 4        | 0 | 0 | 1 | 2 | 5 | 6 | 6 | 7 | 8 |

---

## Complete DP Table

| Items \ Capacity | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| ---------------- | - | - | - | - | - | - | - | - | - |
| 0 Items          | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Item 1           | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| Item 2           | 0 | 0 | 1 | 2 | 2 | 3 | 3 | 3 | 3 |
| Item 3           | 0 | 0 | 1 | 2 | 5 | 5 | 6 | 7 | 7 |
| Item 4           | 0 | 0 | 1 | 2 | 5 | 6 | 6 | 7 | 8 |

---

## Final Answer

The maximum profit is:

```text
V[4][8] = 8
```

### Selected Items

| Item | Weight | Profit |
| ---- | ------ | ------ |
| 2    | 3      | 2      |
| 4    | 5      | 6      |

Total Weight:

```text
3 + 5 = 8
```

Total Profit:

```text
2 + 6 = 8
```

---

# 2. Memoization (Top-Down) Method

Instead of filling the table iteratively, we solve the problem recursively.

For each item:

```text
knapsack(i, w)
```

We have two choices:

### Exclude Current Item

```text
knapsack(i-1, w)
```

### Include Current Item

```text
knapsack(i-1, w-weight[i]) + profit[i]
```

Then:

```text
knapsack(i, w) =
max(
    knapsack(i-1, w),
    knapsack(i-1, w-weight[i]) + profit[i]
)
```

The computed states are stored in a memoization table so they are not recalculated.

---

# Time Complexity

| Approach    | Time Complexity | Space Complexity |
| ----------- | --------------- | ---------------- |
| Recursion   | O(2^n)          | O(n)             |
| Memoization | O(n × W)        | O(n × W)         |
| Tabulation  | O(n × W)        | O(n × W)         |

Where:

* n = Number of items
* W = Knapsack Capacity

---

# Key Takeaways

* 0/1 Knapsack is a classic Dynamic Programming problem.
* Each item can be selected at most once.
* DP eliminates repeated computations.
* Both Memoization and Tabulation achieve:

```text
O(n × W)
```

time complexity.

* Tabulation is generally preferred in competitive programming and interviews because it is iterative and easy to implement.

---

# Reference

**Abdul Bari – Knapsack Problem using Dynamic Programming**

Video:

https://youtu.be/nLmhmB6NzcM?si=D1KScrORxzH-K8XK
