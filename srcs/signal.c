/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:30:48 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/02 12:38:05 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_general(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	sig_exec(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = CMD_INTER;
}

void	sig_here_no_pid(int signal)
{
	(void)signal;
	g_exit_status = CMD_INTER;
	exit(CMD_INTER);
}

void	sig_here_pid(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	signal_handler(t_mini_data *data, int type, int pid)
{
	if (type == GENERAL)
	{
		turn_off_echoctl();
		signal(SIGINT, sig_general);
	}
	else if (type == EXEC)
	{
		signal(SIGINT, sig_exec);
		restore_termattr(&data->termattr);
	}
	else if (type == HEREDOC && !pid)
		signal(SIGINT, sig_here_no_pid);
	else if (type == HEREDOC && pid)
		signal(SIGINT, sig_here_pid);
	signal(SIGQUIT, SIG_IGN);
}
