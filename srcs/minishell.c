/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:37:03 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/26 09:32:18 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_d(t_mini_data *data)
{
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[11C", STDOUT_FILENO);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_shell(data, NULL, 1);
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
}


int	main(int argc, char *argv[], char *envp[])
{
	t_mini_data	data;


	(void)argc;
	(void)argv;
	init_mini_data(&data);
	set_env_list(envp, &data);
	backup_termattr(&data.termattr);
	signal_handler(&data, GENERAL, 0);
	while(1)
	{
		reset_data(&data);
		data.line = readline(SHNAME "> " );
		if (!data.line)
			ctrl_d(&data);
		data.err = parser(&data);
		if (!data.err)
		{
			signal_handler(&data, EXEC, 0);
			executer(&data, &data.cmds);
			signal_handler(&data, GENERAL, 0);
		}
	}
	return(0);
}

/*
Cambiar los write por ft_putstr_fd
*/

/*Tests to pass:
exit -10 ## shouldn't print anything and yield a $? == 246
exit +10 ## shouldn't print anything and yield a $? == 10
cd no_file  ## should print no_file: No such file or directory
cd a b c d  ## should print a: No such file or directory
Ctrl + C (with something written) ## shoudn't print ^C (not very important);
exit 0 | exit 1 ## Should yield a $? == 1 (not exiting)
exit 1 | exit 0 ## Should yield a $? == 0 (not exiting)
verificar las variables con espacios, a lo mejor hay que rodearlas con "" o ''
$HOME hola ## is a directory

Resueltos:
export "" OR export $ ## not a valid identifier
Look over the g_exit_status, when it changes to 1, does't return to 0 after a correct command
export no debe cortar al no encontrar una variable, cambiar el sistema de errores.
unset leaves leaks
export var ## leaks
ls | nocmd | wc ## Should show:	0	0	0
"" OR $ ## command not found
export | wc ## no funciona
cd $HOME/Documents  ## needs to go to Users/(user)/Documents
ls > "" ## No such file or directory
export a=""; ls > $a ## ambiguous redirect
ls > $ ## creates a file "$" and fills it with the ls
$not_defined_var ## nothing, just a new line
echo bonjour > $test ## var test not defined -> ambiguous redirect
file_name_in_current_dir ## with a file named file_name_in_current_dir -> command not found
export var ="cat Makefile | grep >"  ##  should export var and export ="cat Makefile | grep >" -> not a valid identifier
cat algo_que_no_exista ## should yield a $? == 1
Incluir la parte de la línea que causó el error.
Ctrl + D  ## must print the exit word in the same line, when it's empty
Ctrl + C  ## do not print ^C but when a command is active it does, unless it is in heredoc.
exit hola ## should print a "numeric argument required" and yield a $? == 255
*/


/* More stuff:
Check wheter the built-ins support absolute path

try to perform the heredoc on a pipe instead of on a file

manage $? on every cmd execution

print the error on the execution of the cmd not at the end of then all

show the cause of an error when printing it:
	-when command not found:
	-when not a file or directory
*/