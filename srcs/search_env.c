/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:24:39 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/19 14:30:50 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Searches the env_var in the env list and returns a double pointer to the
**	link that contains it so you can manipulate it.
*/

t_env	**search_env(const char *env_name, t_env **env)
{
	if (!env_name)
		return (NULL);
	else
		while (*env && ft_strcmp(env[0]->var[0], env_name))
			env = &env[0]->next;
	return (env);
}
