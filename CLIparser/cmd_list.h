#include <stdio.h>
#include <stdlib.h>


#ifndef __CMD_LIST_H__
#define __CMD_LIST_H__

/*
 * NODEs
 */
extern cdb_node_t cmd_root[];
extern cdb_node_t cmd_enable[];
extern cdb_node_t cmd_cfg_terminal[];
extern cdb_node_t cmd_cfg_if[];
extern cdb_node_t cfg_if_type[];
extern cdb_node_t cfg_if_list[];
extern cdb_node_t cmd_cfg[];
extern cdb_node_t cmd_show[];
/*
 * NODE call backs
 */
void enable_config_terminal(cdb_t *sptr_cdb);
void cmd_show_version(cdb_t *sptr_cdb);
void cmd_show_configurations(cdb_t *sptr_cdb);
void cmd_show_global_config_ver(cdb_t *sptr_cdb);
void enable_cmd_prompt(cdb_t *sptr_cdb);
void config_interface(cdb_t *sptr_cdb);
void config_if_type_enet(cdb_t *sptr_cdb);
void config_if_type_mgmt(cdb_t *sptr_cdb);
void config_if_list(cdb_t *sptr_cdb);
void config_if_enable(cdb_t *sptr_cdb);
void config_if_disable(cdb_t *sptr_cdb);
#endif /*__CMD_LIST_H__*/
