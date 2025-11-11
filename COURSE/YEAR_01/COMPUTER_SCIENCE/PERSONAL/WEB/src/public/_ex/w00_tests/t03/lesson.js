/// Variables, temporary memory locations that store data useful to a task
variable = "value"



/// Data types (scalar)

// Numbers, for mathematical operations
1, -2, 1.5

// Strings, for working with text
"Hi", "Hydro"



/// Data types (compound)

// Arrays, to store multiple data (usually of the same type) in a single variable
[ "String1", "String2", "String3" ]

// Objects, to store multiple data of different type in a single variable
{ text: "String", textLength: 6 }



/// Programming logic

// Find the maximum value in a given list

[
  17, 6, 3, 7, 10, 45, 30, 23, 46, 17, 8, 9
]



// Find the median of an unordered list

/*
  1. Order the list
  2. Calculate the median
    2.1 count <- 0, median <- 0
    2.2 For every element of the array
      2.3 count <- count + 1
    2.4 If count is even
      2.5 median <- (array[count / 2] + array[count / 2 + 1]) / 2
    2.6 Else
      2.7 median <- array[count / 2]
    2.8 Return median
*/ 




[
  1, 2, 3, 4, 5
]

[
  1, 2, 3, 4, 5, 6, 7, 8
]


// Task: clean your room (from niggers as well)

// 1. Get the niggers out
// 2. Pass the vacuum cleaner in the room
// 3. Wipe the floors
// 4. Clean bookshelf


/// Task: make a pizza <<<

// Subtask 1: Make the dough
  // Step 1: Get the ingredients (...)
  // Step 2: ...
// Subtask 2: Let it rise
// Subtask 3: Press it down until it's a circle
// Subtask 4: Put the toppings
    // Step 1: Spread the tomato sauce
    // Step 2: Put mozzarella on the base
    // Step 3: Put pepperoni on pizza
    // Step 4: Put basil
    // Step 5: Put extravirgin olive oil
// Subtask 5: Cook it
    // Step 1: Let the oven pre-heat to 220°C
    // Step 2: Put the pizza in the oven
    // Step 3: Wait 10-15mins
// Subtask 6: Serve & eat





let count = 0;
let numInput = 0; // <-- NUMERO INPUT
console.groupCollapsed("COMBINAZIONI CIRCUITO");

for (let j = 0; j < 1 << numInput; ++j) {
  let i = []
    // , a = i[0]
    // , b = i[1]
    // etc.
  ;

  for (let k = numInput; k >= 0; --k)
    i[numInput - k] = (j & (1 << k)) >> k;

  let expr = true; // <-- ESPRESSIONE DEL CIRCUITO LOGICO
  count += expr;

  console.log(i, expr);
}

console.groupEnd();
console.log(`SOLZ./TOT. -> ${count}/${1 << numInput}`);





















// MODIFICA: NUMERO DI INPUT, DICHIARATORI ED ESPRESSIONE

// NUMERO DI INPUT
let numInput = 0;

let count = 0;
console.groupCollapsed("COMBINAZIONI CIRCUITO");

for (let j = 0; j < 1 << numInput; ++j) {
  let i = [];

  for (let k = numInput - 1; k >= 0; --k)
    i[numInput - k - 1] = (j & (1 << k)) >> k;

  // DICHIARATORI (modifica come necessario)
  let a = i[0]
    , b = i[1]
    , c = i[2]
    , d = i[3]
    , e = i[4]
    , f = i[5]
    , g = i[6]
    , h = i[7]
  ;

  // ESPRESSIONE
  let expr = true;
  count += expr;

  expr
    ? console.warn(i, expr)
    : console.log(i, expr)
  ;
}

console.groupEnd();
console.log(`SOLZ./TOT. -> ${count}/${1 << numInput}`);

if (numInput === 0)
  console.error(atob('RGV2aSBtb2RpZmljYXJlIGlsIG51bWVybyBkaSBpbnB1dCBtYXJlbW1hIHp1Y2NoaW5hLg=='));
else if (count === 1 << numInput || count === 0)
  console.error(atob('TWFpYWwgZGVsIGJvc2NvIGZyZWdvIGNoZSBlc3ByZXNzaW9uZSBkZWwgcGlmZmVybw=='));



// Selection sort pseudocode

/*
 * Example:
 * INPUT           OUTPUT
 * [1, 4, 3, 2] -> [1, 2, 3, 4]
 *
 * minpos = Minimum's position
 * c1 = Current position of outer loop
 * c2 = Current position of inner loop
 * 
 * 1. Iterate through the whole list
 *  2. minpos = c1
 *  3. Find the new minimum's position in the array
 *    3.1. Iterate through the whole list starting from the current position c1 ("c2")
 *      3.2. If the element at the c2 position < element at minpos position
 *        3.3. minpos <- c2 position
 *  4. If minpos != c1 (doesn't equal)
 *    5. Swap the elements at minpos and c1 positions
*/






/*
  Program to calculate the median

  INPUT              OUTPUT
  [Unsorted list] -> Number



  Subtask 1: Sort the list
  <[Unsorted list]> -> [Sorted list]

  Subtask 2: Calculate the median
  [Sorted list] -> <Number>

  Subtask 3: Use median to retrieve a value given a formula
  <Number> -> <Number>



  INPUT                                       OUTPUT
  <Unsorted list> -> Sorted list -> Number -> <Number>
*/



/**
 * Program that given a number x, it creates a list of values from 1 to x
 * 
 * INPUT       OUTPUT
 * Number x -> Sorted list of values 1 to x
 */

/**
 * Program that counts the number of niggers in a room.
 * 
 * INPUT             OUTPUT
 * 
 */




/**
 * Given a value, find the matching record inside a table with 1 billion elements
 * 
 * > If the list isn't sorted, we can't assume where the element is.
 * > In the worst case, we would have to read all the billion elements.
 * 
 * > But what if the list *is* sorted?
 */
