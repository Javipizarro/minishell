/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:36:05 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/02 17:52:23 by jpizarro         ###   ########.fr       */
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
			token = APOUT;
		else
		token = OUT;
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
			token = HERE;
		else
		token = IN;
	}
	return (token);
}

/*
**	Parses the token at the beggining of the line, stores its value inthe cmd
**	structure, erases it form the line, and returns its value.
*/

char	tokenizer(char *line, t_cmds *cmd)
{
	int i;
	char token;

	if (line[0] != '<' && line[0] != '>')
		return (0);
	i = 1;
	if (line[0] == '<')
	{
		token = get_in_token(line[i]);
		cmd->tok_in = token;
	}
	if (line[0] == '>')
	{
		token = get_out_token(line[i]);
		cmd->tok_out = token;
	}
	if (line[1] == line[0])
		i++;
	while (line[i] == ' ')
		i++;
	ft_memcpy(line, &line[i], ft_strlen(&line[i] + 1));
	return (token);
}
