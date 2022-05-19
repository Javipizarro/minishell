/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 19:47:11 by jpizarro          #+#    #+#             */
/*   Updated: 2022/03/05 20:32:23 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Executes all the commands in row conecting to the previous one and
**	the next one.
*/

#include "../pipex.h"

void	exec_cmds(t_pipex_data *data, char *argv[], char *environ[])
{
	int		i;

	i = -1;
	while (++i < data->cmd_num)
	{
		if (i < data->cmd_num - 1)
			if (pipe(data->out_pipe) < 0)
				perror_exit("Error piping");
		data->pid = fork();
		if (data->pid < 0)
			perror_exit("Error forking");
		if (data->pid == 0)
			exec_cmd(data, argv, environ, i);
		if (i)
			close(data->in_pipe[READ_END]);
		if (i < data->cmd_num - 1)
		{
			data->in_pipe[READ_END] = data->out_pipe[READ_END];
			close(data->out_pipe[WRITE_END]);
		}
	}
	close(data->infile);
	close(data->outfile);

}