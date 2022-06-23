/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:54:58 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/23 13:46:04 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_here(int signal)
{
	(void)signal;
	printf("\n");
	exit(g_exit_status);
}

//int	get_heredoc_line(int fd, char *keyword)
//{
//	char	*here_line;
//	int	new_line;
//
//	here_line = readline("> ");
//	new_line = ft_strcmp(keyword, here_line);
//	if (new_line)
//	{
//		write(fd, here_line, ft_strlen(here_line));
//		write(fd, "\n", 1);
//	}
//	free(here_line);
//	here_line = NULL;
//	return (new_line);
//}
//
//
//int	heredoc(char *path[])
//{
//	char	*keyword;
//	int	fd;
//	int	pid;
//
//	pid = fork();
//	if (pid < 0)
//		return (FORKING);
//	signal(SIGINT, SIG_IGN);
//	keyword = *path;
//	*path = strdup(".heredoc");
//	if (!pid)
//	{
//		fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
//		signal(SIGINT, sig_here);
//		while (get_heredoc_line(fd, keyword))
//			continue;
////		while (get_heredoc_line(fd, keyword))
////			signal(SIGINT, sig_here);
//		close(fd);
//		exit(0);
//	}
//	return (0);
//}

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
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		signal(SIGINT, sig_here);
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
	signal_handler();
	free (keyword);
	return (0);
}
