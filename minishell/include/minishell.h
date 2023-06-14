/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:23:36 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/14 09:07:42 by wcorrea-         ###   ########.fr       */
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

# define EXIT_ARG 0
# define BUILTIN_EXIT 1

# define UNLOCK 0
# define NO_START 0
# define COMMON 1
# define SPECIAL 2
# define INVALID 3

# define STOP_RESTORE 1
# define STOP_QUIT 2
# define EXIT 3

# define D_QUOTE '\"'
# define QUOTE '\''
# define STR_QUOTE "\'"
# define STR_D_QUOTE "\""

# define ERROR_TITLE "minishell"
# define ERROR_FORK "fork error"
# define ERROR_PIPE "syntax error near unexpected token `|'"
# define ERROR_DIR "No such file or directory"
# define ERROR_CMD "command not found"
# define ERROR_HOME "HOME not set"
# define ERROR_PID "pipe error"
# define ERROR_NUM "numeric argument required"
# define ERROR_ARG "too many arguments"
# define ERROR_REDIR "syntax error near unexpected token `newline'"

extern int	g_exit;

typedef struct s_envp
{
	char	**envp;
	char	**key;
	char	**content;
	int		size;
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
	char	*user_input;
	char	*part;
	char	*file_name;
	char	*file_error;
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
}			t_shell;

/*main.c*/
void	run_builtin(t_shell *msh);
void	parse_input(t_shell *msh, char *s, int i);
void	get_input(t_shell *msh);
void	set_environment_and_paths(t_shell *msh);

/*environment.c*/
void	create_msh_environment(t_shell *msh, char **system_envp);
void	get_envp_size(t_shell *msh);
int		get_paths(t_shell *msh);
char	*envp_content(t_shell *msh, char *key);
void	alloc_key_content(t_envp *envp, int size);

/*signals.c*/
void	set_signal(int sg, t_shell *msh);
void	reset_prompt(int sg);
void	ctrl_c(int sig);
void	back_slash(int sig);
void	check_first_cmd(t_shell *msh);

/*utils.c*/
void	start_parse_values(t_shell *msh);
int		count_redirections(t_shell *msh, char *s, int i);
void	print_error(char *msg, char *key, int exit_code);
void	free_export_builtin(char **tmp);
void	implicit_cat(t_shell *msh, int i);

/*commands.c*/
void	commands_manager(t_shell *msh, int i);
void	init_control_flags(t_shell *msh, int i);
void	run_command(t_shell *msh);
void	check_redirections(t_shell *msh);
void	close_control_flags(t_shell *msh);

/*commands_utils.c*/
int		fd_handler(int in, int out);
void	handle_spaces_and_execve(t_shell *msh, int i, char *cmd);
void	execve_error(t_shell *msh);
void	execve_pipe(t_shell *msh, int i, char *cmd);
void	exec_process(t_shell *msh, int in, int out);

/*redirections.c*/
void	redirect_out(t_shell *msh, int i);
void	redirect_in(t_shell *msh, int i);
char	**double_redirect_in(t_shell *msh, char **file, int i);
void	start_heredoc(char *end);
char	*new_command(int i, char **s);

/*tokens.c*/
void	get_tokens(t_shell *msh);
void	get_dollar_sign(t_shell *msh, t_token *token);
void	get_home_sign(t_shell *msh, t_token *token);
void	close_current_tokens(t_shell *msh, t_token *token);
void	check_quotes(t_shell *msh, t_token *token);

/*tokens_utils.c*/
int		search_position(char *s, char c, t_token *token);
t_token	*create_token(t_shell *msh);
int		quotes_handler(t_shell *msh, char c, char *tmp, int j);
void	fix_quotes_to_print(t_shell *msh, char *s, int i, int j);
void	fix_cut_with_space_char(t_shell *msh);

/*builtins.c*/
void	echo_builtin(t_shell *msh);
int		cd_builtin(t_shell *msh);
void	env_builtin(t_shell *msh);
void	export_builtin(t_shell *msh, int i);
void	unset_builtin(t_shell *msh);

/*builtins_utils.c*/
void	is_builtin(t_shell *msh, char *cmd);
void	check_envp(t_shell *msh, char **new, int i);
void	add_envp(t_shell *msh, char *new_key, char *new_content);
void	remove_envp(t_shell *msh);
void	pwd_builtin(t_shell *msh);

/*clean_exit.c*/
void	free_tokens(t_token *token);
void	free_split(char **str, int free_str);
int		is_valid_exit(t_shell *msh, int i, int tokens);
void	clean_exit(t_shell *msh, int mode);
void	exit_builtin(t_shell *msh, int i);

#endif