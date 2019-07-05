#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "cmd_list.h"
#include "parser.h"

mode_map_t g_mode_map[CMD_MODE_MAX] = {
    {CMD_MODE_MAX,     CMD_MODE_ROOT,   "root",          "$", cmd_root},
    {CMD_MODE_ROOT,    CMD_MODE_ENABLE, "config-enable", ">", cmd_enable},
    {CMD_MODE_ENABLE , CMD_MODE_CONFIG, "config-term",   "#", cmd_cfg},
    {CMD_MODE_CONFIG,  CMD_MODE_IF,     "config-if",     "#", cmd_cfg_if},
    {CMD_MODE_CONFIG,  CMD_MODE_MIF,    "config-mif",    "#", cmd_cfg},
    {CMD_MODE_CONFIG , CMD_MODE_NONE,   "config-none",   "#", cmd_cfg},
};

char * getCmdModeStr(cdb_cmd_mode_t mode)
{
    int i = 0;
    for( i = 0 ; i < CMD_MODE_MAX ; i++ )
    {
        if (mode == i)
            return g_mode_map[i].mode_str;
    }
    return "Unknown";
}

char * getCmdModePrompt(cdb_cmd_mode_t mode)
{
    int i = 0;
    for( i = 0 ; i < CMD_MODE_MAX ; i++ )
    {
        if (mode == i)
            return g_mode_map[i].mode_prompt;
    }
    return "*";
}

cdb_cmd_mode_t getCurrCmdMode()
{
    return getCmdModeFromModeStr(g_sptr_cdb.curr_mode_str);
}

cdb_cmd_mode_t getPrevCmdMode(cdb_cmd_mode_t mode)
{
    int i;
    for( i = 0 ; i < CMD_MODE_MAX ; i++ )
    {
        if (g_mode_map[i].mode == mode)
            return g_mode_map[i].prevMode;
    }
    return CMD_MODE_MAX;
}

cdb_cmd_mode_t getCmdModeFromModeStr(char *str)
{
    int i;
    for( i = 0 ; i < CMD_MODE_MAX ; i++ )
    {
        if (0 == strcmp(str, getCmdModeStr(i)))
        {
            return i;
        }
    }
    return CMD_MODE_MAX;
}

void setCmdModeParams(cdb_t *sptr_cdb, cdb_cmd_mode_t mode)
{
	sptr_cdb->mode = mode;
	snprintf(sptr_cdb->curr_mode_str, CMD_LEN, "%s", getCmdModeStr(mode));
	snprintf(sptr_cdb->cmd_prompt,CMD_LEN,"%s",getCmdModePrompt(mode));
}

void cleanUpCdb(cdb_t *sptr_cdb)
{
    snprintf(sptr_cdb->curr_mode_usr_str, CMD_LINE_LEN, "%s", "");
}


cdb_node_t * getCmdNodeFromMode(cdb_cmd_mode_t mode)
{
    int i;
    for( i = 0 ; i < CMD_MODE_MAX ; i++ )
    {
        if (mode == i)
            return g_mode_map[i].modeRootNode;
    }
    return NULL;
}



