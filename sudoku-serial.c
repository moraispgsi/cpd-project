/************************** Includes **************************/
#include <stdio.h>
#include <stdlib.h>
#include "matrix2D.h"

/******************* Function Declarations ********************/
void usage (char* prog_name);
void loadFile (char *file_name);

/********************** Global Variables **********************/
FILE* input_file;   /* file with sudoku instance matrix */
int sqrN;           /* square root of the matrix dimensions */
//sqrN fica na estrutura da matriz?


int main (int argc, char *argv[]) {
    // the first argument is the program name
    if (argc < 2) {
        printf ("\n");
        printf ("Insufficient arguments.");
        usage (argv[0]);
        exit (EXIT_FAILURE); 
    }
    //loadFile (argv[1]);
    PtMatrix matrix = matrix2dCreate (4, 4);
    matrix2dDebugPrint (matrix);
    matrix2dSetValue (matrix, 0, 2, 5);
    matrix2dDebugPrint (matrix);
    int* lineZero = matrix2dGetLine (matrix, 0);
    printf ("\nval: %d\n", lineZero[2]);
    lineZero[0] = 34;
    int newLine[4] = {0, 1, 2, 3};
    matrix2dSetLine (matrix, 0, newLine);
    printf("line changed\n");
    matrix2dDebugPrint (matrix);

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


void loadFile (char *file_name) {
  /*  input_file = fopen (file_name, "r");
    if (input_file == NULL) {
        printf ("Unable to open the file: %s", file_name);
        exit (EXIT_FAILURE);
    }

    fscanf (input_file, "%1d", &sqrN);  /* read square root value */
   // size_t lineLength = 1024;           /* considered to be the max size of a line */
    //char line[lineLength];    // what if N > 1024 ??? - Como sei que estão lá mais de 1024 characters?
    //int *int_line;                      /* stores values of a line on the correct data type */
    //while (fgets (line, lineLength, input_file) != NULL) {  // read until reachs the end of the file
        
      //  sscanf (s, "")
        // trans
       // puts(line);
        // clear line

        //memset (line, '0', lineLength); // clear all the elements on the 'line' array
   // }
    //printf ("\nReached EOF\n");
}

// Inicializava o array com valores a 0 e depois aqui no loadFile, a cada linha lida carregava para o array
