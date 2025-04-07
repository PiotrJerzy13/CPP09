# C++ Projects: Bitcoin Exchange, Reverse Polish Notation, and Ford-Johnson Sorting

This repository contains three advanced C++ projects that demonstrate the use of modern C++ features, data processing, and algorithmic techniques. Each project is based on real-world applications and complex algorithmic challenges.

## Projects Overview

1. **Bitcoin Exchange**: Utilizes historical Bitcoin exchange rate data to compute the value of transactions on specific dates.
2. **Reverse Polish Notation (RPN) Calculator**: Parses and evaluates expressions written in RPN, a postfix notation that eliminates the need for parentheses.
3. **Ford-Johnson Sorting Algorithm**: Implements an advanced sorting technique to efficiently sort large datasets.

## Bitcoin Exchange

### Functionality

- Loads a CSV file containing historical exchange rates of Bitcoin.
- Processes a user-provided file with transaction requests specifying date and Bitcoin amounts.
- Outputs the value of each transaction based on historical rates.

### Technologies

- C++17 for modern language features.
- STL containers and algorithms for efficient data handling.

### Key Concepts

- Date validation.
- CSV parsing.
- Use of `std::map` to maintain sorted date-rate pairs.

## Reverse Polish Notation (RPN)

### What is RPN?

Reverse Polish Notation is a mathematical notation in which operators follow their operands. It does not require parentheses as long as each operator has a fixed number of operands.

### Functionality

- Parses command-line input representing an RPN expression.
- Supports basic arithmetic operations: addition, subtraction, multiplication, and division.
- Evaluates the expression and outputs the result.

### Technologies

- C++17
- Use of `std::stack` for handling the order of operations.

## Ford-Johnson Sorting Algorithm

### What is the Ford-Johnson Algorithm?

The Ford-Johnson algorithm, also known as Merge Insertion, is noted for its efficiency in sorting small sets of data. It combines merge sort and insertion sort principles to minimize comparisons and improve sorting speed.

### Functionality

- Accepts a sequence of numbers.
- Uses two different STL containers to demonstrate the algorithm's efficiency.
- Measures and compares the performance of sorting with different containers.

### Technologies

- C++17
- Advanced use of STL containers like `std::vector` and `std::list`.

## Building and Running

Each project includes a Makefile for easy compilation. Use the following commands in each project directory:

```bash
make        # Compiles the project
./program   # Runs the program (replace `program` with the actual executable name)
```

## Dependencies

- A C++17 compatible compiler (GCC or Clang recommended).
- Standard C++ libraries.

## Usage

Here’s a detailed guide on how to use the Reverse Polish Notation (RPN) Calculator and the Ford-Johnson Sorting application included in your repository. These usage instructions can be integrated into your README file under each respective project section.

## Usage Instructions

### Reverse Polish Notation (RPN) Calculator

#### Overview
The RPN Calculator takes a string representing an RPN expression and computes its value. The expression should contain integers and operators (`+`, `-`, `*`, `/`) separated by spaces. It evaluates these expressions using a stack-based algorithm.

#### Running the RPN Calculator
1. **Compile the Program**:
   Navigate to the RPN project directory and compile the code using the provided Makefile:
   ```bash
   make
   ```
2. **Execute the Program**:
   Run the program by providing an RPN expression as a command-line argument:
   ```bash
   ./RPN "3 4 + 2 * 7 /"
   ```
   This example evaluates the expression \((3 + 4) \times 2 / 7\).

#### Input Format
- The input must be a single string where numbers and operators are separated by spaces.
- Valid operators are `+`, `-`, `*`, and `/`.
- Only integers are handled, and they must be less than 10 per input specification.

#### Output
- The program outputs the result of the RPN expression.
- If an error occurs (such as division by zero or malformed input), an appropriate error message is displayed.

### Ford-Johnson Sorting Algorithm (PmergeMe)

#### Overview
The PmergeMe program implements the Ford-Johnson sorting algorithm, which is efficient for sorting small sets of data. It uses two different STL containers to demonstrate the algorithm's efficiency and outputs the sorted data along with the time taken using each container.

#### Running PmergeMe
1. **Compile the Program**:
   Navigate to the sorting algorithm project directory and compile the code:
   ```bash
   make
   ```
2. **Execute the Program**:
   Run the program by providing a sequence of integers as command-line arguments:
   ```bash
   ./PmergeMe 10 3 5 8 1 4
   ```
   This command sorts the sequence `10, 3, 5, 8, 1, 4` using the Ford-Johnson algorithm.

#### Input Format
- Input integers should be provided directly as command-line arguments.
- Each integer must be positive.

#### Output
- The first line displays the original sequence of integers.
- The second line shows the sorted sequence.
- Subsequent lines display the time taken to sort using each of the two containers, with precision that clearly shows the performance difference.

#### Example Output
```plaintext
Before: 10 3 5 8 1 4
After: 1 3 4 5 8 10
Time to process a range of 6 elements with std::vector: 0.002 ms
Time to process a range of 6 elements with std::list: 0.003 ms
```
