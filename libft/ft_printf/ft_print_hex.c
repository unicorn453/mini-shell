/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:56:20 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/31 16:55:56 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_void_ptr(va_list args)
{
	unsigned long	adr;
	char			output[20];
	char			*hex;
	int				i;
	int				temp;

	hex = "0123456789abcdef";
	adr = (unsigned long)va_arg(args, void *);
	if (adr == 0)
		return (write(1, "0x0", 3));
	i = 0;
	while (adr != 0)
	{
		temp = adr % 16;
		output[i] = hex[temp];
		adr /= 16;
		i++;
	}
	temp = write(1, "0x", 2);
	if (temp == -1)
		return (-1);
	return (ft_reverse_print(i, output) + 2);
}

int	ft_reverse_print(int i, char *output)
{
	int	i_cpy;
	int	temp;

	i_cpy = i;
	while (--i >= 0)
	{
		temp = write(1, &output[i], 1);
		if (temp == -1)
			return (-1);
	}
	return (i_cpy);
}

int	ft_dec_to_hex(int zero_one, va_list args)
{
	char			*hex;
	unsigned int	num;
	char			output[20];
	int				i;
	int				temp;

	num = va_arg(args, unsigned int);
	if (num == 0)
		return (write(1, "0", 1));
	if (zero_one == 0)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	i = 0;
	while (num != 0)
	{
		temp = num % 16;
		output[i] = hex[temp];
		num /= 16;
		i++;
	}
	return (ft_reverse_print(i, output));
}
