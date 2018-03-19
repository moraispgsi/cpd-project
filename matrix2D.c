/************************** Includes **************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix2D.h"

/********************* Matrix Structure ***********************/
struct intMatrix2D{
    int lines;   /* vlaue of the line on the matrix */
    int columns; /* value of the column on the matrix */
    int *data;   /* pointer to all the data on the matrix */     
};

/********************* Internal Functions /*********************/
PtMatrix initialize2DMatrix () {
    return (PtMatrix) malloc (sizeof (struct intMatrix2D));
}

/*************** Implement matrix2D.h Functions ****************/

PtMatrix matrix2dCreate (int lines, int columns) {
    printf("Entreiu");
    PtMatrix matrix2D = initialize2DMatrix ();
    if (matrix2D == NULL) {
        // No memory is available, update error
        return NULL;
    }
    matrix2D->lines = lines;
    matrix2D->columns = columns;
    // allocate contiguous space to hold data in a line by column manner
    matrix2D->data = (int*) malloc (sizeof (int) * lines * columns);
    if (matrix2D->data == NULL) {
        free (matrix2D);  
        return NULL;
    }
    int i, j;
    for (i = 0; i < lines; i++) {
        for (j = 0; j < columns; j++) {
            matrix2dSetValue (matrix2D, i, j, 0);   // initialize position with value 0
        }
    }
    return matrix2D;
}

PtMatrix matrix2dCopy (PtMatrix pMatrix) {
    if (pMatrix == NULL) {
        return NULL;
    }
    PtMatrix newPMatrix = initialize2DMatrix ();
    newPMatrix->lines = pMatrix->lines;
    newPMatrix->columns = pMatrix->columns;
    memcpy (pMatrix->data, newPMatrix->data, sizeof(int) * pMatrix->lines * pMatrix->columns); // could raise problems? because memcopy is for strings
    return newPMatrix;
}

void matrix2dDestroy (PtMatrix* pMatrix) {
    PtMatrix matrix = *pMatrix;
    if (matrix == NULL) {
        return;
    }
    free (matrix->data);
    free (matrix);
    *pMatrix = NULL;    // prevents future reads or random memory overwrite after it's freed if it is accessed
}

int matrix2dGetValue (PtMatrix pMatrix, int line, int column) {
    if (pMatrix == NULL) {
        //return;   return negative value? - got to check it on the otherside..
    }
    int position = line * pMatrix->lines + column;
    return pMatrix->data[position];
}

void matrix2dSetValue (PtMatrix pMatrix, int line, int column, int value) {
    if (pMatrix == NULL) {
        // no matrix
        return;
    }
    int position = line * pMatrix->lines + column;
    pMatrix->data[position] = value;
}

int* matrix2dGetLine (PtMatrix pMatrix, int line) {
    if (pMatrix == NULL) {
        return NULL;
    }
    if (line < 0 || line > pMatrix->lines) {
        return NULL; // out of bounds!
    }
    int position = line * pMatrix->lines;
    return &(pMatrix->data[position]); // reference to the line
}

// MISSING
void matrix2dSetLine (PtMatrix pMatrix, int line, int lineValues[]) {
    if (pMatrix == NULL) {
        return;
    }
    if (line < 0 || line > pMatrix->lines) {
        return; // out of bounds!
    }
    int initialPosition = line * pMatrix->lines;
    int finalPosition = (line + 1) * pMatrix->lines;
    int i, j = 0;
    // manual replacement of data 
    for (i = initialPosition; i < finalPosition; i++) {
        pMatrix->data[i] = lineValues[j++];
    }
}

// MISSING
int* matrix2dGetColumn (PtMatrix pMatrix, int column) {

}

void matrix2dPrint (PtMatrix pMatrix) {
    if (pMatrix == NULL) {
        // no matrix
        return;
    }
    int i, j;
    for (i = 0; i < pMatrix->lines; i++) {
        for (j = 0; j < pMatrix->columns; j++) {
            printf ("%d ", matrix2dGetValue (pMatrix, i, j));
        }
        printf("\n");
    }
}

void matrix2dDebugPrint (PtMatrix pMatrix) {
    printf ("\n\n***************************************");
    printf ("\nSudoku Matrix");
    printf ("\n***************************************\n");
    matrix2dPrint (pMatrix);
    printf ("\n***************************************");
}

int matrix2dCompare (PtMatrix pMatrixA, PtMatrix pMatrixB) {
    if (pMatrixA == NULL || pMatrixB == NULL) {
        // no matrixs
        //return;
    }
    if (pMatrixA->lines != pMatrixB->lines || pMatrixA->columns || pMatrixB->columns) {
        return -1;  // matrixs have different sizes
    }
    int i, j;
    for (i = 0; i < pMatrixA->lines; i++) {
        for (j = 0; j < pMatrixA->columns; j++) {
            if (matrix2dGetValue (pMatrixA, i, j) != matrix2dGetValue (pMatrixB, i, j)) {
                return -1;  // values are different on the same position in both matrixs
            }
        }
    }
    return 0; // matrixs are equal
}