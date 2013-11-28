#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define MAX 65536

static inline char **resize_array(char **strings, int *max_strings);
char **readline(int *amount)
{
        char **strings = malloc(sizeof(char*));
        int num_strings = 0;
        int max_strings = 1;
        int chars_in_word = 0;
        char last_char = '_'; /* arbitrary */
        char temp_string[MAX];
        int i;

        while (last_char != '\n' && 
               last_char != '\0' && 
               last_char != '\t')
        {
                last_char = getc(stdin);
                if (!isspace(last_char))
                {
                        if (chars_in_word >= MAX - 1)
                        {
                                fprintf(stderr, "input too long! :(\n");
                                exit(1);
                        }
                        temp_string[chars_in_word++] = last_char;
                }
                else 
                {
                        if (num_strings + 1 > max_strings) 
                                strings = resize_array(strings, &max_strings);
                        strings[num_strings] = malloc(sizeof(char) *
                                               chars_in_word);
                        for (i = 0; i < chars_in_word; i++)
                        {
                                strings[num_strings][i] = temp_string[i];
                                temp_string[i] = '\0';
                        }
                        chars_in_word = 0;
                        num_strings++;
                }
        }
        * amount = num_strings;

        return strings;
}

static inline char **resize_array(char **strings, int *max_strings)
{
        (* max_strings) += (* max_strings);
        char **to_return = malloc((* max_strings) * sizeof(char*));
        int i;
        for (i = 0; i < (* max_strings) / 2; i++)
                to_return[i] = strings[i];
        free(strings);
        return to_return;
}

