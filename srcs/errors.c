/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:53:13 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/06 19:17:00 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
**	Sets the global variable g_exit_status according to the error found if any.
*/
//// Esta puede desaparecer
void	set_builtin_exit_status(int error)
{
	if (error == KEEPGESTAT)
		return;
	else if (!error || error == CONTINUE)
		g_exit_status = 0;
	else if (error < 100)
		g_exit_status = 1;
	else
		g_exit_status = error;
}

/*
**	Depending on the error received, it returns the main part of the message
**	to print as an error.
*/

char	*select_main_msg(int error)
{
	if (error == QUOTERR)
		return ("open quotes are not suported by ");
	else if (error == TOKERR)
		return ("syntax error near unexpected token");
	else if (error == AMBRED)
		return ("ambiguous redirect");
	else if (error == NOTFILE)
		return ("No such file or directory");
	else if (error == PIPING)
		return ("Error while piping");
	else if (error == DUPING)
		return ("Error while dupping");
	else if (error == FORKING)
		return ("Error while forking");
	else if (error == IDENERR)
		return ("not a valid identifier");
	else if (error == CMDERR)
		return ("command not found");
	else if (error == HOMELESS)
		return ("HOME not set");
	else if (error == NOINTARG)
		return ("numeric argument required");
	else if (error == TOOMARG)
		return ("too many arguments");
	return (NULL);
}

/*
**	If an error has ocurred in the previous cicle, it prints it.
*/

void	print_error(char *cmd_name, int error, char *culprit)
{
	char	*main_msg;

	if (!error || error == CONTINUE)
		return;
	main_msg = select_main_msg(error);
	if (!main_msg)
		return;
	write(2, SHNAME, ft_strlen(SHNAME));
	write(2, ": ", 2);
	if (cmd_name && cmd_name[0])
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": ", 2);
	}
	if (culprit && culprit[0])
	{
		write(2, culprit, ft_strlen(culprit));
		write(2, ": ", 2);
	}
	write(2, main_msg, ft_strlen(main_msg));
	if (error == QUOTERR)
		write(2, SHNAME, ft_strlen(SHNAME));
	write(2, "\n", 1);
}

/*
**	Returns the 'err_exit' value depending on the 'err_print' one.
**	'err_exit' is the error value that a process will return when exeuted
**	by the execve() function.
*/

int	set_error_exit(int err_print)
{
	if (!err_print)
		return (0);
	if (err_print == CONTINUE)
		return (128);
	else if (err_print == CMDINTERR)
		return (2);
	else if (err_print == CMDERR)
		return (127 * 256);
	else if (err_print == NOINTARG)
		return (255 * 256);
//	else if (err_print == QUOTERR || err_print == TOKERR || err_print == AMBRED
//	|| err_print == NOTFILE || err_print == PIPING || err_print == DUPING
//	|| err_print == FORKING || err_print == IDENERR || err_print == HOMELESS
//	|| err_print == TOOMARG)

	return (256);
}



/*
**	Manages the errors printing the corresponding message and setting the
**
*/

int	manage_errors(char *cmd, int err_print, char *culprit)
{
	int	err_exit;
	
(void)cmd;
(void)culprit;

//	perror("error");
	print_error(cmd, err_print, culprit);
//	set_builtin_exit_status(error);
//	return(error);
	err_exit = set_error_exit(err_print);
	printf("ERROR: %d\n", err_exit);
//////
//	printf("err_exit returne by manage_errors = %i\n", err_exit);
	return(err_exit);
}
