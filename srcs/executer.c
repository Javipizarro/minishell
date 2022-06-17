/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:23:54 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/16 19:40:25 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_cmds *cmd)	// Some parts must be done by the father
{
	if (cmd->fd_in == PIPED)
		close(cmd->pipe[OUT]);
	else if (cmd->fd_in >= 0)
		close(cmd->fd_in);
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
	if (cmd->fd_out == NOSET && cmd->next && cmd->next->fd_in == NOSET
	&& ft_strcmp(cmd->next->cmd[0], "exit"))
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
	if (cmd->fd_out == PIPED)
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
//		close(cmd->fd_out);
	}
	return (0);
}

/*
**	Checks whether the command is a built-in or an external command and
**	executes it with its in_fd and out_fd.
*/

void	executer(t_mini_data *data, t_cmds	**cmds)
{
	int	pid;

	while (cmds[0])
	{
		if (!ft_strcmp(cmds[0]->cmd[0], "exit") && exit_shell(data, 1)
		== CONTINUE)
			skip_cmd(cmds);
		data->err = piper(*cmds);
		if(data->err)
			break;
		pid = fork();
		if (pid < 0)
		{
			data->err = FORKING;
			break;
		}
		if (!pid)
		{
			data->err = set_inoutputs(cmds[0]);
			if(!data->err)
				data->err = builtiner(cmds[0]->cmd, data);
			if (!data->err)
				data->err = external(cmds[0], data);
			close_fds(cmds[0]);
			exit_shell(data, pid);
		}
		wait(&data->err);
		close_fds(cmds[0]);
		if (data->err && data->err != CONTINUE)
			break;
		cmds = &cmds[0]->next;
	}
}

//int	executer(t_mini_data *data, t_cmds	**cmds)
//{
//	int	pid;
//
//	while (cmds[0])
//	{
//		pid = fork();
//		if (pid < 0)
//			return(FORKING);
//		if (pid == 0)
//		{
//			data->err = piper(*cmds);
//			if(data->err)
//				break;
//			data->err = builtiner(cmds[0]->cmd, data);
//			if (!data->err)
//				data->err = external(cmds[0], data);
//			if (cmds[0]->fd_in == PIPED)
//				close(cmds[0]->pipe[OUT]);
//			else if (cmds[0]->fd_in >= 0)
//				close(cmds[0]->fd_in);
//			if (cmds[0]->next && cmds[0]->next->fd_in == PIPED)
//				close(cmds[0]->next->pipe[IN]);
//			else if (cmds[0]->fd_out >= 0)
//				close(cmds[0]->fd_out);
//			if (data->err && data->err != CONTINUE)
//				break;
//			exit_shell(data);
//	//	kill(pid, SIGKILL);
//		}
//		cmds = &cmds[0]->next;
//		wait(NULL);	//Hay que darle el puntero donde pueda almacenar el estado de salida del proceso hijo
//	if (pid > 0)
//		kill(pid, SIGKILL);
//	}
//	return (0);
//}