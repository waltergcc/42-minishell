/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:58:49 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/03 12:23:28 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_new_envp(t_shell *msh)
{
	int	i;

	i = -1;
	while (msh->environment.key[++i])
	{
		printf("key: %s\n", msh->environment.key[i]);
		printf("content: %s\n\n", msh->environment.content[i]);
	}
}

void	print_paths(t_shell *msh)
{
	int	i;

	i = -1;
	while (msh->paths[++i])
		printf("path: %s\n", msh->paths[i]);
}
