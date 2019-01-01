#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "cmd.h"

void parser(cdb_t *sptr_cdb, char *cmdline)
{
	if (strlen(cmdline) == 0)
		return;

	if(strcmp(cmdline,"exit") == 0)
	{
		char hostname[CMD_HOST_NAME_LEN] = {0};
		strcpy(hostname, sptr_cdb->cmd_hostname);
		setCmdModeParams(sptr_cdb, CMD_MODE_ROOT);
		parserInit(hostname, sptr_cdb);
		return;
	}

	if (sptr_cdb->mode == CMD_MODE_ROOT)
	{
		if(strcmp(cmdline,"enable") == 0)
		{
			setCmdModeParams(sptr_cdb, CMD_MODE_ENABLE);
			return;
		}
		else
		{
			printf("cli is not enabled\n");
			return;
		}
	}

	if (sptr_cdb->mode == CMD_MODE_ENABLE)
	{
		if (strstr(cmdline, "show") != 0)
		{
			printf("Only show commands allowed\n");
			return;
		}
		else if (strcmp(cmdline,"configure terminal") == 0)
		{
			setCmdModeParams(sptr_cdb, CMD_MODE_CONFIG);
			return;
		}
		else if (strstr(cmdline, "show") != 0)
		{
			printf("Only show commands allowed\n");
			return;
		}
		else
		{
			printf("show commands section yet to be implimented\n");
			return;
		}
	}

	if (sptr_cdb->mode == CMD_MODE_CONFIG)
	{
		printf("config commands section yet to be implimented\n");
	}

}

void parserInit(char *cliHost, cdb_t *sptr_cdb)
{
	/*char mode_str[CMD_LEN] = {0};*/
	memset(sptr_cdb, 0, sizeof(cdb_t));
	snprintf(sptr_cdb->cmd_hostname, CMD_HOST_NAME_LEN, "%s", cliHost);
	setCmdModeParams(sptr_cdb, CMD_MODE_ROOT);
		/*sptr_cdb->cmd_mode = CMD_MODE_ROOT;*/
		/*sprintf(mode_str, CMD_LEN, getCmdModeStr(sptr_cdb->cmd_mode));*/
		/*sprintf(sptr_cdb->curr_mode_str, CMD_LEN, "%s", mode_str);*/
		/*sprintf(sptr_cdb->cmd_prompt,CMD_LEN,"%c",getCmdModePrompt(sptr_cdb->cmd_mode));*/
}

void parserCliSrart(char *cliHost)
{
	char cmdLine[CMD_LEN] = {0};
	cdb_t sptr_cdb;
	parserInit(cliHost, &sptr_cdb);
	while(1)
	{
		printf("%s(%s)%s ", sptr_cdb.cmd_hostname, sptr_cdb.curr_mode_str, sptr_cdb.cmd_prompt);
		fgets(cmdLine, CMD_LINE_LEN, stdin);
		cmdLine[strlen(cmdLine)-1] = '\0';	
		parser(&sptr_cdb, cmdLine);
	}
}

