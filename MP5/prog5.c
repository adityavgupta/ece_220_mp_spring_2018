/* Aditya Vikram Gupta		
 * avgupta3 
 * 3/1/18
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */

 /* Intro paragraph:
  * In this program we write the three functions "set_seed", "start game", "make_guess", for the codebreaker program.
  * The function set_seed sets the seed value for the pseudo random.
  * The function start_game is called by main.c after set_seed but before the user makes guesses.
  * The function make_guess is called after the user inputs the numbers.
  * The function must calculate the number of perfect and misplaced matches for a guess, given the solution recorded earlier by start_game.


 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
    int seed, valid;
    char post[2];
    valid = sscanf (seed_str, "%d%1s", &seed, post);
    if (valid == 1){
        srand(seed);
        return 1;
    }else {
        printf("set_seed: invalid seed\n");
        return 0;
    }
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
   
}

/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    *one=solution1=(rand()%8)+1;
    *two=solution2=(rand()%8)+1;
    *three=solution3=(rand()%8)+1;
    *four=solution4=(rand()%8)+1;
    
    guess_number=1;
    
    //printf("      %d %d %d %d    \n", solution1, solution2, solution3, solution4);
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

    char post[2];
    int w,x,y,z;
    
    int perfect = 0;			//Initialize all the variables used in this function.
    int misplaced = 0;
    int w_paired = 0;
    int x_paired = 0;
    int y_paired = 0;
    int z_paired = 0;
    int sol1_paired = 0;
    int sol2_paired = 0;
    int sol3_paired = 0;
    int sol4_paired = 0;
    
	// Variables w,x,y,z have to be in the range 1 to 8. 
	// If they are less than 1 or greater than 8, it is an invalid guess.

    if (sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)==4){
        if(w < 1 || w > 8){
            printf("make_guess: invalid guess\n");			
            return 0;
        }
        if(x < 1 || x > 8){
            printf("make_guess: invalid guess\n");
            return 0;
        }
        if(y < 1 || y > 8){
            printf("make_guess: invalid guess\n");
            return 0;
        }
        if(z < 1 || z > 8){
            printf("make_guess: invalid guess\n");
            return 0;
        }
        
//If the string is valid, we store a copy of the guessed code in order of the four addresses provided as input parameters (one, two, three, four)

        *one = w;
        *two = x;
        *three = y;
        *four = z;
  
// For w, x, y, z check if they are equal to their respective solutions 1, 2, 3, 4
// Count the number of perfect matches. If there is a perfect match, mark the guess and solution as "paired" 
      
        if(w == solution1){
            perfect++;
            w_paired = 1;
            sol1_paired = 1;
        }
        
        if(x == solution2){
            perfect++;
            x_paired = 1;
            sol2_paired = 1;
        }
        
        if(y == solution3){
            perfect++;
            y_paired = 1;
            sol3_paired = 1;
        }
     
        if(z == solution4){
            perfect++;
            z_paired = 1;
            sol4_paired = 1;
        }

// If the first guess number is not paired yet, check it against the second solution number (if it is also not paired).
// If it matches, count a misplaced match and mark the second solution number as paired.
// Repeat 2-3 for the second guess number (if it is not already paired), then the third guess number, then the fourth.
        
        if (w_paired == 0){
            if(sol2_paired == 0 && w == solution2){
                misplaced++;
                sol2_paired = 1;
            }
            else if(sol3_paired == 0 && w == solution3){
                misplaced++;
                sol3_paired = 1;
            }
            else if (sol4_paired == 0 && w == solution4){
                misplaced++;
                sol4_paired = 1;
            }
        }
        if (x_paired == 0){
            if(sol1_paired == 0 && x == solution1){
                misplaced++;
                sol1_paired = 1;
            }
            else if(sol3_paired == 0 && x == solution3){
                misplaced++;
                sol3_paired = 1;
            }
            else if (sol4_paired == 0 && x == solution4){
                misplaced++;
                sol4_paired = 1;
            }
        }
        if (y_paired == 0){
            if(sol1_paired == 0 && y == solution1){
                misplaced++;
                sol1_paired = 1;
            }
            else if(sol2_paired == 0 && y == solution2){
                misplaced++;
                sol2_paired = 1;
            }
            else if (sol4_paired == 0 && y == solution4){
                misplaced++;
                sol4_paired = 1;
            }
        }
        if (z_paired == 0){
            if(sol1_paired == 0 && z == solution1){
                misplaced++;
                sol1_paired = 1;
            }
            else if(sol2_paired == 0 && z == solution2){
                misplaced++;
                sol2_paired = 1;
            }
            else if (sol3_paired == 0 && z == solution3){
                misplaced++;
                sol3_paired = 1;
            }
        }
        printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
        guess_number++;
        return 1;
    }
    else printf("make_guess: invalid guess\n");
    return 0;
}




