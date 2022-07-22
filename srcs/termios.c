/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:44:11 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/22 22:52:21 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Everithing related with termiios is here.
*/

void	backup_termattr(struct termios *termattr)
{
	static int	flag;

	if (flag)
		return ;
	tcgetattr(STDOUT_FILENO, termattr);
	flag = 1;
}

/*
**
*/

void	restore_termattr(struct termios *termattr)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, termattr);
}

/*
**
*/

void	turn_off_echoctl(void)
{
	struct termios	termattr;

	tcgetattr(STDOUT_FILENO, &termattr);
	termattr.c_lflag = ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &termattr);
}
