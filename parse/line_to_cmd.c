/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:53:09 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/04 11:33:47 by jpizarro         ###   ########.fr       */
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

void	line_to_cmds(t_mini_data *data, t_cmds	**cmd)
{
	int	i;
	char	**cmds;

	cmds = split_by_pipes(data->line);
	i = -1;
	while (cmds[++i])
	{
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

/////////////////////// OLD FUNCTION ->
//	j = 0;
//	i = 0;
//	cmds = &data->cmds;
//	while (data->line[j])
//	{
//		cmds[0] = new_cmds();
//		while (data->line[j] && data->line[j] != '|'
//		&& data->line[j] != '<' && data->line[j] != '>')
//			j++;
//		i += parse_type(data->line, i, cmds[0]);
//		cmd = ft_calloc(sizeof(char), j - i + 1);
//		ft_memcpy(cmd, &data->line[i], j - i);
//		cmds[0]->cmd = ft_split(cmd, 31);
//		free(cmd);
//		cmd = NULL;
//		if (!cmds[0]->cmd[0])
//			return (1);
//		cmds = &cmds[0]->next;
//		i = j;
//		if (data->line[j] == data->line[j + 1] && (data->line[j] == '<'
//		|| data->line[j] == '>'))
//			j++;
//		j++;
//	}
//	return (0);
//}
