/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:03:12 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/13 20:09:50 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	ft_numlen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		len;

	num = n;
	if (num < 0)
		num = -num;
	len = ft_numlen(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

// int	main(void)
// {
// 	char	*string;

// 	string = ft_itoa(-1);
// 	printf("expected: -1 got: %s\n", string);
// 	free(string);
// 	string = ft_itoa(10010);
// 	printf("expected: 10010 got: %s\n", string);
// 	free(string);
// 	return (0);
// }
