/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:25:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 09:55:18 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	execute_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->tokens[0], "exit", 4))
		execute_exit(msh, 0);
	if (!ft_strncmp(msh->tokens[0], "echo", 4))
		execute_echo(msh);
	if (!ft_strncmp(msh->tokens[0], "pwd", 3))
		execute_pwd(msh, NULL);
	if (!ft_strncmp(msh->tokens[0], "export", 6))
		execute_export(msh, 0);
	if (!ft_strncmp(msh->tokens[0], "unset", 5))
		execute_unset(msh);
	if (!ft_strncmp(msh->tokens[0], "env", 3))
		execute_env(msh, -1);
	if (!ft_strncmp(msh->tokens[0], "cd", 2))
	{
		if (msh->tokens[1] && msh->tokens[2])
			print_error(ERROR_ARG, msh->tokens[0], 1);
		else
			execute_cd(msh, NULL);
	}
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
				i = split_input_in_cmds(msh, s, i);
		}
		msh->parse.size++;
	}
	if (ft_strlen(s) > 0)
		msh->cmds[msh->parse.id++] = ft_substr(s, msh->parse.start, i);
	free (s);
	msh->cmds[msh->parse.id] = NULL;
}

void	get_user_input(t_shell *msh, char *prompt)
{
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
	create_environment(msh, __environ, NULL, -1);
	get_paths(msh, NULL, -1);
	msh->home = ft_strdup(get_envinroment_content(msh, "HOME", -1));
	msh->oldpwd = ft_strdup(get_envinroment_content(msh, "OLDPWD", -1));
}

int	main(void)
{
	t_shell	msh;

	set_environment_and_paths(&msh);
	while (1)
	{
		msh.fdin = STDIN_FILENO;
		msh.fdout = STDOUT_FILENO;
		get_user_input(&msh, NULL);
		if (msh.user_input)
		{
			if (ft_strlen(msh.user_input) && is_valid_input(msh.user_input, 0))
			{
				parse_input(&msh, msh.user_input, -1);
				if (first_cmd_valid(&msh) && redirections_are_valid(&msh, -1))
					commands_manager(&msh, -1);
				free_split(msh.cmds, NO);
			}
			free(msh.user_input);
		}
		else
			set_signal(EXIT, &msh);
	}
}
