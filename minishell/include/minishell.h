/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:23:36 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/30 17:09:16 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define YES 1
# define NO 0

# define BEGIN 1
# define END 0

# define NOT_NUM 2
# define EXIT_ARG 0
# define BUILTIN_EXIT 1

# define UNLOCK 0
# define NO_START 0
# define COMMON 1
# define SPECIAL 2

# define STOP_RESTORE 1
# define STOP_QUIT 2
# define EXIT 3
# define HEREDOC 4
# define HEREDOC_PAUSE 5

# define D_QUOTE '\"'
# define QUOTE '\''
# define STR_QUOTE "\'"
# define STR_D_QUOTE "\""
# define QUOTE_SET "\'\""
# define CHARSET "?%*+,.-/#:@~ \t"
# define N_HANDLE "&;(){}*\\"
# define SPC " \t"
# define SPC_QUOTES " \t\'\""

# define ERROR_TITLE "minishell"
# define ERROR_FORK "fork error"
# define ERROR_QUOTE "unclosed quotes"
# define ERROR_PIPE "syntax error near unexpected token `|'"
# define ERROR_PROMPT "no support for pipe prompt"
# define ERROR_DIR "No such file or directory"
# define ERROR_CMD "command not found"
# define ERROR_EXP "not a valid identifier"
# define ERROR_HOME "HOME not set"
# define ERROR_PID "pipe error"
# define ERROR_NUM "numeric argument required"
# define ERROR_ARG "too many arguments"
# define ERROR_SUPPORT "Arguments and options aren't supported"
# define ERROR_OPTIONS "options aren't supported"
# define ERROR_REDIR "syntax error near unexpected token `newline'"
# define ERROR_SYNTAX "syntax error near unexpected token"
# define EXPORT_NOTE "too few argumnts"

extern int	g_exit;
typedef struct s_key
{
	char	*key;
	char	*content;
	void	*next;
}			t_key;
typedef struct s_envp
{
	char	**envp;
	char	**key;
	char	**key_tmp;
	t_key	*key_ex;
	char	**content;
	int		size;
	int		size_tmp;
	int		index;
}			t_envp;

typedef struct s_parse
{
	int		id;
	int		pipes;
	int		q;
	int		start;
	int		size;
}			t_parse;

typedef struct s_token
{
	char	quote;
	char	*print;
	char	*end;
	char	*new;
	int		i;
	int		start;
	int		size;
	int		lock;
	int		position;
	int		dollar_remain;
}			t_token;

typedef struct s_shell
{
	t_envp	environment;
	t_envp	tmp_envp;
	t_token	token;
	t_parse	parse;
	char	**paths;
	char	*cmds[50];
	char	**tokens;
	char	*home;
	char	*oldpwd;
	char	*user_input;
	char	*tmp_cmd;
	char	*file_name;
	char	*file_error;
	char	*not_numeric;
	int		id;
	int		fdin;
	int		fdout;
	int		control;
	int		is_first_time;
	int		is_last_redirection;
	int		is_builtin;
	int		is_append;
	int		has_flag_n;
	int		error_flag;
	int		cat_case;
	int		exit_is_numeric;
	int		unsupport;
	int		ctrlc;
}			t_shell;

/*input.c*/
void	get_user_input(t_shell *msh, char *prompt);
int		have_only_redirections(char *s, int i);
int		redirections_are_valid(t_shell *msh, int i);
int		have_only_spaces(char *s, int i);
int		is_valid_input(char *s, int end);

/*environment.c*/
void	set_environment_and_paths(t_shell *msh);
void	create_environment(t_shell *msh, char **envp, char **tmp, int i);
void	get_envinroment_size(t_shell *msh, int i);
char	*get_envinroment_content(t_shell *msh, char *key, int i);
void	key_content_malloc(t_envp *envp, int size);

/*signals.c*/
void	set_signal(int sg, t_shell *msh);
void	reset_prompt(int sg);
void	ctrl_c(int sig);
void	back_slash(int sig);

/*parse.c*/
void	parse_input(t_shell *msh, char *s, int i);
void	start_parse_values(t_shell *msh);
int		split_input_in_cmds(t_shell *msh, char *s, int i);
int		first_cmd_valid(t_shell *msh);
int		have_forbidden(char *s, int n);

/*commands_manager.c*/
void	commands_manager(t_shell *msh, int i);
void	init_control_flags(t_shell *msh, int i);
void	command_handler(t_shell *msh);
void	check_redirections(t_shell *msh);
void	close_control_flags(t_shell *msh);

/*commands_execute.c*/
void	execute_builtin(t_shell *msh);
int		file_descriptor_handler(int in, int out);
void	execute_relative_command(t_shell *msh, int i, char *cmd);
void	execute_command(t_shell *msh, int i, char *cmd);
void	create_child_process(t_shell *msh, int in, int out);

/*commands_utils.c*/
void	check_first_cmd(t_shell *msh);
void	implicit_cat(t_shell *msh, int i);
void	check_if_is_builtin(t_shell *msh, char *cmd);
void	print_error_if_command_fail(t_shell *msh);
int		have_options(t_shell *msh, int i);

/*redirections.c*/
void	redirect_out(t_shell *msh, int i, char *file);
void	redirect_in(t_shell *msh, int i, char **file, char *tmp);
char	**double_redirect_in(t_shell *msh, char **file, int i);
char	*new_command(int i, char **s);

/*heredoc.c*/
void	start_heredoc(char *end, t_shell *msh);
int		has_expand(char *line, int i);
int		search_variable_end(char *s, char *c, int i);
char	*expand_line(char *line, t_shell *msh, t_token *exp, char *tail);
void	get_expand_variable(char *line, t_shell *msh, t_token *exp);

/*tokens.c*/
void	get_tokens(t_shell *msh);
void	get_dollar_sign(t_shell *msh, t_token *token);
void	get_home_sign(t_shell *msh, t_token *token);
void	close_current_tokens(t_shell *msh, t_token *token);
void	check_quotes(t_shell *msh, t_token *token);

/*tokens_utils.c*/
t_token	*create_token(t_shell *msh);
int		search_position(char *s, char *c, t_token *token, int i);
int		quotes_handler(t_shell *msh, char c, char *tmp, int j);
void	fix_quotes_to_print(t_shell *msh, char *s, int i, int j);
int		verify_flag_n(t_shell *msh, char *s, int i);

/*tokens_split.c*/
char	**split_tokens(char *s, int i, int j, char	*charset);

/*builtins_basic.c*/
void	execute_echo(t_shell *msh);
int		execute_cd(t_shell *msh, char *tmp);
void	execute_exit(t_shell *msh, int i);
void	execute_env(t_shell *msh, int i);
void	execute_pwd(t_shell *msh, char *pwd);

/*builtins_complex.c*/
void	execute_export(t_shell *msh, int i, char **tmp);
void	execute_unset(t_shell *msh, int i);
void	check_and_set_envinroment_var(t_shell *msh, char **new, int i);
void	add_environment(t_shell *msh, char *new_key, char *new_content, int i);
void	remove_environment_var(t_shell *msh, int i, int j);

/*builtins_utils.c*/
void	update_envinroment_pwds(t_shell *msh, char *to_update, char *pwd);
void	update_last_pwd(t_shell *msh, char *pwd);
int		is_valid_exit(t_shell *msh, int i, int tokens);
char	**split_export_token(t_shell *msh, int *i, char **tmp);
void	export_without_args(t_shell *msh);

/*builtins_export_lists.c*/
t_key	*stack_new(char **key, char **content, int index);
t_key	*fill_stack(int size, char **key, char **key_tmp, char **content);
void	free_stack(t_key **stack);
void	stack_add_bottom(t_key **header, t_key *new);
void	ordenate_keys(t_key *header);

/*builtins_export_tmp.c*/
void	check_tmp_key(t_shell *msh, char *token, int i, int already_exist);
char	**ft_realloc_double(char **str, int size);
int		if_exist_key_tmp(t_shell *msh, char *token, int i);
void	remove_tmp_var(t_shell *msh, char *token, int i, int j);
void	export_output(t_shell *msh, t_key *tmp);

/*utils.c*/
void	print_error(char *msg, char *key, int exit_code);
void	free_split(char **str, int free_str);
void	clean_exit(t_shell *msh, int mode);
int		get_paths(t_shell *msh, char *tmp, int i);
void	free_tokens(t_token *token);

/*utils_extra.c*/
void	clean_handler(t_shell *msh);
void	child_signal_handler(int sig);
void	child_signal_handler2(int sig);
char	**split_environment_vars(t_shell *msh, int *i, char **tmp);

#endif