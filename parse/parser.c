/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:56:11 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/04 23:46:44 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

///*
//**	Receives the line where the environment variable name must be repaced,
//**	the start and end possition of the name in the line and the t_env that
//**	contains the varible.
//**	Replaces the name of the environment variable in the line by its value.
//*/
//
//void	env_var_to_value(char **line, int *i, int end, t_env ** env)
//{
//	char	*temp1;
//	char	*temp2;
//
//	if (!env[0])
//		ft_memcpy(&line[0][*i], &line[0][end],
//		ft_strlen(&line[0][*i]) + 1);
//	else
//	{
//		temp1 = calloc(*i + 1, sizeof(char));
//		ft_memcpy(temp1, *line, *i);
//		temp2 = ft_strjoin(temp1, env[0]->var[1]);
//		free(temp1);
//		temp1 = calloc(ft_strlen(*line) - end + 1, sizeof(char));
//		ft_memcpy(temp1, &line[0][end], ft_strlen(&line[0][end]));
//		free(*line);
//		line[0] = ft_strjoin(temp2, temp1);
//		free(temp1);
//		temp1 = NULL;
//		free(temp2);
//		temp2 = NULL;
//		*i += ft_strlen(env[0]->var[1]);
//	}
//}

///*
//**	Receives a pointer to a possition where a environmental variable can be
//**	expanded, checks if there is a variable to be expanded and replaces the
//**	call to the variable by its value or by nothing if there is no such varable.
//**	Returns 1 if a variable has been expanded, or 0 if nothing has been done.
//*/
//
//int	expand_env_var(char **line, int *i, t_env **env)
//{
//	int		end;
//	char	*name;
//
//	if (line[0][*i] != '$')
//		return (0);
//	end = *i + 1;
//	while (line[0][end] && line[0][end] != ' ' && line[0][end] != '|'
//	&& line[0][end] != '<' && line[0][end] != '>' && line[0][end] != '='
//	&& line[0][end] != '\"' && line[0][end] != '$')
//		end++;
//	name = ft_calloc(end - *i, sizeof(char));
//	ft_memcpy(name, &line[0][*i + 1], end - *i - 1);
//	env = search_env(name, env);
//	env_var_to_value(line, i, end, env);
//	free(name);
//	name = NULL;
//	return (1);
//}

///*
//**	Expands the environment variables that are outside '' and erase the
//**	quotes so the line can be later managed to store it into the cmds list.
//*/
//
//void	expand_line(t_mini_data *data)
//{
//	int	i;
//	char	quo;
//
//	i = 0;
//	quo = 0;
//	while (data->line[i])
//	{
//		if (parse_quotes(data->line, &quo, &i))
//			continue;
//		if (expand_env_var(&data->line, &i, &data->env))
//			continue;
//		i++;
//	}
//}

/*
**	Checks whether there are any wrong place token.
*/

int	check_tokens(char *line)
{
	int	i;
	char quo;
	char token;

	i = ft_strlen(line);
	if (line[0] == '|' || line[i] == '|' || line[i] == '>' || line[i] == '<')
		return (1);
	i = -1;
	quo = 0;
	token = 0;
	while (line[++i])
	{
		quotes_status(line[i], &quo);
		if (quo || (line[i] != '|' && line[i] != '<' && line[i] != '>'))
		{
			if (token && line[i] != ' ')
				token = 0;
			continue;
		}
		if ((line[i] == '<' || line[i] == '>') && line[i] == line[i + 1])
			i++;
		if (token && (line[i] == '|' || token != '|'))
			return (1);
		else
			token = line[i];
	}
	return (0);
}


/*
**	Trims all the unnecessary spaces from the line for parsing it.
*/

void	trim_spaces(char *line)
{
	int i;
	char	quo;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (i)
		ft_memcpy(&line[0], &line[i], ft_strlen(&line[i]) + 1);
	i = 0;
	quo = 0;
	while (line[i])
	{
		quotes_status(line[i], &quo);
		if (!quo && line[i] == ' ' && line[i + 1] == ' ')
		{
			ft_memcpy(&line[i], &line[i + 1], ft_strlen(&line[i]));
			continue;
		}
		i++;
	}
	while (line[--i] == ' ')
		line[i] = 0;
}


/*
**	From the info in 'data->line', it arranges the commands in it
**	and stores them in the 'data->cmds' t_cmds structure to
**	execute them later.
**	Returns 0 if the commands can be passed or a value related with
**	the issue found if there is any.
*/

int	parser(t_mini_data *data)
{
	if (!data->line || !data->line[0])
		return (CONTINUE);
	add_history(data->line);
	trim_spaces(data->line);
	if (!data->line[0])
		return (CONTINUE);
	if (check_open_quotes(data->line))
		return (QUOTERR);
	if (check_tokens(data->line))
		return (TOKERR);
	line_to_cmds(data, &data->cmds);
	if (data->err)
		return (data->err);
	return (0);
}