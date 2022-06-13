/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:53:09 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/10 16:30:02 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	new->fd_in = NOSET;
	new->fd_out = NOSET;
	new->pipe[IN] = 0;
	new->pipe[OUT] = 0;
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

void	line_to_cmds(t_mini_data *data, t_cmds	**cmd)
{
	int	i;
	char	**cmds;

	cmds = split_by_pipes(data->line);
	i = -1;
	while (cmds[++i])
	{
		data->cmd_num++;
		*cmd = new_cmd();
		parse_files(cmds[i], *cmd, data);
		if (data->err)
			break;
		parse_cmd(&cmds[i], *cmd, data);
		if (data->err)
			break;
	}
	ft_free_split(cmds);
}
