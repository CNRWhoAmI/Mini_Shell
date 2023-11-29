/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:45:14 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 14:15:50 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	free_text(char **text)
{
	int	i;

	i = 0;
	if (text)
	{
		if (text[i])
		{
			while (text[i])
				free(text[i++]);
		}
		free(text);
	}
}

void	_free_parse(t_parse *main_parse)
{
	t_parse	*tmp;

	while (main_parse)
	{
		tmp = main_parse;
		main_parse = main_parse->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->text)
			free_text(tmp->text);
		free(tmp);
	}
}

void	free_parser(t_shell *main_shell)
{
	t_parse	*parse;

	parse = main_shell->main_parse;
	if (parse)
		_free_parse(parse);
	else if (main_shell->main_parse)
		free(main_shell->main_parse);
}

int	*create_pipe(void)
{
	int	index;
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 6);
	if (!fd)
		return (NULL);
	index = -1;
	while (++index < 6)
		fd[index] = 0;
	return (fd);
}

void	exit_free(t_shell *main_shell, int exec_status)
{
	free_(main_shell);
	free_loop(1, main_shell);
	free(main_shell->lex_list);
	free(main_shell);
	write(1, "exit\n", 5);
	exit(exec_status % 256);
}
