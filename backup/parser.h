/*
 * Reads in the bases to be used in calculation
 */
void read_bases(int *to_base, int *from_base);

/* 
 * Reads an int from stdin in base base, returns its decimal form
 *
 * exits if "!q" or "!quit" is input 
 */
int calculate_input(int base);
