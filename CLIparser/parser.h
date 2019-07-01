#include <stdio.h>
#include <stdlib.h>


#ifndef __PARSER_H__
#define __PARSER_H__

#include "cmd.h"

typedef enum {
	FALSE = 0,
	TRUE  = 1,
}bool;

#define CMD_MAX_TOKEN       20
#define CMD_MAX_TOKEN_LEN   50

void parser(cdb_t *cur_sptr_cdb, char *cmdline);
void parserInit(char *cliHost, cdb_t *sptr_cdb);
void parserCliSrart(char *cliHost);
cdb_node_t * getCdbNode(char *);
cdb_node_t * getCdbNextNode(char *);
cdb_node_t * getCdbExecCli(char *cmdline);

extern cdb_t g_sptr_cdb;
#endif /*__PARSER_H__*/
