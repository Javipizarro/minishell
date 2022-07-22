/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:51:09 by jpizarro          #+#    #+#             */
/*   Updated: 2022/07/21 18:03:08 by jpizarro         ###   ########.fr       */
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
	char	*var_to_expand;

	i = 0;
	quo = 0;
	while (line[0][++i])
	{
//		if (line[0][i] != '$' && line[0][i] != ' ')
//			cmd->only_vars = 0;
		quotes_status(line[0][i], &quo);
		if (quo == '\'')
			continue;
		if (line[0][i] == '$')
		{
			var_to_expand = extract_env_var_name(*line, i);
			expand_var(line, &i, var_to_expand, env);
			free(var_to_expand);
			i--;
		}
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
	int i;

	trim_spaces(*line);
	expand_vars(line, data->env);
	spaces_to_31(*line);
	cmd->cmd = ft_split(*line, 31);
	i = -1;
	while (cmd->cmd[++i])
		erase_quotes(cmd->cmd[i]);
}
