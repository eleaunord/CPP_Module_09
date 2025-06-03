# C++ Module 09 — STL

This module is the final part of the C++ piscine at 42, focusing on the **Standard Template Library (STL)** and efficient use of containers. Each exercise challenges you to solve real-world problems using different STL structures, emphasizing performance, design, and C++ best practices.

## What I Learned

* Practical use of STL containers like `map`, `stack`, `deque`, `vector`, etc.
* Designing programs using C++98 standard
* Efficient sorting algorithms (e.g., Ford-Johnson)
* Performance benchmarking
* Robust error handling and input validation
* Managing multiple files and clean project architecture

---

## Exercise 00 – Bitcoin Exchange

**Goal:** Build a program `btc` that reads a historical Bitcoin price database and evaluates values on requested dates.

### Concepts Covered:

* File I/O and parsing `.csv`-like structures
* Use of `map` to associate dates with values
* Custom string processing
* Date comparison and closest-match logic

### Key Features:

* Takes an input file of lines like `YYYY-MM-DD | value`
* Multiplies the value by the Bitcoin price of that date (or nearest past date)
* Handles malformed lines, invalid numbers, missing files

📦 **Container used:** `std::map`

---

## ➕ Exercise 01 – Reverse Polish Notation

**Goal:** Build a calculator that evaluates expressions in Reverse Polish Notation (RPN).

### Concepts Covered:

* Stack-based algorithm for expression parsing
* Handling basic math operations (`+ - * /`)
* Managing operator precedence without parentheses
* Input validation and error handling

### Key Features:

* Expression passed as a single argument: `"3 4 + 2 *"`
* Uses stack logic to compute final result
* Detects malformed input and prints errors

📦 **Container used:** `std::stack`

---

## Exercise 02 – PmergeMe

**Goal:** Implement a sorting algorithm (Ford-Johnson / Merge-Insertion Sort) that handles thousands of integers efficiently.

### Concepts Covered:

* Implementation of a complex hybrid sorting algorithm
* Benchmarking execution time using high-precision clocks
* Comparison of container efficiency
* Advanced command-line argument handling

### Key Features:

* Input: sequence of positive integers as CLI arguments
* Outputs before/after values and time taken by two different containers
* Manages invalid or duplicate entries gracefully

📦 **Containers used:** `std::deque`, `std::vector`

---

## 🛠 How to Compile

Each exercise includes a `Makefile`. Use:

```bash
make
./<executable> [args]
```

Example:

```bash
cd ex00 && make && ./btc input.txt
```

---

## Project Constraints

* Standard: `c++98`
* Must use STL containers
* One container = one exercise (cannot reuse)
* No `printf`, `malloc`, `free`, or C-style hacks
* Use `Makefile` with rules: `all`, `clean`, `fclean`, `re`
* No use of `using namespace` or `friend`

---

## Final Thoughts

This module was a deep dive into STL and algorithmic thinking in C++. Each exercise required a different mindset — from finance simulation to stack-based math to high-performance sorting. It was a great way to consolidate all the skills developed throughout the piscine, and a solid foundation for real-world C++ development.
