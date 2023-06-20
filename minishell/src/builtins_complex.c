/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_complex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 00:40:14 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/20 16:03:08 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_and_set_envinroment_var(t_shell *msh, char **new, int i)
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
	free_split(new, YES);
	new = NULL;
}

void	execute_export(t_shell *msh, int i, char **tmp)
{
	int	current_position;

	while (msh->tokens[++i])
	{
		while (msh->tokens[i] && msh->tokens[i][0] == '=')
		{
			printf("minishell: export: `%s': %s\n", msh->tokens[i], ERROR_EXP);
			g_exit = 1;
			i++;
		}
		if (msh->tokens[i] == NULL)
			break ;
		if (!ft_strchr(msh->tokens[i], '='))
			continue ;
		current_position = i;
		if (ft_strchr(msh->tokens[i], D_QUOTE))
			tmp = split_export_token(msh, &i, tmp, D_QUOTE);
		else if (ft_strchr(msh->tokens[i], QUOTE))
			tmp = split_export_token(msh, &i, tmp, QUOTE);
		else
			tmp = split_export_token(msh, &i, tmp, UNLOCK);
		check_and_set_envinroment_var(msh, tmp, current_position);
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
