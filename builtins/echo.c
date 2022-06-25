/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihorcada <ihorcada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:31:20 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/25 17:19:06 by ihorcada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	
*/

int	echo(char **cmd, int pid)
{
	int		i;
	char	flag;
	int		k;

	k = 0;
	i = 0;
	flag = 0;
	if (!pid)
		return (CONTINUE);
	while (cmd[++i] && cmd[i][k] == '-')
	{
		while (cmd[i][++k] == 'n')
			continue ;
		if (cmd[i][k] == '\0')
			flag = 'n';
		else
			break ;
		k = 0;
	}
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
