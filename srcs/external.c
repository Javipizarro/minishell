/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:37:10 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/18 10:56:31 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Returns the possible paths to the cmds on the system that are stored in
**	the PATH environment variable and returns them into a split.
**	Returns NULL if the PATH varible is not found.
*/

char	**get_system_paths(t_env *env)
{
	t_env	*env_path;

	env_path = *search_env("PATH", &env);
	if (!env_path)
		return (NULL);
	return (ft_split(env_path->var[1], ':'));
}

/*
**	Tries to open the command 'cmd' appliying the root path 'root' with a '/'
**	in between.
**	If root is NULL then applies the cmd directly.
**	Returns the pointer to the malloced path when it can be open, or
**	NULL otherwise.
*/

char	*test_path(char *root, char *cmd)
{
	int	fd;
	char	*temp;
	char	*path;

	temp = NULL;
	if (root)
	{
		temp = ft_strjoin(root, "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		temp = NULL;
	}
	else
		path = ft_strdup(cmd);
	fd = open(path, O_RDONLY);
	if (fd >= 0)
		close(fd);
	else
	{
		free(path);
		path = NULL;
	}
	return (path);
}

/*
**	Tries the cmd as it is, if this does not work, tries the different
**	possible paths resulting from combining the root_paths in the "PATH="
**	environment variable, and the cmd.
**	Returns the path that works malloced(3) or NULL if none of them has worked../
*/

char	*get_cmd_path(char *cmd, t_mini_data *data)
{
	int		i;
	char	**system_paths;
	char	*cwd;
	char 	*path;

	path = (test_path(NULL, cmd));
	if (path)
		return (path);
	cwd = getcwd(NULL, 0);	
	path = test_path(cwd,cmd);
	free(cwd);
	cwd = NULL;
	if (path)
		return (path);
	i = -1;
	system_paths = get_system_paths(data->env);
	if (!system_paths)
		return (NULL);
	while (system_paths[++i])
	{
		path = test_path(system_paths[i], cmd);
		if (path)
			break;
	}
	ft_free_split(system_paths);
	return (path);
}

/*
**	Executes the cmd when it is not a built-in.
*/

int	external(t_cmds *cmd, t_mini_data *data)
{
	char	*path;

	
	if (cmd->next && cmd->next->fd_in == PIPED)
		close(cmd->next->pipe[OUT]);
	path = get_cmd_path(cmd->cmd[0], data);
	if (!path)
		return (CMDERR);
	execve(path, cmd->cmd, data->envp);
	return (0);
}
