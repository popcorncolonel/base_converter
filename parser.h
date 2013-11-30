/*
 * Reads in the bases to be used in calculation
 */
void read_bases(int *to_base, int *from_base);

/*
 * Converts an integer (in string form) from base from_base to decimal
 */
int n_to_dec(char *old_base_str, int from_base);

/* 
 * Reads an int from stdin in base base, returns its decimal form
 *
 * exits if "!q" or "!quit" is input 
 */
int calculate_input(int base);

/*
 * Defines a syntax error with the bad string given. exits the program.
 */
void syntax_error(char *bad_string);
