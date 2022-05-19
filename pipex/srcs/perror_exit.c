/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:01:33 by jpizarro          #+#    #+#             */
/*   Updated: 2022/02/27 18:01:16 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
**	Receives a string, calls perror with that string, and exits the program.
*/

void	perror_exit(char* str)
{
	perror(str);
	error_exit(NULL);
}