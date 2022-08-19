/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:30:00 by mtorrado          #+#    #+#             */
/*   Updated: 2022/08/19 19:31:35 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Closes the fds that are not needed anymore.
*/

void	close_fds(t_cmds *cmd, pid_t pid, int i)
{
	if (i)
		close(cmd->pipe[OUT]);
	if (cmd->next)
		close(cmd->next->pipe[IN]);
	if (cmd->next && !pid)
		close(cmd->next->pipe[OUT]);
	if (cmd->fd_in >= 0)
	{
		if (cmd->tok_in == TOKHERE && pid)
			unlink(".heredoc");
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
}
