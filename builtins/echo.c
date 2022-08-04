/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:31:20 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/03 19:15:34 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
**	Recognizes whether the 'str' string refers to a 'n' flag or it's a
**	a string that need to be printed.
**	Returns 1 if the 'str' is recognized as an 'n' flag or 0 otherwise.
*/

int	is_a_n_flag(char *str)
{
	int i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

/*
**	Mimics the behavior of the echo command, including the different
**	possibilities of the 'n' flag.
*/

int	echo(char **cmd, pid_t pid)
{
	int	i;
	char	flag;

	if (pid)
		return (manage_errors(cmd[0], CONTINUE, NULL));
	i = 0;
	flag = 0;
	while (is_a_n_flag(cmd[++i]))
		flag = 'n';
	while (cmd[i])
	{
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if (cmd[++i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	return (manage_errors(cmd[0], CONTINUE, NULL));
}
