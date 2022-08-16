/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:34:33 by mtorrado          #+#    #+#             */
/*   Updated: 2022/08/16 17:35:51 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks whether the path points to a directory.
**	Return 0 if it does not and 1 otherwise.
*/

int	chek_dir(char *path)
{
	struct stat	info;

	if (!lstat(path, &info))
	{
		if (S_ISDIR(info.st_mode))
			return(1);
	}
	return(0);
}
