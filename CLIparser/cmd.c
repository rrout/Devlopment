#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "cmd_list.h"

char * getCmdModeStr(cdb_cmd_mode_t mode)
{
	switch(mode)
	{
		case CMD_MODE_ROOT:
			return "root";
		break;
		case CMD_MODE_ENABLE:
			return "config-enable";
        break;
		case CMD_MODE_CONFIG:
			return "config-term";
        break;
		case CMD_MODE_IF:
			return "config-if";
        break;
		case CMD_MODE_MIF:
			return "config-mif";
        break;
		default:
			return "Unknown";
		break;
	}
}

char * getCmdModePrompt(cdb_cmd_mode_t mode)
{
    switch(mode)
    {
        case CMD_MODE_ROOT:
            return "$";
        break;
        case CMD_MODE_ENABLE:
            return ">";
        break;
        case CMD_MODE_CONFIG:
		case CMD_MODE_IF:
		case CMD_MODE_MIF:
            return "#";
        break;
        default:
            return "*";
        break;
    }
}


void setCmdModeParams(cdb_t *sptr_cdb, cdb_cmd_mode_t mode)
{
	sptr_cdb->mode = mode;
	snprintf(sptr_cdb->curr_mode_str, CMD_LEN, "%s", getCmdModeStr(mode));
	snprintf(sptr_cdb->cmd_prompt,CMD_LEN,"%s",getCmdModePrompt(mode));
}

cdb_node_t cmd_root[] = {
	{
		CMD_MODE_ROOT,
		"enable",
		"Enable Command prompt for configuration",
		enable_cmd_prompt,
		NULL,
		CMD_FLAG_LAST
	}
};

cdb_node_t cmd_cfg_terminal[] = {
	{
		CMD_MODE_ENABLE,
		"terminal",
		"Config Terminal",
		enable_config_terminal,
		NULL,
		CMD_FLAG_LAST
	}
};

cdb_node_t cmd_show[] = {
	{
		CMD_MODE_NONE,
		"version",
		"Check Software Version",
		cmd_show_version,
		NULL,
		CMD_FLAG_NEXT
	},
	{
		CMD_MODE_NONE,
		"config",
		"Show Configurations",
		cmd_show_configurations,
		NULL,
		CMD_FLAG_LAST
	}
};

cdb_node_t cmd_enable[] = {
	{
		CMD_MODE_ENABLE,
		"config",
		"Enable Configuration",
		NULL,
		cmd_cfg_terminal,
		CMD_FLAG_NEXT
	},
	{
		CMD_MODE_ENABLE,
		"show",
		"Show Commands",
		NULL,
		cmd_show,
		CMD_FLAG_NEXT | CMD_FLAG_LAST
	}
};







