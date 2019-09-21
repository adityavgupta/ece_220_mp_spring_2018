#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/* Aditya Vikram Gupta
 * avgupta3
 * BD2
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */

 /* Intro Paragraph:
  * This code creates a maze from the .txt taken as input.
  * Read all the chars except for '\n' and construct the board.
  * If the char read is 'S', set the start point.
  * If the char is 'E' set the end point.
  * In destroyMaze, destroy each row which is a string. Destroy the char** and the maze object.
  * In printMaze, print each element of the cells and print '\n' for each newline.
  * In solveMazeManhattanDFS, first check whether this point was visited or is invalid. Check whether it is the end point.
  * Recursively solve this problem using backtracking.
  * The functions used are:
  * maze_t*createMaze
  * destroyMaze
  * printMaze
  * recursive function : solveMazeManhattanDFS
  */

maze_t * createMaze(char * fileName)
{
  // Your code here. Make sure to replace following line with your own code.
  // allocate memory for the maze

  maze_t *maze = malloc(sizeof(maze_t));	// declare maze pointer
  FILE* file = fopen(fileName, "r");		//declare pointer : file
  if (file == NULL) return NULL;

  fscanf(file, "%d %d", &(maze->width), &(maze->height));	// read the number of rows and columns

  maze->cells = (char**)malloc(maze->height * sizeof(char*)); // a new array of size char*

  int i;
  for(i = 0; i < maze->height; i++){

    maze->cells[i] = (char*)malloc(maze->width * sizeof(char));
  }

  char temp;		// declare a temporary variable temp
  int r,c;

  //parse through the matrix
  //Read all the chars except for '\n' and construct the board.
  // If the char read is 'S', set the start point.
  // If the char is 'E' set the end point.

  for( r = 0; r < maze->height; r++){
    for(c= 0; c < maze -> width; c++){
      fscanf(file, "%c", &temp);
      if(temp == '\n'){

	c--;
	continue;

      }
      else maze->cells[r][c] = temp;
      if(temp == 'S'){
        maze->startRow = r;
        maze->startColumn = c;
      }
      else if(temp == 'E'){
        maze->endRow = r;
        maze->endColumn = c;
      }

    }
  }
  fclose(file);
  return maze;

}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */

 // In destroyMaze, destroy each row which is a string. Destroy the char** and the maze object.
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i = 0; i < maze->height; i++){
      free(maze->cells[i]);
    }
    free(maze->cells);
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */


 // In printMaze, print each element of the cells and print '\n' for each newline.

void printMaze(maze_t * maze)
{
    // Your code here.
    int r,c;
    for(r= 0; r < maze->height; r++){
    	for(c = 0; c < maze->width; c++){
    		printf("%c", maze->cells[r][c]);
    	}
    	printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    /*	If (col, row) outside bounds of the maze return false
	if (col, row) is not an empty cell return false
	if (col, row) is the end of the maze return true
	set (col, row) as part of the solution path in the maze (*)
	if (solveMaze(left of (col, row) ) == true) return true
	if (solveMaze(right of (col, row) ) == true) return true
	if (solveMaze(up of (col, row) ) == true) return true
	if (solveMaze(down of (col, row) ) == true) return true
	unmark (col, row) as part of solution and mark as visited (~)
	return false
    */

    if(row < 0 || col < 0 || row >= maze->height || col >= maze->width) return 0;
    if (maze->cells[row][col] == '*' || maze->cells[row][col] == '%' || maze->cells[row][col] == '~' ) return 0;
    if (maze->cells[row][col] == 'E') return 1;

    maze->cells[row][col] = '*';

    if (solveMazeManhattanDFS(maze, col-1, row)){
	maze->cells[maze->startRow][maze->startColumn] = 'S';
    	return 1;
    }
    if (solveMazeManhattanDFS(maze, col+1, row)){
        maze->cells[maze->startRow][maze->startColumn] = 'S';
    	return 1;
    }
    if (solveMazeManhattanDFS(maze, col, row-1)) {
    	maze->cells[maze->startRow][maze->startColumn] = 'S';
	return 1;
    }
    if (solveMazeManhattanDFS(maze, col, row+1)) {
    	maze->cells[maze->startRow][maze->startColumn] = 'S';
	return 1;
    }

    maze->cells[row][col] = '~';
    return 0;

}
