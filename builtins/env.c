/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:44:43 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/17 01:19:07 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Prints the list of environment variables.
*/

//int	env(t_env *env)
//{
//	while (env)
//	{
//		if (env->var[1])
//			printf("%s=%s\n", env->var[0], env->var[1]);
//			env = env->next;
//	}
//	return(0);
//}

int	env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return(0);
}
