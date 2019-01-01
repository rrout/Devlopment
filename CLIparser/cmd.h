#include <stdio.h>
#include <stdlib.h>


#ifndef __CMD_H__
#define __CMD_H__
#define CMD_LEN				20
#define CMD_DESC_LEN		255
#define CMD_LINE_LEN		255
#define CMD_HOST_NAME_LEN	55
typedef enum {
	CMD_MODE_ROOT,
	CMD_MODE_ENABLE,
	CMD_MODE_CONFIG,
	CMD_MODE_IF,
	CMD_MODE_MIF,
	CMD_MODE_MAX,
}cdb_cmd_mode_t;

typedef struct _cdb {
	char cmd_hostname[CMD_HOST_NAME_LEN];
	cdb_cmd_mode_t mode;
	char curr_mode_str[CMD_LEN];
	char cmd_prompt[2];
	unsigned int number1;
	unsigned int number2;
	unsigned int number3;
	unsigned int number4;
	unsigned int number5;
	unsigned int number6;
	unsigned int number7;
	unsigned int number8;
	unsigned int number9;
	unsigned int number10;
	unsigned int number11;
	char str1[CMD_LEN];
	char str2[CMD_LEN];
	char str3[CMD_LEN];
	char str4[CMD_LEN];
	char str5[CMD_LEN];
	char str6[CMD_LEN];
	char str7[CMD_LEN];
	char str8[CMD_LEN];
	char str9[CMD_LEN];
	char str10[CMD_LEN];
	char str11[CMD_LEN];
}cdb_t;

/*void (cmd_callback *) (cdb_t *sptr_cdb);*/
typedef enum {
	CMD_FLAG_FIRST,
	CMD_FLAG_LAST,
	CMD_FLAG_NEXT
}cdb_cmd_flag_t;

typedef struct _cdb_node {
	unsigned int mode_flags;
	char cmd[CMD_LEN];
	char cmd_desc[CMD_DESC_LEN];
	void (*cmd_callback) (cdb_t *sptr_cdb);
	struct _cdb_node *next_node;
	unsigned int flags;
}cdb_node_t;

char * getCmdModeStr(cdb_cmd_mode_t mode);
char * getCmdModePrompt(cdb_cmd_mode_t mode);
void setCmdModeParams(cdb_t *sptr_cdb, cdb_cmd_mode_t mode);

#endif /*__CMD_H__*/
