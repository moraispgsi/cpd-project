/*************************** 2D Matrix Interface ***************************/
#ifndef matrix2D_HEADER_FILE
#define matrix2D_HEADER_FILE

/********* Definition of a pointer type for a matrix *********/
typedef struct Matrix *PtMatrix;

/******************** Define Error Codes *********************/
#define OK                  0 /* No error */
#define NO_MEMORY           1 /* No memory available */
#define NO_MATRIX           2 /* No matrix */
#define INDEX_OUT_OF_BOUNDS 3 /* Index out of bounds */
#define VALUE_OUT_OF_BOUNDS 4 /* Value out of bounds */

/********************** Methods Headers **********************/

/*
    Create and initialize a 2D matrix with lines by columns.

    Error Values: NO_MEMORY
    Return: Matrix pointer to the matrix initialized.
*/
Matrix matrix2dCreate (int lines, int columns);

/*
    Creates a copy of a matrix.

    Error Values: NO_MEMORY, NO_MATRIX
    Return: Matrix pointer to the new copied matrix.
*/
Matrix matrix2dCopy (Matrix *pMatrix);

/*
    Destroys a matrix.

    Error Values: NO_MATRIX
    Return: Void.
*/
void matrix2dDestroy (Matrix *pMatrix);

/*
    Retrieves a value from a matrix on the intersection between a line and a column.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS
    Return: int containing the value of the position.
*/
int matrix2dGetValue (Matrix *pmatrix, int line, int column);

/*
    Retrieves a complete line of a matrix.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS
    Return: Int pointer to the line.
*/
int* matrix2dGetLine (Matrix *pmatrix, int line);

/*
    Retrieves a complete column of a matrix.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS
    Return: Int pointer to the column.
*/
int* matrix2dGetColumn (Matrix *pmatrix, int column);

/*
    Changes the value of a position (intersection between a line and a column) in a matrix.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS, VALUE_OUT_OF_BOUNDS
    Return: Void.
*/
void matrix2dSetValue (Matrix *pmatrix, int line, int column, int value);

/*
    Outputs the matrix to the stdout.

    Error Values: NO_MATRIX
    Return: Void.
*/
void matrix2dPrint (Matrix *pmatrix);

/*
    Compares the values in the positions of each matrix.
    
    Error Values: No_MATRIX
    Return: 0 - if the matrixs are equal, -1 - if the matrixs are not equal
*/
int matrix2dCompare (Matrix *pmatrixA, Matrix *pmatrixB);

#endif