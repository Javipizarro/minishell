/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:03:23 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/04 18:54:06 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Expands the variable in the possition 'pos' in 'line'. Modifies 'pos' to
**	point at the end of the expanded var.
*/

int	expand_var(char **line, int *pos, t_env *env, int check_spaces)
{
	int i;
	int	j;
	char	*tmp;
	char	*var_val;
	
	i = *pos;
	j = *pos + 1;
	while (line[0][j] && line[0][j] != '$' && line[0][j] != ' '
	&& line[0][j] != '"' && line[0][j] != '\'' && line[0][j] != '=')
		j++;
	tmp = ft_calloc(j - i, sizeof(char));
	ft_memcpy(tmp, &line[0][i + 1], j - i - 1);
	env = *search_env(tmp, &env);
	if (!env && !ft_strcmp(tmp, "?"))
		var_val = ft_itoa(g_exit_status);
	else if (!env)
		var_val = "";
	else
		var_val = env->var[1];
	free(tmp);
	if (check_spaces && ft_strchr(var_val, ' '))
		return (AMBRED);
	tmp = ft_calloc(ft_strlen(var_val) + ft_strlen(*line) - j + i + 1,
	sizeof(char));
	ft_memcpy(tmp, *line, i);
	ft_memcpy(&tmp[i], var_val, ft_strlen(var_val));
	ft_memcpy(&tmp[i + ft_strlen(var_val)], &line[0][j],
	ft_strlen(&line[0][j]));
	free(*line);
	*line = tmp;
	*pos += ft_strlen(var_val) - 1;
	return(0);
}
