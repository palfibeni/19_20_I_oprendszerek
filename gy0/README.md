Órán felmerült kérdések:

- char * -> points to a character in the memory, there could be more beind, which results in string, or char array
- char ** -> points to a string or char array, there could be more, results in string array.
- gcc filename -> builds the C filename results in a.out filename
- ./a.out argument1 argument2 etc... -> runs the program with given arguments (first parameter is always the name of the file)
- atoi -> converts to int
- there is no String in C, only char[]
- printf with \n ensures that the puffer gets emptied.
- malloc(size) allocates memory for the given size ex.: malloc(80*sizeof(char))
- strcmp(str1, str2) -> find difference between two string, returns 0 if the same