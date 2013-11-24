#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "readline.h"
#include "convert.h"

#define MAX 1024

/* TODO: 
 *       fix arbirarity of MAX and reading strings
 *       reading strings, ignoring whitespace
 *       parsing these strings and using the +, -, etc. to do calcs
 *              commands to add: +*-/^!
 *
 *       ...
 *
 *       online support :)
 */

void print_backwards(char *to_print, int len);
void read_bases(int *to_base, int *from_base);
int read_int(int base);

int main()
{
        int to_base, from_base;
        char old_base[MAX];
        /*
        char **temp = readline();
        int i;
        fprintf(stdout, "strings: \n");
        for(i = 0; i < 5; i++)
                fprintf(stdout, "%s\n", temp[i]);
        free(temp);
        */

        read_bases(&to_base, &from_base);

        fprintf(stdout, "Write a number in base %d to convert to base %d... ",
                from_base, to_base);

        int dec = 0;
        while (fscanf(stdin, "%s", old_base) == 1 && 
               strcmp(old_base, "quit") != 0) /* cannot use 'quit' it is a valid num */
        {
                dec = n_to_dec(old_base, from_base);
                if (* old_base == '-')
                        dec *= -1;
                print_in_new_base(dec, to_base);
                fprintf(stdout, 
                        "Write a number in base %d to convert to base %d... ", 
                        from_base, to_base);
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
        if (is_neg) fprintf(stdout, "-");
        print_backwards(to_print, i - 1);
}

void read_bases(int *to_base, int *from_base)
{
        fprintf(stdout, "Type \"quit\" at any point to exit.\n");
        fprintf(stdout, "0 < base <= 62\n");
        fprintf(stdout, "Notation: 0<1< ... <9<A<B< ... <Z<a<b< ... <z\n");

        fprintf(stdout, "Convert from base... ");
        assert(fscanf(stdin, "%d", from_base) == 1);
        assert(* from_base > 0 && * from_base < 63);

        fprintf(stdout, "to base... ");
        assert(fscanf(stdin, "%d", to_base) == 1);
        assert(* to_base > 0 && * to_base < 63);
}

int n_to_dec(char *old_base, int from_base)
{
        if (* old_base == '-') old_base = old_base + 1;
        int sum = 0, offset = 1;
        int i;
        for (i = 0; i < MAX && old_base[i] != '\0' && old_base[i] != '\n'; i++);
        while (i != 0)
        {
                i--;
                if (old_base[i] >= 'a')
                {
                        if (old_base[i] - 'a' + 36 >= from_base)
                        {
                                fprintf(stderr, 
                                        "letter '%c' too large for base %d!",
                                        old_base[i], from_base);
                                exit(1);
                        }
                        sum += offset * (old_base[i] - 'a' + 36);
                }
                else if (old_base[i] >= 'A')
                {
                        if (old_base[i] - 'A' + 10 >= from_base)
                        {
                                fprintf(stderr, 
                                        "letter '%c' too large for base %d!",
                                        old_base[i], from_base);
                                exit(1);
                        }
                        sum += offset * (old_base[i] - 'A' + 10);
                }
                else if (old_base[i] - '0' < from_base)
                {
                        sum += offset * (old_base[i] - '0');
                }
                else
                {
                        fprintf(stderr, 
                                "letter '%c' too large for base %d!",
                                old_base[i], from_base);
                        exit(1);
                }
                offset *= from_base;
        }
        return sum;
}

void print_backwards(char *to_print, int len)
{
        FILE *out = stdout;
        int j;
        for (j = len; j >= 0 && to_print[j] != '\0'; j--) 
        {
                fprintf(out, "%c", to_print[j]);
        }
        fprintf(out, "\n");
}

