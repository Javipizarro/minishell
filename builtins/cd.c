/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:06:26 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/20 19:20:51 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Changes the beginning of the line with the content of the HOME variable.
**	Returns HOMELESS if this variable has been removed.
*/

int	ch_home_dir(t_mini_data *data, char *new_wd)
{
	char	*home;
	char	*abs_wd;

	home = search_env("HOME", &data->env)[0]->var[1];
	if (!home)
		return (HOMELESS);
	if (!new_wd)
		return(chdir(home));
	abs_wd = ft_strjoin(home, &new_wd[1]);
	data->err = chdir(abs_wd);
	free(abs_wd);
	abs_wd = NULL;
	return (data->err);
}

/*
**	Changes the current working directory, along with the values of the
**	PWD and OLDPWD environment variables.
**	If the path is empty or starts with '~', it redirects to the directory
**	on the HOME environment variable.
*/


int	cd(t_mini_data *data, char **cmd, int pid)
{
	char	*cwd;

	if (!pid)
		return (CONTINUE);
	cwd = getcwd(NULL, 0);
	if (!cmd[1] || cmd[1][0] == '~')
		data->err = ch_home_dir(data, cmd[1]);
	else
		data->err = chdir(cmd[1]);
	if (!data->err)
		set_env_value("OLDPWD", &cwd, data->env);
	free (cwd);
	if (data->err == HOMELESS)	
		return (HOMELESS);
	if (data->err < 0)	
		return (NOTFILE);
	cwd = getcwd(NULL, 0);
	set_env_value("PWD", &cwd, data->env);
	free (cwd);
	cwd = NULL;
	return (CONTINUE);
}