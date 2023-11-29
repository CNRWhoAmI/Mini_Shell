/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:47:21 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/26 10:47:22 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	edit_env_(t_list *node, char *key, char *value, t_shell *main_shell)
{
	t_env	*new_env;

	if (node == NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return ;
		new_env->key = key;
		new_env->value = value;
		ft_lstadd_back(&(main_shell->env), ft_lstnew(new_env));
	}
}

void	exec_pwd(t_parse *data, t_shell *main_shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(data->outfile, &cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		main_shell->exec_status = 0;
	}
	else
	{
		perror("getcwd");
		main_shell->exec_status = 1;
	}
}

char	*get_home(t_shell *main_shell)
{
	t_list	*tmp;
	t_env	*env;

	tmp = main_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "HOME"))
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}
