/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvieira <anvieira@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:40:33 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/20 20:38:03 by anvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_spaces(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != ' ' && s[i] != '\t')
			return (NO);
	return (YES);
}
