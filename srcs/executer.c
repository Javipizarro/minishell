/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:23:54 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/03 12:41:45 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
**	Checks whether the command is empty and returns a corresponding error to
** 	avoid processing it, if it is.
*/

int	check_empty_cmd(t_cmds *cmd)
{
	if (cmd->avoid)
		return (CONTINUE);
	else if (!cmd->cmd)
		return (CMDERR);
	else if (!cmd->cmd[0])
		return (CMDERR);
	return (0);
}

/*
**	Sets a pipe between the current cmd and the next one if there
**	is any, and fd_out is not set in the current one and fd_in is not
**	set for the next one.
*/

int	piper(t_cmds *cmd)
{
	if (cmd->next)
		if (pipe(cmd->next->pipe))
			return (manage_errors(NULL, PIPING, NULL));
	return (0);
}

/*
**	Checks the fd_in and fd_out exist in the cmd structure and sets
**	sets stdin and stdout if they do.
*/

int	set_inoutputs(t_cmds *cmd, int i)
{
	if (cmd->fd_in == NOSET && i)
	{
		if (dup2(cmd->pipe[OUT], STDIN_FILENO) < 0)
			return (manage_errors(NULL, DUPING, NULL));
	}
	else if (cmd->fd_in >= 0)
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			return (manage_errors(NULL, DUPING, NULL));
	if (cmd->next && cmd->fd_out == NOSET)
	{
		if (dup2(cmd->next->pipe[IN], STDOUT_FILENO) < 0)
			return (manage_errors(NULL, DUPING, NULL));
	}
	else if (cmd->fd_out >= 0)
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (manage_errors(NULL, DUPING, NULL));
	return (0);
}

/*
**	
*/

void	close_fds(t_cmds *cmd, pid_t pid, int i)
{
	if (i)
		close(cmd->pipe[OUT]);
	if (cmd->next)
		close(cmd->next->pipe[IN]);
	if (cmd->next && !pid)
		close(cmd->next->pipe[OUT]);
	if (cmd->fd_in >= 0)
	{
		if (cmd->tok_in == TOKHERE && pid)
			unlink(".heredoc");
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
}

/*
**	Checks whether the command is a built-in or an external command and
**	executes it with its in_fd and out_fd.
*/

void	executer(t_mini_data *data, t_cmds	**cmds)
{
	pid_t	pid;
	int i;
	
	i = 0;
	while (cmds[0])
	{
		data->err = piper(*cmds);
		if(data->err)
			break;
		pid = fork();
		if (pid < 0)
		{
			data->err = manage_errors(NULL, FORKING, NULL);
			break;
		}
		if (!pid)
			data->err = set_inoutputs(cmds[0], i);
		close_fds(cmds[0], pid, i);
//////
//	printf("cmd = %s cmd->fd_in = %i\n", cmds[0]->cmd[0], cmds[0]->fd_in);
//	printf("cmd = %s cmd->fd_out = %i\n", cmds[0]->cmd[0],cmds[0]->fd_out);
		if(!data->err)
			data->err = check_empty_cmd(cmds[0]);
		if(!data->err)
			data->err = builtiner(cmds[0]->cmd, data, pid);
		if (!pid && !data->err)
			data->err = external(cmds[0], data);
		if (!pid)
			exit_shell(data, NULL, pid);
		cmds = &cmds[0]->next;
		i++;
	}
	i = 0;
	while (i < data->cmd_num && ++i)
	{
		wait(&data->err);
		if (data->err == 2)
			data->err = manage_errors(NULL, CMD_INTER, NULL);
		else if (data->err < CMD_INTER)
			data->err = manage_errors(NULL, data->err, NULL);
		else
			data->err = manage_errors(NULL, data->err / 256, NULL);
		if (data->err == 256)
			g_exit_status = 1;
	}
}
