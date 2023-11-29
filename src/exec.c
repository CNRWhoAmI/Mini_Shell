/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:45:23 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 17:11:53 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	run_command(char **env, t_parse *tmp, int *fd, t_shell *main_shell)
{
	int	control;

	control = is_builtin(tmp);
	if (control)
	{
		execute_builtin_command(tmp, main_shell);
		main_shell->exec_status = 0;
	}
	else
		exec_others(tmp, env, fd, main_shell);
	free_(main_shell);
	free_loop(1, main_shell);
	free(main_shell->lex_list);
	free(main_shell);
	exit(0);
}

void	run_single_command(char **env, t_parse *parse, t_shell *main_shell)
{
	int	control;
	int	i;

	i = 0;
	control = 0;
	if (parse->type != HEREDOC)
		control = is_builtin(parse);
	if (control)
	{
		execute_builtin_command(main_shell->main_parse, main_shell);
		main_shell->exec_status = 0;
	}
	else
		exec_others(main_shell->main_parse, env, NULL, main_shell);
}

void	multi_command_(t_parse *main_parse, char **env, t_shell *main_shell,
		int *fd)
{
	t_parse	*nparse;
	int		x;

	x = 0;
	while (main_parse)
	{
		if (main_parse->next)
			pipe(fd);
		nparse = _next_command(&main_parse);
		main_parse->pid = fork();
		if (main_parse->pid == 0)
		{
			create_dup_one(main_parse, fd);
			run_command(env, main_parse, fd, main_shell);
		}
		if (nparse)
			create_dup_two(nparse, fd);
		main_parse = nparse;
	}
}

void	multi_command(char **env, int x, t_parse *parse, t_shell *main_shell)
{
	int		*fd;
	t_parse	*main_parse;

	(void)x;
	main_parse = parse;
	main_shell->main_parse->std_in = dup(0);
	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return ;
	multi_command_(main_parse, env, main_shell, fd);
	dup2(main_shell->main_parse->std_in, 0);
	clear_pipe(fd);
	wait_all(main_shell);
}

void	exec(char **env, t_shell *main_shell)
{
	int	x;

	if (g_does_have_heredoc != 0)
		loop_heredoc(main_shell);
	if (!ft_strcmp(main_shell->cmd, ""))
		return ;
	x = single_or_multi_command(main_shell);
	if (!x && g_does_have_heredoc != -10)
		run_single_command(env, main_shell->main_parse, main_shell);
	else if (g_does_have_heredoc != -10)
		multi_command(env, 0, main_shell->main_parse, main_shell);
	g_does_have_heredoc = 0;
}
