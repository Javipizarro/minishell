/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 19:56:25 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/07 18:49:37 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>	// For open, close...
# include <fcntl.h>		// For O_RDONLY and those flags
# include <sys/wait.h>

# define READ_END	0
# define WRITE_END	1

typedef struct s_pipex_data
{
	int			cmd_num;
	char		**cmd;
	int			infile;
	int			outfile;
	int			in_pipe[2];
	int			out_pipe[2];
	pid_t		pid;
}			t_pipex_data;

void	check_argc(int argc);
void	pipex_data_init(t_pipex_data *data);
void	error_exit(char *str);
void	exec_cmd(t_pipex_data *data, char *argv[], char *environ[], int i);
void	exec_cmds(t_pipex_data *data, char *argv[], char *environ[]);
char	*get_env_path(char *environ[]);
void	get_files(int argc, char *argv[], t_pipex_data *data);
void	get_path(char *cmd, char *environ[], char **path);
void	perror_exit(char* str);

#endif