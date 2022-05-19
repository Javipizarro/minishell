/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:45:46 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/12 09:18:59 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Prints the current working directory.
*/

int	pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	printf("%s\n", buff);
	return (0);
}
