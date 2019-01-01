#include <stdio.h>
#include <stdlib.h>


#ifndef __PARSER_H__
#define __PARSER_H__

#include "cmd.h"

void parser(cdb_t *cur_sptr_cdb, char *cmdline);
void parserInit(char *cliHost, cdb_t *sptr_cdb);
void parserCliSrart(char *cliHost);

#endif /*__PARSER_H__*/
