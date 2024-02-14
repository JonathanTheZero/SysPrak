#include "pipe.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void toUpperChar(char *source, char *dest)
{
    for (int i = 0; i < strlen(source); ++i)
    {
        dest[i] = (char)toupper((unsigned)source[i]);
    }
}