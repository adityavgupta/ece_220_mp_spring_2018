#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------
// Aditya Vikram Gupta
// avgupta3
// BD2 
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  // initialize a variable m for column
  // in the loop check if sudoku[i][m] = val
  // return true if val exists in row i
        int m;
        for (m = 0; m < 9; m++){
          if(sudoku[i][m] == val){
            return 1;
          }
        }

  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  // initialize a row variable n and check if sudoku[n][j] = val
  // return true if cloumn j has val
  int n;
  for (n = 0; n < 9; n++){
    if(sudoku[n][j] == val){
      return 1;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  // initialize variables rowstart, colstart, r, c
  // divide the 9 rows and 9 columns into groups of three
  // group 0 would have i and j from 0 to 2, group 1 would have i and j from 3 to 5, group 2 i and j from 6 to 8
  // dividing i or j gives us an int corresponding to the group (0,1 or 2)
  // multiplying this int gives us the location of the first element of each group
  // increment this in the loop to get location of each element within that group
  // if the group has val return true  
  int rowstart, colstart, r, c;
	
	rowstart = (i / 3) * 3;
	colstart = (j / 3) * 3;
	
	for(r = rowstart; r < rowstart + 3; r++){
		for(c = colstart; c < colstart + 3; c++){
			
			if(sudoku[r][c] == val)
				return 1;
			
		}
	}

	return 0;	

  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  // use the functions previously defined to check if the val can be filled in the given entry
  
  if (is_val_in_row(val, i, sudoku)) return 0;
  if (is_val_in_col(val, j, sudoku)) return 0;
  if (is_val_in_3x3_zone(val, i, j, sudoku)) return 0;
  
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  // base case:
  // traverse the entire matrix. If no 0 is found return true.
  // if zero is found goto loop (recursive case)
  // in the recursive loop check if num can be filles by using the function "is_val_valid"
  // use the solve_sudoku funtion recursively
  int i, j, r, c;
  for (r = 0; r < 9; r++){
  	for (c = 0; c < 9; c++){
  	
  		if (sudoku[r][c] == 0){
  			i = r;
  			j = c;
  			goto loop;
  		}
  	}
  }
  
  return 1;
  
  loop:
  	for (int num = 1; num <= 9; num++){
  		if (is_val_valid(num, i, j, sudoku)){
  			sudoku[i][j] = num;
  			if (solve_sudoku(sudoku)) 
  				return 1;
  				
  			sudoku[i][j] = 0;
  		}
  	} 
  
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
