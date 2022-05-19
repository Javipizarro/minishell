/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:27:22 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/19 17:50:17 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Liberates the env chain.
*/

void	free_env(t_env **env)
{
	if (env[0]->next)
		free_env(&env[0]->next);
	ft_free_split(env[0]->var);
	free(env[0]);
	env[0] = NULL;
}

/*
**	Manages how the mini-shell is abandoned.
*/

//void	*exit_shell(t_mini_data *data)
void	exit_shell(t_mini_data *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
//	if (data->cmd)		TODO: Hacer función para liberar la cadena t_cmds parecida a free_env()
//	{
//		ft_free_split(data->cmd);
//		data->cmd = NULL;
//	}
	data->envp = NULL;
	free(data->envp);
	free(data->shell_name);
	free(data->prompt);
	rl_clear_history();
	free_env(&data->env);
	printf("exit\n");	//TODO: valorar usar echo
	exit(g_exit_status);
}