/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:37:02 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/06 18:37:37 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Liberates the cmds chain.
*/

void	free_cmds(t_cmds **cmds)
{
	if (cmds[0]->next)
		free_cmds(&cmds[0]->next);
	if (cmds[0]->cmd)
		ft_free_split(cmds[0]->cmd);
	// if (cmds[0]->fd_in == PIPED)
	// 	close(cmds[0]->pipe[IN]);
	// if (cmds[0]->fd_out == PIPED)
	// 	close(cmds[0]->pipe[OUT]);
	if (cmds[0]->fd_in >= 0)
		close(cmds[0]->fd_in);
	if (cmds[0]->fd_out >= 0)
		close(cmds[0]->fd_out);
	cmds[0]->tok_in = 0;
	cmds[0]->tok_out = 0;
	free(cmds[0]);
	cmds[0] = NULL;
}

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
**	Frees everything to exit without leaks.
*/

void	free_stuff(t_mini_data *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->cmds)
		free_cmds(&data->cmds);
	ft_free_split(data->envp);
	data->envp = NULL;
	rl_clear_history();
	free_env(&data->env);

}