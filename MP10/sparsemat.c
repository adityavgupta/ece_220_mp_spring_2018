/* Aditya Vikram Gupta 
   avgupta3 
   BD2
*/

/*
   This program takes a sparse matrix (a matrix with mostly zeroes) and stores it so that the only values 
   that are in the structure are nonzero terms. 
   The structure is a lists of lists, which is storing the row, the column, and then the value within
   that column. 
   This is done by various functions. 
   load_lils opens the file and then reads the data from that file, while calling the set_lils function in order to set
   the correct row and column to value.
   The set_lils function checks if the value is 0 at the node and then will delete it, while switching the pointer so that it goes
   to the next correct node. 
   gv_lils returns the value of the element at the row and column within the matrix. 
   save_lils writes into a text file so that the linked lists are in the corret order (row major order). 
   add_lils adds the two matricies A and B together in order to calculate the necessary additions. 
   Last but not least, destroy_lils frees all the memory so that all the memory allocations are freed and so
   there are no memory leaks.
 */
 
 
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


sp_lils * load_lils(char* input_file)
{
	FILE* file = fopen(input_file, "r");		//Open file for reading
	
	sp_lils* matrix = calloc(1, sizeof(sp_lils));	//Allocate mem space
	
	fscanf(file, "%d %d", &matrix->m, &matrix->n);	//Scan row and col vals
	matrix->nz = 0;
	
	int r, c;
	double temp;
	
	while(fscanf(file, "%d %d %lf\n", &r, &c, &temp) > 0){
		set_lils(matrix, r, c, temp);		//Keep reading and adding nodes until nothing left
	}
	
	fclose(file);
	return matrix;
}


double gv_lils(sp_lils * mat_l,int row,int col)
{	
	sp_lils_row_node * curr_row = mat_l->row_list_head;	//Curr row pointer
	
	while(curr_row != NULL && curr_row->next != NULL && curr_row->idx_r != row && 
	  curr_row->next->idx_r <= row){
		curr_row = curr_row->next;		//Find matching row
	}
	
	if(curr_row == NULL || curr_row->idx_r != row)	//If row doesnt exist
		return 0;
	
	sp_lils_col_node * curr_col = curr_row->col_list_head;	//Curr col pointer
	
	while(curr_col != NULL && curr_col->next != NULL && curr_col->idx_c != row && 
	  curr_col->next->idx_c <= col){
		curr_col = curr_col->next;		//Find matching col
	}
	
	if(curr_col == NULL || curr_col->idx_c != col)	//If col doesnt exist
		return 0;
		
	return curr_col->value;		//Return val
}

// This function takes care of all possible cases, for adding/replacing/deleting nodes
void set_lils(sp_lils * mat_l, int row, int col, double value)
{
	sp_lils_row_node* curr_row = mat_l->row_list_head;
	
	//Look for row, stop if null reached or row found
	while(curr_row != NULL && curr_row->idx_r != row && curr_row->next != NULL && 
	  curr_row->next->idx_r <= row){
		curr_row = curr_row->next;
	}
	
	//No matching row found and value is 0
	if(curr_row == NULL && value == 0){
		return;
	}
	
	//Row doesnt exist
	if(curr_row != NULL && curr_row->idx_r != row && value == 0){
		return;
	}

	//Create col, add node
	if(curr_row == NULL || curr_row->idx_r > row){
		sp_lils_row_node* temp = curr_row;
		mat_l->row_list_head = calloc(1, sizeof(sp_lils_row_node));
		curr_row = mat_l->row_list_head;
		curr_row->idx_r = row;
		curr_row->col_list_head = NULL;
		curr_row->next = temp;
	}
	
	//Create row, add node
	if(curr_row->idx_r < row){
		sp_lils_row_node* temp = curr_row->next;
		curr_row->next = calloc(1, sizeof(sp_lils_row_node));
		curr_row->next->next = temp;
		curr_row->next->col_list_head = NULL;
		curr_row->next->idx_r = row;
		curr_row = curr_row->next;
	}
	
	//Look for col
	sp_lils_col_node* curr_col = curr_row->col_list_head;
	
	while(curr_col != NULL && curr_col->idx_c != row && curr_col->next != NULL && 
	  curr_col->next->idx_c <= col){
		if(value == 0 && curr_col->next->idx_c == col){
			break;
		}
		curr_col = curr_col->next;
	}

	//Col head doesnt exist
	if(curr_col == NULL && value == 0){
		return;
	}
	
	//Col doesnt exist
	if(curr_col != NULL && curr_col->idx_c != col && value == 0){
		return;
	}
	
	//If head, remove
	if(value == 0 && curr_col == curr_row->col_list_head){
		free(curr_col);
		curr_row->col_list_head = NULL;
		mat_l->nz--;
		return;
	}

	//Delete node if in row, col
	if(value == 0 && curr_col->next != NULL && curr_col->next->idx_c == col && curr_row->idx_r == row){
		sp_lils_col_node* temp = curr_col->next->next;
		free(curr_col->next);
		curr_col->next = temp;
		mat_l->nz--;
		return;
	}
	
	//Check if curr, next is in bounds
	if(value == 0 && curr_col->idx_c < col && curr_col->next->idx_c > col){
		return;
	}
	
	//Make head col node
	if(curr_col == NULL || curr_col->idx_c > col){
		sp_lils_col_node *temp = curr_col;
		curr_row->col_list_head = calloc(1, sizeof(sp_lils_col_node));
		curr_col = curr_row->col_list_head;
		mat_l->nz++;
		curr_col->idx_c = col;
		curr_col->value = value;
		curr_col->next = temp;
	}
	
	//Make col node
	if(curr_col->idx_c < col && value != 0){
		sp_lils_col_node *temp = curr_col->next;
		curr_col->next = calloc(1, sizeof(sp_lils_col_node));
		mat_l->nz++;
		curr_col->next->idx_c = col;
		curr_col->next->value = value;
		curr_col->next->next = temp;
		curr_col = curr_col->next;
	}

	//Set val again
	if(curr_row->idx_r == row && curr_col->idx_c == col && value != 0){
		curr_col->value = value;
	}
	
	return;
}


void save_lils(char * file_name,sp_lils * mat_l)
{
	FILE* file = fopen(file_name, "w");			//Open file for writing
	
	fprintf(file, "%d %d\n", mat_l->m, mat_l->n);		//Print row and col vals
	
	sp_lils_row_node* curr_row = mat_l->row_list_head;	//Create curr pointers
	sp_lils_col_node* curr_col = mat_l->row_list_head->col_list_head;
	
	while(curr_row != NULL){			//Loop through rows
		curr_col = curr_row->col_list_head;
		while(curr_col != NULL){		//Through cols
			
			fprintf(file, "%d %d %lf\n", curr_row->idx_r, curr_col->idx_c, curr_col->value);
			curr_col = curr_col->next;	//Print r,c,val and newline
			
		}
		curr_row = curr_row->next;
		
	}
	
	fclose(file);		//Close file
	return;
}


sp_lils * add_lils(sp_lils * matA, sp_lils * matB)
{
	if (matA->n != matB->n || matA->m != matB->m)	//Check if they can be added
		return NULL;
		
	sp_lils* matC = calloc(1, sizeof(sp_lils));	//Create 3rd matrix
	matC->m = matA->m;
	matC->n = matA->n;
	
	sp_lils_row_node* curr_row = matA->row_list_head;	//Create curr pointers
	sp_lils_col_node* curr_col = matA->row_list_head->col_list_head;
	while(curr_row != NULL){				//Loop through rows
		curr_col = curr_row->col_list_head;
		while(curr_col != NULL){			//Loop through cols
			set_lils(matC,curr_row->idx_r, curr_col->idx_c, curr_col->value);
			curr_col = curr_col->next;		//Create node C = C + A
		}
		curr_row = curr_row->next;
	}
	
	sp_lils_row_node* curr_row2 = matB->row_list_head;	//Create curr pointers
	sp_lils_col_node* curr_col2 = matB->row_list_head->col_list_head;
	while(curr_row2 != NULL){				//Loop through rows
		curr_col2 = curr_row2->col_list_head;
		while(curr_col2 != NULL){			//Loop through cols
			set_lils(matC,curr_row2->idx_r, curr_col2->idx_c, (curr_col2->value + 
			  gv_lils(matC, curr_row2->idx_r, curr_col2->idx_c)));
			curr_col2 = curr_col2->next;		//Create node C = C + B
		}
		curr_row2 = curr_row2->next;
	}
	
	return matC;		//Return added matrix
}


void destroy_lils(sp_lils * mat_l)
{
	sp_lils_row_node* curr_row = mat_l->row_list_head;	//Set current pointers
	sp_lils_col_node* curr_col = mat_l->row_list_head->col_list_head;
	
	while(curr_row != NULL){				//Iterate though rows
		curr_col = curr_row->col_list_head;		//Through cols
		while(curr_col != NULL){
			sp_lils_col_node* temp1 = curr_col;	//Use temp to not loose nodes.
			curr_col = curr_col->next;
			free(temp1);				//Free all cols first
		}
		
		sp_lils_row_node* temp2 = curr_row;		//Then free the row
		curr_row = curr_row->next;
		free(temp2);
	}

	free(mat_l);
	
	return;
}


