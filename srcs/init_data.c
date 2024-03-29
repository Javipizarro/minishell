/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:19:31 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/19 14:37:08 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Initiates the necessary data for the minishell to work from a fresh star.
*/

void	init_mini_data(t_mini_data *data)
{
	data->env = NULL;
	data->envp = NULL;
	data->line = NULL;
	data->cmds = NULL;
	data->err_print = 0;
}
