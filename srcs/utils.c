/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:03:23 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/04 13:25:48 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Expands the variable in the possition 'pos' in 'line'. Modifies 'pos' to
**	point at the end of the expanded var.
*/

void	expand_var(char **line, int *pos, t_env *env)
{
	int i;
	int	j;
	char	*tmp;
	char	*var_val;
	
	i = *pos;
	j = *pos + 1;
	while (line[0][j] && line[0][j] != '$' && line[0][j] != ' '
	&& line[0][j] != '"' && line[0][j] != '\'')
		j++;
	tmp = ft_calloc(j - i, sizeof(char));
	ft_memcpy(tmp, &line[0][i + 1], j - i - 1);
	while (env && ft_strcmp(tmp, env->var[0]))
		env = env->next;
	free(tmp);
	if (!env)
		var_val = "";
	else
		var_val = env->var[1];
	tmp = ft_calloc(ft_strlen(var_val) + ft_strlen(*line) - j + i + 1,
	sizeof(char));
	ft_memcpy(tmp, *line, i);
	ft_memcpy(&tmp[i], var_val, ft_strlen(var_val));
	ft_memcpy(&tmp[i + ft_strlen(var_val)], &line[0][j],
	ft_strlen(&line[0][j]));
	free(*line);
	*line = tmp;
	*pos += ft_strlen(var_val) - 1;
}
