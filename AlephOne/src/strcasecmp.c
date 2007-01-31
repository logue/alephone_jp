
#include <string.h>
#include <ctype.h>

#include "strcasecmp.h"

int strcasecmp(const char *s1, const char *s2)
{
    int i;
    if (strlen (s1) != strlen (s1))
	return (1);
    for (i = 0; i < strlen (s1); i++)
	if (toupper (s1[i]) != toupper (s2[i]))
	    return (1);
    return (0);
}
