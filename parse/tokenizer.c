/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:36:05 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/19 17:25:56 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Searches for an exit token.
**	Returns the token.
*/

char	get_out_token(char *line)
{
	char	token;

	token = 0;
	if (line[0] == '>')
	{
		if (line[1] == line[0])
			token = TOKAPPN;
		else
		token = TOKOUT;
	}
	return (token);
}

/*
**	Searches for an entry token.
**	Returns the token.
*/

char	get_in_token(char *line)
{
	char	token;

	token = 0;
	if (line[0] == '<')
	{
		if (line[1] == line[0])
			token = TOKHERE;
		else
		token = TOKIN;
	}
	return (token);
}

/*
**	Parses the token at the beggining of the line, stores its value in the cmd
**	structure, erases it form the line, and returns its value.
*/

char	tokenizer(char *line, t_cmds *cmd)
{
	int		i;
	char	token;

	if (line[0] != '<' && line[0] != '>')
		return (0);
	i = 1;
	if (line[0] == '<')
	{
		token = get_in_token(&line[0]);
		cmd->tok_in = token;
	}
	if (line[0] == '>')
	{
		token = get_out_token(&line[0]);
		cmd->tok_out = token;
	}
	if (line[1] == line[0])
		i++;
	while (line[i] == ' ')
		i++;
	ft_memcpy(line, &line[i], ft_strlen(&line[i]) + 1);
	return (token);
}

/*
**	Searches the next token from the i position in line and returns it.
*/

char	next_token(char *line, t_cmds *cmd, char *token, int *i)
{
	char	quo;

	*i = -1;
	quo = 0;
	*token = 0;
	while (line[++*i])
	{
		quotes_status(line[*i], &quo);
		if (quo)
			continue ;
		if (line[*i] == '<' || line[*i] == '>')
			*token = tokenizer(&line[*i], cmd);
		if (*token)
			break ;
	}
	return (*token);
}
