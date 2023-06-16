/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:32:00 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 11:56:28 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (i);
}

void	start_parse_values(t_shell *msh)
{
	msh->parse.id = 0;
	msh->parse.start = 0;
	msh->parse.size = 0;
	msh->parse.pipes = 0;
	msh->parse.q = UNLOCK;
	msh->is_last_redirection = NO;
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
