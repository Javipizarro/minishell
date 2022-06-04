/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:19:31 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/25 03:07:07 by jpizarro         ###   ########.fr       */
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
	data->env = NULL;
	data->envp = NULL;
	data->line = NULL;
	data->cmds = NULL;
//	data->err = 0;
}