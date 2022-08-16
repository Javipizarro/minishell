/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:36:05 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/16 19:36:13 by jpizarro         ###   ########.fr       */
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
		data->err_print = manage_errors(NULL, HOMELESS, NULL);
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

int	expand_path(char **path, t_mini_data *data)
{
	int	i;
	char	quo;
	char	*var_to_expand;
	char	*var_val;
	
	i = -1;
	quo = 0;
	while (path[0][++i])
	{
		quotes_status(path[0][i], &quo);
		if (quo == '\'')
			continue;
		if (path[0][i] == '$')
		{
			var_to_expand = extract_env_var_name(*path, i);
			var_val = expand_var(path, &i, var_to_expand, data->env);
		//////
		//	printf("despues de expand_var\n");
		//	sleep(10);
			if (!var_val || !var_val[0] || (ft_charpos(var_val, ' ') && !quo))
			{
				data->err_print = manage_errors(NULL, AMBRED, var_to_expand);
				set_exit_status(256);
				free(var_to_expand);
				free(var_val);
		////
		//	printf("despues de expand_var\n");
		//	sleep(10);

				return (1);
			}
			free(var_to_expand);
			free(var_val);
			i--;
		}
	}
	erase_quotes(*path);
	return (0);
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
	if (token == TOKIN && cmd->fd_in < 0)
		data->err_print = manage_errors(NULL, NOTFILE, path);
	else if ((token == TOKOUT || token == TOKAPPN)
	&& cmd->fd_out < 0)
		data->err_print = manage_errors(NULL, NOTFILE, path);
}

/*
**	Finds redirection tokens, stores them into the cmd structure.
**	Opens the files pointed by the redirection tokens the way they have
**	to be oppened, and stores their fds into the cmd structure.
**	Fills data->err_print if there is any.
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
		return (1);
	path = get_file_path(&line[i], data);
	if (token == TOKHERE)
		data->err_print = heredoc(data, &path);
	else if (expand_path(&path, data))
	{
		free(path);
		return (1);
	}
//	if (data->err_print)
//		return(1);
	if (path[0] == '~')
			path = add_home_to_path(data, path);
//	if (data->err_print)
//		return (1);
	if (chek_dir(path))
	{
		data->err_print = ISDIRFILE;
		free(path);
		return(manage_errors(NULL, ISDIRFILE, path));
	}
	open_file(token, path, cmd, data);
	free(path);
	path = NULL;
	if (data->err_print)
		return (1);
	return (0);
}
