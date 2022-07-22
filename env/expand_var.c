/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:03:23 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/21 21:09:25 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Expands the variable in the possition 'pos' in 'line'. Modifies 'pos' to
**	point at the end of the expanded var.
*/

int	expand_var(char **line, int *pos, const char *var_name, t_env *env)
{
	char	*tmp;
	char	*var_val;

	env = *search_env(&var_name[1], &env);
	if (!env && !ft_strcmp(var_name, "$?"))
		var_val = ft_itoa(g_exit_status);
	else if (!env && !var_name[1])
		var_val = "$";
	else if (!env)
		var_val = "";
	else
		var_val = env->var[1];
	tmp = ft_calloc(ft_strlen(var_val) + ft_strlen(*line) + 1,
	sizeof(char));
	ft_memcpy(tmp, *line, *pos);
	ft_memcpy(&tmp[*pos], var_val, ft_strlen(var_val));
	ft_memcpy(&tmp[*pos + ft_strlen(var_val)], &line[0][*pos],
	ft_strlen(&line[0][*pos]));
	free(*line);
	*line = tmp;
	*pos += ft_strlen(var_val);
	return(var_val && var_val[0]);
}
