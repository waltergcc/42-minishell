/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:40:14 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 10:30:42 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_is_builtin(t_shell *msh, char *cmd)
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

void	execute_pwd(t_shell *msh, char *pwd)
{
	pwd = getcwd(pwd, 2000);
	ft_putendl_fd(pwd, msh->fdout);
	if (!pwd)
		g_exit = 1;
	else
		g_exit = 0;
	free(pwd);
}

void	remove_environment_var(t_shell *msh, int i, int j)
{
	msh->environment.size--;
	key_content_malloc(&msh->tmp_envp, msh->environment.size);
	while (i < msh->environment.size + 1)
	{
		if (i != msh->environment.index)
		{
			msh->tmp_envp.key[j] = ft_strdup(msh->environment.key[i]);
			msh->tmp_envp.content[j] = ft_strdup(msh->environment.content[i]);
			j++;
		}
		i++;
	}
	msh->tmp_envp.key[j] = NULL;
	msh->tmp_envp.content[j] = NULL;
	free_split(msh->environment.key, YES);
	free_split(msh->environment.content, YES);
	msh->environment.key = msh->tmp_envp.key;
	msh->environment.content = msh->tmp_envp.content;
}

void	add_environment(t_shell *msh, char *new_key, char *new_content, int i)
{
	msh->environment.size++;
	key_content_malloc(&msh->tmp_envp, msh->environment.size);
	while (i < msh->environment.size - 1)
	{
		msh->tmp_envp.key[i] = ft_strdup(msh->environment.key[i]);
		msh->tmp_envp.content[i] = ft_strdup(msh->environment.content[i]);
		i++;
	}
	msh->tmp_envp.key[i] = ft_strdup(new_key);
	msh->tmp_envp.content[i] = ft_strdup(new_content);
	i++;
	msh->tmp_envp.key[i] = NULL;
	msh->tmp_envp.content[i] = NULL;
	free_split(msh->environment.key, YES);
	free_split(msh->environment.content, YES);
	msh->environment.key = msh->tmp_envp.key;
	msh->environment.content = msh->tmp_envp.content;
}

void	check_envp(t_shell *msh, char **new, int i)
{
	if (get_envinroment_content(msh, new[0], -1))
	{
		free(msh->environment.content[msh->environment.index]);
		msh->environment.content[msh->environment.index] = ft_strdup(new[1]);
	}
	else
		add_environment(msh, new[0], new[1], 0);
	if (!ft_strncmp(msh->tokens[i], "PATH", 4))
	{
		if (msh->paths)
			free_split(msh->paths, YES);
		get_paths(msh, NULL, -1);
	}
}
