# Pre-course

## Notes

## Exercise [1]

### Problem [1]

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

### Solution [1]

a -> 3 |
b -> 5 |
c -> 1 |
d -> 4 |
e -> 2

## Exercise [2]

### Problem [2]

Determine the law of the inverse functions of the following:

- *f1*: **R** *->* **R**, *f1*(x) = x + 3
- *f2*: **R** *->* **R**, *f2*(x) = 2x + 3
- *f3*: **R0+** *->* {y € **R** / y >= 1}, *f3*(x) = x^2 + 1
- *f4*: {x € **R** / x >= 1} *->* **R0+**, *f4*(x) = (x - 1)^2

### Solution [2]

- *f1^-1*(y): **R** *->* **R**, *f1^-1*(y) = y - 3
- *f2^-1*(y): **R** *->* **R**, *f2^-1*(y) = (y - 3) / 2
- *f3^-1*(y): {y € **R** / y >= 1} *->* **R0+**, *f3^-1*(y) = *sqrt*(y - 1)
- *f4^-1*(y): **R0+** *->* {x € **R** / x >= 1}, *f4^-1*(y) = *sqrt*(y) + 1

## Exercise [3]

### Problem [3]

If **x** and **y** are the same number, we can apply the following equality chain:

x = y *<=>* x^2 = xy *<=>* x^2 - y^2 = xy - y^2 *<=>* (x - y)(x + y) = y(x - y) *<=>* x + y = y

Since we know that x = y, the last relationship states that each number is equal to its double. Determine which *<=>* step is wrong.

### Solution [3]

The last step is wrong, because it divides both sides of the equation by *x - y*, which is 0.
