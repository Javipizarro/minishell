/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:01:09 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/14 20:01:32 by jpizarro         ###   ########.fr       */
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

