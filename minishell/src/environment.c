/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:57:05 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/05 02:53:34 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_key_content(t_envp *envp, int size)
{
	envp->key = malloc(sizeof(char *) * (size + 1));
	if (!envp->key)
		exit(EXIT_FAILURE);
	envp->content = malloc(sizeof(char *) * (size + 1));
	if (!envp->content)
		exit(EXIT_FAILURE);
}

char	*envp_content(t_shell *msh, char *key)
{
	int	i;

	i = -1;
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

int	get_paths(t_shell *msh)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(envp_content(msh, "PATH"));
	if (!tmp)
		return (0);
	msh->paths = ft_split(tmp, ':');
	i = -1;
	while (msh->paths && msh->paths[++i])
		msh->paths[i] = ft_strjoin(msh->paths[i], "/");
	free(tmp);
	return (1);
}

void	get_envp_size(t_shell *msh)
{
	int	i;

	i = 0;
	while (msh->environment.envp[i])
		i++;
	msh->environment.size = i;
}

void	create_msh_environment(t_shell *msh, char **system_envp)
{
	int		i;
	char	**tmp;

	msh->environment.envp = system_envp;
	get_envp_size(msh);
	alloc_key_content(&msh->environment, msh->environment.size);
	i = -1;
	while (msh->environment.envp[++i])
	{
		tmp = ft_split(msh->environment.envp[i], '=');
		msh->environment.key[i] = ft_strdup(tmp[0]);
		if (tmp[1])
			msh->environment.content[i] = ft_strdup(tmp[1]);
		else
			msh->environment.content[i] = ft_strdup("");
		free_split(tmp, YES);
		tmp = NULL;
	}
	msh->environment.key[i] = NULL;
	msh->environment.content[i] = NULL;
}
