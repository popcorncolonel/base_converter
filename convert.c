/*
 * MAIN FILE - Everything branches out from here 
 *
 * Written by Eric Bailey
 * Fall 2013
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "readline.h"
#include "parser.h"
#include "calculator.h"

#define MAX 1024

/* TODO: 
 *       fix arbirarity of MAX and reading strings
 *       parsing these strings and using the +, -, etc. to do calcs
 *              commands to add: +*-/^!
 *
 *       ...
 *
 *       online support :)
 */

FILE *output = NULL;

void print_in_new_base(int dec, int to_base);
void print_backwards(char *to_print, int len);

int main(int argc, char *argv[])
{
        output = stdout;
        int to_base, from_base;
        if (argc > 5 && argc % 2 == 1)
        {
                fprintf(stderr, "Bad arguments! Usage: ./convert_base ");
                fprintf(stderr, "[<from_base> <to_base> <operation>]\n");
                exit(1);
        }
        if (argc == 1)
        {
                read_bases(&to_base, &from_base);

                while (1)
                {
                        print_in_new_base(calculate_input(from_base), to_base);
                        fprintf(output, "Write a calculation in base %d to convert \
to base %d... ", 
                                        from_base, to_base);
                }
        }
        else
        {
                from_base = atoi(argv[1]);
                to_base = atoi(argv[2]);
                int answer = 0;

                if (argc == 3) answer = n_to_dec(argv[3], from_base);
                if (argc > 3) {
                        answer = calculate(&argv[3], argc - 3, from_base);
                }

                print_in_new_base(answer, to_base);
        }
        return 0;
}
void print_in_new_base(int dec, int to_base)
{
        char to_print[MAX];
        int i = 0;
        int remainder = 0;
        int is_neg = 0;
        if (dec < 0)
        {
                is_neg = 1;
                dec *= -1;
        }
        while (dec != 0)
        {
                remainder = dec % to_base;
                if (remainder >= 36)
                {
                        to_print[i++] = 'a' + remainder - 36;
                }
                else if (remainder >= 10)
                {
                        to_print[i++] = 'A' + remainder - 10;
                }
                else {
                        to_print[i++] = '0' + remainder;
                }
                dec = dec / to_base;
        }
        if (is_neg) fprintf(output, "-");
        print_backwards(to_print, i - 1);
}

void print_backwards(char *to_print, int len)
{
        int j;
        for (j = len; j >= 0 && to_print[j] != '\0'; j--) 
        {
                fprintf(output, "%c", to_print[j]);
        }
        fprintf(output, "\n");
}


