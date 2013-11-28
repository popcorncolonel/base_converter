#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "readline.h"
#include "parser.h"

#define MAX 1024


void read_bases(int *to_base, int *from_base)
{
        FILE *output = stdout;
        fprintf(output, "Type \"!quit\" at any point to exit.\n");
        fprintf(output, "0 < base <= 62\n");
        fprintf(output, "Notation: 0<1< ... <9<A<B< ... <Z<a<b< ... <z\n");

        fprintf(output, "Convert from base... ");
        assert(fscanf(stdin, "%d", from_base) == 1);
        assert(* from_base > 0 && * from_base < 63);

        fprintf(output, "to base... ");
        assert(fscanf(stdin, "%d", to_base) == 1);
        assert(* to_base > 0 && * to_base < 63);
}

int calculate_input(int base)
{
        int dec = 0;
        int *num_strings = malloc(4);
        char **cmds = readline(num_strings);

        /* just converting one int from b1 -> b2 */
        if (* num_strings == 1)
        {
                char *old_base_str = cmds[0];
                if (!(old_base_str != NULL &&
                             old_base_str[0] != '!' && old_base_str[1] != 'q'))
                {
                        int i;
                        for (i = 0; i < * num_strings; i++) free(cmds[i]);
                        free(cmds);
                        free(num_strings);
                        exit(0);
                }
                dec = n_to_dec(old_base_str, base);
                if (* old_base_str == '-')
                        dec *= -1;
        }
        else if (* num_strings > 1)
        {
                fprintf(stderr, "sorry, working on doing a calculator now!\n");
                fprintf(stderr, "here are your strings though: \n");
                int i;
                for (i = 0; i < * num_strings; i++) fprintf(stderr, "%s ", cmds[i]);
                /* calc module has a stack maybe? or does THIS have a stack? */
                /* incorporate the calculator module here */
        }
        int i;
        for (i = 0; i < * num_strings; i++) free(cmds[i]);
        free(cmds);
        free(num_strings);
        return dec;
}

int n_to_dec(char *old_base_str, int from_base)
{
        if (* old_base_str == '-') old_base_str = old_base_str + 1;
        int sum = 0, offset = 1;
        int i = 0;
        /* find the last char */
        for (;i < MAX && old_base_str[i] != '\0' && old_base_str[i] != '\n'; 
             i++);
        while (i != 0)
        {
                i--;
                if (old_base_str[i] >= 'a')
                {
                        if (old_base_str[i] - 'a' + 36 >= from_base)
                        {
                                fprintf(stderr, 
                                        "letter '%c' too large for base %d!",
                                        old_base_str[i], from_base);
                                exit(1);
                        }
                        sum += offset * (old_base_str[i] - 'a' + 36);
                }
                else if (old_base_str[i] >= 'A')
                {
                        if (old_base_str[i] - 'A' + 10 >= from_base)
                        {
                                fprintf(stderr, 
                                        "letter '%c' too large for base %d!",
                                        old_base_str[i], from_base);
                                exit(1);
                        }
                        sum += offset * (old_base_str[i] - 'A' + 10);
                }
                else if (old_base_str[i] - '0' < from_base)
                {
                        sum += offset * (old_base_str[i] - '0');
                }
                else
                {
                        fprintf(stderr, 
                                "letter '%c' too large for base %d!",
                                old_base_str[i], from_base);
                        exit(1);
                }
                offset *= from_base;
        }
        return sum;
}


