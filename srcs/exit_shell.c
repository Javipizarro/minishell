/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:27:22 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/26 09:43:26 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Liberates the cmds chain.
*/

void	free_cmds(t_cmds **cmds)
{
	if (cmds[0]->next)
		free_cmds(&cmds[0]->next);
	if (cmds[0]->cmd)
		ft_free_split(cmds[0]->cmd);
	if (cmds[0]->fd_in == PIPED)
		close(cmds[0]->pipe[IN]);
	if (cmds[0]->fd_in == PIPED)
		close(cmds[0]->pipe[OUT]);
	if (cmds[0]->fd_in >= 0)
		close(cmds[0]->fd_in);
	if (cmds[0]->fd_out >= 0)
		close(cmds[0]->fd_out);
	cmds[0]->tok_in = 0;
	cmds[0]->tok_out = 0;
	free(cmds[0]);
	cmds[0] = NULL;
}

/*
**	Liberates the env chain.
*/

void	free_env(t_env **env)
{
	if (env[0]->next)
		free_env(&env[0]->next);
	ft_free_split(env[0]->var);
	free(env[0]);
	env[0] = NULL;
}

/*
**	Frees everything to exit without leaks.
*/

void	free_stuff(t_mini_data *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->cmds)
		free_cmds(&data->cmds);
	ft_free_split(data->envp);
	data->envp = NULL;
	rl_clear_history();
	free_env(&data->env);

}

/*
**	Checks whether the exit arguments are correct and whether according to
**	them we can actually exit the shell.
*/

int	process_exit_arguments(char **cmd)
{
	int	i;

	if (!cmd[1])
		return (0);
	i = -1;
	if (cmd[1][0] == '-' || cmd[1][0] == '+')
		i++;
	while (cmd[1][++i])
		if (!ft_isdigit(cmd[1][i]))
		{
			manage_errors(cmd[0], NOINTARG, cmd[1]);
			return (0);
		}
	if (cmd[2])
	{
		manage_errors(cmd[0], TOOMARG, NULL);
		return (CONTINUE);
	}
	g_exit_status = ft_atoi(cmd[1]) % 256;
	return (0);
}

/*
**	Manages how the mini-shell is abandoned.
*/

int	exit_shell(t_mini_data *data, char **cmd, pid_t pid) //redo it
{
	if (data->cmd_num > 1 && pid)
		return (CONTINUE);
	if (pid && cmd && cmd[0])
		write(2, "exit\n", 5);
	if (pid > 0 && cmd && cmd[0] && process_exit_arguments(cmd))
		return (CONTINUE);
	free_stuff(data);
	if (!pid)
		exit(data->err);
	restore_termattr(&data->termattr);
	exit (g_exit_status);
}
