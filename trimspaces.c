
#include "trimspaces.h"



void trim_whitespace(char *str) {
    size_t len = strlen(str);

    // Trim leading whitespace
    size_t start = 0;
    while (isspace(str[start])) {
        start++;
    }

    // Trim trailing whitespace
    size_t end = len - 1;
    while (end > start && isspace(str[end])) {
        end--;
    }

    // Shift the non-whitespace part to the beginning of the string
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

