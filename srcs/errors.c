/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:53:13 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/19 16:15:05 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Depending on the error received, they return the main part of the message
**	to print as an error.
*/

char	*select_main_msg2(int error)
{
	if (error == ISDIRCMD)
		return ("is a directory");
	else if (error == ISDIRFILE)
		return ("Is a directory");
	return (NULL);
}

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
	return (select_main_msg2(error));
}

/*
**	If an error has ocurred in the previous cicle, it prints it.
*/

void	print_error(char *cmd_name, int error, char *culprit)
{
	char	*main_msg;

	if (!error || error == CONTINUE)
		return ;
	main_msg = select_main_msg(error);
	if (!main_msg)
		return ;
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
		return (CONTINUE);
	else if (err_print == CMDERR)
		return (CMDERR);
	else if (err_print == CMDINTERR)
		return (CMDINTERR);
	else if (err_print == NOINTARG)
		return (NOINTARG);
	else if (err_print == ISDIRCMD)
		return (ISDIRCMD);
	return (1);
}

/*
**	Manages the errors printing the corresponding message and setting the
*/

int	manage_errors(char *cmd, int err_print, char *culprit)
{
	int	err_exit;

	print_error(cmd, err_print, culprit);
	err_exit = set_error_exit(err_print);
	return (err_exit);
}
