/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 05:28:48 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/07 18:49:37 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int		main(int argc, char *argv[], char *environ[])
{
	t_pipex_data	data;

	pipex_data_init(&data);
	check_argc(argc);
	data.cmd_num = argc - 3;
	get_files(argc, argv, &data);
	exec_cmds(&data, argv, environ);
	return (0);
}
