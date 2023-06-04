/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:47:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/06/04 13:11:46 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && is_set(s1[i], set))
		i++;
	if (i == j)
		return (ft_strdup(""));
	j--;
	while (is_set(s1[j], set))
		j--;
	trimmed = ft_substr(s1, i, j - i + 1);
	return (trimmed);
}
