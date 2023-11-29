/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:46:07 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/26 10:46:09 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

char	*add_char(char *str, char a)
{
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(str);
	tmp = malloc(sizeof(char) * (len + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	if (!a)
	{
		free(tmp);
		return (NULL);
	}
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = a;
	tmp[i + 1] = '\0';
	free(str);
	return (tmp);
}

void	get_var(int *fd, t_shell *main_shell)
{
	char	*a;

	a = malloc(sizeof(char));
	if (!a)
	{
		main_shell->heredoc = NULL;
		return ;
	}
	main_shell->heredoc = ft_calloc(sizeof(char), 2);
	if (!main_shell->heredoc)
	{
		free(a);
		return ;
	}
	while (read(fd[0], a, 1))
	{
		main_shell->heredoc = add_char(main_shell->heredoc, *a);
		free(a);
		a = malloc(sizeof(char));
		if (!a)
			return ;
	}
	if (a)
		free(a);
	close(fd[0]);
}

void	get_input(t_parse *parse, int *fd)
{
	char		*delimiter;
	char		*buffer;

	delimiter = parse->next->text[0];
	while (1 && g_does_have_heredoc != -3)
	{
		buffer = readline("> ");
		if (ft_strcmp(buffer, delimiter) == 0)
		{
			if (buffer)
				free(buffer);
			break ;
		}
		write(fd[1], buffer, ft_strlen(buffer));
		write(fd[1], "\n", 1);
		if (buffer)
			free(buffer);
	}
}

void	heredoc(t_parse *parse, t_shell *main_shell)
{
	int		fd[2];
	int		id;

	pipe(fd);
	signal(SIGINT, set_heredoc);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, killer);
		close(fd[0]);
		get_input(parse, fd);
		close(fd[1]);
		free_(main_shell);
		free_loop(1, main_shell);
		free(main_shell->lex_list);
		free(main_shell);
		exit(1);
	}
	waitpid(-1, NULL, 0);
	signal(SIGINT, signals);
	close(fd[1]);
	get_var(fd, main_shell);
}

void	loop_heredoc(t_shell *main_shell)
{
	t_parse	*parse;

	parse = main_shell->main_parse;
	while (parse)
	{
		if (parse->type == HEREDOC)
		{
			heredoc(parse, main_shell);
		}
		parse = parse->next;
	}
}
