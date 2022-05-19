/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 05:20:57 by jpizarro          #+#    #+#             */
/*   Updated: 2022/03/01 05:38:00 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Finds the "PATH=" environ variable and retrurns it.
*/

#include "../pipex.h"

char	*get_env_path(char *environ[])
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "PATH=", 5))
			return (environ[i]);
		i++;
	}
	return (NULL);
}
