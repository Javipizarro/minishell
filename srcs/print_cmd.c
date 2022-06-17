/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:53:09 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/16 17:26:27 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd(t_cmds *cmd, char *msg)
{
	if (!cmd)
	{
		printf("\n%s\nt_cmds's pointer passed is NULL\n", msg);
		return;
	}
	printf("\n%s\nI'm the process pid=%i\n\n", msg, getpid());
	printf("STDIN=%i\nSTDOUT=%i\ntok_in=%c\ntok_out=%c\nfd_in=%i\nfd_out=%i\npipe[IN]=%i\npipe[OUT]=%i\n",
	STDIN_FILENO, STDOUT_FILENO, cmd->tok_in, cmd->tok_out, cmd->fd_in, cmd->fd_out, cmd->pipe[IN], cmd->pipe[OUT]);
	int k = -1;
	while (cmd->cmd[++k])
		printf("cmd[%i]=%s\n", k, cmd->cmd[k]);
	printf("next=%p\n", cmd->next);
}