/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:54:58 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/19 14:48:02 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Opens the file for the heredoc to store the text, and closes it when
**	the keyword is found.
*/

void	open_heredoc(char *keyword)
{
	char	*line;
	int		fd;
	int		next;

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

/*
**	Activates the here_doc mode of entry information.
*/

int	heredoc(t_mini_data *data, char *path[])
{
	char	*keyword;
	int		pid;

	keyword = *path;
	*path = strdup(".heredoc");
	erase_quotes(keyword);
	pid = fork();
	if (pid < 0)
	{
		free(keyword);
		return (manage_errors(NULL, FORKING, NULL));
	}
	signal_handler(data, HEREDOC, pid);
	if (!pid)
		open_heredoc(keyword);
	wait(NULL);
	signal_handler(data, GENERAL, 0);
	free (keyword);
	return (0);
}
