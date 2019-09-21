;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here
; Aditya Vikram Gupta
; January 25th, 2018
; ECE 220, BD2
; The idea is to divide 16 binary bits into 4 groups of 4 binary bits
; For each group shift the bits to the left and convert the group into a single digit hexadecimal bit by adding the hexadecimal representation of each bit together
; If the digit is more than 9 print out the corresponding alphabets from the chart
; If the digit is less than or equal to 9 print out the digit
; R0 holds the character to be printed out using the OUT trap instruction
; R1 is used as a pointer to the start of the histogram
; R2 is used as counter for bins remaining (loop counter)
; R3 holds the count for the current bin
; R4 is loadded with the value "-9" so as to later use it to distinguish between printing a number or a character
; R5 is the sum of 4 bits which make a single digit(number or character)
; R6 is first used as the "GROUP" counter and later as a temporary register


        LD  R1, HIST_ADDR ; POINT R1 TO START OF THE HISTOGEAM
        AND R2,R2,#0      ; INITIALIZE LOOP COUNT TO 0
BIN_LOOP
        LDR R3,R1,#0      ; GET COUNT FOR THIS BIN

        LD  R0,ASC_LTR    ; PRINT THE BIN NAME
        ADD R0,R0,R2
        OUT
        LD  R0, ASC_SPACE ; PRINT A SPACE
        OUT

  ;start of the code that prints as a hexadecimal

        AND R6,R6, #0     ; 
        ADD R6,R6, #3     ; ADD 3 TO R6
GROUP   BRn FINAL_STAGE
        
        AND R5,R5,#0      ; CLEAR R5
        AND R0,R0,#0      ; CLEAR R0
        
        AND R4,R4,#0      ; ADD THE NUMER "-9"
        ADD R4,R4,#-9

        ADD R3,R3,#0      ; CHECK THE LEFTMOST BIT
        BRzp NXTBIT3      ; IF ZERO OR POSITIVE BRANCH TO LABEL "NXTBIT3"
        ADD R5,R5,#8      ; IF NEGATIVE THEN ADD THE VALUE 8 TO R5

NXTBIT3 ADD R3,R3,R3      ; LEFT SHIFT TO CHECK THE 2ND MOST SIGNIFICANT BIT
        BRzp NXTBIT2      ; IF ZERO OR POSITIVE BRANCH TO LABEL "NXTBIT2"
        ADD R5,R5,#4      ; IF NEGATIVE THEN ADD VALUE 4 TO R5

NXTBIT2 ADD R3,R3,R3      ; LEFT SHIFT
        BRzp NXTBIT1      ; IF ZERO OR POSITIVE BRANCH TO LABEL "NXTBIT2"
        ADD R5,R5,#2      ; IF NEGATIVE ADD THE VALUE 2 TO R5

NXTBIT1 ADD R3,R3,R3      ; LEFT SHIFT
        BRzp FINAL        ; IF ZERO OR POSITIVE BRANCH TO LABEL "FINAL"
        ADD R5,R5,#1      ; ADD VALUE 1 TO R5

FINAL   ADD R4,R4,R5      ; SUM OF R4(-9) AND THE VALUE stored in R5 SO AS TO DISTINGUISH BETWEEN NUMBER OR CHARACTER
        BRnz PRINT_NUM    ; IF SUM IS NEGATIVE OR ZERO BRANCH TO LABEL "PRINT_NUM"
        LD  R0, ASC_LTR   ; LOAD R0 WITH THE VALUE STORED IN "ASC_LTR"
        ADD R0,R0,R4      ; ADD THE VALUE OF R4 TO GET THE REQUIRED CHARACTER
        BR PRINT

PRINT_NUM
        LD R0,ASC_ZERO    ; LOAD R0 WITH THE VALUE STORED IN "ASC_ZERO"
        ADD R0,R0,R5      ; ADD THE VALUE IN R5 TO R0
PRINT   OUT

        ADD R3,R3,R3
        ADD R6,R6,#-1
        BR  GROUP

FINAL_STAGE
        LD R0,ASC_NL     ; PRINT NEW LINE
        OUT

        ADD R1,R1,#1     ; INCREMENT HISTOGRAM POINTER BY 1
        ADD R2,R2,#1     ; INCREMENT LOOP COUNT

        LD  R6,NUM_BINS  ; LOAD R6 WITH 27 
        NOT R6,R6        ;
        ADD R6,R6,#1     ; R6 <- -27
        ADD R6,R6,R2     ; SUBTRACT VALUE IN R2 FROM R6 TO CHECK IF LOOP COUNT IS FINISHED
   
        BRn BIN_LOOP  

     
            
DONE	   HALT			; done

; THE DATA FOR PRINTING HEX VALUES

ASC_LTR      .FILL x0040
ASC_SPACE    .FILL x0020
ASC_NL       .FILL x000A
ASC_ZERO     .FILL x0030


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
