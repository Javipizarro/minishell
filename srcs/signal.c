/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:30:48 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/15 11:30:52 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_definition(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;	// Variable de salida de la minishell, habr'a que ver c'omo usarla.
//		printf("detectado SIGINT\n");
	}
	if (sig == SIGQUIT)
	{
//		printf("detectado SIGQUIT\n");
		signal(SIGQUIT, SIG_IGN);
	}	
}

//void	signal_handler(t_mini_data *data)
void	signal_handler(void)
{
	signal(SIGINT, signal_definition);
	signal(SIGQUIT, SIG_IGN);
//	signal(11, exit_shell(data));
}
