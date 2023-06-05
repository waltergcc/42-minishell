/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:23:36 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/05 21:46:16 by wcorrea-         ###   ########.fr       */
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

extern int	g_exit;

typedef struct s_envp
{
	char	**envp;
	int		size;
	char	**key;
	char	**content;
	int		index;
}			t_envp;

typedef struct s_parse
{
	int		cmd;
	int		start;
	int		size;
	int		q;
	int		pipes;
}			t_parse;

typedef struct s_token
{
	char	*print;
	char	*exec;
	char	quote;
	char	*end;
	char	*new;
	int		i;
	int		size;
	int		start;
	int		position;
}			t_token;

typedef struct s_shell
{
	int		last_redirection;
	char	**tokens;
	t_envp	environment;
	t_envp	tmp_envp;
	char	**paths;
	char	*home_path;
	int		fdin;
	int		fdout;
	char	*user_input;
	t_parse	parse;
	char	*commands[50];
	int		cid;
	char	*cmd;
	char	*file_name;
	char	*file_error;
	int		is_append;
	t_token	token;
	int		has_flag;
	int		error_flag;
	int		is_builtin;
}			t_shell;

/*main.c*/
void	get_input(t_shell *msh);
void	set_environment_and_paths(t_shell *msh);
void	free_split(char **str, int free_str);
void	clean_exit(t_shell *msh);

/*environment.c*/
void	create_msh_environment(t_shell *msh, char **system_envp);
void	get_envp_size(t_shell *msh);
int		get_paths(t_shell *msh);
char	*envp_content(t_shell *msh, char *key);
void	alloc_key_content(t_envp *envp, int size);

/*signals.c*/
void	set_signal(int sg);
void	reset_prompt(int sg);
void	ctrl_c(int sig);
void	back_slash(int sig);

/*parse.c*/
int		count_redirections(t_shell *msh, char *s, int i);
void	start_parse_values(t_shell *msh);
void	parse_input(t_shell *msh, char *s, int i);
void	print_error(char *msg, char *key, int exit_code);

/*commands.c*/
void	commands_manager(t_shell *msh);
void	run_command(t_shell *msh);
void	check_redirections(t_shell *msh);
void	is_builtin(t_shell *msh, char *cmd);
void	run_builtin(t_shell *msh);

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
void	prompt_write_mode_until(char *end);
char	*new_command(int i, char **s);

/*tokens.c*/
void	get_tokens(t_shell *msh);
void	get_dollar_sign(t_shell *msh, t_token *token);
void	get_home_sign(t_shell *msh, t_token *token);
void	close_current_tokens(t_shell *msh, t_token *token);

/*tokens_utils.c*/
void	free_tokens(t_token *token);
int		search_token_position(char *s, char c);
t_token	*create_token(void);
int		quotes_handler(t_shell *msh, char c, char *tmp, int j);
void	fix_quotes_to_print(t_shell *msh, char *s, int i, int j);

/*builtins.c*/
void	echo_builtin(t_shell *msh);
int		cd_builtin(t_shell *msh);
void	env_builtin(t_shell *msh);
void	export_builtin(t_shell *msh);
void	unset_builtin(t_shell *msh);

/*builtins_utils.c*/
void	check_envp(t_shell *msh, char **new, int i);
void	add_envp(t_shell *msh, char *new_key, char *new_content);
void	remove_envp(t_shell *msh);
void	exit_builtin(t_shell *msh);
void	pwd_builtin(t_shell *msh);

#endif