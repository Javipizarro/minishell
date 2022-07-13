/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:23:54 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/12 19:48:10 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_cmds *cmd)
{
	if (cmd->fd_in == PIPED)
		close(cmd->pipe[OUT]);
	else if (cmd->fd_in >= 0)
	{
		if (cmd->tok_in == TOKHERE)
			unlink(".heredoc");
		close(cmd->fd_in);
	}
	if (cmd->fd_out == PIPED)
		close(cmd->next->pipe[IN]);
	else if (cmd->fd_out >= 0)
		close(cmd->fd_out);
}

/*
**	Skips the current command in in the case it's not usefull.
**	Closes the fds related to it.
*/

void	skip_cmd(t_cmds **cmds)
{
	close_fds(cmds[0]);
	cmds = &cmds[0]->next;
}

/*
**	Sets a pipe between the current cmd and the next one if there
**	is any, and fd_out is not set in the current one and fd_in is not
**	set for the next one.
*/

int	piper(t_cmds *cmd)
{
	if (cmd->fd_out == NOSET && cmd->next && cmd->next->fd_in == NOSET)
	{
		if (pipe(cmd->next->pipe))
			return (PIPING);
		cmd->fd_out = PIPED;
		cmd->next->fd_in = PIPED;
	}
	return (0);
}

/*
**	Checks the fd_in and fd_out exist in the cmd structure and sets
**	sets stdin and stdout if they do.
*/

int	set_inoutputs(t_cmds *cmd)
{
	if (cmd->fd_in == PIPED)
	{
		if (dup2(cmd->pipe[OUT], STDIN_FILENO) < 0)
			return (DUPING);
		close(cmd->pipe[OUT]);
	}
	else if (cmd->fd_in >= 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (DUPING);
		close(cmd->fd_in);
	}
	if (cmd->next && cmd->fd_out == PIPED)
	{
		close(cmd->next->pipe[OUT]);
		cmd->next->pipe[OUT] = NOSET;
		if (dup2(cmd->next->pipe[IN], STDOUT_FILENO) < 0)
			return (DUPING);
		close(cmd->next->pipe[IN]);
	}
	else if (cmd->fd_out >= 0)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (DUPING);
		close(cmd->fd_out);
	}
	return (0);
}

/*
**	Checks whether the command is a built-in or an external command and
**	executes it with its in_fd and out_fd.
*/

void	executer(t_mini_data *data, t_cmds	**cmds)
{
	pid_t	pid;

	while (cmds[0])
	{
		if (cmds[0]->cmd[0] && !ft_strcmp(cmds[0]->cmd[0], "exit"))
			exit_shell(data, 1);
		data->err = piper(*cmds);
		if(data->err)
			break;
		pid = fork();
////
//	printf("punto de control 0 pid = %i\n", pid);
		if (pid < 0)
		{
			data->err = FORKING;
			break;
		}
		if (!pid)
			data->err = set_inoutputs(cmds[0]);
////
//	printf("punto de control 1 pid = %i\n", pid);
		if(!data->err)
			data->err = builtiner(cmds[0]->cmd, data, pid);
////
//	printf("punto de control 2 pid = %i\n", pid);
		if (!pid && !data->err)
			data->err = external(cmds[0], data);
		close_fds(cmds[0]);
		if (!pid)
			exit_shell(data, pid);
		if (data->child_err > data->err)
			data->err = data->child_err;
		if (data->err && data->err != CONTINUE)
			break;
		cmds = &cmds[0]->next;
	}
	int i = 0;
	while (i < data->cmd_num && ++i)
	{
		wait(&data->child_err);
		if (data->child_err == 2)
			data->err = CMD_INTER;
		else if (data->child_err > data->err)
			data->err = data->child_err / 256;
		
	}
////
//	printf("salgo de executer\n");
}
