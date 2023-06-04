/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:25:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/04 00:51:13 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	get_input(t_shell *msh)
{
	char	*prompt;

	prompt = NULL;
	prompt = getcwd(prompt, 2000);
	prompt = ft_strjoin(prompt, "$ ");
	set_signal(STOP);
	msh->user_input = readline(prompt);
	if (msh->user_input && msh->user_input)
		add_history(msh->user_input);
	free(prompt);
}

void	set_environment_and_paths(t_shell *msh)
{
	g_exit = 0;
	msh->last_redirection = 0;
	msh->tokens = NULL;
	create_msh_environment(msh, __environ);
	get_paths(msh);
	msh->home_path = ft_strdup(envp_content(msh, "HOME"));
}

int	main(void)
{
	t_shell	msh;

	set_environment_and_paths(&msh);
	while (1)
	{
		msh.fdin = STDIN_FILENO;
		msh.fdout = STDOUT_FILENO;
		get_input(&msh);
		if (msh.user_input)
		{
			if (ft_strlen(msh.user_input))
			{
				parse_input(&msh, msh.user_input, -1);
				if (msh.parse.cmd > 0 && msh.commands[0][0] != '|')
					commands_manager(&msh);
				if (msh.commands[0] && msh.commands[0][0] == '|')
					ft_putstr_fd(ERROR_PIPE, STDERR_FILENO);
				free_split(msh.commands, NO);
				puts("working til here");
				break ;
			}
			free(msh.user_input);
		}
		else
			set_signal(EXIT);
	}
	return (g_exit);
}
