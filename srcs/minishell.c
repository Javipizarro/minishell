/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:37:03 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/19 17:03:03 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Frees and anulates what is needed for a fresh main minishell loop.
*/

void	free_stuff(t_mini_data *data)
{
		if (data->line)
			free(data->line);
		data->line = NULL;
		if (data->cmd)
			ft_free_split(data->cmd);
		data->cmd = NULL;
}


int	main(int argc, char *argv[], char *envp[])
{
	t_mini_data	data;

	(void)argc;
	(void)argv;
	init_mini_data(&data);
	set_env_list(envp, &data);
//	(void)envp;
//	set_env_list(envp, &data);
	signal_handler();
	while(1)
	{
		data.line = readline(data.prompt);
		if (!data.line)
			exit_shell(&data);
		parser(&data);
		executer(&data);
		free_stuff(&data);
	}
}

//	Buscar TODOs antes de dar por finalizada!!