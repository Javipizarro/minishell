/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:37:03 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/30 20:19:55 by jpizarro         ###   ########.fr       */
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
		printf("%s: Error while piping\n", data->shell_name);
	else if (data->err == DUPING)
		printf("%s: Error while dupping\n", data->shell_name);
	else if (data->err == FORKING)
		printf("%s: Error while forking\n", data->shell_name);
	else if (data->err == IDENERR)
		printf("%s: not a valid identifier\n", data->shell_name);
	else if (data->err == CMDERR)
		printf("%s: command not found\n", data->shell_name);
	else if (data->err == HOMELESS)
		printf("%s: cd: HOME not set\n", data->shell_name);
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
	data->cmd_num = 0;
	data->err = 0;
	data->child_err = 0;

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
	signal_handler(GENERAL, 0);
	while(1)
	{
		print_err(&data);
		reset_data(&data);
		data.line = readline(data.prompt);
		if (!data.line)
			exit_shell(&data, 1);
		data.err = parser(&data);
		if (!data.err)
		{
			signal_handler(EXEC, 0);
			executer(&data, &data.cmds);
			signal_handler(GENERAL, 0);
		}
	}
	return(0);
}

//	Buscar TODOs y // antes de dar por finalizada!!
//	Borrar print_cmd