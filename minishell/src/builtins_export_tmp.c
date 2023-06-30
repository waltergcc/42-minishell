/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_tmp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 07:19:37 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/30 17:09:06 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_output(t_shell *msh, t_key *tmp)
{
	ft_putstr_fd("export ", msh->fdout);
	ft_putstr_fd(tmp->key, msh->fdout);
	ft_putchar_fd('=', msh->fdout);
	ft_putchar_fd(D_QUOTE, msh->fdout);
	ft_putstr_fd(tmp->content, msh->fdout);
	ft_putendl_fd(STR_D_QUOTE, msh->fdout);
}

int	if_exist_key_tmp(t_shell *msh, char *token, int i)
{
	while (msh->environment.key_tmp[i])
	{
		if (strcmp(msh->environment.key_tmp[i], token) == 0)
			return (YES);
		i++;
	}
	return (NO);
}

void	remove_tmp_var(t_shell *msh, char *token, int i, int j)
{
	char	**new;

	msh->environment.size_tmp--;
	new = malloc(sizeof(char *) * (msh->environment.size_tmp + 1));
	if (new == NULL)
		return ;
	while (msh->environment.key_tmp[i])
	{
		if (strcmp(msh->environment.key_tmp[i], token) == 0)
			i++;
		if (msh->environment.key_tmp[i] == NULL)
		{
			new[j] = NULL;
			break ;
		}
		new[j] = ft_strdup(msh->environment.key_tmp[i]);
		j++;
		i++;
	}
	new[j] = NULL;
	free_split(msh->environment.key_tmp, YES);
	msh->environment.key_tmp = new;
}

char	**ft_realloc_double(char **str, int size)
{
	char	**new_str;
	int		i;

	i = -1;
	new_str = malloc(sizeof(char *) * (size + 1));
	if (!new_str)
		exit(EXIT_FAILURE);
	while (str[++i])
	{
		new_str[i] = ft_strdup(str[i]);
		free(str[i]);
	}
	free(str);
	return (new_str);
}

void	check_tmp_key(t_shell *msh, char *token, int i, int already_exist)
{
	while (msh->environment.key[++i])
		if (!ft_strcmp(msh->environment.key[i], token))
			already_exist = YES;
	i = -1;
	while (msh->environment.key_tmp[++i])
		if (!ft_strcmp(msh->environment.key_tmp[i], token))
			already_exist = YES;
	if (!already_exist)
	{
		msh->environment.size_tmp++;
		msh->environment.key_tmp = ft_realloc_double(msh->environment.key_tmp,
				msh->environment.size_tmp);
		msh->environment.key_tmp[msh->environment.size_tmp - 1]
			= ft_strdup(token);
		msh->environment.key_tmp[msh->environment.size_tmp] = NULL;
	}
}
