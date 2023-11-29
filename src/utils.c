/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:47:44 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 12:16:37 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	wait_all(t_shell *main_shell)
{
	t_parse	*data;

	data = main_shell->main_parse;
	while (data)
	{
		if (!data->next)
			waitpid(data->pid, &main_shell->exec_status, 0);
		else
			waitpid(data->pid, 0, 0);
		data = data->next;
	}
	main_shell->exec_status = WEXITSTATUS(main_shell->exec_status);
}

void	clear_pipe(int *fd)
{
	int	index;

	if (fd)
	{
		index = -1;
		while (++index < 2)
		{
			if (fd[index])
				close(fd[index]);
		}
		if (fd)
			free(fd);
	}
}

void	_multi_command(t_parse **parse)
{
	if ((*parse)->infile > STDERR || (*parse)->outfile > STDERR
		|| (*parse)->type == HEREDOC)
	{
		(*parse) = (*parse)->next->next;
	}
	else
	{
		(*parse) = (*parse)->next;
	}
}

void	ft_newlstiter(t_list *lst, void (*f)(), t_shell *shell)
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content, shell);
		lst = lst->next;
	}
}

char	*ft_mini_strdup2(size_t len, char *s, int i, const char *str)
{
	int	j;

	j = 0;
	while (i < (int)len)
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				s[j++] = str[i++];
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				s[j++] = str[i++];
			i++;
		}
		else
			s[j++] = str[i++];
	}
	s[j] = '\0';
	return (s);
}
