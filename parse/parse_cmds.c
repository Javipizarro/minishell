/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:51:09 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/04 11:36:43 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Searches the variables contained in 'line' that need to be expanded, and
**	sends them to expand.
*/

void	expand_vars(char **line, t_env *env)
{
	int i;
	char	quo;

	i = -1;
	quo = 0;
	while (line[0][++i])
	{
		quotes_status(line[0][i], &quo);
		if (quo == '\'')
			continue;
		if (line[0][i] == '$')
			expand_var(line, &i, env);
	}
}

/*
**	Replaces the spaces by unit separators (acii char 31), in order to later
**	split the line by them.
*/

void	spaces_to_31(char *line)
{
	int	i;
	char	quo;

	i = -1;
	quo = 0;
	while(line[++i])
	{
		quotes_status(line[i], &quo);
		if (quo)
			continue;
		if (line[i] == ' ')
			line[i] = 31;
	}
}


/*
**	Receives the cmd stripped of files redirections, spands it, stripts it
**	from quotes and splits it to be used with execve.
*/

void	parse_cmd(char **line, t_cmds *cmd, t_mini_data *data)
{
	trim_spaces(*line);
	spaces_to_31(*line);
	expand_vars(line, data->env);
	erase_quotes(*line);
	cmd->cmd = ft_split(*line, 31);
}