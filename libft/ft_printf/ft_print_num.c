/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:06:49 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/31 16:57:51 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(va_list args)
{
	long	num;
	int		temp;
	char	output[11];
	int		i;

	temp = 0;
	num = va_arg(args, int);
	if (num == 0)
		return (ft_print_one('0'));
	else if (num < 0)
	{
		temp += ft_print_one('-');
		num = -num;
	}
	if (temp == -1)
		return (-1);
	i = -1;
	while (num != 0)
	{
		output[++i] = (num % 10) + '0';
		num /= 10;
	}
	temp += ft_reverse_print(i + 1, output);
	return (temp);
}

int	ft_print_one(char c)
{
	int	temp;

	temp = write(1, &c, 1);
	if (temp == -1)
		return (-1);
	return (1);
}

int	ft_putnbr_unsigned(va_list args)
{
	int				temp;
	char			output[11];
	unsigned int	num;
	int				i;

	num = va_arg(args, unsigned int);
	temp = 0;
	if (num == 0)
		return (ft_print_one('0'));
	i = -1;
	while (num != 0)
	{
		output[++i] = (num % 10) + '0';
		num /= 10;
	}
	temp += ft_reverse_print(i + 1, output);
	return (temp);
}
