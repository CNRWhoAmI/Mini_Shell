/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:45:53 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 18:14:45 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	print_error(void)
{
	printf("%s\n", "minishell: syntax error near unexpected token");
	return (0);
}

int	exit_error(int flag)
{
	if (flag == 1)
	{
		printf("Exit:too many arguments\n");
		return (1);
	}
	else if (flag == 2)
	{
		printf("Exit: numeric argument required\n");
		exit(255);
	}
	return (0);
}

void	ft_exit_utils(t_shell *main_shell, int *exec_status)
{
	if (!(is_numeric(main_shell->main_parse->text[0])))
		exit_error(2);
	else
	{
		if ((is_numeric(main_shell->main_parse->text[0])))
			*exec_status = ft_atoi(main_shell->main_parse->text[0]);
		else
			exit_error(2);
	}
}

int	is_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (!cmd[i])
		return (0);
	return (1);
}

int	get_text_len(char **array)
{
	int	count;

	count = 0;
	while (array && *(array++))
		count++;
	return (count);
}
