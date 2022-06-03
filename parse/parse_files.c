/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:36:05 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/03 12:15:15 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Expands the variables in path thar are not between quotes, and replaces
**	the name with the value.
**	Returns an error if there is any.
*/

int	expand_no_quo(char *path, int *pos, t_env *env)
{
	int i;
	int	j;
	char	*tmp;
	
	i = *pos;
	j = *pos + 1;
	while (path[j] && path[j] != '$' && path[j] != ' ' && path[j] != '"'
	&& path[j] != '\'')
		j++;
	tmp = ft_calloc(j - i, sizeof(char));
	ft_memcpy(tmp, path[i + 1], j - i - 1);
	while (env && !ft_strcmp(tmp, env->var[0]))
		env = env->next;
	free(tmp);
	if (!env->var || ft_strchr(env->var[1], ' '))
		return (AMBRED);
	tmp = ft_calloc(ft_strlen(env->var[1] + ft_strlen(path) - j + i + 1,
	sizeof(char)));
	ft_memcpy(tmp, path, i);
	ft_memcpy(&tmp[i], env->var[1], ft_strlen(env->var[1]));
	ft_memcpy(&tmp[i + ft_strlen(env->var[1])], path[j], ft_strlen(&path[j]));
	free(path);
	path = tmp;
	*pos += ft_strlen(env->var[1]);
	return (0);
}



/*
**	Expands the variables in path thar are not between quotes, and replaces
**	the name with the value.
**	Returns an error if there is any.
*/

int	expand_quo(char *path, int *pos, t_env *env)
{
	int i;
	int	j;
	char	*tmp;
	
	i = *pos;
	j = *pos + 1;
	while (path[j] && path[j] != '$' && path[j] != ' ' && path[j] != '"')
		j++;
	tmp = ft_calloc(j - i, sizeof(char));
	ft_memcpy(tmp, path[i + 1], j - i - 1);
	while (env && !ft_strcmp(tmp, env->var[0]))
		env = env->next;
	free(tmp);
	if (!env->var)
		return (NOTFILE);
	tmp = ft_calloc(ft_strlen(env->var[1] + ft_strlen(path) - j + i + 1,
	sizeof(char)));
	ft_memcpy(tmp, path, i);
	ft_memcpy(&tmp[i], env->var[1], ft_strlen(env->var[1]));
	ft_memcpy(&tmp[i + ft_strlen(env->var[1])], path[j], ft_strlen(&path[j]));
	free(path);
	path = tmp;
	*pos += ft_strlen(env->var[1]);
	return (0);
}


/*
**	Expands the variables in path, and verifies whether everything is correct.
*/

void	expand_path(char *path, t_mini_data *data)
{
	int	i;
	char	quo;
	
	i = -1;
	while (path[++i])
	{
		quotes_status(path[i], &quo);
		if (quo == '\'')
			continue;
		else if (!quo && path[i] == '$')
			data->err = expand_no_quo(path, &i,data->env);
		else if (quo || path[i] = '$')
			data->err = expand_quo(path, &i, data->env);
		if (data->err)
			return;
	}
}


/*
**	Takes the next characters string until the firs significative space,
**	expands its variables and search for anything that could be wrong.
**	Returns the string that contains the file path, or null if there has
**	been any problem.
*/

char	*file_path(char *line, t_cmds *cmd, t_mini_data *data)
{
	int	i;
	char	quo;
	char	*path;

	//i = 0;
	//while (line[i] == ' ')
	//	i++;
	//if (i)
	//	ft_memcpy(line, &line[i], ft_strlen(&line[i] + 1));
	i = -1;
	while (line[++i])
	{
		quotes_status(line[i], &quo);
		if (quo)
			continue;
		if (line[i] == ' ')
			break;
	}
	path = ft_calloc(sizeof(char), i + 1);
	ft_memcpy(path, line, i);
	ft_memcpy(line, &line[i], ft_strlen(&line[i]));
	i = -1;
	expand_path(path, data);
	if (data->err)
		return;
	erase_quotes(path);
	return(path);
}


/*
**	Finds redirection tokens, stores them into the cmd structure.
**	Opens the files pointed by the redirection tokens the way they have
**	to be oppened, and stores their fds into the cmd structure.
**	Returns 0 if everything is OK or the error value if it's not.
*/

int	parse_files(char *line, t_cmds *cmd, t_mini_data *data)
{
	int i;
	char	quo;
	char    token;
	char	*path;

	i = -1;
	quo = 0;
	while (line[++i])
	{
		quotes_status(line[i], &quo);
		if (quo)
			continue;
		if (line[i] == '<' || line[i] == '>')
			token = tokenizer(&line[i], cmd);
		if (!token)
			continue;
		path = file_path(&line[i], data);
		if (data->err)
			return;
		
		open_file(token, path, cmd);
		return();
		
		// Hay que escribir estas de arriba,
		// Coger ruta de archivo, abrirlo...
		
			
	}


}

