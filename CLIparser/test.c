#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "parser.h"

int main()
{
	/*parserCliSrart("Switch");*/
	extern void cmdCLIStart(char *cliHost);
	cmdCLIStart("Switch");
	return 1;
}


