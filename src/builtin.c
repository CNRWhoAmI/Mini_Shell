/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:44:33 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/29 15:16:31 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_command(t_parse *parse, t_shell *main_shell)
{
	t_parse	*main_parse;

	main_parse = parse;
	if ((ft_strcmp(main_parse->cmd, "echo") == 0) || (ft_strcmp(main_parse->cmd,
				"ECHO") == 0))
		exec_echo(main_parse, main_shell);
	else if (ft_strcmp(main_parse->cmd, "cd") == 0)
		exec_cd(main_parse, main_shell);
	else if ((ft_strcmp(main_parse->cmd, "pwd") == 0)
		|| (ft_strcmp(main_parse->cmd, "PWD") == 0))
		exec_pwd(main_parse, main_shell);
	else if (ft_strcmp(main_parse->cmd, "export") == 0)
		exec_export(main_parse, main_shell, 0, 0);
	else if (ft_strcmp(main_parse->cmd, "unset") == 0)
		exec_unset(main_parse, main_shell, 0, 0);
	else if (((ft_strcmp(main_parse->cmd, "env") == 0)
			|| (ft_strcmp(main_parse->cmd, "ENV") == 0)))
		exec_env(main_shell);
	else if (ft_strcmp(main_parse->cmd, "exit") == 0)
		exec_exit(main_shell);
}

int	is_builtin(t_parse *data)
{
	if ((ft_strcmp(data->cmd, "echo") == 0) || (ft_strcmp(data->cmd,
				"ECHO") == 0))
		return (1);
	else if ((ft_strcmp(data->cmd, "pwd") == 0) || (ft_strcmp(data->cmd,
				"PWD") == 0))
		return (1);
	else if ((ft_strcmp(data->cmd, "env") == 0) || (ft_strcmp(data->cmd,
				"ENV") == 0))
		return (1);
	else if ((ft_strcmp(data->cmd, "cd") == 0))
		return (1);
	else if ((ft_strcmp(data->cmd, "export") == 0))
		return (1);
	else if ((ft_strcmp(data->cmd, "unset") == 0))
		return (1);
	else if ((ft_strcmp(data->cmd, "exit") == 0))
		return (1);
	return (0);
}
