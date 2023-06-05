/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:15:03 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/05 21:37:39 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg, char *key, int exit_code)
{
	if (key)
		printf("%s: %s: %s\n", ERROR_TITLE, key, msg);
	else
		printf("%s: %s\n", ERROR_TITLE, msg);
	g_exit = exit_code;
}

int	count_redirections(t_shell *msh, char *s, int i)
{
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
	{
		if (s[i] == '|' && !msh->parse.q)
			msh->parse.pipes++;
		if (!msh->parse.q && i > 1 && msh->parse.size > 0)
		{
			msh->commands[msh->parse.cmd++] = ft_substr(s,
					msh->parse.start, msh->parse.size);
			msh->parse.start = i;
			msh->parse.size = 0;
			if (s[i] == '>')
				msh->last_redirection = 1;
			else
				msh->last_redirection = 0;
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
	msh->parse.cmd = 0;
	msh->parse.start = 0;
	msh->parse.size = 0;
	msh->parse.q = 0;
	msh->parse.pipes = 0;
	msh->last_redirection = 0;
}

void	parse_input(t_shell *msh, char *s, int i)
{
	start_parse_values(msh);
	s = ft_strtrim(s, " ");
	while (++i < (int)ft_strlen(s))
	{
		if (!msh->parse.q && (s[i] == D_QUOTE || s[i] == QUOTE))
			msh->parse.q = s[i];
		else
		{
			if (msh->parse.q == s[i])
				msh->parse.q = 0;
			else
				i = count_redirections(msh, s, i);
		}
		msh->parse.size++;
	}
	if (ft_strlen(s) > 0)
		msh->commands[msh->parse.cmd++] = ft_substr(s, msh->parse.start, i);
	free (s);
	msh->commands[msh->parse.cmd] = NULL;
}
