/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:55:23 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 02:55:40 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envinroment_pwds(t_shell *msh, char *to_update)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 2000);
	if (get_envinroment_content(msh, to_update, -1))
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
	return (YES);
}

int	is_valid_input(char *s, int end)
{
	s = ft_strtrim(s, " ");
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
