# Sudoku Solver
This project intends to implement a serial and two different parallel implementations, using OpenMP and MPI, of a Sudoku Solver.

## Usage
#### Serial Implementation

Compile the sourc code:
    
    gcc matrix2D.c sudoku-serial.c -o sudoku-serial

Execute the source code:
The input file contains the sudoku instance matrix. 

    ./sudoku-serial.exe < input_file
 
 
   
Example of an input file containing a sudoku instance matrix:
Note: The input file must have a empty line on the end

    3
    0 0 0 0 0 0 0 0 0
    0 9 3 6 2 8 1 4 0
    0 6 0 0 0 0 0 5 0
    0 3 0 0 0 0 0 9 0
    0 5 0 0 0 0 0 7 0
    0 4 0 0 0 0 0 6 0
    0 8 0 0 0 0 0 3 0
    0 1 7 5 9 3 4 2 0
    0 0 0 0 0 0 0 0 0
