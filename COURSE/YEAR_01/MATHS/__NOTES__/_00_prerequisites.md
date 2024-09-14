# Pre-course

## Notes

## 1. Exercise

### 1. Problem

Imagine a classroom with some students. With **A** we indicate the set of **pens** that the students have, while with **B** we indicate the set of **students** theirselves. With **f : A -> B** we indicate the law which associates a pen with the student who has it with them.

With the following assertions:

- a. Every student has **at least** a pen
- b. Every student has **only one** pen
- c. Every student **that has** a pen, **has got only one**
- d. There exists a student **without** pens
- e. There exists a student **with more than one** pen

State which defines for the application for **f** the:

1. Injectability
2. Non-injectability
3. Surjectivity
4. Non-surjectivity
5. Bijectivity

### 1. Solution

a -> 3 |
b -> 5 |
c -> 1 |
d -> 4 |
e -> 2

## 2. Exercise

### 2. Problem

Determine the law of the inverse functions of the following:

- *f1*: **R** *->* **R**, *f1*(x) = x + 3
- *f2*: **R** *->* **R**, *f2*(x) = 2x + 3
- *f3*: **R0+** *->* {y € **R** / y >= 1}, *f3*(x) = x^2 + 1
- *f4*: {x € **R** / x >= 1} *->* **R0+**, *f4*(x) = (x - 1)^2

### 2. Solution

- *f1^-1*: **R** *->* **R**, *f1^-1*(y) = y - 3
- *f2^-1*: **R** *->* **R**, *f2^-1*(y) = (y - 3) / 2
- *f3^-1*: {y € **R** / y >= 1} *->* **R0+**, *f3^-1*(y) = *sqrt*(y - 1)
- *f4^-1*: **R0+** *->* {x € **R** / x >= 1}, *f4^-1*(y) = *sqrt*(y) + 1

## 3. Exercise

### 3. Problem

If **x** and **y** are the same number, we can apply the following equality chain:

x = y *<=>* x^2 = xy *<=>* x^2 - y^2 = xy - y^2 *<=>* (x - y)(x + y) = y(x - y) *<=>* x + y = y

Since we know that x = y, the last relationship states that each number is equal to its double. Determine which *<=>* step is wrong.

### 3. Solution

The last step is wrong, because it divides both sides of the equation by *x - y*, which is 0.

## 4. Exercise

### 4. Problem

Prove that the following two prepositions are valid:

- a < b, c < d => a + c < b + d
- 0 < a < b, 0 < c < d => ac < bd

### 4. Solution

(^ = AND, v = OR)

a < b ^ c < d => a + c < b + d

- d - c > 0
- a < b < b + d - c => a < b + d - c => a + c < b + d

0 < a < b, 0 < c < d => ac < bd

- 0 < a < b => 0 < ac < bc
- 0 < a < b => 0 < ad < db
- ac < ad, bc < bd
- b > a <=> bd/c > ad/c > a => bd/c > a => bd > ac

## 5. Exercise
