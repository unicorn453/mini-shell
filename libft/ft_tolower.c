/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:56:51 by dtrendaf          #+#    #+#             */
/*   Updated: 2024/10/10 17:16:09 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_tolower(int symbol)
{
	if (symbol >= 65 && symbol <= 90)
	{
		symbol += 32;
	}
	return (symbol);
}

// int main()
// {
//     char str[] = "Hello, World!";

//     for (int i = 0; str[i] != '\0'; i++)
// 	{
//         str[i] = ft_tolower(str[i]);
//     }

//     printf("%s\n", str);
//     return (0);
// }