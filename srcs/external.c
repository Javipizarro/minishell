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
**	Tries to open the command 'cmd' appliying the root path 'root' with a '/'
**	in between.
**	If root is NULL then applies the cmd directly.
**	Returns the pointer to the malloced path when it can be open, or
**	NULL otherwise.
*/

char	*test_path(char *root, char *cmd)
{
	int	fd;
	int	free_root;
	char	*temp;
	char	*path;

	free_root = 0;
	if (!root && ++free_root)
		root = getcwd(NULL, 0);
	temp = ft_strjoin(root, "/");
	if (free_root)
		free(root);
	path = ft_strjoin(temp, cmd);
	free(temp);
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

char	*get_cmd_path(char *cmd, char *environ[])
{
	int		i;
	char	*path;
	char	**root_paths;

	path = test_path(NULL, cmd);
	if (path)
		return (path);
	i = -1;
	root_paths = ft_split(ft_strchr(get_env_path(environ), '/'), ':');
	while (root_paths[++i])
	{
		path = test_path(root_paths[i], cmd);
		if (path)
			break;
		path = NULL;
	}
	ft_free_split(root_paths);
	return (path);
}

/*
**	Executes the cmd when it is not a built-in.
*/

int	external(t_cmds *cmd, t_mini_data *data)
{
	char	*path;

	if (cmd->fd_out >= 0)
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			return (DUPING);
	if (cmd->next && cmd->next->fd_in == PIPED)
		close(cmd->next->pipe[OUT]);
	path = get_cmd_path(cmd->cmd[0], data->envp);
	if (!path)
		return (CMDERR);
	execve(path, cmd->cmd, data->envp);
	return (0);
}