/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:31:24 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/31 18:28:51 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(va_list args)
{
	int		i;
	int		temp;
	int		output;
	char	*string;

	string = va_arg(args, char *);
	if (string == NULL)
	{
		temp = write(1, "(null)", 6);
		if (temp == -1)
			return (-1);
		return (temp);
	}
	i = 0;
	output = 0;
	while (string[i] != '\0')
	{
		temp = write(1, &string[i], 1);
		if (temp == -1)
			return (-1);
		output += temp;
		i++;
	}
	return (output);
}

int	ft_putchr(va_list args)
{
	char	c;

	c = va_arg(args, int);
	return (write(1, &c, 1));
}

int	cases(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchr(args));
	else if (c == 's')
		return (ft_putstr(args));
	else if (c == 'p')
		return (ft_print_void_ptr(args));
	else if (c == 'd')
		return (ft_putnbr(args));
	else if (c == 'i')
		return (ft_putnbr(args));
	else if (c == 'u')
		return (ft_putnbr_unsigned(args));
	else if (c == 'x')
		return (ft_dec_to_hex(0, args));
	else if (c == 'X')
		return (ft_dec_to_hex(1, args));
	else if (c == '%')
		return (ft_print_one('%'));
	return (0);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		chr_count;
	int		temp;

	va_start(args, string);
	i = 0;
	chr_count = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
			temp = cases(string[++i], args);
		else
			temp = write(1, &string[i], 1);
		if (temp == -1)
			return (temp);
		chr_count += temp;
		i++;
	}
	return (va_end(args), chr_count);
}

// // // int main(void)
// // // {
// // // 	// int a = 111111;
// // // 	// printf("%n",  a);
// // // 	// printf("abdef");
// // 	char *string = "dali be ludo\n";
// printf("the value of the custom function is: %d",ft_printf("ahahah
// 				%s", string));
// // 	printf("exp:%d",printf("exp: %p\n",string));
// // 	printf("got:%d",ft_printf("got: %p\n",string));
// printf("this is %x", -2147483648 );
// // // }
