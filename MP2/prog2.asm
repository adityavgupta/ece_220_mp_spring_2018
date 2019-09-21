;Aditya Vikram Gupta
;February 8 2018
;net ID = avgupta3

;This is a stack calculator
;It takes in inputs from 0 through 9 and can perform the following functions:
; + , - , * , / , ^
;It uses stack to evaluate the operation to be executed
;The operations are executed by executing subroutines
;A subroutine is also used for printing the hex value of the number computed

  
.ORIG x3000
	
;your code goes here

      AND   R6,R6,#0
      AND   R1,R1,#0
		
 INPUT   GETC
         OUT
 
      JSR EVALUATE
      BR INPUT



   
;your code goes here
EVALUATE     ST    R7, SAVE_R7
             LD     R1, ASCII_NEG_EQUAL   ; load the 2's complement of the hexadecimal value of "="
             ADD    R1,R1,R0              ; check if the character is "="
             BRz    IS_EQUAL_TO           ; if the character is "=" branch to the label "IS_EQUAL_TO"  
        
             LD     R1, ASCII_NEG_SPACE   ; load the 2's complement of the hexadecimal value of " "
             ADD    R1,R1,R0              ; check if the character is " "
             BRnp   NOT_A_SPACE           ; if the character is not a space then branch to label "Not a space"
             LD     R7, SAVE_R7
             RET

; if the character inputted is not a space then check wether it is valid or not
; the check for validity includes if the character lies within 0 to 9

NOT_A_SPACE   LD   R1, ASCII_NINE
              NOT  R1,R1
              ADD  R1,R1,#1
              ADD  R1,R1,R0   ; check whether the character inputted is less than 9
              BRp NOT_NUM  ; if the character is less than NINE check if it is an operation by going to the label

              LD   R1, ASCII_ZERO
              NOT  R1,R1
              ADD  R1,R1,#1
              ADD  R1,R1,R0   ; check if the character inputted is GREATER THAN ZERO
              BRn  NOT_NUM    ; if the character is LESS than 0 then branch to label "NOT_NUM"
             
	          LD   R1, ASCII_ZERO
              NOT  R1,R1
              ADD  R1,R1,#1
              ADD  R0, R0,R1  ; R0 has the numerical value of the number inputted
              JSR  PUSH
              LD  R7,SAVE_R7
              RET


NOT_NUM       ADD R2, R0, #0
              JSR  POP        ; if the inputted character is an operation then pop the value from stack
              AND  R4,R4,#0
              ADD  R4,R4,R0   ; stores the popped value in R3
              ADD  R5,R5,#-1  ; if the value in R5 is 1 after pop i.e. there is UNDERFLOW           
              BRz  INVALID    ; then go to the label INVALID 

              JSR  POP        ; if the inputted character is an operation then pop the value from stack
              AND  R3,R3,#0
              ADD  R3,R3,R0   ; stores the popped value in R4
              ADD  R5,R5,#-1  ; if the value in R5 is 1 after pop i.e. there is UNDERFLOW           
              BRz  INVALID    ; then go to the label INVALID 
              
; CHECK MULT
              LD   R1, ASCII_NEG_MUL
              ADD  R1,R1,R2           ; check if the opeartion in R0 is multiply
              BRnp CHECK_PLUS         ; if the difference is not zero then go to check for addition
              JSR  MUL                ; if the difference is zero then execute MUL subroutinE
              BR   PUSHVAL


CHECK_PLUS    LD   R1, ASCII_NEG_PLUS
              ADD  R1,R1,R2           ; check if the opeartion in R0 is plus
              BRnp CHECK_MINUS        ; if the difference is not zero then go to check for subtraction
              JSR  PLUS               ; if the difference is zero then execute PLUS subroutine 
              BR   PUSHVAL


CHECK_MINUS   LD   R1, ASCII_NEG_MINUS
              ADD  R1,R1,R2           ; check if the opeartion in R0 is minus
              BRnp CHECK_DIV          ; if the difference is not zero then go to check for division
              JSR  MIN                ; if the difference is zero then execute PLUS subroutine
              BR   PUSHVAL


CHECK_DIV     LD   R1, ASCII_NEG_DIV
              ADD  R1,R1,R2           ; check if the opeartion in R0 is division
              BRnp CHECK_EXP          ; if the difference is not zero then go to check for exponential
              JSR  DIV                ; if the difference is zero then execute DIV subroutine
              BR   PUSHVAL


CHECK_EXP     LD   R1, ASCII_NEG_EXP
              ADD  R1,R1,R2           ; check if the operation in R0 is exp    
              BRnp INVALID            ; if the diiference is not zero then go to invalid
              JSR  EXP 
               
PUSHVAL       ADD R6,R0,#0
			  JSR PUSH
              LD  R7, SAVE_R7
              RET

IS_EQUAL_TO   JSR  POP
              JSR  POP
              ADD  R5,R5,#0
              BRnz INVALID

              ADD R3,R6,#0
	          JSR PRINT_HEX
              BR  DONE
              

INVALID       
              LEA R0,INVAL
              PUTS
              BR  DONE
                     
DONE          HALT        





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX   
            ST   R1, SAVE_PRINT_R1
			ST   R2, SAVE_PRINT_R2
			ST   R3, SAVE_PRINT_R3
			ST   R4, SAVE_PRINT_R4
			ST   R5, SAVE_PRINT_R5
			ST   R7, SAVE_PRINT_R7 


            AND  R1,R1,#0
            ADD  R1,R1,#3 ; Set up counter

GROUP       BRn  RETURN
            
            AND  R5,R5,#0 ;initialize registers
            AND  R0,R0,#0

            AND R4,R4,#0
            ADD R4,R4,#-9
            
            ADD  R3,R3,#0; Check 4th bit
            BRzp NXTBIT3
            ADD  R5,R5,#8

NXTBIT3     ADD  R3,R3,R3 ; left shift to check 3rd bit
            BRzp NXTBIT2
            ADD  R5,R5,#4

NXTBIT2     ADD  R3,R3,R3 ; left shift to check 2nd bit
            BRzp NXTBIT1
            ADD  R5,R5,#2

NXTBIT1     ADD  R3,R3,R3 ; check 1st bit
            BRzp FINAL
            ADD  R5,R5,#1

FINAL       ADD  R4,R4,R5  
            BRn  PRINT_NUM


            LD   R0, CHARACTER 
            ADD  R0,R0,R4 ; store hex value of the character
            BR   PRINT

PRINT_NUM   LD   R0, NUM
            ADD  R0,R0,R5 ; store the hex value of the number

PRINT       OUT

            ADD  R3,R3,R3 ; bitwise shift left
            ADD  R1,R1,#-1
            BR   GROUP


RETURN      LD   R1, SAVE_PRINT_R1
			LD   R2, SAVE_PRINT_R2
			LD   R3, SAVE_PRINT_R3
			LD   R4, SAVE_PRINT_R4
			LD   R5, SAVE_PRINT_R5
			LD   R7, SAVE_PRINT_R7 

            RET

			CHARACTER   	.FILL x40
			NUM         	.FILL x30
			SAVE_PRINT_R1	.FILL x0
			SAVE_PRINT_R2	.FILL x0
			SAVE_PRINT_R3	.FILL x0
			SAVE_PRINT_R4	.FILL x0
			SAVE_PRINT_R5	.FILL x0
			SAVE_PRINT_R7	.FILL x0
              
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

PLUS       ST R7, SAVE_PLUS_R7
	
;your code goes here

              ADD  R0,R3,R4
              LD   R7, SAVE_PLUS_R7
              RET
              
 SAVE_PLUS_R7 .FILL x0                  
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
              ST   R7, SAVE_MIN_R7
              ST   R4,SAVE_MIN_R4
              AND  R0,R0,#0
              NOT  R4,R4
              ADD  R4,R4,#1
              ADD  R0,R3,R4
              LD   R4,SAVE_MIN_R4
              LD   R7, SAVE_MIN_R7
              RET

    SAVE_MIN_R7      .FILL x0                  
	SAVE_MIN_R4      .FILL x0000
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4              ;R3*R4
;out R0
MUL	
;your code goes here
             ST R7, MULT_SAVE_R7
             ST R5, MULT_SAVE_R5

             AND R0,R0,#0
             ADD R5,R4,#0        ;  Set  R5=R4, if R5=0 then done
             BRz MUL_DONE

             BRp MULOOP
             NOT R5,R5
             ADD R5,R5,#1

MULOOP       ADD R0,R0,R3        ; Add R3 to total in R0
             ADD R5,R5,#-1       ; Decrement counter
             BRp MULOOP

             ADD  R4,R4,#0       ; If R4 was originally negative
             BRzp MUL_DONE       ; then complement the final answer, else done
             NOT  R0,R0
             ADD  R0,R0,#1

MUL_DONE     LD R7, MULT_SAVE_R7
             LD R5, MULT_SAVE_R5
             RET
 MULT_SAVE_R7  .FILL x0
 MULT_SAVE_R5  .FILL x0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
            ST R3,  DIV_SAVE_R3
            ST R4,  DIV_SAVE_R4
            ST R7,  DIV_SAVE_R7
            NOT R4,R4
            ADD R4,R4,#1  ;-R4
            AND R0,R0,#0
DIVLOOP     ADD R0,R0,#1
            ADD R3,R3,R4  ; adding -R4 each time
            BRzp DIVLOOP  ; if +, keep dividing

            ADD R0,R0,#-1 ; if negative subtract 1 from quotient for going one extra step

            LD R3,  DIV_SAVE_R3
            LD R4,  DIV_SAVE_R4
            LD R7,  DIV_SAVE_R7
            RET

DIV_SAVE_R3   .FILL x0000
DIV_SAVE_R4   .FILL x0000
DIV_SAVE_R7   .FILL x0000

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4    (R3^R4)
;out R0
EXP
;your code goes here
             ST  R7, EXP_SAVE_R7
             ST  R5, EXP_SAVE_R5
             ST  R4, EXP_SAVE_R4

             ADD R4,R4,#0      ; check if exponent is 0
             BRz EXP_IS_ZERO
            
             ADD R5,R4,#-1     ; check if exp is 1
             BRz EXP_IS_ONE
            
             ADD R4,R3,#0      ; Set R4 equal to R3

EXPLOOP      JSR MUL           ; Multiply R3*R4
             ADD R4,R0,#0      ; Set R4 equal to the answer from multiplication
             ADD R5,R5,#-1     ; Decrement power counter
             BRp EXPLOOP       ; Loop until counter is 0
             BR  EXP_IS_DONE   ; Loop until counter is 0
                 
EXP_IS_ZERO  AND R0,R0,#0  
             ADD R0,R0,#1
             BR  EXP_IS_DONE

EXP_IS_ONE
             ADD R0,R0,R3

EXP_IS_DONE   LD  R7, EXP_SAVE_R7
              LD  R5, EXP_SAVE_R5
              LD  R4, EXP_SAVE_R4
              RET

 EXP_SAVE_R7   .FILL x0000
 EXP_SAVE_R5   .FILL x0000
 EXP_SAVE_R4   .FILL x0000

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	 .BLKW #1	;
POP_SaveR4	 .BLKW #1	;
STACK_END	 .FILL x3FF0	;
STACK_START      .FILL x4000	;
STACK_TOP	 .FILL x4000	;
SAVE_R7          .FILL x0000    ;

ASCIIA           .FILL x37
ASCII_ZERO       .FILL x0030
ASCII_NEG_EQUAL  .FILL #-61  ; 2's complement of the character "="
ASCII_NEG_SPACE  .FILL xFFE0  ; 2's complement of the character "(space) "
ASCII_NINE       .FILL x0039
ASCII_NEG_MUL    .FILL xFFD6  ; 2's complement of the character "*"
ASCII_NEG_PLUS   .FILL xFFD5  ; 2's complement of the character "+"
ASCII_NEG_MINUS  .FILL xFFD3  ; 2's complement of the character "-"
ASCII_NEG_DIV    .FILL xFFD1  ; 2's complement of the character "/"
ASCII_NEG_EXP    .FILL xFFA2  ; 2's complement of the cgaracter "^"
INVAL            .STRINGZ "Invalid Expression"

.END

