/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 01:07:48 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/04/27 00:24:50 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_hex(unsigned int n, const char format)
{
	if (n >= 16)
	{
		ft_put_hex(n / 16, format);
		ft_put_hex(n % 16, format);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
		{
			if (format == 'x')
				ft_putchar(n - 10 + 'a');
			else if (format == 'X')
				ft_putchar(n - 10 + 'A');
		}
	}
}

int	ft_print_hex(unsigned int n, const char format, t_flags *flags)
{
	int		len;

	len = 0;
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (flags->hashtag && format == 'x')
		len += ft_print_str("0x", flags);
	else if (flags->hashtag && format == 'X')
		len += ft_print_str("0X", flags);
	else if (flags->zero)
		len += ft_print_zero(n, flags, 1);
	else if (flags->dot)
		len += ft_precision_others(n, flags, 1);
	if (flags->only_number)
		len += ft_print_justify_before(flags, ft_nbrlen(n, 16));
	ft_put_hex(n, format);
	if (flags->minus)
		len += ft_print_justify_after(flags, ft_nbrlen(n, 16));
	return (len + ft_nbrlen(n, 16));
}
