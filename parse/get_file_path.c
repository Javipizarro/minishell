/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:20:24 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/05 19:45:39 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (data->err_print)
		return(path);
	return(path);
}
