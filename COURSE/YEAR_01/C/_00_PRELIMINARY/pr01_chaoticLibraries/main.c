/**
 * @desc
 * Write a C program that manages a digital library of books. The program should allow 
 * the user to add, remove, update, search, and categorize books. Each book should 
 * have a title, author, ISBN, publication year, genre, and a short description. 
 * Additionally, the program should support advanced text search within the descriptions 
 * of the books using regular expressions.
 * 
 * @note
 * Use the `struct` keyword to define a `Book` structure that stores all the necessary 
 * details about each book.
 * 
 * @note
 * Use the `<regex.h>` library to implement advanced search functionality within book 
 * descriptions. The user should be able to search for books using complex patterns 
 * (e.g., finding books with certain words in the description that start with a specific 
 * letter or contain a specific word).
 * 
 * @note
 * Implement functionality to categorize books by genre, allowing the user to view 
 * all books in a specific category. Use dynamic memory allocation to store and 
 * manage these categories, which should be scalable depending on the number of genres.
 * 
 * @note
 * Incorporate file management to save the entire library to a file and load it on 
 * program startup. Use efficient file handling techniques to deal with large numbers 
 * of books (e.g., storing and loading using binary files, using indexing for faster 
 * search, etc.).
 * 
 * @note
 * Ensure that memory management is handled carefully, with attention to avoiding 
 * memory leaks or segmentation faults, especially when dealing with dynamic memory 
 * and complex data structures.
 * 
 * @note
 * Implement input validation and error handling for various cases, including incorrect 
 * ISBN formats, duplicate entries, invalid search patterns, and file I/O errors.
 */
