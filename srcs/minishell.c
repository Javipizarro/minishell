/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 06:37:03 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/07 02:17:50 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Sets the global variable g_exit_status according to the error found if any.
*/

void	set_exit_status(int error)
{
	if (!error || error == CONTINUE)
		g_exit_status = 0;
	else if (error < 100)
		g_exit_status = 1;
	else
		g_exit_status = error;
}



/*
**	If an error has ocurred in the previous cicle, it prints it.
*/

void	print_err(t_mini_data *data)
{
	if (!data->err || data->err == CONTINUE)
		return;
	else if (data->err == QUOTERR)
		printf("%s: open quotes are not suported by %s\n",
		SHNAME, SHNAME);
	else if (data->err == SYNTERR)
		printf("%s: syntax error\n", SHNAME);
	else if (data->err == TOKERR)
		printf("%s: syntax error near unexpected token\n", SHNAME);
	else if (data->err == AMBRED)
		printf("%s: ambiguous redirect\n", SHNAME);
	else if (data->err == NOTFILE)
		printf("%s: No such file or directory\n", SHNAME);
	else if (data->err == PIPING)
		printf("%s: Error while piping\n", SHNAME);
	else if (data->err == DUPING)
		printf("%s: Error while dupping\n", SHNAME);
	else if (data->err == FORKING)
		printf("%s: Error while forking\n", SHNAME);
	else if (data->err == IDENERR)
		printf("%s: not a valid identifier\n", SHNAME);
	else if (data->err == CMDERR)
		printf("%s: command not found\n", SHNAME);
	else if (data->err == HOMELESS)
		printf("%s: cd: HOME not set\n", SHNAME);
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
		set_exit_status(data.err);
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