/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:51:31 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/19 18:31:37 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Sets the value of the environment variable var_name to the value var_val,
**	wich must be malloced and will receive the old value of the var_val (their
**	pointers are swaped).
**	It returns the pointer to the t_env link where this variable is stored
**	or NULL if env_name doesn't exists.
*/

t_env	*set_env_value(char *var_name, char *var_val[], t_env *env)
{
	char	*temp;

	if (!var_val[0])
		return (env);
	env = *search_env(var_name, &env);
	if (!env)
		return (env);
		temp = env->var[1];
	if (var_val[0])
		env->var[1] = var_val[0];
	else
		env->var[1] = ft_strdup("");
	var_val[0] = temp;
	return (env);
}
