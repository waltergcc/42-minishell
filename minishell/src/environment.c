/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:57:05 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/29 22:34:11 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	key_content_malloc(t_envp *envp, int size)
{
	envp->key = malloc(sizeof(char *) * (size + 1));
	if (!envp->key)
		exit(EXIT_FAILURE);
	envp->content = malloc(sizeof(char *) * (size + 1));
	if (!envp->content)
		exit(EXIT_FAILURE);
}

char	*get_envinroment_content(t_shell *msh, char *key, int i)
{
	while (msh->environment.key[++i])
	{
		if (!ft_strcmp(msh->environment.key[i], key))
		{
			msh->environment.index = i;
			return (msh->environment.content[i]);
		}
	}
	return (NULL);
}

void	get_envinroment_size(t_shell *msh, int i)
{
	while (msh->environment.envp[i])
		i++;
	msh->environment.size = i;
}

void	create_environment(t_shell *msh, char **envp, char **tmp, int i)
{
	msh->environment.envp = envp;
	get_envinroment_size(msh, 0);
	key_content_malloc(&msh->environment, msh->environment.size);
	while (msh->environment.envp[++i])
	{
		tmp = split_environment_vars(msh, &i, tmp);
		msh->environment.key[i] = ft_strdup(tmp[0]);
		msh->environment.content[i] = ft_strdup(tmp[1]);
		free_split(tmp, YES);
		tmp = NULL;
	}
	msh->environment.key[i] = NULL;
	msh->environment.content[i] = NULL;
	msh->environment.key_tmp = malloc(sizeof(char *) * (1));
	msh->environment.key_tmp[0] = NULL;
	msh->environment.size_tmp = 0;
}

void	set_environment_and_paths(t_shell *msh)
{
	g_exit = 0;
	msh->is_last_redirection = NO;
	msh->error_flag = NO;
	msh->has_flag_n = NO;
	msh->tokens = (char **) NULL;
	create_environment(msh, __environ, NULL, -1);
	get_paths(msh, NULL, -1);
	msh->home = ft_strdup(get_envinroment_content(msh, "HOME", -1));
	msh->oldpwd = ft_strdup(get_envinroment_content(msh, "OLDPWD", -1));
}
