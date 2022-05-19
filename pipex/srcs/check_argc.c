/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 07:47:17 by jpizarro          #+#    #+#             */
/*   Updated: 2022/03/15 06:20:15 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Checks whether the number of arguments is 5
**	Only valid for the non-bonus version!!
*/

# include "../pipex.h"

void	check_argc(int argc)
{
	char	*str;
	
	if (argc < 5)
	{
		str = "Wrong args, use:\n./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n";
		error_exit(str);
	}
}