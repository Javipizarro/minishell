/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:37:03 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/12 19:51:28 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
//		print_err(&data);
//		set_exit_status(data.err);
		reset_data(&data);
		data.line = readline(SHNAME "> " );
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

/*
Hacer que los errores se impriman en el momento que se produzcan.
Incluir la parte de la línea que lo causó.
*/

/*Tests to pass:
export "" ## not a valid identifier
export no debe cortar al no encontrar una variable, cambiar el sistema de errores.
unset leaves leaks
verificar las variables con espacios, a lo mejor hay que rodearlas con "" o ''
ls | nocmd | wc ## Should show:	0	0	0
export | wc ## no funciona
cd $HOME/Documents  ## needs to go to Users/(user)/Documents
$not_defined_var ## nothing, just a new line
echo bonjour > $test ## var test not defined -> ambiguous redirect
file_name_in_current_dir ## with a file named file_name_in_current_dir -> command not found
export var ="cat Makefile | grep >"  ##  should export var and export ="cat Makefile | grep >" -> not a valid identifier
cat diufosgid ## should yield a $? == 1
exit hola ## should print a "numeric argument required" and yield a $? == 255
exit -10 ## shouldn't print anything and yield a $? == 246
exit +10 ## shouldn't print anything and yield a $? == 10
cd no_file  ## should print no_file: No such file or directory
cd a b c d  ## should print a: No such file or directory
Ctrl + C (with something written) ## shoudn't print ^C (not very important);
exit 0 | exit 1 ## Should yield a $? == 1 (not exiting)
exit 1 | exit 0 ## Should yield a $? == 0 (not exiting)

Resueltos:
$ ## command not found
*/


/* More stuff:
try to perform the heredoc on a pipe instead of on a file

manage $? on every cmd execution

print the error on the execution of the cmd not at the end of then all

show the cause of an error when printing it:
	-when command not found:
	-when not a file or directory
*/