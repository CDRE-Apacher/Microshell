#ifndef __CMDS_H_
#define __CMDS_H_

#define ADD_CMD(name, func) {name, &func},
#define CMD_FUNC(name) int name(char ** tokenizedInput, int inputTokenCount)


typedef CMD_FUNC(CmdFunc);

typedef struct builtInCmds_s {
	const char *cmd;
	CmdFunc * func;
} builtInCmds_t;


CMD_FUNC(CMD_Exit);
CMD_FUNC(CMD_CD);


static builtInCmds_t builtInCmds[] =
{
	ADD_CMD("quit", CMD_Exit)
	ADD_CMD("exit", CMD_Exit)
	ADD_CMD("cd", CMD_CD)
};

#endif