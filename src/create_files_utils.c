/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:44:44 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/26 10:44:49 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	create_in_files_other_me(t_parse *data, char *pwd)
{
	if (pwd)
		free(pwd);
	printf("minishell: %s: No such file or directory\n", data->text[0]);
	return (0);
}

int	create_in_files_me(t_parse *main_parse)
{
	t_parse	*nparse;
	char	str[256];
	char	*pwd;
	char	*tmp;

	nparse = main_parse->next;
	getcwd(str, 256);
	tmp = ft_strjoin(str, "/");
	pwd = ft_strjoin(tmp, nparse->text[0]);
	if (tmp)
		free(tmp);
	if (!access(pwd, F_OK))
		nparse->fd = open(pwd, O_RDONLY, 0777);
	else
	{
		if (pwd)
			free(pwd);
		printf("minishell: %s: No such file or directory\n",
			main_parse->text[0]);
		return (0);
	}
	if (pwd)
		free(pwd);
	main_parse->infile = nparse->fd;
	return (1);
}
