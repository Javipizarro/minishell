/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 05:06:54 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/17 02:27:27 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Tries the different possible paths in the "PATH=" environ variable, and 
**	saves the correct one on path.
*/

#include "../pipex.h"

void	get_path(char *cmd, char *environ[], char **path)
{
	char	**paths;
	char	*pos_path;
	char	*pos_cmd_path;
	int		i;

	if (!access(cmd, O_RDONLY))
		*path = cmd;
	if (!access(cmd, O_RDONLY))
		return;
	i = 0;
	paths = ft_split(ft_strchr(get_env_path(environ), '/'), ':');
	while (paths[i])
	{
		pos_path = ft_strjoin(paths[i], "/");
		pos_cmd_path = ft_strjoin(pos_path, cmd);
		free(pos_path);
		if (!access(pos_cmd_path, O_RDONLY))
		{
			*path = pos_cmd_path;
			ft_free_split(paths);
			return ;
		}
		free(pos_cmd_path);
		i++;
	}
	ft_free_split(paths);
}