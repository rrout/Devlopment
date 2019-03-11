#include <stdio.h>
#include <stdlib.h>


#ifndef __PARSER_H__
#define __PARSER_H__

#include "cmd.h"

typedef enum {
	FALSE = 0,
	TRUE  = 1,
}bool;

void parser(cdb_t *cur_sptr_cdb, char *cmdline);
void parserInit(char *cliHost, cdb_t *sptr_cdb);
void parserCliSrart(char *cliHost);
cdb_node_t * getCdbNode(char *);

#endif /*__PARSER_H__*/
