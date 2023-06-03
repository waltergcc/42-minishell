/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_std.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:56:42 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/04/27 00:24:47 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(unsigned int n, unsigned int base)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n /= base;
	}
	return (count);
}

int	ft_print_percent(void)
{
	ft_putchar('%');
	return (1);
}

int	ft_print_chr(int c, t_flags *flags)
{
	int	len;

	len = 0;
	if (flags->only_number)
		len += ft_print_justify_before(flags, 1);
	ft_putchar(c);
	len += 1;
	if (flags->minus)
		len += ft_print_justify_after(flags, 1);
	return (len);
}

int	ft_print_str(char *s, t_flags *flags)
{
	int	len;

	len = 0;
	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	if (flags->dot)
		return (ft_precision_str(flags, s));
	if (flags->only_number)
		len += ft_print_justify_before(flags, ft_strlen(s));
	ft_putstr(s);
	len += ft_strlen(s);
	if (len == 0 && flags->numbers)
		len += ft_print_chr(' ', flags);
	if (flags->minus && flags->numbers)
		len += ft_print_justify_after(flags, len);
	return (len);
}

int	ft_print_nbr(int n, t_flags *flags)
{
	int		len;
	char	*nbr;

	len = 0;
	if (flags->zero)
		len += ft_print_zero_nbr(n, flags);
	else if (flags->dot)
		len += ft_precision_nbr(flags, n);
	else
	{
		if (flags->space && n >= 0)
			len += ft_print_chr(' ', flags);
		else if (flags->plus && n >= 0)
			len += ft_print_chr('+', flags);
		nbr = ft_itoa(n);
		len += ft_print_str(nbr, flags);
		free(nbr);
	}
	return (len);
}
