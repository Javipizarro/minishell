/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:47:45 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/17 01:33:14 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Removes the environment variable env_name, from the list env.
*/

int	unset(t_mini_data *data)
{
	t_env *dump;
	t_env **env;

	env = search_env(data->cmd[1], &data->env);
	if (!*env)
		return (0);
	dump = *env;
	env[0] = env[0]->next;
	free(dump);
	dump = NULL;
	reset_envp(data);
	return (0);
}
