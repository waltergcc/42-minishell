/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:49:57 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/04/27 00:25:09 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_conversion_char(char c)
{
	if (c == '%' || c == 'c' || c == 's' || c == 'd' || c == 'i'
		|| c == 'x' || c == 'X' || c == 'u' || c == 'p')
		return (1);
	return (0);
}

t_flags	*ft_flags_list(void)
{
	t_flags	*list;

	list = (t_flags *)malloc(sizeof(t_flags));
	if (!list)
		return (NULL);
	list->space = 0;
	list->plus = 0;
	list->hashtag = 0;
	list->minus = 0;
	list->zero = 0;
	list->dot = 0;
	list->numbers = 0;
	list->only_number = 0;
	list->width = 0;
	list->precision = 0;
	return (list);
}

void	ft_formation_flags(const char *str, size_t *i, t_flags *flags)
{
	int	n;

	n = ft_atoi(&str[*i]);
	*i += ft_nbrlen(n, 10) - 1;
	if (flags->dot)
		flags->precision = n;
	else
		flags->width = n;
	flags->numbers = 1;
	if (!flags->space && !flags->plus && !flags->hashtag
		&& !flags->minus && !flags->zero && !flags->dot)
		flags->only_number = 1;
}

t_flags	*ft_check_flags(const char *str, size_t *i)
{
	t_flags	*flags;

	flags = ft_flags_list();
	if (!flags)
		return (NULL);
	while (str[*i] && !is_conversion_char(str[*i]))
	{
		if (str[*i] == ' ')
			flags->space = 1;
		else if (str[*i] == '+')
			flags->plus = 1;
		else if (str[*i] == '#')
			flags->hashtag = 1;
		else if (str[*i] == '-')
			flags->minus = 1;
		else if (str[*i] == '0')
			flags->zero = 1;
		else if (str[*i] == '.')
			flags->dot = 1;
		else if (str[*i] >= '1' && str[*i] <= '9')
			ft_formation_flags(str, i, flags);
		(*i)++;
	}
	return (flags);
}
