#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "cmd_list.h"
#include "parser.h"

unsigned int g_cli_dbg = 1;

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

bool cmdNodeInsertCbStack(cdb_cb_stack_t *cbStack, cdb_node_t *node, bool last_node)
{
    int nodeNum = 0;
    if (!cbStack || !node || cbStack->numNodes > CMD_MAX_TOKEN)
        return FALSE;

    nodeNum = cbStack->numNodes;
    strcpy(cbStack->cb[nodeNum].cmd, node->cmd);
    cbStack->cb[nodeNum].cmd_callback = node->cmd_callback;
    if (last_node == TRUE)
        cbStack->cb[nodeNum].last_node = TRUE;
    cbStack->numNodes++;

    return TRUE;
}

bool cmdCheckBuildCallBackStack(int is_full_cmd, cdb_node_t *node, cdb_cb_stack_t *cbStack)
{
    if (node)
    {
       if (is_full_cmd)
       {
           if (!(node->flags & CMD_FLAG_CR_ALLOWED)) {
               printf("Incomplete command !\n");
               return FALSE;
            } else {
                cmdNodeInsertCbStack(cbStack, node, is_full_cmd);
           }
       } else {
           cmdNodeInsertCbStack(cbStack, node, is_full_cmd);
       }
    }
    else
    {
        printf("Invalid command node!\n");
    }
    return TRUE;
}

void cmdPrintCbStack(cdb_cb_stack_t *cbStack)
{
    int i = 0;
    for( i = 0 ; i < cbStack->numNodes ; i++ )
    {
        dprintf(CMD_DBG_LEVEL_ALL,
            ("Cmd:%s Callback:%p\n",cbStack->cb[i].cmd, cbStack->cb[i].cmd_callback));
    }
}

void cmdExecCbStack(cdb_cb_stack_t *cbStack, cdb_t *sptr_cdb)
{
    int i = 0;
    for( i = cbStack->numNodes ; i > 0 ; i-- )
    {
        if (cbStack->cb[i-1].cmd_callback) {
            sptr_cdb->last_cmd_token = cbStack->cb[i-1].last_node;
            cbStack->cb[i-1].cmd_callback(sptr_cdb);
            sptr_cdb->last_cmd_token = FALSE;
        }
    }
}
