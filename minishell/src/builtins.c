/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:08:55 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/14 13:39:27 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_shell *msh)
{
	int	i;

	i = 0;
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

int	cd_builtin(t_shell *msh)
{
	char	*tmp;

	char *pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 2000);
	if (envp_content(msh, "OLDPWD"))
	{
		free(msh->environment.content[msh->environment.index]);
		msh->environment.content[msh->environment.index] = ft_strdup(pwd);
	}
	else
		add_envp(msh, "OLDPWD", pwd);
	free(pwd);
	pwd = NULL;
	printf("msh->oldpwd: %s\n", msh->oldpwd);
	if (msh->tokens[1] && msh->tokens[1][0] == '-' && msh->tokens[1][1] == '\0')
	{
		tmp = ft_strdup(msh->oldpwd);
		printf("%s\n", tmp);
	}
	else if(msh->tokens[1])
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
	free(msh->oldpwd);
	pwd = getcwd(pwd, 2000);
	msh->oldpwd = ft_strdup(pwd);
	free(pwd);
	pwd = NULL;
	g_exit = chdir(tmp);
	if (g_exit == -1)
		print_error(ERROR_DIR, msh->tokens[1], 1);
	pwd = getcwd(pwd, 2000);
	if (envp_content(msh, "PWD"))
	{
		free(msh->environment.content[msh->environment.index]);
		msh->environment.content[msh->environment.index] = ft_strdup(pwd);
	}
	else
		add_envp(msh, "PWD", pwd);
	free(pwd);
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
