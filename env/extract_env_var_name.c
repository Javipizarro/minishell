/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env_var_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:55:52 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/27 17:22:09 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Cuts out from the string 'path', the name of the varible in
**	the possition 'pos'.
**	Allocates with malloc(3) enough memory and returns it as a string.
*/

char	*extract_env_var_name(char *line, int pos)
{
	int end;
	char *var_name;

	end = pos + 1;
	if ((line[end] == '?' || line[end] == '%' || line[end] == '^')
	&& !(ft_isalnum(line[end + 1]) || line[end + 1] == '_'))
		end++;
	else
		while (line[end] && (ft_isalnum(line[end]) || line[end] == '_'))
			end++;
	var_name = ft_calloc(end - pos + 1, sizeof(char));
	ft_memcpy(var_name, &line[pos], end - pos);
	ft_memcpy(&line[pos], &line[end], ft_strlen(&line[end] + 1));
	return (var_name);
}