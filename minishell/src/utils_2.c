/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:40:33 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/10 18:42:11 by wcorrea-         ###   ########.fr       */
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
