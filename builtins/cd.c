/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:06:26 by jpizarro          #+#    #+#             */
/*   Updated: 2022/08/05 19:45:39 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Changes the beginning of the line with the content of the HOME variable.
**	Returns HOMELESS if this variable has been removed.
*/

int	ch_home_dir(t_mini_data *data, char *new_wd)
{
	t_env	**home;
	char	*abs_wd;

	home = search_env("HOME", &data->env);
	if (!home[0])
		return (HOMELESS);
	if (!new_wd)
		return(chdir(home[0]->var[1]));
	abs_wd = ft_strjoin(home[0]->var[1], &new_wd[1]);
	data->err_print = chdir(abs_wd);
	free(abs_wd);
	abs_wd = NULL;
	return (data->err_print);
}

/*
**	Changes the current working directory, along with the values of the
**	PWD and OLDPWD environment variables.
**	If the path is empty or starts with '~', it redirects to the directory
**	on the HOME environment variable.
*/


int	cd(t_mini_data *data, char **cmd, pid_t pid)
{
	char	*cwd;

	if ((data->cmd_num > 1 && pid) || (data->cmd_num == 1 && !pid))
		return (CONTINUE);
	cwd = getcwd(NULL, 0);
	if (!cmd[1] || cmd[1][0] == '~')
		data->err_print = ch_home_dir(data, cmd[1]);
	else
		data->err_print = chdir(cmd[1]);
	if (!data->err_print)
		set_env_value("OLDPWD", &cwd, data->env);
	free (cwd);
	if (data->err_print == HOMELESS)	
		return (manage_errors(cmd[0], HOMELESS, NULL));
	if (data->err_print < 0)	
		return (manage_errors(cmd[0], NOTFILE, cmd[1]));	//Needs the culprit
	cwd = getcwd(NULL, 0);
	set_env_value("PWD", &cwd, data->env);
	free (cwd);
	cwd = NULL;
	return (manage_errors(cmd[0], CONTINUE, NULL));
}