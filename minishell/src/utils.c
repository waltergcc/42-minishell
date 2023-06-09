/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:32:00 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/09 10:40:41 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *token)
{
	if (token->end)
	{
		free(token->end);
		token->end = NULL;
	}
	if (token->new)
	{
		free(token->new);
		token->new = NULL;
	}
	if (token->print)
	{
		free(token->print);
		token->print = NULL;
	}
	free(token);
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
		if (s[i] == '|' && !msh->parse.q)
			msh->parse.pipes++;
		if (!msh->parse.q && i > 1 && msh->parse.size > 0)
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
	msh->parse.q = 0;
	msh->parse.pipes = 0;
	msh->is_last_redirection = NO;
}

void	is_builtin(t_shell *msh, char *cmd)
{
	int	size;

	size = ft_strlen(cmd);
	if ((!ft_strncmp(cmd, "echo", 4) && size == 4)
		|| (!ft_strncmp(cmd, "cd", 2) && size == 2)
		|| (!ft_strncmp(cmd, "pwd", 3) && size == 3)
		|| (!ft_strncmp(cmd, "export", 6) && size == 6)
		|| (!ft_strncmp(cmd, "unset", 5) && size == 5)
		|| (!ft_strncmp(cmd, "env", 3) && size == 3)
		|| (!ft_strncmp(cmd, "exit", 4) && size == 4))
		msh->is_builtin = YES;
	else
		msh->is_builtin = NO;
}
