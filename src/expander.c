/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:45:47 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/26 10:45:50 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*ft_mini_strdup(const char *str)
{
	char	*s;
	size_t	len;
	int		qulen;
	int		i;

	i = 0;
	qulen = 2 * quate_len(str);
	len = ft_strlen(str);
	s = (char *)malloc(sizeof(char) * (len - qulen + 1));
	if (!s)
		return (NULL);
	return (ft_mini_strdup2(len, s, i, str));
}

void	ft_tilde(char *lex_str, char *env_value, t_list *lex)
{
	int		i;
	int		j;
	char	*key;

	j = 0;
	i = 0;
	key = malloc(sizeof(char) * (ft_strlen(env_value) + 1));
	if (!key)
		return ;
	if (ft_strchr(lex_str, '/'))
	{
		lex_str = ft_strchr(lex_str, '/');
		while (env_value[i])
		{
			key[j] = env_value[i++];
			j++;
		}
		key[j] = '\0';
		ft_tilde_build1(lex, key, lex_str);
	}
	else
		ft_tilde_build2(lex, env_value);
	free(key);
}

int	check_env(t_list *lex, char *lex_str, int i, t_shell *main_shell)
{
	t_env	*y;
	char	*x;
	t_list	*env;

	env = main_shell->env;
	x = ft_strdup((char *)lex->content);
	while (env)
	{
		y = env->content;
		if (lex_str[i] == '~' && ft_strcmp(y->key, "HOME") == 0)
			ft_tilde(lex_str, y->value, lex);
		if (lex_str[i] == '$' && lex_str[i + 1] == '?')
			ft_exit_status(lex_str, lex, main_shell);
		else if (lex_str[i] == '$'
			&& ft_isdigit(lex_str[i + 1]) && lex_str[i + 2])
			get_after_num(lex_str, lex, i + 2);
		else if (lex_str[i] == '$')
			does_dollar_make_sense(lex_str, lex, env, i + 1);
		env = env->next;
	}
	if (!ft_strcmp(x, (char *)lex->content))
		erase_after(lex_str, lex, i + 1);
	free(x);
	return (0);
}

void	get_env_to_lexlist(t_shell *main_shell, int i, char *lex_str,
		t_list *lex)
{
	lex = main_shell->lex_list->lex;
	while (lex)
	{
		i = 0;
		lex_str = ft_strdup(lex->content);
		while (lex_str[i])
		{
			env_lex_list_(&lex, &lex_str, i, main_shell);
			if (lex_str[i] == '$' && lex_str[0] != '\'')
			{
				check_env(lex, lex_str, i, main_shell);
				if (!ft_strcmp(lex->content, ""))
					break ;
			}
			free(lex_str);
			(lex_str) = ft_strdup((lex)->content);
			i++;
		}
		if (lex->content)
			free(lex->content);
		lex->content = ft_mini_strdup(lex_str);
		free(lex_str);
		(lex) = (lex)->next;
	}
}

void	expander(t_shell *main_shell)
{
	char	*lex_str;
	t_list	*lex;

	lex = NULL;
	lex_str = NULL;
	if (ft_strcmp(main_shell->cmd, ""))
		get_env_to_lexlist(main_shell, 0, lex_str, lex);
}
