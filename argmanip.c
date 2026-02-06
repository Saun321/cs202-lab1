#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>  
#include <ctype.h>
#include "argmanip.h"

char **manipulate_args(int argc, const char *const *argv, int (*const manip)(int)) {
    
    //Allocate pointer array (argc + 1 to add NULL at end)
    char **result;
    result = malloc((argc + 1) * sizeof(char *));
    
    //Loop through each argument
    int i;
    for (i = 0; i < argc; i++) {
        
        //Get length of current string argument````
        int len;
        len = strlen(argv[i]);
        
        //Allocate memory for this string (len + 1 to add '\0' at end)
        result[i] = malloc((len + 1) * sizeof(char));
        
        //Copy each character with manip
        int j;
        for (j = 0; j < len; j++) {
            result[i][j] = manip(argv[i][j]);
        }
        
        //Add null terminator
        result[i][len] = '\0';
    }
    
    //Mark end with NULL
    result[argc] = NULL;
    
    return result;
}

void free_copied_args(char **args, ...) {
// Create and place bookmark
    va_list reader;
    va_start(reader, args);
    
    // Start with first argument (upper)
    char **current = args;

    while (current != NULL) {
        
        // Free each string
        int i;
        i = 0;
        while (current[i] != NULL) {
            free(current[i]);
            i = i + 1;
        }
        
        // Free the array itself
        free(current);
        
        // Get next argument (lower, then NULL)
        current = va_arg(reader, char **);
    }
    
    va_end(reader);
}    