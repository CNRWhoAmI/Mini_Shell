/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:45:31 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/26 12:39:03 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	ft_tilde_build1(t_list *lex, char *key, char *lex_str)
{
	if (lex->content)
		free(lex->content);
	lex->content = ft_strjoin(key, lex_str);
}

void	ft_tilde_build2(t_list *lex, char *str)
{
	if (lex->content)
		free(lex->content);
	lex->content = ft_strdup(str);
}

char	*before_dollar(char *lex_str)
{
	char	*str;
	int		i;

	i = 0;
	while (lex_str[i])
	{
		if (lex_str[i] == '$')
		{
			str = ft_substr(lex_str, 0, i);
			if (i != 0)
				return (str);
			else
			{
				free(str);
				break ;
			}
		}
		i++;
	}
	return (NULL);
}

void	get_after_num(char *lex_str, t_list *lex, int i)
{
	char	*before;
	char	*str;

	str = NULL;
	before = before_dollar(lex_str);
	if (before)
	{
		if (lex->content)
			free(lex->content);
		str = ft_substr(lex_str, i, ft_strlen(lex_str) - i);
		lex->content = ft_strjoin(before, str);
	}
	else
	{
		if (lex->content)
			free(lex->content);
		lex->content = ft_substr(lex_str, i, ft_strlen(lex_str) - i);
	}
	if (before)
		free(before);
	if (str)
		free(str);
}
