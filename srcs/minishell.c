/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:37:03 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/07 12:07:02 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	If an error has ocurred in the previous cicle, it prints it.
*/

void	print_err(t_mini_data *data)
{
	if (!data->err || data->err == CONTINUE)
		return;
	else if (data->err == QUOTERR)
		printf("%s: open quotes are not suported by %s\n",
		data->shell_name, data->shell_name);
	else if (data->err == SYNTERR)
		printf("%s: syntax error\n", data->shell_name);
	else if (data->err == TOKERR)
		printf("%s: syntax error near unexpected token\n", data->shell_name);
	else if (data->err == AMBRED)
		printf("%s: ambiguous redirect\n", data->shell_name);
	else if (data->err == NOTFILE)
		printf("%s: No such file or directory\n", data->shell_name);
	else if (data->err == PIPING)
		printf("%s: Error whlie piping\n", data->shell_name);
	else if (data->err == DUPING)
		printf("%s: Error whlie dupping\n", data->shell_name);
}


/*
**	Frees and anulates what is needed for a fresh main minishell loop.
*/

void	reset_data(t_mini_data *data)
{
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->cmds)
		free_cmds(&data->cmds);
	data->cmds = NULL;
	data->err = 0;

//	if (data->cmd)
//		ft_free_split(data->cmd);
//	data->cmd = NULL;
}


int	main(int argc, char *argv[], char *envp[])
{
	t_mini_data	data;
	
	(void)argc;
	(void)argv;
	init_mini_data(&data);
	set_env_list(envp, &data);
	signal_handler();
	while(1)
	{
		print_err(&data);
		reset_data(&data);
		data.line = readline(data.prompt);
		if (!data.line)
			exit_shell(&data);
		data.err = parser(&data);
	if (!data.err)
			executer(&data, &data.cmds);
	}
	return(0);
}

//	Buscar TODOs y // antes de dar por finalizada!!