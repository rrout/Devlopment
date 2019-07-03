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

}


