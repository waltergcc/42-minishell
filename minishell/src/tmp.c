/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 01:37:15 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/16 01:37:54 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_only_redirections(char *s, int i)
{
	while (s[++i])
		if (s[i] != '>' && s[i] != '<')
			if (s[i] != ' ' && s[i] != '\t')
				return (NO);
	return (YES);
}

int	is_redirections_valid(t_shell *msh, int i)
{
	while (msh->cmds[++i])
	{
		if (have_only_redirections(msh->cmds[i], -1))
		{
			print_error(NULL, msh->cmds[i], 1);
			return (NO);
		}
	}
	return (YES);
}
