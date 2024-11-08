
/* bierz symbole po kolei
*  1. liczba
*     odloz na stos
*  2. operator
*     zdejmi ze stosu elem a
*     zdejmij ze stosu elem b
*     odloz na stos wartosc b op a
*
*  mozliwe tokeny: 
*  liczba: calkowita, moze byc ujemna, moze miec kilka cyfr
*  operator: dodawanie, odejmowanie, mnozenie, dzielenie, potegowanie, modulo
* 
*  mozliwe bledy:
*    dizelenie przez zero
*    za mala liczba argumentow
*    za mala liczba operatorow
*    zly symbol
*
*/

%{

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define STACK_SIZE 128

int error = 0;

int16_t* stack = NULL;
int16_t* top = NULL;

void push(int16_t num) {
    if ( top >= stack + STACK_SIZE ) {
        printf("Stack overflow! :(\n");
        exit(EXIT_FAILURE);
    } else {
        *top = num;
        top++;
    }
}

int16_t pop(void) {
    if ( top == stack ) {
        printf("Error: not enough arguments!\n");
        error = 1;
        return 0;
    } else {
        top--;
        return *top;
    }
}

void reset_error(void) {
     printf("Resetting state\n");
    top = stack;
    error = 0;
}

%}

%x ERROR_HANDLER

%%

<INITIAL>{
        
        -?[[:digit:]]+    { int16_t num = (int16_t)strtol(yytext, NULL, 10); 
                            push(num);
                          }

        "+"               { int16_t a = pop(); 
                            int16_t b = pop();
                            if ( error ) {
                                reset_error(); BEGIN(ERROR_HANDLER); 
                            } else { 
                                push(b + a);
                            } 
                          }

        "-"               { int16_t a = pop(); 
                            int16_t b = pop(); 
                            if ( error ) {
                                reset_error(); BEGIN(ERROR_HANDLER); 
                            } else { 
                                push(b - a);
                            }
                          }

        "*"               { int16_t a = pop(); 
                            int16_t b = pop(); 
                            if ( error ) {
                                reset_error(); BEGIN(ERROR_HANDLER); 
                            } else { 
                                push(b * a);
                            }
                          }

        "/"               { int16_t a = pop(); 
                            if ( a == 0 ) {
                                printf("Error: can't divide by zero!\n");
                                reset_error(); BEGIN(ERROR_HANDLER);
                            } else {
                                int16_t b = pop();
                                if ( error ) {
                                    reset_error(); BEGIN(ERROR_HANDLER); 
                                } else { 
                                    push(b / a);
                                }
                            }
                          }

        "^"               { int16_t a = pop(); 
                            int16_t b = pop();
                            if ( error ) {
                                reset_error(); BEGIN(ERROR_HANDLER); 
                            } else { 
                                push((uint16_t)pow((double)b, (double)a)); 
                            }
                          }

        "%"               { int16_t a = pop(); 
                            int16_t b = pop(); 
                            if ( error ) {
                                reset_error(); BEGIN(ERROR_HANDLER);
                            } else { 
                                push(b % a); 
                            }
                          }

        \n                { if ( top > stack + 1 ) {
                                printf("Error: not enough operators!\n");
                                reset_error(); BEGIN(INITIAL);
                            } else {
                                int16_t num = pop();
                                if ( error ) {
                                    reset_error(); BEGIN(INITIAL);
                                } else { 
                                    printf("= %" PRId16 "\n\n", num);
                                }
                            }
                          }

        [ ]+               {}

        .                 { printf("Error: unexpected symbol %s\n\n", yytext);
                            reset_error();
                            BEGIN(ERROR_HANDLER); 
                          }
}

<ERROR_HANDLER>{
        "\n"              { BEGIN(INITIAL);}
        .                 {  }                
}

%%
int main() {

    stack = (int16_t*)malloc(STACK_SIZE * sizeof(int16_t));
    if ( !stack ) {
        printf("Couldn't allocate memory! :(\n");
        exit(1);
    }

    top = stack;

    yylex();

    free(stack);
    top = NULL;

    return 0;
}
