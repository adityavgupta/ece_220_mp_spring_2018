#include <stdlib.h>
#include <stdio.h>

/* Aditya Vikram Gupta
   avgupta3
   ECE 220 BD2
 
 This is a program that prints out the semi-primes in [a, b].
 A semiprime is a positive integer that is a product of two prime numbers (the prime numbers can be identical).
 Two functions are implemented namely :
 -> int is_prime(int number): this function checks whether the input number is a prime number or not and returns 1 if the number is a prime number, otherwise 0.
 ->int print_semiprimes(int a, int b): this function prints all the semiprimes in [a,b] and returns 0 if there is no semiprime within the range, otherwise 1.
 */


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
    print_semiprimes(a, b);

}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number) {
    if (number == 1){
        return 0;
        }
    /*
     This loop increments from 2 to the number, and decides the number is not prime
     if the number in question is divisible by any of the looped numbers.
     */

    for (int i=2; i < number; i++) {
        if ((number % i) == 0) {
 		   return 0;
		}
    }
	return 1;
}

/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)

{       int answer = 0;
    
    /*
     This loop increments by 1, starts at the first number, and ends at the last one.
     */
		for (int n = a; n<= b; n++){
            /*
             This loop increments by 1, starting at 2 and ending at the current number(i) minus 1.
             For each number between those 2 bounds (inclusive) it checks if the if the number is a
             semiprime using the current looped number.
             */
		
			for (int k = 2; k <= n - 1; k++){

				if ((is_prime(k) == 1) && ((n % k) == 0) && (is_prime(n / k) == 1) ){ 
				printf("%d ", n);
                    answer = 1;
                    break;
				
			}
		}
			
	}
    return answer;
}


