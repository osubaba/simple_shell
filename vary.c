#include "main.h"

/**
 * check_env - Checks if the typed variable is an environment variable.
 *
 * @h: Head of linked list
 * @in: Input string
 * @data: Data structure
 * Return: No return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, j, len_val;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				len_val = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, j, _envr[row] + chr + 1, len_val);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - Check if the typed variable is $$ or $?
 *
 * @h: Head of the linked list
 * @in: Input string
 * @st: Last status of the Shell
 * @data: Data structure
 * Return: No return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int i, last_status, len_pid;

	last_status = _strlen(st);
	len_pid = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node(h, 2, st, last_status), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, len_pid), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_input - Replaces string into variables.
 *
 * @head: Head of the linked list
 * @input: Input string
 * @new_input: New input string (replaced)
 * @nlen: New length
 * Return: Replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					new_input[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - Calls functions to replace string into vars.
 *
 * @input: Input string
 * @datash: Data structure
 * Return: Replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *index;
	char *status, *new_input;
	int orig_len, new_len;

	status = aux_itoa(datash->status);
	head = NULL;

	orig_len = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	new_len = 0;

	while (index != NULL)
	{
		new_len += (index->len_val - index->len_var);
		index = index->next;
	}

	new_len += orig_len;

	new_input = malloc(sizeof(char) * (new_len + 1));
	new_input[new_len] = '\0';

	new_input = replaced_input(&head, input, new_input, new_len);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}

