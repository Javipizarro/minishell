/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:37:10 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/07 12:29:00 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Finds the "PATH=" environ variable and retrurns it.
*/

char	*get_env_path(char *environ[])
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "PATH=", 5))
			return (environ[i]);
		i++;
	}
	return (NULL);
}

/*
**	Tries the different possible paths in the "PATH=" environment variable, and 
**	saves the correct one on path.
*/

void	get_cmd_path(char *cmd, char *environ[], char **path)
{
	char	**paths;
	char	*pos_path;
	char	*pos_cmd_path;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(ft_strchr(get_env_path(environ), '/'), ':');
	while (paths[i])
	{
		pos_path = ft_strjoin(paths[i], "/");
		pos_cmd_path = ft_strjoin(pos_path, cmd);
		free(pos_path);
		fd = open(pos_cmd_path, O_RDONLY);
		if (fd >= 0)
		{
			*path = pos_cmd_path;
			ft_free_split(paths);
			close(fd);
			return ;
		}
		free(pos_cmd_path);
		i++;
	}
	ft_free_split(paths);
}

/*
**	Executes the cmd when it is not a built-in.
*/

int	external(t_cmds *cmd, t_mini_data *data)
{
	char	*path;
	int	pid;

	pid = fork();
	if (pid < 0)
		return(FORKING);
	if (pid == 0)
	{
		get_cmd_path(cmd->cmd[0], data->envp, &path);
		execve(path, cmd->cmd, data->envp);
	}
	return (0);
}