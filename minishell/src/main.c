/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 10:25:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 01:13:25 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	run_builtin(t_shell *msh)
{
	if (!ft_strncmp(msh->tokens[0], "exit", 4))
		exit_builtin(msh, 0);
	if (!ft_strncmp(msh->tokens[0], "echo", 4))
		echo_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "pwd", 3))
		pwd_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "export", 6))
		export_builtin(msh, 0);
	if (!ft_strncmp(msh->tokens[0], "unset", 5))
		unset_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "env", 3))
		env_builtin(msh);
	if (!ft_strncmp(msh->tokens[0], "cd", 2))
	{
		if (msh->tokens[1] && msh->tokens[2])
			print_error(ERROR_ARG, msh->tokens[0], 1);
		else
			cd_builtin(msh, NULL);
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
	create_environment(msh, __environ, NULL, -1);
	get_paths(msh, NULL, -1);
	msh->home = ft_strdup(envp_content(msh, "HOME"));
	msh->oldpwd = ft_strdup(envp_content(msh, "OLDPWD"));
}

int	have_only_redirections(char *s, int i)
{
	while (s[++i])
		if (s[i] != '>' && s[i] != '<')
			if (s[i] != ' ' && s[i] != '\t')
				return (NO);
	return (YES);
}

int	is_redirections_valid(t_shell *msh, int i)
{
	while (msh->cmds[++i])
	{
		if (have_only_redirections(msh->cmds[i], -1))
		{
			print_error(NULL, msh->cmds[i], 1);
			return (NO);
		}
	}
	return (YES);
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
			if (ft_strlen(msh.user_input) && !have_only_spaces(msh.user_input)
				&& is_end_char_valid(msh.user_input, 0))
			{
				parse_input(&msh, msh.user_input, -1);
				if (is_first_char_valid(&msh)
					&& is_redirections_valid(&msh, -1))
					commands_manager(&msh, -1);
				free_split(msh.cmds, NO);
			}
			free(msh.user_input);
		}
		else
			set_signal(EXIT, &msh);
	}
}
