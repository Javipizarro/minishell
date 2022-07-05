/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:30:48 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/04 19:13:30 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_general(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	sig_exec(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 1;
}

void	sig_here_no_pid(int signal)
{
	(void)signal;
	exit(g_exit_status);
}

void	sig_here_pid(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	signal_handler(int type, int pid)
{
	if (type == GENERAL)
		signal(SIGINT, sig_general);
	else if (type == EXEC)
		signal(SIGINT, sig_exec);
	else if (type == HEREDOC && !pid)
		signal(SIGINT, sig_here_no_pid);
	else if (type == HEREDOC && pid)
		signal(SIGINT, sig_here_pid);
	signal(SIGQUIT, SIG_IGN);
}
