#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list-utils-private.h"
/* Function that checks if a string is present in an array of strings.
* returns 1 if array contains item, 0 if not, -1 if error.
*/
int contains(char** array, char* item, int size) {
    if (array == NULL || size < 0)
        return -1;
    if (size == 0) 
        return 0;
    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(array[i], item) == 0)
            return 1;
    }
    return 0;
}