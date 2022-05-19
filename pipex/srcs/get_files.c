/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:02:41 by jpizarro          #+#    #+#             */
/*   Updated: 2022/03/02 06:55:34 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Opens the infile and outfile and load the fd in the data structure.
**	In case of error it exits the program calling perror_exit() function.
*/

#include "../pipex.h"

void	get_files(int argc, char *argv[], t_pipex_data *data)
{
	data->outfile = open (argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC
		| O_APPEND,	S_IRWXU);
	if (data->outfile < 0)
		perror_exit(argv[argc - 1]);
	data->infile = open (argv[1], O_RDONLY);
	if (data->infile < 0)
		perror_exit(argv[1]);
}