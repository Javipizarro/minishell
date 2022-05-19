/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:49:50 by jpizarro          #+#    #+#             */
/*   Updated: 2022/03/02 06:22:45 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	 Ininitiates a pipex_data structure.
*/

#include "../pipex.h"

void	pipex_data_init(t_pipex_data *data)
{
	data->cmd_num = 0;
	data->cmd = NULL;
	data->infile = 0;
	data->outfile = 0;
	data->in_pipe[0] = -1;
	data->in_pipe[1] = -1;
	data->out_pipe[0] = 0;
	data->out_pipe[1] = 0;
	data->pid = 0;
}
