/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:46:32 by eozdur            #+#    #+#             */
/*   Updated: 2023/11/28 18:04:04 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# define EXEC 0
# define HEREDOC 1
# define PIPE 2
# define GREAT 3
# define GREATER 4
# define LESS 5
# define STDINN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_env
{
	char				*key;
	char				*value;
}						t_env;

typedef struct s_data
{
	char				*read_data;
}						t_data;

typedef struct s_lexer
{
	t_list				*lex;
}						t_lexer;

typedef struct s_main_parse
{
	char				*cmd;
	char				**text;
	int					type;
	int					outfile;
	int					infile;
	int					fd;
	int					pid;
	int					control;
	int					std_in;
	struct s_main_parse	*next;
}						t_parse;

typedef struct s_shell
{
	t_parse				*main_parse;
	t_list				*env;
	char				*cmd;
	t_lexer				*lex_list;
	t_list				*parse;
	char				*heredoc;
	int					exec_status;
	int					kill;
}						t_shell;

extern int				g_does_have_heredoc;

int						is_space(char *cmd);
void					_create_dup(t_shell *main_shell);
void					ft_newlstiter(t_list *lst, void (*f)(), t_shell *shell);
void					fd_init(int *fd);
void					create_dup_two(t_parse *parse, int *fd);
void					create_dup_one(t_parse *parse, int *fd);
int						create_in_files_me(t_parse *main_parse);
int						ignore_quote(char const *cmd, int i);
int						check_what_is(const char *cmd, int i);
char					*ft_make_words(char *word, char const *s, int j,
							int word_ln);
void					mini_parse(t_list *lex, t_shell *main_shell, int a[3]);
t_parse					*parse_(int *j, t_list *new, int *i);
char					*after_dark2(char *key, char *tmp);
char					*quote_control(char *tmp);
char					*set_build(char *str);
char					*before_dollar(char *tmp);
char					*_search_path(t_shell *main_shell);
int						ft_ultimatestrcmp(char *key, char *tmp, int i);
int						quote_len(char *data);
int						check(t_shell *main_shell);
int						is_builtin(t_parse *tmp);
int						single_or_multi_command(t_shell *main_shell);
int						ft_parser(t_shell *main_shell);
int						create_files(void);
int						create_files_m(t_shell *main_shell);
int						create_in_files(t_parse *data3, t_list *tmp3);
int						quote_check(char *data);
int						quote_check1(char *data);
int						print_error(void);
int						create_files(void);
void					signals(int sig);
void					signals_control(void);
void					free_str1(char *str1, int flag);
int						quate_len(const char *str);
void					free_tmps(char *str, char *str2, char *str_tmp);
void					_ft_exit_status(t_list *data, char *str1);
void					set_heredoc(int sig);
void					killer(int sig);
void					clear_pipe(int *fd);
void					env_get(char **env, t_shell **shell);
void					get_readline(t_shell *main_shell);
void					lexer(t_shell *main_shell);
void					expander(t_shell *main_shell);
void					get_env_to_lexlist(t_shell *main_shell, int i,
							char *lex_str, t_list *lex);
void					print_list(void *data, t_shell *main_shell);
void					exec(char **env, t_shell *main_shell);
void					loop_heredoc(t_shell *main_shell);
void					run_single_command(char **env, t_parse *data,
							t_shell *main_shell);
void					free_env(t_shell *main_shell);
void					free_parser(t_shell *main_shell);
void					free_loop(int control, t_shell *main_shell);
void					free_lexer(void);
void					free_text(char **text);
void					free_(t_shell *main_shell);
void					erase_after(char *tmp, t_list *data, int i);
void					free_tmp_tmp2(char *tmp, char *tmp2);
void					ft_tilde_build1(t_list *data, char *key, char *tmp);
void					ft_tilde_build2(t_list *data, char *str);
void					get_after_num(char *tmp, t_list *data, int i);
void					quote_build(char **tmp, char **data, int *i, int *j);
void					ft_exit_status(char *tmp, t_list *data,
							t_shell *main_shell);
void					free_node(t_list *node);
void					welcome_to_parse(t_list *node, int i, int j, int flag);
void					get_text(t_parse **parse, char *str, int j, int a);
void					tokenize_type(t_parse **parse, const char *str);
void					free_parse(t_parse *parse);
void					parse_init(void);
void					does_dollar_make_sense(char *tmp, t_list *data,
							t_list *shell_data, int i);
void					_does_dollar_make_sense(t_env *y, char *before,
							char *after, t_list *data);
void					exec_echo(t_parse *data, t_shell *main_shell);
void					exec_env(t_shell *main_shell);
void					exec_export(t_parse *data, t_shell *main_shell, int i,
							int keylen);
void					exec_unset(t_parse *data, t_shell *main_shell, int i,
							int x);
void					exec_pwd(t_parse *data, t_shell *main_shell);
void					exec_cd(t_parse *data, t_shell *main_shell);
void					create_dup(t_shell *main_shell, t_parse *parse);
void					clear_pipe(int *fd);
int						*create_pipe(void);
void					switch_pipe(int **fd);
void					exec_exit(t_shell *main_shell);
void					wait_all(t_shell *main_shell);
int						get_text_len(char **array);
void					execute_builtin_command(t_parse *parse,
							t_shell *main_shell);
void					exec_others(t_parse *data, char **env, int *fd,
							t_shell *main_shell);
char					*get_home(t_shell *main_shell);
char					**get_args(t_parse *data);
void					execve_child_free(char **str, t_shell *main_shell);
int						*create_pipe(void);
int						exit_error(int flag);
int						is_numeric(char *text);
void					exit_free(t_shell *main_shell, int exec_status);
t_parse					*_next_command(t_parse **parse);
void					ft_exit_utils(t_shell *main_shell, int *exec_status);
char					*ft_mini_strdup2(size_t len, char *s, int i,
							const char *str);
void					env_lex_list_(t_list **lex, char **lex_str, int i,
							t_shell *main_shell);
int						check_env(t_list *lex, char *lex_str, int i,
							t_shell *main_shell);
void					ft_count_words_(char const *cmd, int *i);
void					edit_env_(t_list *node, char *key, char *value,
							t_shell *main_shell);

#endif