/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:31:06 by mtorrado          #+#    #+#             */
/*   Updated: 2022/08/19 19:32:08 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Makes the father proccess wait for their children exit.
*/

void	waiter(t_mini_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_num)
	{
		wait(&data->err_exit);
		set_exit_status(data->err_exit);
	}
}
