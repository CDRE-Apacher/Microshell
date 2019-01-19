#include "common.h"
#include "tokenizer.h"

char ** tokenArray;
static char tokenized[8192];

char ** tokenize_input(char * input, int *tokenCount)
{
	rbool isInStringLiteral = rfalse;
	int currentTokenID = 0;
	int currentTokenStrIndex = 0;
	/* allocate an array for tokens */
	tokenArray = (char **)calloc(2, sizeof(uintptr_t));
	tokenArray[0] = tokenized;
	memset(tokenArray[0], 0, 8192);

	int i = 0;

	for(i = 0;;i++)
	{
		assert(currentTokenStrIndex < 8192);
		if (input[i] == '\0')
		{
			/* we reached the end of the input, break */
			tokenized[currentTokenStrIndex] = '\0';
			break;
		}
		if (i != 0)
		{
			/* check if the current character is " and is not escaped by \, then we can assume we're inside a string */
			if (input[i] == '"' && input[i - 1] != '\\')
				isInStringLiteral = !isInStringLiteral;
		}
		if (input[i] == ' ' && strlen(tokenArray[currentTokenID]) != 0)
		{
			/* if we're not inside a string and we encountered a space, move on to a new token */
			if (!isInStringLiteral)
			{
				tokenized[currentTokenStrIndex] = '\0';
				currentTokenStrIndex++;
				currentTokenID++;
				tokenArray = (char **)realloc(tokenArray, sizeof(uintptr_t) * (currentTokenID + 2));
				tokenArray[currentTokenID] = &tokenized[currentTokenStrIndex];
				continue;
			}
		}

		/* handling escape sequences */

		if (input[i] == '"' && input[i - 1] == '\\')
		{
			tokenized[currentTokenStrIndex] = input[i];
			currentTokenStrIndex++;
			continue;
		}
		if (input[i] == 'n' && input[i - 1] == '\\')
		{
			tokenized[currentTokenStrIndex] = '\n';
			currentTokenStrIndex++;
			continue;
		}

		/* user pressed enter, break */
		if (input[i] == '\n')
		{
			tokenized[currentTokenStrIndex] = '\0';
			break;
		}
		if (input[i] == '\\') continue;
		
		/* add every other character */
		if ((input[i] != ' ' || isInStringLiteral) && input[i] != '"')
		{
			tokenized[currentTokenStrIndex] = input[i];
			currentTokenStrIndex++;
		}
	}
	*tokenCount = currentTokenID + 1;
	tokenArray[*tokenCount] = NULL;
	return tokenArray;
}
