/************************** Includes **************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "matrix2D.h"

/******************* Function Declarations ********************/
void usage (char* prog_name);
void loadMatrixFromFile (char* file_name);
int numberOfLines (char* file_name);
int solveSudoku (PtMatrix pMatrix);

/********************** Global Variables **********************/
FILE* input_file;   /* file with sudoku instance matrix */
int sqrN;           /* square root of the matrix dimensions */
//sqrN fica na estrutura da matriz?
PtMatrix matrix = NULL;


int main (int argc, char* argv[]) {
    // the first argument is the program name
    if (argc < 2) {
        printf ("\n");
        printf ("Insufficient arguments.");
        usage (argv[0]);
        exit (EXIT_FAILURE); 
    }
    /*PtMatrix matrix = matrix2dCreate (4, 4);
    matrix2dDebugPrint (matrix);
    matrix2dSetValue (matrix, 0, 2, 5);
    matrix2dDebugPrint (matrix);
    int* lineZero = matrix2dGetLine (matrix, 0);
    printf ("\nval: %d\n", lineZero[2]);
    lineZero[0] = 34;
    int newLine[5] = {0, 1, 2, 3, 4}; 
    matrix2dSetLine (matrix, 0, newLine);
    printf("line changed\n");
    matrix2dDebugPrint (matrix);
    */
    //matrix = matrix2dCreate (4, 4);
    loadMatrixFromFile (argv[1]); // receive matrix
    printf ("square root: %d", sqrN);
    matrix2dDebugPrint (matrix);

    //int* lineZero = matrix2dGetLine (matrix, 1);
    //printf ("\nval: %d\n", lineZero[3]);
    //printf ("\nval: %d\n", lineZero[4]);

    //loadFile (argv[1]);
    //solveSudoku (matrix);
    //matrix2dPrint (matrix);

    exit (EXIT_SUCCESS);
}


/*
    Outputs to the stdout how to execute the program successfully.

    Return: Void.
*/
void usage (char* prog_name) {
    printf ("\n*******************************************");
    printf ("\nUsage: %s < input-file ", prog_name);
    printf ("\nThe 'input-file' stands for the file containing the sudoku instance matrix.");
    printf ("\nExample: %s instance1.in", prog_name);
    printf ("\n\n");
}


/*
    Load matrix from file to memory.

    Return: Void.
*/
void loadMatrixFromFile (char* file_name) {
    input_file = fopen (file_name, "r");
    if (input_file == NULL) {
        printf ("Unable to open the file: %s", file_name);
        exit (EXIT_FAILURE);
    }
    int numLines = numberOfLines (file_name) - 1;   // probabily adds unnecessary overhead
    matrix = matrix2dCreate (numLines , numLines); /* create matrix based on the number of line; -1 because the 1st line doesn't count */
    
    size_t lineLength = 11; /* assume to be the max length of a line */
    int line[lineLength];   /* stores the values on a line in integer format */
    char character;         /* token read */
    size_t position = 0;    /* current position to write to the line array */
    size_t lineIndex = 0;   /* number of the line that is being read */
    int firstLine = 1;      /* workaround to process the 1st line differently */
    // read file
    while ((character = fgetc (input_file)) != EOF) {
        if (character == ' ') {
            continue;
        }else if (character == '\n') {
            if (firstLine) {
                firstLine = 0;
            }else {
                position = 0; // reset position index
                matrix2dSetLine (matrix, lineIndex++, line);
            }
        }else { // its assumed to be a number
            if (firstLine) {
                sqrN = atoi (&character);   /* convert character to integer */
            } else {
                line[position++] = atoi (&character);
            }
        }
    }
}

/*
    Count the number of lines inside a file.

    Return Value: Int representing the number of lines inside a file.
*/
int numberOfLines (char* file_name) {
    FILE* input_file = fopen (file_name, "r");
    if (input_file == NULL) {
        printf ("Unable to open the file: %s", file_name);
        exit (EXIT_FAILURE);
    }

    int lines = 0;
    char character;
    while ((character = fgetc (input_file)) != EOF) {
        if (character == '\n') {
            lines++;
        }
    }
    return lines;
}

// TODO
int solveSudoku (PtMatrix pMatrix) {

}

