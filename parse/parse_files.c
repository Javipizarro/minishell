/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:36:05 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/04 14:21:39 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Opens the file pointed by path according to the token instructions.
**	Fills the cmd structure with the fd of the file, and closes any previous fd.
*/

void	open_file(char token, char *path, t_cmds *cmd, t_mini_data *data)
{
	//	TODO: Verificar permisos de usuarios?
	if ((token == IN || token == HERE) && cmd->fd_in >= 0)
		close(cmd->fd_in);
	if ((token == OUT || token == APOUT) && cmd->fd_out >= 0)
		close(cmd->fd_out);
	if (token == IN)
	{
		cmd->fd_in = open(path, O_RDONLY);
		if (cmd->fd_in < 0)
			data->err = NOTFILE;
	}
	else if (token == OUT)
		cmd->fd_out = open(path, O_WRONLY | O_CREAT | O_TRUNC);
	else if (token == HERE)
	{ printf("working on <<.\nSorry for the inconvenieces\n");}	//	TODO: Write a function to manage HERE
	else if (token == APOUT)
		cmd->fd_out = open(path, O_WRONLY | O_CREAT | O_APPEND);
}

/*
**	Finds redirection tokens, stores them into the cmd structure.
**	Opens the files pointed by the redirection tokens the way they have
**	to be oppened, and stores their fds into the cmd structure.
**	Fills data->err if there is any.
*/

void	parse_files(char *line, t_cmds *cmd, t_mini_data *data)
{
	int i;
	char	quo;
	char	token;
	char	*path;

	i = -1;
	quo = 0;
	path = NULL;
	while (line[++i])
	{
		token = 0;
		quotes_status(line[i], &quo);
		if (quo)
			continue;
		if (line[i] == '<' || line[i] == '>')
			token = tokenizer(&line[i], cmd);
		if (!token)
			continue;
		path = file_path(&line[i], data);
		if (data->err)
			break;
		open_file(token, path, cmd, data);
		if (data->err)
			break;
		free(path);
		path = NULL;
		i--;
	}
	if (path)
		free(path);
		path = NULL;
}
