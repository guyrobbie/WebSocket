#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(char *msg)
{
	printf("Error: ");
    perror(msg);
    exit(0);
}