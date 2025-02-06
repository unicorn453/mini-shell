/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:03:12 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/07 21:19:31 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

// int	main(void)
// {
// 	int i = -7;
// 	while (i < 15)
// 	{
// 		printf(" expected: %i got: %i\n",isdigit(48 + i),ft_isdigit(48 + i));
// 		i++;
// 	}
// }