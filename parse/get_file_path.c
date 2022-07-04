/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:20:24 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/04 15:08:50 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

/*
**	Expands the variables in path thar are not between quotes, and replaces
**	the name with the value.
**	Returns an error if there is any.
*/

int	expand_no_quo(char **path, int *pos, t_env *env)
{
	int i;
	int	j;
	char	*tmp;
	char	*var_val;
	
	i = *pos;
	j = *pos + 1;
	while (path[0][j] && path[0][j] != '$' && path[0][j] != ' '
	&& path[0][j] != '"' && path[0][j] != '\'')
		j++;
	tmp = ft_calloc(j - i, sizeof(char));
	ft_memcpy(tmp, &path[0][i + 1], j - i - 1);
	while (env && !ft_strcmp(tmp, env->var[0]))
		env = env->next;
	free(tmp);
	if (!env)
		var_val = "";
	else
		var_val = env->var[1];
	if (ft_strchr(var_val, ' '))
		return (AMBRED);
	tmp = ft_calloc(ft_strlen(var_val + ft_strlen(*path) - j + i + 1), 
	sizeof(char));
	ft_memcpy(tmp, *path, i);
	ft_memcpy(&tmp[i], var_val, ft_strlen(var_val));
	ft_memcpy(&tmp[i + ft_strlen(var_val)], &path[0][j], ft_strlen(&path[0][j]));
	free(*path);
	*path = tmp;
	*pos += ft_strlen(var_val);
	return (0);
}

// /*
// **	Expands the variables in path, and verifies whether everything is correct.
// */
//
// void	expand_path(char **path, t_mini_data *data)
// {
// 	int	i;
// 	char	quo;
//	
// 	i = -1;
// 	while (path[0][++i])
// 	{
// 		quotes_status(path[0][i], &quo);
// 		if (quo == '\'')
// 			continue;
// 		else if (!quo && path[0][i] == '$')
// 			data->err = expand_no_quo(path, &i,data->env);
// 		else if (quo || path[0][i] == '$')
// 			expand_var(path, &i, data->env);
// 		if (data->err)
// 			return;
// 	}
// }

/*
**	Takes the next characters string until the firs significative space,
**	expands its variables and search for anything that could be wrong.
**	Returns the string that contains the file path, or null if there has
**	been any problem.
*/

char	*get_file_path(char *line, t_mini_data *data)
{
	int	i;
	char	quo;
	char	*path;

	i = -1;
	quo = 0;
	while (line[++i])
	{
		quotes_status(line[i], &quo);
		if (quo)
			continue;
		if (line[i] == ' ' || line[i] == '<' || line[i] == '>')
			break;
	}
	path = ft_calloc(sizeof(char), i + 1);
	ft_memcpy(path, line, i);
	ft_memcpy(line, &line[i], ft_strlen(&line[i]) + 1);
	if (data->err)
		return(path);
//	erase_quotes(path);
	return(path);
}
