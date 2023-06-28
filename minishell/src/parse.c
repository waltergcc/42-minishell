/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:32:00 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/28 04:33:19 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_forbidden(char *s, int n)
{
	int	i;

	i = -1;
	while (s[++i] && i < n)
		if (ft_isset(s[i], CHARSET) || ft_isset(s[i], QUOTE_SET))
			return (YES);
	if (s[0] <= '9' && s[0] >= '0')
		return (YES);
	return (NO);
}

int	first_cmd_valid(t_shell *msh)
{
	if (msh->cmds[0][0] == '>' || msh->cmds[0][0] == '<')
	{
		if (have_only_redirections(msh->cmds[0], -1)
			|| (msh->cmds[0][0] == '<' && msh->cmds[0][1] != '<'
			&& !msh->cmds[1]))
		{
			print_error(ERROR_REDIR, NULL, 1);
			return (NO);
		}
	}
	if (msh->parse.q != UNLOCK)
	{
		print_error(ERROR_QUOTE, NULL, 2);
		return (NO);
	}
	if (msh->unsupport)
	{
		printf("minishell: no support for operator `%c'\n", msh->unsupport);
		g_exit = 2;
		return (NO);
	}
	return (YES);
}

int	split_input_in_cmds(t_shell *msh, char *s, int i)
{
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
	{
		if (s[i] == '|' && msh->parse.q == UNLOCK)
			msh->parse.pipes++;
		if (msh->parse.q == UNLOCK && msh->parse.size > 0
			&& ((s[i] == '|' && i > 0) || (s[i] != '|' && i > 1)))
		{
			msh->cmds[msh->parse.id++] = ft_substr(s,
					msh->parse.start, msh->parse.size);
			msh->parse.start = i;
			msh->parse.size = 0;
			if (s[i] == '>')
				msh->is_last_redirection = YES;
			else
				msh->is_last_redirection = NO;
			if (s[i] == s[i + 1])
			{
				i++;
				msh->parse.size = 1;
			}
		}
	}
	else if (ft_isset(s[i], N_HANDLE) && !msh->parse.q && !msh->unsupport)
		msh->unsupport = s[i];
	return (i);
}

void	start_parse_values(t_shell *msh)
{
	msh->parse.id = 0;
	msh->parse.start = 0;
	msh->parse.size = 0;
	msh->parse.pipes = 0;
	msh->parse.q = UNLOCK;
	msh->unsupport = NO;
	msh->is_last_redirection = NO;
}

void	parse_input(t_shell *msh, char *s, int i)
{
	start_parse_values(msh);
	s = ft_strtrim(s, SPC);
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
