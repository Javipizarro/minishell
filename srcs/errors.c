/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:53:13 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/12 19:39:25 by jpizarro         ###   ########.fr       */
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

void	print_error(int error, char *culprit)
{
	(void)culprit;
	if (!error || error == CONTINUE)
		return;
	else if (error == QUOTERR)
		printf("%s: open quotes are not suported by %s\n",
		SHNAME, SHNAME);
	else if (error == SYNTERR)
		printf("%s: syntax error\n", SHNAME);
	else if (error == TOKERR)
		printf("%s: syntax error near unexpected token\n", SHNAME);
	else if (error == AMBRED)
		printf("%s: ambiguous redirect\n", SHNAME);
	else if (error == NOTFILE)
		printf("%s: No such file or directory\n", SHNAME);
	else if (error == PIPING)
		printf("%s: Error while piping\n", SHNAME);
	else if (error == DUPING)
		printf("%s: Error while dupping\n", SHNAME);
	else if (error == FORKING)
		printf("%s: Error while forking\n", SHNAME);
	else if (error == IDENERR)
		printf("%s: not a valid identifier\n", SHNAME);
	else if (error == CMDERR)
		printf("%s: command not found\n", SHNAME);
	else if (error == HOMELESS)
		printf("%s: cd: HOME not set\n", SHNAME);
}

/*
**	Manages the errors printing the corresponding message and setting the
**	g_exit_status global varible.
*/

void	manage_errors(int error, char *culprit)
{
	if (!error || error == CONTINUE)
		return;
	print_error(error, culprit);
	set_exit_status(error);
}
