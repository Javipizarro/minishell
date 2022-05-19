/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:53:09 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/19 17:38:42 by jpizarro         ###   ########.fr       */
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
	if (cmds->tipe == HERE || cmds->type == APOUT)
		return (2);
	else if (cmds->tipe == PIPE || cmds->tipe == IN || cmds->tipe == OUT)
		return (1);
	pritnf("parse_type() error: Error reading the type on %s\n", &line[i]);
	return (0);
}

/*
**	Creates a fresh malloced t_cmds structure to work with it.
**	Returns a pointer to it.
*/

t_cmds	*new_cmds()
{
	t_cmds	new;

	new = malloc(sizeof(t_cmds));
	new.type = 0;
	new.cmd = NULL;
	new.next = NULL;
	return (&new);
}


/*
**	Chops the line into its different commands and stores them into a t_cmds
**	structure along with the type of accition to take on that entry.
*/

int	line_to_cmds(t_mini_data *data)
{
	int	i;
	int	j;
	char	*cmd;
	t_cmds	**cmds;

	j = 0;
	cmds = &data->cmd;
	while (data->line[j])
	{
		i = j;
		cmds[0] = new_cmds();
		while (data->line[j] && data->line[j] != "|"
		&& data->line[j] != "<" && data->line[j] != ">")
			j++;
		i += parse_type(data->line, i, cmds[0]);
		cmd = ft_calloc(sizeof(char), j - i + 1);
		ft_memcpy(cmd, &data->line[i], j - i);
		cmds[0]->cmd = ft_split(cmd, ' ');
		free(cmd);
		cmd = NULL;
		cmds = &cmds[0]->next;
		if (data->line[j] == data->line[j + 1] && (data->line[j] == '<'
		|| data->line[j] == '>'))
			j++;
		j++;
	}
}