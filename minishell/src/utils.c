/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:32:00 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/12 03:03:31 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_export_builtin(char **tmp)
{
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
}

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
		if (s[i] == '|' && msh->parse.q == UNLOCK)
			msh->parse.pipes++;
		if (msh->parse.q == UNLOCK && i > 1 && msh->parse.size > 0)
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
