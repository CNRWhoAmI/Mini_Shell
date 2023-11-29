/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:47:17 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/26 10:47:18 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	change_old(char *str, t_shell *main_shell)
{
	t_list	*tmp;
	t_env	*env;

	tmp = main_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			if (env->value)
				free(env->value);
			env->value = str;
		}
		tmp = tmp->next;
	}
}

void	_change_pwd(t_env **env)
{
	char	cwd[1024];

	if (!ft_strcmp((*env)->key, "PWD"))
	{
		if ((*env)->value)
			free((*env)->value);
		(*env)->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	}
}

void	change_pwd(t_parse	*data, t_shell *main_shell)
{
	t_list	*tmp;
	t_env	*env;
	char	cwd[1024];

	tmp = main_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "PWD")
			&& data->text && !ft_strcmp(data->text[0], "~"))
		{
			if (env->value)
				free(env->value);
			env->value = get_home(main_shell);
		}
		else if (!ft_strcmp(env->key, "PWD")
			&& data->text && !ft_strcmp(data->text[0], ".."))
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
		}
		_change_pwd(&env);
		tmp = tmp->next;
	}
}

void	exec_cd1(char *str, t_parse *data, t_shell *main_shell)
{
	change_old(str, main_shell);
	chdir(get_home(main_shell));
	change_pwd(data, main_shell);
	main_shell->exec_status = 0;
}

void	exec_cd(t_parse *data, t_shell *main_shell)
{
	char	cwd[1024];
	char	*str;

	str = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (data->text && data->text[0])
	{
		if (chdir(data->text[0]) == 0)
		{
			change_old(str, main_shell);
			change_pwd(data, main_shell);
			main_shell->exec_status = 0;
		}
		else
		{
			if (str)
				free(str);
			main_shell->exec_status = 1;
			perror("cd");
		}
	}
	else
		exec_cd1(str, data, main_shell);
}
