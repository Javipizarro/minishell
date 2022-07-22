/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:56:11 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/21 16:58:50 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks whether there are any wrong place token.
*/

int	check_tokens(char *line)
{
	int	i;
	char quo;
	char token;

	i = ft_strlen(line) - 1;
	if (line[0] == '|' || line[i] == '|' || line[i] == '>' || line[i] == '<')
		return (1);
	i = -1;
	quo = 0;
	token = 0;
	while (line[++i])
	{
		quotes_status(line[i], &quo);
		if (quo || (line[i] != '|' && line[i] != '<' && line[i] != '>'))
		{
			if (token && line[i] != ' ')
				token = 0;
			continue;
		}
		if ((line[i] == '<' || line[i] == '>') && line[i] == line[i + 1])
			i++;
		if (token && (line[i] == '|' || token != '|'))
			return (1);
		else
			token = line[i];
	}
	return (0);
}


/*
**	Trims all the unnecessary spaces from the line for parsing it.
*/

void	trim_spaces(char *line)
{
	int i;
	char	quo;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (i)
		ft_memcpy(&line[0], &line[i], ft_strlen(&line[i]) + 1);
	i = 0;
	quo = 0;
	while (line[i])
	{
		quotes_status(line[i], &quo);
		if (!quo && line[i] == ' ' && line[i + 1] == ' ')
		{
			ft_memcpy(&line[i], &line[i + 1], ft_strlen(&line[i]));
			continue;
		}
		i++;
	}
	while (line[--i] == ' ')
		line[i] = 0;
}


/*
**	From the info in 'data->line', it arranges the commands in it
**	and stores them in the 'data->cmds' t_cmds structure to
**	execute them later.
**	Returns 0 if the commands can be passed or a value related with
**	the issue found if there is any.
*/

int	parser(t_mini_data *data)
{
	if (!data->line || !data->line[0])
		return (CONTINUE);
	add_history(data->line);
	trim_spaces(data->line);
	if (!data->line[0])
		return (CONTINUE);
	if (check_open_quotes(data->line))
		return (manage_errors(NULL, QUOTERR, NULL));
	if (check_tokens(data->line))
		return (manage_errors(NULL, TOKERR, NULL));
	line_to_cmds(data, &data->cmds);
	if (data->err)
		return (data->err);
	return (0);
}
