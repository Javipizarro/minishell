/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:49:33 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/20 14:23:42 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
**
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
	char	**env_var;

	if (var_def[0] == '=')
		return (1);
	env_var = ft_splitonce(var_def, '=');
	env = search_env(env_var[0], env);
	if (!env[0])
		env[0] = add_env_link(env_var, ft_charpos(var_def, '='));
	else
		set_env_value(env_var, ft_charpos(var_def, '='), *env);
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
	if (env[0]->var[1])
		printf("%s=\"%s\"\n", env[0]->var[0], env[0]->var[1]);
	else
		printf("%s\n", env[0]->var[0]);
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
			if (ft_strcmp(head->var[0], ref)>0
			&& ft_strcmp(head->var[0], to_print)< 0)
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

int	export(char **cmd, t_mini_data *data)
{
	int i;
	int err;

	i = 0;
	err = 0;
	if (!cmd[1])
		arrange_n_print(&data->env);
	else
	{
		while (cmd[++i])
		{
			err = export_env(cmd[i], &data->env);
			if(err)
				break;

		}
		if (err)
			printf("%s: %s: '%s': not a valid identifier\n",
			data->shell_name, cmd[0], cmd[i]);	// TODO: Valorar hacer una funci'on de impresi'on de errores
		else
			reset_envp(data);
	}	
	return(1);
}