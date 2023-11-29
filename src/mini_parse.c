/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:46:27 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 15:09:38 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_parse	*main_parse_init(size_t len)
{
	t_parse	*main_parse;

	main_parse = malloc(sizeof(t_parse));
	if (!main_parse)
		return (NULL);
	(main_parse)->next = NULL;
	(main_parse)->cmd = NULL;
	(main_parse)->text = ft_calloc(sizeof(char *), len + 1);
	if (!(main_parse)->text)
		return (NULL);
	(main_parse)->type = 0;
	(main_parse)->infile = STDINN;
	(main_parse)->outfile = STDOUT;
	(main_parse)->fd = 1;
	(main_parse)->pid = 0;
	(main_parse)->control = 0;
	return (main_parse);
}

void	tokenize_type_m(t_parse **parse, const char *str)
{
	if (str[0] == '|')
		(*parse)->type = PIPE;
	else if (str[0] == '>' && str[1] == '>')
		(*parse)->type = GREATER;
	else if (str[0] == '<' && str[1] == '<')
	{
		(*parse)->type = HEREDOC;
		g_does_have_heredoc = 1;
	}
	else if (str[0] == '>')
		(*parse)->type = GREAT;
	else if (str[0] == '<')
		(*parse)->type = LESS;
}

void	parse_text_m(t_parse *parse, char *str, int *j, int *flag)
{
	parse->text[*j] = ft_strdup(str);
	*j += 1;
	parse->text[*j] = NULL;
	*flag = 1;
}

void	flag_(t_parse *parse)
{
	free_text(parse->text);
	parse->text = NULL;
}

void	mini_parse(t_list *lex, t_shell *main_shell, int order[3])
{
	char	*str;
	t_parse	*parse;

	parse = main_parse_init((size_t)ft_lstsize(lex));
	main_shell->main_parse = parse;
	while (lex)
	{
		str = lex->content;
		if (order[0]++ == 0 && ft_strcmp(str, "<<"))
			parse->cmd = ft_strdup(str);
		else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		{
			if (tokenize_type_m(&parse, str), str[0] == '|')
				order[0] = 0;
			parse->next = main_parse_init((size_t)ft_lstsize(lex));
			order[1] = 0;
			parse = parse->next;
		}
		else if (ft_strcmp(str, ""))
			parse_text_m(parse, str, &order[1], &order[2]);
		lex = lex->next;
	}
	if (order[2] == 0)
		flag_(parse);
}
