/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:54:58 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/30 20:30:12 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Activates the here_doc mode of entry information.
*/

int	heredoc(char *path[])
{
	char	*keyword;
	char	*line;
	int	fd;
	int	next;
	int	pid;


	keyword = *path;
	*path = strdup(".heredoc");
	pid = fork();
	if (pid < 0)
	{
		free(keyword);
		return (FORKING);
	}
	signal_handler(HEREDOC, pid);
	if (!pid)
	{
		fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		next = 1;
		while (next)
		{
			line = readline("> ");
			next = ft_strcmp(keyword, line);
			if (next)
			{
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
			}
			free(line);
			line = NULL;
		}
		close (fd);
		exit (0);
	}
	wait(NULL);
	signal_handler(GENERAL, 0);
	free (keyword);
	return (0);
}
