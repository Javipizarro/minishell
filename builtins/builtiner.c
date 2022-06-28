/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtiner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:10:43 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/28 13:40:46 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks whether the cmd is a built-in command and executes it if it is.
**	Returns one on possitive result, and 0 on negative.
*/

int	builtiner(char **cmd, t_mini_data *data, pid_t pid)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (cd(data, cmd, pid));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (echo(cmd, pid));
	else if (!ft_strcmp(cmd[0], "env"))
		return(env(data->envp, pid));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (exit_shell(data, 1));
	else if (!ft_strcmp(cmd[0], "export"))
		return (export(cmd, data, pid));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return(pwd(pid));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (unset(cmd, data, pid));
	return (0);
}
