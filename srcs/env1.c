/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:49 by jpizarro          #+#    #+#             */
/*   Updated: 2022/05/17 01:22:30 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Checks whether the SHLVL, PWD, OLDPWD and _ environment variables are set,
**	and sets them if they aren't.
*/

void	check_basic_env(t_env **env)
{
	char	*buff;
	char	*joint;

	if (!*search_env("SHLVL", env))
		export_env("SHLVL=1", env);
	if (!*search_env("PWD", env))
	{
		buff = getcwd(NULL, 0);
		joint = ft_strjoin("PWD=", buff);
		export_env(joint, env);
		free(buff);
		buff = NULL;
		free(joint);
		joint = NULL;
	}
	if (!*search_env("OLDPWD", env))
		export_env("OLDPWD=", env);
	if (!*search_env("_", env))
		export_env("_=", env);
}

/*
**	Searches the SHLVL environment variable and adds one to its value.
*/

void	shlvl_up(t_env **env)
{
	int lvl;

	env = search_env("SHLVL", env);
	if (!env[0])
		return;
	lvl = ft_atoi(env[0]->var[1]);
	lvl++;
	env[0]->var[1] = ft_itoa(lvl);
}

/*
**	Receives a pointer to the t_mini_data structure and sets up the env member
**	ready to work in the new minishell.
*/

void	set_env_list(char *envp[], t_mini_data *data)
{
	int 	i;

	i = -1;
	while (envp[++i])
		export_env(envp[i], &data->env);
	shlvl_up(&data->env);
	check_basic_env(&data->env);
	reset_envp(data);
}

/*
**	Sets the value of the environment variable env_name to the value env_val.
**	It returns the pointer to the t_env link where this variable is stored or NULL
**	if env_name doesn't exists.
*/

t_env	*set_env_value(char **var, int def, t_env *env)
{
	char	*temp;

	if (!var[1] && !def)
		return (env);
	env = *search_env(var[0], &env);
	if (!env)
		return (env);
//	if (env->var[1])
		temp = env->var[1];
//	else
//		temp = NULL;
	if (var[1])
		env->var[1] = var[1];
	else
		env->var[1] = ft_strdup("");
	var[1] = temp;
	return(env);
}
