#include "common.h"
#include "cmds.h"

CMD_FUNC(CMD_Exit)
{
	exit(0);
	return 0;
}

CMD_FUNC(CMD_CD)
{
	return set_working_directory(tokenizedInput[1]);
}