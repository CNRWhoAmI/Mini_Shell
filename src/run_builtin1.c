/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:47:12 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/29 15:19:43 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	edit_env(t_list *node, char *key, char *value, t_shell *main_shell)
{
	t_env	*env;

	while (node != NULL)
	{
		env = (t_env *)node->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(value);
			free(value);
			free(key);
			return ;
		}
		node = node->next;
	}
	edit_env_(node, key, value, main_shell);
}

void	declare_export(void *data, t_shell *main_shell)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = main_shell->main_parse;
	new = (t_env *)data;
	write(str->outfile, "declare -x ", 11);
	while (new->key[i])
	{
		write(str->outfile, &new->key[i++], 1);
	}
	if (new->value)
		write(str->outfile, "=", 1);
	i = 0;
	if (new->value)
	{
		while (new->value[i])
			write(str->outfile, &new->value[i++], 1);
	}
	write(str->outfile, "\n", 1);
}

void	exec_export(t_parse *data, t_shell *main_shell, int i, int keylen)
{
	char	*key;
	char	*v;

	key = NULL;
	v = NULL;
	if (data->text == NULL)
		ft_newlstiter(main_shell->env, declare_export, main_shell);
	else if (!ft_strchr(data->text[0], '='))
	{
		while (data->text[0][keylen++])
			key = ft_substr(data->text[0], 0, keylen);
		edit_env(main_shell->env, key, v, main_shell);
		return ;
	}
	else
	{
		while (data->text[i])
		{
			key = ft_substr(data->text[i], 0, chrin(data->text[i], '='));
			v = ft_substr(data->text[i], chrin(data->text[i], '=') + 1,
					(ft_strlen(data->text[i]) - 1));
			edit_env(main_shell->env, key, v, main_shell);
			i++;
		}
	}
}

int	unset_edit(t_list **node, t_list **prev_node, t_shell *main_shell)
{
	t_env	*tmp;

	tmp = (*node)->content;
	if (*prev_node == NULL)
		main_shell->env = (*node)->next;
	else
		(*prev_node)->next = (*node)->next;
	free(tmp->key);
	free(tmp->value);
	free((*node)->content);
	free(*node);
	return (1);
}

void	exec_unset(t_parse *data, t_shell *main_shell, int i, int x)
{
	t_list	*prev_node;
	t_list	*node;
	t_env	*env;

	env = NULL;
	if (data->text == NULL)
		return ;
	while (data->text[i])
	{
		prev_node = NULL;
		node = main_shell->env;
		while (node != NULL)
		{
			env = (t_env *)node->content;
			if (ft_strcmp(env->key, data->text[i]) == 0)
				x = unset_edit(&node, &prev_node, main_shell);
			if (x)
				break ;
			prev_node = node;
			node = node->next;
		}
		i++;
	}
}
