/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:55:23 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/19 11:18:45 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_export_builtin(char **tmp)
{
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
}

void	update_envinroment_pwds(t_shell *msh, char *to_update, char *pwd)
{
	pwd = getcwd(pwd, 2000);
	if (get_envinroment_content(msh, to_update, -1))
	{
		free(msh->environment.content[msh->environment.index]);
		msh->environment.content[msh->environment.index] = ft_strdup(pwd);
	}
	else
		add_environment(msh, to_update, pwd, 0);
	free(pwd);
}

void	update_last_pwd(t_shell *msh, char *pwd)
{
	free(msh->oldpwd);
	pwd = getcwd(pwd, 2000);
	msh->oldpwd = ft_strdup(pwd);
	free(pwd);
}

int	is_valid_exit(t_shell *msh, int i, int tokens)
{
	msh->exit_is_numeric = NO;
	if (tokens > 2)
	{
		print_error(ERROR_ARG, "exit", 1);
		return (NO);
	}
	while (msh->tokens[1][++i])
	{
		if (i == 0 && (msh->tokens[1][0] == '-' || msh->tokens[1][0] == '+'))
			i++;
		if (!ft_isdigit(msh->tokens[1][i]))
		{
			g_exit = 2;
			msh->not_numeric = ft_strdup(msh->tokens[1]);
			return (NOT_NUM);
		}
	}
	g_exit = ft_atoi(msh->tokens[1]);
	msh->exit_is_numeric = YES;
	return (YES);
}
