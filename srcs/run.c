#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*output;

	while (1)
	{
		output = readline("tinyshell$ ");
		if (!output)
		{
			printf("no input\n");
			return (0);
		}
		add_history(output);
		free(output);
	}
	return (0);
}
