/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:47:08 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 18:04:14 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	run_echo(t_parse *data, int *i)
{
	int	x;
	int	j;

	x = *i;
	while (data->text[x])
	{
		j = 0;
		while (data->text[x][j])
			write(data->outfile, &data->text[x][j++], 1);
		if (data->text[x][j] == '\0' && data->text[x + 1] != NULL)
			write(data->outfile, " ", 1);
		x++;
		*i += 1;
	}
}

void	exec_echo(t_parse *data, t_shell *main_shell)
{
	int	i;

	i = 0;
	if (!data->text)
		write(data->outfile, "\n", 1);
	else
	{
		if (ft_strcmp(data->text[0], "-n") == 0)
		{
			i = 1;
			if (data->text[1])
				run_echo(data, &i);
		}
		else
		{
			run_echo(data, &i);
			if (!data->text[i])
				write(data->outfile, "\n", 1);
		}
	}
	main_shell->exec_status = 0;
}

void	print_list(void *data, t_shell *main_shell)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = main_shell->main_parse;
	new = (t_env *)data;
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	write(str->outfile, "=", 1);
	i = 0;
	while (new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

void	exec_env(t_shell *main_shell)
{
	ft_newlstiter(main_shell->env, print_list, main_shell);
	main_shell->exec_status = 0;
}

void	exec_exit(t_shell *main_shell)
{
	int	exec_status;
	int	len;
	int	flag;

	flag = 0;
	exec_status = 0;
	len = get_text_len(&main_shell->main_parse->text[0]);
	if (len > 1)
		flag = exit_error(1);
	else if (len == 1)
	{
		ft_exit_utils(main_shell, &exec_status);
	}
	else
		exec_status = 0;
	if (flag != 1)
		exit_free(main_shell, exec_status);
}
