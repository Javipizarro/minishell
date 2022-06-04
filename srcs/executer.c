/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:23:54 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/05 00:16:55 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks the fd_in and fd_out exist in the cmd structure and sets
**	sets stdin and stdout if they do.
**	Also sets a pipe between the current cmd and the next one if there
**	is any, and fd_out is not set in the current one and fd_in is not
**	set for the next one.
*/

int	piper(t_cmds *cmd)
{
	if (cmd->fd_in >= 0)
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (DUPING);
	if (cmd->fd_out >= 0)
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (DUPING);
	if (cmd->fd_out == NOSET && cmd->next && cmd->next->fd_in == NOSET)
	{
		if (pipe(cmd->next->pipe))
			return (PIPING);
		if (dup2(cmd->next->pipe[IN], STDOUT_FILENO) < 0)
			return (DUPING);
		cmd->next->fd_in = PIPED;
	}
	if (cmd->fd_in == PIPED)
		if (dup2(cmd->pipe[OUT], STDIN_FILENO) < 0)
			return (DUPING);
		return (0);
}

/*
**	Checks whether the command is a built-in or an external command and
**	executes it with its in_fd and out_fd.
*/

int	executer(t_mini_data *data, t_cmds	**cmds)
{
	while (cmds[0])
	{
		data->err = piper(cmds[0]);
		if(data->err)
			break;
		if(!builtiner(cmds[0]->cmd, data))
			data->err = external(cmds[0], data);
		if (data->err)
			break;
		cmds = &cmds[0]->next;
	}
	return (0);
}