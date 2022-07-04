/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:45:46 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/04 17:41:03 by jpizarro         ###   ########.fr       */
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
//	printf("%s\n", cwd);
	free(cwd);
	cwd = NULL;
	return (CONTINUE);
}
