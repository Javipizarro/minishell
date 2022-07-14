/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:47:45 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/14 20:13:56 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Removes the environment variable env_name, from the list env.
*/

int	unset(char **cmd, t_mini_data *data, pid_t pid)
{
	t_env *dump;
	t_env **env;
	int	i;

	if (!pid)
		return (CONTINUE);
	i = 0;
	while (cmd[++i])
	{
		env = search_env(cmd[i], &data->env);
		if (!*env)
			return (manage_errors(CONTINUE, NULL));
		dump = *env;
		env[0] = env[0]->next;
		ft_free_split(dump->var);
		free(dump);
		dump = NULL;
	}
	return (manage_errors(CONTINUE, NULL));
}
