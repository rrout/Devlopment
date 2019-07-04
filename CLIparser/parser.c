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

bool checkPartialStr(const char *prefix, const char *str)
{
    int lenPrefix = strlen(prefix);
    int lenStr = strlen(str);
    if (lenStr < lenPrefix)
        return FALSE;
    if (strncmp(prefix, str, lenPrefix) == 0)
        return TRUE;
    return FALSE;
}

bool checkCmdLineTokenMatch(cdb_node_t *cmdNode, const char *cmdLine,
    bool fullMatch, unsigned int *matchIndex, unsigned int *matchCount)
{
    int curIter = 0, iter = 0, count = 0;

    if (!cmdNode || !cmdLine || !matchIndex) {
        printf ("Invalid usage of the libreary function\n");
        return FALSE;
    }
    /* Initialize to  0 */
    *matchIndex = 0;

    /* Browse through all the CMD subnodes first */
    do {
        curIter = iter;
        if (cmdNode[iter].cmd_type == CMD_TYPE_CMD) {
           if(strcmp(cmdNode[iter].cmd , cmdLine) == 0 ||
                ((fullMatch == FALSE) &&
                checkPartialStr(cmdLine, cmdNode[iter].cmd))) {
                count++;
                if (*matchIndex == 0)   /* Capture the first index Only */
                    *matchIndex = iter;
                //break;
            }
        }
        iter++;
    }while (!(cmdNode[curIter].flags & CMD_FLAG_LAST));

    /* Browse through the non CMD sunnodes if no cmd matches*/
    if (count == 0) { //No command matched
        curIter = iter  = 0;
        do {
            curIter = iter;
            switch (cmdNode[iter].cmd_type) {
                case CMD_TYPE_IF_STRING:
                case CMD_TYPE_STRING:
                case CMD_TYPE_DECIMAL:
                case CMD_TYPE_HEX:
                case CMD_TYPE_IP:
                    if (*matchIndex == 0)   /* Capture the first index Only */
                        *matchIndex = iter;
                    count++;
                    break;
                default:
                    break;
            }
            iter++;
        }while (!(cmdNode[curIter].flags & CMD_FLAG_LAST));
    }

    if (count) {
        if (matchCount)
            *matchCount = count;
        return TRUE;
    }
    return FALSE;
}

bool checkCmdLineMatch(cdb_node_t *cmdNode, const char *cmdLine,
    unsigned int *matchIndex, unsigned int *matchCount)
{
    return checkCmdLineTokenMatch(cmdNode, cmdLine, FALSE, matchIndex,matchCount);
}

bool checkCmdLineMatchFull(cdb_node_t *cmdNode, const char *cmdLine,
    unsigned int *matchIndex, unsigned int *matchCount)
{
    return checkCmdLineTokenMatch(cmdNode, cmdLine, TRUE, matchIndex, matchCount);
}


cdb_node_t * getCdbNode(char *cmdline)
{
	char delim[] = " "; // " ,-";
	char *token;
	int tokenCount = 0,  i = 0, subnode = 0;;
	char tokenDb[CMD_MAX_TOKEN][CMD_MAX_TOKEN_LEN] = {{'\0'}};
	cdb_node_t *cmdRoot;
	bool gotNode = FALSE;
	bool cmdNodeFound = FALSE;
    char command[1024] = {0};

    strcpy (command, cmdline);

	if (strlen(cmdline) == 0)
	{
		return cmd_enable;
	}

	for (token = strtok(command, delim); token; token = strtok(NULL, delim))
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
	int tokenCount = 0,  i = 0, subnode = 0, curnode = 0, matchIndex = 0;
	char tokenDb[CMD_MAX_TOKEN][CMD_MAX_TOKEN_LEN] = {{'\0'}};
    unsigned int tokenDbMatched[CMD_MAX_TOKEN] = {FALSE};
	cdb_node_t *cmdRoot;
    char command[1024] = {0};
    int matchCount = 0;
    cdb_cmd_mode_t curr_mode =  CMD_MODE_MAX;

    strcpy (command, cmdline);
    curr_mode = getCmdModeFromModeStr(g_sptr_cdb.curr_mode_str);
    cmdRoot = getCmdNodeFromMode(curr_mode);

    if (!cmdRoot)
        return NULL;

	if (strlen(cmdline) == 0)
	{
		return cmdRoot;
	}

	for (token = strtok(command, delim); token; token = strtok(NULL, delim))
	{
		strncpy(tokenDb[tokenCount++], token, sizeof(tokenDb[0]));
	}
#if 0
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
#else
   while (i < tokenCount)
    {
#if 0
        subnode = 0;
        do {
            curnode = subnode;
            if (cmdRoot[subnode].cmd_type == CMD_TYPE_CMD) {
                if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0 ||
                    ((i != tokenCount-1) &&
                     checkPartialStr(tokenDb[i], cmdRoot[subnode].cmd))) {
                    cmdRoot = cmdRoot[subnode].next_node;
                    tokenDbMatched[i] = 1;
                    matchCount++;
                    break;
                }
            } else if (cmdRoot[subnode].cmd_type == CMD_TYPE_STRING) {
                /*
                 * Check if tokenDb[i] is a plane string
                 * if yes increment match as it matched
                 * then jump to next node
                 */
            } else if (cmdRoot[subnode].cmd_type == CMD_TYPE_DECIMAL) {

            }else if (cmdRoot[subnode].cmd_type == CMD_TYPE_HEX) {

            }
            subnode++;
        }while (!(cmdRoot[curnode].flags & CMD_FLAG_LAST));
#else
        if (i != tokenCount-1) {
            if (checkCmdLineMatch(cmdRoot, tokenDb[i], &matchIndex, NULL)) {
                cmdRoot = cmdRoot[matchIndex].next_node;
                tokenDbMatched[i] = 1;
                matchCount++;
            }
        } else {
            if (checkCmdLineMatchFull(cmdRoot, tokenDb[i], &matchIndex, NULL)) {
                cmdRoot = cmdRoot[matchIndex].next_node;
                tokenDbMatched[i] = 1;
                matchCount++;
            }
        }
#endif

        if (cmdRoot == NULL)
            break;
        i++;
    }
#endif


    /* This is junk actually not needed */
    if (matchCount == 0 && strlen(cmdline) == 0)
        return NULL;

    /* if there is a token which is not first, check its prev token matched 
        Revisit as this has to check if first token is a full word or a pracially entered
        in case of partial entered we still need to identify and auto complete this*/
    //if (matchCount == 0 && tokenCount != 1)
    //return NULL;

    /* command has to match all token except last */ 
    for( i=0 ; i < tokenCount-1 ; i++ )
    {
        if(tokenDbMatched[i] != TRUE)
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
    char tokenDb[CMD_MAX_TOKEN][CMD_MAX_TOKEN_LEN] = {{'\0'}};
    cdb_cmd_mode_t curr_mode =  CMD_MODE_MAX;
    cdb_node_t *cmdRoot = NULL;
    char command[1024] = {0};

    strcpy (command, cmdline);
    if (strlen(cmdline) == 0)
        return cmdRoot;
    curr_mode = getCmdModeFromModeStr(g_sptr_cdb.curr_mode_str);
    cmdRoot = getCmdNodeFromMode(curr_mode);
    if (!cmdRoot)
    {
        printf ("Unknown Command\n");
        return NULL;
    }
    for (token = strtok(command, delim); token; token = strtok(NULL, delim))
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
    /* if cmd tree ends, show CR else show node options*/
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
bool is_valid_if_line(char *cmdLine)
{
    int i = 0;
    unsigned int length = 0;
    if (!cmdLine)
        return FALSE;
    length = strlen(cmdLine);
    for (i=0;i<length; i++) {
        /*if (i > 0) {
            if (cmdLine[i] == '-' || cmdLine[i] == ',') {
                if (cmdLine[i-1] == '-' || cmdLine[i-1] == ',') {
                    return FALSE;
                }
            }
        }*/
        if ((i > 0) && (cmdLine[i] == '-' || cmdLine[i] == ',') &&
            (cmdLine[i-1] == '-' || cmdLine[i-1] == ','))
            return FALSE;

        if (isdigit(cmdLine[i]) || cmdLine[i] == '-' || cmdLine[i] == ',' )
            continue;
        else
            return FALSE;
    }

    if (cmdLine[0] == '-' || cmdLine[0] == ',')
        return FALSE;
    if((length > 1) && (cmdLine[length-1] == '-' || cmdLine[length-1] == ','))
        return FALSE;

    return TRUE;
}

int setIfBit(unsigned int *if_map, unsigned int bit)
{
    if (!if_map)
        return 0;
    if (bit > MAX_IF_BITS) {
        printf("%s: bit %d ig greater than MAX_IF_BITS\n",__FUNCTION__, bit);
        return 0;
    }

    *if_map |= 1<<bit;
}

bool ifLineToIfMap(char *cmdLine, unsigned int *if_map)
{
    char line[CMD_LEN];
    char *delim = "-,";
    int to = 0, from = 0, i = 0;
    char *res = NULL;
    int bit = 0;
    int tokenArr[MAX_IF_BITS+MAX_IF_BITS] = {0};
    int elemCount = 0;
    int last_set_bit = 0;

    if (!cmdLine || !if_map || !is_valid_if_line(cmdLine))
    {
        printf("Invalid Line %s\n", cmdLine);
        return FALSE;
    }

    strcpy(line, cmdLine);
    res = strtok(line, delim);
#if 0
    while (res) {
        printf("%s\n",res);
        tokenArr[
        bit = atoi(res);
        if(!setIfBit(if_map, bit))
            return FALSE;
        from = res-line+strlen(res);
        res = strtok( NULL, delim );
        to = res != NULL ? res-line : strlen(cmdLine);
        // Print delimeter
        printf("%.*s\n", to-from, cmdLine+from);

    }
#else
    while (res) {
        //printf("%s",res);
        tokenArr[elemCount++] = atoi(res);
        //printf("%c", cmdLine[res-line+strlen(res)]);
        if (cmdLine[res-line+strlen(res)] == '-')
            tokenArr[elemCount++] = IF_SEPARATOR_DASH;
        if (cmdLine[res-line+strlen(res)] == ',')
            tokenArr[elemCount++] = IF_SEPARATOR_COMA;
        res = strtok( NULL, delim );
    }
    //printf("\n");

    last_set_bit = 0;
    for( i = 0 ; i < elemCount; i++ )
    {
        //printf("%d  ",tokenArr[i]);
        if(tokenArr[i] != IF_SEPARATOR_DASH && tokenArr[i] != IF_SEPARATOR_COMA) {
            if (last_set_bit && last_set_bit > tokenArr[i]) {
                //printf("Invalid if config : %s\n", cmdLine);
                return FALSE;
            }
            last_set_bit = tokenArr[i];
        }
    }
    //printf("\n");

    last_set_bit = 0;
    for( i = 0 ; i < elemCount; i++ )
    {
        if (i == 0) {
            setIfBit(if_map, tokenArr[i]);
            last_set_bit = tokenArr[i];
        }
        else
        {
            if(tokenArr[i] != IF_SEPARATOR_DASH && tokenArr[i] != IF_SEPARATOR_COMA) {
                setIfBit(if_map, tokenArr[i]);
                if((tokenArr[i-1] == IF_SEPARATOR_DASH))
                {
                    int iter = 0;
                    for (iter = last_set_bit; iter < tokenArr[i]; iter++)
                        setIfBit(if_map, iter);
                }
                last_set_bit = tokenArr[i];
            }
        }
    }
#endif
    return TRUE;
}

bool ifMapToIfLine(unsigned int *if_map, char *ifLine)
{
    int i;
    if (!ifLine || !if_map) {
        printf("Invalid Args %s\n", __FUNCTION__);
        return FALSE;
    }
}


bool execCmdNodeParseToken(int last_token, cdb_cmd_type_t cmd_type, char *cmdToken, cdb_t *sptr_cdb)
{
    unsigned int if_map = 0;
    bool ret = TRUE;

    if (!cmdToken || !sptr_cdb)
    {
        printf ("Unknown Args\n");
        return FALSE;
    }
    switch (cmd_type)
    {
        case CMD_TYPE_IF_STRING:
            {
                ret = ifLineToIfMap(cmdToken, &if_map);
                if (ret == TRUE) {
                    sptr_cdb->if_map = if_map;
                    strncpy(sptr_cdb->if_str, cmdToken, CMD_LINE_LEN);
                }
            }
            break;
        default:
            ret = TRUE;
            break;
    }

    return ret;
}

cdb_node_t * getCdbExecCli(char *cmdline)
{
	char delim[] = " "; // " ,-";
	char *token;
	int tokenCount = 0,  i = 0, subnode = 0, curnode = 0, matchIndex = 0, chkCount = 0;
    int last_token = 0, ret = 0;
	char tokenDb[CMD_MAX_TOKEN][CMD_MAX_TOKEN_LEN] = {{'\0'}};
	cdb_node_t *cmdRoot = NULL;
    cdb_node_t *tmpCmdRoot = NULL;
    char command[1024] = {0};
    int matchCount = 0;
    cdb_cmd_mode_t curr_mode =  CMD_MODE_MAX;
    cdb_cmd_mode_t prev_mode =  CMD_MODE_MAX;

    strcpy (command, cmdline);
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

	for (token = strtok(command, delim); token; token = strtok(NULL, delim))
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

    if (tokenCount == 1 && ( 0 == strcmp(tokenDb[0], "exit") || checkPartialStr(tokenDb[0], "exit") ||
                0 == strcmp(tokenDb[0], "quit") || checkPartialStr(tokenDb[0], "quit"))) {
        if (0 == strcmp(tokenDb[0], "quit") || checkPartialStr(tokenDb[0], "quit")) {
            prev_mode = getPrevCmdMode(curr_mode);
        } else if (0 == strcmp(tokenDb[0], "exit") || checkPartialStr(tokenDb[0], "exit")) {
            if (curr_mode == CMD_MODE_ENABLE)
                prev_mode = CMD_MODE_ROOT;
            else if (curr_mode == CMD_MODE_ROOT)
                prev_mode = CMD_MODE_MAX;
            else
                prev_mode = CMD_MODE_ENABLE;
        }
        if (prev_mode != CMD_MODE_MAX) {
            setCmdModeParams(&g_sptr_cdb, prev_mode);
            cleanUpCdb(&g_sptr_cdb);
        }
         return NULL;
    }

    i = 0;
    tmpCmdRoot = cmdRoot;
    while (i < tokenCount)
    {
#if 0
        subnode = 0;
        do{
            curnode = subnode;
            if(strcmp(tmpCmdRoot[subnode].cmd , tokenDb[i]) == 0 ||
                checkPartialStr(tokenDb[i], tmpCmdRoot[subnode].cmd)) {
                /* Check Shall this be a unique node to jump next
                 * First check if its not the last element and if it is so
                 * Keep searching the uniqueness in the next set of elements*/
                if (checkPartialStr(tokenDb[i], tmpCmdRoot[subnode].cmd) &&
                    !(tmpCmdRoot[subnode].flags & CMD_FLAG_LAST)) {
                    int next = subnode+1;
                    int nextCurNode = 0;
                    do {
                        nextCurNode = next;
                        if (checkPartialStr(tokenDb[i], tmpCmdRoot[next].cmd))
                            matchCount++;
                        next++;
                    }while(!(tmpCmdRoot[nextCurNode].flags & CMD_FLAG_LAST));
                }
                tmpCmdRoot = tmpCmdRoot[subnode].next_node;
                matchCount++;
                break;
            }
            subnode++;
        }while (!(tmpCmdRoot[curnode].flags & CMD_FLAG_LAST));
#else
        if (checkCmdLineMatch(tmpCmdRoot, tokenDb[i], &matchIndex, &chkCount)) {
            if (chkCount > 1)
            {
                printf ("Ambgious Command!!!!!\n");
                return NULL;
            }
            tmpCmdRoot = tmpCmdRoot[matchIndex].next_node;
            matchCount++;
        }

#endif
        if (tmpCmdRoot == NULL)
            break;
        i++;
    }
#if 0
    /* check all token exactly matches in the cmd node to proceed in exec */
    if (matchCount > tokenCount)
    {
        printf ("Ambgious Command!\n");
        return NULL;
    }
#endif
    if (tokenCount != matchCount)
    {
        printf ("Unrecognized Command!\n");
        return NULL;
    }

    i = 0;
    matchCount = 0;
    while (i < tokenCount)
    {
        (i == (tokenCount-1))? (last_token = 1) : (last_token = 0);
#if 0        
        if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0 ||
            checkPartialStr(tokenDb[i], cmdRoot[subnode].cmd)) {
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
            if(strcmp(cmdRoot[subnode].cmd , tokenDb[i]) == 0 ||
                checkPartialStr(tokenDb[i], cmdRoot[subnode].cmd))
            {
                execCmdNodeCallBack(last_token, &cmdRoot[subnode], &g_sptr_cdb);
                cmdRoot = cmdRoot[subnode].next_node;
                matchCount++;
                break;
            }
            subnode++;
        } while (!(cmdRoot[curnode].flags & CMD_FLAG_LAST));
#else
    if (checkCmdLineMatch(cmdRoot, tokenDb[i], &matchIndex, &chkCount)) {
        ret = execCmdNodeParseToken(last_token,
            cmdRoot[matchIndex].cmd_type, tokenDb[i], &g_sptr_cdb);
        if (ret == FALSE)
            return NULL;
        execCmdNodeCallBack(last_token, &cmdRoot[matchIndex], &g_sptr_cdb);
        cmdRoot = cmdRoot[matchIndex].next_node;
        matchCount++;
    }
#endif
        if (cmdRoot == NULL)
            break;
        i++;
        /* Break if all token does not match  --- Junk */
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

