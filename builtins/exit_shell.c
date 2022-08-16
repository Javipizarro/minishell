/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:27:22 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/16 13:42:53 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks whether the exit arguments are correct and whether according to
**	them we can actually exit the shell.
*/

int	process_exit_arguments(char **cmd, int cmd_num, char *do_not_exit)
{
	int	i;

	if (!cmd[1] && cmd_num == 1 && !g_exit_status)
		return (256);
	if (!cmd[1] && cmd_num == 1 && !g_exit_status)
		return (g_exit_status);
	if (!cmd[1])
		return (256);
	i = -1;
	if (cmd[1][0] == '-' || cmd[1][0] == '+')
		i++;
	while (cmd[1][++i])
		if (!ft_isdigit(cmd[1][i]))
			return (manage_errors(cmd[0], NOINTARG, cmd[1]));
	if (cmd[2])
	{
		do_not_exit[0] = 1;
		return (manage_errors(cmd[0], TOOMARG, NULL));
	}
	return (ft_atoi(cmd[1]) % 256);
}

/*
**	Manages how the mini-shell is abandoned.
*/

int	exit_shell(t_mini_data *data, char **cmd, pid_t pid)
{
	char do_not_exit;

	do_not_exit = 0;
	if (pid && data->cmd_num > 1)
		return (CONTINUE);
	if (!pid)
		return (process_exit_arguments(cmd, data->cmd_num, &do_not_exit));
	write(2, "exit\n", 5);
	printf("do_not_print = %c\n", do_not_exit);
	if (do_not_exit)
		return (CONTINUE);
	wait(&data->err_exit);
	set_exit_status(data->err_exit);
	exit(g_exit_status);
}

/*
**	Checks whether the exit arguments are correct and whether according to
**	them we can actually exit the shell.
*/

//int	process_exit_arguments(char **cmd)
//{
//	int	i;
//
//	if (!cmd[1])
//		return (0);
//	i = -1;
//	if (cmd[1][0] == '-' || cmd[1][0] == '+')
//		i++;
//	while (cmd[1][++i])
//		if (!ft_isdigit(cmd[1][i]))
//		{
//			manage_errors(cmd[0], NOINTARG, cmd[1]);
//			return (0);
//		}
//	if (cmd[2])
//	{
//		manage_errors(cmd[0], TOOMARG, NULL);
//		return (CONTINUE);
//	}
//	g_exit_status = ft_atoi(cmd[1]) % 256;
//	return (0);
//}

/*
**	Manages how the mini-shell is abandoned.
*/

//int	exit_shell(t_mini_data *data, char **cmd, pid_t pid) //redo it
//{
////	if (!pid)
////	{
////		if (data->cmd_num > 1)
////			data->err_exit = KEEPGESTAT;
////		free_stuff(data);
////		return(data->err_exit);
////		//exit(data->err_exit);
////	}
//	if (pid && cmd && cmd[0] && data->cmd_num == 1)
//		write(2, "exit\n", 5);
//////
//	printf("data->cmd_num on exit = %i\n", data->cmd_num);
//	if (pid && cmd && cmd[0] && process_exit_arguments(cmd)
//	&& data->cmd_num > 1)
//	{
//		printf("entro en return(continue)\n");
//		return (CONTINUE);
//	}
////	if (data->cmd_num > 1)
////		return (KEEPGESTAT);
//	free_stuff(data);
//	if (pid)
//		restore_termattr(&data->termattr);
//	exit (g_exit_status);
//}
