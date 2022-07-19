/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:36:05 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/19 12:21:29 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Replaces the '~' char at the beginning of a path with the value of the
**	home environmental variable.
**	Returns a pointer to the new path.
*/

char	*add_home_to_path(t_mini_data *data, char *path)
{
	t_env	**home;
	char	*abs_path;

	home = search_env("HOME", &data->env);
	if (!home[0])
	{
		data->err = manage_errors(HOMELESS, "");
		return (path);
	}
	abs_path = ft_strjoin(home[0]->var[1], &path[1]);
	free(path);
	path = NULL;
	return (abs_path);
}

/*
**	Expands the variables in path, and verifies whether everything is correct.
*/

void	expand_path(char **path, t_mini_data *data, t_cmds *cmd)
{
	int	i;
	char	quo;
	
	i = -1;
	quo = 0;
	cmd->only_vars = 1;
	while (path[0][++i])
	{
		quotes_status(path[0][i], &quo);
		if (path[0][i] != '$')
			cmd->only_vars = 0;
		if (quo == '\'')
			continue;
		if (path[0][i] == '$')
			expand_var(path, &i, data->env);
//		if (path[0][i] == '$')
//			data->err = expand_var(path, &i, data->env);
//		if (data->err && cmd->only_vars)
//			return;
	}
	erase_quotes(*path);
}

/*
**	Opens the file pointed by path according to the token instructions.
**	Fills the cmd structure with the fd of the file, and closes any previous fd.
*/

void	open_file(char token, char *path, t_cmds *cmd, t_mini_data *data)
{
	if ((token == TOKIN || token == TOKHERE) && cmd->fd_in >= 0)
		close(cmd->fd_in);
	if ((token == TOKOUT || token == TOKAPPN) && cmd->fd_out >= 0)
		close(cmd->fd_out);
	if (token == TOKIN)
			cmd->fd_in = open(path, O_RDONLY);
	else if (token == TOKOUT)
			cmd->fd_out = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (token == TOKHERE)
		cmd->fd_in = open(path, O_RDONLY);
	else if (token == TOKAPPN)
		cmd->fd_out = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (token == TOKIN && cmd->fd_in < 0 && !cmd->only_vars)
		data->err = manage_errors(NOTFILE, path);
	else if (token == TOKIN && cmd->fd_in < 0 && cmd->only_vars)
		data->err = manage_errors(AMBRED, path);
	else if ((token == TOKOUT || token == TOKAPPN)
	&& cmd->fd_out < 0 && !cmd->only_vars)
		data->err = manage_errors(NOTFILE, path);
	else if ((token == TOKOUT || token == TOKAPPN)
	&& cmd->fd_out < 0 && cmd->only_vars)
		data->err = manage_errors(AMBRED, path);
}

/*
**	Finds redirection tokens, stores them into the cmd structure.
**	Opens the files pointed by the redirection tokens the way they have
**	to be oppened, and stores their fds into the cmd structure.
**	Fills data->err if there is any.
*/

int	parse_files(char *line, t_cmds *cmd, t_mini_data *data)
{
	int i;
	char	quo;
	char	token;
	char	*path;

	i = -1;
	quo = 0;
	path = NULL;
	token = 0;
	while (line[++i])
	{
		quotes_status(line[i], &quo);
		if (quo)
			continue;
		if (line[i] == '<' || line[i] == '>')
			token = tokenizer(&line[i], cmd);
		if (token)
			break;
	}
	if (!token)
		return (0);
	path = get_file_path(&line[i], data);
	if (token == TOKHERE)
		data->err = heredoc(&path);
	else
		expand_path(&path, data, cmd);
	if (path[0] == '~')
			path = add_home_to_path(data, path);
	if (data->err)
		return (0);
	open_file(token, path, cmd, data);
	free(path);
	path = NULL;
	if (data->err)
		return (0);
	return (1);
}
