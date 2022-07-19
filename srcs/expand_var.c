/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:03:23 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/19 12:21:29 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Expands the variable in the possition 'pos' in 'line'. Modifies 'pos' to
**	point at the end of the expanded var.
*/

//int	expand_var(char **line, int *pos, t_env *env, int check_spaces)
void	expand_var(char **line, int *pos, t_env *env)
{
	int i;
	int	j;
	char	*tmp;
	char	*var_val;

	i = *pos;
	j = *pos + 1;
	while (line[0][j] && (ft_isalnum(line[0][j]) || line[0][j] == '_'))
		j++;
	tmp = ft_calloc(j - i, sizeof(char));
	ft_memcpy(tmp, &line[0][i + 1], j - i - 1);
	env = *search_env(tmp, &env);
	if (!env && !ft_strcmp(tmp, "?"))
		var_val = ft_itoa(g_exit_status);
	else if (!env && !tmp[0])
		var_val = "$";
	else if (!env)
		var_val = "";
//		var_val = "''";
	else
		var_val = env->var[1];
	free(tmp);
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
