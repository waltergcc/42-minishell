/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:08:55 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 10:38:50 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(t_shell *msh, int i)
{
	if (msh->tokens[1])
	{
		print_error(ERROR_SUPPORT, "env", 1);
		return ;
	}
	while (++i < msh->environment.size)
	{
		ft_putstr_fd(msh->environment.key[i], msh->fdout);
		ft_putchar_fd('=', msh->fdout);
		ft_putendl_fd(msh->environment.content[i], msh->fdout);
	}
	g_exit = 0;
}

void	execute_echo(t_shell *msh)
{
	if (msh->tokens[1])
	{
		ft_putstr_fd(msh->token.print, msh->fdout);
		g_exit = 0;
		if (!msh->has_flag_n)
			ft_putstr_fd("\n", msh->fdout);
	}
	else
		ft_putstr_fd("\n", msh->fdout);
}

int	execute_cd(t_shell *msh, char *tmp)
{
	update_envinroment_pwds(msh, "OLDPWD", NULL);
	if (msh->tokens[1] && msh->tokens[1][0] == '-' && msh->tokens[1][1] == '\0')
	{
		tmp = ft_strdup(msh->oldpwd);
		printf("%s\n", tmp);
	}
	else if (msh->tokens[1])
		tmp = ft_strdup(msh->token.print);
	else
	{
		if (get_envinroment_content(msh, "HOME", -1))
			tmp = ft_strdup(get_envinroment_content(msh, "HOME", -1));
		else
		{
			print_error(ERROR_HOME, "cd", 1);
			return (1);
		}
	}
	update_last_pwd(msh, NULL);
	g_exit = chdir(tmp);
	if (g_exit == -1)
		print_error(ERROR_DIR, msh->tokens[1], 1);
	update_envinroment_pwds(msh, "PWD", NULL);
	free(tmp);
	return (0);
}

void	execute_export(t_shell *msh, int i, char **tmp)
{
	while (msh->tokens[++i])
	{
		if (!ft_strchr(msh->tokens[i], '='))
			continue ;
		if (ft_strchr(msh->tokens[i], D_QUOTE)
			|| ft_strchr(msh->tokens[i], QUOTE))
			tmp = ft_split(msh->token.print, '=');
		else
			tmp = ft_split(msh->tokens[i], '=');
		if (tmp[1])
		{
			check_and_set_envinroment_var(msh, tmp, i);
			free_split(tmp, YES);
		}
		else
		{
			tmp[1] = ft_strdup("");
			check_and_set_envinroment_var(msh, tmp, i);
			free_export_builtin(tmp);
		}
		tmp = NULL;
	}
	g_exit = 0;
}

void	execute_unset(t_shell *msh, int i)
{
	while (msh->tokens[++i])
	{
		if (get_envinroment_content(msh, msh->tokens[i], -1))
		{
			remove_environment_var(msh, 0, 0);
			if (!ft_strncmp(msh->tokens[i], "PATH", 4))
			{
				free_split(msh->paths, YES);
				msh->paths = NULL;
			}
		}
	}
	g_exit = 0;
}
