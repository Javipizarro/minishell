/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:53:09 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/03 10:03:38 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Parses the line where the type simbol(s) are (<, >, |, <<, >>) and returns
**	the equivalent value to store it in the t_cmds structure.
*/

char	parse_type(char *line, int i, t_cmds *cmds)
{
	if (!i)
	{
		cmds->type = PIPE;
		return (0);
	}
	else if (line[i] == '|')
		cmds->type = PIPE;
	else if (line[i] == '<' && line[i + 1] == '<')
		cmds->type = HERE;
	else if (line[i] == '<')
		cmds->type = IN;
	else if (line[i] == '>' && line[i + 1] == '>')
		cmds->type = APOUT;
	else if (line[i] == '>')
		cmds->type = OUT;
	if (cmds->type == HERE || cmds->type == APOUT)
		return (2);
	else if (cmds->type == PIPE || cmds->type == IN || cmds->type == OUT)
		return (1);
	printf("parse_type() error: Error reading the type on %s\n", &line[i]);
	return (0);
}

/*
**	Creates a fresh malloced t_cmds structure to work with it.
**	Returns a pointer to it.
*/

t_cmds	*new_cmd()
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	new->tok_in = 0;
	new->tok_out = 0;
	new->fd_in = -1;
	new->fd_out = -1;
	new->cmd = NULL;
	new->next = NULL;
	return (new);
}

/*
**	In the line received, it looks for valid pipes that splits this line into
**	different commands and stores them into a string array.
**	It returns the pointer to this string array.
*/

char	**split_by_pipes(char *line)
{
	int i;
	char	quo;

	i = -1;
	quo = 0;
	while (line[++i])
	{
		quotes_status(line[i], &quo);
		if (!quo && line[i] == '|')
			line[i] = 29;
	}
	return (ft_split(line, 29));
}

/*
**	Chops the line into its different commands and stores them into a t_cmds
**	structure along with the type of accition to take on that entry.
*/

int	line_to_cmds(t_mini_data *data, t_cmds	**cmd)
{
	int	i;
//	int	j;
	char	**cmds;

	cmds = split_by_pipes(data->line);
	i = -1;
	while (cmds[++i])
	{
		cmd = &new_cmd();
		parse_files(cmds[i], *cmd, data); // <- in progress

		trim_spaces(cmds[i]);

	}


/////////////////////// OLD FUNCTION ->
	j = 0;
	i = 0;
	cmds = &data->cmds;
	while (data->line[j])
	{
		cmds[0] = new_cmds();
		while (data->line[j] && data->line[j] != '|'
		&& data->line[j] != '<' && data->line[j] != '>')
			j++;
		i += parse_type(data->line, i, cmds[0]);
		cmd = ft_calloc(sizeof(char), j - i + 1);
		ft_memcpy(cmd, &data->line[i], j - i);
		cmds[0]->cmd = ft_split(cmd, 31);
		free(cmd);
		cmd = NULL;
		if (!cmds[0]->cmd[0])
			return (1);
		cmds = &cmds[0]->next;
		i = j;
		if (data->line[j] == data->line[j + 1] && (data->line[j] == '<'
		|| data->line[j] == '>'))
			j++;
		j++;
	}
	return (0);
}
