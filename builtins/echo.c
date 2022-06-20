/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:31:20 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/20 20:02:35 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	
*/

int	echo(char **cmd, int pid)
{
	int	i;
	char	flag;

	i = 0;
	flag = 0;
	if (!pid)
		return (CONTINUE);
	while (!ft_strcmp(cmd[++i], "-n"))
		flag = 'n';
	while (cmd[i])
	{
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if (cmd[++i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	return (CONTINUE);
}