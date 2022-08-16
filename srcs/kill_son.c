/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_son.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:34:30 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/10 15:54:34 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	kill_son(t_mini_data *data, pid_t pid)
{
	if (pid)
		return;
	free_stuff(data);
	exit(data->err_exit);
}
