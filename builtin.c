#include "main.h"

/**
 * get_builtin - Find a built-in function by command name.
 * @cmd: The command name.
 *
 * Return: A function pointer to the built-in function.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{"env", _env},
		{"exit", exit_shell},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", cd_shell},
		{"help", get_help},
		{NULL, NULL}
	};
	int i = 0;

	while (builtin[i].name)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
		i++;
	}

	return (builtin[i].f);
}

