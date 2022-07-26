/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:53:13 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/26 12:47:48 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
**	Sets the global variable g_exit_status according to the error found if any.
*/

void	set_exit_status(int error)
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
**	Manages the errors printing the corresponding message and setting the
**	g_exit_status global varible.
*/

int	manage_errors(char *cmd, int error, char *culprit)
{
	print_error(cmd, error, culprit);
	set_exit_status(error);
	return(error);
}
