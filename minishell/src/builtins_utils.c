/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:40:14 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/10 18:33:02 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_exit(t_shell *msh, int i)
{
	while (msh->tokens[1][++i])
	{
		if (!ft_isdigit(msh->tokens[1][i]))
		{
			print_error("Illegal number", "exit", 1);
			return (0);
		}
	}
	g_exit = ft_atoi(msh->tokens[1]);
	return (1);
}

void	exit_builtin(t_shell *msh)
{
	int	i;

	i = 0;
	while (msh->tokens[i])
		i++;
	if (i > 1 && !is_valid_exit(msh, -1))
		return ;
	free_split(msh->cmds, NO);
	free_split(msh->tokens, YES);
	free(msh->token.print);
	printf("exit\n");
	if (i == 1)
		clean_exit(msh, BUILTIN_EXIT);
	else
		clean_exit(msh, EXIT_ARG);
}

void	pwd_builtin(t_shell *msh)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 2000);
	ft_putendl_fd(pwd, msh->fdout);
	if (!pwd)
		g_exit = 1;
	else
		g_exit = 0;
	free(pwd);
}

void	remove_envp(t_shell *msh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	msh->environment.size--;
	alloc_key_content(&msh->tmp_envp, msh->environment.size);
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

void	add_envp(t_shell *msh, char *new_key, char *new_content)
{
	int		i;

	i = 0;
	msh->environment.size++;
	alloc_key_content(&msh->tmp_envp, msh->environment.size);
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
	if (envp_content(msh, new[0]))
	{
		free(msh->environment.content[msh->environment.index]);
		msh->environment.content[msh->environment.index] = ft_strdup(new[1]);
	}
	else
		add_envp(msh, new[0], new[1]);
	if (!ft_strncmp(msh->tokens[i], "PATH", 4))
	{
		if (msh->paths)
			free_split(msh->paths, YES);
		get_paths(msh);
	}
}
