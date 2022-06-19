/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:06:26 by jpizarro          #+#    #+#             */
/*   Updated: 2022/06/19 18:31:42 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(t_mini_data *data, char **cmd, int pid)
{
	char	*cwd;
	t_env	*home;

	if (!pid)
		return (CONTINUE);
	cwd = getcwd(NULL, 0);
	if (!cmd[1] || cmd[1] == '~')
	{
		home = *search_env("HOME", data->env)[0]->var[1];
		if (!home)
			return (HOMELESS);
		data->err = chdir(home->var[1]);
	}
	else
		data->err = chdir(cmd[1]);
	if (!data->err)
		set_env_value("OLDPWD", &cwd, data->env);
	free (cwd);
	if (data->err)	
		return (NOTFILE);
	cwd = getcwd(NULL, 0);
	set_env_value("PWD", &cwd, data->env);
	free (cwd);
	cwd = NULL;
	return (CONTINUE);
}