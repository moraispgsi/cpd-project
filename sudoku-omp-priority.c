#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <math.h>

// get the size of elements on an array
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

typedef int bool;
#define false 0
#define true 1

struct Puzzle {
    int row;
    int col;
    int depth;
    long double priority;
	int root_n;
	int n;
	int ** matrix;
};

typedef struct Puzzle Puzzle;


static int _states_searched_ = 0;

///////////////////////////////////////////////////////////
//// Priority Queue
///////////////////////////////////////////////////////////

// Node
typedef struct node {
    Puzzle * puzzle;
    struct node* next;
} Node;


// Function to Create A New Node
Node* newNode(Puzzle * puzzle)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->puzzle = puzzle;
    temp->next = NULL;
 
    return temp;
}
 
// Return the value at head
/**
* Return the value at head of the queue
* @param head The head of the queue
* @return puzzle A pointer to a Sudoku structure
*/ 
Puzzle * peek(Node** head)
{
    return (*head)->puzzle;
}

 
/**
* Removes the element with the highest priority form the list
* @param head The head of the queue
*/ 
void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
 
 
/**
* Function to push a Sudoku structure according to its priority
* @param head The head of the queue
* @param puzzle A pointer to a Sudoku structure
*/
void push(Node** head, Puzzle * puzzle)
{

    Node* start = (*head);
 
    // Create new Node
    Node* temp = newNode(puzzle);
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->puzzle->priority > puzzle->priority) {
 
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
 
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
               start->next->puzzle->priority < puzzle->priority) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }

}
 
/**
* Function to check if the list is empty
* @param head The head of the queue
* @return Returns true if the list is empty
*/
int isEmpty(Node** head)
{
    return (*head) == NULL;
}


///////////////////////////////////////////////////////////
//// Global Variables
///////////////////////////////////////////////////////////

bool solution_found = false; // no solution found at the beginning
Node* queue;
    


/**
* Check if number is already in a sub grid of the puzzle matrix.
* @param row Row.
* @param col Column.
* @param num Comparison value.
* @return Returns true if the number is inside one of the sub-grids of the matrix.
*/
bool check_grid(Puzzle * puzzle, int row, int col, int num){
    int i, j;
    int count = 0;
    for (i = 0; i < puzzle->root_n; ++i){
        for (j = 0; j < puzzle->root_n; ++j){
            if (puzzle->matrix[i + row][j + col] == num){
                count++;
                if(count > 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
* Check if a number is already in a column.
* @param puzzle Sudoku puzzle data structure.
* @param col Column.
* @param num Comparison value.
* @return Returns true if the number is in the column.
*/
bool check_column(Puzzle * puzzle, int col, int num){
    int i;
    int count = 0;
    for (i = 0; i < puzzle->n; ++i){
        if(puzzle->matrix[i][col] == num){
            count++;
            if(count > 1) {
                return true;
            }
        }
    }
    return false;
}

/**
* Check if a number is already in a row.
* @param puzzle Sudoku puzzle data structure.
* @param row Row.
* @param num Comparison value.
* @return Returns true if the number is in the row.
*/
bool check_row(Puzzle * puzzle, int row, int num){
    int i;
    int count = 0;
    for (i = 0; i < puzzle->n; ++i){
        if (puzzle->matrix[row][i] == num){
            count++;
            if(count > 1) {
                return true;
            }
        }
    }
    return false;
}


/**
* Check if a number is already in a matrix cell according to sudoku rules.
* @param puzzle A pointer to a Sudoku puzzle data structure.
* @param row Row.
* @param col Column.
* @param num Comparison value.
* @return Returns true if the number is not valid.
*/
bool is_valid(Puzzle * puzzle, int row, int col, int num){
    return !(check_row(puzzle,row, num)) && 
           !(check_column(puzzle,col, num)) && 
           !(check_grid(puzzle, row - row % puzzle->root_n, col - col % puzzle->root_n, num));
}


/**
* Print the puzzle matrix.
* @param puzzle A pointer to a Sudoku puzzle data structure.
*/
void debug_puzzle(Puzzle * puzzle){
    #pragma omp critical 
    {
        if (puzzle != NULL) {
            int n = puzzle->n;
            int slots = (n + n - 1);
            char buffer[slots + 1];
            memset(buffer, '-', slots);    // init all positions with '-'
            buffer[slots] = '\0';          // define end of string
            printf("%s\n",buffer);
            printf("Puzzle:\n"); 
            printf("-depth: %d\n", puzzle->depth);
            printf("-row: %d\n", puzzle->row);
            printf("-col: %d\n", puzzle->col);
            //printf("-priority: %Lf\n", puzzle->priority);
            printf("%s\n",buffer);
            int i, j;
            for (i = 0; i < n; ++i){
                for (j = 0; j < n; ++j){
                    printf("%d ", puzzle->matrix[i][j]);
                }
                printf("\n");
            }
            printf("%s\n",buffer);
        }
    }
}


Puzzle * copy(Puzzle * puzzle) {
    if (puzzle == NULL) {
        return NULL;
    }
    Puzzle * copyPuzzle = malloc(sizeof(Puzzle));
    copyPuzzle->depth = puzzle->depth;
    copyPuzzle->priority = puzzle->priority;
    copyPuzzle->row = puzzle->row;
    copyPuzzle->col = puzzle->col;
    copyPuzzle->root_n = puzzle->root_n;
    copyPuzzle->n = puzzle->n;
    copyPuzzle->matrix = (int**) malloc(puzzle->n * sizeof(int*));          // alloc space for matrix
    int i,j;
    // manual copy
    for (i = 0; i < puzzle->n; ++i){
        copyPuzzle->matrix[i] = (int * )malloc(puzzle->n * sizeof(int));    // alloc space
        for (j = 0; j < puzzle->n; ++j){
            copyPuzzle->matrix[i][j] = puzzle->matrix[i][j];                // copy values
        }
    }
    return copyPuzzle;
}

/**
* Find empty cell in the sudoku.
* @param puzzle A Pointer to a Sudoku puzzle data structure.
* @param row Row number reference
* @param col Column number reference
* @return Returns true if the puzzle has an empty position.
*/
bool find_empty(Puzzle * puzzle, int * row, int * col){
    for (*row = 0; *row < puzzle->n; (*row)++){
        for (*col = 0; *col < puzzle->n; (*col)++){
            if (puzzle->matrix[*row][*col] == 0){
                return true;
            }
        }
    }
    return false;
}


/**
* Generates the successors for a given puzzle
* @param puzzle Sudoku puzzle data structure.
* @return Returns true if there were sucessors, false otherwise
*/
bool generateSucessors(Puzzle * puzzle) {
    
    int n = puzzle->n;
    int pos, row, col, i; 
    bool found = find_empty(puzzle, &row, &col);

    if(!found) {
        return false;
    }

    for(i = 1; i <= n; i++) {
        Puzzle * sucessor = copy (puzzle);
        sucessor->matrix[row][col] = i;
        sucessor->depth = puzzle->depth + 1;
        sucessor->row = row;
        sucessor->col = col;
        long double offset = powl((long double) n, (long double) n * n + 2 - sucessor->depth);
        sucessor->priority = ((long double)i) * offset + puzzle->priority;
        
        #pragma omp critical 
        {
            if(queue == NULL) {
                queue = newNode(sucessor);
            } else {
                push(&queue, sucessor);
            }
        }
        
    }

    return true;
}

/**
* Free's a Sudoku puzzle structure
* @param puzzle A pointer to a Sudoku puzzle data structure.
*/
void cleanPuzzle (Puzzle * puzzle) {
    if (puzzle != NULL) {
        int n = puzzle->n;
        int i;
        // Free memory   
        for (i = 0; i <  n ; i++){
            free(puzzle->matrix[i]);
        }
        free(puzzle->matrix);
        free(puzzle);
    }
}

/**
* Solves a Sudoku puzzle in parallel
* @param puzzle A pointer to a Sudoku puzzle data structure.
*/
void solve(Puzzle * puzzle) {
    
    queue = newNode(puzzle);
    #pragma omp parallel
    {
        do 
        {
            Puzzle * puzzle;
            #pragma omp critical 
            {
                if(!isEmpty(&queue)) {
                    puzzle = peek(&queue);
                    pop(&queue);
                    _states_searched_ ++;
                } else {
                    puzzle = NULL;
                    queue = NULL;
                }
            }
          
            if(puzzle != NULL) {
                int row = puzzle->row;
                int col = puzzle->col;
                
                bool isValid = is_valid(puzzle, row, col, puzzle->matrix[row][col]);
                //printf("%d %d %d %d %d\n", puzzle->depth, row, col, puzzle->matrix[row][col], isValid);
                if(puzzle->depth == 1 || isValid) {
                    //debug_puzzle(puzzle);
                    bool hasSucessors = generateSucessors(puzzle);
                    //This is necessary because we can't assign a false to solution_found concurrently
                    if(!hasSucessors) {
                        solution_found = true; 
                        printf("--------SOLUTION--------\n");
                        debug_puzzle(puzzle);
                        /*
                        //Releasing the queue takes a long time
                        #pragma omp critical 
                        {
                            //release the queue
                            while(!isEmpty(&queue)) {
                                pop(&queue);
                            }
                        }
                        */
                    }
                    
                }
                
                cleanPuzzle(puzzle);
            }  
            
          
        } while(!solution_found);
        
    }

    
}


int main(int argc, char *argv[]){
	double start = omp_get_wtime();

	FILE * file_input;
	FILE * file_output;

	char * filename;

	// Check if file path was passed as an argument
	if (argc > 2){
		printf("ERROR: Too many arguments.\n");
		exit(EXIT_FAILURE);
	} else if (argc < 2) {
		printf("ERROR: Missing arguments.\n");
		exit(EXIT_FAILURE);
	}

	filename = argv[1];

	// Open file in read mode
	if ((file_input = fopen(filename,"r")) == NULL){
		printf("ERROR: Could not open file %s\n",filename);
		exit(EXIT_FAILURE);
	}

	// Number of rows and columns
	int n;
	// Square root of n
	int root_n;

	// Read first line from the file to get n
	fscanf(file_input, "%d\n", &root_n);

	n = root_n * root_n;

	// ======================================
	/** Initialize puzzle data structure */

	// Puzzle matrix N x N
	Puzzle * puzzle = malloc(sizeof(Puzzle));
	puzzle->n = n;
	puzzle->root_n = root_n;
    puzzle->row = 0;
    puzzle->col = 0;
	puzzle->depth = 1;
	puzzle->priority = 0;
	puzzle->matrix = (int**) malloc(n * sizeof(int*));
    int i;
	for (i = 0; i < n; ++i){
		puzzle->matrix[i] = (int * )malloc(n * sizeof(int));
	}

	// Read matrix from the file
	int cursor;
	int row = 0, col = 0, j;
	for (i = 0; i < n; ++i){
		
		for (j = 0; j < n; ++j){
			fscanf(file_input,"%d",&puzzle->matrix[i][j]);
		}
		fscanf(file_input, "\n");
	}
	// ======================================

	// Close file
	fclose(file_input);


    //////////////////////////////////////////////////////////
    ////// START
    //////////////////////////////////////////////////////////
    
    solve(puzzle);    
    
    



    //////////////////////////////////////////////////////////
    ////// END
    //////////////////////////////////////////////////////////
    
    /*
	if(solve(puzzle)){

		// Write solution to .out file.
		char * name_out;
		
		// Split file name
		filename[strlen(filename) - 3 ] = '\0';
		name_out = (char *) malloc(sizeof(char) * (strlen(filename) + 4));
		strcpy(name_out, filename);
		strcat(name_out, "serial.out");

		// Open file in write mode
		file_output = fopen(name_out, "w");
		print_puzzle(file_output, puzzle);
		// Close output file
		fclose(file_output);
	} else {
		printf("No solution\n");
	}

    */

	double end = omp_get_wtime();
    printf("Searched %d states in total.\n", _states_searched_);
	printf("Elapsed time: %f (s)\n", end - start);
	return EXIT_SUCCESS;
}