/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:28:13 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/31 18:30:55 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int		i;
	int		is_min;
	long	result;
	int		sign_count;

	i = 0;
	is_min = 1;
	result = 0;
	sign_count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_min = -1;
		sign_count++;
		if (sign_count > 1)
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + str[i++] - 48;
	return (result * is_min);
}

// int	main(void)
// {
// 	char string[] = "    -214748364abc89";
// 	int result = ft_atoi(string);
// 	int result2 = atoi(string); 
	// printf("got: %i expected: %i", result,result2);
// }