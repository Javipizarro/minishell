/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:45:46 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/13 18:05:50 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Prints the current working directory.
*/

int	pwd(pid_t pid)
{
	char	*cwd;

	if (pid)
		return (CONTINUE);
	cwd = getcwd(NULL, 0);
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	cwd = NULL;
	return (manage_errors(CONTINUE, NULL));
}
