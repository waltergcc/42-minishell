/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:37:15 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/22 17:23:13 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_only_redirections(char *s, int i)
{
	while (s[++i])
		if (s[i] != '>' && s[i] != '<')
			if (s[i] != ' ' && s[i] != '\t')
				return (NO);
	return (YES);
}

int	have_only_spaces(char *s, int i)
{
	while (s[++i])
		if (s[i] != ' ' && s[i] != '\t')
			return (NO);
	return (YES);
}

int	redirections_are_valid(t_shell *msh, int i)
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

int	is_valid_input(char *s, int end)
{
	s = ft_strtrim(s, SPC);
	if (!s[0] || s[0] == '|')
	{
		if (s[0] == '|')
			print_error(ERROR_PIPE, NULL, 1);
		free(s);
		return (NO);
	}
	end = ft_strlen(s) - 1;
	if (s[end] == '|' || s[end] == '>' || s[end] == '<')
	{
		if (s[end] == '|')
			print_error(ERROR_PROMPT, NULL, 2);
		else if (s[end] == '>' || s[end] == '<')
			print_error(ERROR_REDIR, NULL, 2);
		free(s);
		return (NO);
	}
	free(s);
	return (YES);
}

void	get_user_input(t_shell *msh, char *prompt)
{
	prompt = getcwd(prompt, 2000);
	prompt = ft_strjoin(prompt, ":$ ");
	set_signal(STOP_RESTORE, NULL);
	msh->user_input = readline(prompt);
	if (msh->user_input && !have_only_spaces(msh->user_input, -1))
		add_history(msh->user_input);
	free(prompt);
}
