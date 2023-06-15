/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:08:55 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/15 11:09:43 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_shell *msh)
{
	int	i;

	i = 0;
	if (msh->tokens[1])
	{
		print_error(ERROR_SUPPORT, "env", 1);
		return ;
	}
	while (i < msh->environment.size)
	{
		ft_putstr_fd(msh->environment.key[i], msh->fdout);
		ft_putchar_fd('=', msh->fdout);
		ft_putendl_fd(msh->environment.content[i], msh->fdout);
		i++;
	}
	g_exit = 0;
}

void	echo_builtin(t_shell *msh)
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

int	cd_builtin(t_shell *msh, char *tmp)
{
	update_envinroment_pwds(msh, "OLDPWD");
	if (msh->tokens[1] && msh->tokens[1][0] == '-' && msh->tokens[1][1] == '\0')
	{
		tmp = ft_strdup(msh->oldpwd);
		printf("%s\n", tmp);
	}
	else if (msh->tokens[1])
		tmp = ft_strdup(msh->token.print);
	else
	{
		if (envp_content(msh, "HOME"))
			tmp = ft_strdup(envp_content(msh, "HOME"));
		else
		{
			print_error(ERROR_HOME, "cd", 1);
			return (1);
		}
	}
	update_last_pwd(msh);
	g_exit = chdir(tmp);
	if (g_exit == -1)
		print_error(ERROR_DIR, msh->tokens[1], 1);
	update_envinroment_pwds(msh, "PWD");
	free(tmp);
	return (0);
}

void	export_builtin(t_shell *msh, int i)
{
	char	**tmp;

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
			check_envp(msh, tmp, i);
			free_split(tmp, YES);
		}
		else
		{
			tmp[1] = ft_strdup("");
			check_envp(msh, tmp, i);
			free_export_builtin(tmp);
		}
		tmp = NULL;
	}
	g_exit = 0;
}

void	unset_builtin(t_shell *msh)
{
	int	i;

	i = 1;
	while (msh->tokens[i])
	{
		if (envp_content(msh, msh->tokens[i]))
		{
			remove_envp(msh);
			if (!ft_strncmp(msh->tokens[i], "PATH", 4))
			{
				free_split(msh->paths, YES);
				msh->paths = NULL;
			}
		}
		i++;
	}
	g_exit = 0;
}
