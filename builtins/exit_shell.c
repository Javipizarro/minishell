/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:27:22 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/06 18:36:34 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
//	if (!pid)
//	{
//		if (data->cmd_num > 1)
//			data->err_exit = KEEPGESTAT;
//		free_stuff(data);
//		return(data->err_exit);
//		//exit(data->err_exit);
//	}
	if (pid && cmd && cmd[0] && data->cmd_num == 1)
		write(2, "exit\n", 5);
	if (pid && cmd && cmd[0] && process_exit_arguments(cmd))
		return (CONTINUE);
	if (data->cmd_num > 1)
		return (KEEPGESTAT);
	free_stuff(data);
	restore_termattr(&data->termattr);
	exit (g_exit_status);
}
