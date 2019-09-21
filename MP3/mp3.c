#include <stdio.h>
#include <stdlib.h>

<<<<<<< .mine
/* Intro paragraph:
 Aditya Vikram Gupta
 avgupta3
 February 12 2018
 This is a program that prints out a row of the Pascal's triangle depending on the row index entered
 
 */
 
 


||||||| .r5268
=======
/*Intro Para:
 Aditya Vikram Gupta
 avgupta3
 February 12 2018
 This program prints a row of the pascal's triangle depending in the row index entered
*/

>>>>>>> .r7326
int main()
{
<<<<<<< .mine
  int row; // declare row
  unsigned long int num;
  printf("Enter a row index : "); //input row index
||||||| .r5268
  int row;

  printf("Enter a row index: ");
=======
  int row; //declare row
  unsigned long num;

  printf("Enter a row index: ");
>>>>>>> .r7326
  scanf("%d",&row);
<<<<<<< .mine
    
    int k;
    int i; //declare loop counter
    
    for (k = 0; k <= row; k++){
        
        num = 1;
        for(i = 1; i<=k ; i++){
        num = num * (row + 1 - i) / i ;
    }
    
    printf(" %lu ", num);
    }
    printf("\n");
    
||||||| .r5268

  // Write your code here

=======

     // Write your code here

>>>>>>> .r7326
  int k; //declare k
  int i; //declare i
 
  for ( k = 0; k<= row; k++) {
     
      num =1;

      for(i=1; i<=k; i++) {
          num = num * (row + 1 - i)/ i ;
     }

   printf(" %lu ", num);

  }
  
  printf("\n");


  return 0;
}
