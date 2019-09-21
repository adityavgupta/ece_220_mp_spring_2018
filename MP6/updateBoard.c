/* Aditya Vikram Gupta
 * ece 220 BD2
 * netID : avgupta3
 */

/* countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors
 */
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int alive = 0;
int c;				// Initialize variables
int r;
    
// the for loops are set up to check the immediate neighbors of the column to be tested
// the outer loop is for immediate row neighbors and the inner loop is for the column neighbors.
    for (r = row - 1; r <= row + 1; r++){
        for (c = col-1; c <= col + 1; c++){

// conditons under which the count for alive cells will be incremented

            if (!(r == row && c== col) && r < boardRowSize && c < boardColSize && r >= 0 && c >=0){
                if(board[r * boardColSize + c] == 1){
                alive++;
                }
            }
        }
    }
    return alive;
}



/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {

// create an array boardcopy to copy the current values in the actual board

	int boardcopy[boardRowSize*boardColSize];
	int r,c,i,live;

	for(i=0; i < boardRowSize*boardColSize; i++){ 			//iterate to copy each value in the bordcopy array
		boardcopy[i] = board[i]; 
	}
	for (r = 0 ; r < boardRowSize; r++){
        	for (c = 0; c < boardColSize; c++){
			live = countLiveNeighbor(boardcopy, boardRowSize, boardColSize,r,c); //get the number of live neighbors

			if (boardcopy[r * boardColSize + c] == 1){			// if the current cell is alive 
				if (live < 2 || live > 3)				// if live cells < 2 or > 3 then new cell becomes dead
											// else it continues to stay 1
					board[r * boardColSize + c] = 0;
			}	
				
			 else{
				if(live == 3)						// if however the cell is dead 
					board[r * boardColSize + c] = 1;		// if live neighbors = 3 then revive the cell
				else
					board[r * boardColSize + c] = 0;		// else it stays dead
			}
				 
		}
	}
}	

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){

	int boardnew[boardRowSize*boardColSize];
	int i;
	
	for(i = 0; i < boardRowSize*boardColSize; i++){
		boardnew[i] = board[i];				//copy the current board in a new board
	}

	updateBoard(boardnew, boardRowSize, boardColSize);   	//use the function update board to update the conditions

	for(i=0; i < boardRowSize*boardColSize; i++){		
		if (board[i] != boardnew[i])
			return 0;
	}
	
	return 1;
}


			

