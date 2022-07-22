/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:49:33 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/21 11:40:31 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Allocates (with malloc(3)) and returns an array of strings obtained
**	by splitting ’s’ using the first ocurrence of the character ’c’ as a
**	delimiter. The array is ended by a NULL pointer.
*/

char	**ft_splitonce(const char *s, char c)
{
	char	**mem;
	size_t	var[4];

	var[0] = 1 + (ft_charpos(s, c) > 0);
	mem = malloc(sizeof(char *) * (var[0] + 1));
	var[1] = 0;
	var[3] = 0;
	while (var[1] < var[0])
	{	
		if (var[1] == var[0] - 1)
			var[2] = ft_strlen(&s[var[3]]);
		else
			var[2] = ft_charindex(s, c);
		mem[var[1]] = malloc(sizeof(char) * (var[2] + 1));
		ft_memcpy(mem[var[1]], s + var[3], var[2]);
		mem[var[1]++][var[2]] = 0;
		var[3] = var[2] + 1;
	}
	mem[var[1]] = NULL;
	return (mem);
}


/*
**	Adds a new entry at the end of the environment variable chain.
**	Receives the line of the variable as it is written when the printenv
**	or env command is called, and a pointer to the head of the chain.
*/

int	export_env(char *var_def, t_env **env)
{
	int i;
	char	**env_var;

	i = -1;
	if (!var_def[0] || var_def[0] == '=')
		return (IDENERR);

	while (var_def[++i] && (ft_isalnum(var_def[i]) || var_def[i] == '_'))
		continue;
	if (var_def[i] && var_def[i] != '=')
		return (IDENERR);
	env_var = ft_splitonce(var_def, '=');
	env = search_env(env_var[0], env);
	if (!env[0])
		env[0] = add_env_link(env_var, ft_charpos(var_def, '='));
	else
		set_env_value(env_var[0], &env_var[1], *env);
	ft_free_split(env_var);
	env_var = NULL;
	return (0);
}

/*
**	Prints the environ variables var, followed by an = sign and with
**	the value between "", or just the name if it does't have a value.
*/

void	expvar_printer(char *var_name, t_env **env)
{
	env = search_env(var_name, env);
	
	write(STDOUT_FILENO, "declare -x ", 11);
	write(STDOUT_FILENO, env[0]->var[0], ft_strlen(env[0]->var[0]));
	if (env[0]->var[1])
	{
		write(STDOUT_FILENO, "=\"", 2);
		write(STDOUT_FILENO, env[0]->var[1], ft_strlen(env[0]->var[1]));
		write(STDOUT_FILENO, "\"", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

/*
**	Duplicates the env chain arranging it by alphabetical order of
**	the var_name (var[0]).
*/

void	arrange_n_print(t_env **env)
{
	char	*ref;
	char	*to_print;
	char	*last;
	t_env	*head;

	head = *env;
	ref = "";
	last = head->var[0];
	while (head)
	{
		if (ft_strcmp(head->var[0], last) > 0)
			last = head->var[0];
		head = head->next;
	}
	while (ft_strcmp(ref, last))
	{
		to_print = last;
		head = *env;
		while (head)
		{
			if (ft_strcmp(head->var[0], ref) > 0
			&& ft_strcmp(head->var[0], to_print) < 0)
				to_print = head->var[0];
			head = head->next;
		}
		ref = to_print;
		expvar_printer(to_print, env);
	}
}

/*
**	Receives the export cmd with its arguments if there are any, and executes
**	the corresponding actions.
*/

int	export(char **cmd, t_mini_data *data, pid_t pid)
{
	int i;

	i = 0;
	if (!cmd[1] && !pid)
		arrange_n_print(&data->env);
	else if (cmd[1] && pid)
	{
		while (cmd[++i])
		{
			data->err = export_env(cmd[i], &data->env);
			if (data->err)
				manage_errors(cmd[0], data->err, NULL);
		}
		reset_envp(data);
	}	
	return(CONTINUE);
}
