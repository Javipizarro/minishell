/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:19:31 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/19 16:15:17 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Initiates the necessary data for the minishell to work from a fresh star.
*/

void 	init_mini_data(t_mini_data *data)
{
	//	TODO?:llamar a un malloc free para las var que lo necesiten.
	//data->pip = NULL;
	//data->par = NULL;
	//data->sig = NULL;
	//data->bin = NULL;
	data->shell_name = ft_strdup("JaviShell");
	data->prompt = ft_strdup("JaviShell> ");
	data->cmd = NULL;
	data->envp = NULL;
	data->env = NULL;
	data->cmd = NULL;
	data->line = NULL;
}