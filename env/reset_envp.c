/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset__envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:31:23 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/19 18:33:32 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Counts the amount of environment variables in the env list.
*/

int	count_env(t_env **env)
{
	int	i;

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
	data->envp = ft_calloc(sizeof(char **), env_quan + 1);
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
