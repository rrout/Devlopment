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

extern cdb_node_t cmd_enable[];

cdb_node_t * getCdbNode(char *cmdline)
{
	char delim[] = " "; // " ,-";
	char *token;
	int tokenCount = 0,  i = 0, subnode = 0;;
	char tokenDb[20][50] = {'\0'};
	cdb_node_t *cmdRoot;
	bool gotNode = FALSE;
	bool cmdNodeFound = FALSE;
    char cmmmonnnd[1024] = {0};

    strcpy (cmmmonnnd, cmdline);

	if (strlen(cmdline) == 0)
	{
		return cmd_enable;
	}

	for (token = strtok(cmmmonnnd, delim); token; token = strtok(NULL, delim))
	{
		strncpy(tokenDb[tokenCount++], token, sizeof(tokenDb[0]));
	}

	cmdRoot = cmd_enable;
	while (i < tokenCount)
	{
		subnode = 0;
		while (!(cmdRoot[subnode].flags & CMD_FLAG_LAST))
		{
			if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0)
			{
				cmdRoot = cmdRoot[subnode].next_node;
				gotNode = TRUE;
				//break;
			}
			subnode++;
		}
		if (gotNode == TRUE)
		{
			cmdNodeFound = TRUE;
			break;
		}
		/* try to get next node */
		i++;
	}

	if (cmdNodeFound)
		return cmdRoot;
	else
		return NULL;
}

cdb_node_t * getCdbNextNode(char *cmdline)
{
	char delim[] = " "; // " ,-";
	char *token;
	int tokenCount = 0,  i = 0, subnode = 0;;
	char tokenDb[20][50] = {'\0'};
    unsigned int tokenDbMatched[20] = {0};
	cdb_node_t *cmdRoot;
	bool gotNode = FALSE;
	bool cmdNodeFound = FALSE;
    char cmmmonnnd[1024] = {0};
    int matchCount = 0;
    cdb_cmd_mode_t curr_mode =  CMD_MODE_MAX;

    strcpy (cmmmonnnd, cmdline);
    curr_mode = getCmdModeFromModeStr(g_sptr_cdb.curr_mode_str);
    cmdRoot = getCmdNodeFromMode(curr_mode);

    if (!cmdRoot)
        return NULL;

	if (strlen(cmdline) == 0)
	{
		return cmdRoot;
	}

	for (token = strtok(cmmmonnnd, delim); token; token = strtok(NULL, delim))
	{
		strncpy(tokenDb[tokenCount++], token, sizeof(tokenDb[0]));
	}

	//cmdRoot = cmd_enable;

    while (i < tokenCount)
    {
        if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0) {
            cmdRoot = cmdRoot[subnode].next_node;
            tokenDbMatched[i] = 1;
            matchCount++;
            if (cmdRoot == NULL)
                break;
            i++;
            continue;
        }

        subnode = 0;
        while (!(cmdRoot[subnode].flags & CMD_FLAG_LAST))
        {
            if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0)
            {
                cmdRoot = cmdRoot[subnode].next_node;
                tokenDbMatched[i] = 1;
                matchCount++;
                break;
            }
            subnode++;
        }
        if (cmdRoot == NULL)
            break;

        if (cmdRoot[subnode].flags & CMD_FLAG_LAST &&
            strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0) {
            cmdRoot = cmdRoot[subnode].next_node;
            tokenDbMatched[i] = 1; 
            matchCount++;
            if (cmdRoot == NULL)
                break;
            i++;
            continue;
        }

        i++;
    }

    /* This is junk actually not needed */
    if (matchCount == 0 && strlen(cmdline) == 0)
        return NULL;

    /* if there is a token which is not first, check its prev token matched 
        Revisit as this has to check if first token is a full word or a pracial */
    //if (matchCount == 0 && tokenCount != 0)
    //return NULL;

    /* command has to match all token except last */ 
    for( i=0 ; i < tokenCount-1 ; i++ )
    {
        if(tokenDbMatched[i] != 1)
            return NULL;
    }
    return cmdRoot;
}

void showCmdNodeOptions(cdb_node_t *node)
{
    int node_iter = 0,  curnode = 0;
    
    char cr_op[10];
    if (node)
    {
       node_iter = 0;
        do {
            curnode = node_iter;
            sprintf(cr_op, "%s", " ");
            if (node[node_iter].flags & CMD_FLAG_CR_ALLOWED)
                sprintf(cr_op, "%s", "(  <CR> )");
            if (node[node_iter].flags & CMD_FLAG_NEXT)
                sprintf(cr_op, "%s", "(   ->  )");
            if (node[node_iter].flags & CMD_FLAG_LAST)
                sprintf(cr_op, "%s", "(  <CR> )");
            if (node[node_iter].flags & CMD_FLAG_CR_ALLOWED &&
               node[node_iter].flags & CMD_FLAG_NEXT)
                sprintf(cr_op, "%s", "(<CR> ->)");
            printf("\t%-10s %-8s %s\n",node[node_iter].cmd, cr_op, node[node_iter].cmd_desc);
            node_iter++;
        }while (!(node[curnode].flags & CMD_FLAG_LAST));
    } else {
        printf ("Unknown Command\n");
    }
}

void showCmdQuitOptions()
{
    printf("\t%-10s %-8s %s\n","exit", "(  <CR> )", "Exit to root mode");
    printf("\t%-10s %-8s %s\n","quit", "(  <CR> )", "Quit from current mode");
}

void showCmdCrOption()
{
    printf("\t%-10s %-8s %s\n","", "(  <CR> )", "Enter <-|");
}

cdb_node_t *showHelp(char *cmdline)
{
    char delim[] = " ";
    char *token;
    int tokenCount = 0,  i = 0, subnode = 0, curnode = 0, matchCount = 0;
    char tokenDb[20][50] = {'\0'};
    cdb_cmd_mode_t curr_mode =  CMD_MODE_MAX;
    cdb_node_t *cmdRoot;
    char cmmmonnnd[1024] = {0};

    strcpy (cmmmonnnd, cmdline);
    if (strlen(cmdline) == 0)
        return cmdRoot;
    curr_mode = getCmdModeFromModeStr(g_sptr_cdb.curr_mode_str);
    cmdRoot = getCmdNodeFromMode(curr_mode);
    if (!cmdRoot)
    {
        printf ("Unknown Command\n");
        return NULL;
    }
    for (token = strtok(cmmmonnnd, delim); token; token = strtok(NULL, delim))
        strncpy(tokenDb[tokenCount++], token, sizeof(tokenDb[0]));

    while (i < tokenCount)
    {
        subnode = 0;
        do {
            curnode = subnode;
            if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0)
            {
                cmdRoot = cmdRoot[subnode].next_node;
                matchCount++;
            }
            if (!cmdRoot)
                break;
            subnode++;
        }while (!(cmdRoot[curnode].flags & CMD_FLAG_LAST));

        if (cmdRoot == NULL)
            break;
        i++;
    }
    if((tokenCount - matchCount) > 1)
    {
        printf ("Unknown Command\n");
        return NULL;
    }
    /* if cmd tree ends show CR else show node options*/
    if (!cmdRoot && matchCount == tokenCount-1)
        showCmdCrOption();
    else
        showCmdNodeOptions(cmdRoot);
    return NULL;
}

void execCmdNodeCallBack(int is_full_cmd, cdb_node_t *node, cdb_t *sptr_cdb)
{
    if (node)
    {
       sptr_cdb->last_cmd_token = is_full_cmd;
       if (is_full_cmd)
       {
           if (!(node->flags & CMD_FLAG_CR_ALLOWED)) {
               printf("Incomplete command !\n");
            } else {
               if (node->cmd_callback)
                   node->cmd_callback(sptr_cdb);
           }
       } else {
           if (node->cmd_callback)
               node->cmd_callback(sptr_cdb);
       }
    }
    else
    {
        printf("Invalid command node!\n");
    }
    sptr_cdb->last_cmd_token = 0;
}

cdb_node_t * getCdbExecCli(char *cmdline)
{
	char delim[] = " "; // " ,-";
	char *token;
	int tokenCount = 0,  i = 0, subnode = 0, curnode = 0;
    int last_token = 0;
	char tokenDb[20][50] = {'\0'};
	cdb_node_t *cmdRoot;
    cdb_node_t *prevCmdRoot = NULL;
	bool gotNode = FALSE;
	bool cmdNodeFound = FALSE;
    char cmmmonnnd[1024] = {0};
    int matchCount = 0;
    cdb_cmd_mode_t curr_mode =  CMD_MODE_MAX;
    cdb_cmd_mode_t prev_mode =  CMD_MODE_MAX;

    strcpy (cmmmonnnd, cmdline);
    curr_mode = getCmdModeFromModeStr(g_sptr_cdb.curr_mode_str);
    cmdRoot = getCmdNodeFromMode(curr_mode);
    if (!cmdRoot)
    {
        printf ("Unknown Command\n");
        return NULL;
    }

	if (strlen(cmdline) == 0)
	{
		return cmdRoot;
	}

	for (token = strtok(cmmmonnnd, delim); token; token = strtok(NULL, delim))
	{
		strncpy(tokenDb[tokenCount++], token, sizeof(tokenDb[0]));
	}

    while (i < tokenCount)
    {
        if (0 == strcmp(tokenDb[i++], "?"))
        {
            showHelp(cmdline);
            if (tokenCount == 1)
                showCmdQuitOptions();
            return NULL;
        }
    }

    if (tokenCount == 1 && ( 0 == strcmp(tokenDb[0], "exit") ||
                0 == strcmp(tokenDb[0], "quit"))) {
        if (0 == strcmp(tokenDb[0], "quit")) {
            prev_mode = getPrevCmdMode(curr_mode);
        } else if (0 == strcmp(tokenDb[0], "exit")) {
            if (curr_mode == CMD_MODE_ENABLE)
                prev_mode = CMD_MODE_ROOT;
            else if (curr_mode == CMD_MODE_ROOT)
                prev_mode = CMD_MODE_MAX;
            else
                prev_mode = CMD_MODE_ENABLE;
        }
        if (prev_mode != CMD_MODE_MAX)
            setCmdModeParams(&g_sptr_cdb, prev_mode);
         return NULL;
    }
	//cmdRoot = cmd_enable;
    i = 0;
    while (i < tokenCount)
    {
        (i == (tokenCount-1))? (last_token = 1) : (last_token = 0);
        
        if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0) {
            execCmdNodeCallBack(last_token, &cmdRoot[subnode], &g_sptr_cdb);
            cmdRoot = cmdRoot[subnode].next_node;
            matchCount++;
            if (cmdRoot == NULL)
                break;
            i++;
            continue;
        }
        subnode = 0;
        //while (!(cmdRoot[subnode].flags & CMD_FLAG_LAST))
        do
        {
            curnode = subnode;
            if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0)
            {
                execCmdNodeCallBack(last_token, &cmdRoot[subnode], &g_sptr_cdb);
                cmdRoot = cmdRoot[subnode].next_node;
                matchCount++;
                break;
            }
            subnode++;
        } while (!(cmdRoot[curnode].flags & CMD_FLAG_LAST));
        
        if (cmdRoot == NULL)
            break;
        i++;
        /* Break is all token does not match */
        if (i != matchCount)
            break;
    }

    if (matchCount == 0)
    {
        printf ("Unknown Command\n");
        return NULL;
    }
    if ((tokenCount - matchCount) > 1)
    {
        printf ("Unknown Command\n");
        return NULL;
    }
    return cmdRoot;
}


cdb_t g_sptr_cdb;
void parserCliSrart(char *cliHost)
{
	char cmdLine[CMD_LEN] = {0};
	//cdb_t sptr_cdb;
	parserInit(cliHost, &g_sptr_cdb);
	while(1)
	{
        //printf("%s(%s)%s ", sptr_cdb.cmd_hostname, sptr_cdb.curr_mode_str, sptr_cdb.cmd_prompt);
        printf("%s(%s)%s ", g_sptr_cdb.cmd_hostname, g_sptr_cdb.curr_mode_str, g_sptr_cdb.cmd_prompt);
        fgets(cmdLine, CMD_LINE_LEN, stdin);
		cmdLine[strlen(cmdLine)-1] = '\0';	
		parser(&g_sptr_cdb, cmdLine);
	}
}

