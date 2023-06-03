/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:23:36 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/03 17:39:06 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define STOP 1

extern int	g_exit;

typedef struct s_envp
{
	char	**envp;
	int		size;
	char	**key;
	char	**content;
	int		index;
}			t_envp;
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
	char	**tokens;
}			t_shell;

/*tests.c*/
void	print_new_envp(t_shell *msh);
void	print_paths(t_shell *msh);

/*clean.c*/
void	free_split(char **str);

/*environment.c*/
void	create_msh_environment(t_shell *msh, char **system_envp);
void	get_envp_size(t_shell *msh);
void	key_content_alloc(t_shell *msh);
int		get_paths(t_shell *msh);
char	*envp_content(t_shell *msh, char *key);

/*signals.c*/
void	set_signal(int sg);
void	reset_prompt(int sg);

#endif