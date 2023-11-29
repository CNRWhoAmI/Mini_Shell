/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:46:03 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 16:05:25 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

void	killer(int sig)
{
	(void)sig;
	g_does_have_heredoc = -3;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	set_heredoc(int sig)
{
	(void)sig;
	g_does_have_heredoc = -10;
}

int	quote_check1(char *data)
{
	int		i;
	int		flag;
	char	c;

	flag = 1;
	i = 0;
	while (data[i])
	{
		if (data[i] == '\"' || data[i] == '\'')
		{
			c = data[i];
			i++;
			while (data[i] != c && data[i])
				i++;
			if (data[i] == c)
				flag = 1;
			else
				return (0);
		}
		i++;
	}
	return (flag);
}
