/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtiner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:10:43 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/19 17:03:03 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks whether the cmd is a built-in command and executes it if it is.
**	Returns one on possitive result, and 0 on negative.
*/

//int	builtiner(t_mini_data *data) //Habrá que modificarlos para que lean de fds!!!!
//{
//	if (!ft_strcmp(data->cmd[0], "cd"))
//		printf("%s command is a work in progress right now\n", data->cmd[0]);
//	else if (!ft_strcmp(data->cmd[0], "echo"))
//		printf("%s command is a work in progress right now\n", data->cmd[0]);
//	else if (!ft_strcmp(data->cmd[0], "env"))
//		return(!env(data->envp));
//	else if (!ft_strcmp(data->cmd[0], "exit"))
//		exit_shell(data);
//	else if (!ft_strcmp(data->cmd[0], "export"))
//		return (export(data->cmd, data));
//	else if (!ft_strcmp(data->cmd[0], "pwd"))
//		return(!pwd());
//	else if (!ft_strcmp(data->cmd[0], "unset"))
//		return (unset(data));
//	return (0);
//}
int	builtiner(t_mini_data *data, char **cmd) //Habrá que modificarlos para que lean de fds!!!!
{
	if (!ft_strcmp(cmd[0], "cd"))
		printf("%s command is a work in progress right now\n", cmd[0]);
	else if (!ft_strcmp(cmd[0], "echo"))
		printf("%s command is a work in progress right now\n", cmd[0]);
	else if (!ft_strcmp(cmd[0], "env"))
		return(!env(data->envp));
	else if (!ft_strcmp(cmd[0], "exit"))
		exit_shell(data);
	else if (!ft_strcmp(cmd[0], "export"))
		return (export(cmd, data));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return(!pwd());
	else if (!ft_strcmp(cmd[0], "unset"))
		return (unset(data));
	return (0);
}

int	executer(t_mini_data *data)
{
//	builtiner(data); // Valorar el pasar struct cmd y envp en vez de data para trabajar con el comando que estemos en ese momento.
	builtiner(data, data->cmd->cmd); // Valorar el pasar struct cmd y envp en vez de data para trabajar con el comando que estemos en ese momento.
	
}
