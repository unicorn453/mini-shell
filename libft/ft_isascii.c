/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:51:26 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/10 17:18:23 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
//     int i = -10;
//     while (i < 130)
//     {
//         printf(" expected: %i got: %i\n",isascii(i),ft_isascii(i));
//         i++;
//     }
// }
