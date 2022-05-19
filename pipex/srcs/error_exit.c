/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 12:31:45 by jpizarro          #+#    #+#             */
/*   Updated: 2022/02/27 12:48:41 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Exits the program displaying the str messages if there is any, and freeing
**	the malloced memory.
*/

#include "../pipex.h"

void	error_exit(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	// TODO: Free mallocs if they exists
	exit(0);
}