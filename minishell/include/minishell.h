/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:23:36 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/04 10:53:17 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NO 0
# define YES 1


# define STOP 1
# define EXIT 3

# define D_QUOTE '\"'
# define QUOTE '\''

# define ERROR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERROR_DIR "No such file or directory\n"

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
typedef struct s_shell
{
	int		last_redirection;
	t_envp	environment;
	t_envp	tmp;
	char	**paths;
	char	*home_path;
	int		fdin;
	int		fdout;
	char	*user_input;
	t_parse	parse;
	char	*commands[50];
	int		cmd_id;
	char	*cmd;
	char	*file_name;
	char	*file_error;
	int		is_append;
	char	**tokens;
}			t_shell;

/*tests.c*/
void	print_new_envp(t_shell *msh);
void	print_paths(t_shell *msh);
void	print_commands(t_shell *msh);

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

#endif