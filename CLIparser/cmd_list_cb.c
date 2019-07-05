#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "cmd.h"

void enable_config_terminal(cdb_t *sptr_cdb)
{
    setCmdModeParams(sptr_cdb, CMD_MODE_CONFIG);
}
void cmd_show_version(cdb_t *sptr_cdb)
{
    if (sptr_cdb->last_cmd_token == 0)
        return;
    printf ("CLI Parser V.0.01\n");
}
void cmd_show_configurations(cdb_t *sptr_cdb)
{
    if (sptr_cdb->last_cmd_token == 0)
        return;
    printf ("====== Current Saved Configuration ========\n");
}
void cmd_show_global_config_ver(cdb_t *sptr_cdb)
{
    if (sptr_cdb->last_cmd_token == 0)
        return;
    printf ("====== Current Global Config List ========\n");
    printf ("\n");
}

void enable_cmd_prompt(cdb_t *sptr_cdb)
{
    setCmdModeParams(sptr_cdb, CMD_MODE_ENABLE);
}

void config_interface(cdb_t *sptr_cdb)
{
    setCmdModeParams(sptr_cdb, CMD_MODE_IF);
}

void config_if_type_enet(cdb_t *sptr_cdb)
{
    sptr_cdb->if_type =  IF_TYPE_ETH;
}

void config_if_type_mgmt(cdb_t *sptr_cdb)
{
    sptr_cdb->if_type =  IF_TYPE_MGMT;
}

void config_if_list(cdb_t *sptr_cdb)
{
    if (sptr_cdb->last_cmd_token == 0)
        return;
    char str[255] = {0};
    char type_char = ' ';
    if (sptr_cdb->if_type == IF_TYPE_ETH)
        type_char = 'e';
    if (sptr_cdb->if_type == IF_TYPE_MGMT)
        type_char = 'm';
    extern bool ifMapToIfLine(unsigned int *if_map, char *ifLine);
    ifMapToIfLine(&sptr_cdb->if_map, str);
    printf ("Configuring if: %x(%s)---%s\n", sptr_cdb->if_map, sptr_cdb->if_str, str);
    sprintf(sptr_cdb->curr_mode_usr_str, "(%c-%s)", type_char, str);
}
void config_if_enable(cdb_t *sptr_cdb)
{
    if (sptr_cdb->last_cmd_token == 0)
        return;
}

void config_if_disable(cdb_t *sptr_cdb)
{
    if (sptr_cdb->last_cmd_token == 0)
        return;
}


