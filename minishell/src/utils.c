/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:32:00 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/14 22:37:03 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	implicit_cat(t_shell *msh, int i)
{
	char	*tmp[50];

	tmp[0] = ft_strdup("cat");
	while (msh->cmds[++i])
		tmp[i + 1] = ft_strdup(msh->cmds[i]);
	tmp[i + 1] = NULL;
	i = -1;
	free_split(msh->cmds, NO);
	while (tmp[++i])
		msh->cmds[i] = tmp[i];
	msh->cmds[i] = NULL;
}

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
		if (msh->parse.q == UNLOCK && i > 0 && msh->parse.size > 0)
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
