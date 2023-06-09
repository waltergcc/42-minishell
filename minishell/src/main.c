/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:25:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/09 21:32:14 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	clean_exit(t_shell *msh, int mode)
{
	free_split(msh->paths, YES);
	free_split(msh->environment.key, YES);
	free_split(msh->environment.content, YES);
	free(msh->user_input);
	free(msh->home);
	// if (msh->token.print)
	// 	free(msh->token.print);
	// if (msh->tokens)
	// 	free_split(msh->tokens, YES);
	if (mode == BUILTIN_EXIT)
		exit(EXIT_SUCCESS);
	else
		exit(g_exit);
}

void	parse_input(t_shell *msh, char *s, int i)
{
	start_parse_values(msh);
	s = ft_strtrim(s, " ");
	while (++i < (int)ft_strlen(s))
	{
		if (msh->parse.q == UNLOCK && (s[i] == D_QUOTE || s[i] == QUOTE))
			msh->parse.q = s[i];
		else
		{
			if (msh->parse.q == s[i])
				msh->parse.q = UNLOCK;
			else
				i = count_redirections(msh, s, i);
		}
		msh->parse.size++;
	}
	if (ft_strlen(s) > 0)
		msh->cmds[msh->parse.id++] = ft_substr(s, msh->parse.start, i);
	free (s);
	msh->cmds[msh->parse.id] = NULL;
}

void	get_input(t_shell *msh)
{
	char	*prompt;

	prompt = NULL;
	prompt = getcwd(prompt, 2000);
	prompt = ft_strjoin(prompt, ":$ ");
	set_signal(STOP_RESTORE, NULL);
	msh->user_input = readline(prompt);
	if (msh->user_input)
		add_history(msh->user_input);
	free(prompt);
}

void	set_environment_and_paths(t_shell *msh)
{
	g_exit = 0;
	msh->is_last_redirection = NO;
	msh->error_flag = NO;
	msh->has_flag_n = NO;
	msh->tokens = (char **) NULL;
	create_msh_environment(msh, __environ);
	get_paths(msh);
	msh->home = ft_strdup(envp_content(msh, "HOME"));
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
				if (msh.parse.id > 0 && msh.cmds[0][0] != '|')
					commands_manager(&msh, -1);
				if (msh.cmds[0] && msh.cmds[0][0] == '|')
					print_error(ERROR_PIPE, NULL, 1);
				free_split(msh.cmds, NO);
			}
			free(msh.user_input);
		}
		else
			set_signal(EXIT, &msh);
	}
	clean_exit(&msh, PROGRAM_END);
}
