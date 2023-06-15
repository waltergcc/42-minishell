/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:55:23 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 00:45:38 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_only_spaces(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
	}
	return (1);
}

void	update_envinroment_pwds(t_shell *msh, char *to_update)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 2000);
	if (envp_content(msh, to_update))
	{
		free(msh->environment.content[msh->environment.index]);
		msh->environment.content[msh->environment.index] = ft_strdup(pwd);
	}
	else
		add_envp(msh, to_update, pwd);
	free(pwd);
}

void	update_last_pwd(t_shell *msh)
{
	char	*pwd;

	free(msh->oldpwd);
	pwd = NULL;
	pwd = getcwd(pwd, 2000);
	msh->oldpwd = ft_strdup(pwd);
	free(pwd);
}

int	is_first_char_valid(t_shell *msh)
{
	if ((msh->cmds[0][0] == '|') && msh->parse.id > 0)
	{
		print_error(ERROR_PIPE, NULL, 1);
		return (NO);
	}
	if (msh->cmds[0][0] == '>' || msh->cmds[0][0] == '<')
	{
		if (have_only_redirections(msh->cmds[0], -1) || (msh->cmds[0][0] == '<'
			&& msh->cmds[0][1] != '<' && !msh->cmds[1]))
		{
			print_error(ERROR_REDIR, NULL, 1);
			return (NO);
		}
	}
	return (YES);
}

int	is_end_char_valid(char *s, int i)
{
	s = ft_strtrim(s, " ");
	i = ft_strlen(s) - 1;
	if (s[i] == '|' || s[i] == '>' || s[i] == '<')
	{
		if (s[i] == '|')
			print_error(ERROR_PROMPT, NULL, 2);
		else
			print_error(ERROR_REDIR, NULL, 2);
		free(s);
		return (NO);
	}
	free(s);
	return (YES);
}
