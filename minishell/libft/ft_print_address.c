/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:46:20 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/04/27 00:24:55 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_address_len(unsigned long long n)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n /= 16;
	}
	return (count);
}

void	ft_put_address(unsigned long long n)
{
	if (n >= 16)
	{
		ft_put_address(n / 16);
		ft_put_address(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar_fd((n + '0'), 1);
		else
			ft_putchar_fd((n - 10 + 'a'), 1);
	}
}

int	ft_print_address(unsigned long long n, t_flags *flags)
{
	int	len;

	len = 0;
	if (n == 0)
		len += ft_print_str("(nil)", flags);
	else
	{
		if (flags->only_number)
			len += ft_print_justify_before(flags, ft_address_len(n) + 2);
		ft_putstr("0x");
		len += 2;
		ft_put_address(n);
		len += ft_address_len(n);
		if (flags->minus)
			len += ft_print_justify_after(flags, ft_address_len(n) + 2);
	}
	return (len);
}
