/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:23:36 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/04 17:17:06 by wcorrea-         ###   ########.fr       */
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

# define ERROR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERROR_DIR "No such file or directory\n"
# define ERROR_CMD "command not found\n"

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
	// t_envp	tmp;
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
	int		is_builtin;
}			t_shell;

/*tests.c*/
void	print_new_envp(t_shell *msh);
void	print_paths(t_shell *msh);
void	print_commands(t_shell *msh);
void	print_tokens(t_shell *msh);

/*clean.c*/
void	free_split(char **str, int free_str);
void	clean_exit(t_shell *msh);

/*environment.c*/
void	create_msh_environment(t_shell *msh, char **system_envp);
void	get_envp_size(t_shell *msh);
void	key_content_alloc(t_shell *msh);
int		get_paths(t_shell *msh);
char	*envp_content(t_shell *msh, char *key);

/*signals.c*/
void	set_signal(int sg);
void	reset_prompt(int sg);

/*parse.c*/
int		count_redirections(t_shell *msh, char *s, int i);
void	start_parse_values(t_shell *msh);
void	parse_input(t_shell *msh, char *s, int i);

/*cmd_manager.c*/
void	commands_manager(t_shell *msh);
void	run_command(t_shell *msh);
void	check_redirections(t_shell *msh);

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
void	is_builtin(t_shell *msh, char *cmd);
void	run_builtin(t_shell *msh);

/*builtins.c*/
int		fd_handler(int in, int out);
void	handle_spaces_and_execve(t_shell *msh, int i, char *cmd);
void	execve_error(t_shell *msh);
void	execve_pipe(t_shell *msh, int i, char *cmd);
void	exec_process(t_shell *msh);

#endif