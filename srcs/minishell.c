/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:37:03 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/19 14:36:13 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Manages the Crl + D signal.
*/

void	ctrl_d(t_mini_data *data)
{
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[11C", STDOUT_FILENO);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_shell(data, NULL, 1);
}

/*
**	Frees and anulates what is needed for a fresh main minishell loop.
*/

void	reset_data(t_mini_data *data)
{
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->cmds)
		free_cmds(&data->cmds);
	data->cmds = NULL;
	data->cmd_num = 0;
	data->err_print = 0;
}

/*
**	Initializes the minishell and runs the main loop.
*/

int	main(int argc, char *argv[], char *envp[])
{
	t_mini_data	data;

	(void)argc;
	(void)argv;
	init_mini_data(&data);
	set_env_list(envp, &data);
	backup_termattr(&data.termattr);
	signal_handler(&data, GENERAL, 0);
	while (1)
	{
		reset_data(&data);
		data.line = readline(SHNAME "> " );
		if (!data.line)
			ctrl_d(&data);
		data.err_print = parser(&data);
		if (!data.err_print)
		{
			signal_handler(&data, EXEC, 0);
			executer(&data, &data.cmds);
			signal_handler(&data, GENERAL, 0);
		}
	}
	return (0);
}
