/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:47:25 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/29 13:49:26 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*search_command(char *cmd, char **value)
{
	char	*data;
	int		i;
	char	*tmp;
	char	*substring;

	tmp = *value;
	i = 0;
	(void)cmd;
	while (*tmp && *tmp != ':')
	{
		i++;
		tmp++;
	}
	if (!i)
		return (NULL);
	substring = ft_substr(*value, 0, i);
	data = ft_strjoin(substring, "/");
	free(substring);
	substring = ft_strjoin(data, cmd);
	free(data);
	*value = *value + i + 1;
	return (substring);
}

char	*_search_path(t_shell *main_shell)
{
	t_env	*env;
	t_list	*tmp;
	char	*value;

	value = NULL;
	tmp = main_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			value = env->value;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	search_path(t_parse *data, int i, t_shell *main_shell)
{
	char	*value;
	char	*str;
	int		x;

	x = -1;
	str = NULL;
	value = _search_path(main_shell);
	while (x != 0 && value && ++i < 10)
	{
		if (str)
			free(str);
		str = search_command(data->cmd, &value);
		x = access(str, F_OK);
		if (str && x == 0)
		{
			if (data->cmd)
				free(data->cmd);
			data->cmd = ft_strdup(str);
		}
	}
	if (str)
		free(str);
}

void	run_execve(t_parse *parse, char **env, int *fd, t_shell *main_shell)
{
	char		**full_cmd;

	search_path(parse, -1, main_shell);
	parse->pid = fork();
	full_cmd = NULL;
	if (!parse->pid)
	{
		full_cmd = get_args(parse);
		create_dup(main_shell, parse);
		if ((execve(parse->cmd, full_cmd, env) == -1))
		{
			if (parse->cmd && ft_strcmp(parse->cmd, "<<"))
				printf("minishell: %s: command not found\n", parse->cmd);
			execve_child_free(full_cmd, main_shell);
			exit(127);
		}
	}
	if (fd && parse->pid)
		clear_pipe(fd);
	waitpid(parse->pid, &main_shell->exec_status, 0);
	main_shell->exec_status = WEXITSTATUS(main_shell->exec_status);
}

void	exec_others(t_parse *parse, char **env, int *fd, t_shell *main_shell)
{
	run_execve(parse, env, fd, main_shell);
}
