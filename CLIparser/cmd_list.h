#include <stdio.h>
#include <stdlib.h>


#ifndef __CMD_LIST_H__
#define __CMD_LIST_H__

void enable_config_terminal(cdb_t *sptr_cdb);
void cmd_show_version(cdb_t *sptr_cdb);
void cmd_show_configurations(cdb_t *sptr_cdb);
void enable_cmd_prompt(cdb_t *sptr_cdb);
#endif /*__CMD_LIST_H__*/
