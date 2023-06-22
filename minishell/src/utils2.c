/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:32:04 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/22 05:34:30 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_charset(char c, char *set, int i)
{
	while (set[++i])
		if (set[i] == c)
			return (YES);
	return (NO);
}

int	have_forbidden(char *s, int n)
{
	int	i;

	i = -1;
	while (s[++i] && i < n)
		if (is_charset(s[i], CHARSET, -1))
			return (YES);
	return (NO);
}
