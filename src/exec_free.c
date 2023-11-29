/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:45:08 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 14:06:21 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

void	_free_env(t_list *tmp2, t_shell *main_shell)
{
	t_env	*tmp;

	while (tmp2)
	{
		tmp = tmp2->content;
		if (tmp2->content)
		{
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
		tmp2 = tmp2->next;
	}
	while (main_shell->env)
	{
		tmp2 = main_shell->env;
		main_shell->env = main_shell->env->next;
		if (tmp2)
			free(tmp2);
	}
}

void	free_env(t_shell *main_shell)
{
	t_list	*tmp2;

	tmp2 = main_shell->env;
	if (tmp2 && tmp2->content)
		_free_env(tmp2, main_shell);
	else if (main_shell->env && !main_shell->env->content)
		free(main_shell->env);
}

void	free_(t_shell *main_shell)
{
	free_env(main_shell);
	rl_clear_history();
}

void	free_loop(int control, t_shell *main_shell)
{
	if (main_shell->cmd)
		free(main_shell->cmd);
	if (control)
	{
		if (main_shell->main_parse)
			free_parser(main_shell);
	}
	if (main_shell->heredoc)
	{
		free(main_shell->heredoc);
		main_shell->heredoc = NULL;
	}
}

void	execve_child_free(char **str, t_shell *main_shell)
{
	free_(main_shell);
	free_loop(1, main_shell);
	free_text(str);
	free(main_shell->lex_list);
	free(main_shell);
}
