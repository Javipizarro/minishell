/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:31:23 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/04 18:50:25 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Generates a new link with the environment variable received as
**	env_var argument, the def tells whether the variable is
**	just declared (0) or is defined (>0).
**	Returns it a pointer to the new link.
*/

t_env	*add_env_link(char **env_var, int def)
{
	t_env	*new;
	char	*temp;

	new = malloc(sizeof(t_env));
	if (!new)
		perror("malloc error");
	new->var = ft_split("javi", 'a');
	temp = new->var[0];
	new->var[0] = env_var[0];
	env_var[0] = temp;
	temp = new->var[1];
	if (env_var[1])
	{
		new->var[1] = env_var[1];
		env_var[1] = temp;
	}
	else if (def)
		new->var[1] = ft_strdup("");
	else
		new->var[1] = NULL;
	new->next = NULL;
	return(new);
}

/*
**	Searches the env_var in the env list and returns a double pointer to the
**	link that contains it so you can manipulate it.
*/

t_env	**search_env(char *env_name, t_env **env)
{
	if (!env_name)
		return (NULL);
	else
		while (*env && ft_strcmp(env[0]->var[0], env_name))
			env = &env[0]->next;
	return (env);
}

/*
**	Counts the amount of environment variables in the env list.
*/

int	count_env(t_env **env)
{
	int i;

	i = 0;
	while (env[0] && ++i)
		env = &env[0]->next;
	return (i);
}


/*
**	Transforms a env_var info into a malloced *char to use as an envp line and
**	returns it. It returns NULL if the variable is not initialized.
*/

char	*get_envp_line(t_env *env_var)
{
	char	*temp;
	char	*envp_line;

	if (!env_var->var[1])
		return (NULL);
	temp = ft_strjoin(env_var->var[0], "=");
	envp_line = ft_strjoin(temp, env_var->var[1]);
	free(temp);
	temp = NULL;
	return (envp_line);
}

/*
**	Creates a malloced envp list in a ft_split mode and replaces the previous
**	one if there is any.
*/

void	reset_envp(t_mini_data *data)
{
	t_env	*env_var;
	int		env_quan;
	int		i;

	if (data->envp)
		ft_free_split(data->envp);
	i = 0;
	env_quan = count_env(&data->env);
	data->envp = ft_calloc(sizeof(char**), env_quan + 1);
	env_var = data->env;
	while (i < env_quan && env_var)
	{
		data->envp[i] = get_envp_line(env_var);
			env_var = env_var->next;
		if (data->envp[i])
			i++;
		else
			env_quan--;
	}
}