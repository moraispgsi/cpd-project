/*************************** 2D Matrix Interface ***************************/
#ifndef matrix2D_HEADER_FILE
#define matrix2D_HEADER_FILE

/********* Definition of a pointer type for a matrix *********/
typedef struct intMatrix2D *PtMatrix;

/******************** Define Error Codes *********************/
#define OK                  0 /* No error */
#define NO_MEMORY           1 /* No memory available */
#define NO_MATRIX           2 /* No matrix */
#define INDEX_OUT_OF_BOUNDS 3 /* Index out of bounds */
#define VALUE_OUT_OF_BOUNDS 4 /* Value out of bounds */
#define NO_ARRAY            5 /* No array */

/********************** Methods Headers **********************/

/*
    Create and initialize a 2D matrix with lines by columns.

    Error Values: NO_MEMORY
    Return: Matrix pointer to the matrix initialized. NULL - if the matrix
        wasn't created.
*/
PtMatrix matrix2dCreate (int lines, int columns);

/*
    Creates a copy of a matrix.

    Error Values: NO_MEMORY, NO_MATRIX
    Return: Matrix pointer to the new copied matrix.
*/
PtMatrix matrix2dCopy (PtMatrix pMatrix);

/*
    Destroys a matrix.

    Error Values: NO_MATRIX
    Return: Void.
*/
void matrix2dDestroy (PtMatrix *pMatrix);

/*
    Retrieves a value from a matrix on the intersection between a line and a column.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS
    Return: Int containing the value of the position.
*/
int matrix2dGetValue (PtMatrix pMatrix, int line, int column);

/*
    Changes the value of a position (intersection between a line and a column) in a matrix.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS, VALUE_OUT_OF_BOUNDS
    Return: Void.
*/
void matrix2dSetValue (PtMatrix pMatrix, int line, int column, int value);

/*
    Retrieves a complete line of a matrix.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS
    Return: Int pointer to the line.
*/
int* matrix2dGetLine (PtMatrix pMatrix, int line);

/*
    Changes the values of an entire line of a matrix.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS, NO_ARRAY
    Return: Void.
*/
void matrix2dSetLine (PtMatrix pMatrix, int line, int lineValues[]);

/*
    Retrieves a complete column of a matrix.

    Error Values: NO_MATRIX, INDEX_OUT_OF_BOUNDS
    Return: Int pointer to the column.
*/
int* matrix2dGetColumn (PtMatrix pMatrix, int column);

/*
    Outputs the matrix to the stdout. The matrix is on the same format as the input matrix.

    Error Values: NO_MATRIX
    Return: Void.
*/
void matrix2dPrint (PtMatrix pMatrix);

/*
    Outputs the matrix to the stdout, but more easy to read.
    Error Values: NO_MATRIX
    Return: Void.
*/
void matrix2dDebugPrint (PtMatrix pMatrix);

/*
    Compares the values in the positions of each matrix.
    
    Error Values: No_MATRIX
    Return: 0 - if the matrixs are equal, -1 - if the matrixs are not equal
*/
int matrix2dCompare (PtMatrix pMatrixA, PtMatrix pMatrixB);

#endif