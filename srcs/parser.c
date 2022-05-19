/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:56:11 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/19 16:58:07 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks whether we are opening or closing quotes and erase them
**	from the "line" string.
*/

int	parse_quotes(char *line, char *quo, int *i)
{
	if ((line[0] == '"' || line[0] == '\'') && (!*quo || line[0] == *quo))
	{
		if (!*quo)
			*quo = line[0];
		else
			*quo = 0;
		ft_memcpy(&line[0], &line[1], ft_strlen(line) + 1);
		return(1);
	}
	if ((*quo == '\'') || (*quo == '"' && line[0] != '$'))
	{
		(*i)++;
		return(1);
	}
	return (0);
}

/*
**	Receives the line where the environment variable name must be repaced,
**	the start and end possition of the name in the line and the t_env that
**	contains the varible.
**	Replaces the name of the environment variable in the line by its value.
*/

void	env_var_to_value(char **line, int *i, int end, t_env ** env)
{
	char	*temp1;
	char	*temp2;

	if (!env[0])
		ft_memcpy(&line[0][*i], &line[0][end],
		ft_strlen(&line[0][*i]) + 1);
	else
	{
		temp1 = calloc(*i + 1, sizeof(char));
		ft_memcpy(temp1, *line, *i);
		temp2 = ft_strjoin(temp1, env[0]->var[1]);
		free(temp1);
		temp1 = calloc(ft_strlen(*line) - end + 1, sizeof(char));
		ft_memcpy(temp1, &line[0][end], ft_strlen(&line[0][end]));
		free(*line);
		line[0] = ft_strjoin(temp2, temp1);
		free(temp1);
		temp1 = NULL;
		free(temp2);
		temp2 = NULL;
		*i += ft_strlen(env[0]->var[1]);
	}
}

/*
**	Receives a pointer to a possition where a environmental variable can be
**	expanded, checks if there is a variable to be expanded and replaces the
**	call to the variable by its value or by nothing if there is no such varable.
**	Returns 1 if a variable has been expanded, or 0 if nothing has been done.
*/

int	expand_env_var(char **line, int *i, t_env **env)
{
	int		end;
	char	*name;

	if (line[0][*i] != '$')
		return (0);
	end = *i + 1;
	while (line[0][end] && line[0][end] != ' ' && line[0][end] != '|'
	&& line[0][end] != '<' && line[0][end] != '>' && line[0][end] != '='
	&& line[0][end] != '\"' && line[0][end] != '$')
		end++;
	name = ft_calloc(end - *i, sizeof(char));
	ft_memcpy(name, &line[0][*i + 1], end - *i - 1);
	env = search_env(name, env);
	env_var_to_value(line, i, end, env);
	free(name);
	name = NULL;
	return (1);
}

/*
**	Checks whether there are open quotes that invalidate the entry.
*/

int	arrange_cmd(t_mini_data *data)
{
	int 	i;
	char	quo;
	int		err;

	i = 0;
	quo = 0;
	while (data->line[i])
	{
		if (parse_quotes(&data->line[i], &quo, &i))
			continue;
		if (expand_env_var(&data->line, &i, &data->env))
			continue;
		i++;
	}
	if (quo)
		printf("%s: open quotes are not suported by %s\n",
		data->shell_name, data->shell_name);
	else
		err = line_to_cmds(data);
	return ((int)quo + err);
}


/*
**	
*/

void	parser(t_mini_data *data)
{
	if (!data->line || !data->line[0])
		return;
	add_history(data->line);
	if (arrange_cmd(data))
		return;
	data->cmd = ft_split(data->line, ' ');
}