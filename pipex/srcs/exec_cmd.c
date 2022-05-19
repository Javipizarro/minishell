/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 05:33:34 by jpizarro          #+#    #+#             */
/*   Updated: 2022/03/05 20:32:23 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Executes the sub routine
*/

#include "../pipex.h"

void	exec_cmd(t_pipex_data *data, char *argv[], char *environ[], int i)
{
	char	*path;

	if (!(data->cmd = ft_split(argv[i + 2], ' ')))
		error_exit("Error while allocating memory for arguments");
	get_path(data->cmd[0], environ, &path);
	if (i == 0)
		dup2(data->infile, STDIN_FILENO);
	else
	{
		dup2(data->in_pipe[READ_END], STDIN_FILENO);
		close(data->in_pipe[READ_END]);
	}
	if (i == data->cmd_num - 1)
		dup2(data->outfile, STDOUT_FILENO);
	else
	{
		close(data->out_pipe[READ_END]);
		dup2(data->out_pipe[WRITE_END], STDOUT_FILENO);
		close(data->out_pipe[WRITE_END]);
	}
	execve(path, data->cmd, environ);
}