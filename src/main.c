/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:46:23 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 16:51:00 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

int		g_does_have_heredoc;

void	shell_init(t_shell **main_shell, int ac)
{
	if (ac != 1)
		exit(printf("This program cannot accept any arguments\n"));
	*main_shell = malloc(sizeof(t_shell));
	if (!(*main_shell))
		return ;
	(*main_shell)->env = malloc(sizeof(t_env));
	(*main_shell)->lex_list = malloc(sizeof(t_lexer));
	(*main_shell)->main_parse = NULL;
	(*main_shell)->lex_list->lex = NULL;
	(*main_shell)->exec_status = 0;
	(*main_shell)->heredoc = NULL;
	(*main_shell)->cmd = NULL;
	g_does_have_heredoc = 0;
	signals_control();
}

void	get_readline(t_shell *main_shell)
{
	main_shell->cmd = readline("minishell-$ ");
	if (main_shell->cmd && !is_space(main_shell->cmd))
	{
		free(main_shell->cmd);
		get_readline(main_shell);
	}
	if (!main_shell->cmd)
	{
		free_loop(0, main_shell);
		free_(main_shell);
		free(main_shell->lex_list);
		free(main_shell);
		exit(1);
	}
	add_history(main_shell->cmd);
}

void	go_parser(char **env, t_shell *main_shell)
{
	if (ft_strcmp(main_shell->cmd, ""))
	{
		if (ft_parser(main_shell))
		{
			exec(env, main_shell);
		}
	}
}

void	error_free(t_list **node)
{
	if (!*node)
		return ;
	if ((*node)->next != NULL)
		free_node((*node)->next);
	if ((*node)->content)
		(*node)->content = (free((*node)->content), NULL);
	if ((*node))
		(*node) = (free(*node), NULL);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*main_shell;
	int		control;

	(void)av;
	shell_init(&main_shell, ac);
	env_get(env, &main_shell);
	while (1)
	{
		get_readline(main_shell);
		if (quote_check(main_shell->cmd))
		{
			lexer(main_shell);
			expander(main_shell);
			control = check(main_shell);
			if (control)
				go_parser(env, main_shell);
			else
				error_free(&(main_shell->lex_list)->lex);
		}
		if (quote_check(main_shell->cmd) == 1)
			free_loop(control, main_shell);
		else
			free(main_shell->cmd);
	}
}
