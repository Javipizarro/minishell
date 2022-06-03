/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:53:20 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/03 12:12:00 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks whether we are opening or closing quotes and erase them
**	from the "line" string.
*/

void	erase_quotes(char *line)
{
	int i;
	char	quo;

	i = -1;
	quo = 0;
	while (line[++i])
	{
		if ((line[i] == '"' || line[i] == '\'') && (!quo || line[i] == quo))
		{
			if (!quo)
				quo = line[i];
			else
				quo = 0;
			ft_memcpy(line[i], line[i + 1], ft_strlen(&line[i]));
		}
	}
}

/*
**	Checks whether we are opening or closing quotes.
**	Returns 
*/

void	quotes_status(char c, char *quo)
{
	if ((c == '"' || c == '\'') && (!*quo || c == *quo))
	{
		if (!*quo)
			*quo = c;
		else
			*quo = 0;
	}
}

/*
**	Checks whether the line has open quotes.
**	Returns 1 if it does.
*/

int	check_open_quotes(char *line)
{
	int i;
	char	quo;

	i  = 0;
	quo = 0;
	while (line[i])
	{
		quotes_status(line[i], &quo);
		i++;
	}
	if (quo)
		return (1);
	return (0);
}